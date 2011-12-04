#pragma once

class CLASS_DECL_ca2 dialog :
   virtual public ::user::form_callback
{
public:


   form_document *            m_pdocument;
   simple_frame_window *      m_pframe;


   dialog(::ca::application * papp);
   virtual ~dialog();

   virtual void on_position_parent_frame();

   virtual void EndModalLoop(id nResult);

   virtual bool show(const char * pszMatter, gen::property_set & propertyset);
   
   virtual void on_show(const char * pszMatter, gen::property_set & propertyset);





   // MFC dialog compatibility : TODO, ca2fy, at least the member function names
   virtual void OnCancel();
   virtual void OnOK();
   //virtual bool UpdateData(bool bSave);
   // UpdateData true
   virtual void form_from_user();
   // UpdateData false
   virtual void form_to_user();
   //virtual BOOL OnInitDialog();
   // substituir, replace _001Initialize

};


