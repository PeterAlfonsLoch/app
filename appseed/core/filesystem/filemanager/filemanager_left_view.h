#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE left_view :
      virtual public ::user::split_view,
      virtual public impact
   {
   public:


      sp(::user::tree)           m_pusertree;
      sp(::filemanager::tree)    m_ptree;


      left_view(sp(::base::application) papp);
      virtual ~left_view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      void on_create_views();

      void FileManagerBrowse(const char * lpcwstr, ::action::context actioncontext);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

   };



} // namespace filemanager



