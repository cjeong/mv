/* @file stlutil.h
 *
 * utility functions for STL
 */
#ifndef MDW_UTIL_STL_H
#define MDW_UTIL_STL_H

#include <cstddef>  /* std::size_t */

namespace mdw {
namespace util {


/*
 * for arrays
 */

/* find where an array ends (for ending iterators); this returns a pointer 
   to the byte immediately after the end of an array */
template<class T, std::size_t N>
inline T *array_endof(T (&array)[N]) {
  return array + N;
}

/* find the length of an array */
template<class T, std::size_t N>
inline size_t array_lengthof(T (&array)[N]) {
  return N;
}
  
    
}
}

#endif /* MDW_UTIL_STL_H */
