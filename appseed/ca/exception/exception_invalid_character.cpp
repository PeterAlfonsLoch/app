#include "framework.h"


invalid_character::invalid_character(const char * pszMessage) :
   simple_exception(pszMessage)
{

}


invalid_character::~invalid_character()
{

}

