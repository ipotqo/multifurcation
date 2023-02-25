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

#include <array>
#include <concepts>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
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
concept real = std::is_floating_point_v< GenericT >;

template< real ArithmeticT = float >
struct location;

template< typename GenericT >
concept featurable = requires ( GenericT value ) {
                       { value.centre () } -> std::same_as< location<> >;
                       { visualise ( value ) } -> std::same_as< std::string >;
                     };

// ================================================================

/**
 * \brief Two-Dimensional Cartesian Location
 */

template< real ArithmeticT >
struct location {

  explicit location ()
      : horizontal { static_cast< ArithmeticT > ( 0.f ) }
      , vertical { static_cast< ArithmeticT > ( 0.f ) } {}

  explicit location ( ArithmeticT const& h, ArithmeticT const& v )
      : horizontal { h }
      , vertical { v } {}

  ArithmeticT horizontal;
  ArithmeticT vertical;
};

// ================================================================

/**
 * \brief Two-Dimensional Discretised Scalar Field
 */

using lattice_t = std::size_t;

template< real ArithmeticT = float, lattice_t RowsN = 256,
          lattice_t ColsN = 256 >
class field : public std::array< ArithmeticT, RowsN * ColsN > {
public:
  explicit field< ArithmeticT, RowsN, ColsN > ()
      : std::array< ArithmeticT, RowsN * ColsN > () {}

private:
  // TODO: index_t

private:
  location< ArithmeticT > anchor; // south-west
  std::pair< ArithmeticT, ArithmeticT > resolution;
};

// ================================================================

/**
 * Feature (Type Erasure Pattern)
 */

template< real ArithmeticT = float >
class feature {

private:
  // "Concept"
  struct FeatureNotion {

    virtual ~FeatureNotion () = default;

    // clone function: c.f. copy operations
    virtual std::unique_ptr< FeatureNotion > clone () const = 0;

    // doers
    // virtual void serialisation () const = 0;
    virtual void visualisation () const = 0;
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
 * Demonstration (Facade Pattern)
 */

// ================================================================

int main ( int argc, char *argv[] ) {

  printf ( "MULTIFURCATION VERSION %d.%d.%d\n", MULTIFURCATION_VERSION_MAJOR,
           MULTIFURCATION_VERSION_MINOR, MULTIFURCATION_VERSION_PATCH );

  return EXIT_SUCCESS;
}