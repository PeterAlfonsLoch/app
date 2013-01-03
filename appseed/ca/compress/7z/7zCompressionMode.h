// 7zCompressionMode.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace n7z 
{

   struct CMethodFull: public ::compress::method
   {
      uint32_t NumInStreams;
      uint32_t NumOutStreams;
      bool IsSimpleCoder() const { return (NumInStreams == 1) && (NumOutStreams == 1); }
   };

   struct CBind
   {
      uint32_t InCoder;
      uint32_t InStream;
      uint32_t OutCoder;
      uint32_t OutStream;
   };

   struct CCompressionMethodMode
   {
      array_ptr_alloc <CMethodFull> Methods;
      base_array<CBind> Binds;
      uint32_t NumThreads;
      bool PasswordIsDefined;
      string Password;

      bool is_empty() const { return (Methods.is_empty() && !PasswordIsDefined); }
      CCompressionMethodMode(): PasswordIsDefined(false)
         , NumThreads(1)
      {}
   };

} // namespace 7z