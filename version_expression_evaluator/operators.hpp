#pragma once

#include <array>
#include <string_view>

namespace jsribar::version_expression {

enum class operator_t
{
    not_op,
    and_op,
    or_op,
    equal_to,
    not_equal_to,
    greater_than_or_equal_to,
    greater_than,
    less_than_or_equal_to,
    less_than,
};

struct operator_definition_t
{
    std::string_view token;
    operator_t op;
};

// Order of greater... and less... tokens respectively is important to resolve them correctly.
inline constexpr auto comparison_operators_k = std::to_array<operator_definition_t>({
    { "=", operator_t::equal_to },
    { "!=", operator_t::not_equal_to },
    { ">=", operator_t::greater_than_or_equal_to },
    { ">", operator_t::greater_than },
    { "<=", operator_t::less_than_or_equal_to },
    { "<", operator_t::less_than },
    });

inline constexpr auto boolean_operators_k = std::to_array<operator_definition_t>({
    { "NOT", operator_t::not_op },
    { "AND", operator_t::and_op },
    { "OR", operator_t::or_op },
    });

}