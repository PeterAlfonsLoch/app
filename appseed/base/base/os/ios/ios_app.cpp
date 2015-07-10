//
//  ios_app.cpp
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/07/15.
//
//




ui_window_ptr new_round_window(plane_system * psystem, CGRect rect);




//
//  app_system.cpp
//  app
//
//  Created by Carlos Gustavo Cecyn Lundgren on 12/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//







plane_system * new_system(const char * pszId)
{
   
   on_init_thread();
   
   
   return new ::plane_system(pszId);
   
   
   
}

::base::system * create_base_system()
{
   
   ::aura::system * paurasystem = create_aura_system();
   
   if(paurasystem == NULL)
      return NULL;
      
   ::base::system * pbasesystem = dynamic_cast<::base::system *>(paurasystem);
   
   if(pbasesystem == NULL)
   {
      
      ::aura::del(paurasystem);
      
      return NULL;
      
   }
   
   return pbasesystem;
   
}

plane_system::plane_system(const char * pszId)
{
   
   m_psystem = create_base_system();
   
   m_psystem->m_posdata->m_pui = new ::user::interaction(m_psystem);
   
   ::ios::main_init_data * pinitmaindata  = new ::ios::main_init_data;
   
   
   
   pinitmaindata->m_hInstance             = NULL;
   pinitmaindata->m_hPrevInstance         = NULL;
   pinitmaindata->m_vssCommandLine        = pszId;
   pinitmaindata->m_nCmdShow              = 0;
   
   m_psystem->init_main_data(pinitmaindata);
   
   
   
}

ui_window_ptr init_part_2ex(plane_system * psystem, CGRect rect)
{
   
   return psystem->init_part_2ex(rect);
   
}


UINT system_main(LPVOID lp)
{
   ::base::system * psystem = (::base::system *) lp;
   try
   {
//      psystem->set_thread(psystem);
      psystem->m_iReturnCode = 0;
      psystem->m_bReady = true;
      psystem->m_bRun = true;
//      psystem->thread::m_p->m_bRun= true;
      psystem->m_iReturnCode = psystem->on_run();
      if(psystem->m_iReturnCode != 0)
      {
         ::OutputDebugStringW(L"application::main on_run termination failure");
      }
      if(psystem->is_system())
      {
         psystem->post_to_all_threads(WM_QUIT, 0, 0);
      }
      try
      {
         psystem->m_iReturnCode = psystem->exit();
      }
      catch(...)
      {
         psystem->m_iReturnCode = -1;
      }
      
   }
   catch(::exit_exception &)
   {
      
      psystem->post_to_all_threads(WM_QUIT, 0, 0);
      
   }
   
   return 0;
}


ui_window_ptr plane_system::init_part_2ex(CGRect rect)
{
   
   //m_psystem->m_window = ios_start_window(this, rect);
   
   int nReturnCode = 0;
   
   manual_reset_event ev(m_psystem);
   
   m_psystem->m_peventReady = &ev;
   
   if(!m_psystem->begin_synch())
      return NULL;
   
   ev.wait();
   
   ui_window_ptr pwindow = new_round_window(this, rect);
   
   //::user::native_window_initialize initialize;
   
   //initialize.pwindow = this;
   //initialize.window = m_window.Get();
   
   //m_psystem->m_posdata->m_pui->initialize(&initialize);
   
   //m_psystem->m_ptwf = create_twf_2ex();
   
   //m_psystem->m_ptwf->twf_start();
   
   stringa straLibrary = m_psystem->command()->m_varTopicQuery["app"].stra();
   
   for(int i = 0; i < m_psystem->command()->m_varTopicQuery["app"].array_get_count(); i++)
   {
      string strApp = m_psystem->command()->m_varTopicQuery["app"].at(i);
   }
   
   straLibrary.replace("\\", "_");
   straLibrary.replace("-", "_");
   
   for(int i = 0; i < straLibrary.get_count(); i++)
   {
      string strLibrary = straLibrary[i];
      strsize iFind = strLibrary.find("/");
      if(iFind >= 0)
         strLibrary = strLibrary.Left(iFind) + '_' + strLibrary.Mid(iFind + 1);
      iFind = strLibrary.find("/", iFind + 1);
      if(iFind >= 0)
         strLibrary.Truncate(iFind);
      m_psystem->m_mapAppLibrary[m_psystem->command()->m_varTopicQuery["app"][i]] = strLibrary;
   }
   
   for(int i = 0; i < m_psystem->command()->m_varTopicQuery["app"].get_count(); i++)
   {
      string strApp = m_psystem->command()->m_varTopicQuery["app"][i];
   }
   
   m_psystem->m_mapAppLibrary["app/ca2/cube"] = "ca2";
   m_psystem->m_mapAppLibrary["app/ca2/bergedge"] = "ca2";
   
   return pwindow;
}


void system_begin_main(plane_system * psystem)
{
   
   psystem->begin();
   
}

void plane_system::begin()
{
   
   __begin_thread(m_psystem, &system_main, m_psystem);
   
}



round_window * ios_start_window(plane_system * psystem, CGRect rect)
{
   
   ::user::interaction * pui = psystem->m_psystem->m_posdata->m_pui;
   
   ::user::native_window_initialize initialize;
   
   initialize.m_rect.left = rect.origin.x;
   initialize.m_rect.top = rect.origin.y;
   initialize.m_rect.right = rect.origin.x + rect.size.width;
   initialize.m_rect.bottom = rect.origin.x + rect.size.height;
   
   pui->initialize(&initialize);
   
   return pui->m_pimpl.cast < ::ios::interaction_impl > ();
   
}

int ios_initialize_window(round_window * proundwindow, UIWindow * window)
{
   
   ::ios::interaction_impl * puiimpl = dynamic_cast < ::ios::interaction_impl * > (proundwindow);
   
   puiimpl->m_oswindow = oswindow_get(window);
   
   puiimpl->m_oswindow->set_user_interaction(puiimpl->m_pui);
   ::user::create_struct cs;
   cs.dwExStyle = 0;
   cs.lpszClass = 0;
   cs.lpszName = NULL;
   cs.style = 0;
   cs.x = 0;
   cs.y = 0;
   cs.cx = 0;
   cs.cy = 0;
   //      cs.hwndParent = hWndParent;
   //   cs.hMenu = hWndParent == NULL ? NULL : nIDorHMenu;
   cs.hMenu = NULL;
   //      cs.hInstance = System.m_hInstance;
   cs.lpCreateParams = NULL;
   
   if(puiimpl->m_pui != NULL)
   {
      
      if(!puiimpl->m_pui->pre_create_window(cs))
      {
         
         puiimpl->PostNcDestroy();
         
         return FALSE;
         
      }
      
   }
   else
   {
      
      if (!puiimpl->pre_create_window(cs))
      {
         
         puiimpl->PostNcDestroy();
         
         return FALSE;
         
      }
      
   }
   
   if(cs.hwndParent == NULL)
   {
      
      cs.style &= ~WS_CHILD;
      
   }
   
//   puiimpl->m_pui->m_pthread = ::get_thread();
   
   puiimpl->send_message(WM_CREATE, 0, (LPARAM) &cs);
   
   ::rect rectMainScreen;
   
   GetMainScreenRect(rectMainScreen);
   
   puiimpl->SetPlacement(rectMainScreen);
   
   return TRUE;
   
}




ui_window_ptr new_round_window(plane_system * psystem, CGRect rect)
{
   
   round_window * pwindow = ios_start_window(psystem, rect);
   
   UIWindow * window = new_round_window(pwindow, rect);
   
   ios_initialize_window(pwindow, window);
   
   return window;
   
}


