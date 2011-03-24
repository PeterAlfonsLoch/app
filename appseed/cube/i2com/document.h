#pragma once

namespace i2com
{

   class view;

   class comm_view;

   class CLASS_DECL_CA2_CUBE document :
      virtual public form_document,
      virtual public rtprx::document,
      virtual public rtptx::document
   {
   public:
      string               m_strTopic;
      view *               m_ppaneview;
      i2com::comm_view *   m_pcommview;

      document(::ca::application * papp);  
      virtual ~document();

      
      virtual BOOL on_new_document();


      virtual bool on_open_document(var varFile);


      virtual void OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

      DECL_GEN_VSIGNAL(data_on_after_change)

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace i2com