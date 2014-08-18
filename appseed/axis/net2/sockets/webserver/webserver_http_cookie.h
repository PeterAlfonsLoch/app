#pragma once


class http_socket;


namespace http
{


   class CLASS_DECL_AXIS cookie :
      virtual public root
   {
   public:


      string         m_strName;
      string         m_strNameLow;
      var            m_varValue;
      string         m_strExpire;
      string         m_strPath;
      string         m_strDomain;
      bool           m_bSecure;


      cookie();
      cookie(const cookie & cookie);
      virtual ~cookie();


      string get_cookie_string();

      cookie & operator = (var var)
      {
         m_varValue = var;
         return *this;
      }


      cookie & operator = (const cookie & cookie);

      bool is_set()
      {
         return m_varValue.is_set();
      }

      bool is_new()
      {
         return m_varValue.is_new();
      }

      operator var &()
      {
         return m_varValue;
      }

      inline string to_string() const
      {
         return m_varValue.to_string();
      }

   };



   class CLASS_DECL_AXIS cookies :
      public spa(cookie)
   {
   public:



      cookies();
      virtual ~cookies();


      index find_cookie(const char * name);
      index lowfind_cookie(const char * name);
      http::cookie & cookie(const char * name);
      http::cookie & lowcookie(const char * name);
      using  spa(http::cookie)::add;
      void add(const char * psz);
      void parse_header(const char * psz);
      string get_cookie_header();
      strsize get_length(const char * name);
      string set_cookie(
         const char * pszKey,
         var var,
         int32_t iExpire = 0,
         const char * pszDomain = NULL,
         const char * pszPath = NULL,
         bool bSecure = false);
      static string expire(time_t iExpire = 0);


      using spa(class http::cookie)::operator [];
      http::cookie & operator [](const char * name);


      cookies & operator = (const cookies & cookies);

   };


} // namespace http


