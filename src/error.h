// -*- c++ -*-
#ifndef LTW8_ERROR_H_
#define LTW8_ERROR_H_

/* Copyright 2002 The gtkmm Development Team
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

#ifdef DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
#include <glibmmconfig.h>
#include <glibmm/exception.h>
#else //ltw8
#include <glib.h>
#include "exception.h"
#endif

namespace ltw8
{

class Error : public ltw8::Exception
{
public:
  Error();
  Error(GQuark error_domain, int error_code, const ltw8::ustring& message);
  explicit Error(GError* gobject, bool take_copy = false);

  Error(const Error& other);
  Error& operator=(const Error& other);

  ~Error() noexcept override;

  GQuark domain() const;
  int code() const;
  ltw8::ustring what() const override;

  bool matches(GQuark error_domain, int error_code) const;

  GError* gobj();
  const GError* gobj() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

  void propagate(GError** dest);

  using ThrowFunc = void(*)(GError*);

  static void register_init();
  static void register_cleanup();
  static void register_domain(GQuark error_domain, ThrowFunc throw_func);

  static void throw_exception(GError* gobject) G_GNUC_NORETURN;

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

protected:
  GError* gobject_;
};

} // namespace ltw8

#endif /* LTW8_ERROR_H_ */
