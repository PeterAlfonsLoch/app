#pragma once


namespace file
{


   class CLASS_DECL_ACE byte_stream :
      virtual public byte_ostream,
      virtual public byte_istream,
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

      virtual file_position_t get_position() const;

   };


} // namespace file


