#pragma once


namespace file
{

   class CLASS_DECL_AURA listing:
   // recursive fetchings should set a meaningful m_iRelative value at each returned path
      virtual public ::file::patha
   {
   public:

      operator bool () const
      {
         return m_cres;
      }

      listing & operator = (e_context_switcher_failed) { m_cres = failure; return *this; }

      class CLASS_DECL_AURA provider
      {
      public:

         virtual listing & perform_file_listing(listing & listing) = 0;

      };

      provider *        m_pprovider;
      ::file::path      m_path;
      bool              m_bFile = true;
      bool              m_bDir = true;
      // recursive fetchings should set a meaningful m_iRelative value at each returned path
      bool              m_bRecursive = false;
      string            m_strPattern;
      e_extract         m_eextract = extract_first;
      stringa           m_straIgnoreName;
      bool              m_bAccumul = false;
      cres              m_cres;
      stringa           m_straTitle;

      listing(provider * pprovider = NULL);
      virtual ~listing();


      path  & add_child(const ::file::path & path)
      {
         return add(m_path / path);
      }


      listing & ignore(const string & strName)
      {

         m_straIgnoreName.add(strName);

         return *this;

      }

      listing & ls(const ::file::path & path)
      {
         m_path = path;
         return ls();
      }

      listing & ls_file(const ::file::path & path)
      {
         m_path = path;
         m_bDir = false;
         return ls();
      }

      listing & ls_dir(const ::file::path & path)
      {
         m_path = path;
         m_bFile = false;
         return ls();
      }

      listing & rls(const ::file::path & path)
      {
         m_path = path;
         m_bRecursive = true;
         return ls();
      }

      listing & rls_file(const ::file::path & path)
      {
         m_path = path;
         m_bRecursive = true;
         m_bDir = false;
         return ls();
      }

      listing & rls_dir(const ::file::path & path)
      {
         m_path = path;
         m_bRecursive = true;
         m_bFile = false;
         return ls();
      }



      listing & ls_pattern(const ::file::path & path, const string & strPattern)
      {
         m_path = path;
         m_strPattern = strPattern;
         return ls();
      }

      listing & ls_pattern_file(const ::file::path & path,const string & strPattern)
      {
         m_path = path;
         m_strPattern = strPattern;
         m_bDir = false;
         return ls();
      }

      listing & ls_pattern_dir(const ::file::path & path,const string & strPattern)
      {
         m_path = path;
         m_strPattern = strPattern;
         m_bFile = false;
         return ls();
      }

      listing & rls_pattern(const ::file::path & path,const string & strPattern)
      {
         m_path = path;
         m_strPattern = strPattern;
         m_bRecursive = true;
         return ls();
      }

      listing & rls_pattern_file(const ::file::path & path,const string & strPattern)
      {
         m_path = path;
         m_strPattern = strPattern;
         m_bRecursive = true;
         m_bDir = false;
         return ls();
      }

      listing & rls_pattern_dir(const ::file::path & path,const string & strPattern)
      {
         m_path = path;
         m_strPattern = strPattern;
         m_bRecursive = true;
         m_bFile = false;
         return ls();
      }

      listing & ls();

      void clear_results() { m_cres.release(); remove_all(); }

      string os_pattern() const { return m_strPattern.is_empty() ? string("*.*") : m_strPattern;  }

   };



} // namespace file





