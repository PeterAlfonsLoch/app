#pragma once


namespace querydb
{

class CLASS_DECL_CA2_QUERYDB menu_view : 
   public userex::split_view,
   public FileManagerCallbackInterface,
   public querydb::form_callback
{
public:

   enum EMenuView
   {
      MenuViewLeft,
      MenuViewRight,
   };

   ::filemanager::document * m_pdocStartMenu;

	menu_view(::ca::application * papp);
	virtual ~menu_view();
   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   void on_show();

	virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   void on_create_view(view_data * pviewdata);


   void OnFileManagerOpenFile(
      ::filemanager::data * pdata, 
      ::fs::item_array & itema);

   DECL_GEN_SIGNAL(_001OnMenuMessage)
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

protected:
	DECL_GEN_SIGNAL(_001OnCreate)
};


} // namespace querydb

