#pragma once

namespace user
{

   class form;

}
namespace html
{

   class data;

}
//class form_document;


namespace user
{


   class form;


   class CLASS_DECL_BASE form_callback:
      virtual public ::object
   {
   public:


      strsp(::aura::document)		                        m_mapdoc;
      strsp(::user::form)		                        	m_mapview;


      form_callback();
      virtual ~form_callback();


      virtual void on_update(::user::form * pform,sp(::aura::impact) pSender,LPARAM lHint,object* phint);
      virtual bool BaseOnControlEvent(::user::form * pview,::user::control_event * pevent);
      virtual void OnUser123(WPARAM wparam,LPARAM lparam);
      virtual void OnBeforeNavigate2(::html::data * pdata,var & varFile,uint32_t nFlags,const char * lpszTargetFrameName,byte_array& baPostedData,const char * lpszHeaders,bool* pbCancel);
      virtual void _001InitializeFormPreData(::user::form * pform);

   };


} // namespace user

