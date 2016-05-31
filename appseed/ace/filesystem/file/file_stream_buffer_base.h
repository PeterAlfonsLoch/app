#pragma once


namespace file
{


    enum e_buffer
    {
       buffer_read, 
       buffer_write, 
       buffer_commit,
       buffer_check
    };




   class exception;
   struct file_status;


   class CLASS_DECL_ACE stream_buffer_base :
      virtual public ::object,
      virtual public ::file::seekable,
      virtual public ::file::writer_flush
   {
   public:


      stream_buffer_base();
      virtual ~stream_buffer_base();

      virtual void * get_internal_data();
      virtual const void * get_internal_data() const;
      virtual memory_size_t get_internal_data_size() const;
      virtual bool set_internal_data_size(memory_size_t c);
      virtual bool increase_internal_data_size(memory_size_t c);

   };



} // namespace file






