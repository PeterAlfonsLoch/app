#pragma once


namespace xml
{


   class edit;


   class CLASS_DECL_ca document :
      public node,
      public ::ca::data
   {
   public:


      string_to_string_map       entitiesHash;
      string_to_string_map       extEntitiesHash;
      parse_info *               m_pparseinfo;
      string                     m_strLocation;
      string                     m_strData;
      ::xml::edit *              m_pedit;


      document(::ca::application * papp, parse_info * pparseinfo = ::null());
      virtual ~document();
    

      string consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt);
      char * patch_entity_ref(const char * & pszXml, bool useExtEnt, ...);

      node * get_root();
      
      bool load_location(const char * psz);
      bool load(::ca::file * pfile);
      bool load(const char * psz);

      document & operator = (document & document);


      virtual void edit(::ca::base_edit * pbaseedit);


      inline ::xml::edit * validate_edit(::ca::base_edit * pbaseedit)
      {
         return ::ca::data::validate_edit < ::xml::edit > (pbaseedit);
      }


   };


} // namespace xml


