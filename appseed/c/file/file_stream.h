#pragma once


namespace file
{


   class CLASS_DECL_c stream :
      virtual public output_stream,
      virtual public input_stream
   {
   public:

      
      stream();
      stream(reader * preader, writer * pwriter);
      stream(stream_buffer * pbuffer);
      stream(const stream & stream);
      virtual ~stream();

      
      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();

   };


} // namespace file


