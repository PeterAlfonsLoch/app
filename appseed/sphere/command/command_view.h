#pragma once


namespace command
{

   class CLASS_DECL_SPHERE view :
      virtual public ::user::impact,
      virtual public ::user::interaction
   {
   public:

      enum e_message
      {
         MessageOp = WM_USER + 1123,
      };

      enum EOp
      {
         OpUpdateCurrentArea,
      };

	   view(::aura::application * papp);
	   virtual ~view();


   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      void GetDateTime(string & strDateTime);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool pre_create_window(::user::create_struct& cs);
	   virtual void OnDraw(::draw2d::graphics * pgraphics);      // overridden to draw this ::view
      virtual void _001OnInitialUpdate();
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
	   virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);

      ::user::document * get_document();

	   DECL_GEN_SIGNAL(_001OnDestroy);
	   DECL_GEN_SIGNAL(_001OnSize);
	   DECL_GEN_SIGNAL(_001OnPaint);
	   DECL_GEN_SIGNAL(_001OnCreate);
	   DECL_GEN_SIGNAL(_001OnContextMenu);
	   DECL_GEN_SIGNAL(_001OnSetCursor);
	   DECL_GEN_SIGNAL(_001OnOp);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      virtual void _001OnTabClick(int32_t iTab);
   };


} // namespace command


