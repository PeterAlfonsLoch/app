#include "framework.h" // from "axis/net/net_sockets.h"
#include "axis/net/net_sockets.h"


namespace http
{


   transaction::transaction(::aura::application * papp) :
      ::object(papp)
   {

   }


   transaction::transaction(const transaction & src) :
      ::object(((class request&) src).get_app()),
      m_propertysetAttribute(src.m_propertysetAttribute),
      m_propertysetHeader(src.m_propertysetHeader)
   {

   }


   transaction::~transaction()
   {

   }


   void transaction::SetAccept(const string & value)
   {

      header(__id(accept)) = value;

   }


   string transaction::Accept()
   {
      return header(__id(accept));
   }

   void transaction::SetAcceptCharset(const string & value)
   {
      header("Accept-Charset") = value;
   }

   string transaction::AcceptCharset()
   {
      return header("Accept-Charset");
   }

   void transaction::SetAcceptEncoding(const string & value)
   {
      header("Accept-Encoding") = value;
   }

   string transaction::AcceptEncoding()
   {
      return header("Accept-Encoding");
   }

   void transaction::SetAcceptLanguage(const string & value)
   {
      header("Accept-Language") = value;
   }

   string transaction::AcceptLanguage()
   {
      return header("Accept-Language");
   }

   void transaction::SetConnection(const string & value)
   {
      header(__id(connection)) = value;
   }

   string transaction::Connection()
   {
      return header(__id(connection));
   }

   void transaction::SetContentType(const string & value)
   {
      header(__id(content_type)) = value;
   }

   string transaction::ContentType()
   {
      return header(__id(content_type));
   }

   void transaction::SetContentLength(memory_size_t value)
   {
      header(__id(content_length)) = value;
   }

   memory_size_t transaction::ContentLength()
   {
      return atol(header(__id(content_length)));
   }

   void transaction::SetHost(const string & value)
   {
      header("Host") = value;
   }

   string transaction::Host()
   {
      return header("Host");
   }

   void transaction::SetPragma(const string & value)
   {
      header("Pragma") = value;
   }

   string transaction::Pragma()
   {
      return header("Pragma");
   }

   void transaction::SetReferer(const string & value)
   {
      header("Referer") = value;
   }

   string transaction::Referer()
   {
      return header("Referer");
   }

   void transaction::SetUserAgent(const string & value)
   {
      header("User-Agent") = value;
   }

   string transaction::UserAgent()
   {
      return header("User-Agent");
   }

   void transaction::clear()
   {
      m_propertysetAttribute.clear();
      m_propertysetHeader.clear();
      m_cookies.remove_all();
   }




} // namespace http




