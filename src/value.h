#ifndef _GLIBMM_VALUE_H
#define _GLIBMM_VALUE_H

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

//#include <glibmmconfig.h>
#include <refptr.h>
#include "ltw8_ustring.h"
#include <enums.h>
#include <glib-object.h>

namespace ltw8
{

class ObjectBase;
class Object;

/** @defgroup glibmmValue Generic Values
 *
 * ltw8::Value<> is specialized for almost any type used within
 * the glibmm and gtkmm libraries.
 *
 * - Basic types like <tt>int</tt>, <tt>char</tt>, <tt>bool</tt>, etc., also <tt>void*</tt>.
 * - ltw8::ustring and std::string.
 * - Pointers to classes derived from ltw8::Object.
 * - ltw8::RefPtr<> pointer types, which are assumed to be ltw8::Object pointers.
 * - All flags and enum types used within the gtkmm libraries.
 *
 * If a type doesn't fit into any of these categories, then a generic
 * implementation for custom types will be used.  The requirements imposed
 * on custom types are described in the ltw8::Value class documentation.
 */

/**
 * @ingroup glibmmValue
 */
class ValueBase
{
public:
  /** Initializes the GValue, but without a type.  You have to
   * call init() before using the set(), get(), or reset() methods.
   */
  ValueBase();

  ValueBase(const ValueBase& other);
  ValueBase& operator=(const ValueBase& other);

  ~ValueBase() noexcept;

  /** Setup the GValue for storing the specified @a type.
   * The contents will be initialized to the default value for this type.
   * Note that init() should never be called twice.
   *
   * init() is not implemented as constructor, to avoid the necessity
   * to implement a forward constructor in each derived class.
   *
   * @param type The type that the Value should hold.
   */
  void init(GType type);

  /** Setup the GValue storing the type and value of the specified @a value.
   * Note that init() should never be called twice.
   *
   * init() is not implemented as constructor, to avoid the necessity
   * to implement a forward constructor in each derived class.
   *
   * @param value The existing GValue.
   */
  void init(const GValue* value);

  /** Reset contents to the default value of its type.
   */
  void reset();

  GValue* gobj() { return &gobject_; }
  const GValue* gobj() const { return &gobject_; }

protected:
  GValue gobject_;
};

/**
 * @ingroup glibmmValue
 */
class ValueBase_Boxed : public ValueBase
{
public:
  static GType value_type() G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GParamSpec* create_param_spec(const ltw8::ustring& name) const;
  GParamSpec* create_param_spec(const ltw8::ustring& name, const ltw8::ustring& nick,
                                const ltw8::ustring& blurb, ltw8::ParamFlags flags) const;
#endif

protected:
  void set_boxed(const void* data);
  void* get_boxed() const; // doesn't copy
};

/**
 * @ingroup glibmmValue
 */
class ValueBase_Object : public ValueBase
{
public:
  static GType value_type() G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GParamSpec* create_param_spec(const ltw8::ustring& name) const;
  GParamSpec* create_param_spec(const ltw8::ustring& name, const ltw8::ustring& nick,
                                const ltw8::ustring& blurb, ltw8::ParamFlags flags) const;

#endif

protected:
  void set_object(ltw8::ObjectBase* data);
  ltw8::ObjectBase* get_object() const;
  ltw8::RefPtr<ltw8::ObjectBase> get_object_copy() const;
};

/**
 * @ingroup glibmmValue
 */
class ValueBase_Enum : public ValueBase
{
public:
  using CType = gint;
  static GType value_type() G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GParamSpec* create_param_spec(const ltw8::ustring& name) const;
  GParamSpec* create_param_spec(const ltw8::ustring& name, const ltw8::ustring& nick,
                                const ltw8::ustring& blurb, ltw8::ParamFlags flags) const;

#endif

protected:
  void set_enum(int data);
  int get_enum() const;
};

/**
 * @ingroup glibmmValue
 */
class ValueBase_Flags : public ValueBase
{
public:
  using CType = guint;
  static GType value_type() G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GParamSpec* create_param_spec(const ltw8::ustring& name) const;
  GParamSpec* create_param_spec(const ltw8::ustring& name, const ltw8::ustring& nick,
                                const ltw8::ustring& blurb, ltw8::ParamFlags flags) const;

#endif

protected:
  void set_flags(unsigned int data);
  unsigned int get_flags() const;
};

/**
 * @ingroup glibmmValue
 */
class ValueBase_String : public ValueBase
{
public:
  using CType = const gchar*;
  static GType value_type() G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GParamSpec* create_param_spec(const ltw8::ustring& name) const;
  GParamSpec* create_param_spec(const ltw8::ustring& name, const ltw8::ustring& nick,
                                const ltw8::ustring& blurb, ltw8::ParamFlags flags) const;

#endif

protected:
  void set_cstring(const char* data);
  const char* get_cstring() const; // never returns nullptr
};

} // namespace ltw8

/* Include generic ltw8::Value<> template, before any specializations:
 */
#define _GLIBMM_VALUE_H_INCLUDE_VALUE_CUSTOM_H
#include <value_custom.h>
#undef _GLIBMM_VALUE_H_INCLUDE_VALUE_CUSTOM_H

namespace ltw8
{

/**
 * @ingroup glibmmValue
 */
template <class T>
class Value_Boxed : public ValueBase_Boxed
{
public:
  using CppType = T;
  using CType = typename T::BaseObjectType*;

  static GType value_type() { return T::get_type(); }

  void set(const CppType& data) { set_boxed(data.gobj()); }
  CppType get() const { return CppType(static_cast<CType>(get_boxed())); }
};

// More spec-compliant compilers (such as Tru64) need this to be near ltw8::Object instead.
#ifdef GLIBMM_CAN_USE_DYNAMIC_CAST_IN_UNUSED_TEMPLATE_WITHOUT_DEFINITION

/** Partial specialization for RefPtr<> to ltw8::Object.
 * @ingroup glibmmValue
 */
template <class T>
class Value<ltw8::RefPtr<T>> : public ValueBase_Object
{
public:
  using CppType = ltw8::RefPtr<T>;
  using CType = typename T::BaseObjectType*;

  static GType value_type() { return T::get_base_type(); }

  void set(const CppType& data) { set_object(data.operator->()); }
  CppType get() const { return ltw8::RefPtr<T>::cast_dynamic(get_object_copy()); }
};

// The SUN Forte Compiler has a problem with this:
#ifdef GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS

/** Partial specialization for RefPtr<> to const ltw8::Object.
 * @ingroup glibmmValue
 */
template <class T>
class Value<ltw8::RefPtr<const T>> : public ValueBase_Object
{
public:
  using CppType = ltw8::RefPtr<const T>;
  using CType = typename T::BaseObjectType*;

  static GType value_type() { return T::get_base_type(); }

  void set(const CppType& data) { set_object(const_cast<T*>(data.operator->())); }
  CppType get() const { return ltw8::RefPtr<T>::cast_dynamic(get_object_copy()); }
};
#endif // GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS

#endif // GLIBMM_CAN_USE_DYNAMIC_CAST_IN_UNUSED_TEMPLATE_WITHOUT_DEFINITION

} // namespace ltw8

/* Include generated specializations of ltw8::Value<> for fundamental types:
 */
#define _GLIBMM_VALUE_H_INCLUDE_VALUE_BASICTYPES_H
#include <value_basictypes.h>
#undef _GLIBMM_VALUE_H_INCLUDE_VALUE_BASICTYPES_H

namespace ltw8
{

/** Specialization for strings.
 * @ingroup glibmmValue
 */
template <>
class Value<std::string> : public ValueBase_String
{
public:
  using CppType = std::string;

  void set(const std::string& data);
  std::string get() const { return get_cstring(); }
};

/** Specialization for UTF-8 strings.
 * @ingroup glibmmValue
 */
template <>
class Value<ltw8::ustring> : public ValueBase_String
{
public:
  using CppType = ltw8::ustring;

  void set(const ltw8::ustring& data);
  ltw8::ustring get() const { return get_cstring(); }
};

/** Base class of ltw8::Value<T> specializations for enum types.
 * @ingroup glibmmValue
 */
template <class T>
class Value_Enum : public ValueBase_Enum
{
public:
  using CppType = T;

  void set(CppType data) { set_enum(data); }
  CppType get() const { return CppType(get_enum()); }
};

/** Base class of ltw8::Value<T> specializations for flags types.
 * @ingroup glibmmValue
 */
template <class T>
class Value_Flags : public ValueBase_Flags
{
public:
  using CppType = T;

  void set(CppType data) { set_flags(data); }
  CppType get() const { return CppType(get_flags()); }
};

} // namespace ltw8

#endif /* _GLIBMM_VALUE_H */