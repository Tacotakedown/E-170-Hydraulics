#pragma once
#include <string>
#include "imgui.h"

class tools
{
public:
	static std::string BoolToString(bool i);
	static ImVec4 GetBoolColor(bool i);
};

