#pragma once


namespace ex1
{

   enum e_seek
   {
      seek_begin     = 0x0,
      seek_current   = 0x1,
      seek_end       = 0x2 
   };   


   class output_stream;
   class input_stream;


   class CLASS_DECL_ca stream_get_size :
      virtual public ::radix::object
   {
   public:
      virtual int GetSize(uint64 * psize) = 0;
   };

   class CLASS_DECL_ca out_stream_flush :
      virtual public ::radix::object
   {
   public:
      virtual int Flush() = 0;
   };


   class CLASS_DECL_ca reader :
      virtual public ex1::serializable
   {
   public:
      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);
      virtual void write(output_stream & ostream);
      virtual void read(input_stream & ostream);
      virtual uint64 find(const void * pFind, unsigned size, const uint64 * limit);
   };

   class CLASS_DECL_ca input_stream  :
      virtual public reader
   {
   public:
      input_stream();
      input_stream(reader * preader);
      virtual ~input_stream();

      reader * m_preader;

      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);

      input_stream & operator >> (char & ch);
      input_stream & operator >> (unsigned char & uch);
      input_stream & operator >> (short & sh);
      input_stream & operator >> (unsigned short & ush);
#if !core_level_1 && !core_level_2
      input_stream & operator >> (wchar_t & wch);
#endif
      input_stream & operator >> (bool & b);
      input_stream & operator >> (int & i);
      input_stream & operator >> (unsigned int & ui);
      input_stream & operator >> (long & l);
      input_stream & operator >> (unsigned long & ul);
      input_stream & operator >> (__int64 & i);
      input_stream & operator >> (unsigned __int64 & ui);
      input_stream & operator >> (float & f);
      input_stream & operator >> (double & d);
      input_stream & operator >> (LPRECT lprect);
      input_stream & operator >> (SIZE & size);
      input_stream & operator >> (::ca::type_info & info);
      input_stream & operator >> (serializable & serializable);

      virtual string get_location() const;

      virtual void seek_to_begin();
      virtual DWORD_PTR seek(INT_PTR offset, e_seek seekOrigin);

   };



   class CLASS_DECL_ca writer :
      virtual public ex1::serializable
   {
   public:
      virtual void write(const void *lpBuf, DWORD_PTR nCount);
      virtual void write(const void *lpBuf, DWORD_PTR nCount, DWORD_PTR * dwWritten);
      virtual void write(output_stream & ostream);
      virtual void read(input_stream & ostream);
   };


   class CLASS_DECL_ca output_stream :
      virtual public writer
   {
   public:
      output_stream();
      output_stream(writer * pwrite);
      virtual ~output_stream();

      writer * m_pwriter;

      virtual void write(const void * lpBuf, DWORD_PTR nCount);

      output_stream & operator << (char ch);
      output_stream & operator << (unsigned char uch);
      output_stream & operator << (short sh);
      output_stream & operator << (unsigned short ush);
#if !core_level_1 && !core_level_2
      output_stream & operator << (wchar_t wch);
#endif
      output_stream & operator << (bool b);
      output_stream & operator << (int i);
      output_stream & operator << (unsigned int ui);
      output_stream & operator << (long i);
      output_stream & operator << (unsigned long i);
      output_stream & operator << (__int64 i);
      output_stream & operator << (unsigned __int64 ui);
      output_stream & operator << (float f);
      output_stream & operator << (double d);
      output_stream & operator << (LPCRECT lpcrect);
      output_stream & operator << (SIZE & size);
      output_stream & operator << (::ca::type_info & info);
      output_stream & operator << (serializable & serializable);
      output_stream & operator << (const char * psz);

      virtual string get_location() const;

      virtual DWORD_PTR seek(INT_PTR offset, e_seek seekOrigin);
      void set_length(DWORD_PTR newSize);

   };

   class CLASS_DECL_ca io_stream :
      virtual public input_stream,
      virtual public output_stream
   {
   public:
      io_stream();
      io_stream(reader * preader, writer * pwriter);
      virtual ~io_stream();

      using output_stream::write;
      virtual void write(output_stream & ostream);

      using input_stream::read;
      virtual void read(input_stream & istream);

      virtual DWORD_PTR seek(INT_PTR offset, e_seek seekOrigin);

      virtual string get_location() const;
   };


   CLASS_DECL_ca HRESULT ReadStream(reader * stream, void *data, size_t *size);
   CLASS_DECL_ca HRESULT ReadStream_FALSE(reader * stream, void *data, size_t size);
   CLASS_DECL_ca HRESULT ReadStream_FAIL(reader * stream, void *data, size_t size);
   CLASS_DECL_ca HRESULT WriteStream(writer * stream, const void *data, size_t size);

} // namespace ex1




