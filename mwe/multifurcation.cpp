/**
 * \file  multifurcation/mwe/multifurcation.cpp
 * \brief Desired Functionalities in Isolated Unit
 *
 * MULTIFURCATION (C) 2023 // TIM PLEASETH @IPOTQO
 *
 * THIS FILE IS PART OF THE MULTIFURCATION PROJECT:
 * HTTPS://WWW.GITHUB.COM/IPOTQO/MULTIFURCATION
 *
 * LICENSE: UNLICENSE
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#define MULTIFURCATION_VERSION_MAJOR 0
#define MULTIFURCATION_VERSION_MINOR 0
#define MULTIFURCATION_VERSION_PATCH 0

#include <cassert>
#include <cmath>
#include <cstddef>

#include <algorithm>
#include <array>
#include <chrono>
#include <concepts>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>

namespace multifurcation {
namespace utilities {}
namespace tools {}
namespace libraries {}
} // namespace multifurcation

// ================================================================

template< typename GenericT >
concept measurable = std::is_floating_point_v< GenericT >;

template< typename GenericT >
concept rootable = requires ( GenericT value ) {
                     { std::is_floating_point_v< GenericT > };
                     { value >= 0. };
                   };

// ================================================================

class FALLBACK {
public:
  static constexpr std::size_t ROWS = 256;
  static constexpr std::size_t COLS = 256;

  template< measurable ArithmeticT >
  static constexpr ArithmeticT ANCHOR_HORIZONTAL =
      static_cast< ArithmeticT > ( 0.f );

  template< measurable ArithmeticT >
  static constexpr ArithmeticT ANCHOR_VERTICAL =
      static_cast< ArithmeticT > ( 0.f );

  template< measurable ArithmeticT >
  static constexpr ArithmeticT RESOLUTION_HORIZONTAL =
      static_cast< ArithmeticT > ( 0.f );

  template< measurable ArithmeticT >
  static constexpr ArithmeticT RESOLUTION_VERTICAL =
      static_cast< ArithmeticT > ( 0.f );

  template< measurable ArithmeticT >
  static constexpr ArithmeticT FIELD_VALUE = static_cast< ArithmeticT > ( 0.f );
};

// ================================================================

/*
template< typename GenericT >
concept featurable = requires ( GenericT value ) {
                       { value.centre () } -> std::same_as< location<> >;
                       {
                         visualise ( value )
                         } -> std::same_as< std::string_view >;
                     };
*/

// ================================================================

/**
 * \brief Two-Dimensional Cartesian Location
 */

template< measurable ArithmeticT = float >
struct location;

template< measurable ArithmeticT >
std::ostream& operator<< ( std::ostream&, location< ArithmeticT > const& );

template< measurable ArithmeticT >
struct location {

  explicit location ()
      : horizontal { static_cast< ArithmeticT > ( 0.f ) }
      , vertical { static_cast< ArithmeticT > ( 0.f ) } {}

  explicit location ( ArithmeticT const& h, ArithmeticT const& v )
      : horizontal { h }
      , vertical { v } {}

  ~location< ArithmeticT > () noexcept = default;

  // --------------------------------

  location< ArithmeticT >& operator= ( location< ArithmeticT > other ) {
    std::swap( horizontal, other.horizontal );
    std::swap ( vertical, other.vertical );
    return *this;
  }

  location< ArithmeticT >& operator+= ( location< ArithmeticT > const& rhs ) {
    this->horizontal += rhs.horizontal;
    this->vertical   += rhs.vertical;
    return *this;
  }

  location< ArithmeticT >& operator-= ( location< ArithmeticT > const& rhs ) {
    this->horizontal -= rhs.horizontal;
    this->vertical   -= rhs.vertical;
    return *this;
  }

  location< ArithmeticT >& operator*= ( ArithmeticT const& rhs ) {
    this->horizontal *= rhs;
    this->vertical   *= rhs;
    return *this;
  }

  location< ArithmeticT >& operator/= ( ArithmeticT const& rhs ) {
    this->horizontal /= rhs;
    this->vertical   /= rhs;
    return *this;
  }

  // --------------------------------

  friend std::ostream&
  operator<< < ArithmeticT > ( std::ostream&, location< ArithmeticT > const& );

  // --------------------------------

  ArithmeticT horizontal;
  ArithmeticT vertical;
};

template< measurable ArithmeticT >
inline constexpr auto operator+ ( location< ArithmeticT >        lhs,
                                  location< ArithmeticT > const& rhs ) {
  lhs += rhs;
  return lhs;
}

template< measurable ArithmeticT >
inline constexpr auto operator- ( location< ArithmeticT >        lhs,
                                  location< ArithmeticT > const& rhs ) {
  lhs -= rhs;
  return lhs;
}

template< measurable ArithmeticT >
inline constexpr auto operator== ( location< ArithmeticT > const& lhs,
                                   location< ArithmeticT > const& rhs ) {
  return ( lhs.horizontal == rhs.horizontal && lhs.vertical == rhs.vertical );
}

template< measurable ArithmeticT >
inline constexpr auto operator!= ( location< ArithmeticT > const& lhs,
                                   location< ArithmeticT > const& rhs ) {
  return !operator== ( lhs, rhs );
}

template< measurable ArithmeticT >
std::ostream& operator<< ( std::ostream                 & os,
                           location< ArithmeticT > const& l ) {
  os << l.horizontal << '\t' << l.vertical;
  return os;
}

template< measurable ArithmeticT >
auto constexpr norm ( location< ArithmeticT > const& l ) {
  return hypot ( l.horizontal, l.vertical );
}

template< measurable ArithmeticT >
auto constexpr orientation ( location< ArithmeticT > const& l ) {
  return atan2 ( l.vertical, l.horizontal );
}

// ================================================================

/**
 * \brief Two-Dimensional Discretised Scalar Field
 */

using lattice_t = std::size_t;
using index_t   = std::size_t;

template< measurable ArithmeticT = float, lattice_t RowsN = FALLBACK::ROWS,
          lattice_t ColsN = FALLBACK::COLS >
class field;

template< measurable ArithmeticT, lattice_t RowsN, lattice_t ColsN >
std::ostream& operator<< ( std::ostream&,
                           field< ArithmeticT, RowsN, ColsN > const& );

template< measurable ArithmeticT, lattice_t RowsN, lattice_t ColsN >
class field {

public:
  explicit field< ArithmeticT, RowsN, ColsN > () {
    for ( auto& e : this->element ) {
      e = FALLBACK::FIELD_VALUE< ArithmeticT >;
    }
  }

  ~field< ArithmeticT, RowsN, ColsN > () noexcept = default;

  // --------------------------------

  auto set_boundaries ( location< ArithmeticT > const& south_west,
                                  location< ArithmeticT > const& north_east ) {
    this->anchor.first  = south_west;
    this->anchor.second = north_east;
  }

  // --------------------------------

  auto constexpr horizontal_resolution () const {
    return fabs ( std::midpoint ( this->anchor.second.horizontal,
                                  this->anchor.first.horizontal ) );
  }

  auto constexpr vertical_resolution () const {
    return fabs ( std::midpoint ( this->anchor.second.vertical,
                                  this->anchor.first.vertical ) );
  }

public:
  auto& value ( index_t const& row, index_t const& col ) {
    return this->element[rindex ( row, col )];
  }

  auto const& value ( index_t const& row, index_t const& col ) const {
    return this->element[rindex ( row, col )];
  }

  // --------------------------------

  friend std::ostream& operator<< < ArithmeticT, RowsN, ColsN > (
      std::ostream&, field< ArithmeticT, RowsN, ColsN > const& );

private:
  auto& operator[] ( index_t const& index ) {
    return this->element.at ( index );
  }

  auto const& operator[] ( index_t const& index ) const {
    return this->element.at ( index );
  }

  // rolled index
  inline index_t constexpr rindex ( index_t const& row, index_t const& col ) {
    return ( row % RowsN ) + ( col * ColsN );
  }

private:
  using coordinate = location< ArithmeticT >;
  using domain     = std::pair< coordinate, coordinate >;
  using matrix     = std::array< ArithmeticT, RowsN * ColsN >;

private:
  matrix element; // rolled vectorised form
  domain anchor;  // south-west and north-east corners
};

template< measurable ArithmeticT, lattice_t RowsN, lattice_t ColsN >
std::ostream& operator<< ( std::ostream                            & os,
                           field< ArithmeticT, RowsN, ColsN > const& f ) {

 // TODO: NEAT PRINT

    auto const hs = f.anchor.first.horizontal;
    auto const vs = f.anchor.first.vertical;

    auto const hr = f.horizontal_resolution();
    auto const vr = f.vertical_resolution ();

    std::size_t row = 0;
    std::size_t col = 0;

    auto site = [](ArithmeticT const& start, ArithmeticT const& resolution, lattice_t index){
        return start + index * resolution;
    };

 for ( auto e : f.element ) {
    os << site (hs,hr,row) << '\t' << site(vs,vr,col) << '\t' << e << '\n';
    if ( ++col % ColsN == 0 && ++row < RowsN ) {
        os << '\n';
    }
 }

  return os;
}

// ================================================================

/**
 * Feature (Type Erasure Pattern)
 */

template< measurable ArithmeticT = float >
class feature {

private:
  // "Concept"
  struct FeatureNotion {

    virtual ~FeatureNotion ()                                       = default;

    // clone function: c.f. copy operations
    virtual std::unique_ptr< FeatureNotion > clone () const         = 0;

    // doers
    // virtual void serialisation () const = 0;
    virtual void                             visualisation () const = 0;
  };

  template< typename FeatureT >
  struct FeatureModel final : public FeatureNotion {

    FeatureModel ( FeatureT i_feature )
        : m_feature { std::move ( i_feature ) } {}

    // Prototype Design Pattern
    std::unique_ptr< FeatureNotion > clone () const override {
      return std::make_unique< FeatureModel > ( *this );
    }

    /*
    void serialisation () const override {
        serialise ( m_feature );
    }
    */

    void visualisation () const override {
      visualise ( m_feature );
    }

    FeatureT m_feature;
  };

  friend void visualise ( feature const& a_feature ) {
    a_feature.pimpl->visualisation ();
  }

  std::unique_ptr< FeatureNotion > pimpl;

private:
  location< ArithmeticT > centre;

public:
  // Bridge Pattern: Templated Constructor
  template< typename FeatureT >
  feature ( FeatureT i_feature )
      : pimpl { std::make_unique< FeatureModel< FeatureT > > (
            std::move ( i_feature ) ) } {}

  /*
  // Note: dependency injection with visualisation strategy
  template< typename FeatureT, typename VisualisationStr >
  feature ( FeatureT i_feature, VisualisationStr i_visualiser )
      : pimpl {
  std::make_unique<FeatureExtendedModel<FeatureT,VisualisationStr>>(
  std::move(i_feature), std::move(i_visualiser) ) }
  {}
  */

  // Copy Operations
  feature ( feature const& other )
      : pimpl { other.pimpl->clone () } {}

  feature& operator= ( feature const& other ) {
    other.pimpl->clone ().swap ( pimpl ); // copy-and-swap
    return *this;
  }

  // Move Operations
  // Note: various options available for the move operations

  // move constructor undefined (not deleted or defaulted)
  // feature ( feature&& other );

  // move assignment implemented in terms of the swap
  feature& operator= ( feature&& other ) {
    pimpl.swap ( other.pimpl );
    return *this;
  }
};

void visualise ( std::vector< feature<> > const& feature_collection ) {
  for ( auto const& feature : feature_collection ) {
    visualise ( feature );
  }
}

// ================================================================

/**
 * Simulation (Factory Method Pattern)
 */

// ================================================================

/**
 * Contour (Builder Pattern)
 */

// ================================================================

/**
 * Visualisation (Builder Pattern)
 */

// ================================================================

/**
 * Test Suite (Prototype Declaration)
 */
int test_location ();
int test_field ();
int test ();

// ================================================================

/**
 * Demonstration (Facade Pattern)
 */

int EntrancePoint ( int argc, char *argv[] ) {
  return EXIT_SUCCESS;
}

// ================================================================

int main ( int argc, char *argv[] ) {

  printf ( "MULTIFURCATION VERSION %d.%d.%d\n", MULTIFURCATION_VERSION_MAJOR,
           MULTIFURCATION_VERSION_MINOR, MULTIFURCATION_VERSION_PATCH );

  if ( test () == 0 )
    return EntrancePoint ( argc, argv );
  else {
    fprintf ( stderr, "ERROR" );
    return EXIT_FAILURE;
  }
}

// ================================================================

/**
 * Test Suite (Implementation)
 */

// Random Float
float rndf () {
  static std::random_device               RANDOM_DEVICE;
  static std::mt19937                     ENGINE ( RANDOM_DEVICE () );
  static std::uniform_real_distribution<> DISTRIBUTION ( -10, 10 );
  return DISTRIBUTION ( ENGINE );
}

int test () {

  auto status_location = test_location ();
  // auto status_field    = test_field ();

  return EXIT_SUCCESS;
}

int test_location () {

  {

    auto const        h = rndf ();
    auto const        v = rndf ();

    location< float > a ( h, v );
    location< float > b ( 0., 0. );

    std::cout << a << '\n';
    std::cout << b << '\n';

    b = a;

    std::cout << b << '\n';

  }

  return 0;
}

int test_field () {

  {

    field< float, 4, 4 > f;

    location<float> sw (0,0);
    location<float> ne (1,1);

    f.set_boundaries ( sw, ne );

    f.value ( 0, 0 ) = 0;
    f.value ( 1, 0 ) = 1;
    f.value ( 2, 0 ) = 2;
    f.value ( 3, 0 ) = 3;

    std::cout << f << '\n';
  }

  return 0;
}