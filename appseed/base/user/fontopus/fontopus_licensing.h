#pragma once


namespace fontopus
{


   class CLASS_DECL_BASE licensing :
      virtual public ::object
   {
   public:

      class CLASS_DECL_BASE info
      {
      public:
         string      m_strId;
         bool        m_bLicensed;
      };

      string_map < info >  m_mapInfo;

      licensing(sp(::axis::application) papp);
      virtual ~licensing();

      bool has(const char * pszId, bool bInteractive = true);
      bool check(const char * pszId, bool bInteractive = true);

      ::count clear_all_cache();
      bool clear_cache(const char * pszId);


   };


} // namespace fontopus



