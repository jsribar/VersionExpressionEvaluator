#include <catch2/catch.hpp>

#include "../version_expression_evaluator/expression_parser.hpp"

using namespace jsribar::version_expression;

TEST_CASE("parse method creates expression object for simple comparison", "[parse]")
{
    SECTION("Equal to comparison")
    {
        constexpr auto text{ "version:=1.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == true);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == false);
        }
    }

    SECTION("Equal to comparison with ==")
    {
        constexpr auto text{ "version:==1.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == true);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == false);
        }
    }

    SECTION("Not equal to comparison")
    {
        constexpr auto text{ "version:!=1.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == false);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == true);
        }
    }

    SECTION("Less than comparison")
    {
        constexpr auto text{ "version:<2.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == true);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == false);
        }
    }

    SECTION("Less than or equal to comparison")
    {
        constexpr auto text{ "version:<=2.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == true);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == true);
        }
        {
            version_t version{ "3.0" };
            CHECK(expression->evaluate(version) == false);
        }
    }

    SECTION("Greater than comparison")
    {
        constexpr auto text{ "version:>1.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == false);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == true);
        }
    }

    SECTION("Greater than or equal to comparison")
    {
        constexpr auto text{ "version:>=2.0" };
        auto expression = parse(text);

        {
            version_t version{ "1.0" };
            CHECK(expression->evaluate(version) == false);
        }
        {
            version_t version{ "2.0" };
            CHECK(expression->evaluate(version) == true);
        }
        {
            version_t version{ "3.0" };
            CHECK(expression->evaluate(version) == true);
        }
    }
}

TEST_CASE("parse method creates object for expression with NOT operator", "[parse]")
{
    constexpr auto text{ "NOT version:=2.12.2" };
    auto expression = parse(text);

    {
        version_t version{ "2.12.1" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.12.2" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.12.3" };
        CHECK(expression->evaluate(version) == true);
    }
}

TEST_CASE("parse method creates object for expression with AND operator", "[parse]")
{
    constexpr auto text{ "version:>2.15.0 AND version:<=2.15.5" };
    auto expression = parse(text);

    {
        version_t version{ "2.15.0" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15.1" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.5" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.6" };
        CHECK(expression->evaluate(version) == false);
    }

}

TEST_CASE("parse method creates object for expression with OR operator", "[parse]")
{
    constexpr auto text{ "version:<=2.15.0 OR version:>2.15.5" };
    auto expression = parse(text);

    {
        version_t version{ "2.15.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.1" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15.5" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15.6" };
        CHECK(expression->evaluate(version) == true);
    }

}

TEST_CASE("parse method creates object for expression with AND and NOT operators", "[parse]")
{
    constexpr auto text{ "version:<=2.15.0 AND NOT version:=2.12.2" };
    auto expression = parse(text);

    {
        version_t version{ "2.15.1" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.14" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.12.2" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.12.1" };
        CHECK(expression->evaluate(version) == true);
    }
}

TEST_CASE("parse method creates object for expression with multiple AND and NOT operators", "[parse]")
{
    constexpr auto text{ "version:<=2.15.0 AND NOT version:=2.12.2 AND NOT version:=2.12.3" };
    const auto expression = parse(text);

    {
        version_t version{ "2.12.1" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.12.2" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.12.3" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.1" };
        CHECK(expression->evaluate(version) == false);
    }
}

TEST_CASE("parse method creates object for expression with multiple OR and AND operators", "[parse]")
{
    constexpr auto text{ "version:>=2.15.0 AND version:<2.20 OR version:>=3.0 AND version:<4.0" };
    auto expression = parse(text);

    {
        version_t version{ "2.12.1" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.20" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "3.0.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "3.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "4.0" };
        CHECK(expression->evaluate(version) == false);
    }
}

TEST_CASE("parse method creates object for expression with multiple AND and NOT operators and leading NOT", "[parse]")
{
    constexpr auto text{ "NOT version:>2.15.0 AND NOT version:=2.12.2 AND NOT version:=2.12.3" };
    auto expression = parse(text);

    {
        version_t version{ "2.12.1" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.12.2" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.12.3" };
        CHECK(expression->evaluate(version) == false);
    }
    {
        version_t version{ "2.15" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.0" };
        CHECK(expression->evaluate(version) == true);
    }
    {
        version_t version{ "2.15.1" };
        CHECK(expression->evaluate(version) == false);
    }
}

