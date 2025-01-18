#pragma once

#include "context.hpp"
#include "version.hpp"

namespace jsribar::version_expression {

class context_t
{
public:

    explicit context_t(version_t version_t)
        : version_m(std::move(version_t))
    {
    }

    const version_t& version() const
    {
        return version_m;
    }

private:
    version_t version_m;
};

}