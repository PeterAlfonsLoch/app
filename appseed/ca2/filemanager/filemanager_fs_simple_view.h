#pragma once

namespace filemanager
{


   namespace fs
   {

      namespace simple
      {
      
         class tree_view;
         class list_view;

         class CLASS_DECL_ca view :
            virtual public ::userbase::split_view
         {
         public:
            tree_view * m_ptree;
            list_view * m_plist;
            ::ex1::request_interface * m_prequestinterface;

            view(::ax::application * papp);

            void install_message_handling(::gen::message::dispatch * pinterface);

            void open_file(__int64 iFolder, const char * lpszFileName, const char * pszExt);
            void open_folder(__int64 iFolder);
            void start_music();
            void start_root();
            void CreateViews();

            void set_request_interface(::ex1::request_interface * prequestinterface);

            virtual ~view();
         #ifdef _DEBUG
            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;
         #endif

            DECL_GEN_SIGNAL(on_request_response);

         };


      } // namespace simple


   } // namespace fs


} // namespace mplite
