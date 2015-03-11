#pragma once

namespace file { class path; }

inline bool is_url_dup(const string & strCandidate);

namespace file
{

   class path;

   typedef CLASS_DECL_AURA ::string_array < ::file::path,string > patha;


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

      //typedef ::string_array < ::file::path,string > patha;

      static const char * s_pszDirSep;
      static const char * s_pszOtherDirSep;


   protected:


      e_path     m_epath;


   public:

      int64_t           m_iSize = -1; // if negative, not set/calculated/retrieved the file size(for directories would be all contained elements total sum size)
      int               m_iDir = -1; // if negative, not set/calculated/retrieved whether is a directory/folder/(file/folder/(...) container)


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

      path & operator = (const var & var);
      path & operator += (const var & var);

      path & operator = (const wstring & wstr) { return operator = (string(wstr)); }
      path & operator += (const wstring & wstr) { return operator += (string(wstr)); }

      path & operator = (const wchar_t * psz) { return operator = (wstring(psz)); }
      path & operator += (const wchar_t * psz) { return operator += (wstring(psz)); }

      //path operator * () const;

      path operator -- () const;
      path operator -- (int) const { return operator --(); }


      string & to_string(string & str) const
      {
         return str = (const string &)*this;
      }

      path sibling(const path & path) const;
      path sibling(const string & str) const;
      path sibling(const char * psz) const;

      path operator *(const path & path) const { return sibling(path); }
      path operator *(const string & str) const { return sibling(str); }
      path operator *(const char * psz) const { return sibling(psz); }


      path operator -(int i) const { ::file::path p(*this); while(i > 1){ p = p--; i--; } return p; }
      path & operator -=(int i)  { while(i > 1){ *this = (*this)--; i--; } return *this; }

      ::file::path title() const
      {
         return ::file_title_dup(operator const char*());
      }

      ::file::path name() const
      {
         return ::file_name_dup(operator const char*());
      }

      bool is_equal(const ::file::path & path2) const;

      string extension() const;

      string ext() const
      {
         return extension();
      }


      //class CLASS_DECL_AURA path:
      //   virtual public ::object
      //{
      //public:

      //   ::file::system * m_pfile;


      //   bool is_equal(const char * lpszFilPathA,const char * lpszFilPathB); << is_equal
      //   bool eat_end_level(string & str,int32_t iLevelCount,const char * lpSeparator); << operator *
      //   void split(::file::patha & stra,const char * lpcszPath);
      //   bool is_relative(const char * psz);

      //   bool rename(const char * pszNew,const char * psz,::aura::application * papp); TODO should go to something like file::system

      //};

      void split(patha & patha);
      bool is_relative()
      {
         return file_path_is_relative_dup(*this) != FALSE;
      }

      patha & ascendants_path(patha & patha) const;
      patha & ascendants_name(patha & namea) const;
      patha ascendants_path() const;
      patha ascendants_name() const;


   };

   


} // namespace file





