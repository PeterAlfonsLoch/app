#include "framework.h"


html_form::html_form(sp(::ca::application) papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::form(papp)
{

   m_sphtmldata = new html::data(papp);

}

html_form::~html_form()
{
}



void html_form::_001OnDraw(::ca::graphics * pdc)
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

   if(sphtmldata.is_set() && !sphtmldata->is_in_use())
   {
      sphtmldata->_001OnDraw(pdc);
   }



}


void html_form::_001DrawChildren(::ca::graphics *pdc)
{

   if(m_pguie != ::null() && m_pguie != this)
   {
      m_pguie->_001DrawChildren(pdc);
   }
   else
   {
      sp(::user::interaction) pui = get_bottom_child();
      while(pui != ::null())
      {
         try
         {
            if(pui->m_bVisible && (get_html_data() == ::null() || !get_html_data()->contains(pui)))
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
}


void html_form::_001OnImageLoaded(::ca::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(get_html_data() != ::null())
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() > 0)
      {

         get_html_data()->m_box = rectClient;

         ::ca::data::writing writing(get_html_data());

         ::ca::client_graphics pdc(this);
         get_html_data()->delete_implementation();
         get_html_data()->layout(pdc);

         _001RedrawWindow();
      }
   }
}


void html_form::install_message_handling(::ca::message::dispatch * pinterface)
{
   ::user::form::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_form::_001OnCreate);

//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::html_form::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &html_form::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &html_form::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &html_form::_001OnLButtonUp);

   IGUI_WIN_MSG_LINK(html::message_on_image_loaded, pinterface, this, &html_form::_001OnImageLoaded);
}

/*
bool html_form::open_document(const char * lpszPathName)
{
   string strPathName(lpszPathName);
   if(strPathName.Mid(3) == "wb:")
      return FALSE;
   string str = Application.file().as_string(lpszPathName);
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

   mutex_lock sl(user_mutex(), true);

   if(get_html_data() == ::null())
      return;

   get_html_data()->implement_and_layout(this);

}


void html_form::_001OnCreate(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::create, pcreate, pobj)
   if(pobj->previous())
      return;
   get_html_data()->m_pform = this;
   ASSERT(get_html_data() != ::null());
   if(get_html_data() == ::null())
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



void html_form::_001OnLButtonDown(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::mouse, pmouse, pobj);
   point pt;
   pt = pmouse->m_pt;
   ScreenToClient(&pt);
   m_pelementalLButtonDown = get_html_data()->m_elemental.hit_test(get_html_data(), pt);
   if(m_pelementalLButtonDown != ::null())
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdata = get_html_data();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonDown(&signal);
   }
   pmouse->m_bRet = true;
   pmouse->set_lresult(1);
}
   /*void html_form::_001OnMouseMove(::ca::signal_object * pobj)
{
SCAST_PTR(::ca::message::mouse, pmouse, pobj);
   point pt;
   pt = pmouse->m_pt;
   ScreenToClient(&pt);
   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(pt);
   if(pelemental != ::null())
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = m_pcontainer;
      signal.m_psignal = pmouse;
      pelemental->OnMouseMove(&signal);
   }*/

void html_form::_001OnMouseMove(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::mouse, pmouse, pobj);
   point pt(pmouse->m_pt);
   ScreenToClient(&pt);
   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(get_html_data(), pt);
   html::signal signal(pobj->m_psignal);
   signal.m_pdata = get_html_data();
   signal.m_psignal = pmouse;
   signal.m_pui = this;
   if(pelemental != ::null())
   {
      pelemental->OnMouseMove(&signal);
      if(signal.m_bRet)
         m_elementalptraMouseMove.add(pelemental);
   }
   for(int32_t i = 0; i < m_elementalptraMouseMove.get_count(); )
   {
      try
      {
         m_elementalptraMouseMove.element_at(i)->OnMouseMove(&signal);
         if(!signal.m_bRet)
         {
            m_elementalptraMouseMove.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      catch(...)
      {
         m_elementalptraMouseMove.remove_at(i);
      }
   }

}

void html_form::_001OnLButtonUp(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::mouse, pmouse, pobj);
   point pt(pmouse->m_pt);
   ScreenToClient(&pt);
   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(get_html_data(), pt);
   if(m_pelementalLButtonDown != ::null()
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
   else if(varFile.ca < ::ca::file > () != ::null())
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


void html_form::_001GetText(string & str)
{
   get_html_data()->m_elemental.get_html(const_cast < html::data * > (get_html_data()), str);
}

void html_form::_001SetText(const char * psz)
{

   bool bFocus = Application.user()->get_keyboard_focus() == this || is_descendant(Application.user()->get_keyboard_focus());

   sp(::html::data) sphtmldata;

   sphtmldata = new ::html::data(get_app());

   sphtmldata->m_pform = this;

   sphtmldata->load(psz);

   sphtmldata->implement_and_layout(this);

   m_sphtmldata = sphtmldata;

   if(bFocus)
   {
	   sp(::user::keyboard_focus) pfocus = get_focusable_descendant();
      if(pfocus != ::null())
      {
         Application.user()->set_keyboard_focus(pfocus);
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

void html_form::_001OnKeyDown(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::key, pkey, pobj);
   if(pkey->m_ekey == ::user::key_tab)
   {
      pkey->m_bRet = true;
      return;
   }
}


void html_form::defer_implement()
{

   if(get_html_data() == ::null())
      return;

   GetClientBox(get_html_data()->m_box);

   if(get_html_data()->m_box.area() <= 0.f)
      return;

   ::ca::client_graphics pdc(this);

   get_html_data()->m_pguie = this;
   get_html_data()->m_pform = this;
   get_html_data()->implement(pdc);


}


void html_form::defer_layout()
{

   if(get_html_data() == ::null())
      return;

   GetClientBox(get_html_data()->m_box);

   if(get_html_data()->m_box.area() <= 0.f)
      return;

   ::ca::client_graphics pdc(this);

   get_html_data()->m_pguie = this;
   get_html_data()->m_pform = this;
   get_html_data()->layout(pdc);

   _001RedrawWindow();

}


