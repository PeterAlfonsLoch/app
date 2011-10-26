#pragma once


namespace windesk
{

class CLASS_DECL_CA2_WINDESK menu_view : 
   public userex::split_view,
   public FileManagerCallbackInterface,
   public windesk::form_callback
{
public:

   enum EMenuView
   {
      MenuViewLeft,
      MenuViewRight,
   };

	menu_view(::ca::application * papp);

	virtual ~menu_view();

   virtual void install_message_handling(::user::win::message::dispatch * pinterface);

   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
	virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   void on_create_view(::user::view_creator_data * pcreatordata);

   void OnFileManagerOpenFile(
      ::filemanager::data * pdata, 
      ::fs::item_array & itema);

   DECL_GEN_SIGNAL(_001OnMenuMessage)
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

	DECL_GEN_SIGNAL(_001OnCreate)
};


} // namespace windesk

