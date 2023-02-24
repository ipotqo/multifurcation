#include "utl.hpp"

void utl::terminal ( std::string_view const& statement ) {
    printf( "utl:\t%s\n", statement.data() );
}