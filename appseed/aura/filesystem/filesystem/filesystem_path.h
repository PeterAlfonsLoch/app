#pragma once

namespace file { class path; }

inline bool is_url_dup(const string & strCandidate);

CLASS_DECL_AURA string defer_solve_relative_compresions(const string & str);

namespace file
{

   class path;

   typedef CLASS_DECL_AURA ::string_array < ::file::path,string > patha;


   enum e_path
   {
      path_none,
      path_file,
      path_url
   };

   CLASS_DECL_AURA e_path get_path_type(const string & str, e_path epathForce = path_none);

   struct CLASS_DECL_AURA path_meta
   {

      e_path            m_epath;

      int64_t           m_iSize = -1; // if negative, not set/calculated/retrieved the file size(for directories would be all contained elements total sum size)
      int               m_iDir = -1; // if negative, not set/calculated/retrieved whether is a directory/folder/(file/folder/(...) container)
      strsize           m_iName = -1; // if negative, not set/calculated/retrieved where name starts
      strsize           m_iRelative = -1; // if negative, not set/calculated/retrieved where relative starts - this information is very, very relative :-) much more than all own other ::file::path cached information (relative to which folders... not stored this information...)
      
      path_meta()
      {
         
         m_epath     = path_none;
         m_iSize     = -1;
         m_iDir      = -1;
         m_iName     = -1;
         m_iRelative = -1;
         
      }
      
      
   };
   

   CLASS_DECL_AURA string normalize_path(string strPath, e_path epath = path_none);
   
   inline char path_sep(e_path epath);
   
   inline char path_osep(e_path epath);

   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class CLASS_DECL_AURA path :
      public string,
      public path_meta
   {
   public:

      //typedef ::string_array < ::file::path,string > patha;

      path(e_context_switcher_null);
      path(e_path epath = path_file);
      path(const string & str,e_path epath = path_none);
      path(const id & id,e_path epath = path_none);
      path(const var & var, e_path epath = path_none);
      path(const path & path);
      path(path && path);
      path(const char * psz,e_path epath = path_none);
      path(const unichar * psz,e_path epath = path_none);
      path(const wstring & wstr,e_path epath = path_none);
      //path(const var & var,e_path epath = path_file);
      path(const property & property,e_path epath = path_none);

      ~path() throw();


      void set_type(e_path epath);
      
      
      inline char sep() const
      {
         
         return path_sep(m_epath);
         
      }

      inline char osep() const
      {
         
         return path_osep(m_epath);
         
      }

      path & operator = (const ::file::path & path);

      path & operator = (const string & str);

      bool operator == (const path & path) const;

      bool operator == (const string & str) const;
      bool operator == (const char * psz) const;
      bool operator == (const var & var) const;

      bool operator != (const path & path) const;

      bool operator != (const string & str) const;
      bool operator != (const char * psz) const;
      bool operator != (const var & var) const;

      path operator + (const path & path) const;


      path operator + (const string & str) const;

      path operator + (const char * psz) const;
      path operator + (const var & var) const;
      path operator + (const property & property) const;
      path operator + (const id & id) const;

      path & operator += (const path & path);
      path & operator += (const string & str);
      path operator / (const path & path) const;
      path operator / (const string & str) const;
      path operator / (const char * psz) const;
      path operator / (const property & property) const;
      
      path & operator /= (const path & path);
      path & operator /= (const string & str);
      path & operator /= (const char * psz);



      //::file::path & file_cat(const string & str) { return *this + str; }

      //::file::path & operator | (const string & str) { return file_cat(str); } // what is good here is the operator precedence

      //string arg(const string & str) const { return ((const string &)*this) + str; }

      //string operator << (const string & str) const { return arg(str); }

      path & operator = (const char * psz);
      path & operator += (const char * psz);

      path & operator = (const var & var);
      path & operator += (const var & var);

      path & operator = (const wstring & wstr);
      path & operator += (const wstring & wstr);

      path & operator = (const unichar * psz);
      path & operator += (const unichar * psz);

      //path operator * () const;

      //path operator -- () const;
      //path operator -- (int) const { return operator --(); }


      string & to_string(string & str) const;

      path sibling(const path & path) const;
      path sibling(const string & str) const;
      path sibling(const char * psz) const;

      path operator * (const path & path) const;

      path operator * (const string & str) const;
      path operator * (const char * psz) const;
      path operator * (const property & property) const;

      path & operator *= (const path & path);

      path & operator *= (const string & str);
      path & operator *= (const char * psz);
      path & operator *= (const property & property);

      ::file::path title() const;

      ::file::path name() const;

      index find_file_name() const;

      bool is_equal(const ::file::path & path2) const;

      string extension() const;

      string ext() const;

      string final_extension() const;

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

      void split(patha & patha) const;
      bool is_relative();

      patha & ascendants_path(patha & patha) const;
      patha & ascendants_name(patha & namea) const;
      patha ascendants_path() const;
      patha ascendants_name() const;

      path relative() const;


      path folder() const;
      path folder(int i) const;
      path up() const;
      path up(int i) const;
      path & go_up();
      path & go_up(int i);
      path & operator -= (int i);



   };


   CLASS_DECL_AURA e_path get_path_type(const string & str, e_path epathForce);


   inline char path_sep(e_path epath)
   {
      
#ifdef WINDOWS
      
      if(epath == path_file)
      {
         
         return '\\';
         
      }
      
#endif
      
      return '/';
      
   }
   
   inline char path_osep(e_path epath)
   {
      
#ifdef WINDOWS
      
      if(epath == path_file)
      {
         
         return '/';
         
      }
      
#endif
      
      return '\\';
      
   }

} // namespace file








inline const char * FormatArgument(const ::file::path & value) noexcept
{
   return value.c_str();
}

template<>
inline UINT HashKey<const ::file::path &>(const ::file::path &  key)
{

   return HashKey<const char * >(key.c_str());

}