#include "StdAfx.h"


namespace cubebase
{


   application::application()
   {
   }

   application::~application()
   {
   }

   ::ca::application * application::get_system()
   {
      return new application();
   }

   bool application::initialize1()
   {


      if(!::plane::application::initialize1())
         return false;

      if(m_psystem == NULL)
         return false;

      if(m_psystem->m_pcube == NULL)
      {
         
         ::cube::cube * pcube          = new ::cube::cube();
         pcube->m_papp                 = m_psystem;
         pcube->m_psystem              = m_psystem;
         pcube->m_psession             = m_psession;
         m_psystem->m_pcube            = pcube;
         m_psystem->m_pcubeInterface   = pcube;

         if(!pcube->start_application(true, NULL))
            return false;

      }

      return true;
   }
    
   bool application::initialize()
   {

      if(!::plane::application::initialize())
         return false;

      
      return true;

   }


} //namespace cube


