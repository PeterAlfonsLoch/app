// CoderMixer.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{
   namespace coder_mixer
   {

      struct coder_info
      {
        sp(::libcompress::coder_interface) Coder;
        sp(::ca::reader) InStream;
        sp(::ca::writer) OutStream;
        sp(::libcompress::progress_info_interface) Progress;

        uint64 InSizeValue;
        uint64 OutSizeValue;
        bool InSizeAssigned;
        bool OutSizeAssigned;

        void ReInit()
        {
          InSizeAssigned = OutSizeAssigned = false;
        }

        void SetCoderInfo(const uint64 *inSize, const uint64 *outSize);
      };

   } // namespace coder_mixer

} // namespace libcompress
