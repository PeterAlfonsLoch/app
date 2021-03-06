//#include "framework.h"

map_ptr_to_ptr::map_ptr_to_ptr(::aura::application * papp, ::count nBlockSize) :
   object(papp),
   map < void *, void *, void *, void *> (papp, nBlockSize)
{
}

map_ptr_to_word::map_ptr_to_word(::aura::application * papp, ::count nBlockSize) :
   object(papp),
   map < void *, void *, WORD, WORD > (papp, nBlockSize)
{
}


map_string_to_ob::map_string_to_ob(::aura::application * papp, ::count nBlockSize) :
   object(papp),
   map < string, const string &, object *, object * > (papp, nBlockSize)
{
}

map_string_to_ptr::map_string_to_ptr(::aura::application * papp, ::count nBlockSize) :
   object(papp),
   map < string, const string &, void *, void * > (papp, nBlockSize)
{
}

map_word_to_ob::map_word_to_ob(::aura::application * papp, ::count nBlockSize) :
   object(papp),
   map < WORD, WORD, object *, object * > (papp, nBlockSize)
{
}

map_word_to_ptr::map_word_to_ptr(::aura::application * papp, ::count nBlockSize) :
   object(papp),
   map < WORD, WORD, void *, void * > (papp, nBlockSize)
{
}

