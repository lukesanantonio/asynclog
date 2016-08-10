/*
 * Copyright (c) 2016 Luke San Antonio Bialecki
 * All rights reserved.
 *
 * Released under the BSD 2-clause license. See LICENSE in the top-level source
 * tree for the entire license text.
 */
#ifndef ASYNCLOG_LOG_H
#define ASYNCLOG_LOG_H
#include <string>
#include "translate.h"

// Use the macros when you want to be able to disable those messages at compile
// time. Define ASLOG_DISABLE_LOGGING to disable them, or define it only when
// debugging is not enabled, for example.
#ifndef AL_DISABLE_LOGGING
  // This macro leaks, use Scoped_Log_Init when you can, but if you can't just
  // make sure to uninit_log() when you are done. It's no problem because that
  // will succeed even if the logging lib was never initialized in the first
  // place. Also, feel free to initialize the logger multiple times, any
  // additional calls to init_log are no-ops (no reference counting is done, one
  // call to uninit_log is all you need to uninitialize the whole logger, no
  // matter how many times init was called).
  #define AL_LOG_ATTEMPT_INIT() init_log()

  #define AL_LOG_E(...) redc::log_e(__VA_ARGS__)
  #define AL_LOG_W(...) redc::log_w(__VA_ARGS__)
  #define AL_LOG_I(...) redc::log_i(__VA_ARGS__)
  #define AL_LOG_D(...) redc::log_d(__VA_ARGS__)
#else
  #define AL_LOG_ATTEMPT_INIT() ((void*)0)

  #define AL_LOG_E ((void*)0)
  #define AL_LOG_W ((void*)0)
  #define AL_LOG_I ((void*)0)
  #define AL_LOG_D ((void*)0)
#endif

namespace al
{
  struct Scoped_Log_Init
  {
    Scoped_Log_Init() noexcept;
    ~Scoped_Log_Init() noexcept;
  };

  void init_log() noexcept;
  void uninit_log() noexcept;

  void flush_log() noexcept;
  void flush_log_full() noexcept;

  // Higher is more severe!
  enum class Log_Severity : unsigned int
  {
    Debug = 0, Info = 1, Warning = 2, Error = 3
  };

  void set_log_file(std::string filename) noexcept;
  void set_out_log_level(Log_Severity level) noexcept;
  void set_file_log_level(Log_Severity level) noexcept;

  inline void log() {}

  template <class... Args>
  inline void log(Log_Severity severity, std::string msg, Args&&... args) noexcept
  {
    log(severity, format(msg, 0, "", std::forward<Args>(args)...));
  }
  void log(Log_Severity severity, std::string msg) noexcept;

  inline void log_e() {}

  inline void log_e(std::string msg) noexcept
  {
    log(Log_Severity::Error, msg);
  }

  template <class... Args>
  inline void log_e(std::string msg, Args&&... args) noexcept
  {
    log_e(format(msg, 0, "", std::forward<Args>(args)...));
  }

  inline void log_w() {}

  inline void log_w(std::string msg) noexcept
  {
    log(Log_Severity::Warning, msg);
  }

  template <class... Args>
  inline void log_w(std::string msg, Args&&... args) noexcept
  {
    log_w(format(msg, 0, "", std::forward<Args>(args)...));
  }

  inline void log_i() {}

  inline void log_i(std::string msg) noexcept
  {
    log(Log_Severity::Info, msg);
  }

  template <class... Args>
  inline void log_i(std::string msg, Args&&... args) noexcept
  {
    log_i(format(msg, 0, "", std::forward<Args>(args)...));
  }

  inline void log_d() {}

  inline void log_d(std::string msg) noexcept
  {
    log(Log_Severity::Debug, msg);
  }

  template <class... Args>
  inline void log_d(std::string msg, Args&&... args) noexcept
  {
    log_d(format(msg, 0, "", std::forward<Args>(args)...));
  }
}
#endif // ASYNCLOG_LOG_H
