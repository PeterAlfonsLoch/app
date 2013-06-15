#pragma once


namespace sip
{


   class CLASS_DECL_ca2 transaction :
      virtual public ::ca2::object
   {
   public:


      ::ca2::property_set     m_propertysetHeader;
      ::ca2::property_set     m_propertysetAttribute;
      http::cookies           m_cookies;
      string m_null;


      transaction(::ca2::application * papp);
      transaction(const transaction & src);
      virtual ~transaction();

      ::ca2::property & header(const char * pszKey);

      void SetAccept(const string & value);
      string Accept();

      void SetAcceptCharset(const string & value);
      string AcceptCharset();

      void SetAcceptEncoding(const string & value);
      string AcceptEncoding();

      void SetAcceptLanguage(const string & value);
      string AcceptLanguage();

      void SetConnection(const string & value);
      string Connection();

      void SetContentType(const string & value);
      string ContentType();

      void SetContentLength(long value);
      long ContentLength();

      void SetHost(const string & value);
      string Host();

      void SetPragma(const string & value);
      string Pragma();

      void SetReferer(const string & value);
      string Referer();

      void SetUserAgent(const string & value);
      string UserAgent();

      ::ca2::property_set & headers();

      ::ca2::property_set & attrs();

      ::ca2::property & attr(const char * psz);
      http::cookies & cookies();

      virtual void clear();

      
   }; // end of class


} // namespace sip




