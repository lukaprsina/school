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

class Length
{
public:
    Length(double length, Unit unit)
        : m_Length(length), m_Unit(unit)
    {
    }

    double Convert(double length, Unit from, Unit to) const
    {
        return length * k_Map.at(from) / k_Map.at(to);
    }

    std::string ToMetric() const
    {
        double remaining = m_Length;

        double meters = Convert(remaining, m_Unit, Unit::Meters);
        remaining -= Convert(std::floor(meters), Unit::Meters, m_Unit);

        double decimeters = Convert(remaining, m_Unit, Unit::Decimeters);
        remaining -= Convert(std::floor(decimeters), Unit::Decimeters, m_Unit);

        double centimeters = Convert(remaining, m_Unit, Unit::Centimeters);
        remaining -= Convert(std::floor(centimeters), Unit::Centimeters, m_Unit);

        double milimeters = Convert(remaining, m_Unit, Unit::Milimeters);

        return std::to_string(static_cast<int>(std::floor(meters))) + "m " +
               std::to_string(static_cast<int>(std::floor(decimeters))) + "dm " +
               std::to_string(static_cast<int>(std::floor(centimeters))) + "cm " +
               std::to_string(static_cast<int>(std::round(milimeters))) + "mm";
    }

    friend std::ostream &operator<<(std::ostream &stream, const Length &length)
    {
        return stream << length.ToMetric();
    }

private:
    double m_Length{0.0f};
    Unit m_Unit{Unit::Centimeters};
};

int main(int, char **)
{
    Length length(1, Unit::Inches);
    std::cout << length << std::endl;
}
