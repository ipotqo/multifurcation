#include "innovation.hpp"

void innovation::terminal ( std::string_view const& statement ) {
    printf ( "innovation:\t%s\n", statement.data() );
    academic::terminal( statement.data() );
    author::terminal( statement.data() );
}