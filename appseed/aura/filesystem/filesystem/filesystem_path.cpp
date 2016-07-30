#include "framework.h"


namespace file
{

   path::path(e_context_switcher_null)
   {
   
      m_epath = path_file;
      
   }
   
   
   path::path(e_path epath)
   {
      
      m_epath = epath;
   
   }
   
   path::path(const string & str, e_path epath)
   {
      
      m_epath = get_path_type(str, epath);
      
      ::string::operator = (normalize_path(str, m_epath));
   
   }
   
   
   path::path(const id & id,e_path epath) :
      path(string(id), epath)
   {
      
   }
   
   path::path(const var & var, e_path epath) :
      path(var.get_string(), epath)
   {
      
   
   }
           
   path::path(const path & path) :
      ::string((const string &) path),
      path_meta((path_meta &) path)
   {
      
   }
           
           
   path::path(path && path) :
      string(::move(path)),
      path_meta((path_meta &) path)
   {
      
   }
   
   
   path::path(const char * psz,e_path epath ):
      path(string(psz), epath)
   {
      
   }
   
   path::path(const unichar * psz,e_path epath ) :
      path(string(psz),epath)
   {
      
   }
        
        
   path::path(const wstring & wstr,e_path epath):
        path(string(wstr),epath)
   {
   
   }
        
   //path(const var & var,e_path epath = path_file);
   //path(const property & property,e_path epath = path_none);

   path::~path() throw()
   {


   }


   bool path::is_equal(const path & path) const
   {

      if(((const string &)*this).operator == ((const string &)path)) // undoubtely eaqual...
         return true;

      // find extend equalitys..

      ::file::patha patha1;

      split(patha1);

      ::file::patha patha2;

      path.split(patha2);

      if(patha1.get_size() == patha2.get_size())
      {

         for(index i = 0; i < patha1.get_size(); i++)
         {

            if(patha1[i].::string::operator!=(patha2[i]))
            {

               goto there_s_difference_in_this_step_1;

            }

         }

         return true;

      }

      there_s_difference_in_this_step_1:


      return false;

   }


   void path::split(patha & patha) const
   {
      stringa straSeparator;
      straSeparator.add("\\");
      straSeparator.add("/");
      patha.add_smallest_tokens(*this,straSeparator,FALSE);
   }

   patha & path::ascendants_path(patha & straParam) const
   {

      ::file::patha stra;

      ascendants_name(stra);

      ::file::path str;

      if(stra.get_count() > 0)
      {
         str = stra[0];
         straParam.add(str);
      }

      for(int32_t i = 1; i < stra.get_size(); i++)
      {
         str /= stra[i];
         straParam.add(str);
      }

      return straParam;

   }


   patha & path::ascendants_name(patha & straParam) const
   {

      stringa straSeparator;

      straSeparator.add("/");
      straSeparator.add("\\");

      straParam.add_smallest_tokens(*this,straSeparator,FALSE);
      if(straParam.get_count() > 0)
      {
         if(sep() == '/' && operator[](0) == '/')
         {
            straParam[0] = "/" + straParam[0];
         }
         strsize iFind = straParam[0].find(':');
         //if(iFind >= 2)
         //{
         //   straParam[0] += "//";
         //}
         //else if(iFind == 1)
         //{
         //   straParam[0] += "\\";
         //}
      }

      return straParam;

   }


   path path::folder(int i) const
   {

      ::file::path path(*this);

      while(i > 0)
      {

         path = path.folder();

         i--;

      }

      return path;

   }


   path & path::go_up()
   {

      return *this = folder();

   }


   path & path::go_up(int i)
   {

      while(i > 0)
      {

         go_up();

         i--;

      }

      return *this;

   }

   
   path & path::operator += (const path & path)
   {
      
      string str = path;
      
      str.trim_left("\\/");
      
      string::operator += (str);
      
      return *this;
      
   }
   
   path & path::operator += (const string & strParam)
   {
      
      string str = strParam;
      
      str.trim_left("\\/");
      
      string strThis = *this;
      
      string::operator = (normalize_path(strThis + str, m_epath));
      
      return *this;
      
   }
   
   
   path path::operator / (const path & path) const
   {
      
      string strPath;
      
      strPath = string(*this);
      
      strPath += sep();
      
      string str = path;
      
      str.trim_left("\\/");
      
      return ::file::path(strPath + str, m_epath);
      
   }
   
   path path::operator / (const string & str) const
   {
      
      return operator /(::file::path(str));
      
   }
   
   
   path path::operator / (const char * psz) const
   {
      
      return operator /(::file::path(psz));
      
   }
   
   //path path::operator / (const property & property) const;
   
   path & path::operator /= (const path & path)
   {
      
      string strPath;
      
      strPath = string(*this);
      
      strPath += sep();
      
      string str = path;
      
      str.trim_left("\\/");
      
      return operator = (::file::path(strPath + str, m_epath));
      
   }
   
   path & path::operator /= (const string & str)
   {
      
      return operator /=(::file::path(str));
      
   }
   
   path & path::operator /= (const char * psz)
   {
      
      return operator /=(::file::path(psz));
      
   }

   void path::set_type(e_path epath)
   {
      
      if(epath != m_epath)
      {
         
         m_epath = epath;
         
         ::string::operator = (normalize_path(*this, m_epath));
                               ;
      }
                               
   }
   
   

   
   
   path & path::operator = (const ::file::path & path)
   {
      
      if(&path != this)
      {
         
         string::operator  = ((const string &) path);
         *((path_meta *)this) = (const path_meta &)path;
         
      }
      
      return *this;
      
      
   }
   

   path & path::operator = (const string & str)
   {
      
      *((path_meta*)this) = path_meta();
      
      m_epath = is_url_dup(str) ? path_url : path_file;

      string::operator  = (normalize_path(str, m_epath));
      
      return *this;
      
   }
   
   
   bool path::operator == (const path & path) const
   {
      
      return is_equal(path);
      
   }
   
   bool path::operator == (const string & str) const
   {
      
      return operator == (path(str));
   
   }
   
   
   bool path::operator == (const char * psz) const
   {
      
      return operator == (string(psz));
   
   }
   
   
   //bool path::operator == (const var & var) const;
   
   bool path::operator != (const path & path) const
   {
      
      return !is_equal(path);
      
   }
   
   
   bool path::operator != (const string & str) const
   {
      
      return operator != (path(str));
   
   }
   
   
   bool path::operator != (const char * psz) const
   {
      
      return operator != (string(psz));
   
   }
   
   
   //bool operator != (const var & var) const;
   
   
   path path::operator + (const path & path) const
   {
      
      return ::file::path((const string &)*this  + string((const string &)path), m_epath);
      
   }
   
   
   path path::operator + (const string & str) const
   {
      
      return ::file::path((const string &)*this + string((const string &)str),m_epath);
      
   }

   
   path path::operator + (const char * psz) const
   {
      
      return operator + (string(psz));
   
   }
   
   
   //path operator + (const var & var) const;
   //path operator + (const property & property) const;
   //path operator + (const id & id) const;
   
   //path & operator += (const path & path);
   //path & operator += (const string & str);
   //path operator / (const path & path) const;
   //path operator / (const string & str) const;
   //path operator / (const char * psz) const;
   //path operator / (const property & property) const;
   
   //path & operator /= (const path & path);
   //path & operator /= (const string & str);
   //path & operator /= (const char * psz);
   
   
   
   //::file::path & file_cat(const string & str) { return *this + str; }
   
   //::file::path & operator | (const string & str) { return file_cat(str); } // what is good here is the operator precedence
   
   //string arg(const string & str) const { return ((const string &)*this) + str; }
   
   //string operator << (const string & str) const { return arg(str); }
   
   path & path::operator = (const char * psz)
   {
      
      return operator = (string(psz));
   
   }
   
   
   path & path::operator += (const char * psz)
   {
      
      return operator += (string(psz));
   
   }
   
   //path & operator = (const var & var);
   //path & operator += (const var & var);
   
   path & path::operator = (const wstring & wstr)
   {
      
      return operator = (string(wstr));
   
   }
   
   path & path::operator += (const wstring & wstr) { return operator += (string(wstr)); }
   
   path & path::operator = (const unichar * psz) { return operator = (wstring(psz)); }
   path & path::operator += (const unichar * psz) { return operator += (wstring(psz)); }
   
   //path operator * () const;
   
   //path operator -- () const;
   //path operator -- (int) const { return operator --(); }
   
   
   string & path::to_string(string & str) const
   {
      return str = (const string &)*this;
   }
   
//   path sibling(const path & path) const;
//   path sibling(const string & str) const;
//   path sibling(const char * psz) const;
   
   path path::operator * (const path & path) const
   {
      
      return sibling(path);
      
   }
   
   path path::operator * (const string & str) const { return operator * (::file::path(str)); }
   path path::operator * (const char * psz) const { return operator * (::file::path(psz)); }
   //path path::operator * (const property & property) const;
   
   path & path::operator *= (const path & path)
   {
      
      if(this != &path)
      {
         
         *this = sibling(path);
         
      }
      
      return *this;
      
   }
   
   path & path::operator *= (const string & str) { return operator *= (::file::path(str)); }
   path & path::operator *= (const char * psz) { return operator *= (::file::path(psz)); }
   //path & operator *= (const property & property);
   
   ::file::path path::title() const
   {
      return ::file_title_dup(operator const char*());
   }
   
   ::file::path path::name() const
   {
      if(m_iName < 0)
         ((path *) this)->m_iName = find_file_name();
      return Mid(m_iName);
   }
   
   index path::find_file_name() const
   {
      return MAX(0, reverse_find(sep()) + 1);
   }
   
   //bool is_equal(const ::file::path & path2) const;
   
   //string extension() const;
   
   string path::ext() const
   {
      return extension();
   }
   
   //string final_extension() const;
   
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
   
   //void split(patha & patha) const;
   bool path::is_relative()
   {
      return file_path_is_relative_dup(*this) != FALSE;
   }
   
//   patha & ascendants_path(patha & patha) const;
//   patha & ascendants_name(patha & namea) const;
//   patha ascendants_path() const;
//   patha ascendants_name() const;
   
   path path::relative() const
   {
      
      return Mid(MAX(0,m_iRelative));
   
   }
   
   
//   path folder() const;
//   path folder(int i) const;
   path path::up() const
   {
      
      return folder();
   
   }
   
   
   path path::up(int i) const
   {
      
      return folder(i);
   
   }
   
   
//   inline path & go_up();
//   path & go_up(int i);
   path & path::operator -= (int i)
   {
      
      return go_up(i);
   
   }
   
   



   e_path get_path_type(const string & str, e_path epathForce)
   {
   
      if(epathForce != path_none)
      {
      
         return epathForce;
      
      }
      else if(is_url_dup(str))
      {
         
         return path_url;
      
      }
      else
      {
      
         return path_file;
      
      }
   
   }

   
   string normalize_path(string strPath, e_path epath)
   {
   
      strPath = defer_solve_relative_compresions(strPath);
   
      if(strPath.has_char())
      {
      
         strPath.trim_right("\\/");
      
         strPath.replace(path_osep(epath),path_sep(epath));
         
      }
   
      return strPath;
   
   }

   
} // namespace file



