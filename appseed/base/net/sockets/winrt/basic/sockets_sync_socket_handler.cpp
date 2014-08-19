#include "framework.h"

namespace sockets
{

   sync_socket_handler::sync_socket_handler(::axis::application * papp, logger * plog) :
      element(papp),
      m_handler(papp, plog),
      m_file(papp)
   {
      m_psocket            = NULL;
      m_iDefaultTimeout    = 60;
   }

   sync_socket_handler::~sync_socket_handler()
   {
   }

   void sync_socket_handler::handle(socket * psocket)
   {
      if(m_psocket != NULL)
         throw simple_exception(get_app()); // busy
      m_psocket = psocket;
      m_psocket->m_pcallback = this;
      m_handler.add(m_psocket);
   }


   void sync_socket_handler::OnRawData(socket * psocket, void * pdata, size_t len)
   {
      if(m_psocket == psocket)
      {
         m_file.write(pdata, len);
      }
   }

   void sync_socket_handler::write(string &str)
   {
      m_psocket->write(str);
   }

   void sync_socket_handler::write(void * pdata, ::primitive::memory_size len)
   {
      m_psocket->write((char *) pdata, len);
   }

   ::primitive::memory_size sync_socket_handler::read(void * pdata, ::primitive::memory_size len)
   {
      while(m_file.get_size() < len && m_handler.get_count() > 0)
      {
         m_handler.select(8, 0);
      }
      return m_file.remove_begin(pdata, len);
   }

   string sync_socket_handler::read_string()
   {
      string str;
      m_file.to_string(str);
      return str;
   }

   string sync_socket_handler::read_line()
   {
      string str;
      char ch;
      while(m_file.read(&ch, 1) > 0)
      {
         if(ch == '\0')
         {
            return str;
         }
         str += ch;
         if(ch == '\r' || ch == '\n')
         {
            if(m_file.read(&ch, 1) <= 0)
               break;
            if(ch == '\r' || ch == '\n')
            {
               str += ch;
               return str;
            }
            else
            {
               m_file.seek(-1, ::file::seek_current);
               return str;
            }
         }
      }
      return str;
   }

   void sync_socket_handler::read_payload_v1(string & xml_payload, int iTimeout)
   {
      UNREFERENCED_PARAMETER(xml_payload);
      if(iTimeout < 0)
         iTimeout = m_iDefaultTimeout;
      ::primitive::memory_size uiLen = 0;
      if(read(&uiLen, 4) != 4)
         throw simple_exception(get_app());
      ntohl((u_long) uiLen);
      primitive::memory memory;
      memory.allocate(uiLen);
      if(read(memory, uiLen) != uiLen)
         throw simple_exception(get_app());
   }

   void sync_socket_handler::write_payload_v1(const char * xml_payload, int iTimeout)
   {
      if(iTimeout < 0)
         iTimeout = m_iDefaultTimeout;
      strsize uiLen = strlen(xml_payload);
      uint32_t wf_total_length = htonl((u_long) uiLen);
      write(&wf_total_length, 4);
      write( (char *) xml_payload, uiLen);
   }

} // namespace sockets
