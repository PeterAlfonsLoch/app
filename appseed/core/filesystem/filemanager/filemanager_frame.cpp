#include "framework.h"


namespace filemanager
{



   frame::frame(sp(::base::application) papp) :
      element(papp),
      simple_frame_window(papp)
   {

   }

   frame::~frame()
   {

   }

   void  frame::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

   }


   bool  frame::on_create_bars()
   {
      
      sp(manager) pmanager = (GetActiveDocument());

      return pmanager->on_create_bars(this);

   }


   void  frame::install_message_handling(::message::dispatch * pinterface)
   {

      simple_frame_window::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_SETTEXT, pinterface, this, &frame::_001OnSetText);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);

   }


   void  frame::_001OnSetText(signal_details * pobj)
   {
      //   SCAST_PTR(::message::base, pbase, pobj)

      pobj->previous();

      string str;

      ::filemanager::tab_view * ptabview = GetTypedParent < ::filemanager::tab_view >();
      if (ptabview != NULL)
      {
         GetWindowText(str);
         ptabview->SetTitleById(m_idTab, str);
      }

   }



} // namespace filemanager




