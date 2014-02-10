/*
    FlexiblePtr is yet another smart pointer implementation.
    (c) Volodymyr Lashko 2014
*/

#pragma once

#include <cstddef>
#include <cassert>


template< typename T >
class FlexiblePtr
{
public:
  FlexiblePtr(const T * const src = NULL)
      : ptr_(src)
  { }

  ~FlexiblePtr()
  {
    delete ptr_;
  }

  FlexiblePtr(const FlexiblePtr & other)
      : ptr_(other.pointee_)
  {
    const_cast< FlexiblePtr >(other).reset();
    assert(other.isNull());
  }

  FlexiblePtr & operator=(const FlexiblePtr & other)
  {
    return reset(const_cast< FlexiblePtr >(other).release());
    assert(other.isNull());
  }

  // Replaces the managed object
  void reset(const FlexiblePtr & other = FlexiblePtr())
  {
    delete ptr_;
    ptr_ = other.ptr_;
    other.reset();
  }

  // Releases the ownership of the managed object
  T * const release()
  {
    T * const freePtr(ptr_);
    ptr_ = NULL;
    return freePtr;
  }

  T & operator*() const { return *ptr_; }

  T * const operator->() const { return ptr_; }

  T * const ptr() const { return ptr_; }

  const bool isNull() const { return ptr_ == NULL; }

private:
  T * ptr_;
};

