// 7zEncode.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace n7z
{

   class CEncoder :
      virtual public ::ca::object
   {
      ::libcompress::coder_mixer::CCoderMixer2MT *                 _mixerCoderSpec;
      ::ca::smart_pointer < ::libcompress::coder2_interface >      _mixerCoder;

      ::collection::smart_pointer_array<CCoderInfo>                               _codersInfo;

      CCompressionMethodMode                                    _options;
      ::libcompress::coder_mixer::CBindInfo                        _bindInfo;
      ::libcompress::coder_mixer::CBindInfo                        _decompressBindInfo;
      ::libcompress::coder_mixer::CBindReverseConverter *          _bindReverseConverter;
      base_array < ::libcompress::method_id >                      _decompressionMethods;

      HRESULT CreateMixerCoder(::libcompress::codecs_info_interface *codecsInfo, const base_array < ::libcompress::codec_info_ex > *externalCodecs, const file_size *inSizeForReduce);

      bool _constructed;
   public:
      CEncoder(::ca::application * papp, const CCompressionMethodMode &options);
      virtual ~CEncoder();
      HRESULT EncoderConstr();
      HRESULT Encode(
         ::libcompress::codecs_info_interface *codecsInfo, const base_array < ::libcompress::codec_info_ex > *externalCodecs,
         ::ca::reader *inStream,
         const file_size *inStreamSize, const file_size *inSizeForReduce,
         CFolder &folderItem,
         ::ca::writer *outStream,
         base_array < file_size > &packSizes,
         ::libcompress::progress_info_interface *compressProgress);
   };

} // namespace n7z
