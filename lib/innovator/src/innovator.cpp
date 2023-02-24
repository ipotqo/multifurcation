#include "innovator.hpp"

void innovator::terminal ( std::string_view const& statement ) {
    printf ( "innovator:\t%s\n", statement.data() );
    academic::terminal( statement.data() );
    author::terminal( statement.data() );
}