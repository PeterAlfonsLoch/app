#include "StdAfx.h"

#include "mplite_library_tree_view.h"
#include "mplite_library_view.h"
#include "mplite_library_list_view.h"

namespace mplite
{
   namespace library
   {

      view::view(::ca::application * papp) :
         ca(papp),
         ::userbase::split_layout(papp),
         ::userbase::view(papp),
         ::userbase::split_view(papp),
         place_holder_container(papp)
      {
      //   m_pinetsession = NULL;
      }

      view::~view()
      {
        // if(m_pinetsession != NULL)
          //  delete m_pinetsession;
      }

      void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
      {
         ::userbase::split_view::_001InstallMessageHandling(pinterface);
      }


      #ifdef _DEBUG
      void view::assert_valid() const
      {
         ::userbase::split_view::assert_valid();
      }

      void view::dump(dump_context & dumpcontext) const
      {
         ::userbase::split_view::dump(dumpcontext);
      }
      #endif //_DEBUG

      void view::CreateViews()
      {
         SetPaneCount(2);

         SetSplitOrientation(orientation_vertical);
        
         set_position_rate(0, 0.2);

         

         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView =  &typeid(tree_view);
         m_ptree = dynamic_cast < tree_view * > (create_view(&cc, this, 100));

         m_ptree->m_pserver = this;

         SetPane(0, m_ptree, false);

         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView =  &typeid(list_view);

         m_plist = dynamic_cast < list_view * > (create_view(&cc, this, 101));

         m_plist->m_pserver = this;

         SetPane(1, m_plist, false);

         layout();

      }

      void view::Start()
      {
         ca4::http::signal * psignal = new ca4::http::signal;


         (*psignal)()["request"] = "";
         psignal->m_strUrl = "http://karaoke.veriwell.com.br/vmplightfolder.php";

         psignal->m_puser = &ApplicationUser;

         gen::emit(get_app(), this, &view::on_request_response, &Application.http(), &ca4::http::application::get, psignal);

      }

      void view::on_request_response(gen::signal_object * pobj)
      {
         SCAST_PTR(ca4::http::signal, psignal, pobj);

         string strResponse;

         psignal->m_memoryRet.to_string(strResponse);

         m_ptree->Parse((*psignal)()["request"], strResponse);
         m_plist->Parse(strResponse);

      }

      void view::Request(const char * lpsz)
      {
         string strId;

         strId = lpsz;

         string strURL;

         strURL = "http://karaoke.veriwell.com.br/vmplightfolder.php";

         strURL += "?id=" + strId;

         ca4::http::signal * psignal = new ca4::http::signal;

         (*psignal)()["request"] = lpsz;
         psignal->m_strUrl = strURL;

         psignal->m_puser = &ApplicationUser;

         gen::emit(get_app(), this, &view::on_request_response, &Application.http(), &ca4::http::application::get, psignal);
         


      }

      void view::OpenSongFile(
         int iId,
         const char * lpszFileName)
      {
         string strUrl;

         strUrl.Format("http://karaoke.veriwell.com.br/get/download.php?p_songid=%d", iId);

         //string wstrPath = System.dir().ca2("database/file/veriwell.com.br/karaoke files", lpszFileName);

         //System.http().download(strURL, wstrPath);

         PlaylistDoc * pdoc = Application.GetPlaylistCentral().GetCurrentPlaylist(true, false);
         if(pdoc != NULL)
         {
            pdoc->AddSong(
               strUrl,
               PlaylistDoc::AddSongAndPlayIfNotPlaying, 
               false,
               true);
         }
      }

   } // namespace library

} // namespace mplite