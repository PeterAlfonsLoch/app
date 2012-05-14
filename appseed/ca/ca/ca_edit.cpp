#include "framework.h"


namespace ca
{


   base_edit::base_edit(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp)
   {
   }

   base_edit::~base_edit()
   {
   }

   void base_edit::apply()
   {
      
      m_spdata->edit(this);
      on_apply();

   }

   void base_edit::on_apply()
   {
   }


} // namespace ca



