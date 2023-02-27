/**
 * \file  multifurcation/mwe/multifurcation.cpp
 * \brief Desired Functionalities in Isolated Unit
 *
 * MULTIFURCATION (C) 2023 // TIM PLEASETH @IPOTQO
 *
 * THIS FILE IS PART OF THE \b MULTIFURCATION PROJECT:
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
#include <memory>
#include <mutex>
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

auto constexpr interval ( auto const& minimum, auto const& maximum,
                          auto const& discretisation ) {
  return fabs ( maximum - minimum ) / ( discretisation - 1 );
}

// Random Float
auto rndf () {
  static std::random_device               RANDOM_DEVICE;
  static std::mt19937                     ENGINE ( RANDOM_DEVICE () );
  static std::uniform_real_distribution<> DISTRIBUTION ( -10, 10 );
  return DISTRIBUTION ( ENGINE );
}

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
    std::swap ( horizontal, other.horizontal );
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

using demarcation_t = std::size_t;
using index_t       = std::size_t;

template< measurable ArithmeticT = float, demarcation_t RowsN = FALLBACK::ROWS,
          demarcation_t ColsN = FALLBACK::COLS >
class field;

template< measurable ArithmeticT = float, demarcation_t RowsN = FALLBACK::ROWS,
          demarcation_t ColsN = FALLBACK::COLS >
void initialisation ( field< ArithmeticT, RowsN, ColsN >&,
                      ArithmeticT ( * ) ( ArithmeticT const&,
                                          ArithmeticT const& ) );

template< measurable ArithmeticT, demarcation_t RowsN, demarcation_t ColsN >
std::ostream& operator<< ( std::ostream&,
                           field< ArithmeticT, RowsN, ColsN > const& );

template< measurable ArithmeticT, demarcation_t RowsN, demarcation_t ColsN >
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
    return interval ( this->anchor.first.horizontal,
                      this->anchor.second.horizontal, RowsN );
  }

  auto constexpr vertical_resolution () const {
    return interval ( this->anchor.first.vertical, this->anchor.second.vertical,
                      ColsN );
  }

  auto constexpr site ( demarcation_t const& row,
                        demarcation_t const& col ) const {

    location< ArithmeticT > const translation ( row * horizontal_resolution (),
                                                col * vertical_resolution () );

    return anchor.first + translation;

    // TODO: symmetric version which uses anchor.second & translation / 2
  }

  // --------------------------------

  // TODO: overloaded operators

  // --------------------------------

public:
  auto& value ( index_t const& row, index_t const& col ) {
    return this->element[rindex ( row, col )];
  }

  auto const& value ( index_t const& row, index_t const& col ) const {
    return this->element[rindex ( row, col )];
  }

  // --------------------------------

  // TODO: maximum and minimum element

  // --------------------------------

  friend void initialisation< ArithmeticT, RowsN, ColsN > (
      field< ArithmeticT, RowsN, ColsN >&,
      ArithmeticT ( * ) ( ArithmeticT const&, ArithmeticT const& ) );

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
    return ( row % RowsN ) + ( col % ColsN * ColsN );
  }

private:
  using coordinate = location< ArithmeticT >;
  using domain     = std::pair< coordinate, coordinate >;
  using matrix     = std::array< ArithmeticT, RowsN * ColsN >;

private:
  matrix element; // rolled vectorised form
  domain anchor;  // south-west and north-east corners
};

// ----------------------------------------------------------------

template< measurable ArithmeticT, demarcation_t RowsN, demarcation_t ColsN >
void initialisation ( field< ArithmeticT, RowsN, ColsN >& f,
                      ArithmeticT ( *m ) ( ArithmeticT const&,
                                           ArithmeticT const& ) ) {

  demarcation_t row = 0;
  demarcation_t col = 0;
  for ( auto& e : f.element ) {
    auto s = f.site ( row, col );
    e      = m ( s.horizontal, s.vertical );
    if ( ++col % ColsN == 0 && ++row < RowsN ) {
      col = 0;
    }
  }
}

// ----------------------------------------------------------------

template< measurable ArithmeticT, demarcation_t RowsN, demarcation_t ColsN >
std::ostream& operator<< ( std::ostream                            & os,
                           field< ArithmeticT, RowsN, ColsN > const& f ) {

  // TODO: NEAT PRINT

  demarcation_t row = 0;
  demarcation_t col = 0;

  for ( auto const& e : f.element ) {

    os << f.site ( row, col ) << '\t' << e << '\n';
    if ( ++col % ColsN == 0 && ++row < RowsN ) {
      os << '\n';
      col = 0;
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

  // Extended Model: Policy-Based Design (Visualisation Strategy)
  template< typename FeatureT, typename VisualisationStr >
  struct FeatureExtendedModel final : public FeatureNotion {

    explicit FeatureExtendedModel ( FeatureT         i_feature,
                                    VisualisationStr i_visualiser )
        : m_feature { std::move ( i_feature ) }
        , m_visualiser { std::move ( i_visualiser ) } {}

    void visualisation () const override {
      m_visualiser ( m_feature );
    }

    std::unique_ptr< FeatureNotion > clone () const override {
      return std::make_unique< FeatureExtendedModel > ( *this );
    }

    FeatureT         m_feature;
    VisualisationStr m_visualiser;
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

  // Note: dependency injection with visualisation strategy
  template< typename FeatureT, typename VisualisationStr >
  feature ( FeatureT i_feature, VisualisationStr i_visualiser )
      : pimpl { std::make_unique<
            FeatureExtendedModel< FeatureT, VisualisationStr > > (
            std::move ( i_feature ), std::move ( i_visualiser ) ) } {}

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
 * Notable Elements (Feature Concretions)
 */

template< typename GenericT >
concept notable = requires ( GenericT v ) {
                    { visualise ( v ) } -> std::same_as< void >;
                  };

struct PointFeature final {
  explicit PointFeature ( location< float > c = location< float > ( 0, 0 ) )
      : centre { c } {}

  location< float > centre;
};

struct LineFeature final {
  explicit LineFeature () {}

  location< float > centre;
  float             size;
  float             colour;
  float             orientation;
};

struct AreaFeature final {
  explicit AreaFeature () {}

  location< float > centre;
};

struct VolumeFeature final {
  explicit VolumeFeature () {}

  location< float > centre;
};

auto visualise ( PointFeature const& f ) {
  std::cout << "Point Feature\t@\t(" << f.centre << ")\n";
}

auto visualise ( LineFeature const& f ) {
  std::cout << "Line Feature\t@\t(" << f.centre << ")\n";
}

auto visualise ( AreaFeature const& f ) {
  std::cout << "Area Feature\t@\t(" << f.centre << ")\n";
}

auto visualise ( VolumeFeature const& f ) {
  std::cout << "Volume Feature\t@\t(" << f.centre << ")\n";
}

// ================================================================

/**
 * Simulation (Factory Method & Observer Patterns)
 */

template< measurable ArithmeticT, demarcation_t RowsN, demarcation_t ColsN >
class simulation {

public:
  simulation< ArithmeticT, RowsN, ColsN > () {
    this->feature_collection.resize ( 0 );
  }

public:
  field< ArithmeticT, RowsN, ColsN >    field_state;
  std::vector< feature< ArithmeticT > > feature_collection;
};

// TODO thread & mutex lock
// TODO std::accummulate with lambda idiom

// ================================================================

/**
 * Contour (Builder Pattern)
 */

constexpr auto command () {
  return "gnuplot -persist";
}

constexpr auto contour () {
  return "#!/usr/bin/gnuplot\n"
         "reset\n"
         "set terminal epslatex size 5,5 color\n"
         "set output \"contour.tex\"\n"
         "set lmargin 0\n"
         "set rmargin 0\n"
         "set tmargin 0\n"
         "set bmargin 0\n"
         "set nokey\n"
         "set xrange [-5:5]\n"
         "set yrange [-5:5]\n"
         "set isosample 250,250\n"
         "set table \"contour_map.dat\"\n"
         "splot \"contour.dat\" using 1:2:3\n"
         "unset table\n"
         "set contour base\n"
         "set palette rgbformulae 33,13,10\n"
         "set cbrange [-10:10]\n"
         "set cntrparam level discrete -10,1,10\n"
         "unset surface\n"
         "set table \"contour_curve.dat\"\n"
         "splot \"contour.dat\" using 1:2:3\n"
         "unset table\n"
         "unset xtics\n"
         "unset ytics\n"
         "unset cbtics\n"
         "unset colorbox\n"
         "p \"contour_map.dat\" with image, \"contour_curve.dat\" with l lc "
         "\"black\"";
}

class Contour {};

class PlotBuilder {};

class GnuBuilder : public PlotBuilder {};

// ================================================================

/**
 * Visualisation (Builder Pattern)
 */

class visualisation {};

// ================================================================

/**
 * Test Suite (Prototype Declaration)
 */
using error = int;

error test_location ();
error test_field ();
error test_feature ();
error test_simulation ();
error test_visualisation ();
error test ();

// ================================================================

/**
 * Demonstration (Facade Pattern)
 */

template< measurable ArithmeticT = float >
constexpr ArithmeticT function ( ArithmeticT const& h, ArithmeticT const& v ) {
  return -1e1 * v * ( 3. * h * h - v * v ) /
         ( ( h * h + v * v ) * ( h * h + v * v ) );
}

auto demonstration () {
  field< float, 1024, 1024 > f;

  f.set_boundaries ( location< float > ( -5, -5 ), location< float > ( 5, 5 ) );

  initialisation< float, 1024, 1024 > ( f, function );

  std::ofstream data_file;
  data_file.open ( "contour.dat" );
  data_file << f;
  data_file.close ();

  std::ofstream contour_file;
  contour_file.open ( "contour.gnu" );
  contour_file << contour ();
  contour_file.close ();

#define GNUPLOT "gnuplot -persist"

  FILE *contour = popen ( GNUPLOT, "w" );

  fprintf ( contour, "load \"contour.gnu\"" );
}

int EntrancePoint ( int argc, char *argv[] ) {

  demonstration ();

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

error test () {

  auto status_location      = test_location ();
  auto status_field         = test_field ();
  auto status_feature       = test_feature ();
  auto status_simulation    = test_simulation ();
  auto status_visualisation = test_visualisation ();

  return EXIT_SUCCESS;
}

error test_location () {

  {

    using lctn = location< float >;

    lctn a ( rndf (), rndf () );
    lctn b ( 0., 0. );

    std::cout << a << '\n';
    std::cout << b << '\n';

    b = a;

    std::cout << b << '\n';
  }

  return 0;
}

error test_field () {

  {

    using fld  = field< float, 4, 4 >;
    using lctn = location< float >;

    fld  f;
    lctn sw ( 0, 0 );
    lctn ne ( 1, 1 );

    f.set_boundaries ( sw, ne );

    f.set_boundaries ( lctn ( 0.f, 0.f ), lctn ( 10.f, 10.f ) );

    f.value ( 0, 0 ) = 0;
    f.value ( 1, 0 ) = 1;
    f.value ( 2, 0 ) = 2;
    f.value ( 3, 3 ) = 3;

    std::cout << f << '\n';
  }

  return 0;
}

error test_feature () {

  {
    std::vector< feature< float > > feature_collection;

    feature_collection.emplace_back ( PointFeature {} );
    feature_collection.emplace_back ( LineFeature {} );
    feature_collection.emplace_back ( AreaFeature {} );
    feature_collection.emplace_back ( VolumeFeature {} );

    visualise ( feature_collection );
  }

  return 0;
}

error test_simulation () {
  return 0;
}

error test_visualisation () {
  return 0;
}