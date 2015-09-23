#pragma once


namespace file
{


   class ostream;

   typedef smart_pointer < ostream > ostream_sp;


   class CLASS_DECL_AURA ostream :
      virtual public stream_base,
      virtual public writer
   {
   public:


      ostream();
      ostream(const char * lpszFileName, uint32_t nOpenFlags, ::aura::application * papp = ::get_thread_app());
      ostream(stream_buffer * pwriter);
      ostream(const ostream & pwriter);
      virtual ~ostream();

      virtual void write_from_hex(const void *lpBuf,memory_size_t nCount);
      virtual void write(const void *lpBuf, memory_size_t nCount);
      virtual void write(const void *lpBuf, memory_size_t nCount, memory_size_t * dwWritten);
      template < typename T >
      void full_write(const T & t) { write(&t, sizeof(T)); }

      //virtual void read(reader & reader);

      ostream & operator = (const ostream & writer);

      virtual bool is_writer_null();
      virtual bool is_writer_set();

      virtual void close();

      virtual void flush();

      virtual void set_length(file_size_t len);

      using stream_base::operator<< ;

      inline ostream & operator << (char ch                              ) { write(ch              ); return *this;}
      inline ostream & operator << (uchar uch                            ) { write(uch             ); return *this;}
      inline ostream & operator << (int16_t sh                           ) { write(sh              ); return *this;}
      inline ostream & operator << (uint16_t ui                          ) { write(ui              ); return *this;}
#ifdef WINDOWS
      inline ostream & operator << (unichar wch                          ) { write(wch             ); return *this;}
#endif
      inline ostream & operator << (bool b                               ) { write(b               ); return *this;}
      inline ostream & operator << (int32_t i                            ) { write(i               ); return *this;}
      inline ostream & operator << (uint32_t ui                          ) { write(ui              ); return *this;}
      inline ostream & operator << (int64_t i                            ) { write(i               ); return *this;}
      inline ostream & operator << (uint64_t ui                          ) { write(ui              ); return *this;}
#if defined(APPLEOS)
      inline ostream & operator << (unsigned long ui                     ) { write(ui              ); return *this;}
#endif
      inline ostream & operator << (float f                              ) { write(f               ); return *this;}
      inline ostream & operator << (double d                             ) { write(d               ); return *this;}
      inline ostream & operator << (const RECT & rect                    ) { write(rect            ); return *this;}
      inline ostream & operator << (const LPCRECT lpcrect                ) { write(lpcrect         ); return *this;}
      inline ostream & operator << (const SIZE & size                    ) { write(size            ); return *this;}
      inline ostream & operator << (const sp(type) info                  ) { write(info            ); return *this;}
      inline ostream & operator << (const serializable & serializable    ) { write(serializable    ); return *this;}
      inline ostream & operator << (const char * psz                     ) { write(psz             ); return *this;}
      inline ostream & operator << (const id & id                        ) { write(id              ); return *this;}
      inline ostream & operator << (const var & var                      ) { write(var             ); return *this;}
      inline ostream & operator << (const property & property            ) { write(property        ); return *this; }
      inline ostream & operator << (const string & str                   ) { write(str             ); return *this;}


      virtual void write_arbitrary(int32_t i);
      virtual void write_arbitrary(uint32_t ui);
      virtual void write_arbitrary(int64_t i);
      virtual void write_arbitrary(uint64_t ui);
      virtual void write_arbitrary(uint64_t ui, int signal);



      virtual void write (char ch);
      virtual void write (uchar uch);
      virtual void write (int16_t sh);
      virtual void write (uint16_t ui);
#ifdef WINDOWS
      virtual void write (unichar wch);
#endif
      virtual void write (bool b);
      virtual void write (int32_t i);
      virtual void write (uint32_t ui);
      virtual void write (int64_t i);
      virtual void write (uint64_t ui);
#if defined(APPLEOS)
      virtual void write (unsigned long ui);
#endif
      virtual void write (float f);
      virtual void write (double d);
      virtual void write (const RECT & rect);
      virtual void write (LPCRECT lpcrect);
      virtual void write (const SIZE & size);
      virtual void write (const sp(type) info);
      virtual void write (const serializable & serializable);
      virtual void write (const char * psz);
      virtual void write (const id & id);
      virtual void write (const var & var);
      virtual void write (const property & property);
      virtual void write (const string & str);

      file_position_t tellp() { return m_spbuffer->tell(); }
      ostream & seekp(file_position_t position) { m_spbuffer->seek_from_begin(position); return *this; }
      ostream & seekp(file_offset_t offset, e_seek eseek) { m_spbuffer->seek(offset, eseek); return *this; }


      ostream & put(char ch);

   };


} // namespace file



