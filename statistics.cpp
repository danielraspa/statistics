#include "statistics.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace pf {
  void Sample::add(double x) {
    entries_.push_back(x);
  }

  bool Sample::remove(double x) {
    for (auto it = entries_.begin(); it != entries_.end(); it++) {
      if (x == *it) {
        entries_.erase(it);
        return true;
      }
    }
    return false;
  }

  Statistics Sample::statistics() const {
      const int N(size());

      if (entries_.size() < 2) {
        throw std::runtime_error("There's not enough points");
      } 

      double sum_x_{};
      double sum_x2_{};

      for (auto const& e : entries_)
      {
        sum_x_ += e;
        sum_x2_ += e * e;
      }

      double mean = sum_x_ / N;
      double sigma = std::sqrt((sum_x2_ - N * mean * mean) / (N - 1));
      double mean_err = sigma / std::sqrt(N);
      double median{};

      auto entries{entries_};
      std::sort(entries.begin(), entries.end());

      if (N % 2 != 0) {
        median = entries[N/2];
      } else {
        median = (entries[N/2] + entries[N/2 - 1]) * 0.5;
      }

      return {mean, sigma, mean_err, median};
  }

  Sample& Sample::operator+=(const Sample& r) {
        entries_.reserve(size() + r.size());
        entries_.insert(entries_.end(), r.entries().begin(), r.entries().end());

        return *this;
  }

  Sample operator+(const Sample& l, const Sample& r){
    Sample sum(l);

    return sum += r;
  }
}