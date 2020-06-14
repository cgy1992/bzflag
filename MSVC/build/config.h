/* bzflag
 * Copyright (c) 1993-2020 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* win32/config.h.  Generated by hand by Jeff Myers 6-12-03 */
/* this config is just for visual C++ since it doesn't use automake*/

// Don't complain about using "insecure" string functions.
// This is safe, Microsoft says they will not be removed.
#define _CRT_SECURE_NO_DEPRECATE 1

// We use some POSIX names, but defining _POSIX_ breaks some other code.
// Tell VC8 to just shut up about it.  This is possibly unsafe, as the
// affected functions may be removed in the future.
#define _CRT_NONSTDC_NO_DEPRECATE 1

/* Building regex */
#define HAVE_REGEX_H 1

/* Debug Rendering */
/* #undef DEBUG_RENDERING */

/* Enabling Robots */
#define ROBOT 1

/* On windows, strcasecmp is really strcmp */
#define HAVE_STRICMP 1

/* Use modern template for std::count */
#define HAVE_STD__COUNT 1

/* Use modern template for std::isnan */
#define HAVE_STD__ISNAN 1

/* We have float math functions */
#define HAVE_ASINF 1
#define HAVE_ATAN2F 1
#define HAVE_ATANF 1
#define HAVE_COSF 1
#define HAVE_EXPF 1
#define HAVE_FABSF 1
#define HAVE_FLOORF 1
#define HAVE_FMODF 1
#define HAVE_LOGF 1
#define HAVE_POWF 1
#define HAVE_SINF 1
#define HAVE_SQRTF 1
#define HAVE_TANF 1
#define HAVE_LOG10F 1
#define HAVE_STD__ISNAN 1

/* but we don't have this one */
/* #undef HAVE_HYPOTF */

/* Define to 1 if you have regex stuff available */
/* undef HAVE_REGEX_H */

// define our OS

#ifndef BZ_BUILD_OS
#ifndef BZ_MSVC_VER
#if (_MSC_VER >= 1400 && _MSC_VER < 1500)
#define BZ_MSVC_VER "VC8"
#elif (_MSC_VER >= 1500 && _MSC_VER < 1600)
#define BZ_MSVC_VER "VC9"
#elif (_MSC_VER >= 1600 && _MSC_VER < 1700)
#define BZ_MSVC_VER "VC10"
#elif (_MSC_VER >= 1700 && _MSC_VER < 1800)
#define BZ_MSVC_VER "VC11"
#elif (_MSC_VER >= 1800 && _MSC_VER < 1900)
#define BZ_MSVC_VER "VC12"
#elif (_MSC_VER >= 1900 && _MSC_VER <= 1916)
#define BZ_MSVC_VER "VC14"
#else
#error MSVC version out of range. Please update MSVC/build/config.h.
#endif
#endif // BZ_MSVC_VER
#ifdef _DEBUG
#define DEBUG
#define DEBUG_RENDERING
#ifdef _M_X64
#define BZ_BUILD_OS         "Win64" BZ_MSVC_VER "Dbg"
#else
#define BZ_BUILD_OS         "Win32" BZ_MSVC_VER "Dbg"
#endif
#else
#ifdef _M_X64
#define BZ_BUILD_OS         "Win64" BZ_MSVC_VER
#else
#define BZ_BUILD_OS         "Win32" BZ_MSVC_VER
#endif
#endif //_DEBUG
#endif //BZ_BUILD_OS

/* Define to 1 if you have the `WaitForSingleObject' function. */
#define HAVE_WAITFORSINGLEOBJECT 1

/* Define to 1 if you have the `Sleep' function. */
#define HAVE_SLEEP 1

/* Define to 1 if you have the `_stricmp' function */
#define HAVE__STRICMP 1

/* Define to 1 if you have the `_strnicmp' function */
#define HAVE__STRNICMP 1

/* Define to 1 if you have the `_vsnprintf' function */
#define HAVE__VSNPRINTF 1

/* Define if you wish to build exporting the bzflag API for plugins */
#define BZ_PLUGINS 1

// Use SDL2
#define HAVE_SDL 1
#define HAVE_SDL2 1
#define HAVE_SDL2_SDL_H 1

#define HAVE_STD__MIN 1
#define HAVE_STD__MAX 1

#define HAVE_ARES_LIBRARY_INIT 1
