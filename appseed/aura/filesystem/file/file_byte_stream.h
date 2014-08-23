#pragma once


namespace file
{


   class CLASS_DECL_AXIS byte_stream :
      virtual public byte_output_stream,
      virtual public byte_input_stream,
      virtual public stream
   {
   public:

      
      byte_stream();
      byte_stream(stream_buffer * pbuffer);
      byte_stream(const stream & stream);
      virtual ~byte_stream();

      
      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();

      virtual file_position get_position() const;

   };


} // namespace file


