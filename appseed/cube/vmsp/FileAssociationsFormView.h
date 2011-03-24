#pragma once


class CLASS_DECL_CA2_CUBE FileAssociationsFormView :
   public form_view
{
public:
   FileAssociationsFormView(::ca::application * papp);

   virtual void _001InitializeFormPreData();
//   virtual void DoDataExchange(CDataExchange* pDX);  
   virtual ~FileAssociationsFormView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   afx_msg void OnForceKarRegistration();
   afx_msg void OnForceMidRegistration();
   afx_msg void OnUpdateForceKarRegistration(cmd_ui * pcmdui);
   afx_msg void OnUpdateForceMidRegistration(cmd_ui * pcmdui);
};

