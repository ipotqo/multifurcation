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

// Libraries (incl. Tools and Utilties)


namespace multifurcation {

int EntrancePoint(int argc, char *argv[]) {
    
    std::cout << "multifurcation\n";
    
    author::terminal ( "<utilities:author>" );
    
    return EXIT_SUCCESS;
}

} // namespace multifurcation

#endif // __MULTIFURCATION_HPP__