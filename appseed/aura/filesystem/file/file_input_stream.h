#pragma once


namespace file
{

   class writer;
   class reader;
   class serializable;


   typedef smart_pointer < reader > input_stream_sp;


   class CLASS_DECL_AURA input_stream :
      virtual public stream_base,
      virtual public reader
   {
   public:


      ::primitive::memory_size      m_gcount;


      input_stream();
      input_stream(const char * lpszFileName, uint32_t nOpenFlags, sp(::aura::application) papp = ::get_thread_app());
      input_stream(stream_buffer * preader);
      input_stream(const input_stream & preader);
      virtual ~input_stream();



      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void full_read(void *lpBuf, ::primitive::memory_size nCount);
      template < typename TYPE >
      void full_fill(TYPE & t)
      {
         full_read(&t, sizeof(t));
      }
      virtual void full_fill(::primitive::memory_base & m);

      input_stream & operator = (const input_stream & ostream);

      virtual bool is_reader_null();
      virtual bool is_reader_set();

      virtual void read_to_hex(string & str, file_position iStart = -1, file_position iEnd = -1);


      inline input_stream & operator >> (bool            & b               ) { read(b              ); return *this; }
      inline input_stream & operator >> (char            & ch              ) { read(ch             ); return *this; }
      inline input_stream & operator >> (uchar           & uch             ) { read(uch            ); return *this; }
      inline input_stream & operator >> (wchar_t         & wch             ) { read(wch            ); return *this; }
      inline input_stream & operator >> (int16_t         & sh              ) { read(sh             ); return *this; }
      inline input_stream & operator >> (uint16_t        & ui              ) { read(ui             ); return *this; }
      inline input_stream & operator >> (int32_t         & i               ) { read(i              ); return *this; }
      inline input_stream & operator >> (uint32_t        & ui              ) { read(ui             ); return *this; }
      inline input_stream & operator >> (int64_t         & i               ) { read(i              ); return *this; }
      inline input_stream & operator >> (uint64_t        & ui              ) { read(ui             ); return *this; }
#ifdef APPLEOS
      inline input_stream & operator >> (unsigned long   & ui              ) { read(ui             ); return *this; }
#endif
      inline input_stream & operator >> (float           & f               ) { read(f              ); return *this; }
      inline input_stream & operator >> (double          & d               ) { read(d              ); return *this; }
      inline input_stream & operator >> (LPRECT            lprect          ) { read(lprect         ); return *this; }
      inline input_stream & operator >> (SIZE            & size            ) { read(size           ); return *this; }
      inline input_stream & operator >> (sp(type)        & info            ) { read(info           ); return *this; }
      inline input_stream & operator >> (serializable    & serializable    ) { read(serializable   ); return *this; }
      inline input_stream & operator >> (id              & id              ) { read(id             ); return *this; }
      inline input_stream & operator >> (var             & var             ) { read(var            ); return *this; }
      inline input_stream & operator >> (string          & str             ) { read(str            ); return *this; }


      virtual void read_arbitrary(int32_t & i);
      virtual void read_arbitrary(uint32_t & ui);
      virtual void read_arbitrary(int64_t & i);
      virtual void read_arbitrary(uint64_t & ui);


      virtual void read (bool & b);
      virtual void read (char & ch);
      virtual void read (uchar & uch);
      virtual void read (wchar_t & wch);
      virtual void read (int16_t & sh);
      virtual void read (uint16_t & uint16_t);
      virtual void read (int32_t & i);
      virtual void read (uint32_t & ui);
      virtual void read (int64_t & i);
      virtual void read (uint64_t & ui);
#ifdef APPLEOS
      virtual void read (unsigned long & ui);
#endif
      virtual void read (float & f);
      virtual void read (double & d);
      virtual void read (LPRECT lprect);
      virtual void read (SIZE & size);
      virtual void read (sp(type) info);
      virtual void read (serializable & serializable);
      virtual void read (id & id);
      virtual void read (var & var);
      virtual void read (string & str);

      virtual input_stream & getline(char * sz, strsize n);
      virtual int get();
      virtual int peek();

      virtual void close();

      ::primitive::memory_size gcount() { return m_gcount; }
      ::file_position tellg() { return m_spbuffer->tell(); }
      input_stream & seekg(file_position position) { m_spbuffer->seek_from_begin(position); return *this; }
      input_stream & seekg(file_offset offset, e_seek eseek) { m_spbuffer->seek(offset, eseek); return *this; }

      ::file_size get_left() { return m_spbuffer->get_length() - m_spbuffer->get_position(); }

      virtual bool is_open();

   };


} // namespace file





