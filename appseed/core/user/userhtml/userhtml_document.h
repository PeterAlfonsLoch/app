#pragma once


class CLASS_DECL_CORE html_document :
   virtual public ::user::object,
   virtual public ::database::client,
   virtual public ::user::form_callback
{
public:

   
   html_document(sp(base_application) papp);
   virtual ~html_document();

   
   virtual void OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);
   
   virtual ::html::data * get_html_data();
   DECL_GEN_VSIGNAL(data_on_after_change)

   virtual bool open_document(var varFile);

   virtual bool on_new_document();

#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   bool on_open_document(var varFile);

   virtual bool on_simple_update(cmd_ui * pcmdui);
   virtual bool on_simple_action(id id);

   virtual void soft_reload();


};



