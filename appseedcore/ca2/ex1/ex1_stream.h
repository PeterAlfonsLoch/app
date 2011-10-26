#pragma once


namespace ex1
{


   class CLASS_DECL_ca stream :
      virtual public reader,
      virtual public writer
   {
   public:

      
      stream();
      stream(reader * preader, writer * pwriter);
      stream(const reader & reader, const writer & pwriter);
      stream(const stream & stream);
      virtual ~stream();

      
      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();

   };


} // namespace ex1


