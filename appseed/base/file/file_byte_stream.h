#pragma once


namespace file
{


   class CLASS_DECL_c byte_stream :
      virtual public output_stream,
      virtual public input_stream,
      virtual public stream
   {
   public:

      
      byte_stream();
      byte_stream(reader * preader, writer * pwriter);
      byte_stream(stream_buffer * pbuffer);
      byte_stream(const stream & stream);
      virtual ~byte_stream();

      
      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();

   };


} // namespace file


