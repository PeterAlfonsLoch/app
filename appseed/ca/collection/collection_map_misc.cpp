#include "framework.h"

map_ptr_to_ptr::map_ptr_to_ptr(int_ptr nBlockSize) :
   ::collection::map < void *, void *, void *, void *>(nBlockSize)
{
}

map_ptr_to_word::map_ptr_to_word(int_ptr nBlockSize) :
   ::collection::map < void *, void *, WORD, WORD >(nBlockSize)
{
}


map_string_to_ob::map_string_to_ob(int_ptr nBlockSize) :
   ::collection::map < string, const string &, ::gen::object *, ::gen::object * >(nBlockSize)
{
}

map_string_to_ptr::map_string_to_ptr(int_ptr nBlockSize) :
   ::collection::map < string, const string &, void *, void * >(nBlockSize)
{
}

map_word_to_ob::map_word_to_ob(int_ptr nBlockSize) :
   ::collection::map < WORD, WORD, ::gen::object *, ::gen::object * >(nBlockSize)
{
}

map_word_to_ptr::map_word_to_ptr(int_ptr nBlockSize) :
   ::collection::map < WORD, WORD, void *, void * >(nBlockSize)
{
}

