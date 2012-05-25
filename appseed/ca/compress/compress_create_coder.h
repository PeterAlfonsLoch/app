// from 7-zip on 2010-12-22
#pragma once

namespace compress
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

   HRESULT LoadExternalCodecs(::compress::codecs_info_interface *codecsInfo, base_array < codec_info_ex >  & externalCodecs);

   bool FindMethod(
      ::compress::codecs_info_interface *codecsInfo, const base_array<codec_info_ex> *externalCodecs,
      const string &name, method_id &methodId, uint32 &numInStreams, uint32 &numOutStreams);

   bool FindMethod(
      ::compress::codecs_info_interface *codecsInfo, const base_array<codec_info_ex> *externalCodecs,
      method_id methodId, string &name);


   HRESULT CreateCoder(
      ::compress::codecs_info_interface *codecsInfo, const base_array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::compress::filter_interface * & filter,
      ::compress::coder_interface * & coder,
      ::compress::coder2_interface * & coder2,
      bool encode, bool onlyCoder);

   HRESULT CreateCoder(
      ::compress::codecs_info_interface *codecsInfo, const base_array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::compress::coder_interface * & coder,
      ::compress::coder2_interface * & coder2,
      bool encode);

   HRESULT CreateCoder(
      ::compress::codecs_info_interface *codecsInfo, const base_array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::compress::coder_interface * & coder, bool encode);

   HRESULT CreateFilter(
      ::compress::codecs_info_interface *codecsInfo, const base_array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::compress::filter_interface * & filter,
      bool encode);

} // namespace compress