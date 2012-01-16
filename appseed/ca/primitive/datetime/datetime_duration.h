#pragma once


#include "template/template_c_number.h"


class CLASS_DECL_ca duration
{
public:

   __int64     m_iNanoseconds;
   __int64     m_iSeconds;

   inline duration();
   inline duration(__int64 iSeconds, __int64 iNanoseconds, bool bNormalize = true);
   inline duration(const duration & duration);

   inline __int64 get_total_milliseconds() const;
   inline __int64 total_milliseconds() const;
   inline bool is_pos_infinity() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   inline bool operator == (const duration & duration) const;

   inline duration & operator = (const duration & duration);

   void normalize();

   inline class os_lock_duration os_lock_duration() const;


   inline operator class os_lock_duration() const;

};

duration::duration()
{
   m_iSeconds     = 0;
   m_iNanoseconds = 0;
}


duration::duration(__int64 iSeconds, __int64 iNanoseconds, bool bNormalize)
{
   m_iSeconds     = iSeconds;
   m_iNanoseconds = iNanoseconds;
   if(bNormalize)
   {
      normalize();
   }
}

duration::duration(const duration & duration)
{
   m_iSeconds        = duration.m_iSeconds;
   m_iNanoseconds    = duration.m_iNanoseconds;
}

__int64 duration::get_total_milliseconds() const
{
   return m_iSeconds * 1000 + m_iNanoseconds / 1000000;
}

os_lock_duration duration::os_lock_duration() const
{
   if(is_pos_infinity())
      return 0xfffffffe;
//      return INFINITE;
   if(get_total_milliseconds() >= 0xffffffff)
      return 0xfffffffe;
   return (DWORD) get_total_milliseconds();
}

duration::operator ::os_lock_duration() const
{
   return ::duration::os_lock_duration();
}

__int64 duration::total_milliseconds() const
{
   return get_total_milliseconds();
}

bool duration::is_pos_infinity() const
{
   return operator == (pos_infinity());
}

duration duration::infinite()
{
   return pos_infinity();
}

duration duration::pos_infinity()
{
   return duration(0x7fffffffffffffff, 1000000000, false);
}

duration duration::zero()
{
   return duration(0, 0);
}

bool duration::operator == (const duration & duration) const
{
   const_cast < class duration * >(this)->normalize();
   const_cast < class duration * >(&duration)->normalize();
   return m_iSeconds == duration.m_iSeconds
      && m_iNanoseconds == duration.m_iNanoseconds;
}

duration & duration::operator = (const duration & duration)
{
   m_iSeconds        = duration.m_iSeconds;
   m_iNanoseconds    = duration.m_iNanoseconds;
   return *this;
}

class CLASS_DECL_ca millis :
   public duration
{
public:


   inline millis(__int64 iMillis = 0);
   inline millis(int iMillis);
   inline millis(DWORD dwMillis);
   millis(double dMillis);

};


class CLASS_DECL_ca seconds :
   public millis
{
public:


   inline seconds(__int64 iSeconds = 0);
   inline seconds(int iSeconds);
   inline seconds(DWORD dwSeconds);
   inline seconds(double dSeconds);


};


class CLASS_DECL_ca minutes :
   public seconds
{
public:


   inline minutes(__int64 iMinutes = 0);
   inline minutes(int iMinutes);
   inline minutes(DWORD dwMinutes);
   inline minutes(double dMinutes);


};


class CLASS_DECL_ca hours :
   public minutes
{
public:


   inline hours(__int64 iHours = 0);
   inline hours(int iHours);
   inline hours(DWORD dwHours);
   inline hours(double dHours);


};


class CLASS_DECL_ca days :
   public hours
{
public:


   inline days(__int64 iDays = 0);
   inline days(int iDays);
   inline days(DWORD dwDays);
   inline days(double dDays);


};




millis::millis(__int64 i) :
   duration(i / 1000, (i % 1000) * 1000000)
{
}

millis::millis(int i) :
   duration(i / 1000, (i % 1000) * 1000000)
{
}

millis::millis(DWORD dw) :
   duration(dw / 1000, (dw % 1000) * 1000000)
{
}


seconds::seconds(__int64 i) :
   millis(i * 1000)
{
}

seconds::seconds(int i) :
   millis(i * 1000)
{
}

seconds::seconds(DWORD dw) :
   millis(dw * 1000)
{
}

seconds::seconds(double d) :
   millis(d * 1000.0)
{
}

minutes::minutes(__int64 i) :
   seconds(i * 60)
{
}

minutes::minutes(int i) :
   seconds(i * 60)
{
}

minutes::minutes(DWORD dw) :
   seconds(dw * 60)
{
}

minutes::minutes(double d) :
   seconds(d * 60.0)
{
}

hours::hours(__int64 i) :
   minutes(i * 60)
{
}

hours::hours(int i) :
   minutes(i * 60)
{
}

hours::hours(DWORD dw) :
   minutes(dw * 60)
{
}

hours::hours(double d) :
   minutes(d * 60.0)
{
}

days::days(__int64 i) :
   hours(i * 24)
{
}

days::days(int i) :
   hours(i * 24)
{
}

days::days(DWORD dw) :
   hours(dw * 24)
{
}

days::days(double d) :
   hours(d * 24.0)
{
}
