#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC top_view:
      virtual public ::user::split_view
   {
   public:


      edit_view *             m_peditview;
      toggle_view *           m_ptoggleview;
      view *                  m_pview;


      top_view(::aura::application * papp);
      virtual ~top_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_views();

      virtual void on_update(::aura::impact * pSender,LPARAM lHint,object* pHint);


   };


} // namespace turboc







