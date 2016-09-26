// -*- c++ -*-
// Generated by gmmproc 2.46.4 -- DO NOT MODIFY!
#ifndef _GLIBMM_THREADS_H
#define _GLIBMM_THREADS_H

////////#include <glibmmconfig.h>


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


#include <glib.h>
#include <error.h>
#include <sigc++/sigc++.h>
#include <string>
#include <cstddef>

namespace ltw8
{

namespace Threads
{
//The GMMPROC_EXTRA_NAMESPACE() macro is a hint to generate_wrap_init.pl to put it in the Threads sub-namespace


/** @defgroup Threads Threads
 * %Thread abstraction; including threads, different mutexes,
 * conditions and thread private data.
 * @{
 */

enum NotLock { NOT_LOCK };
enum TryLock { TRY_LOCK };

class Mutex;
class RecMutex;
class RWLock;

/** %Exception class for thread-related errors.
 */
class ThreadError : public ltw8::Error
{
public:
  /**  @var Code AGAIN
   * A thread couldn't be created due to resource
   * shortage. Try again later.
   * 
   *  @enum Code
   * 
   * Possible errors of thread related functions.
   */
  enum Code
  {
    AGAIN
  };

  ThreadError(Code error_code, const ltw8::ustring& error_message);
  explicit ThreadError(GError* gobject);
  Code code() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:

  static void throw_func(GError* gobject);

  friend void wrap_init(); // uses throw_func()

  #endif //DOXYGEN_SHOULD_SKIP_THIS
};


/** Represents a running thread.
 * An instance of this class can only be obtained with create(), self(),
 * or wrap(GThread*).  It's not possible to delete a Thread object.
 * You must call join() to avoid a memory leak.
 *
 * @note g_thread_exit() is not wrapped, because that function exits a thread
 * without any cleanup.  That's especially dangerous in C++ code, since the
 * destructors of automatic objects won't be invoked.  Instead, you can throw
 * a Threads::Thread::Exit exception, which will be caught by the internal thread
 * entry function.
 *
 * @note The thread entry slot doesn't have the void* return value that a
 * GThreadFunc has.  If you want to return any data from your thread,
 * you can pass an additional output argument to the thread's entry slot.
 */
class Thread
{
public:

  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  class Exit;

  //See http://bugzilla.gnome.org/show_bug.cgi?id=512348 about the sigc::trackable issue.
  // TODO: At the next ABI break, consider changing const sigc::slot<void>& slot
  // to const std::function<void()>& func, if it can be assumed that all supported
  // compilers understand the C++11 template class std::function<>.
  /** Creates a new thread.
   * You can wait for this thread's termination by calling join().
   *
   * The new thread executes the function or method @a slot points to.  You can
   * pass additional arguments using sigc::bind().  If the thread was created
   * successfully, it is returned, otherwise a Threads::ThreadError exception is thrown.
   *
   * Because sigc::trackable is not thread-safe, if the slot represents a
   * non-static class method and is created by sigc::mem_fun(), the class concerned
   * should not derive from sigc::trackable. You can use, say, boost::bind() or,
   * in C++11, std::bind() or a C++11 lambda expression instead of sigc::mem_fun().
   *
   * @param slot A slot to execute in the new thread.
   * @return The new Thread* on success.
   * @throw ltw8::Threads::ThreadError
   */
  static Thread* create(const sigc::slot<void>& slot);

  // TODO: At next ABI break, remove the single parameter create
  //       method and default name to std::string()

  /** Creates a new named thread.
   * You can wait for this thread's termination by calling join().
   *
   * The new thread executes the function or method @a slot points to.  You can
   * pass additional arguments using sigc::bind().  If the thread was created
   * successfully, it is returned, otherwise a Threads::ThreadError exception is thrown.
   *
   * Because sigc::trackable is not thread-safe, if the slot represents a
   * non-static class method and is created by sigc::mem_fun(), the class concerned
   * should not derive from sigc::trackable. You can use, say, boost::bind() or,
   * in C++11, std::bind() or a C++11 lambda expression instead of sigc::mem_fun().
   *
   * The @a name can be useful for discriminating threads in a debugger.
   * It is not used for other purposes and does not have to be unique.
   * Some systems restrict the length of @a name to 16 bytes.
   *
   * @param slot A slot to execute in the new thread.
   * @param name A name for the new thread.
   * @return The new Thread* on success.
   * @throw ltw8::Threads::ThreadError
   *
   * @newin{2,36}
   */
  static Thread* create(const sigc::slot<void>& slot, const std::string& name);

  /** Returns the Thread* corresponding to the calling thread.
   * @return The current thread.
   */
  static Thread* self();

  /** Waits until the thread finishes.
   * Waits until the thread finishes, i.e. the slot, as given to create(),
   * returns or g_thread_exit() is called by the thread.  (Calling
   * g_thread_exit() in a C++ program should be avoided.)  All resources of
   * the thread including the ltw8::Threads::Thread object are released.
   */
  void join();

  /** Gives way to other threads waiting to be scheduled.
   * This function is often used as a method to make busy wait less evil.  But
   * in most cases, you will encounter, there are better methods to do that.
   * So in general you shouldn't use this function.
   */
  static void yield();

  GThread*       gobj();
  const GThread* gobj() const;

private:
  // ltw8::Thread can neither be constructed nor deleted.
  Thread();
  void operator delete(void*, std::size_t);
};

/** %Exception class used to exit from a thread.
 * @code
 * throw ltw8::Threads::Thread::Exit();
 * @endcode
 * Write this if you want to exit from a thread created by Threads::Thread::create().
 * Of course you must make sure not to catch Threads::Thread::Exit by accident, i.e.
 * when using <tt>catch(...)</tt> somewhere in your code.
 */
class Thread::Exit
{};

/** A C++ wrapper for the C object.
 *
 * @param gobject The C instance.
 * @return The C++ wrapper.
 *
 * @relates ltw8::Threads::Thread
 */
Thread* wrap(GThread* gobject);

/** Represents a mutex (mutual exclusion).
 * It can be used to protect data against shared access.  Try to use
 * Mutex::Lock instead of calling lock() and unlock() directly&nbsp;--
 * it will make your life much easier.
 *
 * @note ltw8::Threads::Mutex is not recursive, i.e. a thread will deadlock, if it
 * already has locked the mutex while calling lock().  Use ltw8::Threads::RecMutex
 * instead, if you need recursive mutexes.
 */
class Mutex
{
public:
  class Lock;

  Mutex();

  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  ~Mutex();

  /** Locks the mutex.
   * If mutex is already locked by another thread, the current thread will
   * block until mutex is unlocked by the other thread.
   * @see Mutex::Lock
   */
  void lock();

  /** Tries to lock the mutex.
   * If the mutex is already locked by another thread, it immediately returns
   * @c false.  Otherwise it locks the mutex and returns @c true.
   * @return Whether the mutex could be locked.
   * @see Mutex::Lock
   */
  bool trylock();

  /** Unlocks the mutex.
   * If another thread is blocked in a lock() call for this mutex, it will be
   * woken and can lock the mutex itself.
   * @see Mutex::Lock
   */
  void unlock();

  GMutex* gobj() { return &gobject_; }

private:
  GMutex gobject_;
};

/** Utility class for exception-safe mutex locking.
 * @par Usage example:
 * @code
 * {
 *   ltw8::Threads::Mutex::Lock lock(mutex); // calls mutex.lock()
 *   do_something();
 * } // the destructor calls mutex.unlock()
 * @endcode
 * As you can see, the compiler takes care of the unlocking.  This is not
 * only exception-safe but also much less error-prone.  You could even
 * <tt>return</tt> while still holding the lock and it will be released
 * properly.
 */
class Mutex::Lock
{
public:
  explicit inline Lock(Mutex& mutex);
  inline Lock(Mutex& mutex, NotLock);
  inline Lock(Mutex& mutex, TryLock);

  Lock(const Mutex::Lock&) = delete;
  Mutex::Lock& operator=(const Mutex::Lock&) = delete;

  inline ~Lock();

  inline void acquire();
  inline bool try_acquire();
  inline void release();
  inline bool locked() const;

private:
  Mutex&  mutex_;
  bool    locked_;
};

/** A C++ wrapper for the C object.
 * Do not use operator delete on the returned pointer. If the caller owns the
 * GMutex object, the caller must destroy it in the same way as if this function
 * had not been called.
 *
 * @param gobject The C instance.
 * @result The GMutex* cast to a ltw8::Threads::Mutex*.
 *
 * @relates ltw8::Threads::Mutex
 */
Mutex* wrap(GMutex* gobject);

/** This represents a recursive mutex.
 * It is similar to a Mutex with the difference
 * that it is possible to lock a RecMutex multiple times in the same
 * thread without deadlock. When doing so, care has to be taken to
 * unlock the recursive mutex as often as it has been locked.
 */
class RecMutex
{
public:
  class Lock;

  RecMutex();

  RecMutex(const RecMutex&) = delete;
  RecMutex& operator=(const RecMutex&) = delete;

  ~RecMutex();

  void lock();
  bool trylock();
  void unlock();

  GRecMutex* gobj() { return &gobject_; }

private:
  GRecMutex gobject_;
};

/** Utility class for exception-safe locking of recursive mutexes.
 */
class RecMutex::Lock
{
public:
  explicit inline Lock(RecMutex& mutex);
  inline Lock(RecMutex& mutex, NotLock);
  inline Lock(RecMutex& mutex, TryLock);

  Lock(const RecMutex::Lock&) = delete;
  RecMutex::Lock& operator=(const RecMutex::Lock&) = delete;

  inline ~Lock();

  inline void acquire();
  inline bool try_acquire();
  inline void release();
  inline bool locked() const;

private:
  RecMutex& mutex_;
  bool      locked_;
};

/** A C++ wrapper for the C object.
 * Do not use operator delete on the returned pointer. If the caller owns the
 * GRecMutex object, the caller must destroy it in the same way as if this function
 * had not been called.
 *
 * @param gobject The C instance.
 * @result The GRecMutex* cast to a ltw8::Threads::RecMutex*.
 *
 * @relates ltw8::Threads::RecMutex
 */
RecMutex* wrap(GRecMutex* gobject);

/** This represents a reader-writer lock.
 * It is similar to a Mutex in that it allows
 * multiple threads to coordinate access to a shared resource.
 *
 * The difference to a mutex is that a reader-writer lock discriminates
 * between read-only ('reader') and full ('writer') access. While only
 * one thread at a time is allowed write access (by holding the 'writer'
 * lock via writer_lock()), multiple threads can gain
 * simultaneous read-only access (by holding the 'reader' lock via
 * reader_lock()).
 */
class RWLock
{
public:
  class ReaderLock;
  class WriterLock;

  RWLock();

  RWLock(const RWLock&) = delete;
  RWLock& operator=(const RWLock&) = delete;

  ~RWLock();

  void reader_lock();
  bool reader_trylock();
  void reader_unlock();

  void writer_lock();
  bool writer_trylock();
  void writer_unlock();

  GRWLock* gobj() { return &gobject_; }

private:
  GRWLock gobject_;
};

/** Utility class for exception-safe locking of read/write locks.
 */
class RWLock::ReaderLock
{
public:
  explicit inline ReaderLock(RWLock& rwlock);
  inline ReaderLock(RWLock& rwlock, NotLock);
  inline ReaderLock(RWLock& rwlock, TryLock);

  ReaderLock(const RWLock::ReaderLock&) = delete;
  RWLock::ReaderLock& operator=(const RWLock::ReaderLock&) = delete;

  inline ~ReaderLock();

  inline void acquire();
  inline bool try_acquire();
  inline void release();
  inline bool locked() const;

private:
  RWLock& rwlock_;
  bool    locked_;
};

/** Utility class for exception-safe locking of read/write locks.
 */
class RWLock::WriterLock
{
public:
  explicit inline WriterLock(RWLock& rwlock);
  inline WriterLock(RWLock& rwlock, NotLock);
  inline WriterLock(RWLock& rwlock, TryLock);

  WriterLock(const RWLock::WriterLock&) = delete;
  RWLock::WriterLock& operator=(const RWLock::WriterLock&) = delete;

  inline ~WriterLock();

  inline void acquire();
  inline bool try_acquire();
  inline void release();
  inline bool locked() const;

private:
  RWLock& rwlock_;
  bool    locked_;
};

/** An opaque data structure to represent a condition.
 * A @a Cond is an object that threads can block on, if they find a certain
 * condition to be false. If other threads change the state of this condition
 * they can signal the @a Cond, such that the waiting thread is woken up.
 * @par Usage example:
 * @code
 * ltw8::Threads::Cond  data_cond;
 * ltw8::Threads::Mutex data_mutex;
 * void* current_data = nullptr;
 *
 * void push_data(void* data)
 * {
 *   ltw8::Threads::Mutex::Lock lock(data_mutex);
 *
 *   current_data = data;
 *   data_cond.signal();
 * }
 *
 * void* pop_data()
 * {
 *   ltw8::Threads::Mutex::Lock lock(data_mutex);
 *
 *   while (!current_data)
 *     data_cond.wait(data_mutex);
 *
 *   void* const data = current_data;
 *   current_data = nullptr;
 *
 *   return data;
 * }
 * @endcode
 */
class Cond
{
public:
  Cond();

  Cond(const Cond&) = delete;
  Cond& operator=(const Cond&) = delete;

  ~Cond();

  /** If threads are waiting for this @a Cond, exactly one of them is woken up.
   * It is good practice to hold the same lock as the waiting thread, while calling
   * this method, though not required.
   */
  void signal();

  /** If threads are waiting for this @a Cond, all of them are woken up.
   * It is good practice to hold the same lock as the waiting threads, while calling
   * this method, though not required.
   */
  void broadcast();

  /** Waits until this thread is woken up on this @a Cond.
   * The mutex is unlocked before falling asleep and locked again before resuming.
   *
   * @param mutex A @a Mutex that is currently locked.
   *
   * @note It is important to use the @a wait() and @a wait_until() methods
   * only inside a loop, which checks for the condition to be true as it is not
   * guaranteed that the waiting thread will find it fulfilled, even if the signaling
   * thread left the condition in that state. This is because another thread can have
   * altered the condition, before the waiting thread got the chance to be woken up,
   * even if the condition itself is protected by a @a Mutex.
   */
  void wait(Mutex& mutex);

  /** Waits until this thread is woken up on this @a Cond, but not longer
   * than until the time specified by @a end_time.
   * The mutex is unlocked before falling asleep and locked again before resuming.
   *
   * @par Usage example:
   * Extending the example presented in the documentation of class Cond.
   * @code
   * void* pop_data_timed()
   * {
   *   ltw8::Threads::Mutex::Lock lock(data_mutex);
   *
   *   // Wait at most 5 seconds.
   *   const gint64 end_time = g_get_monotonic_time() + 5 * G_TIME_SPAN_SECOND;
   *   while (!current_data)
   *     if (!data_cond.wait_until(data_mutex, end_time)
   *       return 0; // timeout
   *
   *   void* const data = current_data;
   *   current_data = nullptr;
   *
   *   return data;
   * }
   * @endcode
   * The end time is calculated once, before entering the loop, and reused.
   * This is the motivation behind the use of absolute time. If a relative time
   * of 5 seconds were passed directly to the call and a spurious wakeup
   * occurred, the program would have to start over waiting again, which would
   * lead to a total wait time of more than 5 seconds.
   *
   * @param mutex A @a Mutex that is currently locked.
   * @param end_time The monotonic time to wait until, in microseconds.
   *                 See g_get_monotonic_time().
   * @return <tt>true</tt> if the condition variable was signalled (or in the case
   *         of a spurious wakeup), <tt>false</tt> if @a end_time has passed.
   *
   * @note It is important to use the @a wait() and @a wait_until() methods
   * only inside a loop, which checks for the condition to be true as it is not
   * guaranteed that the waiting thread will find it fulfilled, even if the signaling
   * thread left the condition in that state. This is because another thread can have
   * altered the condition, before the waiting thread got the chance to be woken up,
   * even if the condition itself is protected by a @a Mutex.
   */
  bool wait_until(Mutex& mutex, gint64 end_time);

  GCond* gobj() { return &gobject_; }

private:
  GCond gobject_;
};

/** Thread-local data pointer.
 *
 * It is recommended that all instances of this class are statically allocated.
 * The first time an instance is used (get(), set() or replace() is called)
 * glib allocates a scarce OS resource that cannot be deallocated.
 */
template <class T>
class Private
{
public:
  Private(const Private<T>&) = delete;
  Private<T>& operator=(const Private<T>&) = delete;

  typedef void (*DestructorFunc) (void*);

  /** Deletes static_cast<T*>(data)
   */
  static void delete_ptr(void* data);

  /** Constructor.
   *
   * @param destructor_func Function pointer, or 0. If @a destructor_func is not 0
   * and the stored data pointer is not 0, this function is called when replace()
   * is called and when the thread exits.
   */
  explicit inline Private(DestructorFunc destructor_func = &Private<T>::delete_ptr);

  /** Gets the pointer stored in the calling thread.
   *
   * @return If no value has yet been set in this thread, 0 is returned.
   */
  inline T* get();

  /** Sets the pointer in the calling thread without calling <tt>destructor_func()</tt>.
   */
  inline void set(T* data);

  /** Sets the pointer in the calling thread and calls <tt>destructor_func()</tt>.
   * If a function pointer (and not 0) was specified in the constructor, and
   * the stored data pointer before the call to replace() is not 0, then
   * <tt>destructor_func()</tt> is called with this old pointer value.
   *
   * @newin{2,32}
   */
  inline void replace(T* data);

  GPrivate* gobj() { return gobject_; }

private:
  GPrivate gobject_;
};

/** @} group Threads */

/*! A glibmm thread example.
 * @example thread/thread.cc
 */


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/***************************************************************************/
/*  inline implementation                                                  */
/***************************************************************************/

/**** ltw8::Threads::Mutex::Lock *******************************************/

inline
Mutex::Lock::Lock(Mutex& mutex)
:
  mutex_  (mutex),
  locked_ (true)
{
  mutex_.lock();
}

inline
Mutex::Lock::Lock(Mutex& mutex, NotLock)
:
  mutex_  (mutex),
  locked_ (false)
{}

inline
Mutex::Lock::Lock(Mutex& mutex, TryLock)
:
  mutex_  (mutex),
  locked_ (mutex.trylock())
{}

inline
Mutex::Lock::~Lock()
{
  if(locked_)
    mutex_.unlock();
}

inline
void Mutex::Lock::acquire()
{
  mutex_.lock();
  locked_ = true;
}

inline
bool Mutex::Lock::try_acquire()
{
  locked_ = mutex_.trylock();
  return locked_;
}

inline
void Mutex::Lock::release()
{
  mutex_.unlock();
  locked_ = false;
}

inline
bool Mutex::Lock::locked() const
{
  return locked_;
}


/**** ltw8::Threads::RecMutex::Lock ****************************************/

inline
RecMutex::Lock::Lock(RecMutex& mutex)
:
  mutex_  (mutex),
  locked_ (true)
{
  mutex_.lock();
}

inline
RecMutex::Lock::Lock(RecMutex& mutex, NotLock)
:
  mutex_  (mutex),
  locked_ (false)
{}

inline
RecMutex::Lock::Lock(RecMutex& mutex, TryLock)
:
  mutex_  (mutex),
  locked_ (mutex.trylock())
{}

inline
RecMutex::Lock::~Lock()
{
  if(locked_)
    mutex_.unlock();
}

inline
void RecMutex::Lock::acquire()
{
  mutex_.lock();
  locked_ = true;
}

inline
bool RecMutex::Lock::try_acquire()
{
  locked_ = mutex_.trylock();
  return locked_;
}

inline
void RecMutex::Lock::release()
{
  mutex_.unlock();
  locked_ = false;
}

inline
bool RecMutex::Lock::locked() const
{
  return locked_;
}


/**** ltw8::Threads::RWLock::ReaderLock ************************************/

inline
RWLock::ReaderLock::ReaderLock(RWLock& rwlock)
:
  rwlock_ (rwlock),
  locked_ (true)
{
  rwlock_.reader_lock();
}

inline
RWLock::ReaderLock::ReaderLock(RWLock& rwlock, NotLock)
:
  rwlock_ (rwlock),
  locked_ (false)
{}

inline
RWLock::ReaderLock::ReaderLock(RWLock& rwlock, TryLock)
:
  rwlock_ (rwlock),
  locked_ (rwlock.reader_trylock())
{}

inline
RWLock::ReaderLock::~ReaderLock()
{
  if(locked_)
    rwlock_.reader_unlock();
}

inline
void RWLock::ReaderLock::acquire()
{
  rwlock_.reader_lock();
  locked_ = true;
}

inline
bool RWLock::ReaderLock::try_acquire()
{
  locked_ = rwlock_.reader_trylock();
  return locked_;
}

inline
void RWLock::ReaderLock::release()
{
  rwlock_.reader_unlock();
  locked_ = false;
}

inline
bool RWLock::ReaderLock::locked() const
{
  return locked_;
}


/**** ltw8::Threads::RWLock::WriterLock ************************************/

inline
RWLock::WriterLock::WriterLock(RWLock& rwlock)
:
  rwlock_ (rwlock),
  locked_ (true)
{
  rwlock_.writer_lock();
}

inline
RWLock::WriterLock::WriterLock(RWLock& rwlock, NotLock)
:
  rwlock_ (rwlock),
  locked_ (false)
{}

inline
RWLock::WriterLock::WriterLock(RWLock& rwlock, TryLock)
:
  rwlock_ (rwlock),
  locked_ (rwlock.writer_trylock())
{}

inline
RWLock::WriterLock::~WriterLock()
{
  if(locked_)
    rwlock_.writer_unlock();
}

inline
void RWLock::WriterLock::acquire()
{
  rwlock_.writer_lock();
  locked_ = true;
}

inline
bool RWLock::WriterLock::try_acquire()
{
  locked_ = rwlock_.writer_trylock();
  return locked_;
}

inline
void RWLock::WriterLock::release()
{
  rwlock_.writer_unlock();
  locked_ = false;
}

inline
bool RWLock::WriterLock::locked() const
{
  return locked_;
}

/**** ltw8::Threads::Private<T> ********************************************/

// static
template <class T>
void Private<T>::delete_ptr(void* data)
{
  delete static_cast<T*>(data);
}

template <class T> inline
Private<T>::Private(typename Private<T>::DestructorFunc destructor_func)
{
  // gobject_ = G_PRIVATE_INIT(destructor_func);
  // does not compile with --enable-warnings=fatal.
  // GPrivate is a struct, and G_PRIVATE_INIT is an initializer of type { ... }.
  // G_PRIVATE_INIT can be used only in initializations.
  const GPrivate temp = G_PRIVATE_INIT(destructor_func);
  gobject_ = temp;
}

template <class T> inline
T* Private<T>::get()
{
  return static_cast<T*>(g_private_get(&gobject_));
}

template <class T> inline
void Private<T>::set(T* data)
{
  g_private_set(&gobject_, data);
}

template <class T> inline
void Private<T>::replace(T* data)
{
  g_private_replace(&gobject_, data);
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} //namespace Threads

} // namespace ltw8


#endif /* _GLIBMM_THREADS_H */

