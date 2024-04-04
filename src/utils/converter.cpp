/**
 * @file converter.cpp
 * @author DrkWithT
 * @brief Implements conversion utilities.
 * @date 2024-04-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "utils/converter.hpp"

namespace demoapp::utils
{
    using ConvertMode = ConversionDirection;

    constexpr double bad_placeholder = -1.0;
    constexpr double m_to_ft = 3.28;

    LengthEntry::LengthEntry(const char* name_cstr, LengthUnit unit, double factor)
    : unit_name {name_cstr}, unit_code {unit}, base_factor {factor} {}

    const std::string& LengthEntry::viewName() const
    {
        return unit_name;
    }

    [[nodiscard]] ConversionDirection LengthConverter::deduceDirection(LengthUnit initial, LengthUnit result) const
    {
        if (initial <= LengthUnit::metric_mm && result <= LengthUnit::metric_mm)
            return ConversionDirection::in_metric;

        if (initial >= LengthUnit::imperial_in && result >= LengthUnit >= LengthUnit::imperial_in)
            return ConversionDirection::in_imperial;

        if (initial <= LengthUnit::metric_mm && result >= LengthUnit::imperial_in)
            return ConversionDirection::forward;

        return ConversionDirection::backward;
    }

    [[nodiscard]] double LengthConverter::convertInMetric(double input_len, LengthUnit input_unit, LengthUnit result_unit) const
    {
        double start_factor = metric_map.at(input_unit).base_factor;
        double end_factor = metric_map.at(result_unit).base_factor;
        double as_meters = input_len * start_factor;

        if (start_factor < end_factor)
            return as_meters / end_factor;

        return as_meters * end_factor;
    }

    [[nodiscard]] double LengthConverter::convertInImperial(double input_len, LengthUnit input_unit, LengthUnit result_unit) const
    {
        double start_factor = imperial_map.at(input_unit).base_factor;
        double end_factor = imperial_map.at(result_unit).base_factor;
        double as_feet = input_len * start_factor;

        if (start_factor < end_factor)
            return as_feet / end_factor;

        return as_feet * end_factor;
    }

    [[nodiscard]] double LengthConverter::convertMetricImperial(double input_len, LengthUnit input_unit, LengthUnit result_unit) const
    {
        double start_factor = metric_map.at(input_unit).base_factor;
        double end_factor = imperial_map.at(result_unit).base_factor;

        return input_len * start_factor * m_to_ft / end_factor;
    }

    [[nodiscard]] double LengthConverter::convertImperialMetric(double input_len, LengthUnit input_unit, LengthUnit result_unit)
    {
        double start_factor = imperial_map.at(input_unit).base_factor;
        double end_factor = metric_map.at(result_unit).base_factor;

        return input_len * start_factor / (m_to_ft * end_factor);
    }

    LengthConverter::LengthConverter(std::initializer_list<LengthEntry> imperials, std::initializer_list<LengthEntry> metrics)
    : metric_map {}, imperial_map {}
    {
        for (const auto& i_item : imperials)
            imperial_map.insert(i_item.unit_code, i_item);
        
        for (const auto& m_item : metrics)
            metric_map.insert(m_item.unit_code, m_item);
    }

    const LengthEntry& LengthConverter::getUnitEntry(LengthUnit arg) const
    {
        if (metric_map.find(arg) != metric_map.end())
            return metric_map.at(arg);

        return imperial_map.at(arg);
    }

    [[nodiscard]] double LengthConverter::convertLength(double input_len, LengthUnit input_unit, LengthUnit result_unit) const
    {
        auto convert_mode = deduceDirection(input_unit, result_unit);
        double result = bad_placeholder;

        switch (convert_mode)
        {
        case ConvertMode::in_metric:
            result = convertInMetric(input_len, input_unit, result_unit);
            break;
        case ConvertMode::in_imperial:
            result = convertInImperial(input_len, input_unit, result_unit);
            break;
        case ConvertMode::forward:
            result = convertMetricImperial(input_len, input_unit, result_unit);
            break;
        case ConvertMode::backward:
            result = convertImperialMetric(input_len, input_unit, result_unit);
            break;
        default:
            break;
        }

        return result;
    }
}
