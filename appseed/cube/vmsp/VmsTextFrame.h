#pragma once
class CWndFrameworkV033;

class CLASS_DECL_CA2_CUBE CVmsTextFrame :
   public simple_frame_window
{
public:
   CVmsTextFrame(::ca::application * papp);

//   SimpleReBar         m_rebar;
   simple_toolbar      m_wndToolBarStandard;


   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);

   virtual ~CVmsTextFrame();

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

