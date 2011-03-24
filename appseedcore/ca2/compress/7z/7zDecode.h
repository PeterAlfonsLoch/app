// 7zDecode.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace n7z 
{

   struct CBindInfoEx: public ::compress::coder_mixer::CBindInfo
   {
      base_array<::compress::method_id> CoderMethodIDs;
      void remove_all()
      {
         CBindInfo::remove_all();
         CoderMethodIDs.remove_all();
      }
   };

   class CDecoder
   {
      bool _bindInfoExPrevIsDefined;
      CBindInfoEx _bindInfoExPrev;

      bool _multiThread;
      ::compress::coder_mixer::CCoderMixer2MT *_mixerCoderMTSpec;
      ::compress::coder_mixer::CCoderMixer2 *_mixerCoderCommon;

      ::ca::smart_pointer<::compress::coder2_interface> _mixerCoder;
      base_array<::ca::smart_pointer<::ca::ca> > _decoders;
      // array_ptr_alloc<::ca::smart_pointer<::compress::coder2_interface> > _decoders2;
   public:
      CDecoder(bool multiThread);
      HRESULT Decode(
         ::compress::codecs_info_interface *codecsInfo, const base_array<::compress::codec_info_ex> *externalCodecs,
         ex1::input_stream *inStream,
         uint64 startPos,
         const uint64 *packSizes,
         const CFolder &folder,
         ::ex1::writer *outStream,
         ::compress::progress_info_interface *compressProgress,
         ::crypto::get_text_password_interface *getTextPasswordSpec, bool &passwordIsDefined,
         bool mtMode, uint32 numThreads
         );
   };

} // namespace n7z

