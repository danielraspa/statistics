#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <vector>

namespace  pf{
  struct Statistics {
    double mean{};
    double sigma{};
    double mean_err{};
    double median{};
  };

  class Sample {

    std::vector<double> entries_;

    public:
      int size() const {return entries_.size();}

      void add(double);

      bool remove(double);

      const auto& entries() const {return entries_;}

      auto& entries() {return entries_;}

      Statistics statistics() const;

      Sample& operator+=(const Sample&);
  };

  Sample operator+(const Sample& l, const Sample& r);
}

#endif
