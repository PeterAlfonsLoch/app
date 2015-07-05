#pragma once


namespace user
{


   class CLASS_DECL_BASE form_callback:
      virtual public ::object
   {
   public:


      strsp(::user::form_window)                        	m_mapform;


      form_callback();
      virtual ~form_callback();


      virtual void on_update(::user::impact * pform,sp(::user::impact) pSender,LPARAM lHint,object* phint);
      virtual bool BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent);
      virtual void OnUser123(WPARAM wparam,LPARAM lparam);
      virtual void OnBeforeNavigate2(::html::data * pdata,var & varFile,uint32_t nFlags,const char * lpszTargetFrameName,byte_array& baPostedData,const char * lpszHeaders,bool* pbCancel);
      virtual void _001InitializeFormPreData(::user::form_window * pform);

      form_view * get_form_view(const string & strId);
      ::user::document * get_form_document(const string & strId);

   };


} // namespace user


