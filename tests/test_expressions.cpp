#include <catch2/catch.hpp>

#include "../version_expression_evaluator/expression.hpp"

using namespace jsribar::version_expression;

TEST_CASE("Simple expressions evaluate value", "[expression]")
{
    SECTION("not_expression inverts the result")
    {
        comparison_expression_t cmp{ operator_t::greater_than , version_t{"1.0"}};
        not_expression_t not_exp{ cmp };

        {
            context_t context{ version_t{"1.0"} };

            REQUIRE(cmp.evaluate(context) == false);

            CHECK(not_exp.evaluate(context) == true);
        }
        {
            context_t context{ version_t{"2.0"} };

            REQUIRE(cmp.evaluate(context) == true);

            CHECK(not_exp.evaluate(context) == false);
        }
    }

    SECTION("and_expression returns logical AND of 2 expressions")
    {
        comparison_expression_t cmp1{ operator_t::greater_than_or_equal_to, version_t{"1.0"} };
        comparison_expression_t cmp2{ operator_t::less_than, version_t{"2.0"} };
        and_expression_t end_exp{ cmp1, cmp2 };

        {
            context_t context{ version_t{"0.9"} };
            CHECK(end_exp.evaluate(context) == false);
        }
        {
            context_t context{ version_t{"1.0"} };
            CHECK(end_exp.evaluate(context) == true);
        }
        {
            context_t context{ version_t{"1.5"} };
            CHECK(end_exp.evaluate(context) == true);
        }
        {
            context_t context{ version_t{"2.0"} };
            CHECK(end_exp.evaluate(context) == false);
        }
        {
            context_t context{ version_t{"3.0"} };
            CHECK(end_exp.evaluate(context) == false);
        }
    }

    SECTION("or_expression returns logical OR of 2 expressions")
    {
        comparison_expression_t cmp1{ operator_t::less_than_or_equal_to, version_t{"1.0"} };
        comparison_expression_t cmp2{ operator_t::greater_than, version_t{"2.0"} };
        or_expression_t or_exp{ cmp1, cmp2 };

        {
            context_t context{ version_t{"0.9"} };
            CHECK(or_exp.evaluate(context) == true);
        }
        {
            context_t context{ version_t{"1.0"} };
            CHECK(or_exp.evaluate(context) == true);
        }
        {
            context_t context{ version_t{"1.5"} };
            CHECK(or_exp.evaluate(context) == false);
        }
        {
            context_t context{ version_t{"2.0"} };
            CHECK(or_exp.evaluate(context) == false);
        }
        {
            context_t context{ version_t{"3.0"} };
            CHECK(or_exp.evaluate(context) == true);
        }
    }
}
