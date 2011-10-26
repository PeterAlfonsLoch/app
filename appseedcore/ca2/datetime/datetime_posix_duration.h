#pragma once

typedef CLASS_DECL_ca c_number < DWORD > os_lock_duration;

namespace posix
{





   class CLASS_DECL_ca duration
   {
   public:
      
      __int64     m_iNanoseconds;
      __int64     m_iSeconds;

      duration(__int64 iSeconds = 0, __int64 iNanoseconds = 0);

      __int64 get_total_milliseconds() const;
      __int64 total_milliseconds() const;
      bool is_pos_infinity() const;
      static duration infinite();
      static duration pos_infinity();
      static duration zero();
      bool operator == (const duration & duration) const;

      void normalize();

      os_lock_duration os_lock_duration() const;

   };


}
