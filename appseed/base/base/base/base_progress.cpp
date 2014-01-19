#include "framework.h"


void progress_listener::on_progress(double dRate)
{

}


int_progress::int_progress()
{

   m_plistener          = NULL;
   m_dProgressStart     = 0.0;
   m_dProgressEnd       = 1.0;

}


int_progress::~int_progress()
{

   m_plistener          = NULL;

}


void int_progress::trace_progress(int64_t iStep)
{

   m_scalar = iStep;

}

void int_progress::trace_progress()
{

   if (m_plistener != NULL)
   {

      m_plistener->on_progress(m_dProgressStart + (m_dProgressEnd - m_dProgressStart) * m_scalar.rate());

   }

}

void int_progress::progress_step()
{

   m_scalar++;

   trace_progress();

}



void int_progress::on_set_scalar(int_scalar_source * psource, e_scalar escalar, int64_t iValue)
{

   if (m_scalar.m_psource == psource)
   {
    
      if (m_scalar.m_escalar == escalar)
      {

         trace_progress();

      }
      else
      {
      }

   }

}