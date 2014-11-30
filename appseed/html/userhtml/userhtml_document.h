#pragma once


class CLASS_DECL_HTML html_document :
   virtual public ::form_document
{
public:

   
   html_document(::aura::application * papp);
   virtual ~html_document();

   
   virtual void OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);
   
   virtual ::html::data * get_html_data();
   DECL_GEN_VSIGNAL(data_on_after_change);

   virtual bool open_document(var varFile);

   virtual bool load_html(const string & str);

   virtual bool on_new_document();

   virtual void form_document_set_property_set(const property_set & set);
   virtual property_set * form_document_get_property_set();

   virtual void form_document_set_view(form_view * pview);
   virtual void form_document_set_callback(form_callback * pcallback);

#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   bool on_open_document(var varFile);

   virtual bool on_simple_update(cmd_ui * pcmdui);
   virtual bool on_simple_action(id id);

   virtual void soft_reload();

   virtual sp(::user::interaction) get_frame();





};



