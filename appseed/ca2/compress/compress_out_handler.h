// HandlerOut.h
// from 7-zip on morning of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{

   struct COneMethodInfo :
      virtual public ::ca2::ca2
   {
      ::ca2::property_set Props;
      string MethodName;

      bool IsLzma() const;
   };

   class CLASS_DECL_ca2 out_handler :
      virtual public ::ca2::object
   {
   public:

      out_handler(sp(::ca2::application) papp);

      ::ca2::HRes SetProperty(const char *name, var value);

      ::ca2::HRes SetSolidSettings(const string &s);
      ::ca2::HRes SetSolidSettings(var value);

      uint32_t _numThreads;

      uint32_t _crcSize;

      spa(COneMethodInfo) _methods;
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

      ::ca2::HRes SetParam(COneMethodInfo &oneMethodInfo, const string &name, const string &value);
      ::ca2::HRes SetParams(COneMethodInfo &oneMethodInfo, const string &srcString);

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
