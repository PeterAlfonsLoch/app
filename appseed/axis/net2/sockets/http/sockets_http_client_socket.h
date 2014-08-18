#pragma once


   namespace sockets
   {


      enum e_http_method
      {
         http_method_none,
         http_method_get,
         http_method_post,
         http_method_put

      };

      
      CLASS_DECL_AXIS string http_method_string(e_http_method emethod);
      CLASS_DECL_AXIS e_http_method string_http_method(const string & str);


      /** get http response to file or primitive::memory.
      \ingroup http */
      class CLASS_DECL_AXIS http_client_socket :
         virtual public http_tunnel,
         virtual public int_scalar_source
      {
      public:


         mutex                         m_mutexData;
         ::file::memory_buffer         m_memoryfile;
         ::file::stream_buffer *       m_pfile;
         int64_t                       m_iFinalSize;
         int_progress                  m_progress;
         e_http_method                 m_emethod;


         //primitive::memory    m_memoryData; ///< Ptr to buffer where to store response
         //size_t m_data_size; ///< Max size of data buffer
         ::primitive::memory_size m_content_length; ///< Content-length header received from remote
         string m_content; ///< Received http headers
         //bool m_data_ptr_set; ///< buffer set from outside, do not delete
         ::primitive::memory_position m_content_ptr; ///< Number of bytes received from body
         bool m_b_complete; ///< The entire content-length number of bytes has been received
         bool m_b_close_when_complete; ///< close when the full response has been received
         string m_protocol; ///< Protocol part of url_in
         string m_url_filename; ///< Filename from url_in
         string m_content_type; ///< Content-type: header from response



         http_client_socket(base_socket_handler&);
         http_client_socket(base_socket_handler&,const string & url_in);
         ~http_client_socket();


         virtual void OnConnect();

         /** Parse url to protocol,host,port,url and spfile-> */
         void Url(const string & url_in,string & host,port_t& port);

         void OnFirst();
         void OnHeader(id,const string &);
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
         const unsigned char *GetDataPtr() const;

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


         virtual void on_set_scalar(e_scalar escalar, int64_t iValue);
         virtual void get_scalar_minimum(e_scalar escalar, int64_t & i);
         virtual void get_scalar(e_scalar escalar, int64_t & i);
         virtual void get_scalar_maximum(e_scalar escalar, int64_t & i);


      };


   } // namespace sockets


