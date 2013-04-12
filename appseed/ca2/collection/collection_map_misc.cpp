#include "framework.h"

map_ptr_to_ptr::map_ptr_to_ptr(int_ptr nBlockSize) :
   map < void *, void *, void *, void *>(nBlockSize)
{
}

map_ptr_to_word::map_ptr_to_word(int_ptr nBlockSize) :
   map < void *, void *, WORD, WORD >(nBlockSize)
{
}


map_string_to_ob::map_string_to_ob(int_ptr nBlockSize) :
   map < string, const string &, ::ca::object *, ::ca::object * >(nBlockSize)
{
}

map_string_to_ptr::map_string_to_ptr(int_ptr nBlockSize) :
   map < string, const string &, void *, void * >(nBlockSize)
{
}

map_word_to_ob::map_word_to_ob(int_ptr nBlockSize) :
   map < WORD, WORD, ::ca::object *, ::ca::object * >(nBlockSize)
{
}

map_word_to_ptr::map_word_to_ptr(int_ptr nBlockSize) :
   map < WORD, WORD, void *, void * >(nBlockSize)
{
}

