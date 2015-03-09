#pragma once

namespace file { class path; }

#ifdef WINDOWS
#define OS_FILESYSTEM_DIR_SEP "\\"
#else
#define OS_FILESYSTEM_DIR_SEP "/"
#endif



namespace file
{

   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class CLASS_DECL_AURA path:
      public string
   {
   public:

      path()
      {
      }

      path(const string & str):
         string(str)
      {
         normalize();
      }

      path(const char * psz): path((const string &)psz){};
      path(const wchar_t * psz): path((const string &)psz){};
      path(const wstring & wstr): path((const string &)wstr){};

      path(const path & path) :
         string(path)
      {
      }

      path(path && path) :
         string(::move(path))
      {
      }


      void normalize()
      {
         trim_right("\\/");
      }

      bool operator == (const path & path) const
      {
         return is_equal(path);
      }

      path operator + (const path & path) const
      {

         return ::file::path((const string &)*this + string(OS_FILESYSTEM_DIR_SEP) + string((const string &)path).trim_left("\\/"));

      }


      path operator + (const string & str) const
      {

         return ::file::path((const string &)*this + string(OS_FILESYSTEM_DIR_SEP) + string((const string &)str).trim_left("\\/"));


      }

      path operator + (const char * psz) const
      {

         return ::file::path((const string &)*this + string(OS_FILESYSTEM_DIR_SEP) + string((const string &)psz).trim_left("\\/"));


      }

      path & operator += (const path & path)
      {

         string::operator += (OS_FILESYSTEM_DIR_SEP + string((const string &)path).trim_left("\\/"));

         return *this;

      }

      path & operator += (const string & str)
      {

         string::operator += (OS_FILESYSTEM_DIR_SEP + string(str).trim_left("\\/"));

         normalize();

         return *this;

      }

      
      path & operator = (const string & str)
      {

         string::operator = (string(str).trim_left("\\/"));

         normalize();

         return *this;

      }

      string arg(const string & str) { return ((const string &)*this) + str; }

      string operator << (const string & str) { return arg(str); }


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
         return ::file::path(::dir::name((const string &)*this));
      }


      string & to_string(string & str) const
      {
         return str = (const string &)*this;
      }

      path sibling(const path & path) const
      {
         return ::file::path(::dir::name((const string &)*this) + string(OS_FILESYSTEM_DIR_SEP) + string(path).trim_left("\\/"));
      }

      path sibling(const string & str) const
      {
         return ::file::path(::dir::name((const string &)*this) + string(OS_FILESYSTEM_DIR_SEP) + string(str).trim_left("\\/"));
      }

      path sibling(const char * psz) const
      {

         return ::file::path(::dir::name((const string &)*this) + string(OS_FILESYSTEM_DIR_SEP) + string((const string &)psz).trim_left("\\/"));

      }

      path operator *(const path & path) const { return sibling(path); }
      path operator *(const string & str) const { return sibling(str); }
      path operator *(const char * psz) const { return sibling(psz); }


      path operator *(int i) const { ::file::path p(*this); while(i > 1){ p = *p; i--; } return p; }

      ::file::path title()
      {
         return ::file_title_dup(operator const char*());
      }

      string name()
      {
         return ::file_name_dup(operator const char*());
      }

      bool is_equal(const ::file::path & path2) const;

   };


   typedef CLASS_DECL_AURA ::string_array < ::file::path, string > patha;


} // namespace file








