#pragma once


namespace winshelllink
{


   class CLASS_DECL_CA2_WINSHELLLINK pane_view : 
      virtual public ::userex::pane_tab_view,
      virtual public FileManagerCallbackInterface,
      virtual public winshelllink::form_callback
   {
   public:

      
      pane_view(::ca::application * papp);
      virtual ~pane_view();
      
      
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);


      void on_create_view(::user::view_creator_data * pcreatordata);
      void on_show_view();


	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      void OnFileManagerOpenFile(::filemanager::data * pdata,  ::fs::item_array & itema);

	   void rotate();

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnMenuMessage)


   };


} // namespace winshelllink

