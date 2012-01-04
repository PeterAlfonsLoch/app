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
         
         ::cube::cube * pcube                = new ::cube::cube();
         pcube->m_psystem                    = m_psystem;
         pcube->m_psession                   = m_psession;
         m_psystem->m_pcube                  = pcube;
         m_psystem->m_pcubeInterface         = pcube;

         pcube->directrix().consolidate(&m_psystem->directrix());

         if(!pcube->start_application(true, NULL))
            return false;

      }

      if(m_psession == NULL)
         return false;

      if(m_psession->m_pbergedge == NULL)
      {
         
         ::bergedge::bergedge * pbergedge    = new ::bergedge::bergedge();
         pbergedge->m_psystem                = m_psystem;
         pbergedge->m_psession               = m_psession;
         m_psession->m_pbergedge             = pbergedge;
         m_psession->m_pbergedgeInterface    = pbergedge;

         if(!pbergedge->start_application(true, NULL))
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

   bool application::is_cube()
   {
      return false;
   }


} //namespace cube


