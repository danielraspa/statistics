#include "statistics.hpp"

#include <random>
#include<iostream>

int main () {
  pf::Sample data{};
  std::random_device r;
  std::default_random_engine eng(r());
  std::normal_distribution<double> dist;

  for(int i = 1; i < 1000000; i++) {
    data.add(dist(eng));
  }

  const auto stat{data.statistics()};
  std::cout << "Mean: " << stat.mean << '\n'
            << "Sigma: " << stat.sigma << '\n';
}  