#include "context.hpp"
#include "expression.hpp"

namespace jsribar::version_expression {

bool not_expression::evaluate(const context_t& context) const
{
    return !expression_m.evaluate(context);
}

bool and_expression::evaluate(const context_t& context) const
{
    return lhs_m.evaluate(context) && rhs_m.evaluate(context);
}

bool or_expression::evaluate(const context_t& context) const
{
    return lhs_m.evaluate(context) || rhs_m.evaluate(context);
}

version_t version_variable_expression::evaluate(const context_t& context) const
{
    return context.version();
}

bool equal_expression::evaluate(const context_t&) const
{
    return false;
}

version_t version_constant_expression::evaluate(const context_t&) const
{
    return version_m;
}

bool not_equal_expression::evaluate(const context_t&) const
{
    return false;
}

bool less_expression::evaluate(const context_t&) const
{
    return false;
}

bool less_or_equal_expression::evaluate(const context_t&) const
{
    return false;
}

bool greater_expression::evaluate(const context_t&) const
{
    return false;
}

bool greater_or_equal_expression::evaluate(const context_t&) const
{
    return false;
}

}