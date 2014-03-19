#pragma once


namespace filemanager
{


   class file_list;
   class folder_list;
   class preview;
   class file_properties_form;


   class CLASS_DECL_CORE a_view :
      virtual public ::user::split_view,
      virtual public data_interface
   {
   public:

      a_view(sp(base_application) papp);
      virtual ~a_view();

      void on_create_views();

      void FileManagerBrowse(const char * lpcwstr, ::action::context actioncontext);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };



   class CLASS_DECL_CORE main_view :
      virtual public ::user::split_view,
      virtual public data_interface
   {
   public:

      file_list *         m_pfilelist;
      preview *              m_ppreview;
      file_properties_form *   m_ppropform;
      ::fs::item_array                      m_itema;

      main_view(sp(base_application) papp);
      virtual ~main_view();

      void on_create_views();

      void FileManagerBrowse(const char * lpcwstr, ::action::context actioncontext);

      bool on_simple_action(id id);

      virtual void OpenSelectionProperties();

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace filemanager




