// HandlerOut.h
// from 7-zip on morning of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{

   struct COneMethodInfo
   {
      gen::property_set Props;
      string MethodName;

      bool IsLzma() const;
   };

   class CLASS_DECL_ca out_handler :
      virtual public ::radix::object
   {
   public:

      out_handler(::ca::application * papp);

      ex1::HRes SetProperty(const char *name, var value);

      ex1::HRes SetSolidSettings(const string &s);
      ex1::HRes SetSolidSettings(var value);

      uint32_t _numThreads;

      uint32_t _crcSize;

      array_ptr_alloc<COneMethodInfo> _methods;
      bool _removeSfxBlock;

      uint64_t _numSolidFiles;
      uint64_t _numSolidBytes;
      bool _numSolidBytesDefined;
      bool _solidExtension;

      bool _compressHeaders;
      bool _encryptHeadersSpecified;
      bool _encryptHeaders;

      bool WriteCTime;
      bool WriteATime;
      bool WriteMTime;

      bool _autoFilter;
      uint32_t _level;

      bool _volumeMode;

      ex1::HRes SetParam(COneMethodInfo &oneMethodInfo, const string &name, const string &value);
      ex1::HRes SetParams(COneMethodInfo &oneMethodInfo, const string &srcString);

      void SetCompressionMethod2(COneMethodInfo &oneMethodInfo, uint32_t numThreads);

      void InitSolidFiles() { _numSolidFiles = (uint64_t)(int64_t)(-1); }
      void InitSolidSize()  { _numSolidBytes = (uint64_t)(int64_t)(-1); }
      void InitSolid()
      {
         InitSolidFiles();
         InitSolidSize();
         _solidExtension = false;
         _numSolidBytesDefined = false;
      }

      void Init();

      out_handler() { Init(); }

      void BeforeSetProperty();

      uint32_t minNumber;
      uint32_t numProcessors;
      uint32_t mainDicSize;
      uint32_t mainDicMethodIndex;
   };

} // namespace libcompress
