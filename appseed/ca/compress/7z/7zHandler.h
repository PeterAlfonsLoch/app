// 7z/Handler.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace n7z
{

#ifndef __7Z_SET_PROPERTIES

#ifdef EXTRACT_ONLY
#if !defined(_7ZIP_ST) && !defined(_SFX)
#define __7Z_SET_PROPERTIES
#endif
#else
#define __7Z_SET_PROPERTIES
#endif

#endif


   class handler:
      virtual public ::libcompress::out_handler,
      virtual public ::libcompress::input_archive_interface,
      virtual public ::libcompress::set_properties_interface,
      virtual public ::libcompress::output_archive_interface,
      virtual public ::libcompress::set_codecs_info_interface
   {
   public:
      //MY_QUERYINTERFACE_BEGIN2(IInArchive)
      //#ifdef __7Z_SET_PROPERTIES
      //MY_QUERYINTERFACE_ENTRY(ISetProperties)
      //#endif
      //#ifndef EXTRACT_ONLY
      //MY_QUERYINTERFACE_ENTRY(IOutArchive)
      //#endif
      //QUERY_ENTRY_ISetCompressCodecsInfo
      //MY_QUERYINTERFACE_END
      //MY_ADDREF_RELEASE

      //INTERFACE_IInArchive(;)

      //#ifdef __7Z_SET_PROPERTIES

      //#endif

      //  INTERFACE_IOutArchive(;)
      //#endif
      //

      CA2_COMPRESS_INTERFACE_input_archive(;)
      CA2_COMPRESS_INTERFACE_IOutArchive(;)


      handler();

      virtual ::ca::HRes SetCompressCodecsInfo(::libcompress::codecs_info_interface *compressCodecsInfo) = 0;
      virtual ::ca::HRes SetProperties(const char **names, const var *values, int32_t numProperties);

   private:
      ::ca::smart_pointer < ::ca::byte_input_stream > _inStream;
      n7z::CArchiveDatabaseEx _db;
      //#ifndef _NO_CRYPTO
      bool _passwordIsDefined;
      //#endif



#ifdef EXTRACT_ONLY

#ifdef __7Z_SET_PROPERTIES
      uint32_t _numThreads;
#endif

      uint32_t _crcSize;

#else

      base_array<CBind> _binds;

      ::ca::HRes SetCompressionMethod(CCompressionMethodMode &method,
         array_ptr_alloc < ::libcompress::COneMethodInfo > &methodsInfo
         , uint32_t numThreads
         );

      ::ca::HRes SetCompressionMethod(
         CCompressionMethodMode &method,
         CCompressionMethodMode &headerMethod);

#endif

      bool IsEncrypted(uint32_t index1) const;
//#ifndef _SFX

      base_array<uint64_t> _fileInfoPopIDs;
      void FillPopIDs();

//#endif

      ///DECL_EXTERNAL_CODECS_VARS
      ::libcompress::codecs_info_interface * _codecsInfo;
      base_array < ::libcompress::codec_info_ex > _externalCodecs;
   };

} // namespace n7z
