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
  FlexiblePtr(T * const src = NULL)
      : ptr_(src)
  { }

  ~FlexiblePtr()
  {
    delete ptr_;
  }

  FlexiblePtr(const FlexiblePtr & other)
      : ptr_(const_cast< FlexiblePtr & >(other).release())
  {
    assert(other.isNull());
  }

  FlexiblePtr & operator=(FlexiblePtr & other)
  {
    reset(other);
    assert(other.isNull() || this == &other);
    return *this;
  }

  // Replaces the managed object
  void reset(FlexiblePtr other = FlexiblePtr())
  {
    delete ptr_;
    ptr_ = other.release();
    assert(other.isNull());
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

