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