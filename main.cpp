#include "statistics.hpp"

#include <random>
#include <iostream>
#include <fstream>

int main () {
  pf::Sample data{};
  std::ifstream in_file("data.txt");

  if (in_file.is_open()) {
    std::cout << "The file has been opened" << '\n';
  }

  double x;
  while (in_file >> x) {
    data.add(x);
  }

  const auto stat{data.statistics()};

  std::cout << "Mean: " << stat.mean << '\n'
            << "Sigma: " << stat.sigma << '\n'
            << "Mean error: " << stat.mean_err << '\n'
            << "Median: " << stat.median << '\n';

  std::ofstream out_file("result.txt");

  if (out_file.is_open()) {
    out_file << stat.mean << '\n'
              << stat.sigma << '\n'
              << stat.mean_err << '\n'
              << stat.median << '\n';
    std::cout << "Results has been saved in result.txt" << '\n';
  }
}  