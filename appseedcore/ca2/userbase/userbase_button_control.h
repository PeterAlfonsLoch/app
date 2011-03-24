#pragma once

class image_list;


class CLASS_DECL_ca BaseButtonControl :
   virtual public ::userbase::button
{
public:
   BaseButtonControl(::ca::application * papp);

   image_list *      m_pimagelistNormal;
   image_list *      m_pimagelistItemHover;
   image_list *      m_pimagelistSubItemHover;
   int               m_iImageNormal;
   int               m_iImageItemHover;
   int               m_iImageSubItemHover;

   virtual void _003CustomWindowProc(gen::signal_object * pobj);


   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

   void UpdateDrawingObjects();
   void UpdateWndRgn();
   void _001OnDraw(::ca::graphics * pdc);

   virtual ~BaseButtonControl();

};

