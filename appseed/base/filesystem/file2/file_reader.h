#pragma once


namespace file
{

   class writer;
   class reader;


   typedef smart_pointer < reader > reader_sp;


   class CLASS_DECL_BASE reader :
      virtual public stream_buffer_base
   {
   public:


      reader();
      virtual ~reader();


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual file_position find(const void * pFind, ::primitive::memory_size size, const file_position * limit);

      virtual void transfer_to(writer & writer, ::primitive::memory_size uiBufferSize = 1024 * 1024);

      virtual void close();


      virtual file_position get_position() const;

      file_position tellg() { return get_position(); }

   };


   typedef reader readable;

   CLASS_DECL_BASE HRESULT read(reader * preader, void * data, ::primitive::memory_size * size);
   CLASS_DECL_BASE HRESULT read_false(reader * preader, void * data, ::primitive::memory_size size);
   CLASS_DECL_BASE HRESULT read_fail(reader * preader, void * data, ::primitive::memory_size size);


} // namespace file







