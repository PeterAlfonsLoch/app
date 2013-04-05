#include "framework.h"


raw_pointer::raw_pointer(::ca::applicationsp papp) :
   ::ca::ca(papp)
{

   m_pca = ::null();

}

raw_pointer::raw_pointer(const raw_pointer & holder) :
   ::ca::ca(holder.get_app())
{

   m_pca = holder.m_pca;

}

raw_pointer::raw_pointer(sp(::ca::ca) pca) :
   ::ca::ca(pca != ::null() ? pca->get_app() : ::null())
{

   m_pca = pca;

}

