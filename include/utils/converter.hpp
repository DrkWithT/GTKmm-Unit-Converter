#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <initializer_list>
#include <string>
#include <vector>
#include <map>

namespace demoapp::utils
{
    enum class LengthUnit
    {
        metric_km,
        metric_m, // metric base unit
        metric_cm,
        metric_mm,
        imperial_in,
        imperial_foot, // imperial base unit
        imperial_yard,
        imperial_mile
    };

    enum class ConversionDirection
    {
        in_metric,
        in_imperial,
        forward, // metric to imperial
        backward // imperial to metric
    };

    struct LengthEntry
    {
        std::string unit_name;
        LengthUnit unit_code;
        double base_factor;

        LengthEntry(const char* name_cstr, LengthUnit unit, double factor);

        [[nodiscard]] const std::string& viewName() const noexcept;
    };

    class LengthConverter
    {
    private:
        std::map<LengthUnit, LengthEntry> metric_map;
        std::map<LengthUnit, LengthEntry> imperial_map;

        [[nodiscard]] ConversionDirection deduceDirection(LengthUnit initial, LengthUnit result) const;

        [[nodiscard]] double convertInMetric(double input_len, LengthUnit input_unit, LengthUnit result_unit) const;

        [[nodiscard]] double convertInImperial(double input_len, LengthUnit input_unit, LengthUnit result_unit) const;

        [[nodiscard]] double convertMetricImperial(double input_len, LengthUnit input_unit, LengthUnit result_unit) const;

        [[nodiscard]] double convertImperialMetric(double input_len, LengthUnit input_unit, LengthUnit result_unit) const;

    public:
        LengthConverter(std::initializer_list<LengthEntry> metrics, std::initializer_list<LengthEntry> imperials);

        const LengthEntry& getUnitEntry(LengthUnit arg) const;

        [[nodiscard]] double convertLength(double input_len, LengthUnit input_unit, LengthUnit result_unit) const;
    };
}

#endif
