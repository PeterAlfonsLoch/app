#include "framework.h"


invalid_character::invalid_character(sp(::ca::application) papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage)
{

}


invalid_character::~invalid_character()
{

}

