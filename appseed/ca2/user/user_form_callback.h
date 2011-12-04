#pragma once

namespace user
{
   class form;

   class CLASS_DECL_ca2 form_callback :
      virtual public ::radix::object,
      virtual public html::data_callback
   {
   public:
      form_callback();
      virtual ~form_callback();

      virtual void on_update(::user::form * pform, ::view * pSender, LPARAM lHint, ::radix::object* phint);
      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnUser123(WPARAM wparam, LPARAM lparam);
      virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
      virtual void _001InitializeFormPreData(::user::form * pform);
   };

} // namespace user