// 7zCompressionMode.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace n7z 
{

   struct CMethodFull: public ::compress::method
   {
      uint32 NumInStreams;
      uint32 NumOutStreams;
      bool IsSimpleCoder() const { return (NumInStreams == 1) && (NumOutStreams == 1); }
   };

   struct CBind
   {
      uint32 InCoder;
      uint32 InStream;
      uint32 OutCoder;
      uint32 OutStream;
   };

   struct CCompressionMethodMode
   {
      array_ptr_alloc <CMethodFull> Methods;
      base_array<CBind> Binds;
      uint32 NumThreads;
      bool PasswordIsDefined;
      string Password;

      bool is_empty() const { return (Methods.is_empty() && !PasswordIsDefined); }
      CCompressionMethodMode(): PasswordIsDefined(false)
         , NumThreads(1)
      {}
   };

} // namespace 7z