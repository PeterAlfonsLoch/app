#pragma once


namespace file
{


   class stream_buffer;

   typedef sp(stream_buffer) buffer_sp;


   enum e_iostate
   {
      goodbit        = 0x00,
	   eofbit         = 0x01,
	   failbit        = 0x02,
	   badbit         = 0x04,
	   _Hardfail      = 0x10
   };


   enum e_open
   {
      mode_read                        = (int32_t) 0x00001,
      mode_write                       = (int32_t) 0x00002,
      mode_read_write                  = (int32_t) 0x00003,
      share_compat                     = (int32_t) 0x00000,
      share_exclusive                  = (int32_t) 0x00010,
      share_deny_write                 = (int32_t) 0x00020,
      share_deny_read                  = (int32_t) 0x00030,
      share_deny_none                  = (int32_t) 0x00040,
      mode_no_inherit                  = (int32_t) 0x00080,
      mode_create                      = (int32_t) 0x01000,
      mode_no_truncate                 = (int32_t) 0x02000,
      type_text                        = (int32_t) 0x04000, // type_text and type_binary are used in
      type_binary                      = (int32_t) 0x08000, // derived classes only
      defer_create_directory           = (int32_t) 0x10000,
      hint_unknown_length_supported    = (int32_t) 0x20000,
      binary                           = type_binary,
      out                              = mode_write
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
      floatfield	   = scientific | fixed
   };



   class CLASS_DECL_BASE stream_base :
      virtual public seekable
   {
   public:


      buffer_sp               m_spbuffer;
      e_iostate               m_iostate;

      
      stream_base();
      stream_base(sp(stream_buffer) pbuffer);
      stream_base(const stream_base & stream);
      virtual ~stream_base();


      e_iostate rdstate() const
		{
		   return m_iostate;
		}

      bool operator ! ()
      {
         return fail();
      }

      bool bad() const
      {
         return (m_iostate & badbit) != 0;
      }

      bool fail() const
      {
         return ((int) m_iostate & ((int) badbit | (int) failbit)) != 0;
      }

      bool eof() const
      {
         return (m_iostate & eofbit) != 0;
      }

      bool good() const
      {
         return m_iostate == goodbit;
      }

      void setstate(e_iostate state)
      {
         clear((e_iostate) (rdstate() | state));
      }

      void clear(e_iostate state = goodbit)
      {
         m_iostate = state;
      }

      virtual string GetFilePath() const;

      string fileName() { return GetFilePath(); }

      virtual void close();

      using seekable::seek;
      virtual file_position seek(file_offset offset, e_seek eseek);

   };


} // namespace file






