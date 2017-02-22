//#include "framework.h"


namespace file
{

   circular_file::circular_file(size_t size) :
      m_max(size),
      m_q(0),
      m_b(0),
      m_t(0),
      m_count(0)
   {

      m_memory.allocate(size * 2);

   }

   circular_file::circular_file(const circular_file& buffer)
   {
      operator =(buffer);
   }

   circular_file::~circular_file()
   {
   }


   void circular_file::write(const void * pdata, memory_size_t l)
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


   memory_size_t circular_file::read(void * pbuffer, memory_size_t l)
   {

      byte * s = (byte *) pbuffer;


      if (l > m_q)
      {
         throw io_exception(get_app(), "circular_file::read");
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


   bool circular_file::remove(size_t l)
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


   file_size_t circular_file::get_length() const
   {

      return m_q;

   }


   const char *circular_file::GetStart()
   {

      return (const char * ) (m_memory.get_data() + m_b);

   }


   size_t circular_file::GetL()
   {

      return (m_b + m_q > m_max) ? m_max - m_b : m_q;

   }


   size_t circular_file::Space()
   {
      return m_max - m_q;
   }


   uint_ptr circular_file::ByteCounter(bool clear)
   {
      if (clear)
      {
         uint_ptr x = m_count;
         m_count = 0;
         return x;
      }
      return m_count;
   }


   string circular_file::read_string(size_t l)
   {
      
      memory mem;
      
      mem.allocate(l + 1);

      if (!read(mem.get_data(), l)) // failed, debug printout in read() method
      {
      
         return "";

      }

      mem.get_data()[l] = '\0';

      return (const char * ) mem.get_data();

   }

   circular_file& circular_file::operator=(const circular_file& buffer)
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



