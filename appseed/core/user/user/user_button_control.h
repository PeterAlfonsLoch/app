#pragma once

class image_list;


class CLASS_DECL_CORE BaseButtonControl :
   virtual public ::user::button
{
public:


   sp(image_list)      m_pimagelistNormal;
   sp(image_list)      m_pimagelistItemHover;
   sp(image_list)      m_pimagelistSubItemHover;
   int32_t               m_iImageNormal;
   int32_t               m_iImageItemHover;
   int32_t               m_iImageSubItemHover;


   BaseButtonControl(sp(::base::application) papp);
   virtual ~BaseButtonControl();


   virtual void _003CustomWindowProc(signal_details * pobj);


   virtual bool pre_create_window(::user::create_struct& cs);
   

   virtual void install_message_handling(::message::dispatch * pdispatch);

   void update_drawing_objects();
   void UpdateWndRgn();
   void _001OnDraw(::draw2d::graphics * pdc);

   

};

