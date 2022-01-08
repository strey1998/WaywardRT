// WaywardRT/WaywardRT/include/WaywardRT/Log.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_LOG_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_LOG_H_

#ifdef WAYWARDRT_ENABLE_LOGGING

#include <memory>

#include "spdlog/spdlog.h"

#include "WaywardRT_export.h"

WAYWARDRT_EXPORT std::shared_ptr<spdlog::logger> wlogger();

#define WLOG_LEVEL_TRACE  spdlog::level::debug
#define WLOG_LEVEL_INFO   spdlog::level::info
#define WLOG_LEVEL_WARN   spdlog::level::warn
#define WLOG_LEVEL_ERROR  spdlog::level::error

#define WLOG_SET_LEVEL(x)    wlogger()->set_level(x)
#define WLOG_SET_PATTERN(x)  wlogger()->set_pattern(x)
#define WLOG_TRACE(...)      wlogger()->debug(__VA_ARGS__)
#define WLOG_INFO(...)       wlogger()->info(__VA_ARGS__)
#define WLOG_WARN(...)       wlogger()->warn(__VA_ARGS__)
#define WLOG_ERROR(...)      wlogger()->error(__VA_ARGS__)
#define WLOG_FATAL(...)      wlogger()->error(__VA_ARGS__); exit(1);

#else

#define WLOG_LEVEL_TRACE
#define WLOG_LEVEL_INFO
#define WLOG_LEVEL_WARN
#define WLOG_LEVEL_ERROR

#define WLOG_SET_LEVEL(x)
#define WLOG_SET_PATTERN(x)
#define WLOG_TRACE(...)
#define WLOG_INFO(...)
#define WLOG_WARN(...)
#define WLOG_ERROR(...)
#define WLOG_FATAL(...)

#endif

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_LOG_H_
