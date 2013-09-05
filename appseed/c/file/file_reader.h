#pragma once


namespace file
{

   class writer;
   class reader;


   typedef smart_pointer < reader > reader_sp;


   class CLASS_DECL_c reader :
      virtual public object
   {
   public:


      reader();
      virtual ~reader();


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual file_position find(const void * pFind, ::primitive::memory_size size, const file_position * limit);

      virtual void write_to(writer & writer);

      virtual void close();




   };


   typedef reader readable;


   CLASS_DECL_c HRESULT read_reader(reader * stream, void * data, ::primitive::memory_size * size);
   CLASS_DECL_c HRESULT read_reader_false(reader * stream, void * data, ::primitive::memory_size size);
   CLASS_DECL_c HRESULT read_reader_fail(reader * stream, void * data, ::primitive::memory_size size);

} // namespace file







