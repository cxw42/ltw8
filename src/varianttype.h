// TODO gmmproc processing
/* Copyright 2010 The glibmm Development Team
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

_DEFS(glibmm,glib)

//#include <glibmmconfig.h>
#include <glib-object.h> //For gsize
#include <string>
#include <vector>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GVariantType GVariantType;
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace ltw8
{

/** VariantType - The VariantBase type system.
 * The VariantBase type system is based, in large part, on the D-Bus type
 * system, with two major changes and some minor lifting of restrictions. <a
 * href="http://dbus.freedesktop.org/doc/dbus-specification.html">The
 * D-Bus specification</a>, therefore, provides a significant amount of
 * information that is useful when working with VariantBase.
 *
 * The first major change with respect to the D-Bus type system is the
 * introduction of maybe (or "nullable") types. Any type in VariantBase
 * can be converted to a maybe type, in which case, "nothing" (or "null")
 * becomes a valid value. Maybe types have been added by introducing the
 * character "m" to type strings.
 *
 * The second major change is that the VariantBase type system supports
 * the concept of "indefinite types" -- types that are less specific than the
 * normal types found in D-Bus. For example, it is possible to speak of "an
 * array of any type" in VariantBase, where the D-Bus type system would
 * require you to speak of "an array of integers" or "an array of strings".
 * Indefinite types have been added by introducing the characters "*", "?" and
 * "r" to type strings.
 *
 * Finally, all arbitrary restrictions relating to the complexity of types are
 * lifted along with the restriction that dictionary entries may only appear
 * nested inside of arrays.
 *
 * Just as in D-Bus, VariantBase types are described with strings ("type
 * strings"). Subject to the differences mentioned above, these strings are of
 * the same form as those found in D-Bus. Note, however: D-Bus always works in
 * terms of messages and therefore individual type strings appear nowhere in
 * its interface. Instead, "signatures" are a concatenation of the strings of
 * the type of each argument in a message. VariantBase deals with single
 * values directly so VariantBase type strings always describe the type
 * of exactly one value. This means that a D-Bus signature string is generally
 * not a valid VariantBase type string -- except in the case that it is
 * the signature of a message containing exactly one argument.
 *
 * An indefinite type is similar in spirit to what may be called an abstract
 * type in other type systems. No value can exist that has an indefinite type
 * as its type, but values can exist that have types that are subtypes of
 * indefinite types. That is to say, VariantBase::get_type() will never
 * return an indefinite type, but calling VariantBase::is_of_type() with
 * an indefinite type may return <tt>true</tt>. For example, you cannot have a
 * value that represents "an array of no particular type", but you can have an
 * "array of integers" which certainly matches the type of "an array of no
 * particular type", since "array of integers" is a subtype of "array of no
 * particular type".
 *
 * This is similar to how instances of abstract classes may not directly exist
 * in other type systems, but instances of their non-abstract subtypes may. For
 * example, in gtkmm, no object that has the type of Gtk::Bin can exist (since
 * Gtk::Bin is an abstract class), but a Gtk::Window can certainly be
 * instantiated, and you would say that the Gtk::Window is a Gtk::Bin (since
 * Gtk::Window is a subclass of Gtk::Bin).
 *
 * See the underlying GVariantType documentation for <a href="http://library.gnome.org/devel/glib/unstable/glib-GVariantType.html#gvariant-typestrings">detailed description of the VariantBase type strings</a>.
 *
 * @newin{2,28}
 * @ingroup Variant
 */
class VariantType
{
  _CLASS_OPAQUE_COPYABLE(VariantType, GVariantType, NONE, g_variant_type_copy, g_variant_type_free)
  _IGNORE(g_variant_type_copy, g_variant_type_free)
public:

  /** Copy the C item into a new VariantType instance.
   */
  explicit VariantType(const GVariantType* castitem);

  /** Creates a new VariantType corresponding to the type string given by @a type_string.
    *
    * It is a programmer error to call this function with an invalid type string. Use string_is_valid() if you are unsure.
    */
  explicit VariantType(const std::string& type_string);
  _IGNORE(g_variant_type_new)

  VariantType& operator=(const GVariantType* castitem);


//The C parameters are actually const, but gmmproc doesn't understand that,
//so we add a m4 conversion to satisfy it:
#m4 _CONVERSION(`const VariantType&',`GVariantType*',`($3).gobj()')
  _WRAP_METHOD(static VariantType create_array(const VariantType& element), g_variant_type_new_array)
  _WRAP_METHOD(static VariantType create_maybe(const VariantType& element), g_variant_type_new_maybe)

  /** Constructs a new tuple type, from @a items.
    *
    * @param items A vector of VariantTypes, one for each item.
    * @return A new tuple VariantType.
    *
    * @newin{2,36}
    */
  static VariantType create_tuple(const std::vector<VariantType>& items);
  _IGNORE(g_variant_type_new_tuple)

  _WRAP_METHOD(static VariantType create_dict_entry(const VariantType& key, const VariantType& value), g_variant_type_new_dict_entry)

  //TODO: Use something instead of gsize?
  _WRAP_METHOD(gsize _get_string_length() const, g_variant_type_get_string_length)
  dnl wrapped by hand, because g_variant_type_peek_string does not return a C string.
  _WRAP_METHOD_DOCS_ONLY(g_variant_type_peek_string)
  std::string get_string() const;
  _IGNORE(g_variant_type_dup_string)

  _WRAP_METHOD(bool is_definite() const, g_variant_type_is_definite)
  _WRAP_METHOD(bool is_container() const, g_variant_type_is_container)
  _WRAP_METHOD(bool is_basic() const, g_variant_type_is_basic)
  _WRAP_METHOD(bool is_maybe() const, g_variant_type_is_maybe)
  _WRAP_METHOD(bool is_array() const, g_variant_type_is_array)
  _WRAP_METHOD(bool is_tuple() const, g_variant_type_is_tuple)
  _WRAP_METHOD(bool is_dict_entry() const, g_variant_type_is_dict_entry)
  _WRAP_METHOD(bool is_variant() const, g_variant_type_is_variant)

  #m4 _CONVERSION(`const VariantType&',`gconstpointer',`const_cast<GVariantType*>(($3).gobj())')
  _WRAP_METHOD(guint hash() const, g_variant_type_hash)

  /** Compares @a *this and @a other for equality.
   *
   * Only returns <tt>true</tt> if the types are exactly equal.  Even if one type
   * is an indefinite type and the other is a subtype of it, <tt>false</tt> will
   * be returned if they are not exactly equal.  If you want to check for
   * subtypes, use is_subtype_of().
   *
   * @param other The VariantType to compare with.
   * @return <tt>true</tt> if @a *this and @a other are exactly equal.
   *
   * @newin{2,24}
   */
  _WRAP_METHOD(bool equal(const VariantType& other) const, g_variant_type_equal)

  _WRAP_METHOD(bool is_subtype_of(const VariantType& supertype) const, g_variant_type_is_subtype_of)

// It's necessary to take an extra reference of the 'const GVariantType*'
// returned by g_variant_type_element() because it doesn't do that already.
#m4 _CONVERSION(`const GVariantType*',`VariantType',`ltw8::wrap(const_cast<GVariantType*>($3), true)')
  _WRAP_METHOD(VariantType element() const, g_variant_type_element)
  _WRAP_METHOD(VariantType first() const, g_variant_type_first)
  _WRAP_METHOD(VariantType next () const, g_variant_type_next)
  _WRAP_METHOD(gsize n_items() const, g_variant_type_n_items)
  _WRAP_METHOD(VariantType key() const, g_variant_type_key)
  _WRAP_METHOD(VariantType value() const, g_variant_type_value)

  // This function is part of unexposed API in gvarianttypeinfo.{h,c} for an
  // also unexposed GVariantTypeInfo structure of glib.
  _IGNORE(g_variant_type_info_get)
};

extern const VariantType VARIANT_TYPE_BOOL;

extern const VariantType VARIANT_TYPE_BYTE;

extern const VariantType VARIANT_TYPE_INT16;

extern const VariantType VARIANT_TYPE_UINT16;

extern const VariantType VARIANT_TYPE_INT32;

extern const VariantType VARIANT_TYPE_UINT32;

extern const VariantType VARIANT_TYPE_INT64;

extern const VariantType VARIANT_TYPE_UINT64;

extern const VariantType VARIANT_TYPE_DOUBLE;

extern const VariantType VARIANT_TYPE_STRING;

extern const VariantType VARIANT_TYPE_OBJECT_PATH;

extern const VariantType VARIANT_TYPE_SIGNATURE;

extern const VariantType VARIANT_TYPE_VARIANT;

extern const VariantType VARIANT_TYPE_HANDLE;

extern const VariantType VARIANT_TYPE_UNIT;

extern const VariantType VARIANT_TYPE_ANY;

extern const VariantType VARIANT_TYPE_BASIC;

extern const VariantType VARIANT_TYPE_MAYBE;

extern const VariantType VARIANT_TYPE_ARRAY;

extern const VariantType VARIANT_TYPE_TUPLE;

extern const VariantType VARIANT_TYPE_DICT_ENTRY;

extern const VariantType VARIANT_TYPE_DICTIONARY;

extern const VariantType VARIANT_TYPE_STRING_ARRAY;

extern const VariantType VARIANT_TYPE_BYTESTRING;

extern const VariantType VARIANT_TYPE_BYTESTRING_ARRAY;



} // namespace ltw8