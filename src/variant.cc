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

#include <variant.h>
#include <utility.h>
#include <glib.h>
#include <iostream>

namespace ltw8
{

VariantBase::VariantBase(GVariant* castitem, bool make_a_copy /* = false */)
{
  if (castitem)
  {
    if (g_variant_is_floating(castitem))
    {
      g_variant_ref_sink(castitem);
    }
    if (make_a_copy)
    {
      g_variant_ref(castitem);
    }
  }

  gobject_ = castitem;
}

void
VariantBase::get_normal_form(VariantBase& result) const
{
  GVariant* const g_value = g_variant_get_normal_form(const_cast<GVariant*>(gobj()));

  // The C function never returns NULL, according to its documenation,
  // so we don't need a bool return value.
  result.init(g_value); // g_value is already referenced.
}

void
VariantBase::byteswap(VariantBase& result) const
{
  GVariant* const g_value = g_variant_byteswap(const_cast<GVariant*>(gobj()));
  result.init(g_value); // g_value is already referenced.
}

bool
VariantBase::is_castable_to(const VariantType& supertype) const
{
  const std::string subtype_string = get_type_string();
  const std::string supertype_string = supertype.get_string();

  // The following code is similar to g_variant_type_is_subtype_of(), with
  // these differences:
  // - Both types are assumed to be definite types (no indefinite types,
  //   no 'r', '?' or '*').
  // - VARIANT_TYPE_OBJECT_PATH (o) and VARIANT_TYPE_SIGNATURE (g) can be cast to
  //   VARIANT_TYPE_STRING (s), (Variant<ltw8::ustring>::variant_type()).
  // - VARIANT_TYPE_STRING (s), VARIANT_TYPE_OBJECT_PATH (o) and
  //   VARIANT_TYPE_SIGNATURE (g) can be cast to VARIANT_TYPE_BYTESTRING (ay),
  //   (Variant<std::string>::variant_type()).
  // - VARIANT_TYPE_HANDLE (h) can be cast to VARIANT_TYPE_INT32 (i),
  //   (Variant<gint32>::variant_type()).

  std::size_t subtype_index = 0;
  std::size_t supertype_index = 0;
  const std::size_t supertype_size = supertype_string.size();
  while (supertype_index < supertype_size)
  {
    const char supertype_char = supertype_string[supertype_index++];
    const char subtype_char = subtype_string[subtype_index++];

    if (supertype_char == subtype_char)
      continue;

    switch (supertype_char)
    {
    case 's':
      if (!(subtype_char == 'o' || subtype_char == 'g'))
        return false;
      break;

    case 'a':
      if (!(supertype_string[supertype_index] == 'y' &&
            (subtype_char == 's' || subtype_char == 'o' || subtype_char == 'g')))
        return false;
      supertype_index++;
      break;

    case 'i':
      if (!(subtype_char == 'h'))
        return false;
      break;

    default:
      return false;
    }
  }
  return true;
}

VariantStringBase::VariantStringBase() : VariantBase()
{
}

VariantStringBase::VariantStringBase(GVariant* castitem, bool take_a_reference)
: VariantBase(castitem, take_a_reference)
{
}

// static
void
VariantStringBase::create_object_path(VariantStringBase& output, const std::string& object_path)
{
  GVariant* result = nullptr;
  result = g_variant_new_object_path(object_path.c_str());
  g_variant_ref_sink(result);
  output.init(result);
}

// static
void
VariantStringBase::create_signature(VariantStringBase& output, const std::string& signature)
{
  GVariant* result = nullptr;
  result = g_variant_new_signature(signature.c_str());
  g_variant_ref_sink(result);
  output.init(result);
}

VariantContainerBase::VariantContainerBase() : VariantBase()
{
}

VariantContainerBase::VariantContainerBase(GVariant* castitem, bool take_a_reference)
: VariantBase(castitem, take_a_reference)
{
}

// static
VariantContainerBase
VariantContainerBase::create_tuple(const std::vector<VariantBase>& children)
{
  using var_ptr = GVariant*;
  var_ptr* const var_array = new var_ptr[children.size()];

  for (std::vector<VariantBase>::size_type i = 0; i < children.size(); i++)
  {
    var_array[i] = const_cast<GVariant*>(children[i].gobj());
  }

  VariantContainerBase result =
    VariantContainerBase(g_variant_new_tuple(var_array, children.size()));
  delete[] var_array;
  return result;
}

// static
VariantContainerBase
VariantContainerBase::create_tuple(const VariantBase& child)
{
  std::vector<VariantBase> vec;
  vec.emplace_back(child);
  return create_tuple(vec);
}

// static
VariantContainerBase
VariantContainerBase::create_maybe(const VariantType& child_type, const VariantBase& child)
{
  GVariant* g_variant = g_variant_new_maybe(child_type.gobj(), const_cast<GVariant*>(child.gobj()));
  VariantContainerBase result = VariantContainerBase(g_variant);
  return result;
}

void
VariantContainerBase::get_child(VariantBase& child, gsize index) const
{
  if (index >= g_variant_n_children(gobject_))
    throw std::out_of_range("VariantContainerBase::get_child(): Index out of bounds.");

  GVariant* const gvariant = g_variant_get_child_value(gobject_, index);
  child.init(gvariant);
}

// VariantContainerBase has no method variant_type()
template <>
VariantContainerBase
VariantBase::cast_dynamic<VariantContainerBase>(const VariantBase& v) throw(std::bad_cast)
{
  if (!v.gobj())
  {
    return VariantContainerBase();
  }
  if (v.get_type().is_container())
  {
    return VariantContainerBase(const_cast<GVariant*>(v.gobj()), true);
  }
  else
  {
    // std::cerr << "vtype=" << v.get_type_string() << std::endl;
    throw std::bad_cast();
  }
}

bool
VariantContainerBase::get_maybe(VariantBase& maybe) const
{
  GVariant* const g_value = g_variant_get_maybe(const_cast<GVariant*>(gobj()));

  if (g_value)
  {
    maybe.init(g_value); // g_value is already referenced.
    return true;
  }
  else
    return false;
}

VariantIter
VariantContainerBase::get_iter(const VariantType& container_variant_type) const
{
  // Get the GVariantIter.
  // If the underlying GVariant can be cast to the type of the container,
  // use the actual type (which may differ from container_variant_type, if
  // the GVariant contains strings, object paths or DBus type signatures),
  // otherwise let g_variant_get() report what's wrong with the type.
  GVariantIter* g_iter = nullptr;
  g_variant_get(const_cast<GVariant*>(gobj()),
    is_castable_to(container_variant_type) ? get_type_string().c_str()
                                           : container_variant_type.get_string().c_str(),
    &g_iter);

  return VariantIter(g_iter);
}

/****************** Specializations ***********************************/

_DEPRECATE_IFDEF_START
VariantBase::operator const void*() const
{
  return gobj() ? GINT_TO_POINTER(1) : nullptr;
}
_DEPRECATE_IFDEF_END

VariantBase::operator bool() const
{
  return gobj() ? GINT_TO_POINTER(1) : nullptr;
}

void
VariantBase::init(const GVariant* cobject, bool take_a_reference)
{
  if (gobject_)
    g_variant_unref(gobject_);

  gobject_ = const_cast<GVariant*>(cobject);
  if (take_a_reference)
    g_variant_ref(gobject_);
}

/*--------------------Variant<VariantBase>---------------------*/

Variant<VariantBase>::Variant() : VariantContainerBase()
{
}

Variant<VariantBase>::Variant(GVariant* castitem, bool take_a_reference)
: VariantContainerBase(castitem, take_a_reference)
{
}

// static
const VariantType&
Variant<VariantBase>::variant_type()
{
  return VARIANT_TYPE_VARIANT;
}

Variant<VariantBase>
Variant<VariantBase>::create(const VariantBase& data)
{
  auto result = Variant<VariantBase>(g_variant_new_variant(const_cast<GVariant*>(data.gobj())));
  return result;
}

void
Variant<VariantBase>::get(VariantBase& variant) const
{
  GVariant* const gvariant = g_variant_get_variant(gobject_);
  variant.init(gvariant);
}

/*--------------------Variant<ltw8::ustring>---------------------*/

Variant<ltw8::ustring>::Variant() : VariantStringBase()
{
}

Variant<ltw8::ustring>::Variant(GVariant* castitem, bool take_a_reference)
: VariantStringBase(castitem, take_a_reference)
{
}

// static
const VariantType&
Variant<ltw8::ustring>::variant_type()
{
  return VARIANT_TYPE_STRING;
}

Variant<ltw8::ustring>
Variant<ltw8::ustring>::create(const ltw8::ustring& data)
{
  auto result = Variant<ltw8::ustring>(g_variant_new_string(data.c_str()));
  return result;
}

ltw8::ustring
Variant<ltw8::ustring>::get() const
{
  return convert_const_gchar_ptr_to_ustring(g_variant_get_string(gobject_, nullptr));
}

// Variant<ltw8::ustring> makes sense for multiple types.
// See http://library.gnome.org/devel/glib/unstable/glib-GVariant.html#g-variant-get-string
template <>
Variant<ltw8::ustring>
VariantBase::cast_dynamic<Variant<ltw8::ustring>>(const VariantBase& v) throw(std::bad_cast)
{
  if (!v.gobj())
  {
    return Variant<ltw8::ustring>();
  }

  const VariantType vtype = v.get_type();
  if (vtype.equal(VARIANT_TYPE_STRING) || vtype.equal(VARIANT_TYPE_OBJECT_PATH) ||
      vtype.equal(VARIANT_TYPE_SIGNATURE))
  {
    return Variant<ltw8::ustring>(const_cast<GVariant*>(v.gobj()), true);
  }
  else
  {
    // std::cerr << "vtype=" << v.get_type_string() << std::endl;
    throw std::bad_cast();
  }
}

/*--------------------Variant<std::string>---------------------*/

Variant<std::string>::Variant() : VariantStringBase()
{
}

Variant<std::string>::Variant(GVariant* castitem, bool take_a_reference)
: VariantStringBase(castitem, take_a_reference)
{
}

// static
const VariantType&
Variant<std::string>::variant_type()
{
  return VARIANT_TYPE_BYTESTRING;
}

Variant<std::string>
Variant<std::string>::create(const std::string& data)
{
  auto result = Variant<std::string>(g_variant_new_bytestring(data.c_str()));
  return result;
}

// Variant<std::string> makes sense for multiple types.
// See http://library.gnome.org/devel/glib/unstable/glib-GVariant.html#g-variant-get-string
template <>
Variant<std::string>
VariantBase::cast_dynamic<Variant<std::string>>(const VariantBase& v) throw(std::bad_cast)
{
  if (!v.gobj())
  {
    return Variant<std::string>();
  }

  const VariantType vtype = v.get_type();
  if (vtype.equal(VARIANT_TYPE_STRING) || vtype.equal(VARIANT_TYPE_BYTESTRING) ||
      vtype.equal(VARIANT_TYPE_OBJECT_PATH) || vtype.equal(VARIANT_TYPE_SIGNATURE))
  {
    return Variant<std::string>(const_cast<GVariant*>(v.gobj()), true);
  }
  else
  {
    // std::cerr << "vtype=" << v.get_type_string() << std::endl;
    throw std::bad_cast();
  }
}

std::string
Variant<std::string>::get() const
{
  const VariantType vtype = get_type();

  const char* pch = nullptr;
  if (vtype.equal(VARIANT_TYPE_BYTESTRING))
    pch = g_variant_get_bytestring(gobject_);
  else // g_variant_get_string() can handle strings, object paths, and signatures.
    pch = g_variant_get_string(gobject_, nullptr);

  return convert_const_gchar_ptr_to_stdstring(pch);
}

/*--------------------Variant< std::vector<ltw8::ustring> >---------------------*/

using type_vec_ustring = std::vector<ltw8::ustring>;

Variant<type_vec_ustring>::Variant() : VariantContainerBase()
{
}

Variant<type_vec_ustring>::Variant(GVariant* castitem, bool take_a_reference)
: VariantContainerBase(castitem, take_a_reference)
{
}

// static
const VariantType&
Variant<type_vec_ustring>::variant_type()
{
  return VARIANT_TYPE_STRING_ARRAY;
}

Variant<type_vec_ustring>
Variant<type_vec_ustring>::create(const type_vec_ustring& data)
{
  // Get the variant type of the elements.
  VariantType element_variant_type = Variant<ltw8::ustring>::variant_type();

  // Get the variant type of the array.
  VariantType array_variant_type = Variant<type_vec_ustring>::variant_type();

  // Create a GVariantBuilder to build the array.
  GVariantBuilder* builder = g_variant_builder_new(array_variant_type.gobj());

  // Add the elements of the vector into the builder.
  for (const auto& str : data)
  {
    g_variant_builder_add(builder, element_variant_type.get_string().c_str(), str.c_str());
  }

  // Create the variant using the builder.
  auto result =
    Variant<type_vec_ustring>(g_variant_new(array_variant_type.get_string().c_str(), builder));

  g_variant_builder_unref(builder);

  return result;
}

ltw8::ustring
Variant<type_vec_ustring>::get_child(gsize index) const
{
  if (index >= g_variant_n_children(const_cast<GVariant*>(gobj())))
    throw std::out_of_range(
      "Variant< std::vector<ltw8::ustring> >::get_child(): Index out of bounds.");

  GVariant* gvariant = g_variant_get_child_value(const_cast<GVariant*>(gobj()), index);

  return ltw8::Variant<ltw8::ustring>(gvariant).get();
}

type_vec_ustring
Variant<type_vec_ustring>::get() const
{
  // g_variant_get_strv() can be used only if the type is VARIANT_TYPE_STRING_ARRAY,
  // but the Variant can alternatively hold an array of object paths or DBus type signatures.
  type_vec_ustring result;

  gsize n_children = g_variant_n_children(const_cast<GVariant*>(gobj()));

  for (gsize i = 0; i < n_children; i++)
  {
    GVariant* gvariant = g_variant_get_child_value(const_cast<GVariant*>(gobj()), i);

    result.emplace_back(ltw8::Variant<ltw8::ustring>(gvariant).get());
  }

  return result;
}

VariantIter
Variant<type_vec_ustring>::get_iter() const
{
  return VariantContainerBase::get_iter(variant_type());
}

/*--------------------Variant< std::vector<std::string> >---------------------*/

using type_vec_string = std::vector<std::string>;

Variant<type_vec_string>::Variant() : VariantContainerBase()
{
}

Variant<type_vec_string>::Variant(GVariant* castitem, bool take_a_reference)
: VariantContainerBase(castitem, take_a_reference)
{
}

// static
const VariantType&
Variant<type_vec_string>::variant_type()
{
  return VARIANT_TYPE_BYTESTRING_ARRAY;
}

Variant<type_vec_string>
Variant<type_vec_string>::create(const type_vec_string& data)
{
  // Create a string array to add the strings of the vector to.
  char** str_array = g_new(char*, data.size() + 1);

  // Add the elements of the vector into the string array.
  for (type_vec_string::size_type i = 0; i < data.size(); i++)
  {
    str_array[i] = g_strdup(data[i].c_str());
  }

  // Terminate the string array.
  str_array[data.size()] = nullptr;

  // Create the variant using g_variant_new_bytestring_array() (passing the
  // newly constructed array.
  auto result = Variant<type_vec_string>(g_variant_new_bytestring_array(str_array, data.size()));

  g_strfreev(str_array);
  return result;
}

Variant<type_vec_string>
Variant<type_vec_string>::create_from_object_paths(const type_vec_string& data)
{
  // Create a string array to add the strings of the vector to.
  char** str_array = g_new(char*, data.size() + 1);

  // Add the elements of the vector into the string array.
  for (type_vec_string::size_type i = 0; i < data.size(); i++)
  {
    str_array[i] = g_strdup(data[i].c_str());
  }

  // Terminate the string array.
  str_array[data.size()] = nullptr;

  // Create the variant using g_variant_new_objv() (passing the
  // newly constructed array.
  auto result = Variant<type_vec_string>(g_variant_new_objv(str_array, data.size()));

  g_strfreev(str_array);
  return result;
}

std::string
Variant<type_vec_string>::get_child(gsize index) const
{
  if (index >= g_variant_n_children(const_cast<GVariant*>(gobj())))
    throw std::out_of_range(
      "Variant< std::vector<std::string> >::get_child(): Index out of bounds.");

  GVariant* gvariant = g_variant_get_child_value(const_cast<GVariant*>(gobj()), index);

  return ltw8::Variant<std::string>(gvariant).get();
}

type_vec_string
Variant<type_vec_string>::get() const
{
  // g_variant_get_bytestring_array() can be used only if the type is VARIANT_TYPE_BYTESTRING_ARRAY,
  // but the Variant can alternatively hold an array of strings, object paths or DBus type
  // signatures.
  type_vec_string result;

  gsize n_children = g_variant_n_children(const_cast<GVariant*>(gobj()));

  for (gsize i = 0; i < n_children; i++)
  {
    GVariant* gvariant = g_variant_get_child_value(const_cast<GVariant*>(gobj()), i);

    result.emplace_back(ltw8::Variant<std::string>(gvariant).get());
  }

  return result;
}

VariantIter
Variant<type_vec_string>::get_iter() const
{
  return VariantContainerBase::get_iter(variant_type());
}

} // namespace ltw8