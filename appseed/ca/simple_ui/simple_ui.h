#pragma once


class simple_ui;


class CLASS_DECL_ca simple_ui_ptra : 
   public array < simple_ui * >
{
public:


};


class CLASS_DECL_ca simple_ui
{
public:


   bool                             m_bVisible;
   RECT                             m_rect;
   vsstring                         m_strId;
   vsstring                         m_strText;
   simple_ui_ptra                   m_uiptra;
   simple_ui *                      m_puiParent;
   simple_ui *                      m_puiFocus;
   ::hotplugin::plugin *            m_pplugin;


   simple_ui();
   virtual ~simple_ui();


   virtual void set_parent(simple_ui * puiParent);


   virtual void draw(simple_graphics & hdc);
   virtual void draw_this(simple_graphics & hdc);
   virtual void draw_children(simple_graphics & hdc);

   virtual void draw_focus_rect(simple_graphics & hdc);


   virtual void on_char(int32_t iKey, const vsstring & strChar);
   virtual void on_lbutton_down(int32_t x, int32_t y);
   virtual void on_lbutton_up(int32_t x, int32_t y);
   virtual void on_mouse_move(int32_t x, int32_t y);


   virtual void on_action(const char * pszId);

   
   virtual bool is_focusable();
   virtual void focus_next();
   virtual void set_focus(simple_ui * pui);
   virtual simple_ui * get_focus();

   virtual bool is_visible();

   virtual ::hotplugin::plugin * get_plugin();


   

};




#include "simple_edit_box.h"
#include "simple_label.h"
#include "simple_password.h"
#include "simple_tap.h"
