// -*- c++ -*-
#ifndef LTW8_WRAP_INIT_H_
#define LTW8_WRAP_INIT_H_

/* $Id$ */

/* wrap_init.h
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

#ifdef DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
#include <glibmm/error.h>
#else //ltw8
#include "error.h"
#endif

namespace ltw8
{

void wrap_init();

} // namespace ltw8

#endif /* LTW8_WRAP_INIT_H_ */
