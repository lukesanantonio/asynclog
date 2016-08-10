/*
 * Copyright (c) 2016 Luke San Antonio Bialecki
 * All rights reserved.
 *
 * Released under the BSD 2-clause license. See LICENSE in the top-level source
 * tree for the entire license text.
 */
#ifndef ASYNCLOG_THREAD_LOCAL_H
#define ASYNCLOG_THREAD_LOCAL_H

  #pragma once
  #if defined(__GNUC__) || defined(__MINGW32__) || defined(__clang__)
    #define AL_THREAD_LOCAL __thread
  #elif defined(_MSC_VER)
    #define AL_THREAD_LOCAL __declspec(thread)
  #endif

#endif // ASYNCLOG_THREAD_LOCAL_H
