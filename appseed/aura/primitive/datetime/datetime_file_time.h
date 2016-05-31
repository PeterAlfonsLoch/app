#pragma once


namespace datetime
{


   class CLASS_DECL_AURA file_time:
      public FILETIME
   {
   public:
      file_time() NOTHROW;
      file_time(const FILETIME& ft) NOTHROW;
      file_time(ULONGLONG nTime) NOTHROW;

      static file_time WINAPI get_current_time() NOTHROW;

      file_time& operator=(const FILETIME& ft) NOTHROW;

      file_time& operator+=(file_time_span span) NOTHROW;
      file_time& operator-=(file_time_span span) NOTHROW;

      file_time operator+(file_time_span span) const NOTHROW;
      file_time operator-(file_time_span span) const NOTHROW;
      file_time_span operator-(file_time ft) const NOTHROW;

      bool operator==(file_time ft) const NOTHROW;
      bool operator!=(file_time ft) const NOTHROW;
      bool operator<(file_time ft) const NOTHROW;
      bool operator>(file_time ft) const NOTHROW;
      bool operator<=(file_time ft) const NOTHROW;
      bool operator>=(file_time ft) const NOTHROW;

      ULONGLONG get_time() const NOTHROW;
      void SetTime(ULONGLONG nTime) NOTHROW;

      file_time UTCToLocal() const NOTHROW;
      file_time LocalToUTC() const NOTHROW;

      static const ULONGLONG Millisecond;
      static const ULONGLONG Second;
      static const ULONGLONG Minute;
      static const ULONGLONG Hour;
      static const ULONGLONG Day;
      static const ULONGLONG Week;
   };

   // Used only if these strings could not be found in resources.
   extern CLASS_DECL_AURA const char * const szInvalidDateTime;
   extern CLASS_DECL_AURA const char * const szInvalidDateTimeSpan;

   const int32_t maxTimeBufferSize = 128;
   const long maxDaysInSpan  =   3615897L;




} // namesace datetime


CLASS_DECL_AURA FILETIME get_file_time_now();


struct CLASS_DECL_AURA file_time
{


//#ifdef WINDOWS
   FILETIME                         creation;
   FILETIME                         modified;
   FILETIME                         access; // Not used at Windows?
//#else
  // __time_t                         creation;
//   __time_t                         access;
  // __time_t                         modified;
//#endif

   file_time()
   {

      ZERO(creation);
      ZERO(modified);
      ZERO(access);

   }

   bool operator == (const file_time & t) const
   {
      if(&t == this)
         return true;
      return 
         !memcmp(&creation ,  &t.creation ,sizeof(creation))
      && !memcmp(&modified ,  &t.modified ,sizeof(modified))
	   && !memcmp(&access   ,  &t.access   ,sizeof(access));
   }

   bool modified_timeout(const FILETIME & current, int iSeconds)
   {

      uint64_t mod = (uint64_t)modified.dwLowDateTime | ((uint64_t) modified.dwHighDateTime << 32);
      uint64_t now = (uint64_t)current.dwLowDateTime | ((uint64_t)current.dwHighDateTime << 32);

      if (now - mod > (natural(iSeconds) * 1000 * 1000 * 10))
      {

         return true;

      }

      return false;

   }

   bool modified_timeout( int iSeconds)
   {
      
      FILETIME current = get_file_time_now();

      return modified_timeout(current, iSeconds);

   }

};

CLASS_DECL_AURA bool file_modified_timeout(const char * path, int iSeconds);


CLASS_DECL_AURA void get_file_time(const char * psz,file_time & time);

CLASS_DECL_AURA void get_file_time(const char * psz,FILETIME & creation,FILETIME & modified);

inline file_time get_file_time(const char * psz)
{

   file_time time ={};

   get_file_time(psz,time);

   return time;

}









