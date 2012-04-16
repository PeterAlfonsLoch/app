#pragma once


namespace windows
{


   namespace file_time
   {


      bool DosTimeToFileTime(uint32_t dosTime, FILETIME & fileTime);
      bool FileTimeToDosTime(const FILETIME & fileTime, uint32_t & dosTime);
      void UnixTimeToFileTime(uint32_t unixTime, FILETIME & fileTime);
      bool FileTimeToUnixTime(const FILETIME & fileTime, uint32_t & unixTime);
      bool GetSecondsSince1601(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned min, unsigned sec, uint64_t &resSeconds);
      void GetCurUtcFileTime(FILETIME & ft);


   } // namespace file_time


} // namespace windows



