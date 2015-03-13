#pragma once


namespace file
{


   class listing;


   class CLASS_DECL_AURA listing_provider
   {
   public:


      virtual listing & perform_file_listing(listing & listing) = 0;


   };


   struct CLASS_DECL_AURA listing_meta
   {

      listing_provider *   m_pprovider = NULL;
      bool                 m_bFile = true;
      bool                 m_bDir = true;
      bool                 m_bRecursive = false;
      e_extract            m_eextract = extract_first;
   };



   class CLASS_DECL_AURA listing:
      // recursive fetchings should set a meaningful m_iRelative value at each returned path
      virtual public ::file::patha,
      public listing_meta
   {
   public:

      ::file::path      m_path;
      string            m_strPattern;
      stringa           m_straIgnoreName;
      cres              m_cres;
      stringa           m_straTitle;


      operator bool () const
      {
         return m_cres;
      }

      listing & operator = (e_context_switcher_failed) { m_cres = failure; return *this; }



      listing(listing_provider * pprovider = NULL);
      listing(const listing & listing) { operator = (listing); }
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

      
      listing & rls(const ::file::path & path = cnull, e_extract eextract = extract_first)
      {
         
         m_path = path;

         m_bRecursive = true;

         m_eextract = eextract;

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

      void clear_results() { m_straTitle.remove_all(); m_cres.release(); remove_all(); }

      string os_pattern() const { return m_strPattern.is_empty() ? string("*.*") : m_strPattern;  }


      string title(index i)
      {

         if(i >= 0 && i < m_straTitle.get_count())
         {

            return m_straTitle[i];

         }

         return operator[](i).title();

      }

      listing & operator = (const listing & listing)
      {

         if(this == &listing)
            return *this;

         patha::operator         = (listing);
         *((listing_meta*)this)  = (const listing_meta &) listing;
         m_path                  = listing.m_path;
         m_strPattern            = listing.m_strPattern;
         m_straIgnoreName        = listing.m_straIgnoreName;
         m_cres                  = listing.m_cres;
         m_straTitle             = listing.m_straTitle;

         return *this;

      }

      index name_find_first_ci(const path & lpcsz,index find = 0,index last = -1) const
      {
         if(find < 0)
            find += this->get_count();
         if(last < 0)
            last += this->get_count();
         for(; find <= last; find++)
         {
            if(this->element_at(find).CompareNoCase(lpcsz) == 0)
               return find;
         }
         return -1;
      }

      bool name_move_ci(const path & lpcsz,index iIndex)
      {
         index i = name_find_first_ci(lpcsz);
         if(i < 0)
            return false;
         path p = element_at(i);
         string t = i < m_straTitle.get_count() ? m_straTitle[i] : "";
         remove_at(i);
         insert_at(iIndex,lpcsz);
         return true;
      }


      bool preferred_name(const path & lpcsz)
      {
         return name_move_ci(lpcsz,0);
      }


      ::count preferred_name(patha  & stra)
      {
         ::count count = 0;
         for(index i = stra.get_upper_bound(); i >= 0; i--)
         {
            if(preferred_name(stra[i]))
               count++;
         }
         return count;
      }



   };



} // namespace file





