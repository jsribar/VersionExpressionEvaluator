#include <catch2/catch.hpp>

#include "../version_expression_evaluator/expression.hpp"

using namespace jsribar::version_expression;

TEST_CASE("Simple expressions evaluate value", "[expression]")
{
    SECTION("not_expression inverts the result")
    {
        comparison_expression_t cmp{ operator_t::greater_than, version_t{ "1.0" } };
        not_expression_t not_exp{ std::make_unique<comparison_expression_t>(cmp) };

        {
            version_t version{ "1.0" };

            REQUIRE(cmp.evaluate(version) == false);

            CHECK(not_exp.evaluate(version) == true);
        }
        {
            version_t version{ "2.0" };

            REQUIRE(cmp.evaluate(version) == true);

            CHECK(not_exp.evaluate(version) == false);
        }
    }

    SECTION("and_expression returns logical AND of 2 expressions")
    {
        comparison_expression_t cmp1{ operator_t::greater_than_or_equal_to, version_t{ "1.0" } };
        comparison_expression_t cmp2{ operator_t::less_than, version_t{ "2.0" } };
        and_expression_t end_exp{ std::make_unique<comparison_expression_t>(cmp1), std::make_unique<comparison_expression_t>(cmp2) };

        {
            version_t version{ "0.9" };

            REQUIRE(cmp1.evaluate(version) == false);
            REQUIRE(cmp2.evaluate(version) == true);

            CHECK(end_exp.evaluate(version) == false);
        }
        {
            version_t version{ "1.0" };

            REQUIRE(cmp1.evaluate(version) == true);
            REQUIRE(cmp2.evaluate(version) == true);

            CHECK(end_exp.evaluate(version) == true);
        }
        {
            version_t version{ "1.5" };

            REQUIRE(cmp1.evaluate(version) == true);
            REQUIRE(cmp2.evaluate(version) == true);

            CHECK(end_exp.evaluate(version) == true);
        }
        {
            version_t version{ "2.0" };

            REQUIRE(cmp1.evaluate(version) == true);
            REQUIRE(cmp2.evaluate(version) == false);

            CHECK(end_exp.evaluate(version) == false);
        }
        {
            version_t version{ "3.0" };
            CHECK(end_exp.evaluate(version) == false);
        }
    }

    SECTION("or_expression returns logical OR of 2 expressions")
    {
        comparison_expression_t cmp1{ operator_t::less_than_or_equal_to, version_t{ "1.0" } };
        comparison_expression_t cmp2{ operator_t::greater_than, version_t{ "2.0" } };
        or_expression_t or_exp{ std::make_unique<comparison_expression_t>(cmp1), std::make_unique<comparison_expression_t>(cmp2) };

        {
            version_t version{ "0.9" };

            REQUIRE(cmp1.evaluate(version) == true);
            REQUIRE(cmp2.evaluate(version) == false);

            CHECK(or_exp.evaluate(version) == true);
        }
        {
            version_t version{ "1.0" };

            REQUIRE(cmp1.evaluate(version) == true);
            REQUIRE(cmp2.evaluate(version) == false);

            CHECK(or_exp.evaluate(version) == true);
        }
        {
            version_t version{ "1.5" };

            REQUIRE(cmp1.evaluate(version) == false);
            REQUIRE(cmp2.evaluate(version) == false);

            CHECK(or_exp.evaluate(version) == false);
        }
        {
            version_t version{ "2.0" };

            REQUIRE(cmp1.evaluate(version) == false);
            REQUIRE(cmp2.evaluate(version) == false);

            CHECK(or_exp.evaluate(version) == false);
        }
        {
            version_t version{ "3.0" };

            REQUIRE(cmp1.evaluate(version) == false);
            REQUIRE(cmp2.evaluate(version) == true);

            CHECK(or_exp.evaluate(version) == true);
        }
    }
}
