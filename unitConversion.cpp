#include "unitConversion.h"

double UnitConversion::Length::inchesToCm(double inches)
{
    return inches * 2.54;
}

double UnitConversion::Length::cmToInches(double cm)
{
    return cm / 2.54;
}

double UnitConversion::Area::squareInchesToSquareCm(double squareInches)
{
    return squareInches * 6.4516;
}

double UnitConversion::Area::squareCmToSquareInches(double squareCm)
{
    return squareCm / 6.4516;
}

double UnitConversion::Volume::cubicInchesToCubicCm(double cubicInches)
{
    return cubicInches * 16.387;
}

double UnitConversion::Volume::cubicCmToCubicInches(double cubicCm)
{
    return cubicCm / 16.387;
}

double UnitConversion::Pressure::psiToPascals(double psi)
{
    return psi * 6894.757;
}

double UnitConversion::Pressure::psiToBar(double psi)
{
    return psi * 0.06894757;
}

double UnitConversion::Pressure::pascalsToBar(double pascals)
{
    return pascals * 0.00001;
}

double UnitConversion::Pressure::pascalsToPsi(double pascals)
{
    return pascals * 0.0001450377;
}

double UnitConversion::Pressure::barToPascals(double bar)
{
    return bar * 100000;
}

double UnitConversion::Pressure::barToPsi(double bar)
{
    return bar * 14.50377;
}

double UnitConversion::Force::poundForceToNewton(double poundForce)
{
    return poundForce * 4.448222;
}

double UnitConversion::Force::newtonToPoundForce(double newton)
{
    return newton * 0.2248089;
}

double UnitConversion::FlowRate::gallonsPerMinuteToLitersPerMinute(double gallonsPerMinute)
{
    return gallonsPerMinute * 3.785412;
}

double UnitConversion::FlowRate::litersPerMinuteToGallonsPerMinute(double litersPerMinute)
{
    return litersPerMinute * 0.2641721;
}
