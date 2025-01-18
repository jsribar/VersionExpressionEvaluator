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