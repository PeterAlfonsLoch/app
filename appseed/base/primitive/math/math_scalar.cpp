#include "framework.h"


void double_scalar_source::listener::on_set_scalar(double_scalar_source * psource, e_scalar escalar, double dValue)
{

   UNREFERENCED_PARAMETER(psource);
   UNREFERENCED_PARAMETER(escalar);
   UNREFERENCED_PARAMETER(dValue);

}


bool double_scalar_source::set_scalar(e_scalar escalar, double d, bool bForce)
{

   if (!bForce)
   {

      if (!contains(escalar, d))
         return false;

   }

   on_set_scalar(escalar, d);

   if (m_plistener != NULL)
   {

      m_plistener->on_set_scalar(this, escalar, d);

   }

   return true;

}

bool double_scalar_source::constrain_scalar(e_scalar escalar, double & dValue)
{

   bool bConstrain;

   if ((bConstrain = constrain(escalar, dValue)))
   {

      if (dValue == get_scalar(escalar))
         return true;

   }

   bool bSet = set_scalar(escalar, dValue);

   return bConstrain && bSet;

}


double double_scalar_source::get_rate(e_scalar escalar, double dDefault)
{

   double dDenominator = get_scalar_maximum(escalar) - get_scalar_minimum(escalar);

   if (dDenominator == 0)
      return dDefault;

   double dNumerator = get_scalar(escalar) - get_scalar_minimum(escalar);

   return dNumerator / dDenominator; // aproximate value along iDenominator and iNumerator evaluation

}


bool double_scalar_source::contains(e_scalar escalar, double dValue)
{

   if (dValue < get_scalar_minimum(escalar))
      return false;

   if (dValue > get_scalar_maximum(escalar))
      return false;

   return true;

}

bool double_scalar_source::constrain(e_scalar escalar, double & dValue)
{

   double dLimit = get_scalar_minimum(escalar);

   if (dValue < dLimit)
   {

      dValue = dLimit;

      return true;

   }

   dLimit = get_scalar_maximum(escalar);

   if (dValue > dLimit)
   {

      dValue = dLimit;

      return true;

   }

   return false;

}



void double_scalar_source::on_set_scalar(e_scalar escalar, double d)
{

   UNREFERENCED_PARAMETER(escalar);

   UNREFERENCED_PARAMETER(d);

   // does nothing.

}

double double_scalar_source::get_scalar_minimum(e_scalar escalar)
{

   UNREFERENCED_PARAMETER(escalar);

   return 1.0; // by default

}

double double_scalar_source::get_scalar(e_scalar escalar)
{

   UNREFERENCED_PARAMETER(escalar);

   return 1.0; // by default

}

double double_scalar_source::get_scalar_maximum(e_scalar escalar)
{

   UNREFERENCED_PARAMETER(escalar);

   return 1.0; // by default

}

































void int_scalar_source::listener::on_set_scalar(int_scalar_source * psource, e_scalar escalar, int64_t iValue)
{

   UNREFERENCED_PARAMETER(psource);
   UNREFERENCED_PARAMETER(escalar);
   UNREFERENCED_PARAMETER(iValue);

}


bool int_scalar_source::set_scalar(e_scalar escalar, int64_t iValue, bool bForce)
{

   if (!bForce)
   {
      if (!contains(escalar, iValue))
         return false;
   }

   on_set_scalar(escalar, iValue);

   if (m_plistener != NULL)
   {
      
      m_plistener->on_set_scalar(this, escalar, iValue);

   }

   return true;

}

bool int_scalar_source::constrain_scalar(e_scalar escalar, int64_t & iValue)
{

   bool bConstrain;

   if((bConstrain = constrain(escalar, iValue)))
   {

      if (iValue == get_scalar(escalar))
         return true;

   }

   bool bSet = set_scalar(escalar, iValue);

   return bConstrain && bSet;

}

void int_scalar_source::increment_scalar(e_scalar escalar, int64_t iIncrement)
{
   
   set_scalar(escalar, get_scalar(escalar) + iIncrement);

}

bool int_scalar_source::contains(e_scalar escalar, int64_t iValue)
{

   if (iValue < get_scalar_minimum(escalar))
      return false;

   if (iValue > get_scalar_maximum(escalar))
      return false;

   return true;

}

bool int_scalar_source::constrain(e_scalar escalar, int64_t & iValue)
{

   int64_t iLimit = get_scalar_minimum(escalar);

   if (iValue < iLimit)
   {

      iValue = iLimit;

      return true;

   }

   iLimit = get_scalar_maximum(escalar);

   if (iValue > iLimit)
   {

      iValue = iLimit;

      return true;

   }

   return false;

}



void int_scalar_source::on_set_scalar(e_scalar escalar, int64_t iValue)
{
   
   UNREFERENCED_PARAMETER(escalar);
   
   UNREFERENCED_PARAMETER(iValue);

   // does nothing by default.

}

int64_t int_scalar_source::get_scalar_minimum(e_scalar escalar)
{
   
   UNREFERENCED_PARAMETER(escalar);

   return 0; // by default

}

int64_t int_scalar_source::get_scalar(e_scalar escalar)
{
   
   UNREFERENCED_PARAMETER(escalar);
   
   return 1; // by default

}

int64_t int_scalar_source::get_scalar_maximum(e_scalar escalar)
{
   
   UNREFERENCED_PARAMETER(escalar);
   
   return 1; // by default

}

double int_scalar_source::get_rate(e_scalar escalar, double dDefault)
{

   int64_t iDenominator = get_scalar_maximum(escalar) - get_scalar_minimum(escalar);

   if (iDenominator == 0)
      return dDefault;

   int64_t iNumerator = get_scalar(escalar) - get_scalar_minimum(escalar);

   return (double) iNumerator / (double) iDenominator; // aproximate value along iDenominator and iNumerator evaluation

}




double_scalar::double_scalar()
{

   m_psource   = NULL;
   m_escalar   = scalar_none;

}


void double_scalar::set(double dValue)
{

   if (m_psource == NULL || m_escalar == scalar_none)
      return;

   m_psource->set_scalar(m_escalar, dValue);

}


double double_scalar::get()
{

   if (m_psource == NULL || m_escalar == scalar_none)
      return 0.0;

   return m_psource->get_scalar(m_escalar);

}


double double_scalar::rate(double dDefault)
{

   if (m_psource == NULL || m_escalar == scalar_none)
      return dDefault;

   return m_psource->get_rate(m_escalar, dDefault);

}


double double_scalar::minimum()
{

   if (is_null())
      return 0;

   return m_psource->get_scalar_minimum(m_escalar);

}


double double_scalar::maximum()
{

   if (is_null())
      return 0;

   return m_psource->get_scalar_maximum(m_escalar);

}

int_scalar::int_scalar()
{

   m_psource = NULL;
   m_escalar = scalar_none;

}


void int_scalar::set(int64_t iValue)
{

   if (m_psource == NULL || m_escalar == scalar_none)
      return;

   m_psource->set_scalar(m_escalar, iValue);

}


int64_t int_scalar::get()
{

   if (m_psource == NULL || m_escalar == scalar_none)
      return 0;

   return m_psource->get_scalar(m_escalar);

}


double int_scalar::rate(double dDefault)
{
   
   if (m_psource == NULL || m_escalar == scalar_none)
      return dDefault;

   return m_psource->get_rate(m_escalar, dDefault);

}

int64_t int_scalar::minimum()
{
   
   if (is_null())
      return 0;

   return m_psource->get_scalar_minimum(m_escalar);

}


int64_t int_scalar::maximum()
{

   if (is_null())
      return 0;

   return m_psource->get_scalar_maximum(m_escalar);

}





