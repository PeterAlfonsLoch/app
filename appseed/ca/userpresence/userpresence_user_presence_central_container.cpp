#include "framework.h"


namespace userpresence
{


   presence_central_container::presence_central_container()
   {
      m_pcentral = ::null();
      m_bUserPresenceFeatureRequired = false;
   }
      
   presence_central_container::~presence_central_container()
   {

   }

   bool presence_central_container::initialize_central_container(::ca::applicationsp papp)
   {

      if(!App(papp).is_licensed("user_presence", m_bUserPresenceFeatureRequired))
      {
         TRACE("user presence not licensed for this user");
         return false;
      }
      else
      {
         TRACE("user presence is licensed for this user");
      }

      m_pcentral = new presence_central(get_app());

      if(m_pcentral == ::null())
         throw memory_exception(get_app());


      if(!m_pcentral->initialize())
      {
         delete m_pcentral;
         m_pcentral = ::null();
         return false;
      }

      return true;
   }

   bool presence_central_container::is_initialized()
   {

      if(m_pcentral == ::null())
         return false;

      return m_pcentral->is_initialized();

   }

   bool presence_central_container::finalize_central_container()
   {

      if(!is_initialized())
      {
         return true;
      }

      if(m_pcentral == ::null())
         return true;

      m_pcentral->finalize();

      delete m_pcentral;

      m_pcentral = ::null();

      return true;
   }


} // namespace ca5



