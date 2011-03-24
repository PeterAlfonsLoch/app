#pragma once

namespace verisimplevideo
{

   class document;

   class CLASS_DECL_CA2_CUBE view :
      virtual public ::userbase::view
   {
   public:

      ex1::filesp       m_file;
      video::player *   m_pplayer;
      
      view(::ca::application * papp);
      virtual ~view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);


      virtual void _001OnDraw(::ca::graphics * pdc);

      
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint);

      document * get_document();



      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnExecutePlay)


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace verisimplevideo
