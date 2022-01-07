// WaywardRT/WaywardRT/include/WaywardRT/Timer.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_TIMER_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_TIMER_H_

#include <chrono>

#include "WaywardRT_export.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

class Timer {
 private:
  using clock_type = std::chrono::steady_clock;
  using second_type = std::chrono::duration<double, std::ratio<1> >;

  std::chrono::time_point<clock_type> m_beg { clock_type::now() };

 public:
  void reset() {
    m_beg = clock_type::now();
  }

  double elapsed() const {
    return
      std::chrono::duration_cast<second_type>(clock_type::now() - m_beg)
        .count();
  }
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_TIMER_H_
