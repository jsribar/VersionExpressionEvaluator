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

#include "version.hpp"

#include <optional>

namespace jsribar::version_expression {

version_t::version_t(std::string_view str)
{
    while (!str.empty())
    {
        auto delimiter = std::min(str.find('.'), str.size());
        const auto num = to_int(str.substr(0, delimiter));
        if (!num)
        {
            break;
        }
        digits_m.push_back(*num);
        str.remove_prefix(std::min(delimiter + 1, str.size()));
    }
}

std::optional<int> version_t::to_int(std::string_view str) const
{
    int result = 0;
    size_t pos = 0;
    while (pos < str.size())
    {
        const char c = str.at(pos);
        if (c < '0' || c > '9')
        {
            if (pos == 0)
            {
                return {};
            }
            break;
        }
        result *= 10;
        result += c - '0';
        ++pos;
    }

    return result;
}

}