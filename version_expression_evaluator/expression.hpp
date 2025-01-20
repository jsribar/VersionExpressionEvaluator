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

#include "operators.hpp"
#include "version.hpp"

#include <memory>

namespace jsribar::version_expression {

class expression_t
{
public:
    virtual ~expression_t() = default;

    virtual bool evaluate(const version_t&) const = 0;

};

using expression_ptr = std::unique_ptr<expression_t>;

class not_expression_t : public expression_t
{
public:
    explicit not_expression_t(expression_ptr expression)
        : expression_m(std::move(expression))
    {
    }

    bool evaluate(const version_t&) const override;

private:
    const expression_ptr expression_m;
};


class and_expression_t : public expression_t
{
public:
    and_expression_t(expression_ptr lhs, expression_ptr rhs)
        : lhs_m(std::move(lhs))
        , rhs_m(std::move(rhs))
    {
    }

    bool evaluate(const version_t&) const override;

private:
    const expression_ptr lhs_m;
    const expression_ptr rhs_m;
};

class or_expression_t : public expression_t
{
public:
    or_expression_t(expression_ptr lhs, expression_ptr rhs)
        : lhs_m(std::move(lhs))
        , rhs_m(std::move(rhs))
    {
    }

    bool evaluate(const version_t&) const override;

private:
    const expression_ptr lhs_m;
    const expression_ptr rhs_m;
};

class comparison_expression_t : public expression_t
{
public:
    comparison_expression_t(operator_t comparison_operator, version_t version)
        : operator_m(comparison_operator)
        , version_m(std::move(version))
    {
    }

    bool evaluate(const version_t&) const override;

private:
    operator_t operator_m;
    version_t version_m;
};

}
