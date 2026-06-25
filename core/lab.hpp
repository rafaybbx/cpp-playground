#pragma once

#include <iosfwd>
#include <string_view>

namespace core
{

    using lab_runner = void (*)();

    struct lab_info
    {
        std::string_view key;
        std::string_view title;
        lab_runner run;
    };

    const lab_info *find_lab(std::string_view key);
    void print_available_labs(std::ostream &out);

} // namespace core
