#pragma once


namespace sockets
{

   class response;

   class CLASS_DECL_AXIS http_base_socket : public http_socket
   {
   public:


      http_base_socket(base_socket_handler& h);
      ~http_base_socket();


      void OnFirst();
      void OnHeader(id key, const string & value);
      void OnHeaderComplete();
      void OnData(const char *,size_t);

      void Respond();

      void OnWriteComplete();


      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

      string set_cookie(
         const char * name,
         var var,
         int iExpire,
         const char * path,
         const char * domain,
         bool bSecure);

      virtual void on_compress();



      http_base_socket(const http_base_socket& s);
   protected:
      void Reset();

   private:
      http_base_socket& operator=(const http_base_socket& ) { return *this; } // assignment operator
      void Execute();
      int m_iContentLength;
   };




} // namespace sockets


