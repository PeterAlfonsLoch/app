#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tab_view :
      virtual public ::userex::pane_tab_view,
      virtual public data_interface
   {
   public:
   

      tab_view(sp(base_application) papp);

      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void install_message_handling(::message::dispatch * pinterface);
      void FileManagerBrowse(const char * lpcwstr, ::action::context actioncontext);


      DECL_GEN_SIGNAL(_001OnCreate);
      
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
      virtual ~tab_view();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace filemanager




