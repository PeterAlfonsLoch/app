#include "framework.h"



document::document(::ca::application * papp) :
   ca(papp),
   ::ca::data_container_base(papp),
   ::ca::data_container(papp)
{

   m_documentptra.add(this);

}

document::~document()
{
}



bool document::set_data(::ca::data * pdata)
{

   if(m_spdata.is_set())
   {

      remove_data(m_spdata);

   }

   ::ca::data_container::set_data(pdata);

   if(pdata != ::null())
   {

      add_data(pdata);

   }

   return true;

}