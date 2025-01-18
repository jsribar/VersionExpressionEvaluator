#pragma once

#include "context.hpp"
#include "operators.hpp"
#include "version.hpp"

namespace jsribar::version_expression {

class boolean_expression_t
{
public:
    virtual ~boolean_expression_t() = default;

    virtual bool evaluate(const context_t&) const = 0;

};

class not_expression_t : public boolean_expression_t
{
public:
    explicit not_expression_t(const boolean_expression_t& boolean_expression_t)
        : expression_m(boolean_expression_t)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const boolean_expression_t& expression_m;
};

class and_expression_t : public boolean_expression_t
{
public:
    and_expression_t(const boolean_expression_t& lhs, const boolean_expression_t& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const boolean_expression_t& lhs_m;
    const boolean_expression_t& rhs_m;
};

class or_expression_t : public boolean_expression_t
{
public:
    or_expression_t(const boolean_expression_t& lhs, const boolean_expression_t& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const boolean_expression_t& lhs_m;
    const boolean_expression_t& rhs_m;
};

class comparison_expression_t : public boolean_expression_t
{
public:
    comparison_expression_t(operator_t comparison_operator, const version_t& version)
        : operator_m(comparison_operator)
        , version_m(version)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    operator_t operator_m;
    version_t version_m;
};

}
