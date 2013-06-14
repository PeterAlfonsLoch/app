#include "framework.h"

map_ptr_to_ptr::map_ptr_to_ptr(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < void *, void *, void *, void *> (papp, nBlockSize)
{
}

map_ptr_to_word::map_ptr_to_word(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < void *, void *, WORD, WORD > (papp, nBlockSize)
{
}


map_string_to_ob::map_string_to_ob(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < string, const string &, ::ca2::object *, ::ca2::object * > (papp, nBlockSize)
{
}

map_string_to_ptr::map_string_to_ptr(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < string, const string &, void *, void * > (papp, nBlockSize)
{
}

map_word_to_ob::map_word_to_ob(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < WORD, WORD, ::ca2::object *, ::ca2::object * > (papp, nBlockSize)
{
}

map_word_to_ptr::map_word_to_ptr(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < WORD, WORD, void *, void * > (papp, nBlockSize)
{
}

