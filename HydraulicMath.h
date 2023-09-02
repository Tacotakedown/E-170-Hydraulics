class HydraulicMath
{   
public:
    class PascalsLaw // will determine pressure, force, and area
    {
    public:
    static double getPressure(double force, double area);
    static double getForce(double pressure, double area);
    static double getArea(double pressure, double force);
    };
    class FlowRate //will determine flow rate, volume, and time to extend cylinder
    {
    public:
    static double getFlowRate(double volume, double time);
    static double getVolume(double flowRate, double time);
    static double getTime(double flowRate, double volume);
    };
    class Direction //will determine direction of flow
    {
    public:
    enum DirectionEnum;
    };
    class Cylinder //will determine cylinder volume
    {
    public:
    static double getCylinderVolume(double radius, double length);
    static double getCylinderLength(double radius, double volume);
    static double getArea(double radius);
    };
};


