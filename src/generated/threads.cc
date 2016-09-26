// Generated by gmmproc 2.46.4 -- DO NOT MODIFY!

// Don't let glibmm.h include thread.h. Pretend that it's already included.
// glib.h can then be included with G_DISABLE_DEPRECATED defined, and
// the compiler can react if deprecated glib functions are used.
#define _GLIBMM_THREAD_H
 

#include <glibmm.h>

#include <threads.h>
#include <private/threads_p.h>


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

#include <exceptionhandler.h>
#include <glib.h>

/* Why reinterpret_cast<Thread*>(gobject) is needed:
 *
 * A Thread instance is in fact always a GThread instance.
 * Unfortunately, GThread cannot be a member of Thread,
 * because it is an opaque struct. Also, the C interface does not provide
 * any hooks to install a destroy notification handler, thus we cannot
 * wrap it dynamically either.
 *
 * The cast works because Thread does not have any member data, and
 * it is impossible to derive from it. This is ensured by not implementing
 * the (private) default constructor.
 * This trick is used also in classes declared as _CLASS_OPAQUE_REFCOUNTED.
 */

namespace
{

extern "C"
{

static void* call_thread_entry_slot(void* data)
{
  const auto slot = reinterpret_cast<sigc::slot_base*>(data);

  try
  {
    // Recreate the specific slot.
    (*static_cast<sigc::slot<void>*>(slot))();
  }
  catch (ltw8::Threads::Thread::Exit&)
  {
    // Just exit from the thread.  The Threads::Thread::Exit exception
    // is our sane C++ replacement of g_thread_exit().
  }
  catch (...)
  {
    ltw8::exception_handlers_invoke();
  }

  delete slot;
  return 0;
}

} //extern "C"

} // anonymous namespace


namespace ltw8
{

namespace Threads
{

/**** ltw8::Threads::Thread ************************************************/

// static
Thread* Thread::create(const sigc::slot<void>& slot, const std::string& name)
{
  // Make a copy of slot on the heap.
  const auto slot_copy = new sigc::slot<void>(slot);

  GError* error = nullptr;
  auto thread = g_thread_try_new(name.empty() ? 0 : name.c_str(),
    &call_thread_entry_slot, slot_copy, &error);

  if (error)
  {
    delete slot_copy;
    ltw8::Error::throw_exception(error);
  }
  if (!thread)
  {
    delete slot_copy;
  }
  return reinterpret_cast<Thread*>(thread);
}

// static
Thread* Thread::create(const sigc::slot<void>& slot)
{
  return create(slot, std::string());
}

// static
Thread* Thread::self()
{
  return reinterpret_cast<Thread*>(g_thread_self());
}

void Thread::join()
{
  g_thread_join(reinterpret_cast<GThread*>(this));
}

// static
void Thread::yield()
{
  g_thread_yield();
}

GThread* Thread::gobj()
{
  return reinterpret_cast<GThread*>(this);
}

const GThread* Thread::gobj() const
{
  return reinterpret_cast<const GThread*>(this);
}

Thread* wrap(GThread* gobject)
{
  return reinterpret_cast<Thread*>(gobject);
}


/**** ltw8::Threads::Mutex *************************************************/

Mutex::Mutex()
{
  g_mutex_init(&gobject_);
}

Mutex::~Mutex()
{
  g_mutex_clear(&gobject_);
}

void Mutex::lock()
{
  g_mutex_lock(&gobject_);
}

bool Mutex::trylock()
{
  return g_mutex_trylock(&gobject_);
}

void Mutex::unlock()
{
  g_mutex_unlock(&gobject_);
}

Mutex* wrap(GMutex* gobject)
{
  return reinterpret_cast<Mutex*>(gobject);
}

/**** ltw8::Threads::RecMutex **********************************************/

RecMutex::RecMutex()
{
  g_rec_mutex_init(&gobject_);
}

RecMutex::~RecMutex()
{
  g_rec_mutex_clear(&gobject_);
}

void RecMutex::lock()
{
  g_rec_mutex_lock(&gobject_);
}

bool RecMutex::trylock()
{
  return g_rec_mutex_trylock(&gobject_);
}

void RecMutex::unlock()
{
  g_rec_mutex_unlock(&gobject_);
}

RecMutex* wrap(GRecMutex* gobject)
{
  return reinterpret_cast<RecMutex*>(gobject);
}

/**** ltw8::Threads::RWLock ************************************************/

void RWLock::reader_lock()
{
  g_rw_lock_reader_lock(&gobject_);
}

bool RWLock::reader_trylock()
{
  return g_rw_lock_reader_trylock(&gobject_);
}

void RWLock::reader_unlock()
{
  g_rw_lock_reader_unlock(&gobject_);
}

void RWLock::writer_lock()
{
  g_rw_lock_writer_lock(&gobject_);
}

bool RWLock::writer_trylock()
{
  return g_rw_lock_writer_trylock(&gobject_);
}

void RWLock::writer_unlock()
{
  g_rw_lock_writer_unlock(&gobject_);
}

RWLock::RWLock()
{
  g_rw_lock_init(&gobject_);
}

RWLock::~RWLock()
{
  g_rw_lock_clear(&gobject_);
}


/**** ltw8::Threads::Cond **************************************************/

Cond::Cond()
{
  g_cond_init(&gobject_);
}

Cond::~Cond()
{
  g_cond_clear(&gobject_);
}

void Cond::signal()
{
  g_cond_signal(&gobject_);
}

void Cond::broadcast()
{
  g_cond_broadcast(&gobject_);
}

void Cond::wait(Mutex& mutex)
{
  g_cond_wait(&gobject_, mutex.gobj());
}

bool Cond::wait_until(Mutex& mutex, gint64 end_time)
{
  return g_cond_wait_until(&gobject_, mutex.gobj(), end_time);
}

} // namespace Threads

} // namespace ltw8


namespace
{
} // anonymous namespace


ltw8::Threads::ThreadError::ThreadError(ltw8::Threads::ThreadError::Code error_code, const ltw8::ustring& error_message)
:
  ltw8::Error (G_THREAD_ERROR, error_code, error_message)
{}

ltw8::Threads::ThreadError::ThreadError(GError* gobject)
:
  ltw8::Error (gobject)
{}

ltw8::Threads::ThreadError::Code ltw8::Threads::ThreadError::code() const
{
  return static_cast<Code>(ltw8::Error::code());
}

void ltw8::Threads::ThreadError::throw_func(GError* gobject)
{
  throw ltw8::Threads::ThreadError(gobject);
}


