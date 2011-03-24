#include "StdAfx.h"

on_draw_interface::on_draw_interface()
{
   m_pbuffer = NULL;
   m_bOnPaint = false;
   m_bAutoClip = true;
}

on_draw_interface::~on_draw_interface()
{
   if(m_pbuffer != NULL)
   {
      delete m_pbuffer;
   }
}

::user::interaction * on_draw_interface::get_guie()
{
   return dynamic_cast < ::user::interaction * > (this);
}

void on_draw_interface::_001InstallOnDrawInterface(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(
      WM_PAINT,
      pinterface, 
      this, 
      &on_draw_interface::OnDrawInterfacePaint);

   IGUI_WIN_MSG_LINK(
      WM_NCPAINT,
      pinterface, 
      this, 
      &on_draw_interface::OnDrawInterfaceNcPaint);
   
   m_pwindowinterface = pinterface;

}

void on_draw_interface::OnDrawInterfaceNcPaint(gen::signal_object * pobj)
{
   pobj->m_bRet = true;
}

void on_draw_interface::OnDrawInterfacePaint(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw not_implemented_exception();
 /*  CPaintDC spgraphics(get_guie()->get_wnd());
   
   rect rect(spgraphics->m_ps.rcPaint);
   if(rect.width() == 0 || rect.height() == 0)
   {
      rect rectWindow;
      get_guie()->GetWindowRect(rectWindow);
      m_papp->s_ptwf->Redraw(rectWindow);
   }
   else
   {
      get_guie()->ClientToScreen(rect);
      m_papp->s_ptwf->Redraw(rect);
   }
   /*
   if(m_pbuffer != NULL)
   {
        ::ca::rgn rgnClip;
      rgnClip.CreateRectRgn(0, 0, 0, 0);
      bool bClip = ::GetClipRgn(spgraphics->get_os_data(), rgnClip) == 1;
      if(bClip)
      {
         rect rect;
         rgnClip.GetRgnBox(rect);
         bClip = !rect.is_empty();
      }
      if(bClip)
      {
         m_pbuffer->GetBuffer()->SelectClipRgn(&rgnClip);
      }
      else if(!::is_empty(&spgraphics->m_ps.rcPaint))
      {
         rgnClip.SetRectRgn(&spgraphics->m_ps.rcPaint);
         m_pbuffer->GetBuffer()->SelectClipRgn(&rgnClip);
      }
      else
      {
         m_pbuffer->GetBuffer()->SelectClipRgn(NULL);
      }
      OnDrawInterfaceDraw(m_pbuffer->GetBuffer());
      m_pbuffer->BitBlt(&spgraphics);
   }
   else
   {
      OnDrawInterfaceDraw(&spgraphics);   
   }*/
   //pobj->m_bRet = true;
}

void on_draw_interface::OnDrawInterfaceDraw(::ca::graphics *pdc)
{
   _001OnNcDraw(pdc);
   _001OnDraw(pdc);
}

void on_draw_interface::InstallBuffering(::user::win::message::dispatch * pinterface)
{
   if(m_pbuffer != NULL)
   {
      UninstallBuffering();
   }
   m_pbuffer = new user::buffer(get_app());
   m_pbuffer->InstallMessageHandling(pinterface);
}

void on_draw_interface::UninstallBuffering()
{
   if(m_pbuffer != NULL)
   {
      m_pwindowinterface->RemoveMessageHandler(m_pbuffer);
      delete m_pbuffer;
      m_pbuffer = NULL;
   }
}
