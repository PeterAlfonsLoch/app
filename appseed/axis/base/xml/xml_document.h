#pragma once


namespace xml
{


   class edit;


   class CLASS_DECL_BASE document :
      public node,
      public ::data::data
   {
   public:


      string_to_string       entitiesHash;
      string_to_string       extEntitiesHash;
      parse_info *               m_pparseinfo;
      string                     m_strLocation;
      string                     m_strData;
      sp(::xml::edit)              m_pedit;


      document(sp(::base::application) papp = NULL, parse_info * pparseinfo = NULL);
      virtual ~document();
    

      string consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt);
      char * patch_entity_ref(const char * & pszXml, bool useExtEnt, ...);

      node * get_root();
      
      bool load_location(const char * psz);
      bool load(::file::input_stream & is);
      bool load(const char * psz);

      document & operator = (document & document);


      virtual void edit(base_edit * pbaseedit);


      inline sp(::xml::edit) validate_edit(base_edit * pbaseedit)
      {
         return ::data::data::validate_edit < ::xml::edit > (pbaseedit);
      }


   };


} // namespace xml


