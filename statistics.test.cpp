#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "statistics.hpp"

#include "doctest.h"


TEST_CASE("Testing the class handling a floating point data sample") {
  pf::Sample sample;

  REQUIRE(sample.size() == 0);

  SUBCASE("Testing statistics() with no points") {
    CHECK_THROWS(sample.statistics());
  }

  SUBCASE("Testing statistics() with one point") {
    CHECK_THROWS(sample.statistics());
  }

  SUBCASE("Testing statistics() with two points") {
    sample.add(1.);
    sample.add(2.);
    auto result = sample.statistics();
    CHECK(result.mean == doctest::Approx(1.5));
    CHECK(result.sigma == doctest::Approx(0.707106781186548));
    CHECK(result.mean_err == doctest::Approx(0.5));
    CHECK(result.median == doctest::Approx(1.5));
  }

  SUBCASE("Testing statistics() with three points") {
    sample.add(1.2);
    sample.add(0.6);
    sample.add(3.8);
    auto result = sample.statistics();
    CHECK(result.mean == doctest::Approx(1.86666666666667));
    CHECK(result.sigma == doctest::Approx(1.70098010962308));
    CHECK(result.mean_err == doctest::Approx(0.982061324177082));    
    CHECK(result.median == doctest::Approx(1.2));
  }

  SUBCASE("Remove an existing point") {
    sample.add(2.7);
    sample.add(4.5);
    CHECK(sample.remove(2.7) == true);
  }

  SUBCASE("Remove a non existing point") {    
    sample.add(1.8);
    sample.add(2.7);
    CHECK(sample.remove(1.0) == false);
  }

  SUBCASE("Testing sum operator") {
    sample.add(1.);
    pf::Sample sample_two;
    sample_two.add(2.);
    sample_two.add(3.5);
    auto sum = sample + sample_two;
    CHECK(sum.size() == 3);
    CHECK(sum.entries()[0] == 1.);   
    CHECK(sum.entries()[1] == 2.);
    CHECK(sum.entries()[2] == 3.5);
  }
}

#endif