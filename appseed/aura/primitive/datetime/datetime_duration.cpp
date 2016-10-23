//#include "framework.h"
//#include <math.h>


void duration::normalize()
{

   m_iSeconds     += m_iNanoseconds / (1000 * 1000 * 1000);

   m_iNanoseconds %= 1000 * 1000 * 1000;

}


nanos::nanos(double d)
{

   raw_set((int64_t)(d / (1000.0 * 1000.0 * 1000.0)), (int64_t)fmod(d, 1000.0 * 1000.0 * 1000.0));

}


micros::micros(double d)
{

   raw_set((int64_t)(d / (1000.0 * 1000.0)), (int64_t)fmod(d * 1000.0, 1000.0 * 1000.0 * 1000.0));

}


millis::millis(double d)
{

   raw_set((int64_t)(d / 1000.0), (int64_t)fmod(d * 1000 * 1000.0, 1000.0 * 1000.0 * 1000.0));

}



duration::duration(int64_t iSeconds, int64_t iNanoSeconds)
{

   m_eduration = duration_finite;

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoSeconds;

}

duration::duration(e_duration eduration)
{

   m_eduration = eduration;

}



void duration::set(int64_t i, e_unit eunit)
{

   switch (eunit)
   {
   case unit_nanos:
      raw_set(i / (1000 * 1000 * 1000), i % (1000 * 1000 * 1000));
      break;
   case unit_micros:
      raw_set(i / (1000 * 1000), (i / 1000) % (1000 * 1000 * 1000));
      break;
   case unit_millis:
      raw_set(i / 1000, (i / (1000 * 1000)) % (1000 * 1000 * 1000));
      break;
   case unit_seconds:
      raw_set(i, 0);
      break;
   case unit_minutes:
      raw_set(i * 60, 0);
      break;
   case unit_hours:
      raw_set(i * 60 * 60, 0);
      break;
   default:
      throw invalid_argument_exception(::get_thread_app(), "Unknown time duration unit");

   };

}

void duration::set(double d, e_unit eunit)
{

   switch (eunit)
   {
   case unit_nanos:
      fset(0.0, d);
      break;
   case unit_micros:
      fset(0.0, (d / 1000.0));
      break;
   case unit_millis:
      fset(0.0, d / (1000.0 * 1000.0));
      break;
   case unit_seconds:
      fset(d, 0.0);
      break;
   case unit_minutes:
      fset(d * 60.0, 0.0);
      break;
   case unit_hours:
      fset(d * 60.0 * 60.0, 0.0);
      break;
   default:
      throw invalid_argument_exception(::get_thread_app(), "Unknown time duration unit");

   };
}




void duration::fset(double d, double dNano)
{

   dNano += fmod(d, 1.0) * 1000.0 * 1000.0 * 1000.0;

   raw_set((int64_t)(floor(d) + floor((dNano / (1000.0 * 1000.0 * 1000.0)))), (int64_t)fmod(dNano, 1000.0 * 1000.0 * 1000.0));

}



CLASS_DECL_AURA void Sleep(const duration & duration)
{

   ::Sleep(duration.tick_duration());

}





