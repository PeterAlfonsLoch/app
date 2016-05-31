#pragma once


namespace file
{

   class writer;
   class reader;
   class serializable;


   typedef smart_pointer < reader > istream_sp;


   class CLASS_DECL_ACE istream :
      virtual public stream_base,
      virtual public reader
   {
   public:


      memory_size_t   m_gcount;


      istream();
      istream(stream_buffer * preader);
      istream(const istream & preader);
      virtual ~istream();



      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      virtual void full_read(void *lpBuf, memory_size_t nCount);
      template < typename TYPE >
      void full_fill(TYPE & t)
      {
         full_read(&t, sizeof(t));
      }
      virtual void full_fill(::primitive::memory_base & m);

      istream & operator = (const istream & ostream);

      virtual bool is_reader_null();
      virtual bool is_reader_set();

      virtual void read_to_hex(string & str, file_position_t iStart = -1, file_position_t iEnd = -1);


      inline istream & operator >> (bool            & b               ) { read(b              ); return *this; }
      inline istream & operator >> (char            & ch              ) { read(ch             ); return *this; }
      inline istream & operator >> (uchar           & uch             ) { read(uch            ); return *this; }
#ifdef WINDOWS
      inline istream & operator >> (unichar         & wch             ) { read(wch            ); return *this; }
#endif
      inline istream & operator >> (int16_t         & sh              ) { read(sh             ); return *this; }
      inline istream & operator >> (uint16_t        & ui              ) { read(ui             ); return *this; }
      inline istream & operator >> (int32_t         & i               ) { read(i              ); return *this; }
      inline istream & operator >> (uint32_t        & ui              ) { read(ui             ); return *this; }
      inline istream & operator >> (int64_t         & i               ) { read(i              ); return *this; }
      inline istream & operator >> (uint64_t        & ui              ) { read(ui             ); return *this; }
#ifdef APPLEOS
      inline istream & operator >> (unsigned long   & ui              ) { read(ui             ); return *this; }
#endif
      inline istream & operator >> (float           & f               ) { read(f              ); return *this; }
      inline istream & operator >> (double          & d               ) { read(d              ); return *this; }
      inline istream & operator >> (LPRECT            lprect          ) { read(lprect         ); return *this; }
      inline istream & operator >> (SIZE            & size            ) { read(size           ); return *this; }
      inline istream & operator >> (sp(type)        & info            ) { read(info           ); return *this; }
      inline istream & operator >> (serializable    & serializable    ) { read(serializable   ); return *this; }
      inline istream & operator >> (id              & id              ) { read(id             ); return *this; }
      inline istream & operator >> (var             & var             ) { read(var            ); return *this; }
      inline istream & operator >> (property        & property        ) { read(property       ); return *this; }
      inline istream & operator >> (string          & str             ) { read(str            ); return *this; }


      virtual void read_arbitrary(int32_t & i);
      virtual void read_arbitrary(uint32_t & ui);
      virtual void read_arbitrary(int64_t & i);
      virtual void read_arbitrary(uint64_t & ui);


      virtual void read (bool & b);
      virtual void read (char & ch);
      virtual void read (uchar & uch);
#ifdef WINDOWS
      virtual void read (unichar & wch);
#endif
      virtual void read (int16_t & sh);
      virtual void read (uint16_t & ui);
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
      virtual void read (property & property);
      virtual void read (string & str);

      virtual istream & getline(char * sz, strsize n);
      virtual int get();
      virtual int peek();

      memory_size_t gcount() { return m_gcount; }
      file_position_t tellg() { return m_spbuffer->tell(); }
      istream & seekg(file_position_t position) { m_spbuffer->seek_from_begin(position); return *this; }
      istream & seekg(file_offset_t offset, e_seek eseek) { m_spbuffer->seek(offset, eseek); return *this; }

      file_size_t get_left() { return m_spbuffer->get_length() - m_spbuffer->get_position(); }

   };


} // namespace file





