#include "framework.h"


namespace ca
{

   data_container::data_container(::ca::application * papp) :
      ca(papp)
   {
   }
   
   data_container::~data_container()
   {
   }

   bool data_container::set_data(::ca::data * pdata)
   {
      m_spdata = pdata;
      return true;
   }
      
   data * data_container::get_data() const
   {
      return m_spdata;
   }

   bool data_container::is_data_in_use() const
   {
      return m_spdata->is_in_use();
   }

   void data_container::on_update_data(int iHint)
   {
      UNREFERENCED_PARAMETER(iHint);
   }


} // namespace ca



