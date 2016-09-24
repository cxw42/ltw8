// -*- c++ -*-
// stringutils.cc from the ltw8 UTF-8 library.
// New code copyright (c) Chris White, 2016.

#include "ltw8_stringutils.h"
#include "ltw8_implementation.h"


// from glibmm/glib/glibmm/stringutils.cc
/* $Id$ */

/* Copyright (C) 2002 The gtkmm Development Team
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

//#include <glibmmconfig.h>
#include <utility.h>
#include <glib.h>
#include <cerrno>
#include <stdexcept>

// Note: If compilation problems,
// per https://gcc.gnu.org/ml/gcc-help/2009-10/msg00242.html, 
// can't do this as "ltw8::..." but instead need "namespace ltw8 {...}" 
bool
ltw8::str_has_prefix(const std::string& str, const std::string& prefix)
{
  return g_str_has_prefix(str.c_str(), prefix.c_str());
}

bool
ltw8::str_has_suffix(const std::string& str, const std::string& suffix)
{
  return g_str_has_suffix(str.c_str(), suffix.c_str());
}

double
ltw8::Ascii::strtod(const std::string& str)
{
  std::string::size_type dummy;
  return ltw8::Ascii::strtod(str, dummy, 0);
}

double
ltw8::Ascii::strtod(
  const std::string& str, std::string::size_type& end_index, std::string::size_type start_index)
{
  if (start_index >= str.size())
  {
    throw std::out_of_range("out of range (strtod): start_index > str.size()");
  }

  const char* const bufptr = str.c_str();
  char* endptr = nullptr;

  const double result = g_ascii_strtod(bufptr + start_index, &endptr);
  const int err_no = errno;

  if (err_no != 0)
  {
    g_return_val_if_fail(err_no == ERANGE, result);

    // Interpret the result in the event of an error:
    if (result > 0.0)
      throw std::overflow_error("overflow (strtod): positive number too large");

    if (result < 0.0)
      throw std::overflow_error("overflow (strtod): negative number too large");

    throw std::underflow_error("underflow (strtod): number too small");
  }

  if (endptr)
    end_index = endptr - bufptr;
  else
    end_index = str.size();

  return result;
}

std::string
ltw8::Ascii::dtostr(double d)
{
  char buf[G_ASCII_DTOSTR_BUF_SIZE];

  return g_ascii_dtostr(buf, sizeof(buf), d);
}

std::string
ltw8::strescape(const std::string& source)
{
  const auto buf = make_unique_ptr_gfree(g_strescape(source.c_str(), nullptr));
  return buf.get();
}

std::string
ltw8::strescape(const std::string& source, const std::string& exceptions)
{
  const auto buf = make_unique_ptr_gfree(g_strescape(source.c_str(), exceptions.c_str()));
  return buf.get();
}

std::string
ltw8::strcompress(const std::string& source)
{
  const auto buf = make_unique_ptr_gfree(g_strcompress(source.c_str()));
  return buf.get();
}

ltw8::ustring
ltw8::strerror(int errnum)
{
//#ifdef DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
  return g_strerror(errnum);
//#else //ltw8
//  return ltw8::ustring("");
//#endif // DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
}

ltw8::ustring
ltw8::strsignal(int signum)
{
  return g_strsignal(signum);
}

// vi: set ts=2 sts=2 sw=2 et ai: //

