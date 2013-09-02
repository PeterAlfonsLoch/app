#pragma once


namespace xml
{


   class edit;


   class CLASS_DECL_ca2 document :
      public node,
      public ::ca2::data
   {
   public:


      string_to_string_map       entitiesHash;
      string_to_string_map       extEntitiesHash;
      parse_info *               m_pparseinfo;
      string                     m_strLocation;
      string                     m_strData;
      sp(::xml::edit)              m_pedit;


      document(sp(::application) papp, parse_info * pparseinfo = NULL);
      virtual ~document();
    

      string consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt);
      char * patch_entity_ref(const char * & pszXml, bool useExtEnt, ...);

      node * get_root();
      
      bool load_location(const char * psz);
      bool load(sp(::file::file) pfile);
      bool load(const char * psz);

      document & operator = (document & document);


      virtual void edit(::ca2::base_edit * pbaseedit);


      inline sp(::xml::edit) validate_edit(::ca2::base_edit * pbaseedit)
      {
         return ::ca2::data::validate_edit < ::xml::edit > (pbaseedit);
      }


   };


} // namespace xml


