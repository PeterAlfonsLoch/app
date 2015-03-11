

namespace datetime
{


   file_time::file_time() throw()
   {
      dwLowDateTime = 0;
      dwHighDateTime = 0;
   }

   file_time::file_time(const FILETIME& ft) throw()
   {
      dwLowDateTime = ft.dwLowDateTime;
      dwHighDateTime = ft.dwHighDateTime;
   }

   file_time::file_time(ULONGLONG nTime) throw()
   {
      dwLowDateTime = uint32_t(nTime);
      dwHighDateTime = uint32_t(nTime >> 32);
   }

   file_time& file_time::operator=(const FILETIME& ft) throw()
   {
      dwLowDateTime = ft.dwLowDateTime;
      dwHighDateTime = ft.dwHighDateTime;

      return *this;
   }

   file_time WINAPI file_time::get_current_time() throw()
   {
      file_time ft;
      GetSystemTimeAsFileTime(&ft);
      return ft;
   }

   file_time& file_time::operator+=(file_time_span span) throw()
   {
      SetTime(get_time() + span.GetTimeSpan());

      return *this;
   }

   file_time& file_time::operator-=(file_time_span span) throw()
   {
      SetTime(get_time() - span.GetTimeSpan());

      return *this;
   }

   file_time file_time::operator+(file_time_span span) const throw()
   {
      return(file_time(get_time() + span.GetTimeSpan()));
   }

   file_time file_time::operator-(file_time_span span) const throw()
   {
      return(file_time(get_time() - span.GetTimeSpan()));
   }

   file_time_span file_time::operator-(file_time ft) const throw()
   {
      return(file_time_span(get_time() - ft.get_time()));
   }

   bool file_time::operator==(file_time ft) const throw()
   {
      return(get_time() == ft.get_time());
   }

   bool file_time::operator!=(file_time ft) const throw()
   {
      return(get_time() != ft.get_time());
   }

   bool file_time::operator<(file_time ft) const throw()
   {
      return(get_time() < ft.get_time());
   }

   bool file_time::operator>(file_time ft) const throw()
   {
      return(get_time() > ft.get_time());
   }

   bool file_time::operator<=(file_time ft) const throw()
   {
      return(get_time() <= ft.get_time());
   }

   bool file_time::operator>=(file_time ft) const throw()
   {
      return(get_time() >= ft.get_time());
   }

   ULONGLONG file_time::get_time() const throw()
   {
      return((ULONGLONG(dwHighDateTime) << 32) | dwLowDateTime);
   }

   void file_time::SetTime(ULONGLONG nTime) throw()
   {
      dwLowDateTime = uint32_t(nTime);
      dwHighDateTime = uint32_t(nTime >> 32);
   }

   file_time file_time::UTCToLocal() const throw()
   {
      file_time ftLocal;

      ::FileTimeToLocalFileTime(this,&ftLocal);

      return(ftLocal);
   }

   file_time file_time::LocalToUTC() const throw()
   {
      
      file_time ftUTC;

      ::LocalFileTimeToFileTime(this,&ftUTC);

      return(ftUTC);

   }


   const ULONGLONG file_time::Millisecond = 10000;
   const ULONGLONG file_time::Second = Millisecond * static_cast<ULONGLONG>(1000);
   const ULONGLONG file_time::Minute = Second * static_cast<ULONGLONG>(60);
   const ULONGLONG file_time::Hour = Minute * static_cast<ULONGLONG>(60);
   const ULONGLONG file_time::Day = Hour * static_cast<ULONGLONG>(24);
   const ULONGLONG file_time::Week = Day * static_cast<ULONGLONG>(7);


}





















