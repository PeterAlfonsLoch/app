#pragma once

namespace command
{

   class document;

   class CLASS_DECL_sphere view :
      virtual public ::user::view,
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

	   view(sp(::ca2::application) papp);
	   virtual ~view();


   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      void GetDateTime(string & strDateTime);

      virtual void _001OnDraw(::ca2::graphics * pdc);


      virtual void install_message_handling(::ca2::message::dispatch * pinterface);
      virtual bool pre_create_window(CREATESTRUCT& cs);
	   virtual void OnDraw(::ca2::graphics * pgraphics);      // overridden to draw this ::view
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnRButtonUp)
	   virtual void on_update(sp(::user::view) pSender, LPARAM lHint, ::ca2::object* pHint);

      sp(::user::document) get_document();

	   DECL_GEN_SIGNAL(_001OnDestroy)
	   DECL_GEN_SIGNAL(_001OnSize)
	   DECL_GEN_SIGNAL(_001OnPaint)
	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnContextMenu)
	   DECL_GEN_SIGNAL(_001OnSetCursor)
	   DECL_GEN_SIGNAL(_001OnOp)
      DECL_GEN_SIGNAL(_001OnShowWindow)
      virtual void _001OnTabClick(int32_t iTab);
   };


} // namespace command


