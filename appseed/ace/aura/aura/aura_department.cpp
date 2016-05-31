//#include "framework.h"

namespace aura
{



   department::department(application * papp):
      object(papp)
   {

   }


   department::~department()
   {

   }


   // designed to be in constructors, so should
   // not contain advanced initialization as the
   // papp application pointer may be incompletely
   // initialized specially its virtual functions.
   void department::construct(::aura::application * papp)
   {

      set_app(papp);

   }


   void department::connect_to_application_signal()
   {

      m_pauraapp->m_psignal->connect(this,&department::on_signal);

   }


   bool department::process_initialize()
   {

      return true;

   }


   bool department::initialize()
   {

      return true;

   }


   bool department::initialize1()
   {

      return true;

   }


   bool department::initialize2()
   {

      return true;

   }


   bool department::initialize3()
   {

      return true;

   }


   bool department::initialize_instance()
   {

      return true;

   }


   bool department::finalize()
   {

      return true;

   }


   int32_t department::exit_instance()
   {

      return 0;

   }

   void department::on_signal(signal_details * pobj)
   {

      SCAST_PTR(::aura::application_signal_details,papplicationsignal,pobj);

      try
      {
         if(papplicationsignal->m_esignal == ::aura::application_signal_process_initialize)
         {
            papplicationsignal->m_bOk = process_initialize();
         }
         else if(papplicationsignal->m_esignal == ::aura::application_signal_initialize)
         {
            papplicationsignal->m_bOk = initialize();
         }
         else if(papplicationsignal->m_esignal == ::aura::application_signal_initialize1)
         {
            papplicationsignal->m_bOk = initialize1();
         }
         else if(papplicationsignal->m_esignal == ::aura::application_signal_initialize2)
         {
            papplicationsignal->m_bOk = initialize2();
         }
         else if(papplicationsignal->m_esignal == ::aura::application_signal_initialize3)
         {
            papplicationsignal->m_bOk = initialize3();
         }
         //         else if(papplicationsignal->m_esignal == ::aura::application_signal_initialize_instance)
         //       {
         //        papplicationsignal->m_bOk = initialize();
         //   }
         else if(papplicationsignal->m_esignal == ::aura::application_signal_finalize)
         {
            papplicationsignal->m_bOk = finalize();
         }
      }
      catch(...)
      {
         papplicationsignal->m_bOk = false;
      }

   }







} // namespace aura


