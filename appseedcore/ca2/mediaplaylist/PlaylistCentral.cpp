#include "StdAfx.h"

PlaylistCentral::PlaylistCentral(::ca::application * papp) :
   ca(papp)
{
   m_bOpenPlaylist               = false;
   m_bBeforeOpenPlaylist               = false;
   m_pdoctemplate                = NULL;
   m_pplaylistdocDefault         = NULL;
   m_pplaylistdocCurrent         = NULL;
   m_pcallback                   = NULL;
}

PlaylistCentral::~PlaylistCentral()
{
}

PlaylistDoc * PlaylistCentral::OpenPlaylist(const char * lpszPathName, bool bMakeVisible, ::user::interaction * puieParent)
{
   if(m_bOpenPlaylist)
      return NULL;
   PlaylistDoc * pdoc = NULL;
   
   if(m_pcallback != NULL && !m_bBeforeOpenPlaylist)
   {
      keeper <bool> keepBeforeOpenPlaylist(&m_bBeforeOpenPlaylist, true, false, true);
      pdoc = m_pcallback->OnBeforeOpenPlaylist();
      if(pdoc != NULL)
         return pdoc;
   }
   keeper <bool> keepOpenPlaylist(&m_bOpenPlaylist, true, false, true);
   
   pdoc = dynamic_cast < PlaylistDoc * > (m_pdoctemplate->open_document_file(
      lpszPathName, bMakeVisible ? TRUE : FALSE, puieParent));

   if(pdoc != NULL)
   {
      add(pdoc);
      PlaylistViewUpdateHint uh;
      uh.SetHint(PlaylistViewUpdateHint::HintInitial);
      pdoc->update_all_views(NULL, 0, &uh);
   }
   return pdoc;
}

PlaylistCentral & PlaylistCentral::AppGetPlaylistCentral(::ca::application * papp)
{
   return PlaylistCentralContainer::AppGetPlaylistCentral(papp);   
}

void PlaylistCentral::OnCloseDefaultPlaylist()
{

}

PlaylistDoc * PlaylistCentral::OpenDefaultPlaylist(bool bMakeVisible, ::user::interaction * puieParent)
{
   if(m_pplaylistdocDefault != NULL)
      return m_pplaylistdocDefault;
   string strFile;
   GetDefaultPath(strFile);
   PlaylistDoc * pdoc = NULL;
   if(System.file().exists(strFile))
   {
      pdoc = OpenPlaylist(strFile, bMakeVisible, puieParent);
   }
   else
   {
      pdoc = OpenPlaylist(NULL, bMakeVisible, puieParent);
   }
   if(pdoc == NULL)
      return NULL;
   pdoc->set_path_name(strFile);
   pdoc->set_new(false);
   string str;
//xxx   str.load_string(IDS_DEFAULT_PLAYLIST_TITLE);
   pdoc->set_title(str);
   m_pplaylistdocDefault = pdoc;
   return pdoc;
}


PlaylistDoc * PlaylistCentral::GetDefaultPlaylist()
{
   if(m_pplaylistdocDefault != NULL)
      return m_pplaylistdocDefault;
   return m_pplaylistdocDefault;
}

PlaylistDoc * PlaylistCentral::GetCurrentPlaylist(bool bMakeVisible, ::user::interaction * puieParent)
{
   if(m_pplaylistdocCurrent == NULL)
   {
      m_pplaylistdocCurrent = OpenDefaultPlaylist(bMakeVisible, puieParent);
   }
   return m_pplaylistdocCurrent;
}

bool PlaylistCentral::GetDefaultPath(string & str)
{
   str = Application.dir().userdata("veriwell\\musical player", "default.vpl");
   return true;
}

void PlaylistCentral::on_delete(::ca::ca * pdoc)
{
   if(m_pplaylistdocCurrent == pdoc)
   {
      m_pplaylistdocCurrent = NULL;
   }
   if(m_pplaylistdocDefault == pdoc)
   {
      m_pplaylistdocDefault = NULL;
   }
}


bool PlaylistCentral::Initialize(::ca::application * papp, PlaylistCentralCallbackInterface * pcallback)
{
   m_papp = papp;
   m_pcallback = pcallback;
   pcallback->m_pcentral = this;

   m_pdoctemplate = new userbase::multiple_document_template(
      m_papp,
      m_strMatter,
      &typeid(PlaylistDoc),
      m_typeinfoFrameWnd, // custom MDI child frame
      m_typeinfoView);
   
   if(m_pdoctemplate == NULL)
      return false;

   return true;
}