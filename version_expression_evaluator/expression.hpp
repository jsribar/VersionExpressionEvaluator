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
