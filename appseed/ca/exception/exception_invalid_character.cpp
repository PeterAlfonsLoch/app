#include "framework.h"


invalid_character::invalid_character(::ca::applicationsp papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage)
{

}


invalid_character::~invalid_character()
{

}

