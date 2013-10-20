#pragma once


class CLASS_DECL_BASE duration
{
public:

   int64_t     m_iNanoseconds;
   int64_t     m_iSeconds;

   inline duration();
   inline duration(int64_t iSeconds, int64_t iNanoseconds, bool bNormalize = true);
   inline duration(const duration & duration);

   inline int64_t get_total_milliseconds() const;
   inline int64_t total_milliseconds() const;
   inline int64_t get_total_seconds() const;
   inline int64_t total_seconds() const;
   inline bool is_pos_infinity() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   inline bool operator == (const duration & duration) const;

   inline duration & operator = (const duration & duration);

   void normalize();

   inline class os_lock_duration os_lock_duration() const;


   inline operator class os_lock_duration() const;

   inline __time64_t GetTimeSpan() const;




};

duration::duration()
{
   m_iSeconds     = 0;
   m_iNanoseconds = 0;
}


duration::duration(int64_t iSeconds, int64_t iNanoseconds, bool bNormalize)
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

int64_t duration::get_total_milliseconds() const
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
   return (uint32_t) get_total_milliseconds();
}

duration::operator ::os_lock_duration() const
{
   return ::duration::os_lock_duration();
}

int64_t duration::total_milliseconds() const
{
   return get_total_milliseconds();
}

bool duration::is_pos_infinity() const
{
   return m_iSeconds == 0x7fffffffffffffffLL && m_iNanoseconds == 999999999;
}

duration duration::infinite()
{
   return pos_infinity();
}

duration duration::pos_infinity()
{
   return duration(0x7fffffffffffffffLL, 999999999, false);
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

class CLASS_DECL_BASE millis :
   public duration
{
public:


   inline millis(int64_t iMillis = 0);
   inline millis(int32_t iMillis);
   inline millis(uint32_t dwMillis);
   millis(double dMillis);

};


class CLASS_DECL_BASE seconds :
   public millis
{
public:


   inline seconds(int64_t iSeconds = 0);
   inline seconds(int32_t iSeconds);
   inline seconds(uint32_t dwSeconds);
   inline seconds(double dSeconds);


};


class CLASS_DECL_BASE minutes :
   public seconds
{
public:


   inline minutes(int64_t iMinutes = 0);
   inline minutes(int32_t iMinutes);
   inline minutes(uint32_t dwMinutes);
   inline minutes(double dMinutes);


};


class CLASS_DECL_BASE hours :
   public minutes
{
public:


   inline hours(int64_t iHours = 0);
   inline hours(int32_t iHours);
   inline hours(uint32_t dwHours);
   inline hours(double dHours);


};


class CLASS_DECL_BASE days :
   public hours
{
public:


   inline days(int64_t iDays = 0);
   inline days(int32_t iDays);
   inline days(uint32_t dwDays);
   inline days(double dDays);


};




millis::millis(int64_t i) :
   duration(i / 1000, (i % 1000) * 1000000)
{
}

millis::millis(int32_t i) :
   duration(i / 1000, (i % 1000) * 1000000)
{
}

millis::millis(uint32_t dw) :
   duration(dw / 1000, (dw % 1000) * 1000000)
{
}


seconds::seconds(int64_t i) :
   millis(i * 1000)
{
}

seconds::seconds(int32_t i) :
   millis(i * 1000)
{
}

seconds::seconds(uint32_t dw) :
   millis(dw * 1000)
{
}

seconds::seconds(double d) :
   millis(d * 1000.0)
{
}

minutes::minutes(int64_t i) :
   seconds(i * 60)
{
}

minutes::minutes(int32_t i) :
   seconds(i * 60)
{
}

minutes::minutes(uint32_t dw) :
   seconds(dw * 60)
{
}

minutes::minutes(double d) :
   seconds(d * 60.0)
{
}

hours::hours(int64_t i) :
   minutes(i * 60)
{
}

hours::hours(int32_t i) :
   minutes(i * 60)
{
}

hours::hours(uint32_t dw) :
   minutes(dw * 60)
{
}

hours::hours(double d) :
   minutes(d * 60.0)
{
}

days::days(int64_t i) :
   hours(i * 24)
{
}

days::days(int32_t i) :
   hours(i * 24)
{
}

days::days(uint32_t dw) :
   hours(dw * 24)
{
}

days::days(double d) :
   hours(d * 24.0)
{
}

inline __time64_t duration::GetTimeSpan() const
{
   return total_seconds();
}


inline int64_t duration::get_total_seconds() const
{
   return (get_total_milliseconds() + 500) / 1000;
}

inline int64_t duration::total_seconds() const
{
   return (total_milliseconds() + 500) / 1000;
}
