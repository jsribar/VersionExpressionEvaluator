// SPDX-License-Identifier: MIT

/*
 * MIT License
 *
 * Copyright (c) 2025 by Julijan Šribar
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

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
    { "==", operator_t::equal_to },
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