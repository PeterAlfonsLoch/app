#pragma once

namespace userbase
{
   class multiple_document_template;
}

class PlaylistDoc;
class PlaylistCentralCallbackInterface;

class CLASS_DECL_ca PlaylistCentral : 
   virtual public pha(PlaylistDoc)
{
public:
   userbase::multiple_document_template *    m_pdoctemplate;
   ph(PlaylistDoc)                           m_pplaylistdocDefault;
   ph(PlaylistDoc)                           m_pplaylistdocCurrent;
   PlaylistCentralCallbackInterface *        m_pcallback;
   ::ca::type_info                           m_typeinfoFrameWnd;
   ::ca::type_info                           m_typeinfoView;
   string                                    m_strMatter;

   PlaylistCentral(::ca::application * papp);
   virtual ~PlaylistCentral();

   bool m_bOpenPlaylist;
   bool m_bBeforeOpenPlaylist;
   
   bool Initialize(::ca::application * papp, PlaylistCentralCallbackInterface * pcallback);

   virtual void on_delete(::ca::ca * poc);
   PlaylistDoc * GetDefaultPlaylist();
   PlaylistDoc * GetCurrentPlaylist(bool bMakeVisible = false, ::user::interaction * puieParent = NULL);

   PlaylistDoc * OpenDefaultPlaylist(bool bMakeVisible, ::user::interaction * puieParent = NULL);
   PlaylistDoc * OpenPlaylist(const char * lpcszPath, bool bMakeVisible, ::user::interaction * puieParent = NULL);

   void OnCloseDefaultPlaylist();
   static PlaylistCentral & AppGetPlaylistCentral(::ca::application * papp);
   bool GetDefaultPath(string & str);

};

