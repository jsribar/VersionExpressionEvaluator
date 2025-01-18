#pragma once

#include <optional>
#include <string_view>
#include <vector>

namespace jsribar::version_expression {

class version_t
{
public:
    explicit version_t(std::string_view str);

    const std::vector<int>& digits() const {
        return digits_m;
    }

private:
    std::vector<int> digits_m;

    std::optional<int> to_int(std::string_view str) const;

};

}