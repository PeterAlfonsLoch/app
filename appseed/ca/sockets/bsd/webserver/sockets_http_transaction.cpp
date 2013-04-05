#include "framework.h"


namespace http
{


   transaction::transaction(::ca::applicationsp papp) :
      ca(papp)
   {
      m_propertysetHeader.m_bKeyCaseInsensitive       = true;
      m_propertysetAttribute.m_bKeyCaseInsensitive    = true;
   }

   transaction::transaction(const transaction & src) :
      ::ca::ca(((class request&) src).get_app()),
      m_propertysetAttribute(src.m_propertysetAttribute),
      m_propertysetHeader(src.m_propertysetHeader)
   {
      m_propertysetHeader.m_bKeyCaseInsensitive       = true;
      m_propertysetAttribute.m_bKeyCaseInsensitive    = true;
   }


   transaction::~transaction()
   {
   }

   void transaction::SetAccept(const string & value)
   {
      header("Accept") = value;
   }

   string transaction::Accept()
   {
      return header("Accept");
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
      header("Connection") = value;
   }

   string transaction::Connection()
   {
      return header("Connection");
   }

   void transaction::SetContentType(const string & value)
   {
      header("Content-Type") = value;
   }

   string transaction::ContentType()
   {
      return header("Content-Type");
   }

   void transaction::SetContentLength(primitive::memory_size value)
   {
      header("Content-Length") = value;
   }

   primitive::memory_size transaction::ContentLength()
   {
      return atol(header("Content-Length"));
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




