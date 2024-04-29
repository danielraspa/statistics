#include "statistics.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <limits>

int main() {
  pf::Sample data{};
  char cmd{};
  int N{};
  std::string filename;

  std::cout << "Insert a correct value: " << '\n'
            << "- type g N_ENTRIES to generate a random data sample" << '\n'
            << "- type r FILE_NAME to read data from a FILE_NAME file" << '\n'
            << "- type s to compute the statistics" << '\n'
            << "- type o FILE _NAME to compute the statistics e to write the results in a FILE_NAME file" << '\n'
            << "- type q to close the program" << '\n';

  std::default_random_engine eng;
  std::normal_distribution<double> dist;

  while (std::cin >> cmd) {
    if (cmd == 'g' && std::cin >> N) {
      std::generate_n(std::back_inserter(data), N, [&]() { return dist(eng); });
      std::cout << "Data generated" << '\n';
    } else if (cmd == 'r' && std::cin >> filename) {
      std::ifstream in_file(filename);
      if (!in_file.is_open()) {
        std::cout << "Cannot open the file" << '\n';
      }
      double x;
      while (in_file >> x) {
        data.add(x);
      }
      std::cout << "Data read successfully" << '\n'; //continuare con il prossimo else if
    } else if (cmd == 's'){
      std::cout << "Mean: " << data.statistics().mean << '\n' 
                << "Sigma: " << data.statistics().sigma << '\n'
                << "Mean Error: " << data.statistics().mean_err << '\n'
                << "Median: " << data.statistics().median << '\n';
    } else if (cmd == 'o') {
      std::ofstream out_file("result.txt");
      if (out_file.is_open()) {
        out_file << "Mean: " << data.statistics().mean << '\n'
                 << "Sigma: " << data.statistics().sigma << '\n'
                 << "Mean error: " << data.statistics().sigma << '\n'
                 << "Median: " << data.statistics().sigma << '\n';
      }
    } else if (cmd == 'q') {
      return EXIT_SUCCESS;
    }
  }
}