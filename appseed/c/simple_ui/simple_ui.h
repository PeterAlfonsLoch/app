#pragma once


class simple_ui;


class CLASS_DECL_c simple_ui_ptra : 
   public simple_array < simple_ui * >
{
public:


};


class CLASS_DECL_c simple_ui
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


   virtual void draw(HDC hdc);
   virtual void draw_this(HDC hdc);
   virtual void draw_children(HDC hdc);

   virtual void draw_focus_rect(HDC hdc);


   virtual void on_char(int ch, UINT uScan);
   virtual void on_lbutton_down(int x, int y);
   virtual void on_lbutton_up(int x, int y);
   virtual void on_mouse_move(int x, int y);


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
