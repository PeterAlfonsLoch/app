#pragma once


class CLASS_DECL_ca2 html_document :
   public ::userbase::document,
   virtual public ::database::client,
   virtual public ::user::form_callback
{
public:

   
   html_document(::ca::application * papp);
   virtual ~html_document();

   
   virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
   
   virtual ::html::data * get_html_data();
   virtual ::ca::application * get_app() const;
   DECL_GEN_VSIGNAL(data_on_after_change)

   virtual bool open_document(var varFile);

   virtual BOOL on_new_document();

#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   bool on_open_document(var varFile);

   virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
   virtual bool _001OnCommand(id id);

   virtual void soft_reload();


};



