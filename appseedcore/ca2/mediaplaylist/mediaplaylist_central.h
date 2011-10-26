#pragma once


namespace userbase
{
   class multiple_document_template;
}


namespace mediaplaylist
{


   class document;
   class central_callback_interface;


   class CLASS_DECL_ca central : 
      virtual public pha(document)
   {
   public:


      userbase::multiple_document_template *    m_pdoctemplate;
      ph(document)                              m_pplaylistdocDefault;
      ph(document)                              m_pplaylistdocCurrent;
      central_callback_interface *              m_pcallback;
      ::ca::type_info                           m_typeinfoFrameWnd;
      ::ca::type_info                           m_typeinfoView;
      string                                    m_strMatter;


      central(::ca::application * papp);
      virtual ~central();

      bool m_bOpenPlaylist;
      bool m_bBeforeOpenPlaylist;
   
      bool Initialize(::ca::application * papp, central_callback_interface * pcallback);

      virtual void on_delete(::ca::ca * poc);
      document * GetDefaultPlaylist();
      document * GetCurrentPlaylist(bool bMakeVisible = false, ::user::interaction * puieParent = NULL);

      document * OpenDefaultPlaylist(bool bMakeVisible, ::user::interaction * puieParent = NULL);
      document * OpenPlaylist(const char * lpcszPath, bool bMakeVisible, ::user::interaction * puieParent = NULL);

      void OnCloseDefaultPlaylist();
      static central & AppGetPlaylistCentral(::ca::application * papp);
      bool GetDefaultPath(string & str);


   };


} // namespace mediaplaylist

