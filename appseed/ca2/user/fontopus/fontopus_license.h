#pragma once


namespace fontopus
{


   class CLASS_DECL_ca2 license :
      virtual public ::ca::object
   {
   public:

      class CLASS_DECL_ca2 info
      {
      public:
         string      m_strId;
         bool        m_bLicensed;
      };

      string_map < info >  m_mapInfo;

      license(sp(::ca::application) papp);
      virtual ~license();

      bool has(const char * pszId, bool bInteractive = true);
      bool check(const char * pszId, bool bInteractive = true);

      ::count clear_all_cache();
      bool clear_cache(const char * pszId);


   };


} // namespace fontopus



