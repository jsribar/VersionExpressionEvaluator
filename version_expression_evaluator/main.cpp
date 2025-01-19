#include "expression_parser.hpp"

#include <iostream>

using namespace jsribar::version_expression;

int main()
{
    static constexpr auto text{ "version:<=2.15.0 AND NOT version:=2.12.2 AND NOT version:=2.12.3" };
    std::cout << "Expression: \"" << text << '\"' << std::endl;

    auto expression = parse(text);

    std::cout << std::boolalpha;

    std::cout << "For version 2.12.1 is " << expression->evaluate(version_t{"2.12.1"}) << std::endl; // true
    std::cout << "For version 2.15.0 is " << expression->evaluate(version_t{ "2.15.0" }) << std::endl; // true
    std::cout << "For version 2.12.2 is " << expression->evaluate(version_t{ "2.12.2" }) << std::endl; // false
    std::cout << "For version 2.12.3 is " << expression->evaluate(version_t{ "2.12.3" }) << std::endl; // false

}