#pragma once


namespace file
{


   class CLASS_DECL_c plain_text_stream_string_buffer :
      virtual public plain_text_stream,
      virtual public string_buffer
   {
   public:

      plain_text_stream_string_buffer();
      virtual ~plain_text_stream_string_buffer();

   };


} // namespace file


