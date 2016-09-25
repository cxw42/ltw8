// ltw8_implementation.h: Implementation-only header for the ltw8 UTF-8 library.
// New code copyright (c) Chris White, 2016.

#include "ltw8_internal.h"
//#include "ltw8_gtypes.h"
//  // for gpointer
#include <memory>
  // for unique_ptr
#include <stdlib.h>
  // for malloc
#include <stdarg.h>
  // for varargs
#include <stdio.h>
  // for _vasprintf_r
#include <assert.h>

// All of these are hacks to make the routines compile.
// They should be tested or replaced with something better!

#define _IGNORE(x)
  // from gtkmmproc - per 
  // https://github.com/GNOME/glibmm/blob/master/docs/internal/using_gmmproc.txt
  // _IGNORE is an instruction to gmmproc.

#if 0
// Based on glib/glib/gmessages.h
#define g_return_val_if_fail(expr, val) \
  do { if(!(expr)) { return (val); } } while(0)
#endif

#if 0
// Based on glibmm/glib/glibmm/utility.h
template <typename T>
inline
std::unique_ptr<T[]>
make_unique_ptr_gfree(T* p)
{
  return std::unique_ptr<T[]>(p);
}

namespace ltw8 { using ::make_unique_ptr_gfree; }
#endif

#if 0
// Memory management: use malloc/free since delete<void *> is undefined

#define g_malloc malloc

template<class T>
inline T *
ltw8_g_new(int count) {
// based on glib/glib/gmem.c
  size_t sz = sizeof(T);
  void *ret = malloc(sz*count);
  return static_cast<T*>(ret);
} //ltw8_g_new

#define g_new(ty, count) ltw8_g_new<ty>(count)

inline void g_free(gpointer ptr) { free(ptr); }

// Logging: TODO actually do logging :)
#define g_warning(...) ((void)0)

#define g_assert assert

// Output
inline 
gint
g_vasprintf (gchar **string,
             gchar const *format,
             va_list args)
{
  struct _reent re;
  return _vasprintf_r(&re, string, format, args);
    // TODO see if this needs to change on other than Cygwin
}

// From glib/glib/gprintfint.h
#define _g_printf    printf
#define _g_fprintf   fprintf
#define _g_sprintf   sprintf
#define _g_snprintf  snprintf

#endif

// vi: set ts=2 sts=2 sw=2 et ai syntax=cpp: //

