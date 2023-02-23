#include "author.hpp"

void author::terminal ( std::string_view const& statement ) {
    printf( "author:\t%s\n", statement.data() );
}