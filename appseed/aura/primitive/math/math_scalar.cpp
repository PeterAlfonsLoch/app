#include "framework.h"


void double_scalar_source::listener::on_set_scalar(double_scalar_source * psource, e_scalar escalar, double dValue)
{

   UNREFERENCED_PARAMETER(psource);
   UNREFERENCED_PARAMETER(escalar);
   UNREFERENCED_PARAMETER(dValue);

}

double_scalar_source::double_scalar_source()
{

   m_plistener = NULL;

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

      double d = 0.0;

      get_scalar(escalar, d);

      if (dValue == d)
         return true;

   }

   bool bSet = set_scalar(escalar, dValue);

   return bConstrain && bSet;

}


double double_scalar_source::get_rate(e_scalar escalar, double dDefault)
{

   double dMax = 0.0;

   get_scalar_maximum(escalar, dMax);

   double dMin = 0.0;

   get_scalar_minimum(escalar, dMin);

   double dDenominator = dMax - dMin;

   if (dDenominator == 0)
      return dDefault;

   double dVal = 0.0;

   get_scalar(escalar, dVal);

   double dNumerator = dVal - dMin;

   return dNumerator / dDenominator; // aproximate value along iDenominator and iNumerator evaluation

}


bool double_scalar_source::contains(e_scalar escalar, double dValue)
{

   double dMin = 0.0;

   get_scalar_minimum(escalar, dMin);

   if (dValue < dMin)
      return false;

   double dMax = 0.0;

   get_scalar_maximum(escalar, dMax);

   if (dValue > dMax)
      return false;

   return true;

}

bool double_scalar_source::constrain(e_scalar escalar, double & dValue)
{

   double dMin = 0.0;
   
   get_scalar_minimum(escalar, dMin);

   if (dValue < dMin)
   {

      dValue = dMin;

      return true;

   }

   double dMax = 0.0;

   get_scalar_maximum(escalar, dMax);

   if (dValue > dMax)
   {

      dValue = dMax;

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

void double_scalar_source::get_scalar_minimum(e_scalar escalar, double & d)
{

   UNREFERENCED_PARAMETER(escalar);

   d = 1.0; // by default

}

void double_scalar_source::get_scalar(e_scalar escalar, double & d)
{

   UNREFERENCED_PARAMETER(escalar);

   d = 1.0; // by default

}

void double_scalar_source::get_scalar_maximum(e_scalar escalar, double & d)
{

   UNREFERENCED_PARAMETER(escalar);

   d = 1.0; // by default

}

































void int_scalar_source::listener::on_set_scalar(int_scalar_source * psource, e_scalar escalar, int64_t iValue)
{

   UNREFERENCED_PARAMETER(psource);
   UNREFERENCED_PARAMETER(escalar);
   UNREFERENCED_PARAMETER(iValue);

}


int_scalar_source::int_scalar_source()
{

   m_plistener = NULL;

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

      int64_t i = 0;

      get_scalar(escalar, i);

      if (iValue == i)
         return true;

   }

   bool bSet = set_scalar(escalar, iValue);

   return bConstrain && bSet;

}

void int_scalar_source::increment_scalar(e_scalar escalar, int64_t iIncrement)
{

   int64_t i = 0;

   get_scalar(escalar, i);
   
   set_scalar(escalar, i + iIncrement);

}

bool int_scalar_source::contains(e_scalar escalar, int64_t iValue)
{

   int64_t iMin = 0;

   get_scalar_minimum(escalar, iMin);

   if (iValue < iMin)
      return false;

   int64_t iMax = 0;

   get_scalar_maximum(escalar, iMax);

   if (iValue > iMax)
      return false;

   return true;

}

bool int_scalar_source::constrain(e_scalar escalar, int64_t & iValue)
{

   int64_t iMin = 0;

   get_scalar_minimum(escalar, iMin);

   if (iValue < iMin)
   {

      iValue = iMin;

      return true;

   }

   int64_t iMax = 0;

   get_scalar_maximum(escalar, iMax);

   if (iValue > iMax)
   {

      iValue = iMax;

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

void int_scalar_source::get_scalar_minimum(e_scalar escalar, int64_t & i)
{
   
   UNREFERENCED_PARAMETER(escalar);

   i = 0; // by default

}

void int_scalar_source::get_scalar(e_scalar escalar, int64_t & i)
{
   
   UNREFERENCED_PARAMETER(escalar);
   
   i = 1; // by default

}

void int_scalar_source::get_scalar_maximum(e_scalar escalar, int64_t & i)
{
   
   UNREFERENCED_PARAMETER(escalar);
   
   i = 1; // by default

}

double int_scalar_source::get_rate(e_scalar escalar, double dDefault)
{

   int64_t iMax = 0;

   get_scalar_maximum(escalar, iMax);

   int64_t iMin = 0;

   get_scalar_minimum(escalar, iMin);

   int64_t iDenominator = iMax - iMin;

   if (iDenominator == 0)
      return dDefault;

   int64_t iVal = 0;

   get_scalar(escalar, iVal);

   int64_t iNumerator = iVal - iMin;

   return (double) iNumerator / (double) iDenominator; // aproximate value along iDenominator and iNumerator evaluation

}




double_scalar::double_scalar()
{

   m_psource   = NULL;
   m_escalar   = scalar_none;

}


double_scalar::double_scalar(double_scalar_source * psource, e_scalar escalar)
{

   m_psource = psource;
   m_escalar = escalar;

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

   double d = 0.0;

   m_psource->get_scalar(m_escalar, d);

   return d;

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
      return 0.0;

   double d = 0.0;

   m_psource->get_scalar_minimum(m_escalar, d);

   return d;

}


double double_scalar::maximum()
{

   if (is_null())
      return 0.0;

   double d = 0.0;

   m_psource->get_scalar_maximum(m_escalar, d);

   return d;

}

int_scalar::int_scalar()
{

   m_psource = NULL;
   m_escalar = scalar_none;

}


int_scalar::int_scalar(int_scalar_source * psource, e_scalar escalar)
{

   m_psource = psource;
   m_escalar = escalar;

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

   int64_t i = 0;

   m_psource->get_scalar(m_escalar, i);

   return i;

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

   int64_t i = 0;

   m_psource->get_scalar_minimum(m_escalar, i);

   return i;

}


int64_t int_scalar::maximum()
{

   if (is_null())
      return 0;

   int64_t i = 0;

   m_psource->get_scalar_maximum(m_escalar, i);

   return i;

}





