#include "framework.h"


invalid_character::invalid_character(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage)
{

}


invalid_character::~invalid_character()
{

}

