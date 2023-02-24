/**
 * @file  multifurcation.hpp
 * @brief Root (Surface-Level) Header
 */

#ifndef __MULTIFURCATION_HPP__
#define __MULTIFURCATION_HPP__

#pragma once

// C Headers
#include <cassert>

// C++ Headers
#include <iostream>

// Utilities
#include <utl/utl.hpp>
#include <author/author.hpp>

// Tools (incl. Utilities)
#include <tool/tool.hpp>
#include <academic/academic.hpp>

// Libraries (incl. Tools and Utilties)
#include <innovator/innovator.hpp>
#include <inventor/inventor.hpp>

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
    
    utl::terminal ( "<utilities:utl>" );
    author::terminal ( "<utilities:author>" );

    tool::terminal ( "<tools:tool>" );
    academic::terminal ( "<tools:academic>" );

    innovator::terminal ( "<libraries:innovator>" );
    inventor::terminal ( "<libraries:inventor>" );
    
    return EXIT_SUCCESS;
}

} // namespace multifurcation

#endif // __MULTIFURCATION_HPP__