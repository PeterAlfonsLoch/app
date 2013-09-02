#include "framework.h"


namespace ca2
{

   data_container::data_container()
   {
   }
   
   data_container::~data_container()
   {
   }

   bool data_container::set_data(::ca2::data * pdata)
   {
      m_spdata = pdata;
      return true;
   }
      
   data * data_container::get_data()
   {
      return m_spdata;
   }

   bool data_container::is_data_in_use() const
   {
      return m_spdata->is_in_use();
   }

   void data_container::on_update_data(int32_t iHint)
   {
      UNREFERENCED_PARAMETER(iHint);
   }


   data_container_base::data_container_base(sp(::application) papp)
   {
   }

   data_container_base::~data_container_base()
   {
   }


   bool data_container_base::add_data(::ca2::data * pdata)
   {
      
      for(index i = 0; i < m_spadata.get_count(); i++)
      {

         if(m_spadata.sp_at(i) == pdata)
            return true;

      }

      m_spadata.add(pdata);

      return true;

   }

   bool data_container_base::remove_data(::ca2::data * pdata)
   {

      ::count cRemove = 0;

      for(index i = 0; i < m_spadata.get_count();)
      {

         if(m_spadata.sp_at(i) == pdata)
         {
            m_spadata.remove_at(i);
            cRemove++;
         }
         else
         {
            i++;
         }

      }

      return cRemove > 0;

   }

   data * data_container_base::get_data(index i)
   {
      
      return m_spadata.sp_at(i);

   }

   ::count data_container_base::get_count() const
   {

      return m_spadata.get_count();

   }

   sync_object_ptra data_container_base::get_sync()
   {

      sync_object_ptra ptra;

      for(index i = 0; i < m_spadata.get_count(); i++)
      {

         ptra.add(m_spadata[i].data_mutex());

      }

      return ptra;

   }

} // namespace ca2



