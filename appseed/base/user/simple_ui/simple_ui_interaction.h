#pragma once


class simple_ui;


class CLASS_DECL_BASE simple_ui_ptra : 
   public array < simple_ui * >
{
public:


};


class CLASS_DECL_BASE simple_ui :
   virtual public ::object
{
public:


   bool                             m_bVisible;
   rect                             m_rect;
   string                           m_strId;
   string                           m_strText;
   simple_ui_ptra                   m_uiptra;
   simple_ui *                      m_puiParent;
   simple_ui *                      m_puiFocus;
   ::spa::style *                   m_pstyle;


   simple_ui();
   virtual ~simple_ui();


   virtual void set_parent(simple_ui * puiParent);


   virtual void draw(::draw2d::graphics * pgraphics);
   virtual void draw_this(::draw2d::graphics * pgraphics);
   virtual void draw_children(::draw2d::graphics * pgraphics);

   virtual void draw_focus_rect(::draw2d::graphics * pgraphics);


   virtual bool on_char(int32_t iKey, const string & strChar);
   virtual bool on_lbutton_down(int32_t x, int32_t y);
   virtual bool on_lbutton_up(int32_t x, int32_t y);
   virtual bool on_mouse_move(int32_t x, int32_t y);


   virtual bool on_action(const char * pszId);

   
   virtual bool is_focusable();
   virtual void focus_next();
   virtual void set_focus(simple_ui * pui);
   virtual simple_ui * get_focus();

   virtual bool is_visible();

   virtual ::spa::style * get_style();


   virtual void client_to_screen(POINT * ppt);
   virtual void client_to_screen(RECT * prect);
   virtual void screen_to_client(POINT * ppt);
   virtual void screen_to_client(RECT * prect);

   virtual void get_window_rect(RECT * prect);
   virtual void get_client_rect(RECT * prect);

   void draw_back_01_old(::spa::style::e_schema eschema, rect m_rect, ::draw2d::graphics * pgraphics);
   
   virtual void layout();
};




#include "simple_edit_box.h"
#include "simple_label.h"
#include "simple_password.h"
#include "simple_tap.h"
