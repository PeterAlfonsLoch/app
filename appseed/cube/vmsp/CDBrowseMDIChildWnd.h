#pragma once

class CLASS_DECL_CA2_CUBE CDBrowseMDIChildWnd :
   virtual public ::userbase::mdi_child_window
{
public:
   CDBrowseMDIChildWnd(::ca::application * papp);

   virtual ~CDBrowseMDIChildWnd();
};
