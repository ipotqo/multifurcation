/**
 * @file  multifurcation.hpp
 * @brief Root (Surface-Level) Header
 */

#ifndef __MULTIFURCATION_HPP__
#define __MULTIFURCATION_HPP__

// C Headers
#include <cassert>

// C++ Headers
#include <iostream>

// Utilities
#include <author/author.hpp>

// Tools (incl. Utilities)
#include <academic/academic.hpp>

// Libraries (incl. Tools and Utilties)

// Local Headers
#include "version.hpp"

namespace multifurcation {

int EntrancePoint(int argc, char *argv[]) {
    
    printf(
        "MULTIFURCATION\tVERSION %d.%d.%d\n",
        MULTIFURCATION_VERSION_MAJOR,
        MULTIFURCATION_VERSION_MINOR,
        MULTIFURCATION_VERSION_PATCH
    );
    
    author::terminal ( "<utilities:author>" );

    academic::terminal ( "<tools:academic>" );
    
    return EXIT_SUCCESS;
}

} // namespace multifurcation

#endif // __MULTIFURCATION_HPP__