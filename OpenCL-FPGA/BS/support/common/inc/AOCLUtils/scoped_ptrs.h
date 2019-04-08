// Copyright (C) 2013-2016 Altera Corporation, San Jose, California, USA. All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to
// whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// This agreement shall be governed in all respects by the laws of the State of California and
// by the laws of the United States of America.

// Scoped pointer definitions.

#ifndef AOCL_UTILS_SCOPED_PTRS_H
#define AOCL_UTILS_SCOPED_PTRS_H

namespace aocl_utils {

// Interface is essentially the combination of std::auto_ptr and boost's smart pointers,
// along with some small extensions (auto conversion to TYPE*).

// scoped_ptr: assumes pointer was allocated with operator new; destroys with operator delete
template<typename TYPE>
class scoped_ptr {
public:
  typedef scoped_ptr<TYPE> this_type;

  scoped_ptr() : m_ptr(NULL) {}
  scoped_ptr(TYPE *ptr) : m_ptr(ptr) {}
  ~scoped_ptr() { reset(); }

  TYPE *get() const { return m_ptr; }
  operator TYPE *() const { return m_ptr; }
  TYPE *operator ->() const { return m_ptr; }
  TYPE &operator *() const { return *m_ptr; }

  this_type &operator =(TYPE *ptr) { reset(ptr); return *this; }

  void reset(TYPE *ptr = NULL) { delete m_ptr; m_ptr = ptr; }
  TYPE *release() { TYPE *ptr = m_ptr; m_ptr = NULL; return ptr; }

private:
  TYPE *m_ptr;

  // noncopyable
  scoped_ptr(const this_type &);
  this_type &operator =(const this_type &);
};

// scoped_array: assumes pointer was allocated with operator new[]; destroys with operator delete[]
// Also supports allocation/reset with a number, which is the number of
// elements of type TYPE.
template<typename TYPE>
class scoped_array {
public:
  typedef scoped_array<TYPE> this_type;

  scoped_array() : m_ptr(NULL) {}
  scoped_array(TYPE *ptr) : m_ptr(NULL) { reset(ptr); }
  explicit scoped_array(size_t n) : m_ptr(NULL) { reset(n); }
  ~scoped_array() { reset(); }

  TYPE *get() const { return m_ptr; }
  operator TYPE *() const { return m_ptr; }
  TYPE *operator ->() const { return m_ptr; }
  TYPE &operator *() const { return *m_ptr; }
  TYPE &operator [](int index) const { return m_ptr[index]; }

  this_type &operator =(TYPE *ptr) { reset(ptr); return *this; }

  void reset(TYPE *ptr = NULL) { delete[] m_ptr; m_ptr = ptr; }
  void reset(size_t n) { reset(new TYPE[n]); }
  TYPE *release() { TYPE *ptr = m_ptr; m_ptr = NULL; return ptr; }

private:
  TYPE *m_ptr;

  // noncopyable
  scoped_array(const this_type &);
  this_type &operator =(const this_type &);
};

// scoped_aligned_ptr: assumes pointer was allocated with alignedMalloc; destroys with alignedFree
// Also supports allocation/reset with a number, which is the number of
// elements of type TYPE
template<typename TYPE>
class scoped_aligned_ptr {
public:
  typedef scoped_aligned_ptr<TYPE> this_type;

  scoped_aligned_ptr() : m_ptr(NULL) {}
  scoped_aligned_ptr(TYPE *ptr) : m_ptr(NULL) { reset(ptr); }
  explicit scoped_aligned_ptr(size_t n) : m_ptr(NULL) { reset(n); }
  ~scoped_aligned_ptr() { reset(); }

  TYPE *get() const { return m_ptr; }
  operator TYPE *() const { return m_ptr; }
  TYPE *operator ->() const { return m_ptr; }
  TYPE &operator *() const { return *m_ptr; }
  TYPE &operator [](int index) const { return m_ptr[index]; }

  this_type &operator =(TYPE *ptr) { reset(ptr); return *this; }

  void reset(TYPE *ptr = NULL) { if(m_ptr) alignedFree(m_ptr); m_ptr = ptr; }
  void reset(size_t n) { reset((TYPE*) alignedMalloc(sizeof(TYPE) * n)); }
  TYPE *release() { TYPE *ptr = m_ptr; m_ptr = NULL; return ptr; }

private:
  TYPE *m_ptr;

  // noncopyable
  scoped_aligned_ptr(const this_type &);
  this_type &operator =(const this_type &);
};

} // ns aocl_utils

#endif

