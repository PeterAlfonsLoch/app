#pragma once


namespace ex1
{


   class CLASS_DECL_ca stream_base :
      virtual public radix::object
   {
   public:


      enum e_open
      {
         mode_read               = (int) 0x00001,
         mode_write              = (int) 0x00002,
         mode_read_write         = (int) 0x00003,
         shareCompat             = (int) 0x00000,
         shareExclusive          = (int) 0x00010,
         shareDenyWrite          = (int) 0x00020,
         shareDenyRead           = (int) 0x00030,
         shareDenyNone           = (int) 0x00040,
         modeNoInherit           = (int) 0x00080,
         mode_create             = (int) 0x01000,
         modeNoTruncate                      = (int) 0x02000,
         type_text                           = (int) 0x04000, // type_text and type_binary are used in
         type_binary                         = (int) 0x08000, // derived classes only
         defer_create_directory              = (int) 0x10000,
         hint_unknown_length_supported       = (int) 0x20000,
         binary                  = type_binary,
         out                     = mode_write
      };


   };


} // namespace ex1