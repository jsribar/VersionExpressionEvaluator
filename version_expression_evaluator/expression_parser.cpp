// SPDX-License-Identifier: MIT

/*
 * MIT License
 *
 * Copyright (c) 2025 by Julijan Šribar
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "expression_parser.hpp"
#include "expression.hpp"

#include <algorithm>
#include <cassert>
#include <stack>
#include <stdexcept>

namespace jsribar::version_expression {

constexpr std::string_view version_k{ "version:" };

namespace {

std::string_view trim_left(std::string_view text)
{
    if (const auto found = std::ranges::find_if(text, [](auto c) { return c != ' ' && c != '\t'; }); found != text.cend())
    {
        text.remove_prefix(found - text.cbegin());
    }
    return text;
}

void skip_mandatory_whitespaces(std::string_view& text)
{
    if (text.empty())
    {
        return;
    }

    switch (text.front()) {
    case ' ':
    case '\t':
        text = trim_left(text);
        break;
    default:
        throw std::runtime_error("Missing spaces");
        break;
    }
}

template <typename T>
T pop_value(std::stack<T>& stack)
{
    auto value = std::move(stack.top());
    stack.pop();
    return value;
}

int number_of_operands(operator_t op)
{
    switch (op)
    {
    case operator_t::not_op:
        return 1;
    case operator_t::and_op:
    case operator_t::or_op:
        return 2;
    default:
        assert(false);
        return 0;
    }
}

int get_precedence(operator_t op)
{
    switch (op)
    {
    case operator_t::or_op:
        return 1;
    case operator_t::and_op:
        return 2;
    case operator_t::not_op:
        return 3;
    default:
        assert(false);
        return 0;
    }
}

void consume_version_token(std::string_view& text)
{
    if (text.starts_with(version_k))
    {
        text.remove_prefix(version_k.size());
    }
    else
    {
        throw std::runtime_error("VERSION expected");
    }
}

operator_t consume_operator(std::string_view& text, const auto& operators)
{
    if (const auto found = std::ranges::find_if(operators, [&text](const auto& t) { return text.starts_with(t); }, &operator_definition_t::token); found != operators.cend())
    {
        text.remove_prefix(found->token.size());
        return found->op;
    }
    throw std::runtime_error("Invalid operator");
}

version_t consume_version(std::string_view& text)
{
    const auto end = std::ranges::find_if(text, [](char c) { return c == ' ' || c == '\t'; });
    const size_t length = std::distance(text.begin(), end);
    const auto value = text.substr(0, length);
    text.remove_prefix(length);
    return version_t(value);
}

// Extract and evaluate operations of same precedence.
void evaluate_expression_from_top(std::stack<operator_t>& operators, std::stack<expression_ptr>& output)
{
    // Local stacks for evaluation from left to right.
    std::stack<expression_ptr> top_expressions{};
    std::stack<operator_t> top_operators{};

    int precedence = get_precedence(operators.top());
    top_expressions.push(pop_value(output));

    do
    {
        top_operators.push(pop_value(operators));
        int n = number_of_operands(top_operators.top());
        while (--n > 0)
        {
            top_expressions.push(pop_value(output));
        }
    } while (!operators.empty() && get_precedence(operators.top()) == precedence);

    // Evaluates operations from the local stack and pushes the resulting expression to the output stack.
    auto lhs = pop_value(top_expressions);
    while (!top_operators.empty())
    {
        auto op = pop_value(top_operators);
        switch (op)
        {
        case operator_t::not_op:
            lhs = std::make_unique<not_expression_t>(std::move(lhs));
            break;
        case operator_t::and_op:
            lhs = std::make_unique<and_expression_t>(std::move(lhs), pop_value(top_expressions));
            break;
        case operator_t::or_op:
            lhs = std::make_unique<or_expression_t>(std::move(lhs), pop_value(top_expressions));
            break;
        default:
            assert(false);
            break;
        }
    }
    output.push(std::move(lhs));
}

void push_operator(operator_t op, std::stack<operator_t>& operators, std::stack<expression_ptr>& output)
{
    // Evaluate operations of higher precedence first.
    while (!operators.empty() && get_precedence(op) < get_precedence(operators.top()))
    {
        evaluate_expression_from_top(operators, output);
    }
    operators.push(op);
}

expression_ptr finalize_expression(std::stack<operator_t>& operators, std::stack<expression_ptr>& output)
{
    while (!operators.empty())
    {
        evaluate_expression_from_top(operators, output);
    }
    return pop_value(output);
}

}

expression_ptr parse(std::string_view text)
{
    std::stack<operator_t> operators{};
    std::stack<expression_ptr> output{};

    bool version_processed{ false };

    while (!text.empty())
    {
        if (version_processed)
        {
            push_operator(consume_operator(text, boolean_operators_k), operators, output);
            skip_mandatory_whitespaces(text);
        }
        if (text.starts_with("NOT"))
        {
            push_operator(consume_operator(text, boolean_operators_k), operators, output);
            skip_mandatory_whitespaces(text);
        }
        consume_version_token(text);
        const auto op = consume_operator(text, comparison_operators_k);
        output.push(std::make_unique<comparison_expression_t>(op, consume_version(text)));
        skip_mandatory_whitespaces(text);
        version_processed = true;
    }

    return finalize_expression(operators, output);
}

}
