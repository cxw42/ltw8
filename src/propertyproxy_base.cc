/* propertyproxy_base.h
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

#include <propertyproxy_base.h>

#include <signalproxy_connectionnode.h>
#include <object.h>
#include <private/object_p.h>
#include <utility> // For std::move()

namespace ltw8
{

// PropertyProxyConnectionNode implementation:

PropertyProxyConnectionNode::PropertyProxyConnectionNode(
  const sigc::slot_base& slot, GObject* gobject)
: SignalProxyConnectionNode(slot, gobject)
{
}

PropertyProxyConnectionNode::PropertyProxyConnectionNode(sigc::slot_base&& slot, GObject* gobject)
: SignalProxyConnectionNode(std::move(slot), gobject)
{
}

sigc::connection
PropertyProxyConnectionNode::connect_changed(const ltw8::ustring& property_name)
{
  // connect it to glib
  // 'this' will be passed as the data argument to the callback.
  const ltw8::ustring notify_signal_name = "notify::" + property_name;
  connection_id_ = g_signal_connect_data(object_, notify_signal_name.c_str(),
    (GCallback)(&PropertyProxyConnectionNode::callback), this,
    &PropertyProxyConnectionNode::destroy_notify_handler, G_CONNECT_AFTER);

  return sigc::connection(slot_);
}

void PropertyProxyConnectionNode::callback(GObject*, GParamSpec* pspec, gpointer data) // static
{
  if (pspec && data)
  {
    if (sigc::slot_base* const slot = SignalProxyBase::data_to_slot(data))
      (*static_cast<sigc::slot<void>*>(slot))();
  }
}

// SignalProxyProperty implementation:

SignalProxyProperty::SignalProxyProperty(ltw8::ObjectBase* obj, const gchar* property_name)
: SignalProxyBase(obj), property_name_(property_name)
{
}

SignalProxyProperty::~SignalProxyProperty() noexcept
{
}

sigc::connection
SignalProxyProperty::connect(const SlotType& slot)
{
  // Create a proxy to hold our connection info
  // This will be deleted by destroy_notify_handler.
  auto pConnectionNode = new PropertyProxyConnectionNode(slot, obj_->gobj());

  // connect it to glib
  // pConnectionNode will be passed as the data argument to the callback.
  return pConnectionNode->connect_changed(property_name_);
}

sigc::connection
SignalProxyProperty::connect(SlotType&& slot)
{
  // Create a proxy to hold our connection info
  // This will be deleted by destroy_notify_handler.
  auto pConnectionNode = new PropertyProxyConnectionNode(std::move(slot), obj_->gobj());

  // connect it to glib
  // pConnectionNode will be passed as the data argument to the callback.
  return pConnectionNode->connect_changed(property_name_);
}

// PropertyProxy_Base implementation:

PropertyProxy_Base::PropertyProxy_Base(ObjectBase* obj, const char* property_name)
: obj_(obj), property_name_(property_name)
{
}

PropertyProxy_Base::PropertyProxy_Base(const PropertyProxy_Base& other)
: obj_(other.obj_), property_name_(other.property_name_)
{
}

SignalProxyProperty
PropertyProxy_Base::signal_changed()
{
  return SignalProxyProperty(obj_, property_name_);
}

void
PropertyProxy_Base::set_property_(const ltw8::ValueBase& value)
{
  g_object_set_property(obj_->gobj(), property_name_, value.gobj());
}

void
PropertyProxy_Base::get_property_(ltw8::ValueBase& value) const
{
  g_object_get_property(obj_->gobj(), property_name_, value.gobj());
}

void
PropertyProxy_Base::reset_property_()
{
  // Get information about the parameter:
  const GParamSpec* const pParamSpec =
    g_object_class_find_property(G_OBJECT_GET_CLASS(obj_->gobj()), property_name_);

  g_return_if_fail(pParamSpec != nullptr);

  ltw8::ValueBase value;
  value.init(G_PARAM_SPEC_VALUE_TYPE(pParamSpec));

  // An explicit reset is not needed, because ValueBase:init()
  // has already initialized it to the default value for this type.
  // value.reset();

  g_object_set_property(obj_->gobj(), property_name_, value.gobj());
}

} // namespace ltw8