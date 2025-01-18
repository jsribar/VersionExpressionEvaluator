#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../version_expression_evaluator/version.hpp"

using namespace jsribar::version_expression;

TEST_CASE("version_t constructor creates object from string", "[version_t]")
{
    SECTION("Empty string")
    {
        const auto& version = version_t("");
        CHECK(version.digits().empty());
    }

    SECTION("One number")
    {
        const auto& version = version_t("1");
        REQUIRE(version.digits().size() == 1);
        CHECK(version.digits()[0] == 1);
    }

    SECTION("Two numbers")
    {
        const auto& version = version_t("1.12");
        REQUIRE(version.digits().size() == 2);
        CHECK(version.digits()[0] == 1);
        CHECK(version.digits()[1] == 12);
    }

    SECTION("Three numbers")
    {
        const auto& version = version_t("1.12.99");
        REQUIRE(version.digits().size() == 3);
        CHECK(version.digits()[0] == 1);
        CHECK(version.digits()[1] == 12);
        CHECK(version.digits()[2] == 99);
    }

    SECTION("Two numbers, second followed by character")
    {
        const auto& version = version_t("1.12a");
        REQUIRE(version.digits().size() == 2);
        CHECK(version.digits()[0] == 1);
        CHECK(version.digits()[1] == 12);
    }

    SECTION("Two numbers followed by non-numeric component")
    {
        const auto& version = version_t("1.12.a");
        REQUIRE(version.digits().size() == 2);
        CHECK(version.digits()[0] == 1);
        CHECK(version.digits()[1] == 12);
    }
}

TEST_CASE("version_t comparison operators", "[version_t]")
{
    SECTION("Equal to operator")
    {
        CHECK(version_t("1") == version_t("1"));
        CHECK(version_t("1.2") == version_t("1.2"));

        CHECK_FALSE(version_t("1.2") == version_t("1.2.3"));
    }

    SECTION("Not equal operator")
    {
        CHECK(version_t("1") != version_t("2"));
        CHECK(version_t("1.2") != version_t("2.1"));
        CHECK(version_t("1.2") != version_t("1.2.3"));

        CHECK_FALSE(version_t("1") != version_t("1"));
    }

    SECTION("Less than operator")
    {
        CHECK(version_t("1") < version_t("2"));
        CHECK(version_t("1.2") < version_t("1.3"));

        CHECK(version_t("1.2") < version_t("1.2.0"));
        CHECK(version_t("1.2") < version_t("1.2.1"));
        
        CHECK_FALSE(version_t("3") < version_t("3"));
        CHECK_FALSE(version_t("1.3") < version_t("1.2"));
        CHECK_FALSE(version_t("1.2") < version_t("1.2"));
    }

    SECTION("Less than or equal to operator")
    {
        CHECK(version_t("1") <= version_t("1"));
        CHECK(version_t("1") <= version_t("2"));
        CHECK(version_t("1.2") <= version_t("1.2"));
        CHECK(version_t("1.2") <= version_t("1.3"));

        CHECK_FALSE(version_t("1.3") <= version_t("1.2"));
        CHECK_FALSE(version_t("1.2.0") < version_t("1.2"));
        CHECK_FALSE(version_t("1.2.1") < version_t("1.2"));
    }

    SECTION("Greater than operator")
    {
        CHECK(version_t("2") > version_t("1"));
        CHECK(version_t("1.3") > version_t("1.2"));
        CHECK(version_t("1.3.0") > version_t("1.3"));

        CHECK_FALSE(version_t("3") < version_t("3"));
        CHECK_FALSE(version_t("1.2") < version_t("1.2"));
        CHECK_FALSE(version_t("1.3") < version_t("1.2"));
        CHECK_FALSE(version_t("1.3") < version_t("1.2"));
    }

    SECTION("Greater than or equal to operator")
    {
        CHECK(version_t("1") >= version_t("1"));
        CHECK(version_t("2") >= version_t("1"));
        CHECK(version_t("1.2") >= version_t("1.2"));
        CHECK(version_t("1.3") >= version_t("1.2"));

        CHECK_FALSE(version_t("1.2") >= version_t("1.3"));
        CHECK_FALSE(version_t("1.2") >= version_t("1.2.0"));
    }
}
