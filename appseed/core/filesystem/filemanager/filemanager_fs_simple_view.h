#pragma once


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         class list_view;


         class CLASS_DECL_CORE view :
            virtual public ::user::split_view
         {
         public:
            
            
            sp(tree)             m_ptree;
            sp(::user::tree)     m_pusertree;

            sp(list_view)        m_plist;
            request_interface *  m_prequestinterface;

            
            view(sp(::axis::application) papp);
            virtual ~view();


            void install_message_handling(::message::dispatch * pinterface);

            void open_file(int64_t iFolder, const char * lpszFileName, const char * pszExt);
            void open_folder(int64_t iFolder);
            void start_music();
            void start_root();
            void CreateViews();

            void set_request_interface(request_interface * prequestinterface);

         #ifdef DEBUG
            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;
         #endif

            DECL_GEN_SIGNAL(on_request_response);

         };


      } // namespace simple


   } // namespace fs


} // namespace mplite
