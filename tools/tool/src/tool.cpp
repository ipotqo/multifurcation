#include "tool.hpp"

void tool::terminal ( std::string_view const& statement ) {
    printf("tool:\t%s\n", statement);
    utl::terminal ( statement.data() );
    author::terminal ( statement.data() );
}