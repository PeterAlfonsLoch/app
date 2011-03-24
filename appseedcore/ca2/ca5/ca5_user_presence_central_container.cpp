#include "StdAfx.h"

namespace ca5
{

   namespace user
   {

      presence_central_container::presence_central_container()
      {
         m_pcentral = NULL;
      }
      
      presence_central_container::~presence_central_container()
      {

      }

      bool presence_central_container::initialize_central_container(::ca::application * papp)
      {

         if(!System.is_licensed("user_presence", false))
         {
            TRACE("user presence not licensed for this user");
            return false;
         }
         else
         {
            TRACE("user presence is licensed for this user");
         }

         m_pcentral = new presence_central(get_app());

         if(m_pcentral == NULL)
            AfxThrowMemoryException();


         if(!m_pcentral->initialize())
         {
            delete m_pcentral;
            m_pcentral = NULL;
            return false;
         }

         return true;
      }

      bool presence_central_container::is_initialized()
      {

         if(m_pcentral == NULL)
            return false;

         return m_pcentral->is_initialized();

      }

   } // namespace user

} // namespace ca5