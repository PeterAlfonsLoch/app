#include "framework.h"

map_ptr_to_ptr::map_ptr_to_ptr(::ca::application * papp, ::count nBlockSize) :
   ::ca::ca(papp),
   map < void *, void *, void *, void *> (papp, nBlockSize)
{
}

map_ptr_to_word::map_ptr_to_word(::ca::application * papp, ::count nBlockSize) :
   ::ca::ca(papp),
   map < void *, void *, WORD, WORD > (papp, nBlockSize)
{
}


map_string_to_ob::map_string_to_ob(::ca::application * papp, ::count nBlockSize) :
   ::ca::ca(papp),
   map < string, const string &, ::ca::object *, ::ca::object * > (papp, nBlockSize)
{
}

map_string_to_ptr::map_string_to_ptr(::ca::application * papp, ::count nBlockSize) :
   ::ca::ca(papp),
   map < string, const string &, void *, void * > (papp, nBlockSize)
{
}

map_word_to_ob::map_word_to_ob(::ca::application * papp, ::count nBlockSize) :
   ::ca::ca(papp),
   map < WORD, WORD, ::ca::object *, ::ca::object * > (papp, nBlockSize)
{
}

map_word_to_ptr::map_word_to_ptr(::ca::application * papp, ::count nBlockSize) :
   ::ca::ca(papp),
   map < WORD, WORD, void *, void * > (papp, nBlockSize)
{
}

