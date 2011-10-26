#pragma once


class _declspec(dllexport) biteditor_child_frame :
   public simple_child_frame
{
public:

   
   simple_toolbar        m_toolbar;


   biteditor_child_frame(::ca::application * papp);

   bool CreateBars();
   bool DestroyBars();

   virtual ~biteditor_child_frame();

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnAppLanguage)


};

