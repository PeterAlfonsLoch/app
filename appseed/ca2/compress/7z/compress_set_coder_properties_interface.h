// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace libcompress
{

   namespace coder
   {
      enum e_prop
      {
         prop_default = 0,
         prop_dictionary_size,
         prop_UsedMemorySize,
         prop_Order,
         prop_BlockSize,
         prop_PosStateBits,
         prop_LitContextBits,
         prop_LitPosBits,
         prop_NumFastBytes,
         prop_MatchFinder,
         prop_MatchFinderCycles,
         prop_NumPasses,
         prop_Algorithm,
         prop_NumThreads,
         prop_EndMarker
      };
   };


   //////////////////////
   // It's for DLL file
   enum e_method_prop
   {
      method_prop_ID,
      method_prop_Name,
      method_prop_Decoder,
      method_prop_Encoder,
      method_prop_InStreams,
      method_prop_OutStreams,
      method_prop_Description,
      method_prop_DecoderIsAssigned,
      method_prop_EncoderIsAssigned
   };



   class CLASS_DECL_ca set_coder_properties_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetCoderProperties(const int32_t * propIDs, const var * props, uint32 numProps) = 0;
   };

} // namespace libcompress
