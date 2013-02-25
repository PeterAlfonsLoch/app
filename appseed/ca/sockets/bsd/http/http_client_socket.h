#pragma once


   namespace sockets
   {


      /** get http response to file or primitive::memory. 
      \ingroup http */
      class CLASS_DECL_ca http_client_socket : 
         virtual public http_tunnel
      {
      public:

         mutex                   m_mutexData;
         ::primitive::memory_file        m_memoryfile;
         ::ca::file *             m_pfile;


         //primitive::memory    m_memoryData; ///< Ptr to buffer where to store response
         //size_t m_data_size; ///< Max size of data buffer
         primitive::memory_size m_content_length; ///< Content-length header received from remote
         string m_content; ///< Received http headers
         //bool m_data_ptr_set; ///< buffer set from outside, do not delete
         size_t m_content_ptr; ///< Number of bytes received from body
         bool m_b_complete; ///< The entire content-length number of bytes has been received
         bool m_b_close_when_complete; ///< close when the full response has been received
         string m_protocol; ///< Protocol part of url_in
         string m_url_filename; ///< Filename from url_in
         string m_content_type; ///< Content-type: header from response



         http_client_socket(socket_handler_base&);
         http_client_socket(socket_handler_base&,const string & url_in);
         ~http_client_socket();

         /** Parse url to protocol,host,port,url and spfile-> */
         void Url(const string & url_in,string & host,port_t& port);

         void OnFirst();
         void OnHeader(const string &,const string &, const string & lowvalue);
         void OnHeaderComplete();
         void OnData(const char *,size_t);
         void OnDelete();

         virtual void OnDataArrived(const char *,size_t);

         /** New callback method fires when all data is received. */
         virtual void OnContent();

         /** get response headers. */
         const string & GetContent();

         /** get size of response body. */
         size_t GetContentLength();

         /** get content type from response header. */
         const string & GetContentType();

         /** get size of received response body. */
         size_t GetContentPtr();

         /** get size of received response body. */
         size_t GetPos();

         /** Complete response has been received. */
         bool Complete();

         /** get ptr to response data buffer. */
         const uchar *GetDataPtr() const;

         /** get length of response data buffer. */
         size_t GetDataLength() const;

         /** close socket when response received. */
         void SetCloseOnComplete(bool = true);

         /** get protocol used from url. */
         const string & GetUrlProtocol();

         /** get filename part of url. */
         const string & GetUrlFilename();

         virtual void OnDataComplete();


         


         virtual void request_url(string strUrlParam);

      };


   } // namespace sockets 


