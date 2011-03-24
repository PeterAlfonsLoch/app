#pragma once

namespace mplite
{
   namespace library
   {

      
      class tree_view;
      class list_view;

      class CLASS_DECL_CA2_CUBE view :
         virtual public ::userbase::split_view
      {
      public:
         tree_view * m_ptree;
         list_view * m_plist;

         ::mplite::library::view(::ca::application * papp);

         void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

         void OpenSongFile(int iId, const char * lpszFileName);
         void Request(const char * lpsz);
         void Start();
         void CreateViews();

         virtual ~view();
      #ifdef _DEBUG
         virtual void assert_valid() const;
         virtual void dump(dump_context & dumpcontext) const;
      #endif

         DECL_GEN_SIGNAL(on_request_response);

      };

   } // namespace library

} // namespace mplite
