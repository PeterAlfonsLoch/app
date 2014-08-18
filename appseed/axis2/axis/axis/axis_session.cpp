#include "framework.h"



namespace axis
{


   session::session(sp(::axis::application) papp) :
      element(papp)
   {

      m_pbaseapp        = this;

      m_pbasesession    = this;

      m_pcoreplatform   = NULL;


#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance = m_pbaseapp->m_hinstance;

      }

#endif


      m_bDrawCursor              = false;

      m_pbasesystem->m_basesessionptra.add_unique(this);


      

   }


   void session::construct(sp(::axis::application) papp, int iPhase)
   {

      if(iPhase == 0)
      {
         
         if(papp->is_system())
         {


         }
      }

   }

   session::~session()
   {

      m_pbasesystem->m_basesessionptra.remove(this);


   }


   bool session::is_session()
   {

      return true;

   }





   COLORREF session::get_default_color(uint64_t ui)
   {

      switch(ui)
      {
      case COLOR_3DFACE:
         return ARGB(127,192,192,184);
      case COLOR_WINDOW:
         return ARGB(127,255,255,255);
      case COLOR_3DLIGHT:
         return ARGB(127,218,218,210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127,238,238,230);
      case COLOR_3DSHADOW:
         return ARGB(127,138,138,130);
      case COLOR_3DDKSHADOW:
         return ARGB(127,84,84,77);
      default:
         break;
      }

      return ARGB(127,0,0,0);

   }








   bool session::process_initialize()
   {

      if(!::axis::application::process_initialize())
         return false;


      return true;

   }


   bool session::initialize1()
   {


      if(!::axis::application::initialize1())
         return false;


      return true;

   }


   bool session::initialize2()
   {

      if(!::axis::application::initialize2())
         return false;


      return true;

   }



   bool session::initialize_instance()
   {



      if(!::axis::application::initialize_instance())
         return false;


      return true;

   }


   bool session::initialize()
   {

      if(!::axis::application::initialize())
         return false;


      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;

      try
      {

         bOk = ::axis::application::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      return bOk;

   }


   int32_t session::exit_instance()
   {


      ::axis::application::exit_instance();

      return 0;

   }


   application_ptra & session::appptra()
   {

      return m_appptra;

   }




} // namespace axis
































