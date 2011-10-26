#pragma once


namespace veriview 
{

   class pane_view;

   class CLASS_DECL_CA2_TESSERACT a_view :
      virtual public ::userbase::split_view
   {
   public:


      pane_view *       m_ppaneview;


      a_view(::ca::application * papp);



      main_document * get_document();
      html::data * m_pdata;

      void CreateViews();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
   
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual ~a_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace veriview