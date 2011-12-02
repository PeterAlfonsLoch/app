#pragma once


namespace fontopus
{

   class CLASS_DECL_ca license :
      virtual public ::radix::object
   {
   public:

      class CLASS_DECL_ca info
      {
      public:
         string      m_strId;
         bool        m_bLicensed;
      };

      collection::string_map < info >  m_mapInfo;

      license(::ax::application * papp);
      virtual ~license();

      bool has(const char * pszId, bool bInteractive = true);
      bool check(const char * pszId, bool bInteractive = true);

      count clear_all_cache();
      bool clear_cache(const char * pszId);

   };


} // namespace fontopus



