#include <iostream>
#include <unordered_map>
#include <cmath>

enum class Unit
{
    Milimeters,
    Centimeters,
    Decimeters,
    Meters,
    Inches
};

const std::unordered_map<Unit, double> k_Map = {
    {Unit::Milimeters, 1},
    {Unit::Centimeters, 10},
    {Unit::Decimeters, 100},
    {Unit::Meters, 1000},
    {Unit::Inches, 25.4}};

template <Unit DefaultUnit = Unit::Centimeters>
class Length
{
public:
    Length(double length)
        : m_Length(length)
    {
    }

    double Convert(double length, Unit from, Unit to)
    {
        return length * k_Map.at(from) / k_Map.at(to);
    }

    std::string ToMetric()
    {
        double remaining = m_Length;

        double meters = Convert(remaining, DefaultUnit, Unit::Meters);
        remaining -= Convert(std::floor(meters), Unit::Meters, DefaultUnit);

        double decimeters = Convert(remaining, DefaultUnit, Unit::Decimeters);
        remaining -= Convert(std::floor(decimeters), Unit::Decimeters, DefaultUnit);

        double centimeters = Convert(remaining, DefaultUnit, Unit::Centimeters);
        remaining -= Convert(std::floor(centimeters), Unit::Centimeters, DefaultUnit);

        double milimeters = Convert(remaining, DefaultUnit, Unit::Milimeters);

        return std::to_string(static_cast<int>(std::floor(meters))) + "m " +
               std::to_string(static_cast<int>(std::floor(decimeters))) + "dm " +
               std::to_string(static_cast<int>(std::floor(centimeters))) + "cm " +
               std::to_string(static_cast<int>(std::round(milimeters))) + "mm";
    }

private:
    double m_Length;
    Unit m_Unit = DefaultUnit;
};

int main(int, char **)
{
    Length<Unit::Inches> length(1);
    std::cout << length.ToMetric() << std::endl;
}
