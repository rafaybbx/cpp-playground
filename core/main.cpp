#include "core/lab.hpp"

#include <iostream>
#include <string_view>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: cpp_playground <lab-key>\n\n";
        core::print_available_labs(std::cout);
        return 0;
    }

    const std::string_view lab_key{argv[1]};
    const core::lab_info *selected_lab = core::find_lab(lab_key);

    if (selected_lab == nullptr)
    {
        std::cerr << "Unknown lab: " << lab_key << "\n\n";
        core::print_available_labs(std::cerr);
        return 1;
    }

    std::cout << "Running lab: " << selected_lab->key << "\n\n";
    selected_lab->run();
    return 0;
}
