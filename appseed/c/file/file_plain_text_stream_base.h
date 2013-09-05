#pragma once

//#include <iostream>

//std::iostate

namespace file
{

	enum e_iostate
   {
      goodbit        = 0x00,
	   eofbit         = 0x01,
	   failbit        = 0x02,
	   badbit         = 0x04,
	   _Hardfail      = 0x10,
   };

   CLASS_DECL_c typedef base_enum < e_iostate, goodbit > iostate;

   class plain_text_output_stream;
   class plain_text_input_stream;


   class CLASS_DECL_c plain_text_stream_base :
      virtual public stream_base
   {
   public:


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


} // namespace file



