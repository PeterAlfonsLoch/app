#pragma once

class image_list;


class CLASS_DECL_ca2 BaseButtonControl :
   virtual public ::userbase::button
{
public:


   image_list *      m_pimagelistNormal;
   image_list *      m_pimagelistItemHover;
   image_list *      m_pimagelistSubItemHover;
   int32_t               m_iImageNormal;
   int32_t               m_iImageItemHover;
   int32_t               m_iImageSubItemHover;


   BaseButtonControl(::ca::applicationsp papp);
   virtual ~BaseButtonControl();


   virtual void _003CustomWindowProc(::ca::signal_object * pobj);


   virtual bool pre_create_window(CREATESTRUCT& cs);
   

   virtual void install_message_handling(::ca::message::dispatch * pdispatch);

   void UpdateDrawingObjects();
   void UpdateWndRgn();
   void _001OnDraw(::ca::graphics * pdc);

   

};

