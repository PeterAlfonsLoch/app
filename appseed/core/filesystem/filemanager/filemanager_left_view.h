#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE left_view :
      virtual public ::user::split_view,
      virtual public data_interface
   {
   public:


      left_view(sp(::base::application) papp);

      void on_create_views();

      void FileManagerBrowse(const char * lpcwstr, ::action::context actioncontext);


      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
      virtual ~left_view();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };



} // namespace filemanager