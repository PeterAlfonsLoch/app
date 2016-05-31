#pragma once


namespace file
{


   class CLASS_DECL_ACE plain_text_stream_string_buffer :
      virtual public plain_text_stream
   {
   public:


      string_buffer_sp        m_spstringbuffer;


      plain_text_stream_string_buffer(::ace::application * papp = NULL);
      virtual ~plain_text_stream_string_buffer();

      string str() const;

      operator const char *() const;

   };


} // namespace file


