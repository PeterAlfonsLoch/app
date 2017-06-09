#pragma once


namespace file
{


   class listing;


   class CLASS_DECL_AURA listing_provider
   {
   public:


      virtual listing & perform_file_listing(listing & listing) = 0;
      virtual listing & perform_file_relative_name_listing(listing & listing) = 0;


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
      stringa           m_straPattern;
      stringa           m_straIgnoreName;
      cres              m_cres;
      stringa           m_straTitle;


      bool succeeded () const
      {
         return m_cres.succeeded();
      }

      listing & operator = (e_context_switcher_failed) { m_cres = failure; return *this; }



      listing(listing_provider * pprovider = NULL);
      listing(const listing & listing):patha(listing) { m_nGrowBy = 128; }
      virtual ~listing();


      path  & add_child(const ::file::path & path)
      {
         return *add(m_path / path);
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



      listing & ls_pattern(const ::file::path & path, const stringa & straPattern)
      {
         m_path = path;
         m_straPattern = straPattern;
         return ls();
      }

      listing & ls_pattern_file(const ::file::path & path,const stringa & straPattern)
      {
         m_path = path;
         m_straPattern = straPattern;
         m_bDir = false;
         return ls();
      }

      listing & ls_pattern_dir(const ::file::path & path,const stringa & straPattern)
      {
         m_path = path;
         m_straPattern = straPattern;
         m_bFile = false;
         return ls();
      }

      listing & rls_pattern(const ::file::path & path,const stringa & straPattern)
      {
         m_path = path;
         m_straPattern = straPattern;
         m_bRecursive = true;
         return ls();
      }

      listing & rls_pattern_file(const ::file::path & path,const stringa & straPattern)
      {
         m_path = path;
         m_straPattern = straPattern;
         m_bRecursive = true;
         m_bDir = false;
         return ls();
      }

      listing & rls_pattern_dir(const ::file::path & path,const stringa & straPattern)
      {
         m_path = path;
         m_straPattern = straPattern;
         m_bRecursive = true;
         m_bFile = false;
         return ls();
      }

      virtual listing & ls();
      virtual listing & ls_relative_name();

      void clear_results() { m_straTitle.remove_all(); m_cres.release(); remove_all(); }


      string title(index i)
      {

         if(i >= 0 && i < m_straTitle.get_count())
         {

            return m_straTitle[i];

         }

         return operator[](i).title();

      }

      string name(index i)
      {

         if (i >= 0 && i < m_straTitle.get_count())
         {

            return m_straTitle[i];

         }

         return operator[](i).name();

      }


      void to_name()
      {

         for(index i = 0; i < get_size(); i++)
         {

            element_at(i) = element_at(i).name();

         }

      }

      listing & operator = (const listing & listing)
      {

         if(this == &listing)
            return *this;

         patha::operator         = (listing);
         *((listing_meta*)this)  = (const listing_meta &) listing;
         m_path                  = listing.m_path;
         m_straPattern           = listing.m_straPattern;
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
            if(_stricmp(this->element_at(find).name(), lpcsz) == 0)
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

   class CLASS_DECL_AURA relative_name_listing :
      virtual public listing
   {
   public:


      relative_name_listing(listing_provider * pprovider = NULL);
      relative_name_listing(const relative_name_listing & listing) { operator = (listing); }
      virtual ~relative_name_listing();


      using listing::ls;
      virtual listing & ls() override;

   };



} // namespace file



//CLASS_DECL_AURA bool matches_wildcard_criteria(const string & strCriteria, const string & strValue);
//CLASS_DECL_AURA bool matches_wildcard_criteria_ci(const string & pszCriteria, const string & strValue);

CLASS_DECL_AURA string normalize_wildcard_criteria(const string & strPattern);


CLASS_DECL_AURA bool matches_wildcard_criteria(const stringa & straCriteria, const string & strValue);
CLASS_DECL_AURA bool matches_wildcard_criteria_ci(const stringa & straCriteria, const string & strValue);


