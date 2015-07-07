

#if defined(LINUX) || defined(VSNORD)


CLASS_DECL_AXIS int_bool WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   ::user::elemental * pui = window_from_handle(oswindow);

   if (pui == NULL)
      return FALSE;

   if (pui->m_bDestroying)
      return FALSE;

   HTHREAD  h = pui->m_pauraapp->get_os_handle();

   if (h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if (pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.hwnd = oswindow;
   msg.message = Msg;
   msg.wParam = wParam;
   msg.lParam = lParam;
   msg.pt.x = 0x80000000;
   msg.pt.y = 0x80000000;


   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}


CLASS_DECL_AXIS int_bool mq_remove_window_from_all_queues(oswindow oswindow)
{
   ::user::interaction * pui = window_from_handle(oswindow);

   if (pui == NULL)
      return FALSE;

   HTHREAD  h = pui->m_pauraapp->get_os_handle();

   if (h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if (pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   pmq->ma.remove_pred([=](MESSAGE & item) {return item.hwnd == oswindow;});

}


#endif
