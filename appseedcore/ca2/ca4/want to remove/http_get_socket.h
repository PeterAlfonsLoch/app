#pragma once

namespace ca27
{

class CLASS_DECL_ca2api00200002 http_get_socket : public HttpGetSocket
{
public:

	http_get_socket(ISocketHandler& handler,const string& url,const string& to_file = "");
   http_get_socket(ISocketHandler& handler,const string& host,port_t port,const string& url,const string& to_file = "");

   string m_strHeaderLocation;

   ::http::cookies * m_pcookies;
   
   virtual void OnDataArrived(const char *, size_t len);
   void OnHeader(const string& key,const string& value);

   virtual string MyUseragent();
};


} // namespace ca27