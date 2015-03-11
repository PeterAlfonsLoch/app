#pragma once

namespace file { class path; }

inline bool is_url_dup(const string & strCandidate);

namespace file
{

   enum e_path
   {
      path_file,
      path_url
   };


   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class CLASS_DECL_AURA path:
      public string
   {
   public:


      static const char * s_pszDirSep;
      static const char * s_pszOtherDirSep;


   protected:


      e_path     m_epath;


   public:


      path(e_path epath = path_file)
      {
         
         m_epath = epath;

      }

      path(const string & str):
         string(str)
      {
         
         m_epath = is_url_dup(str) ? path_url : path_file;

         normalize();

      }

      path(const string & str,e_path epath):
         string(str)
      {
         m_epath = epath;
         normalize();
      }

      inline char sep() const
      {
         return s_pszDirSep[(int) m_epath];
      }

      inline char osep() const
      {
         return s_pszOtherDirSep[(int)m_epath];
      }

      path(const char * psz,e_path epath = path_file): path((const string &)psz, epath){};
      path(const wchar_t * psz,e_path epath = path_file): path((const string &)psz,epath){};
      path(const wstring & wstr,e_path epath = path_file): path((const string &)wstr,epath){};

      path(const path & path) :
         string(path)
      {
         m_epath = path.m_epath;
      }

      path(path && path) :
         string(::move(path))
      {
         m_epath = path.m_epath;
      }

      void set_type(e_path epath)
      {
         if(epath != m_epath)
         {
            m_epath = epath;
            normalize();
         }
      }


      void normalize()
      {
         
         trim_right("\\/");
         
         replace(osep(),sep());

      }


      bool operator == (const path & path) const
      {
         return is_equal(path);
      }

      path operator + (const path & path) const
      {

         return ::file::path((const string &)*this  + string((const string &)path).trim_left("\\/"), m_epath);

      }


      path operator + (const string & str) const
      {

         return ::file::path((const string &)*this + string((const string &)str).trim_left("\\/"),m_epath);


      }

      path operator + (const char * psz) const
      {

         return ::file::path((const string &)*this + string((const string &)psz).trim_left("\\/"),m_epath);


      }

      path & operator += (const path & path)
      {

         string::operator += (string((const string &)path).trim_left("\\/"));

         return *this;

      }

      path & operator += (const string & str)
      {

         string::operator += ( + string(str).trim_left("\\/"));

         normalize();

         return *this;

      }


      path operator / (const path & path) const
      {

         return ::file::path((const string &)*this + sep() + string((const string &)path).trim_left("\\/"),m_epath);

      }


      path operator / (const string & str) const
      {

         return ::file::path((const string &)*this + sep() + string((const string &)str).trim_left("\\/"),m_epath);


      }

      path operator / (const char * psz) const
      {

         return ::file::path((const string &)*this + sep() + string((const string &)psz).trim_left("\\/"),m_epath);


      }

      path & operator /= (const path & path)
      {

         string::operator += (string(sep()) + string((const string &)path).trim_left("\\/"));

         return *this;

      }

      path & operator /= (const string & str)
      {

         string::operator += (string(sep()) + string(str).trim_left("\\/"));

         normalize();

         return *this;

      }

      path & operator = (const string & str)
      {

         string::operator = (string(str).trim_left("\\/"));

         normalize();

         return *this;

      }

      //::file::path & file_cat(const string & str) { return *this + str; }

      //::file::path & operator | (const string & str) { return file_cat(str); } // what is good here is the operator precedence

      //string arg(const string & str) const { return ((const string &)*this) + str; }

      //string operator << (const string & str) const { return arg(str); }


      path & operator = (const char * psz) { return operator = (string(psz)); }
      path & operator += (const char * psz) { return operator += (string(psz)); }

      path & operator = (const var & var) { return operator = (var.get_string()); }
      path & operator += (const var & var) { return operator += (var.get_string()); }

      path & operator = (const wstring & wstr) { return operator = (string(wstr)); }
      path & operator += (const wstring & wstr) { return operator += (string(wstr)); }

      path & operator = (const wchar_t * psz) { return operator = (wstring(psz)); }
      path & operator += (const wchar_t * psz) { return operator += (wstring(psz)); }

      path operator * ()
      {
         return ::file::path(::dir::name((const string &)*this),m_epath);
      }


      string & to_string(string & str) const
      {
         return str = (const string &)*this;
      }

      path sibling(const path & path) const
      {
         return ::file::path(::dir::name((const string &)*this) + sep() + string(path).trim_left("\\/"),m_epath);
      }

      path sibling(const string & str) const
      {
         return ::file::path(::dir::name((const string &)*this) + sep() + string(str).trim_left("\\/"),m_epath);
      }

      path sibling(const char * psz) const
      {

         return ::file::path(::dir::name((const string &)*this) + sep() + string((const string &)psz).trim_left("\\/"),m_epath);

      }

      path operator *(const path & path) const { return sibling(path); }
      path operator *(const string & str) const { return sibling(str); }
      path operator *(const char * psz) const { return sibling(psz); }


      path operator *(int i) const { ::file::path p(*this); while(i > 1){ p = *p; i--; } return p; }

      ::file::path title()
      {
         return ::file_title_dup(operator const char*());
      }

      ::file::path name()
      {
         return ::file_name_dup(operator const char*());
      }

      bool is_equal(const ::file::path & path2) const;

      string extension() const
      {
         return file_extension_dup(operator const char *());
      }

      string ext() const
      {
         return extension();
      }

   };

   typedef CLASS_DECL_AURA ::string_array < ::file::path,string > patha;


} // namespace file





namespace url
{


   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class CLASS_DECL_AURA url:
      public string
   {
   public:

      url()
      {
      }

      url(const string & str):
         string(str)
      {
         normalize();
      }

      url(const char * psz): url((const string &)psz){};
      url(const wchar_t * psz): url((const string &)psz){};
      url(const wstring & wstr): url((const string &)wstr){};

      url(const url & url):
         string(url)
      {
      }

      url(url && url):
         string(::move(url))
      {
      }


      void normalize()
      {
      }

      bool operator == (const url & url) const
      {
         return is_equal(url);
      }

      url operator + (const url & url) const
      {

         return class url((const string &)*this + string("/") + string((const string &)url).trim_left("\\/"));

      }


      url operator + (const string & str) const
      {

         return class url((const string &)*this + string("/") + string((const string &)str).trim_left("\\/"));


      }

      url operator + (const char * psz) const
      {

         return class url((const string &)*this + string("/") + string((const string &)psz).trim_left("\\/"));


      }

      url & operator += (const url & url)
      {

         string::operator += ("/" + string((const string &)url).trim_left("\\/"));

         return *this;

      }

      url & operator += (const string & str)
      {

         string::operator += ("/" + string(str).trim_left("\\/"));

         normalize();

         return *this;

      }


      url & operator = (const string & str)
      {

         string::operator = (string(str).trim_left("\\/"));

         normalize();

         return *this;

      }

      url & file_cat(const string & str) { return *this + str; }

      url & operator | (const string & str) { return file_cat(str); } // what is good here is the operator precedence

      string arg(const string & str) const { return ((const string &)*this) + str; }

      string operator << (const string & str) const { return arg(str); }


      url & operator = (const char * psz) { return operator = (string(psz)); }
      url & operator += (const char * psz) { return operator += (string(psz)); }

      url & operator = (const var & var) { return operator = (var.get_string()); }
      url & operator += (const var & var) { return operator += (var.get_string()); }

      url & operator = (const wstring & wstr) { return operator = (string(wstr)); }
      url & operator += (const wstring & wstr) { return operator += (string(wstr)); }

      url & operator = (const wchar_t * psz) { return operator = (wstring(psz)); }
      url & operator += (const wchar_t * psz) { return operator += (wstring(psz)); }

      url operator * ()
      {
         return class url(::dir::name((const string &)*this));
      }


      string & to_string(string & str) const
      {
         return str = (const string &)*this;
      }

      url sibling(const url & url) const
      {
         return class url(::dir::name((const string &)*this) + string("/") + string(url).trim_left("\\/"));
      }

      url sibling(const string & str) const
      {
         return class url(::dir::name((const string &)*this) + string("/") + string(str).trim_left("\\/"));
      }

      url sibling(const char * psz) const
      {

         return class url(::dir::name((const string &)*this) + string("/") + string((const string &)psz).trim_left("\\/"));

      }

      url operator *(const url & url) const { return sibling(url); }
      url operator *(const string & str) const { return sibling(str); }
      url operator *(const char * psz) const { return sibling(psz); }


      url operator *(int i) const { url p(*this); while(i > 1){ p = *p; i--; } return p; }

      url title()
      {
         return ::file_title_dup(operator const char*());
      }

      string name()
      {
         return ::file_name_dup(operator const char*());
      }

      bool is_equal(const url & path2) const;

   };

   typedef CLASS_DECL_AURA ::string_array < url,string > urla;


} // namespace url


