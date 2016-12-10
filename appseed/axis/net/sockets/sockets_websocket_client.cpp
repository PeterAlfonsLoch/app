#include "framework.h" // from "axis/net/net_sockets.h"
#include "axis/net/net_sockets.h"
#include "openssl/ssl.h"


/**
* Return the number of bytes required to store a variable-length unsigned
* 32-bit integer in base-128 varint encoding.
*
* \param v
*      Value to encode.
* \return
*      Number of bytes required.
*/
static inline size_t
uint32_size(uint32_t v)
{
   if (v < (1UL << 7)) {
      return 1;
   }
   else if (v < (1UL << 14)) {
      return 2;
   }
   else if (v < (1UL << 21)) {
      return 3;
   }
   else if (v < (1UL << 28)) {
      return 4;
   }
   else {
      return 5;
   }
}


/**
* Pack an unsigned 32-bit integer in base-128 varint encoding and return the
* number of bytes written, which must be 5 or less.
*
* \param value
*      Value to encode.
* \param[out] out
*      Packed value.
* \return
*      Number of bytes written to `out`.
*/
static inline size_t
uint32_pack(uint32_t value, uint8_t *out)
{
   unsigned rv = 0;

   if (value >= 0x80) {
      out[rv++] = value | 0x80;
      value >>= 7;
      if (value >= 0x80) {
         out[rv++] = value | 0x80;
         value >>= 7;
         if (value >= 0x80) {
            out[rv++] = value | 0x80;
            value >>= 7;
            if (value >= 0x80) {
               out[rv++] = value | 0x80;
               value >>= 7;
            }
         }
      }
   }
   /* assert: value<128 */
   out[rv++] = value;
   return rv;
}


CLASS_DECL_AXIS void websocket_prefix_varuint(memory & m, unsigned int ui)
{

   int iSize = uint32_size(ui);

   m.allocate_add_up(iSize);

   m.move(iSize);

   int iSize2 = uint32_pack(ui, m.get_data());

}


int client_send(memory & m, int fin, memory & memory, bool useMask)
{

   const uint8_t masking_key[4] = { 0x12, 0x34, 0x56, 0x78 };

   strsize len = memory.get_length();

   int64_t message_size = memory.get_size();

   int length = 2 + (message_size >= 126 ? 2 : 0) + (message_size >= 65536 ? 6 : 0) + (useMask ? 4 : 0) + message_size;

   m.allocate(length);

   byte * frame = (byte*)m.get_data();

   byte * header = (byte*)m.get_data();

   header[0] = 0x80 | fin;
   int iOffset = -1;
   if (false) {}
   else if (message_size < 126) {
      header[1] = (message_size & 0xff) | (useMask ? 0x80 : 0);
      
      if (useMask) {
         header[2] = masking_key[0];
         header[3] = masking_key[1];
         header[4] = masking_key[2];
         header[5] = masking_key[3];
         iOffset = 6;
      }
      else
      {
         iOffset = 2;
      }
   }
   else if (message_size < 65536) {
      header[1] = 126 | (useMask ? 0x80 : 0);
      header[2] = (message_size >> 8) & 0xff;
      header[3] = (message_size >> 0) & 0xff;
      if (useMask) {
         header[4] = masking_key[0];
         header[5] = masking_key[1];
         header[6] = masking_key[2];
         header[7] = masking_key[3];
         iOffset = 8;
      }
      else
      {
         iOffset = 4;
      }
   }
   else { // TODO: run coverage testing here
      header[1] = 127 | (useMask ? 0x80 : 0);
      header[2] = (message_size >> 56) & 0xff;
      header[3] = (message_size >> 48) & 0xff;
      header[4] = (message_size >> 40) & 0xff;
      header[5] = (message_size >> 32) & 0xff;
      header[6] = (message_size >> 24) & 0xff;
      header[7] = (message_size >> 16) & 0xff;
      header[8] = (message_size >> 8) & 0xff;
      header[9] = (message_size >> 0) & 0xff;
      if (useMask) {
         header[10] = masking_key[0];
         header[11] = masking_key[1];
         header[12] = masking_key[2];
         header[13] = masking_key[3];
         iOffset = 14;
      }
      else
      {
         iOffset = 10;
      }
   }
   memcpy(&frame[iOffset], memory.get_data(), memory.get_length());
   if (useMask)
   {
      for (index i = 0; i < memory.get_length(); i++)
      {
         frame[iOffset+i] ^= masking_key[i & 3];
      }
   }
   //memcpy(&frame[iOffset+ memory.get_length()],masking_key, 4);

   

   return m.get_size();

}

int client_send(memory & m, memory & memory)
{

   return client_send(m, 0x82, memory, true);

}

int client_send(memory & m, int fin, const char* src)
{

   strsize len = 0;

   if (src != NULL)
   {

      len = strlen(src);

   }

   int length = len
      + 1	//0x00
      + 1;	//0xFF

   if (len >= 127)
   {

      if (len >= 65536)
      {

         length += 8;

      }
      else
      {

         length += 2;

      }

   }

   m.allocate(length);

   char* frame = (char*)m.get_data();

   frame[0] = (char)fin;

   int iOffset;

   if (len >= 126)
   {

      if (len >= 65536)
      {

         iOffset = 10;

         frame[1] = 127;

         *((int64_t*)&frame[2]) = HTONLL(len);

      }
      else
      {

         iOffset = 4;

         frame[1] = 126;

         *((int16_t*)&frame[2]) = htons(len);

      }

   }
   else
   {

      iOffset = 2;

      frame[1] = len;

   }

   for (size_t i = 0; i < len; i++)
   {

      frame[iOffset + i] = src[i];//read src into frame

   }

   return m.get_size();

}


int client_send(memory & m, const char* src)
{

   return client_send(m, 0x82, src);

}

namespace sockets
{

   enum e_opcode {
      CONTINUATION = 0x0,
      TEXT_FRAME = 0x1,
      BINARY_FRAME = 0x2,
      CLOSE = 8,
      PING = 9,
      PONG = 0xa,
   } opcode;

   websocket_client::websocket_client(base_socket_handler& h) :
      object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h)
   {

      m_bUseMask = false;

      m_bRequestSent = false;

      m_bWebSocket = false;

      m_bTls = true;

      m_bExpectRequest = true;

   }


   websocket_client::websocket_client(base_socket_handler& h, const string & url_in, const string & strProtocol) :
      object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {

      m_bUseMask = false;

      m_strWebSocketProtocol = strProtocol;

      m_bRequestSent = false;

      m_bWebSocket = false;

      m_bTls = true;

      m_bExpectRequest = true;

      m_emethod = http_method_get;

   }


   //websocket_client::websocket_client(base_socket_handler& h, const string & host, port_t port, const string & url_in) :
   //   object(h.get_app()),
   //   base_socket(h),
   //   socket(h),
   //   stream_socket(h),
   //   tcp_socket(h),
   //   http_socket(h),
   //   http_tunnel(h),
   //   http_client_socket(h, url_in)
   //{

   //   m_bRequestSent = false;

   //   m_bWebSocket = false;

   //   m_bTls = true;

   //   m_bExpectRequest = true;

   //   m_emethod = http_method_get;

   //   UNREFERENCED_PARAMETER(host);

   //   UNREFERENCED_PARAMETER(port);

   //}


   websocket_client::~websocket_client()
   {
   }


   void websocket_client::step()
   {

      inheader("Host") = m_host;


//      if (!(bool)inattr("minimal_headers"))
      {
         //inheader("Accept") = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
         //inheader("Accept-Language") = "en-us,en;q=0.5";
         //if (m_pfile == NULL) // by the time, inline gzip decompression not yet implemented
         //{
         //   inheader(__id(accept_encoding)) = "gzip,deflate";
         //}
         //inheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
         inheader(__id(user_agent)) = MyUseragent();
      }
      //inheader("Content-Length") = 0;
      inheader("Upgrade") = "websocket";
      inheader("Connection") = "Upgrade";

      memory m;

      m.random_bytes(32);

      m_strBase64 = System.base64().encode(m);

      inheader("Sec-WebSocket-Key") = m_strBase64;
      inheader("Sec-WebSocket-Protocol") = m_strWebSocketProtocol;
      inheader("Sec-WebSocket-Version") = "13";
      string strOrigin = m_protocol + "://" + m_host;
      inheader("Origin") = strOrigin;

      /*      if (GetUrlPort() != 80 && GetUrlPort() != 443)
      inheader(__id(host)) = GetUrlHost() + ":" + ::str::from(GetUrlPort());
      else
      inheader(__id(host)) = GetUrlHost();*/

      m_bExpectResponse = true;
      m_bExpectRequest = false;
      m_bRequestSent = true;
      SendRequest();
   }

   void websocket_client::OnLine(const string & line)
   {


      http_client_socket::OnLine(line);

   }

   void websocket_client::OnHeaderComplete()
   {

      if (outattr(__id(http_status_code)) == 101 && outattr(__id(http_status)) == "Switching Protocols")
      {

         if (outheader("upgrade").compare_value_ci("websocket") == 0)
         {

            if (outheader("connection").compare_value_ci("Upgrade") == 0)
            {



               string strAccept = outheader("sec-websocket-accept");

               string strKey = m_strBase64;

               strKey.trim();

               strKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

               memory mem;

               mem.assign(strKey);

               memory mem2;

               System.crypto().sha1(mem2, mem);

               strKey = System.base64().encode(mem2);

               if (strAccept == strKey)
               {

                  m_bWebSocket            = true;

                  m_strWebSocketProtocol  = outheader("sec-websocket-protocol");

               }

            }

         }

      }

   }

   void websocket_client::OnDataComplete()
   {

   }

   void websocket_client::InitSSLClient()
   {
   #if defined(HAVE_OPENSSL)
         if(m_bTls)
         {
            InitializeContext("",TLS_client_method());
            m_strTlsHostName = m_host;
         }
         else
         {
            InitializeContext("", TLS_client_method());
         }
   #endif
      }



   long websocket_client::cert_common_name_check(const char * common_name)
   {


      int iResult = SSL_get_verify_result(m_ssl);

      return iResult;


      return X509_V_ERR_APPLICATION_VERIFICATION;

   }


   void websocket_client::send_json(var varJson)
   {

      string strJson;

      varJson.get_json(strJson, false);

      memory m;

      client_send(m, strJson);

      write(m.get_data(), m.get_size());

   }


   void websocket_client::send_memory(memory & memory)
   {

      ::memory m;

      client_send(m, memory);

      write(m.get_data(), m.get_size());

   }


   void websocket_client::OnRawData(char *buf, size_t len)
   {

      if (m_bWebSocket)
      {

         //string strLine;

         //strLine.Format("OnRawData len %d", (uint_ptr)len);

         //str += strLine + "\r\n";

         //TRACE("%s", strLine);


         m_memResponse.append(buf, len);

         uint64_t uiLen = 0;

         int iOffset = 2;

         if (m_memResponse.get_size() <= 0)
         {

            return;

         }

         // From
         // https://github.com/dhbaird/easywsclient/blob/master/easywsclient.cpp

         byte * data = (byte *) m_memResponse.get_data(); // peek, but don't consume

         int fin = (data[0] & 0x80) == 0x80; 

         int opcode = (data[0] & 0x0f);

         int mask = data[1] & 0x80;

         int n0 = (data[1] & 0x7f);

         int header_size = 2 + (n0 == 126 ? 2 : 0) + (n0 == 127 ? 8 : 0) + (mask ? 4 : 0);

         byte masking_key[4] = {0, 0, 0, 0};

         if (m_memResponse.get_size() < header_size)
         {

            return; 

         }

         int i = 0;

         uint64_t n = -1;

         if (n0 < 126)
         {

            n = n0;
            i = 2;

         }
         else if (n0 == 126)
         {

            n = 0;
            n |= ((uint64_t)data[2]) << 8;
            n |= ((uint64_t)data[3]) << 0;
            i = 4;

         }
         else if (n0 == 127)
         {

            n = 0;
            n |= ((uint64_t)data[2]) << 56;
            n |= ((uint64_t)data[3]) << 48;
            n |= ((uint64_t)data[4]) << 40;
            n |= ((uint64_t)data[5]) << 32;
            n |= ((uint64_t)data[6]) << 24;
            n |= ((uint64_t)data[7]) << 16;
            n |= ((uint64_t)data[8]) << 8;
            n |= ((uint64_t)data[9]) << 0;
            i = 10;

         }
         
         if (mask)
         {

            masking_key[0] = ((uint8_t)data[i + 0]) << 0;
            masking_key[1] = ((uint8_t)data[i + 1]) << 0;
            masking_key[2] = ((uint8_t)data[i + 2]) << 0;
            masking_key[3] = ((uint8_t)data[i + 3]) << 0;

         }

         if (m_memResponse.get_size() < header_size + n)
         { 
            return; /* Need: ws.header_size+ws.N - rxbuf.size() */ 
         
         }

         // We got a whole message, now do something with it:
         if (opcode == e_opcode::TEXT_FRAME || opcode == e_opcode::BINARY_FRAME || opcode == e_opcode::CONTINUATION)
         {

            if (mask)
            { 

               for (size_t i = 0; i < n; i++)
               { 
                  data[i + header_size] ^= masking_key[i & 0x3]; 

               }

            }

            m_memReceivedData.append(&data[header_size], n);// just feed

            if (fin)
            {

               on_websocket_data(m_memReceivedData.get_data(), m_memReceivedData.get_size());

               m_memReceivedData.allocate(0);

            }
            else
            {

               ::output_debug_string("ws_buffering");

            }
            
         }
         else if (opcode == e_opcode::PING)
         {

            if (mask)
            {

               for (size_t i = 0; i < n; i++)
               {

                  data[i + header_size] ^= masking_key[i & 0x3];

               }

            }

            memory m1(&data[header_size], n);

            memory m;

            client_send(m, e_opcode::PONG, m1, m_bUseMask);

            write(m.get_data(), m.get_size());

            m_memResponse.erase(0, n + header_size);

         }
         else if (opcode == e_opcode::PONG)
         {

         }
         else if (opcode == e_opcode::CLOSE)
         {

            SetCloseAndDelete();
            
         }
         else
         { 

            output_debug_string("ERROR: Got unexpected WebSocket message.\n");

            SetCloseAndDelete();
         
         }

         m_memResponse.erase(0, n + header_size);

      }
      else
      {

         http_client_socket::OnRawData(buf, len);

      }

   }


   void websocket_client::on_websocket_data(byte * pdata, int len)
   {

      string str((const char *) pdata, len);

      on_websocket_data(str);

   }

   void websocket_client::on_websocket_data(string str)
   {

   }

} // namespace sockets


