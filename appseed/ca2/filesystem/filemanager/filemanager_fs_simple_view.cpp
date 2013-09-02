#include "framework.h"


namespace filemanager
{
   
   namespace fs
   {

      namespace simple
      {

         view::view(sp(::application) papp) :
            element(papp),
            ::user::split_layout(papp),
            
            ::user::split_view(papp),
            place_holder_container(papp)
         {
         //   m_pinetsession = NULL;
            m_prequestinterface = NULL;
         }

         view::~view()
         {
           // if(m_pinetsession != NULL)
             //  delete m_pinetsession;
         }

         void view::install_message_handling(::ca2::message::dispatch * pinterface)
         {
            ::user::split_view::install_message_handling(pinterface);
         }


         #ifdef DEBUG
         void view::assert_valid() const
         {
            ::user::split_view::assert_valid();
         }

         void view::dump(dump_context & dumpcontext) const
         {
            ::user::split_view::dump(dumpcontext);
         }
         #endif //DEBUG

         void view::CreateViews()
         {
            SetPaneCount(2);

            SetSplitOrientation(orientation_vertical);
        
            set_position_rate(0, 0.2);

         

            m_ptree = create_view < tree_view > ();

            m_ptree->m_pserver = this;

            SetPane(0, m_ptree, false);

            m_plist = create_view < list_view > ();

            m_plist->m_pserver = this;

            SetPane(1, m_plist, false);

            layout();

         }

         void view::start_music()
         {

            Application.http().get("http://file.veriwell.net/");
            open_folder(1000); // user ::music folder

         }

         void view::start_root()
         {

            Application.http().get("http://file.veriwell.net/");
            open_folder(1); // user root folder

         }

         void view::on_request_response(signal_details * pobj)
         {
            SCAST_PTR(::ca2::http::signal, psignal, pobj);

            string strResponse;

            psignal->m_memoryRet.to_string(strResponse);

            m_ptree->parse(strResponse);
            m_plist->parse(strResponse);

         }

         void view::open_folder(int64_t iFolder)
         {
         
            ::ca2::http::signal * psignal = new ::ca2::http::signal;

            (*psignal)()["request"] = "";
            psignal->m_strUrl.Format("http://file.veriwell.net/ifs/ls?id=%I64d", iFolder); 

            psignal->m_puser = &ApplicationUser;

            ::ca2::emit(get_app(), this, &view::on_request_response, &Application.http(), &::ca2::http::application::get, psignal);

         }

         void view::open_file(int64_t iFolder, const char * lpszFileName, const char * pszExtension)
         {
            string strUrl;

            strUrl.Format("http://file.veriwell.net/ifs/get?name=" + System.url().url_encode(lpszFileName)+ "&folder=%I64d&extension=.%s", iFolder, pszExtension);

            if(m_prequestinterface != NULL)
            {
               m_prequestinterface->add_line_uri(strUrl);
            }

         }

         void view::set_request_interface(::ca2::request_interface * prequestinterface)
         {
            m_prequestinterface = prequestinterface;
         }

      } // namespace simple

   } // namespace library

} // namespace mplite
