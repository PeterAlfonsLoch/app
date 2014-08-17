#pragma once
// transposed 2011-04-08
// originally from C++ sockets library tcp_socket::circular_buffer


namespace file
{

   /** buffer class containing one read/write circular buffer.
   \ingroup internal */

   class circular_buffer :
      virtual public stream_buffer
   {
   protected:


      primitive::memory m_memory;
      size_t m_max;
      size_t m_q;
      size_t m_b;
      size_t m_t;
      uint_ptr m_count;


   public:


      circular_buffer(size_t size);
      circular_buffer(const circular_buffer& buffer);
      circular_buffer& operator=(const circular_buffer& buffer);
      ~circular_buffer();

      /** append l bytes from p to buffer */
      using ::file::stream_buffer::write;
      void write(const void * pdata, ::primitive::memory_size l);
      /** copy l bytes from buffer to dest */
      using ::file::stream_buffer::read;
      ::primitive::memory_size read(void * pbuffer, ::primitive::memory_size l);
      /** skip l bytes from buffer */
      bool remove(size_t l);
      /** read l bytes from buffer, returns as string. */
      using ::file::stream_buffer::read_string;
      string read_string(size_t l);

      /** total buffer length */
      file_size get_length() const;
      /** pointer to circular buffer beginning */
      const char *GetStart();
      /** return number of bytes from circular buffer beginning to buffer physical end */
      size_t GetL();
      /** return free space in buffer, number of bytes until buffer overrun */
      size_t Space();

      /** return total number of bytes written to this buffer, ever */
      uint_ptr ByteCounter(bool clear = false);

   };


} // namespace file




