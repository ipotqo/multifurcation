#include "academic.hpp"

void academic::terminal ( std::string_view const& statement ) {
    printf("academic:\t%s\n\t", statement); 
    author::terminal ( statement.data() );
}