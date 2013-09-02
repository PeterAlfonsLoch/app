#include "framework.h"


namespace ca2
{


   base_edit::base_edit(sp(::application) papp) :
      element(papp)
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


} // namespace ca2



