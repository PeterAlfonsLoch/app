// from 7-zip on 2010-12-22
#pragma once

namespace libcompress
{

   struct codec_info_ex
   {
      string      Name;
      method_id   Id;
      uint32      NumInStreams;
      uint32      NumOutStreams;
      bool        EncoderIsAssigned;
      bool        DecoderIsAssigned;

      bool IsSimpleCodec() const
      {
         return NumOutStreams == 1 && NumInStreams == 1;
      }

      codec_info_ex() :
         EncoderIsAssigned(false),
         DecoderIsAssigned(false)
      {
      }
   };

   HRESULT LoadExternalCodecs(::libcompress::codecs_info_interface *codecsInfo, array < codec_info_ex >  & externalCodecs);

   bool FindMethod(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      const string &name, method_id &methodId, uint32 &numInStreams, uint32 &numOutStreams);

   bool FindMethod(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId, string &name);


   HRESULT CreateCoder(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::filter_interface * & filter,
      ::libcompress::coder_interface * & coder,
      ::libcompress::coder2_interface * & coder2,
      bool encode, bool onlyCoder);

   HRESULT CreateCoder(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::coder_interface * & coder,
      ::libcompress::coder2_interface * & coder2,
      bool encode);

   HRESULT CreateCoder(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::coder_interface * & coder, bool encode);

   HRESULT CreateFilter(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::filter_interface * & filter,
      bool encode);

} // namespace libcompress
