#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 stream_base :
      virtual public ::ca2::object
   {
   public:


      enum e_open
      {
         mode_read               = (int32_t) 0x00001,
         mode_write              = (int32_t) 0x00002,
         mode_read_write         = (int32_t) 0x00003,
         shareCompat             = (int32_t) 0x00000,
         shareExclusive          = (int32_t) 0x00010,
         shareDenyWrite          = (int32_t) 0x00020,
         shareDenyRead           = (int32_t) 0x00030,
         shareDenyNone           = (int32_t) 0x00040,
         modeNoInherit           = (int32_t) 0x00080,
         mode_create             = (int32_t) 0x01000,
         modeNoTruncate                      = (int32_t) 0x02000,
         type_text                           = (int32_t) 0x04000, // type_text and type_binary are used in
         type_binary                         = (int32_t) 0x08000, // derived classes only
         defer_create_directory              = (int32_t) 0x10000,
         hint_unknown_length_supported       = (int32_t) 0x20000,
         binary                  = type_binary,
         out                     = mode_write
      };


   };


} // namespace ca2
