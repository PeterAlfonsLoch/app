#include "StdAfx.h"
#include <WinSpool.h>


namespace user
{


   printer_list_view::printer_list_view(::ca::application * papp) :
      ca(papp),
      userbase::view(papp),
      user::scroll_view(papp),
      user::form(papp),
      user::list(papp),
      user::form_list(papp),
      userbase::form_list(papp),
      simple_list_view(papp),
      m_listdata(papp)
   {
      m_pdata = &m_listdata;
   }
      
   printer_list_view::~printer_list_view()
   {
   }


   void printer_list_view::_001InstallMessageHandling(::user::win::message::dispatch * pdispatch)
   {
      simple_list_view::_001InstallMessageHandling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &printer_list_view::_001OnCreate);
   }


   void printer_list_view::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::create, pcreate, pobj);

      DWORD cbNeeded = 0;
      DWORD cbReturned = 0;

      ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 1, NULL, 0, &cbNeeded, &cbReturned);

      if(cbNeeded <= 0)
         return;

      PRINTER_INFO_1  * infoa = (PRINTER_INFO_1 * ) malloc(cbNeeded);
      ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 1, (LPBYTE) infoa, cbNeeded, &cbNeeded, &cbReturned);

      stringa stra;

      for(int i = 0; i < cbReturned; i++)
      {
         
         stra.add(infoa[i].pName);
      }

      m_listdata.set_data(this, stra);

      free(infoa);


      Column column;
      column.m_iWidth = 500;
      column.m_iSubItem = 0;

      _001InsertColumn(column);

   }


} // namespace user