#include "framework.h"


namespace data
{

   listener::listener(::aura::application * papp) :
      element(papp)
   {

   }


   listener::~listener()
   {

      listen(NULL, false);

   }


   bool listener::listen(data * pdata, bool bListen)
   {

      if(bListen)
      {

         if(pdata == NULL)
            return false;

         pdata->m_listenerptra.add_unique(this);

         m_dataptra.add_unique(pdata);

         return true;

      }
      else
      {

         if(pdata == NULL)
         {

            for(int32_t i = 0; i < m_dataptra.get_count(); i++)
            {

               m_dataptra[i]->m_listenerptra.remove(this);

            }

            m_dataptra.remove_all();

            return true;

         }

         pdata->m_listenerptra.remove(this);

         m_dataptra.remove(pdata);

         return true;

      }

   }


   void listener::on_update_data(data *, int32_t)
   {

   }



} // namespace data



