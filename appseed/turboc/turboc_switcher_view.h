#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC main_view:
      virtual public ::user::split_view
   {
   public:


      top_view *              m_ptopview;
      view *                  m_pview;


      main_view(::aura::application * papp);
      virtual ~main_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_views();

      virtual void on_update(::aura::impact * pSender,LPARAM lHint,object* pHint);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


   };


} // namespace turboc





