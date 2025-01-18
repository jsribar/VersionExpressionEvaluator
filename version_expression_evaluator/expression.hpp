#pragma once

#include "version.hpp"

namespace jsribar::version_expression {

class context_t;

class boolean_expression
{
protected:
    boolean_expression() = default;

public:
    explicit boolean_expression(bool value)
        : value_m(value)
    {
    }
    virtual ~boolean_expression() = default;

    virtual bool evaluate(const context_t&) const
    {
        return value_m;
    }

private:
    bool value_m{ false };
};

class not_expression : public boolean_expression
{
public:
    explicit not_expression(const boolean_expression& boolean_expression)
        : expression_m(boolean_expression)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const boolean_expression& expression_m;
};

class and_expression : public boolean_expression
{
public:
    and_expression(const boolean_expression& lhs, const boolean_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const boolean_expression& lhs_m;
    const boolean_expression& rhs_m;
};

class or_expression : public boolean_expression
{
public:
    or_expression(const boolean_expression& lhs, const boolean_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const boolean_expression& lhs_m;
    const boolean_expression& rhs_m;
};

class value_expression
{
public:
    virtual ~value_expression() = default;

    virtual version_t evaluate(const context_t&) const = 0;
};

class version_constant_expression : public value_expression
{
public:
    explicit version_constant_expression(const version_t& version)
        : version_m(version)
    { }

    version_t evaluate(const context_t&) const override;

private:

    version_t version_m;
};

class version_variable_expression : public value_expression
{
public:
    version_t evaluate(const context_t&) const override;
};


class equal_expression : public boolean_expression
{
public:
    equal_expression(const value_expression& lhs, const value_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const value_expression& lhs_m;
    const value_expression& rhs_m;
};

class not_equal_expression : public boolean_expression
{
public:
    not_equal_expression(const value_expression& lhs, const value_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const value_expression& lhs_m;
    const value_expression& rhs_m;
};

class less_expression : public boolean_expression
{
public:
    less_expression(const value_expression& lhs, const value_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const value_expression& lhs_m;
    const value_expression& rhs_m;
};

class less_or_equal_expression : public boolean_expression
{
public:
    less_or_equal_expression(const value_expression& lhs, const value_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const value_expression& lhs_m;
    const value_expression& rhs_m;
};

class greater_expression : public boolean_expression
{
public:
    greater_expression(const value_expression& lhs, const value_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const value_expression& lhs_m;
    const value_expression& rhs_m;
};

class greater_or_equal_expression : public boolean_expression
{
public:
    greater_or_equal_expression(const value_expression& lhs, const value_expression& rhs)
        : lhs_m(lhs)
        , rhs_m(rhs)
    {
    }

    bool evaluate(const context_t&) const override;

private:
    const value_expression& lhs_m;
    const value_expression& rhs_m;
};

}
