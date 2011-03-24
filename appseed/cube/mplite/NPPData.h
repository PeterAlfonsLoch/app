#pragma once

class document;
class view;

class CLASS_DECL_CA2_CUBE CNPPData :
   public ::radix::object
{
public:
   void UpdateWindowPos();
   ::view * GetView();
   frame_window * GetFrame();
   bool CreateDocTemplate();
   bool open_document_file(HWND hwnd, const char * lpcsz);
   bool OpenPlayerFile(const char * lpcszFilePath);
   CNPPData(::ca::application * papp);
   virtual ~CNPPData();

   HWND                        m_hwndParent;
   musctrl::single_document_template *    m_pdoctemplate;
   document *    m_pdoc;
   string                     m_strFilePath;
   rect                        m_rectLast;


};
