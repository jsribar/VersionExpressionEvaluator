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

#include "expression.hpp"

#include <cassert>

namespace jsribar::version_expression {

bool not_expression_t::evaluate(const version_t& version) const
{
    return !expression_m->evaluate(version);
}

bool and_expression_t::evaluate(const version_t& version) const
{
    return lhs_m->evaluate(version) && rhs_m->evaluate(version);
}

bool or_expression_t::evaluate(const version_t& version) const
{
    return lhs_m->evaluate(version) || rhs_m->evaluate(version);
}

bool comparison_expression_t::evaluate(const version_t& version) const
{
    switch (operator_m)
    {
    case operator_t::equal_to:
        return version == version_m;
    case operator_t::not_equal_to:
        return version != version_m;
    case operator_t::greater_than:
        return version > version_m;
    case operator_t::greater_than_or_equal_to:
        return version >= version_m;
    case operator_t::less_than:
        return version < version_m;
    case operator_t::less_than_or_equal_to:
        return version <= version_m;
    default:
        assert(false);
        break;
    }
    return false;
}

}