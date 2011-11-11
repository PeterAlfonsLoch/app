#pragma once

namespace ihtml
{

class CLASS_DECL_CA2_IHTML form :
   virtual public Ex1VirtualGuieInterface,
   virtual public document_container
{
public:
   form();
   virtual ~form();

   virtual void _001OnDraw(CDC * pdc);



   string m_strPathName;
   string m_strOpenOnCreate;
   rect m_rectOpen;
   
   virtual void Layout();

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

   bool open_document(const char * pszPath);
   virtual bool OpenDocument(const char * psz);

   DECL_GEN_SIGNAL(_001OnSize);
   DECL_GEN_SIGNAL(_001OnCreate);
	DECL_GEN_SIGNAL(_001OnLButtonDown)
	DECL_GEN_SIGNAL(_001OnMouseMove)
	DECL_GEN_SIGNAL(_001OnLButtonUp)

};

} // namespace ihtml