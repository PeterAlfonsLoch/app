// CreateCoder.cpp
// from 7-zip on 2012-12-22
#include "framework.h"

/*#include "../../Windows/Defs.h"
#include "../../Windows/PropVariant.h"

#include "CreateCoder.h"

#include "FilterCoder.h"
#include "RegisterCodec.h"*/

namespace libcompress
{

   static const uint32_t kNumCodecsMax = 64;
   uint32_t g_NumCodecs = 0;
   const codec_info *g_Codecs[kNumCodecsMax];
   void RegisterCodec(const codec_info *codecInfo)
   {
      if (g_NumCodecs < kNumCodecsMax)
         g_Codecs[g_NumCodecs++] = codecInfo;
   }

   static HRESULT ReadNumberOfStreams(::libcompress::codecs_info_interface * codecsInfo, uint32_t index, int32_t propID, uint32_t & res)
   {
      var prop;
      RINOK(codecsInfo->GetProperty(index, propID, &prop));
      if (prop.is_empty())
         res = 1;
      else if (prop.get_type() == var::type_uint32 || prop.get_type() == var::type_int32)
         res = prop;
      else
         return E_INVALIDARG;
      return S_OK;
   }

   #define PROPID int32_t

   static HRESULT ReadIsAssignedProp(::libcompress::codecs_info_interface  * codecsInfo, uint32_t index, PROPID propID, bool &res)
   {
      var prop;
      RINOK(codecsInfo->GetProperty(index, propID, &prop));
      if (prop.is_empty())
         res = true;
      else if (prop.get_type() == var::type_bool)
         res = bool(prop);
      else
         return E_INVALIDARG;
      return S_OK;
   }

   HRESULT LoadExternalCodecs(::libcompress::codecs_info_interface  * codecsInfo, array<codec_info_ex> &externalCodecs)
   {
      uint32_t num;
      RINOK(codecsInfo->GetNumberOfMethods(&num));
      for (uint32_t i = 0; i < num; i++)
      {
         codec_info_ex info;
         var prop;
         RINOK(codecsInfo->GetProperty(i, method_prop_ID, &prop));
         // if (prop.vt != var::type_string)
         // info.Id.IDSize = (byte)SysStringByteLen(prop.bstrVal);
         // memmove(info.Id.ID, prop.bstrVal, info.Id.IDSize);
         if (prop.get_type() != var::type_uint64)
         {
            continue; // old Interface
            // return E_INVALIDARG;
         }
         info.Id = (uint64_t) prop;
         prop.unset();

         RINOK(codecsInfo->GetProperty(i, method_prop_Name, &prop));
         if (prop.get_type() == var::type_string)
            info.Name = prop;
         else if (prop.get_type() != var::type_empty)
            return E_INVALIDARG;;

         RINOK(ReadNumberOfStreams(codecsInfo, i, method_prop_InStreams, info.NumInStreams));
         RINOK(ReadNumberOfStreams(codecsInfo, i, method_prop_OutStreams, info.NumOutStreams));
         RINOK(ReadIsAssignedProp(codecsInfo, i, method_prop_EncoderIsAssigned, info.EncoderIsAssigned));
         RINOK(ReadIsAssignedProp(codecsInfo, i, method_prop_DecoderIsAssigned, info.DecoderIsAssigned));

         externalCodecs.add(info);
      }
      return S_OK;
   }


   bool FindMethod(
      ::libcompress::codecs_info_interface * /*codecsInfo*/, const array<codec_info_ex> *externalCodecs,
      const string &name,
      method_id &methodId, uint32_t &numInStreams, uint32_t &numOutStreams)
   {
      UNREFERENCED_PARAMETER(externalCodecs);
      uint32_t i;
      for (i = 0; i < g_NumCodecs; i++)
      {
         const codec_info &codec = *g_Codecs[i];
         if (name.CompareNoCase(codec.Name) == 0)
         {
            methodId = codec.Id;
            numInStreams = codec.NumInStreams;
            numOutStreams = 1;
            return true;
         }
      }
#ifdef EXTERNAL_CODECS
      if (externalCodecs)
         for (i = 0; i < (uint32_t)externalCodecs->Size(); i++)
         {
            const codec_info_ex &codec = (*externalCodecs)[i];
            if (codec.Name.CompareNoCase(name) == 0)
            {
               methodId = codec.Id;
               numInStreams = codec.NumInStreams;
               numOutStreams = codec.NumOutStreams;
               return true;
            }
         }
#endif
         return false;
   }

   bool FindMethod(
      ::libcompress::codecs_info_interface * /*codecsInfo*/, const array<codec_info_ex> *externalCodecs,
      method_id methodId, string &name)
   {
      UNREFERENCED_PARAMETER(externalCodecs);
      uint32_t i;
      for (i = 0; i < g_NumCodecs; i++)
      {
         const codec_info &codec = *g_Codecs[i];
         if (methodId == codec.Id)
         {
            name = codec.Name;
            return true;
         }
      }
#ifdef EXTERNAL_CODECS
      if (externalCodecs)
         for (i = 0; i < (uint32_t)externalCodecs->Size(); i++)
         {
            const codec_info_ex &codec = (*externalCodecs)[i];
            if (methodId == codec.Id)
            {
               name = codec.Name;
               return true;
            }
         }
#endif
         return false;
   }

   HRESULT CreateCoder(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::filter_interface * &filter,
      ::libcompress::coder_interface * &coder,
      ::libcompress::coder2_interface * &coder2,
      bool encode, bool onlyCoder)
   {
      bool created = false;
      uint32_t i;
      for (i = 0; i < g_NumCodecs; i++)
      {
         const codec_info &codec = *g_Codecs[i];
         if (codec.Id == methodId)
         {
            if (encode)
            {
               if (codec.m_pfnCreateEncoder)
               {
                  void *p = codec.m_pfnCreateEncoder();
                  if (codec.IsFilter) filter = (::libcompress::filter_interface *)p;
                  else if (codec.NumInStreams == 1) coder = (::libcompress::coder_interface *)p;
                  else coder2 = (::libcompress::coder2_interface *)p;
                  created = (p != 0);
                  break;
               }
            }
            else
               if (codec.m_pfnCreateDecoder)
               {
                  void *p = codec.m_pfnCreateDecoder();
                  if (codec.IsFilter) filter = (::libcompress::filter_interface *)p;
                  else if (codec.NumInStreams == 1) coder = (::libcompress::coder_interface *)p;
                  else coder2 = (::libcompress::coder2_interface *)p;
                  created = (p != 0);
                  break;
               }
         }
      }

      if (!created && externalCodecs)
         for (i = 0; i < (uint32_t)externalCodecs->get_size(); i++)
         {
            const codec_info_ex &codec = (*externalCodecs)[i];
            if (codec.Id == methodId)
            {
               if (encode)
               {
                  if (codec.EncoderIsAssigned)
                  {
                     if (codec.IsSimpleCodec())
                     {
                        HRESULT result = codecsInfo->CreateEncoder(i, "compress_coder", (void **)&coder);
                        if (result != S_OK && result != E_NOINTERFACE && result != CLASS_E_CLASSNOTAVAILABLE)
                           return result;
                        if (!coder)
                        {
                           RINOK(codecsInfo->CreateEncoder(i, "compress_filter", (void **)&filter));
                        }
                     }
                     else
                     {
                        RINOK(codecsInfo->CreateEncoder(i, "compress_coder2", (void **)&coder2));
                     }
                     break;
                  }
               }
               else
                  if (codec.DecoderIsAssigned)
                  {
                     if (codec.IsSimpleCodec())
                     {
                        HRESULT result = codecsInfo->CreateDecoder(i, "compress_coder", (void **)&coder);
                        if (result != S_OK && result != E_NOINTERFACE && result != CLASS_E_CLASSNOTAVAILABLE)
                           return result;
                        if (!coder)
                        {
                           RINOK(codecsInfo->CreateDecoder(i, "compress_filter", (void **)&filter));
                        }
                     }
                     else
                     {
                        RINOK(codecsInfo->CreateDecoder(i, "compress_coder2", (void **)&coder2));
                     }
                     break;
                  }
            }
         }

         if (onlyCoder && filter)
         {
            filter_coder *coderSpec = new filter_coder;
            coder = coderSpec;
            coderSpec->Filter = filter;
         }
         return S_OK;
   }

   HRESULT CreateCoder(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::coder_interface * &coder,
      ::libcompress::coder2_interface * &coder2,
      bool encode)
   {
      ::libcompress::filter_interface * filter = NULL;
      return CreateCoder(
         codecsInfo, externalCodecs,
         methodId,
         filter, coder, coder2, encode, true);
   }

   HRESULT CreateCoder(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::coder_interface * &coder, bool encode)
   {
//      ::libcompress::filter_interface * filter = NULL;
      ::libcompress::coder2_interface * coder2 = NULL;
      return CreateCoder(
         codecsInfo, externalCodecs,
         methodId,
         coder, coder2, encode);
   }

   HRESULT CreateFilter(
      ::libcompress::codecs_info_interface *codecsInfo, const array<codec_info_ex> *externalCodecs,
      method_id methodId,
      ::libcompress::filter_interface * &filter,
      bool encode)
   {
      ::libcompress::coder_interface * coder = NULL;
      ::libcompress::coder2_interface * coder2 = NULL;
      return CreateCoder(
         codecsInfo, externalCodecs,
         methodId,
         filter, coder, coder2, encode, false);
   }


} // namespace libcompress
