#pragma once


class CLASS_DECL_AURA duration
{
public:

   enum e_unit
   {

      unit_nanos,
      unit_micros,
      unit_millis,
      unit_seconds,
      unit_minutes,
      unit_hours,
      unit_days

   };

   
   int64_t     m_iNanoseconds;
   int64_t     m_iSeconds;

   
   inline void raw_set(int64_t iSeconds, int64_t iNanoseconds);
   inline void set(int64_t iSeconds, int64_t iNanoseconds);
   inline void set_null();
   static inline duration raw_create(int64_t iSeconds, int64_t iNanoseconds);
   static inline duration create(int64_t iSeconds, int64_t iNanoseconds);
   static inline duration create_null();


   inline void fset(double dSeconds, double dNanoseconds);
   static inline duration fcreate(double dSeconds, double dNanoseconds);

   void set(int64_t i, e_unit eunit);
   void set(double d, e_unit eunit);


   inline int64_t get_total_milliseconds() const;
   inline int64_t total_milliseconds() const;
   inline int64_t get_total_seconds() const;
   inline int64_t total_seconds() const;
   inline bool is_pos_infinity() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   inline bool operator == (const duration & duration) const;


   void normalize();

   inline class os_lock_duration os_lock_duration() const;


   inline operator class os_lock_duration() const;

   inline __time64_t GetTimeSpan() const;




};


void duration::raw_set(int64_t iSeconds, int64_t iNanoseconds)
{

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoseconds;

}


void duration::set(int64_t iSeconds, int64_t iNanoseconds)
{

   raw_set(iSeconds, iNanoseconds);

   normalize();

}


void duration::set_null()
{

   raw_set(0, 0);

}

duration duration::raw_create(int64_t iSeconds, int64_t iNanoseconds)
{

   duration duration;

   duration.raw_set(iSeconds, iNanoseconds);

   return duration;

}

void duration::fset(double d, double dNano)
{

   dNano += fmod(d, 1.0) * 1000.0 * 1000.0 * 1000.0;

   raw_set((int64_t)(floor(d) + floor((dNano / (1000.0 * 1000.0 * 1000.0)))), (int64_t)fmod(dNano, 1000.0 * 1000.0 * 1000.0));

}


duration duration::fcreate(double d, double dNano)
{

   duration duration;

   duration.fset(d, dNano);

   return duration;

}


duration duration::create(int64_t iSeconds, int64_t iNanoseconds)
{

   duration duration;

   duration.set(iSeconds, iNanoseconds);

   return duration;

}


duration duration::create_null()
{

   duration duration;

   duration.set_null();

   return duration;

}


int64_t duration::get_total_milliseconds() const
{

   return m_iSeconds * 1000 + m_iNanoseconds / 1000000;

}


os_lock_duration duration::os_lock_duration() const
{

   if(is_pos_infinity())
      return INFINITE;

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
   return duration::raw_create(0x7fffffffffffffffLL, 999999999);
}

duration duration::zero()
{
   return duration::create(0, 0);
}

bool duration::operator == (const duration & duration) const
{
   const_cast < class duration * >(this)->normalize();
   const_cast < class duration * >(&duration)->normalize();
   return m_iSeconds == duration.m_iSeconds
      && m_iNanoseconds == duration.m_iNanoseconds;
}

class CLASS_DECL_AURA millis :
   public duration
{
public:


   inline millis(int64_t iMillis = 0);
   inline millis(int32_t iMillis);
   inline millis(uint32_t dwMillis);
   millis(double dMillis);

};


class CLASS_DECL_AURA seconds :
   public millis
{
public:


   inline seconds(int64_t iSeconds = 0);
   inline seconds(int32_t iSeconds);
   inline seconds(uint32_t dwSeconds);
   inline seconds(double dSeconds);


};


class CLASS_DECL_AURA minutes :
   public seconds
{
public:


   inline minutes(int64_t iMinutes = 0);
   inline minutes(int32_t iMinutes);
   inline minutes(uint32_t dwMinutes);
   inline minutes(double dMinutes);


};


class CLASS_DECL_AURA hours :
   public minutes
{
public:


   inline hours(int64_t iHours = 0);
   inline hours(int32_t iHours);
   inline hours(uint32_t dwHours);
   inline hours(double dHours);


};


class CLASS_DECL_AURA days :
   public hours
{
public:


   inline days(int64_t iDays = 0);
   inline days(int32_t iDays);
   inline days(uint32_t dwDays);
   inline days(double dDays);


};




millis::millis(int64_t i)
{

   raw_set(i / 1000, (i % 1000) * 1000000);

}


millis::millis(int32_t i)
{

   raw_set(i / 1000, (i % 1000) * 1000000);

}


millis::millis(uint32_t dw)
{

   raw_set(dw / 1000, (dw % 1000) * 1000000);

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

