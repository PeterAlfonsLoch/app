#pragma once


namespace whiteboard
{

   enum e_site
   {
      SiteUpHomeUrl = 0,
      SiteHomeUrl,
      SiteBookmark,
      SiteAnnotate,
      SiteNotifyUrl,
      SiteCalendar,
      SiteLogin,
      SitePulseUserEvent,
      SiteDbHomeBaseUrl,
      SiteWb,
      SiteMrts,
      SiteInvalid
   };

   class CLASS_DECL_CA2_CUBE site
   {
   public:
      site();
      site(
         e_site esite,
         const char * lpcszDefaultUrl,
         const char * lpcszProfileKey,
         const char * lpcszTag);

      e_site       m_esite;
      string     m_strDefaultUrl;
      string     m_strProfileKey;
      string     m_strTag;
   };

} // namespace whiteboard