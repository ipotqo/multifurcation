#include "innovator.hpp"

void innovator::terminal ( std::string_view const& statement ) {
    printf ( "innovator:\t%s\n", statement.data() );
    tool::terminal( statement.data() );
    academic::terminal( statement.data() );
    utl::terminal( statement.data() );
    author::terminal( statement.data() );
}