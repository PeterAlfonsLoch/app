#include "framework.h"


namespace ca
{


   section::section()
   {

   }


   section::~section()
   {

   }


   // designed to be in constructors, so should
   // not contain advanced initialization as the
   // papp application pointer may be incompletely
   // initialized specially its virtual functions.
   void section::construct(::ca::application * papp)
   {

      set_app(papp);

   }

   
   void section::connect_to_application_signal()
   {

      m_papp->m_psignal->connect(this, &::ca::section::on_signal);

   }


   bool section::process_initialize()
   {

      return true;

   }


   bool section::initialize()
   {

      return true;

   }


   bool section::initialize1()
   {

      return true;

   }


   bool section::initialize2()
   {

      return true;

   }


   bool section::initialize3()
   {

      return true;

   }


   bool section::initialize_instance()
   {

      return true;

   }


   bool section::finalize()
   {

      return true;

   }


   int32_t section::exit_instance()
   {

      return 0;

   }

   void section::on_signal(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::application_signal_object, papplicationsignal, pobj);

      try
      {
         if(papplicationsignal->m_esignal == ::ca::application_signal_process_initialize)
         {
            papplicationsignal->m_bOk = process_initialize();
         }
         else if(papplicationsignal->m_esignal == ::ca::application_signal_initialize)
         {
            papplicationsignal->m_bOk = initialize();
         }
         else if(papplicationsignal->m_esignal == ::ca::application_signal_initialize1)
         {
            papplicationsignal->m_bOk = initialize1();
         }
         else if(papplicationsignal->m_esignal == ::ca::application_signal_initialize2)
         {
            papplicationsignal->m_bOk = initialize2();
         }
         else if(papplicationsignal->m_esignal == ::ca::application_signal_initialize3)
         {
            papplicationsignal->m_bOk = initialize3();
         }
//         else if(papplicationsignal->m_esignal == ::ca::application_signal_initialize_instance)
  //       {
    //        papplicationsignal->m_bOk = initialize();
      //   }
         else if(papplicationsignal->m_esignal == ::ca::application_signal_finalize)
         {
            papplicationsignal->m_bOk = finalize();
         }
      }
      catch(...)
      {
         papplicationsignal->m_bOk = false;
      }

   }






} // namespace ca




