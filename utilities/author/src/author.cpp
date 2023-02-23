#include "author.hpp"

void author::terminal ( std::string_view const& record ) {
    std::cout << "author:\t" << record << '\n';
}