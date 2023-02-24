#include "inventor.hpp"

void inventor::terminal ( std::string_view const& statement ) {
    printf ( "inventor:\t%s\n", statement.data() );
    tool::terminal( statement.data() );
    academic::terminal( statement.data() );
    utl::terminal( statement.data() );
    author::terminal( statement.data() );
}