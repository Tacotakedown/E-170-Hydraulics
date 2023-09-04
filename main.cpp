#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include "system.h"
#include "tools.h"
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>
#include <cmath>


static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef std::atomic<int> atomicInt;
typedef std::atomic<bool> atomicBool;
typedef std::atomic<double> atomicDouble;
/*
globals to be acessed outside of simulation loop for render purposes
*/
//int pressure = 0;

atomicBool simRunning = false;
atomicDouble pressure(0);
static atomicBool mlgRetract(false);
static atomicBool mlgExtend(false);
std::atomic<int>fluidLevel(0);
std::atomic<system3Values>system3atomic;
std::atomic<system1Values>monkeyManager;
atomicInt rpm(0);
atomicBool pumpFailed(false);
static atomicBool ElecPump1(false);

void simulation()
{
    const double simulationRate = 120.0;
    const std::chrono::duration<double> timeStep(1.0 / simulationRate);

    while (1==1)
    {
       
        system1Values monkey = System::System1(true,
            pressure,
            ElecPump1.load(std::memory_order_relaxed),
            true,
            true,
            true,
            true,
            100);

        monkeyManager.store(monkey, std::memory_order_relaxed);
        pressure.store(monkey.pressure, std::memory_order_relaxed);
        

        const system3Values system3atomicPrewrite = system3atomic.load(std::memory_order_relaxed);
        system3Values system3s = System::System3(pumpFailed.load(std::memory_order_relaxed),
            monkey.pressure,
            system3atomicPrewrite.mlgCylinderExtension,
            system3atomicPrewrite.mlgCylinderVolume,
            mlgRetract.load(std::memory_order_relaxed),
            mlgExtend.load(std::memory_order_relaxed),
            true,
            true,
            true,
            true,
            true,
            system3atomicPrewrite.pressure);

        rpm.store(system3s.rpm, std::memory_order_relaxed);
        pumpFailed.store(system3s.pumpFailed, std::memory_order_relaxed);
        system3atomic.store(system3s, std::memory_order_relaxed);

        std::this_thread::sleep_for(timeStep);

    }
}



int main(int, char**)
{

    


    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"OBJ_E170", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Real Niggaz Debug Menu dont FW it", WS_MAXIMIZEBOX, 100, 100, 1920, 1080, nullptr, nullptr, wc.hInstance, nullptr);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("C:\\titillium.ttf", 32.0f);
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(9.0f, 9.0f);
    style.FramePadding = ImVec2(9.0f, 7.0f);
    style.CellPadding = ImVec2(8.0f, 6.0f);
    style.ItemSpacing = ImVec2(20.0f, 3.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.IndentSpacing = 15.0f;
    style.ScrollbarSize = 12.0f;
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.GrabMinSize = 15.0f;
    style.WindowBorderSize = 0.0f;
    style.ChildBorderSize = 0.0f;
    style.PopupBorderSize = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.WindowRounding = 12.0f;
    style.ChildRounding = 12.0f;
    style.FrameRounding = 7.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 12.0f;
    style.TabRounding = 12.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.01f, 0.01f, 0.07f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.04f, 0.02f, 0.48f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.09f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.09f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.02f, 0.02f, 0.96f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.85f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.53f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.43f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.88f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.98f, 0.26f, 0.26f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.00f, 0.00f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.00f, 0.00f, 0.80f);
    colors[ImGuiCol_Separator] = ImVec4(0.59f, 0.00f, 0.00f, 0.23f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.59f, 0.00f, 0.00f, 0.23f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.00f, 0.00f, 0.23f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.01f, 0.01f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.01f, 0.01f, 0.98f);
    colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);
    bool done = false;


    std::thread sim(simulation);


    while (!done)
    {
       
        MSG msg;
       
        const system3Values system3atomicPostwrite = system3atomic.load(std::memory_order_relaxed);
        system1Values monkeySystemReturn = monkeyManager.load(std::memory_order_relaxed);
       double pressureReturn = pressure.load(std::memory_order_relaxed);
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize({ 1920,1080 });
    
        ImGui::Begin("Real Niggas Debug Menu",nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoCollapse| ImGuiWindowFlags_AlwaysAutoResize);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        ImGui::BeginChild("##Left", ImVec2(ImGui::GetContentRegionAvail().x / 3.0f, ImGui::GetContentRegionAvail().y / 1.1f));
        ImGui::Text("PressureL: %f", pressureReturn);

        ImGui::PushStyleColor(ImGuiCol_Text, monkeySystemReturn.OutboardBrakes ? ImVec4(0, 255, 0, 255) : ImVec4(255, 0, 0, 255));
        ImGui::Text("OutboardBrakes");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, monkeySystemReturn.LR_3_4_MfSpoiler ? ImVec4(0, 255, 0, 255) : ImVec4(255, 0, 0, 255));
        ImGui::Text("LR_3_4_MfSpoiler");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, monkeySystemReturn.L_ThrustReverser ? ImVec4(0, 255, 0, 255) : ImVec4(255, 0, 0, 255));
        ImGui::Text("L_Thrust Reverser");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, monkeySystemReturn.UpperRudder ? ImVec4(0, 255, 0, 255) : ImVec4(255, 0, 0, 255));
        ImGui::Text("Upper Rudder");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, monkeySystemReturn.L_OutboardElev ? ImVec4(0, 255, 0, 255) : ImVec4(255, 0, 0, 255));
        ImGui::Text("L_OutboardElevator");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, monkeySystemReturn.LR_2_GroundSpoilers? ImVec4(0, 255, 0, 255) :ImVec4(255,0,0,255));
        ImGui::Text("LR_2_GroundSpoilers");
        ImGui::PopStyleColor();

        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(0, 0, 0, 200).Value);
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::PopStyleColor();
        ImGui::SameLine();


        ImGui::BeginChild("##Center", ImVec2(ImGui::GetContentRegionAvail().x / 2.0f, ImGui::GetContentRegionAvail().y/1.1f));

        int roundedPressure = (int)pressureReturn + abs(((int)pressureReturn % 25)-25);
        ImGui::Text("PressureRounded (displays): %i", roundedPressure);
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(0, 0, 0, 200).Value);
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::PopStyleColor();
        ImGui::SameLine();


        ImGui::BeginChild("##Right", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 1.1f));
     
        ImGui::Text("Cylinder extension: %f", system3atomicPostwrite.mlgCylinderExtension);

   
        draw_list->AddRectFilled(ImVec2(500, 550), ImVec2((500 + system3atomicPostwrite.mlgCylinderExtension * 500) , 500), ImColor(192, 198, 209));
        draw_list->AddRectFilled(ImVec2(00, 490), ImVec2(500, 560), ImColor(81, 82, 84));
        draw_list->AddRectFilled(ImVec2(460, 480), ImVec2(500, 570), ImColor(172, 178, 189));
        draw_list->AddRectFilled(ImVec2(00, 480), ImVec2(40, 570), ImColor(172, 178, 189));
        static bool ElecPump1Checkbox;
        static bool mlgRetractBox;
        static bool mlgExtendBox;
        ImGui::Checkbox("ElecPump 1", &ElecPump1Checkbox);
        ImGui::Checkbox("Extend Cylinder", &mlgExtendBox);
        ImGui::Checkbox("Retract Cylinder", &mlgRetractBox);
        static int rpmSlider = 0;
        ImGui::SliderInt("RPM of E-pump:", &rpmSlider, 0, 4000);
        ImGui::PushStyleColor(ImGuiCol_Text, system3atomicPostwrite.limitSwitch ? ImVec4(0, 255, 0, 255) : ImVec4(255, 0, 0, 255));
        ImGui::Text("Limit Switch");
        ImGui::PopStyleColor();
        rpm.store(rpmSlider, std::memory_order_relaxed);
        mlgRetract.store(mlgRetractBox, std::memory_order_relaxed);
        mlgExtend.store(mlgExtendBox, std::memory_order_relaxed);
        ElecPump1.store(ElecPump1Checkbox, std::memory_order_relaxed);
        ImGui::EndChild();
        ImGui::Separator();
        ImGui::BeginChild("##Bottom", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
        ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));

        ImGui::EndChild();
        
        ImGui::End();

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
  
    }
    sim.join();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}


bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); 
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;

    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) 
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
