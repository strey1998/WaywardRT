// WaywardRT/WaywardRT/src/log.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#ifdef WAYWARDRT_ENABLE_LOGGING

#include "WaywardRT/log.h"

#include <memory>
#include <string>

#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


#ifdef WAYWARDRT_ENABLE_CONSOLE_LOGGING
  static auto console_sink
    = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  static auto file_sink
    = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
  // TODO(TS): Figure out why make_shared is failing when used below
  static auto wlogger_
    = std::shared_ptr<spdlog::logger>(
        new spdlog::logger("WaywardRT", {console_sink, file_sink}));
#else
  static auto wlogger_ = spdlog::basic_logger_mt("WaywardRT", "log.txt");
#endif


std::shared_ptr<spdlog::logger> wlogger() { return wlogger_; }

#endif
