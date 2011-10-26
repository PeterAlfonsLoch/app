#include "StdAfx.h"


namespace mediaplaylist
{


   central::central(::ca::application * papp) :
      ca(papp)
   {
      m_bOpenPlaylist               = false;
      m_bBeforeOpenPlaylist               = false;
      m_pdoctemplate                = NULL;
      m_pplaylistdocDefault         = NULL;
      m_pplaylistdocCurrent         = NULL;
      m_pcallback                   = NULL;
   }

   central::~central()
   {
   }

   ::mediaplaylist::document * central::OpenPlaylist(const char * lpszPathName, bool bMakeVisible, ::user::interaction * puieParent)
   {
      if(m_bOpenPlaylist)
         return NULL;
      ::mediaplaylist::document * pdoc = NULL;

      if(m_pcallback != NULL && !m_bBeforeOpenPlaylist)
      {
         keeper <bool> keepBeforeOpenPlaylist(&m_bBeforeOpenPlaylist, true, false, true);
         pdoc = m_pcallback->OnBeforeOpenPlaylist();
         if(pdoc != NULL)
            return pdoc;
      }
      keeper <bool> keepOpenPlaylist(&m_bOpenPlaylist, true, false, true);

      ::ca::create_context_sp cc(get_app());

      cc->m_spCommandLine->m_varFile = lpszPathName;
      cc->m_bMakeVisible  = bMakeVisible;
      cc->m_puiParent = puieParent;

      pdoc = dynamic_cast < ::mediaplaylist::document * > (m_pdoctemplate->open_document_file(cc));

      if(pdoc != NULL)
      {
         add(pdoc);
         PlaylistViewUpdateHint uh;
         uh.SetHint(PlaylistViewUpdateHint::HintInitial);
         pdoc->update_all_views(NULL, 0, &uh);
      }
      return pdoc;
   }

   central & central::AppGetPlaylistCentral(::ca::application * papp)
   {
      return mediaplaylist::central_container::AppGetPlaylistCentral(papp);   
   }

   void central::OnCloseDefaultPlaylist()
   {

   }

   ::mediaplaylist::document * central::OpenDefaultPlaylist(bool bMakeVisible, ::user::interaction * puieParent)
   {
      if(m_pplaylistdocDefault != NULL)
         return m_pplaylistdocDefault;
      string strFile;
      GetDefaultPath(strFile);
      ::mediaplaylist::document * pdoc = NULL;
      if(Application.file().exists(strFile))
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


   ::mediaplaylist::document * central::GetDefaultPlaylist()
   {
      if(m_pplaylistdocDefault != NULL)
         return m_pplaylistdocDefault;
      return m_pplaylistdocDefault;
   }

   ::mediaplaylist::document * central::GetCurrentPlaylist(bool bMakeVisible, ::user::interaction * puieParent)
   {
      if(m_pplaylistdocCurrent == NULL)
      {
         m_pplaylistdocCurrent = OpenDefaultPlaylist(bMakeVisible, puieParent);
      }
      return m_pplaylistdocCurrent;
   }

   bool central::GetDefaultPath(string & str)
   {
      //str = Application.dir().userdata("veriwell\\musical player", "default.vpl");
      str = "uifs://Music/default_playlist.vps";
      return true;
   }

   void central::on_delete(::ca::ca * pdoc)
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


   bool central::Initialize(::ca::application * papp, ::mediaplaylist::central_callback_interface * pcallback)
   {
      m_papp = papp;
      m_pcallback = pcallback;
      pcallback->m_pcentral = this;

      m_pdoctemplate = new userbase::multiple_document_template(
         m_papp,
         m_strMatter,
         ::ca::get_type_info < ::mediaplaylist::document > (),
         m_typeinfoFrameWnd, // custom MDI child frame
         m_typeinfoView);

      if(m_pdoctemplate == NULL)
         return false;

      return true;
   }


} // namespace mediaplaylist


