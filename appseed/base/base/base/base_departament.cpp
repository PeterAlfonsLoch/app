#include "framework.h"


base_departament::base_departament(::base::application * papp) :
   element(papp)
{

}


base_departament::~base_departament()
{

}


// designed to be in constructors, so should
// not contain advanced initialization as the
// papp application pointer may be incompletely
// initialized specially its virtual functions.
void base_departament::construct(sp(::base::application) papp)
{

   set_app(papp);

}


void base_departament::connect_to_application_signal()
{

   m_pbaseapp->m_psignal->connect(this, &::base_departament::on_signal);

}


bool base_departament::process_initialize()
{

   return true;

}


bool base_departament::initialize()
{

   return true;

}


bool base_departament::initialize1()
{

   return true;

}


bool base_departament::initialize2()
{

   return true;

}


bool base_departament::initialize3()
{

   return true;

}


bool base_departament::initialize_instance()
{

   return true;

}


bool base_departament::finalize()
{

   return true;

}


int32_t base_departament::exit_instance()
{

   return 0;

}

void base_departament::on_signal(signal_details * pobj)
{

   SCAST_PTR(application_signal_details, papplicationsignal, pobj);

   try
   {
      if(papplicationsignal->m_esignal == application_signal_process_initialize)
      {
         papplicationsignal->m_bOk = process_initialize();
      }
      else if(papplicationsignal->m_esignal == application_signal_initialize)
      {
         papplicationsignal->m_bOk = initialize();
      }
      else if(papplicationsignal->m_esignal == application_signal_initialize1)
      {
         papplicationsignal->m_bOk = initialize1();
      }
      else if(papplicationsignal->m_esignal == application_signal_initialize2)
      {
         papplicationsignal->m_bOk = initialize2();
      }
      else if(papplicationsignal->m_esignal == application_signal_initialize3)
      {
         papplicationsignal->m_bOk = initialize3();
      }
      //         else if(papplicationsignal->m_esignal == application_signal_initialize_instance)
      //       {
      //        papplicationsignal->m_bOk = initialize();
      //   }
      else if(papplicationsignal->m_esignal == application_signal_finalize)
      {
         papplicationsignal->m_bOk = finalize();
      }
   }
   catch(...)
   {
      papplicationsignal->m_bOk = false;
   }

}





