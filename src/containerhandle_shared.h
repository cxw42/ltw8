#ifndef _GLIBMM_CONTAINERHANDLE_SHARED_H
#define _GLIBMM_CONTAINERHANDLE_SHARED_H

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
#include <refptr.h>
#include "ltw8_ustring.h"
#include <variant.h>
#include <wrap.h>
#include <debug.h>
#include <glib-object.h>

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <vector>
#include <deque>
#include <list>

namespace ltw8
{

/** @defgroup ContHandles Generic container converters
 */

/**
 * @ingroup ContHandles
 */

//! Ownership of the container
/*! Defines how and if the container will release the list and
 * its elemens when it is destroyed
 */
enum OwnershipType
{
  OWNERSHIP_NONE = 0, /*!< Do not release anything */
  OWNERSHIP_SHALLOW, /*!< Release the list, but not its elements, when the container is deleted */
  OWNERSHIP_DEEP /*!< Release the list, and its elements, when the container is deleted. */
};

/** Utility class holding an iterator sequence.
 * @ingroup ContHandles
 * This can be used to initialize a ltw8 container handle (such as
 * ltw8::ArrayHandle) with an iterator sequence.  Use the helper
 * function ltw8::sequence() to create a Sequence<> object.
 */
template <class Iterator>
class Sequence
{
private:
  Iterator pbegin_;
  Iterator pend_;

public:
  Sequence(Iterator pbegin, Iterator pend) : pbegin_(pbegin), pend_(pend) {}

  Iterator begin() const { return pbegin_; }
  Iterator end() const { return pend_; }
  std::size_t size() const { return std::distance(pbegin_, pend_); }
};

/** Helper function to create a ltw8::Sequence<> object, which
 * in turn can be used to initialize a container handle.
 * @ingroup ContHandles
 *
 * @par Usage example:
 * @code
 * combo.set_popdown_strings(ltw8::sequence(foo_begin, foo_end));
 * @endcode
 */
template <class Iterator>
inline Sequence<Iterator>
sequence(Iterator pbegin, Iterator pend)
{
  return Sequence<Iterator>(pbegin, pend);
}

namespace Container_Helpers
{

/** @defgroup ContHelpers Helper classes
 * @ingroup ContHandles
 */

/** Generic TypeTraits implementation.
 * @ingroup ContHelpers
 * This can be used if the C++ type is the same as the C type, or if implicit
 * conversions between the types are available.  Also, the types are required
 * to implement copy-by-value semantics.  (Ownership is just ignored.)
 */
template <class T>
struct TypeTraits
{
  using CppType = T;
  using CType = T;
  using CTypeNonConst = T;

  static CType to_c_type(const CppType& item) { return item; }
  static CppType to_cpp_type(const CType& item) { return item; }
  static void release_c_type(const CType&) {}
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS /* hide the specializations */

// For some (probably, more spec-compliant) compilers, these specializations must
// be next to the objects that they use.
#ifdef GLIBMM_CAN_USE_DYNAMIC_CAST_IN_UNUSED_TEMPLATE_WITHOUT_DEFINITION

/** Partial specialization for pointers to GtkObject instances.
 * @ingroup ContHelpers
 */
template <class T>
struct TypeTraits<T*>
{
  using CppType = T*;
  using CType = typename T::BaseObjectType*;
  using CTypeNonConst = typename T::BaseObjectType*;

  static CType to_c_type(CppType ptr) { return ltw8::unwrap(ptr); }
  static CType to_c_type(CType ptr) { return ptr; }
  static CppType to_cpp_type(CType ptr)
  {
    // We copy/paste the widget wrap() implementation here,
    // because we can not use a specific ltw8::wrap(T_Impl) overload here,
    // because that would be "dependent", and g++ 3.4 does not allow that.
    // The specific ltw8::wrap() overloads don't do anything special anyway.
    GObject* cobj = (GObject*)ptr;
    return dynamic_cast<CppType>(ltw8::wrap_auto(cobj, false /* take_copy */));
  }

  static void release_c_type(CType ptr)
  {
    GLIBMM_DEBUG_UNREFERENCE(nullptr, ptr);
    g_object_unref(ptr);
  }
};

// This confuse the SUN Forte compiler, so we ifdef it out:
#ifdef GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS

/** Partial specialization for pointers to const GtkObject instances.
 * @ingroup ContHelpers
 */
template <class T>
struct TypeTraits<const T*>
{
  using CppType = const T*;
  using CType = const typename T::BaseObjectType*;
  using CTypeNonConst = typename T::BaseObjectType*;

  static CType to_c_type(CppType ptr) { return ltw8::unwrap(ptr); }
  static CType to_c_type(CType ptr) { return ptr; }
  static CppType to_cpp_type(CType ptr)
  {
    // We copy/paste the widget wrap() implementation here,
    // because we can not use a specific ltw8::wrap(T_Impl) overload here,
    // because that would be "dependent", and g++ 3.4 does not allow that.
    // The specific ltw8::wrap() overloads don't do anything special anyway.
    GObject* cobj = (GObject*)const_cast<CTypeNonConst>(ptr);
    return dynamic_cast<CppType>(ltw8::wrap_auto(cobj, false /* take_copy */));
  }

  static void release_c_type(CType ptr)
  {
    GLIBMM_DEBUG_UNREFERENCE(nullptr, ptr);
    g_object_unref(const_cast<CTypeNonConst>(ptr));
  }
};
#endif // GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS

/** Partial specialization for pointers to GObject instances.
 * @ingroup ContHelpers
 * The C++ type is always a ltw8::RefPtr<>.
 */
template <class T>
struct TypeTraits<ltw8::RefPtr<T>>
{
  using CppType = ltw8::RefPtr<T>;
  using CType = typename T::BaseObjectType*;
  using CTypeNonConst = typename T::BaseObjectType*;

  static CType to_c_type(const CppType& ptr) { return ltw8::unwrap(ptr); }
  static CType to_c_type(CType ptr) { return ptr; }
  static CppType to_cpp_type(CType ptr)
  {
    // return ltw8::wrap(ptr, true);

    // We copy/paste the wrap() implementation here,
    // because we can not use a specific ltw8::wrap(CType) overload here,
    // because that would be "dependent", and g++ 3.4 does not allow that.
    // The specific ltw8::wrap() overloads don't do anything special anyway.
    GObject* cobj = (GObject*)(ptr);
    return ltw8::RefPtr<T>(dynamic_cast<T*>(ltw8::wrap_auto(cobj, true /* take_copy */)));
    // We use dynamic_cast<> in case of multiple inheritance.
  }

  static void release_c_type(CType ptr)
  {
    GLIBMM_DEBUG_UNREFERENCE(nullptr, ptr);
    g_object_unref(ptr);
  }
};

// This confuse the SUN Forte compiler, so we ifdef it out:
#ifdef GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS

/** Partial specialization for pointers to const GObject instances.
 * @ingroup ContHelpers
 * The C++ type is always a ltw8::RefPtr<>.
 */
template <class T>
struct TypeTraits<ltw8::RefPtr<const T>>
{
  using CppType = ltw8::RefPtr<const T>;
  using CType = const typename T::BaseObjectType*;
  using CTypeNonConst = typename T::BaseObjectType*;

  static CType to_c_type(const CppType& ptr) { return ltw8::unwrap(ptr); }
  static CType to_c_type(CType ptr) { return ptr; }
  static CppType to_cpp_type(CType ptr)
  {
    // return ltw8::wrap(ptr, true);

    // We copy/paste the wrap() implementation here,
    // because we can not use a specific ltw8::wrap(CType) overload here,
    // because that would be "dependent", and g++ 3.4 does not allow that.
    // The specific ltw8::wrap() overloads don't do anything special anyway.
    GObject* cobj = (GObject*)const_cast<CTypeNonConst>(ptr);
    return ltw8::RefPtr<const T>(
      dynamic_cast<const T*>(ltw8::wrap_auto(cobj, true /* take_copy */)));
    // We use dynamic_cast<> in case of multiple inheritance.
  }

  static void release_c_type(CType ptr)
  {
    GLIBMM_DEBUG_UNREFERENCE(nullptr, ptr);
    g_object_unref(const_cast<CTypeNonConst>(ptr));
  }
};

#endif // GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS

#endif // GLIBMM_CAN_USE_DYNAMIC_CAST_IN_UNUSED_TEMPLATE_WITHOUT_DEFINITION

/** Specialization for UTF-8 strings.
 * @ingroup ContHelpers
 * When converting from C++ to C, ltw8::ustring will be accepted as well as
 * std::string and 'const char*'.  However, when converting to the C++ side,
 * the output type cannot be 'const char*'.
 */
template <>
struct TypeTraits<ltw8::ustring>
{
  using CppType = ltw8::ustring;
  using CType = const char*;
  using CTypeNonConst = char*;

  static CType to_c_type(const ltw8::ustring& str) { return str.c_str(); }
  static CType to_c_type(const std::string& str) { return str.c_str(); }
  static CType to_c_type(CType str) { return str; }

  static CppType to_cpp_type(CType str) { return (str) ? ltw8::ustring(str) : ltw8::ustring(); }

  static void release_c_type(CType str) { g_free(const_cast<CTypeNonConst>(str)); }
};

/** Specialization for std::string.
 * @ingroup ContHelpers
 * When converting from C++ to C, std::string will be accepted as well as
 * 'const char*'.  However, when converting to the C++ side, the output type
 * cannot be 'const char*'.
 */
template <>
struct TypeTraits<std::string>
{
  using CppType = std::string;
  using CType = const char*;
  using CTypeNonConst = char*;

  static CType to_c_type(const std::string& str) { return str.c_str(); }
  static CType to_c_type(const ltw8::ustring& str) { return str.c_str(); }
  static CType to_c_type(CType str) { return str; }

  static CppType to_cpp_type(CType str) { return (str) ? std::string(str) : std::string(); }

  static void release_c_type(CType str) { g_free(const_cast<CTypeNonConst>(str)); }
};

/** Specialization for bool.
 * @ingroup ContHelpers
 */
template <>
struct TypeTraits<bool>
{
  using CppType = bool;
  using CType = gboolean;
  using CTypeNonConst = gboolean;

  static CType to_c_type(CppType item) { return static_cast<CType>(item); }
  static CType to_c_type(CType item) { return item; }
  static CppType to_cpp_type(CType item) { return (item != 0); }
  static void release_c_type(CType) {}
};

/** Specialization for ltw8::VariantBase.
 * @ingroup ContHelpers
 */
template <>
struct TypeTraits<ltw8::VariantBase>
{
  using CppType = ltw8::VariantBase;
  using CType = GVariant*;
  using CTypeNonConst = GVariant*;

  static CType to_c_type(const ltw8::VariantBase& v) { return const_cast<CTypeNonConst>(v.gobj()); }

  static CType to_c_type(CType v) { return v; }

  static CppType to_cpp_type(CType v) { return ltw8::VariantBase(v, true); }

  static void release_c_type(CType v) { g_variant_unref(const_cast<CTypeNonConst>(v)); }
};

/** Specialization for ltw8::VariantContainerBase.
 * @ingroup ContHelpers
 */
template <>
struct TypeTraits<ltw8::VariantContainerBase>
{
  using CppType = ltw8::VariantContainerBase;
  using CType = GVariant*;
  using CTypeNonConst = GVariant*;

  static CType to_c_type(const ltw8::VariantContainerBase& v)
  {
    return const_cast<CTypeNonConst>(v.gobj());
  }

  static CType to_c_type(CType v) { return v; }

  static CppType to_cpp_type(CType v) { return ltw8::VariantContainerBase(v, true); }

  static void release_c_type(CType v) { g_variant_unref(const_cast<CTypeNonConst>(v)); }
};

#ifndef GLIBMM_HAVE_TEMPLATE_SEQUENCE_CTORS

/* The STL containers in Sun's libCstd don't support templated sequence
 * constructors, for "backward compatibility" reasons.  This helper function
 * is used in the ContainerHandle -> STL-container conversion workarounds.
 */
template <class Cont, class In>
void
fill_container(Cont& container, In pbegin, In pend)
{
  for (; pbegin != pend; ++pbegin)
    container.emplace_back(*pbegin);
}

#endif /* GLIBMM_HAVE_TEMPLATE_SEQUENCE_CTORS */
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Container_Helpers

} // namespace ltw8

#endif /* _GLIBMM_CONTAINERHANDLE_SHARED_H */
