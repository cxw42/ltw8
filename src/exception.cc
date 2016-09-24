// -*- c++ -*-
/* $Id$ */

/* exception.cc
 *
 * Copyright 2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

//#include <glib/gtestutils.h> //For g_assert() in glib >= 2.15.0
//#include <glib/gmessages.h> //For g_assert() in glib < 2.15.0
#include <glib.h> //For g_assert() in all versions of glib.

#ifdef DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
#include <glibmm/exception.h>
#else //ltw8
#include "exception.h"
#endif // DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII

namespace ltw8
{

Exception::~Exception() noexcept
{
}

ltw8::ustring
Exception::what() const
{
  g_assert_not_reached();
  return ltw8::ustring();
}

} // namespace ltw8

