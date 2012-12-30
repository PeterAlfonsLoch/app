// CreateCoder.cpp
// from 7-zip on 2012-12-22
#pragma once


namespace compress
{

   typedef void * (*pfn_create_codec)();
   struct codec_info
   {
     pfn_create_codec   m_pfnCreateDecoder;
     pfn_create_codec   m_pfnCreateEncoder;
     method_id          Id;
     const char *       Name;
     uint32             NumInStreams;
     bool               IsFilter;
   };

   void RegisterCodec(const codec_info *codecInfo);

   #define REGISTER_CODEC_NAME(x) CRegisterCodec ## x

   #define REGISTER_CODEC(x) struct REGISTER_CODEC_NAME(x) { \
       REGISTER_CODEC_NAME(x)() { RegisterCodec(&g_CodecInfo); }}; \
       static REGISTER_CODEC_NAME(x) g_RegisterCodec;

   #define REGISTER_CODECS_NAME(x) CRegisterCodecs ## x
   #define REGISTER_CODECS(x) struct REGISTER_CODECS_NAME(x) { \
       REGISTER_CODECS_NAME(x)() { for (int32_t i = 0; i < sizeof(g_CodecsInfo) / sizeof(g_CodecsInfo[0]); i++) \
       RegisterCodec(&g_CodecsInfo[i]); }}; \
       static REGISTER_CODECS_NAME(x) g_RegisterCodecs;

} // namespace compress
