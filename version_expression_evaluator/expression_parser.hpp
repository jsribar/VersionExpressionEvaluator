#pragma once

#include "expression.hpp"

#include <memory>

namespace jsribar::version_expression {

std::unique_ptr<expression_t> parse(std::string_view);

}
