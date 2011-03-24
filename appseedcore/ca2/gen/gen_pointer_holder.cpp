#include "StdAfx.h"

raw_pointer::raw_pointer(::ca::application * papp) :
   ca(papp)
{
   m_pobject = NULL;
}

raw_pointer::raw_pointer(const raw_pointer & holder) :
   ::ca::ca(holder.get_app())
{
   m_pobject = holder.m_pobject;
}

raw_pointer::raw_pointer(::ca::object * pobject) :
   ::ca::ca(pobject != NULL ? pobject->get_app() : NULL)
{
   m_pobject = pobject;
}

