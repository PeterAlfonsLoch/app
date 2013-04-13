#pragma once

namespace xml
{

   class CLASS_DECL_ca document :
      public node,
      virtual public ::radix::object
   {
   public:
      document(::ca::application * papp);
      virtual ~document();


      string_to_string_map       entitiesHash;
      string_to_string_map       extEntitiesHash;
      parse_info                 m_parseinfo;
      string                     m_strLocation;
      string                     m_strData;
    

      string consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt);
      char * patch_entity_ref(const char * & pszXml, bool useExtEnt, ...);

      node * get_root();
      
      char * load_location(const char * psz);

      char * load(const char * psz);

      document & operator = (document & document);
   };

} // namespace xml