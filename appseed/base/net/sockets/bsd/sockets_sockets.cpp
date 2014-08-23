#include "framework.h"


namespace sockets
{


   sockets::sockets(::axis::application * papp) :
     element(papp),
     ::aura::departament(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_pajpbasesocketinit    = NULL;

   }

   sockets::~sockets()
   {
   }

   bool sockets::initialize1()
   {

      if(!::aura::departament::initialize1())
         return false;

      
      if(Application.is_system())
      {


         System.factory().creatable_small < ::file::memory_buffer > ();

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;

      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {
    
      if(Application.is_system())
      {
         if(m_pajpbasesocketinit != NULL)
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = NULL;
         }
      }

      return true;

   }



} // namespace karaoke


