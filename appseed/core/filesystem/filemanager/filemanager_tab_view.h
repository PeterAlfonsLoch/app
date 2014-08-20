#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tab_view :
      virtual public ::userex::pane_tab_view
   {
   public:
   

      tab_view(sp(::axis::application) papp);
      virtual ~tab_view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void install_message_handling(::message::dispatch * pinterface);
      void FileManagerBrowse(const char * lpcwstr, ::action::context actioncontext);


      DECL_GEN_SIGNAL(_001OnCreate);
      
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
      

   };


} // namespace filemanager




