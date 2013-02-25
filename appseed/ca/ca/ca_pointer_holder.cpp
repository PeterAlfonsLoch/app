#include "framework.h"


raw_pointer::raw_pointer(::ca::application * papp) :
   ::ca::ca(papp)
{

   m_pca = NULL;

}

raw_pointer::raw_pointer(const raw_pointer & holder) :
   ::ca::ca(holder.get_app())
{

   m_pca = holder.m_pca;

}

raw_pointer::raw_pointer(::ca::ca * pca) :
   ::ca::ca(pca != NULL ? pca->get_app() : NULL)
{

   m_pca = pca;

}

