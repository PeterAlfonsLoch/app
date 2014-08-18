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


   class CLASS_DECL_BASE stream_buffer_base :
      virtual public ::object,
      virtual public ::file::seekable,
      virtual public ::file::writer_flush
   {
   public:


      stream_buffer_base();
      virtual ~stream_buffer_base();

      virtual void * get_internal_data();
      virtual ::primitive::memory_size get_internal_data_size();
      virtual bool set_internal_data_size(::primitive::memory_size c);
      virtual bool increase_internal_data_size(::primitive::memory_size c);

   };



} // namespace file






