#pragma once


namespace url
{


   CLASS_DECL_AURA bool is_url(const char * pszCandidate,const char ** ppszRequest = NULL);



   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
//   class CLASS_DECL_AURA url:
//      public string
//   {
//   public:
//
//      url()
//      {
//      }
//
//      url(const string & str):
//         string(str)
//      {
//         normalize();
//      }
//
//      url(const char * psz): url((const string &)psz){};
//      url(const char16_t * psz): url((const string &)psz){};
//      url(const wstring & wstr): url((const string &)wstr){};
//
//      url(const url & url):
//         string(url)
//      {
//      }
//
//      url(url && url):
//         string(::move(url))
//      {
//      }
//
//
//      void normalize()
//      {
//      }
//
//      bool operator == (const url & url) const
//      {
//         return is_equal(url);
//      }
//
//      url operator + (const url & url) const
//      {
//
//         return url((const string &)*this + string("/") + string((const string &)url).trim_left("\\/"));
//
//      }
//
//
//      url operator + (const string & str) const
//      {
//
//         return class url((const string &)*this + string("/") + string((const string &)str).trim_left("\\/"));
//
//
//      }
//
//      url operator + (const char * psz) const
//      {
//
//         return class url((const string &)*this + string("/") + string((const string &)psz).trim_left("\\/"));
//
//
//      }
//
//      url & operator += (const url & url)
//      {
//
//         string::operator += ("/" + string((const string &)url).trim_left("\\/"));
//
//         return *this;
//
//      }
//
//      url & operator += (const string & str)
//      {
//
//         string::operator += ("/" + string(str).trim_left("\\/"));
//
//         normalize();
//
//         return *this;
//
//      }
//
//
//      url & operator = (const string & str)
//      {
//
//         string::operator = (string(str).trim_left("\\/"));
//
//         normalize();
//
//         return *this;
//
//      }
//
//      url & file_cat(const string & str) { return *this + str; }
//
//      url & operator | (const string & str) { return file_cat(str); } // what is good here is the operator precedence
//
//      string arg(const string & str) const { return ((const string &)*this) + str; }
//
//      string operator << (const string & str) const { return arg(str); }
//
//
//      url & operator = (const char * psz) { return operator = (string(psz)); }
//      url & operator += (const char * psz) { return operator += (string(psz)); }
//
//      url & operator = (const var & var);
//      url & operator += (const var & var);
//
//      url & operator = (const wstring & wstr) { return operator = (string(wstr)); }
//      url & operator += (const wstring & wstr) { return operator += (string(wstr)); }
//
//      url & operator = (const char16_t * psz) { return operator = (wstring(psz)); }
//      url & operator += (const char16_t * psz) { return operator += (wstring(psz)); }
//
//      url operator * ()
//      {
//         return class url(::dir::name((const string &)*this));
//      }
//
//
//      string & to_string(string & str) const
//      {
//         return str = (const string &)*this;
//      }
//
//      url sibling(const url & url) const
//      {
//         return class url(::dir::name((const string &)*this) + string("/") + string(url).trim_left("\\/"));
//      }
//
//      url sibling(const string & str) const
//      {
//         return class url(::dir::name((const string &)*this) + string("/") + string(str).trim_left("\\/"));
//      }
//
//      url sibling(const char * psz) const
//      {
//
//         return class url(::dir::name((const string &)*this) + string("/") + string((const string &)psz).trim_left("\\/"));
//
//      }
//
//      url operator *(const url & url) const { return sibling(url); }
//      url operator *(const string & str) const { return sibling(str); }
//      url operator *(const char * psz) const { return sibling(psz); }
//
//
//      url operator *(int i) const { url p(*this); while(i > 1){ p = *p; i--; } return p; }
//
//      url title()
//      {
//         return ::file_title_dup(operator const char*());
//      }
//
//      string name()
//      {
//         return ::file_name_dup(operator const char*());
//      }
//
//      bool is_equal(const url & path2) const;
//
//   };
//
//   typedef CLASS_DECL_AURA ::string_array < url,string > urla;
//
//

} // namespace url




inline bool is_url_dup(const string & strCandidate)
{

   return ::url::is_url(strCandidate);

}































