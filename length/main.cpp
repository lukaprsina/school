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

    double ConvertTo(double length, Unit from, Unit to)
    {
        auto a = k_Map.at(from);
        auto b = k_Map.at(to);
        auto c = length;
        auto d = a / b * c;
        return d;
    }

    std::string ToMetric()
    {
        double remaining = m_Length;

        double meters = ConvertTo(remaining, DefaultUnit, Unit::Meters);
        remaining -= ConvertTo(std::floor(meters), Unit::Meters, DefaultUnit);

        double decimeters = ConvertTo(remaining, DefaultUnit, Unit::Decimeters);
        remaining -= ConvertTo(std::floor(decimeters), Unit::Decimeters, DefaultUnit);

        double centimeters = ConvertTo(remaining, DefaultUnit, Unit::Centimeters);
        remaining -= ConvertTo(std::floor(centimeters), Unit::Centimeters, DefaultUnit);

        double milimeters = ConvertTo(remaining, DefaultUnit, Unit::Milimeters);

        return std::to_string(static_cast<int>(std::floor(meters))) + "m " +
               std::to_string(static_cast<int>(std::floor(decimeters))) + "dm " +
               std::to_string(static_cast<int>(std::floor(centimeters))) + "cm " +
               std::to_string(static_cast<int>(std::round(milimeters))) + "mm";
    }

private:
    double m_Length{0.0f};
    Unit m_Unit = DefaultUnit;
};

int main(int, char **)
{
    Length<Unit::Inches> length(1);
    std::cout << length.ToMetric() << std::endl;
}
