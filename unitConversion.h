class UnitConversion
{
    public:
    class Length
    {
        public:
        double inchesToCm(double inches);
        double cmToInches(double cm);
    };
    class Area
    {
        public:
        double squareInchesToSquareCm(double squareInches);
        double squareCmToSquareInches(double squareCm);
    };
    class Volume
    {
        public:
        double cubicInchesToCubicCm(double cubicInches);
        double cubicCmToCubicInches(double cubicCm);
    };
    class Pressure
    {
        public:
        double psiToPascals(double psi);
        double psiToBar(double psi);
        double pascalsToBar(double pascals);
        double pascalsToPsi(double pascals);
        double barToPascals(double bar);
        double barToPsi(double bar);
    };
    class Force
    {
        public:
        double poundForceToNewton(double poundForce);
        double newtonToPoundForce(double newton);
    };
    class FlowRate
    {
        public:
        double gallonsPerMinuteToLitersPerMinute(double gallonsPerMinute);
        double litersPerMinuteToGallonsPerMinute(double litersPerMinute);
    };
};