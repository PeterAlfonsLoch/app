#pragma once

class command_document;

class CLASS_DECL_CA2_COMMAND command_view :
   virtual public ::userbase::view,
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

	command_view(::ca::application * papp);
	virtual ~command_view();


#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif


   void GetDateTime(string & strDateTime);

   virtual void _001OnDraw(::ca::graphics * pdc);


   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnRButtonUp)
	virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   command_document * get_document();

	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnOp)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   virtual void _001OnTabClick(int iTab);
};

