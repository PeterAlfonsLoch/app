#pragma once

//#include <iostream>

//std::iostate

namespace ca
{

	enum e_iostate
   {
      goodbit        = 0x00,
	   eofbit         = 0x01,
	   failbit        = 0x02,
	   badbit         = 0x04,
	   _Hardfail      = 0x10,
   };

   CLASS_DECL_ca typedef base_enum < e_iostate, goodbit > iostate;

   class plain_text_output_stream;
   class plain_text_input_stream;

   class CLASS_DECL_ca plain_text_stream_base :
      virtual public stream_base
   {
   public:

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

      fmtflags          m_fmtflags;
      iostate           m_iostate;


      plain_text_stream_base();
      virtual ~plain_text_stream_base();


      fmtflags setf(fmtflags flagsAdd);
      fmtflags setf(fmtflags flagsAdd, fmtflags flagsRemove);


      iostate rdstate() const;
      void setstate(iostate state);
      void clear(iostate state = goodbit);

      bool bad() const;
      bool fail() const;
      bool eof() const;
      bool good() const;

   };


   class CLASS_DECL_ca plain_text_input_stream :
      virtual public reader,
      virtual public plain_text_stream_base
   {
   public:


      plain_text_input_stream();
      plain_text_input_stream(reader * preader);
      plain_text_input_stream(const plain_text_input_stream & istream);
      virtual ~plain_text_input_stream();


      plain_text_input_stream & operator >> (bool & b);
      plain_text_input_stream & operator >> (char & ch);
      plain_text_input_stream & operator >> (uchar & uch);
      plain_text_input_stream & operator >> (wchar_t & wch);
      plain_text_input_stream & operator >> (int16_t & sh);
      plain_text_input_stream & operator >> (uint16_t & uint16_t);
      plain_text_input_stream & operator >> (int32_t & i);
      plain_text_input_stream & operator >> (uint32_t & ui);
      plain_text_input_stream & operator >> (int64_t & i);
      plain_text_input_stream & operator >> (uint64_t & ui);
      plain_text_input_stream & operator >> (float & f);
      plain_text_input_stream & operator >> (double & d);
      plain_text_input_stream & operator >> (LPRECT lprect);
      plain_text_input_stream & operator >> (SIZE & size);
      plain_text_input_stream & operator >> (::ca::type_info & info);
      plain_text_input_stream & operator >> (plain_text_serializable & writable);

      virtual string get_location() const;

      plain_text_input_stream & operator = (const plain_text_input_stream & istream);

      operator void * ()
      {
         return this;
      }

   };



   class CLASS_DECL_ca plain_text_output_stream :
      virtual public writer,
      virtual public plain_text_stream_base
   {
   public:


      plain_text_output_stream();
      plain_text_output_stream(writer * pwriter);
      plain_text_output_stream(const plain_text_output_stream & ostream);
      virtual ~plain_text_output_stream();


      plain_text_output_stream & operator << (bool b);
      plain_text_output_stream & operator << (char ch);
      plain_text_output_stream & operator << (uchar uch);
      plain_text_output_stream & operator << (wchar_t wch);
      plain_text_output_stream & operator << (int16_t sh);
      plain_text_output_stream & operator << (uint16_t uint16_t);
      plain_text_output_stream & operator << (int32_t i);
      plain_text_output_stream & operator << (uint32_t ui);
      plain_text_output_stream & operator << (int64_t i);
      plain_text_output_stream & operator << (uint64_t ui);
      plain_text_output_stream & operator << (float f);
      plain_text_output_stream & operator << (double d);
      plain_text_output_stream & operator << (LPCRECT lpcrect);
      plain_text_output_stream & operator << (SIZE & size);
      plain_text_output_stream & operator << (::ca::type_info & info);
      plain_text_output_stream & operator << (plain_text_serializable & serializable);
      plain_text_output_stream & operator << (const char * psz);

      plain_text_output_stream & raw_print(const string & str);

      virtual string get_location() const;

      plain_text_output_stream & operator = (const plain_text_output_stream & ostream);

      operator void * ()
      {
         return this;
      }

   };

   class CLASS_DECL_ca plain_text_stream :
      virtual public stream,
      virtual public plain_text_input_stream,
      virtual public plain_text_output_stream
   {
   public:


      plain_text_stream();
      plain_text_stream(const filesp & filesp);
      plain_text_stream(reader * preader, writer * pwriter);
      plain_text_stream(const plain_text_stream & stream);
      virtual ~plain_text_stream();


      plain_text_stream & operator = (const plain_text_stream & stream);


      virtual string get_location() const;


   };


/*
   CLASS_DECL_ca HRESULT ReadStream(reader * stream, void *data, uint64_t *size);
   CLASS_DECL_ca HRESULT ReadStream_FALSE(reader * stream, void *data, uint64_t size);
   CLASS_DECL_ca HRESULT ReadStream_FAIL(reader * stream, void *data, uint64_t size);
   CLASS_DECL_ca HRESULT WriteStream(writer * stream, const void *data, uint64_t size);
   */

   template < class type_array >
   void plain_text_serializable_array < type_array >::write(plain_text_output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream << count;
      for(index index = 0; index < count; index++)
      {
         ostream << this->element_at(index);
      }
   }

   template < class type_array >
   void plain_text_serializable_array < type_array >::read(plain_text_input_stream & istream)
   {
      ::count count;
      istream >> count;
      type_array::set_size(count);
      for(index index = 0; index < count; index++)
      {
         istream >> this->element_at(index);
      }
      on_after_read();
   }

} // namespace ca




