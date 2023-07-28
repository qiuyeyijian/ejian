#ifndef EJIAN_H
#define EJIAN_H

// internal macros for string concatenation and anonymous variable name
// The reason for defining a two-layer macro is that it can be expanded normally
// when the parameter is another macro
#define EJIAN_CAT_IMPL(s1, s2) s1##s2
#define EJIAN_CAT(s1, s2) EJIAN_CAT_IMPL(s1, s2)
#define EJIAN_STR_IMPL(s) #s
#define EJIAN_STR(s) EJIAN_STR_IMPL(s)
#define EJIAN_CAT_STR_IMPL(s1, s2) EJIAN_STR(EJIAN_CAT(s1, s2))
#define EJIAN_CAT_STR(s1, s2) EJIAN_CAT_STR_IMPL(s1, s2)
#ifdef __COUNTER__  // not standard and may be missing for some compilers
#define EJIAN_ANONYMOUS(x) EJIAN_CAT(x, __COUNTER__)
#else  // __COUNTER__
#define EJIAN_ANONYMOUS(x) EJIAN_CAT(x, __LINE__)
#endif  // __COUNTER__

#define EJIAN_VERSION_MAJOR 2
#define EJIAN_VERSION_MINOR 3
#define EJIAN_VERSION_PATCH 3

#define EJIAN_VERSION_STR        \
  EJIAN_STR(EJIAN_VERSION_MAJOR) \
  "." EJIAN_STR(EJIAN_VERSION_MINOR) "." EJIAN_STR(EJIAN_VERSION_PATCH)

// Determines the platform(architecture) on which EJIAN is compiled.
#ifdef __CYGWIN__
#define EJIAN_OS_CYGWIN 1
#elif defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
#define EJIAN_OS_WINDOWS_MINGW 1
#define EJIAN_OS_WINDOWS 1
#elif defined(WIN32) || defined(_WIN32) || defined(_ON_WIN_)
#define EJIAN_OS_WINDOWS 1
#elif defined(__linux__) || defined(_ON_LINUX_)
#define EJIAN_OS_LINUX 1
#if defined __ANDROID__
#define EJIAN_OS_LINUX_ANDROID 1
#endif
#elif defined(__QNX__) || defined(_ON_QNX_)
#define EJIAN_OS_QNX 1
#elif defined(__TDA4__) || defined(_ON_TDA4_)
#define EJIAN_OS_QNX 1
#elif defined __FreeBSD__
#define EJIAN_OS_FREEBSD 1
#elif defined __APPLE__
#define EJIAN_OS_MAC 1
#include <TargetConditionals.h>
#include <mach-o/dyld.h>
#endif  // __CYGWIN__

// Declare the API of EJIAN
#if EJIAN_OS_WINDOWS
#define EJIAN_API_WINDOWS (1)
#elif (EJIAN_OS_LINUX || EJIAN_OS_QNX || EJIAN_OS_TDA4 || EJIAN_OS_MAC)
#define EJIAN_API_POSIX (1)
#endif
#if (EJIAN_OS_MAC)
#define EJIAN_API_MAC (1)
#endif

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#if EJIAN_API_WINDOWS
typedef unsigned short mode_t;
#else
#include<unistd.h>
#endif

namespace ejian {
namespace utils {
int mkdir(const char* path, mode_t mode);
int mkdirs(const char* path, mode_t mode);
}

}  // namespace ejian
#endif