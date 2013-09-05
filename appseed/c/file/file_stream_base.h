#pragma once


namespace file
{


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


   enum fmtflags
   {
      nofmtflags     = 0,
      boolalpha      = 0x00000001,
      showbase       = 0x00000002,
      showpoint      = 0x00000004,
      showpos        = 0x00000008,
      skipws         = 0x00000010,
      unitbuf        = 0x00000020,
      uppercase      = 0x00000040,
      dec            = 0x00000080,
      hex            = 0x00000100,
      oct            = 0x00000200,
      fixed          = 0x00000400,
      scientific     = 0x00000800,
      internal       = 0x00001000,
      left           = 0x00002000,
      right          = 0x00004000,
      adjustfield	   = left | right | internal,
      basefield	   = dec | oct | hex,
      floatfield	   = scientific | fixed,
   };



   class CLASS_DECL_c stream_base :
      virtual public object
   {
   public:




   };


} // namespace file






