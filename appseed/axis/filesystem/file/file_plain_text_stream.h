#pragma once


namespace file
{


   class CLASS_DECL_AXIS plain_text_stream :
      virtual public plain_text_output_stream,
      virtual public plain_text_input_stream,
      virtual public stream
   {
   public:

      
      plain_text_stream();
      plain_text_stream(stream_buffer * pbuffer);
      plain_text_stream(const stream & stream);
      virtual ~plain_text_stream();

      
      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();



   };


} // namespace file


