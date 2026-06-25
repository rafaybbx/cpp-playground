#include "core/lab.hpp"

#include <array>
#include <ostream>

namespace lab
{
    namespace initialization
    {
        void run();
    } // namespace initialization
} // namespace lab

namespace core
{

    namespace
    {

        const std::array<lab_info, 1> labs{{
            {"initialization", "Variable initialization and declaration", &lab::initialization::run},
        }};

    } // namespace

    const lab_info *find_lab(std::string_view key)
    {
        for (const auto &lab_entry : labs)
        {
            if (lab_entry.key == key)
            {
                return &lab_entry;
            }
        }

        return nullptr;
    }

    void print_available_labs(std::ostream &out)
    {
        out << "Available labs:\n";
        for (const auto &lab_entry : labs)
        {
            out << "  - " << lab_entry.key << " : " << lab_entry.title << '\n';
        }
    }

} // namespace core
