#pragma once


namespace querydb
{


   class CLASS_DECL_CA2_QUERYDB query_view : 
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

	   query_view(::ca::application * papp);
	   virtual ~query_view();
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      void on_show();

	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      void on_create_view(::user::view_creator_data * pcreatordata);


      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace querydb

