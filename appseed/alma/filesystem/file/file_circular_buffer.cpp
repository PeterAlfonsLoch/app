#include "framework.h"


namespace file
{

   circular_buffer::circular_buffer(size_t size) :
      m_max(size),
      m_q(0),
      m_b(0),
      m_t(0),
      m_count(0)
   {

      m_memory.allocate(size * 2);

   }

   circular_buffer::circular_buffer(const circular_buffer& buffer)
   {
      operator =(buffer);
   }

   circular_buffer::~circular_buffer()
   {
   }


   void circular_buffer::write(const void * pdata, ::primitive::memory_size l)
   {

      const char * s = (const char *) pdata;

      m_count += (uint_ptr) l;

      if (m_t + l > m_max) // block crosses circular border
      {
         size_t l1 = m_max - m_t; // size left until circular border crossing
         // always copy full block to buffer(m_memory.get_data()) + top pointer(m_t)
         // because we have doubled the buffer size for performance reasons
         memcpy(m_memory.get_data() + m_t, s, l);
         memcpy(m_memory.get_data(), s + l1, l - l1);
         m_t = l - l1;
         m_q += l;
      }
      else
      {
         memcpy(m_memory.get_data() + m_t, s, l);
         memcpy(m_memory.get_data() + m_max + m_t, s, l);
         m_t += l;
         if (m_t >= m_max)
            m_t -= m_max;
         m_q += l;
      }

   }


   ::primitive::memory_size circular_buffer::read(void * pbuffer, primitive::memory_size l)
   {

      byte * s = (byte *) pbuffer;


      if (l > m_q)
      {
         throw io_exception(get_app(), "circular_buffer::read");
      }

      if (m_b + l > m_max) // block crosses circular border
      {

         size_t l1 = m_max - m_b;


         if(s != NULL)
         {

            memcpy(s, m_memory.get_data() + m_b, l1);

            memcpy(s + l1, m_memory.get_data(), l - l1);

         }

         m_b = l - l1;

         m_q -= l;

      }
      else
      {

         if(s != NULL)
         {

            memcpy(s, m_memory.get_data() + m_b, l);

         }

         m_b += l;

         if (m_b >= m_max)
            m_b -= m_max;

         m_q -= l;

      }

      if (!m_q)
      {

         m_b = m_t = 0;

      }

      return l;

   }


   bool circular_buffer::remove(size_t l)
   {

      try
      {

         return read(NULL, l) == l;

      }
      catch(...)
      {

         return false;

      }

   }


   file_size circular_buffer::get_length() const
   {

      return m_q;

   }


   const char *circular_buffer::GetStart()
   {

      return (const char * ) (m_memory.get_data() + m_b);

   }


   size_t circular_buffer::GetL()
   {

      return (m_b + m_q > m_max) ? m_max - m_b : m_q;

   }


   size_t circular_buffer::Space()
   {
      return m_max - m_q;
   }


   uint_ptr circular_buffer::ByteCounter(bool clear)
   {
      if (clear)
      {
         uint_ptr x = m_count;
         m_count = 0;
         return x;
      }
      return m_count;
   }


   string circular_buffer::read_string(size_t l)
   {
      char *sz = new char[l + 1];
      if (!read(sz, l)) // failed, debug printout in read() method
      {
         delete[] sz;
         return "";
      }
      sz[l] = 0;
      string tmp = sz;
      delete[] sz;
      return tmp;
   }

   circular_buffer& circular_buffer::operator=(const circular_buffer& buffer)
   {
      if(&buffer != this)
      {
         m_memory = buffer.m_memory;
         m_q = buffer.m_q;
         m_b = buffer.m_b;
         m_t = buffer.m_t;
         m_count = buffer.m_count;
      }
      return *this;
   }


} // namespace file



