/**
 * @file  multifurcation.hpp
 * @brief Root (Surface-Level) Header
 */

#ifndef __MULTIFURCATION_HPP__
#define __MULTIFURCATION_HPP__

#include <iostream>

#include <author/author.hpp>

namespace multifurcation {

int EntrancePoint(int argc, char *argv[]) {
    
    std::cout << "multifurcation\n";
    
    author::terminal ( "<utilities:author>" );
    
    return EXIT_SUCCESS;
}

} // namespace multifurcation

#endif // __MULTIFURCATION_HPP__