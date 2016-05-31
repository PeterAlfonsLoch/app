#pragma once


namespace file
{

   class writer;
   class reader;


   typedef smart_pointer < reader > reader_sp;


   class CLASS_DECL_ACE reader :
      virtual public stream_buffer_base
   {
   public:


      reader();
      virtual ~reader();


      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      virtual file_position_t find(const void * pFind, memory_size_t size, const file_position_t * limit);

      virtual void transfer_to(writer & writer, memory_size_t uiBufferSize = 1024 * 1024);

      virtual file_position_t get_position() const;

      file_position_t tellg() { return get_position(); }

   };


   typedef reader readable;

   CLASS_DECL_ACE HRESULT read(reader * preader, void * data, memory_size_t * size);
   CLASS_DECL_ACE HRESULT read_false(reader * preader, void * data, memory_size_t size);
   CLASS_DECL_ACE HRESULT read_fail(reader * preader, void * data, memory_size_t size);


} // namespace file







