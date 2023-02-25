/**
 * \file  conventions/conventions.hpp
 * \brief Demonstration of the Conventions
 */

// C Headers
#include <cassert>
#include <cmath>

// C++ Headers
#include <array>
#include <concepts>
#include <iostream>

// Tools/Utilities/Libraries

// Local Headers

namespace conventions {

template< typename NumericT >
using ResolutionT< NumericT > = NumericT;

using lattice_t = std::size_t;

template< typename ArithmeticT, resolution_t RowsN, resolution_t ColsN >
class field : public std::array< ArithmeticT, RowsN * ColsN > {
public:
  explicit field ()
      : horizontal_resolution{ 1.0 }
      , vertical_resolution{ 1.0 } {}

private:
  ResolutionT< ArithmeticT > horizontal_resolution;
  ResolutionT< ArithmeticT > vertical_resolution;
};

} // namespace conventions