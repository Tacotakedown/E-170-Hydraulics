

class HydraulicMath
{

    
public:
    class PascalsLaw // will determine pressure, force, and area
    {
    public:
    double getPressure(double force, double area);
    double getForce(double pressure, double area);
    double getArea(double pressure, double force);
    };
    class FlowRate //will determine flow rate, volume, and time to extend cylinder
    {
    public:
    double getFlowRate(double volume, double time);
    double getVolume(double flowRate, double time);
    double getTime(double flowRate, double volume);
    };
    class Direction //will determine direction of flow
    {
    public:
    enum DirectionEnum {IN=0, OUT=1};
    };

};


