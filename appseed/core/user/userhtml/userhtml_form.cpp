#include "framework.h"


html_form::html_form(sp(::base::application) papp) :
   element(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::form_interface(papp),
   ::user::form(papp)
{

   m_sphtmldata = new html::data(papp);

   m_sphtmldata->m_pui = this;

   m_pelementalHover = NULL;

}

html_form::~html_form()
{
}



void html_form::_001OnDraw(::draw2d::graphics * pdc)
{

   ::user::interaction::_001OnDraw(pdc);


   sp(::html::data) sphtmldata;

   try
   {

      sphtmldata = get_html_data();

   }
   catch(...)
   {
   }

   if(sphtmldata.is_set() && !sphtmldata->is_locked())
   {
      sphtmldata->_001OnDraw(pdc);
   }



}


void html_form::_001DrawChildren(::draw2d::graphics *pdc)
{

   sp(::user::interaction) pui = get_bottom_child();

   while(pui != NULL)
   {
      try
      {
         if(pui->m_bVisible && (get_html_data() == NULL || !get_html_data()->contains(pui)))
         {
            pui->_000OnDraw(pdc);
         }
         pui = pui->above_sibling();
      }
      catch(...)
      {
      }
   }

}


void html_form::_001OnImageLoaded(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(get_html_data() != NULL)
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() > 0)
      {

         get_html_data()->m_box = rectClient;

         ::data::lock lock(get_html_data());

         ::draw2d::memory_graphics pdc(allocer());
         get_html_data()->delete_implementation();
         get_html_data()->layout(pdc);

         RedrawWindow();
      }
   }
}


void html_form::install_message_handling(::message::dispatch * pinterface)
{
   ::user::form::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_form::_001OnCreate);

//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::html_form::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &html_form::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &html_form::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &html_form::_001OnMouseLeave);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &html_form::_001OnLButtonUp);

   IGUI_WIN_MSG_LINK(html::message_on_image_loaded, pinterface, this, &html_form::_001OnImageLoaded);
}

/*
bool html_form::open_document(const char * lpszPathName)
{
   string strPathName(lpszPathName);
   if(strPathName.Mid(3) == "wb:")
      return FALSE;
   string str = session().file().as_string(lpszPathName);
   if(str.is_empty())
   {
      System.sync_load_url(str, lpszPathName, &ApplicationUser, mm_pcookies);
   }
   m_strPathName = lpszPathName;
   get_html_data()->m_strPathName = m_strPathName;
   get_html_data()->load(str);
   layout();
   return TRUE;

}
*/

void html_form::GetClientBox(::html::box & box)
{

   rect rectClient;

   GetClientRect(rectClient);

   box = rectClient;

}


void html_form::layout()
{

   synch_lock sl(&user_mutex());

   if(get_html_data() == NULL)
      return;

   get_html_data()->implement_and_layout(this);

}


void html_form::_001OnCreate(signal_details * pobj)
{
   SCAST_PTR(::message::create, pcreate, pobj)
   if(pobj->previous())
      return;
   get_html_data()->m_pform = this;
   ASSERT(get_html_data() != NULL);
   if(get_html_data() == NULL)
   {
      pcreate->set_lresult(0);
      pcreate->m_bRet = true;
      return;
   }
   if(m_strOpenOnCreate.has_char() && !get_html_data()->open_document(m_strOpenOnCreate))
   {
      pcreate->set_lresult(-1);
      pcreate->m_bRet = true;
      return;
   }
   return;
}



void html_form::_001OnLButtonDown(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj);
   point pt;
   pt = pmouse->m_pt;
   ScreenToClient(&pt);
   m_pelementalLButtonDown = get_html_data()->m_elemental.hit_test(get_html_data(), pt);
   if(m_pelementalLButtonDown != NULL)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdata = get_html_data();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonDown(&signal);
   }
   pmouse->m_bRet = true;
   pmouse->set_lresult(1);
}
   
void html_form::_001OnMouseMove(signal_details * pobj)
{
   
   SCAST_PTR(::message::mouse, pmouse, pobj);

   track_mouse_hover();

   point pt(pmouse->m_pt);

   ScreenToClient(&pt);

   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(get_html_data(), pt);

   if(pelemental != NULL)
   {

      if (pelemental != m_pelementalHover)
      {

         if (m_pelementalHover != NULL)
         {

            if (m_pelementalHover->m_pimpl != NULL)
            {

               m_pelementalHover->m_pimpl->m_bHover = false;

            }

         }

         m_pelementalHover = pelemental;

      }

      html::signal signal(pobj->m_psignal);

      signal.m_pdata = get_html_data();

      signal.m_psignal = pmouse;

      signal.m_pui = this;

      pelemental->OnMouseMove(&signal);
/*      if(signal.m_bRet)
         m_elementalptraMouseMove.add(pelemental);*/
   }

   //for(int32_t i = 0; i < m_elementalptraMouseMove.get_count(); )
   //{
   //   try
   //   {
   //      m_elementalptraMouseMove.element_at(i)->OnMouseMove(&signal);
   //      if(!signal.m_bRet)
   //      {
   //         m_elementalptraMouseMove.remove_at(i);
   //      }
   //      else
   //      {
   //         i++;
   //      }
   //   }
   //   catch(...)
   //   {
   //      m_elementalptraMouseMove.remove_at(i);
   //   }
   //}

}

void html_form::_001OnMouseLeave(signal_details * pobj)
{

   if(m_pelementalHover != NULL)
   {

      if (m_pelementalHover->m_pimpl != NULL)
      {

         m_pelementalHover->m_pimpl->m_bHover = false;

      }

      m_pelementalHover = NULL;

   }

}

void html_form::_001OnLButtonUp(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj);
   point pt(pmouse->m_pt);
   ScreenToClient(&pt);
   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(get_html_data(), pt);
   if(m_pelementalLButtonDown != NULL
      && pelemental == m_pelementalLButtonDown)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdata = get_html_data();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonUp(&signal);
   }
}


string html_form::get_path()
{
   return m_strPath;
}


bool html_form::open_document(var varFile)
{
   if(!get_html_data()->open_document(varFile))
      return false;
   string strPathName;
   if(varFile.get_type() == var::type_propset && varFile.propset()["url"].get_string().has_char())
   {

      strPathName = varFile.propset()["url"];

   }
   else if(varFile.cast < ::file::binary_buffer > () != NULL)
   {

      strPathName = System.datetime().international().get_gmt_date_time() + "." + get_document()->get_document_template()->m_set["default_extension"];

   }
   else
   {

      strPathName = varFile;

   }

   m_strPath = strPathName;

   return true;

}


void html_form::_001GetText(string & str) const
{

   ((html_form *) this)->get_html_data()->m_elemental.get_html(const_cast < ::html::data * > (get_html_data()), str);

}


void html_form::_001SetText(const string & str, ::action::context actioncontext)
{

   bool bFocus = session().user()->get_keyboard_focus() == this || is_descendant(session().user()->get_keyboard_focus());

   sp(::html::data) sphtmldata;

   sphtmldata = new ::html::data(get_app());

   sphtmldata->m_pform = this;

   sphtmldata->load(str);

   sphtmldata->implement_and_layout(this);

   m_sphtmldata = sphtmldata;

   if(bFocus)
   {
	   sp(::user::keyboard_focus) pfocus = get_focusable_descendant();
      if(pfocus != NULL)
      {
         session().user()->set_keyboard_focus(pfocus);
      }
   }
}


::html::data * html_form::get_html_data()
{
   return m_sphtmldata;
}

const ::html::data * html_form::get_html_data() const
{
   return m_sphtmldata;
}

void html_form::_001OnKeyDown(signal_details * pobj)
{
   SCAST_PTR(::message::key, pkey, pobj);
   if(pkey->m_ekey == ::user::key_tab)
   {
      pkey->m_bRet = true;
      return;
   }
}


void html_form::defer_implement()
{

   if(get_html_data() == NULL)
      return;

   GetClientBox(get_html_data()->m_box);

   if(get_html_data()->m_box.area() <= 0.f)
      return;

   ::draw2d::memory_graphics pdc(allocer());

   get_html_data()->m_pui = this;
   get_html_data()->m_pform = this;
   get_html_data()->implement(pdc);


}


void html_form::defer_layout()
{

   if(get_html_data() == NULL)
      return;

   GetClientBox(get_html_data()->m_box);

   if(get_html_data()->m_box.area() <= 0.f)
      return;

   ::draw2d::memory_graphics pdc(allocer());

   get_html_data()->m_pui = this;
   get_html_data()->m_pform = this;
   get_html_data()->layout(pdc);

   RedrawWindow();

}


