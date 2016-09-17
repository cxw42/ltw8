// ltw8_unicode.h: Unicode-routines header for the ltw8 UTF-8 library.
// New code copyright (c) Chris White, 2016.


#ifndef LTW8_UNICODE_H_
#define LTW8_UNICODE_H_

#include "ltw8_gmacros.h"
#include "ltw8_gstrfuncs.h"

// from glib/glib/gunicode.h

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

#ifdef DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
_DEFS(glibmm,glib)

//#m4begin
//_PUSH()
//
//// m4 helper macros to generate the character-class inline functions.
//
//m4_define(`_UNICHAR_FUNC',`dnl
//inline $1 $2(gunichar uc)
//  { return g_unichar_$2(uc); }
//`'dnl`'')
//
////MSVC++ needs the != 0 to avoid an int -> bool cast warning.
//m4_define(`_UNICHAR_FUNC_BOOL',`dnl
//inline $1 $2(gunichar uc)
//  { return (g_unichar_$2(uc) != 0); }
//`'dnl`'')
//
//m4_define(`_ASCII_FUNC',`dnl
//inline $1 $2(char c)
//  { return g_ascii_$2(c); }
//`'dnl`'')
//
//_POP()
//#m4end

#include <glib.h>

#else //ltw8 macros

#define _UNICHAR_FUNC(ty, name) \
  inline ty name(gunichar uc) { return g_unichar_ ## name (uc); }

#define _UNICHAR_FUNC_BOOL(ty, name) \
  inline ty name(gunichar uc) { return (g_unichar_ ## name (uc) != 0); }

#define _ASCII_FUNC(ty, name) \
  inline ty name(char c) { return g_ascii_ ## name (c); }

#endif // DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII


// Not used, but we want to get rid of possible <ctype.h> macros.
#include <cctype>

#undef isalnum
#undef isalpha
#undef iscntrl
#undef isdigit
#undef isgraph
#undef islower
#undef isprint
#undef ispunct
#undef isspace
#undef isupper
#undef isxdigit
#undef istitle
#undef isdefined
#undef iswide
#undef toupper
#undef tolower
#undef totitle


namespace ltw8
{

#ifdef DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII
_WRAP_ENUM(UnicodeType, GUnicodeType, NO_GTYPE)
_WRAP_ENUM(UnicodeBreakType, GUnicodeBreakType, NO_GTYPE)
_WRAP_ENUM(AsciiType, GAsciiType, NO_GTYPE)
_WRAP_ENUM(NormalizeMode, GNormalizeMode, NO_GTYPE)
#else
#define NAMESPACE_LTW8_
#include "ltw8_unicode_enums.h"
#undef NAMESPACE_LTW8_
#endif // DO_NOT_DEFINE_OR_A_BLACK_HOLE_WILL_DESTROY_HAWAII

/** @defgroup Unicode Unicode Manipulation
 * Functions operating on Unicode characters and UTF-8 strings.
 * @{
 */

namespace Unicode
{

_UNICHAR_FUNC_BOOL(bool, validate)
_UNICHAR_FUNC_BOOL(bool, isalnum)
_UNICHAR_FUNC_BOOL(bool, isalpha)
_UNICHAR_FUNC_BOOL(bool, iscntrl)
_UNICHAR_FUNC_BOOL(bool, isdigit)
_UNICHAR_FUNC_BOOL(bool, isgraph)
_UNICHAR_FUNC_BOOL(bool, islower)
_UNICHAR_FUNC_BOOL(bool, isprint)
_UNICHAR_FUNC_BOOL(bool, ispunct)
_UNICHAR_FUNC_BOOL(bool, isspace)
_UNICHAR_FUNC_BOOL(bool, isupper)
_UNICHAR_FUNC_BOOL(bool, isxdigit)
_UNICHAR_FUNC_BOOL(bool, istitle)
_UNICHAR_FUNC_BOOL(bool, isdefined)
_UNICHAR_FUNC_BOOL(bool, iswide)

_UNICHAR_FUNC(gunichar, toupper)
_UNICHAR_FUNC(gunichar, tolower)
_UNICHAR_FUNC(gunichar, totitle)

_UNICHAR_FUNC(int, digit_value)
_UNICHAR_FUNC(int, xdigit_value)

inline ltw8::UnicodeType type(gunichar uc)
  { return static_cast<ltw8::UnicodeType>(static_cast<int>(g_unichar_type(uc))); }

inline ltw8::UnicodeBreakType break_type(gunichar uc)
  { return static_cast<ltw8::UnicodeBreakType>(static_cast<int>(g_unichar_break_type(uc))); }

} // namespace Unicode


namespace Ascii
{

_ASCII_FUNC(bool, isalnum)
_ASCII_FUNC(bool, isalpha)
_ASCII_FUNC(bool, iscntrl)
_ASCII_FUNC(bool, isdigit)
_ASCII_FUNC(bool, isgraph)
_ASCII_FUNC(bool, islower)
_ASCII_FUNC(bool, isprint)
_ASCII_FUNC(bool, ispunct)
_ASCII_FUNC(bool, isspace)
_ASCII_FUNC(bool, isupper)
_ASCII_FUNC(bool, isxdigit)

_ASCII_FUNC(char, tolower)
_ASCII_FUNC(char, toupper)

_ASCII_FUNC(int, digit_value)
_ASCII_FUNC(int, xdigit_value)

} // namespace Ascii


/** @} group Unicode */

} // namespace ltw8

// end from glib/glib/gunicode.h

#endif // LTW8_UNICODE_H_

// vi: set ts=2 sts=2 sw=2 et ai: //

