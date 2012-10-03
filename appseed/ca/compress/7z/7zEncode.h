// 7zEncode.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace n7z
{

   class CEncoder :
      virtual public ::radix::object
   {
      ::compress::coder_mixer::CCoderMixer2MT *                 _mixerCoderSpec;
      ::ca::smart_pointer < ::compress::coder2_interface >      _mixerCoder;

      array_ptr_alloc<CCoderInfo>                               _codersInfo;

      CCompressionMethodMode                                    _options;
      ::compress::coder_mixer::CBindInfo                        _bindInfo;
      ::compress::coder_mixer::CBindInfo                        _decompressBindInfo;
      ::compress::coder_mixer::CBindReverseConverter *          _bindReverseConverter;
      base_array < ::compress::method_id >                      _decompressionMethods;

      HRESULT CreateMixerCoder(::compress::codecs_info_interface *codecsInfo, const base_array < ::compress::codec_info_ex > *externalCodecs, const file_size *inSizeForReduce);

      bool _constructed;
   public:
      CEncoder(::ca::application * papp, const CCompressionMethodMode &options);
      virtual ~CEncoder();
      HRESULT EncoderConstr();
      HRESULT Encode(
         ::compress::codecs_info_interface *codecsInfo, const base_array < ::compress::codec_info_ex > *externalCodecs,
         ::ex1::reader *inStream,
         const file_size *inStreamSize, const file_size *inSizeForReduce,
         CFolder &folderItem,
         ::ex1::writer *outStream,
         base_array < file_size > &packSizes,
         ::compress::progress_info_interface *compressProgress);
   };

} // namespace n7z
