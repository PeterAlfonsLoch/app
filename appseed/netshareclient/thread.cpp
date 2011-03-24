#include "StdAfx.h"

namespace netshareclient
{

thread::thread(::ca::application * papp) :
   ca(papp), 
   ::radix::thread(papp), 
   m_h(papp),
   m_tunnel(m_h)
{
   m_tunnel.m_pthread = this;
//   m_pfile = NULL;
/*	m_strHead += "HTTP/1.1 200 OK\n";
	m_strHead += "Server: netnode/1.0 (Windows)\n";
	m_strHead += "Accept-Ranges: bytes\n";
	m_strHead += "Date: Mon, 23 May 2005 22:38:34 GMT\n";
	m_strHead += "Server: netnode/1.0 (Windows)\n";
	m_strHead += "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n";
	//m_memfileSend += "Etag: "3f80f-1b6-3e1cb03b"";
	m_strHead += "Accept-Ranges: bytes\n";
	// m_memfileSend += "Content-Length: 438";
	//m_strHead += "Connection: close\n";

	/*m_memfileBody << "<html>\n";
	m_memfileBody << "<head>\n";
	m_memfileBody << "</head>\n";
	m_memfileBody << "<body>\n";
	m_memfileBody << "<h1>Ti Amo Carlos Gustavo Cecyn Lundgren de 15 de novembro de 1984!</h1>\n";
	m_memfileBody << "<h1>Assinado Camilo Sasuke Tsumanuma de 2 de abril de 1977!</h1>\n";
	m_memfileBody << "</body>\n";*/
//   m_pconnection = NULL;
}

thread::~thread(void)
{
}

int thread::run()
{
   m_tunnel.netshare_start();
   m_h.EnablePool();
   m_tunnel.netshare_connect();
   m_h.add(&m_tunnel);
   while(get_run())
   {
      while(m_h.get_count())
      {
         m_h.Select(30, 0);
      }
   }
   return 0;
}



} // namespace netshareclient


