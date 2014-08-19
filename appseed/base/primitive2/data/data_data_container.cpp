#include "framework.h"


namespace data
{


   data_container::data_container()
   {
   }

   data_container::~data_container()
   {
   }

   bool data_container::set_data(::data::data * pdata)
   {
      m_spdata = pdata;
      return true;
   }

   data * data_container::get_data()
   {
      return m_spdata;
   }

   bool data_container::is_data_locked() const
   {
      return m_spdata->is_locked();
   }

   void data_container::on_update_data(int32_t iHint)
   {
      UNREFERENCED_PARAMETER(iHint);
   }


   data_container_base::data_container_base(sp(::axis::application) papp)
   {
   }

   data_container_base::~data_container_base()
   {
   }


   bool data_container_base::add_data(::data::data * pdata)
   {

      for(index i = 0; i < m_spadata.get_count(); i++)
      {

         if(m_spadata.sp_at(i) == pdata)
            return true;

      }

      m_spadata.add(pdata);

      return true;

   }

   bool data_container_base::remove_data(::data::data * pdata)
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

   bool data_container_base::is_empty() const
   {

      return m_spadata.is_empty();

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



} // namespace data




