#include "context.hpp"
#include "expression.hpp"

#include <cassert>

namespace jsribar::version_expression {

bool not_expression_t::evaluate(const context_t& context) const
{
    return !expression_m.evaluate(context);
}

bool and_expression_t::evaluate(const context_t& context) const
{
    return lhs_m.evaluate(context) && rhs_m.evaluate(context);
}

bool or_expression_t::evaluate(const context_t& context) const
{
    return lhs_m.evaluate(context) || rhs_m.evaluate(context);
}

bool comparison_expression_t::evaluate(const context_t& context) const
{
    switch (operator_m)
    {
    case operator_t::equal_to:
        return context.version() == version_m;
    case operator_t::not_equal:
        return context.version() != version_m;
    case operator_t::greater_than:
        return context.version() > version_m;
    case operator_t::greater_than_or_equal_to:
        return context.version() >= version_m;
    case operator_t::less_than:
        return context.version() < version_m;
    case operator_t::less_than_or_equal_to:
        return context.version() <= version_m;
    default:
        assert(false);
        break;
    }
    return false;
}

}