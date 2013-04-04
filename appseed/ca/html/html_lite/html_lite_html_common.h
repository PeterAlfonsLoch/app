#pragma once


//  UTILITY MACROS
//
// @author Gurmeet S. Kochar


/*
  
  SAFE_POINTER_DELETE
  Deletes the specified pointer, if non-null, and sets 
  it to ::null() after deletion.
 
  @param p pointer to delete
 
  @since Mar 08, 2004
  @author Gurmeet S. Kochar

 */

#define SAFE_DELETE_POINTER(_P) \
(void)(_P != ::null() ? delete _P, _P = ::null() : 0) \

