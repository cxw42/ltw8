// ltw8_implementation.h: Implementation-only header for the ltw8 UTF-8 library.
// New code copyright (c) Chris White, 2016.

#include "ltw8_internal.h"
#include <memory>

//DEBUG

// Based on glib/glib/gmessages.h
#define g_return_val_if_fail(expr, val) \
  do { if(!(expr)) { return (val); } } while(0)

// Based on glibmm/glib/glibmm/utility.h
template <typename T>
inline
std::unique_ptr<T[]>
make_unique_ptr_gfree(T* p)
{
  return std::unique_ptr<T[]>(p);
}

namespace ltw8 { using ::make_unique_ptr_gfree; }

//END DEBUG

// vi: set ts=2 sts=2 sw=2 et ai: //
