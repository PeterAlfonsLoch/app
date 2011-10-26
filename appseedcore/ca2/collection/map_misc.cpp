#include "StdAfx.h"

map_ptr_to_ptr::map_ptr_to_ptr(INT_PTR nBlockSize) :
   ::collection::map < void *, void *, void *, void *>(nBlockSize)
{
}

map_ptr_to_word::map_ptr_to_word(INT_PTR nBlockSize) :
   ::collection::map < void *, void *, WORD, WORD >(nBlockSize)
{
}


map_string_to_ob::map_string_to_ob(INT_PTR nBlockSize) :
   ::collection::map < string, string, ::radix::object *, ::radix::object * >(nBlockSize)
{
}

map_string_to_ptr::map_string_to_ptr(INT_PTR nBlockSize) :
   ::collection::map < string, string, void *, void * >(nBlockSize)
{
}

map_word_to_ob::map_word_to_ob(INT_PTR nBlockSize) :
   ::collection::map < WORD, WORD, ::radix::object *, ::radix::object * >(nBlockSize)
{
}

map_word_to_ptr::map_word_to_ptr(INT_PTR nBlockSize) :
   ::collection::map < WORD, WORD, void *, void * >(nBlockSize)
{
}

