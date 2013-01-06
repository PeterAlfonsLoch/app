#include "framework.h"
#ifdef WINDOWSEX
#include <winspool.h>
#endif


simple_printer_list_view::simple_printer_list_view(::ca::application * papp) :
   ca(papp),
   userbase::view(papp),
   user::scroll_view(papp),
   user::form(papp),
   ::ca2::user::form(papp),
   user::list(papp),
   user::form_list(papp),
   userbase::form_list(papp),
   simple_list_view(papp),
   m_listdata(papp)
{

   m_pdata = &m_listdata;

}


simple_printer_list_view::~simple_printer_list_view()
{

}


void simple_printer_list_view::install_message_handling(::gen::message::dispatch * pdispatch)
{

   simple_list_view::install_message_handling(pdispatch);
   IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &simple_printer_list_view::_001OnCreate);

}


void simple_printer_list_view::_001OnCreate(gen::signal_object * pobj)
{
//   SCAST_PTR(gen::message::create, pcreate, pobj);

   pobj->previous();

   DWORD cbNeeded = 0;
   DWORD cbReturned = 0;
#ifdef WINDOWSEX
   ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 1, NULL, 0, &cbNeeded, &cbReturned);
#else
   throw todo(get_app());
#endif

   if(cbNeeded <= 0)
      return;

#ifdef WINDOWSEX
   PRINTER_INFO_1  * infoa = (PRINTER_INFO_1 * ) malloc(cbNeeded);
   ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 1, (LPBYTE) infoa, cbNeeded, &cbNeeded, &cbReturned);

   stringa stra;

   for(uint32_t i = 0; i < cbReturned; i++)
   {

      stra.add(infoa[i].pName);
   }

   m_listdata.set_data(this, stra);

   free(infoa);
#else
   throw todo(get_app());
#endif


   ::user::list_column column;
   column.m_iWidth = 500;
   column.m_iSubItem = 0;

   _001InsertColumn(column);

}


void simple_printer_list_view::_001OnClick(UINT nFlags, point point)
{
   UNREFERENCED_PARAMETER(nFlags);
   index iItem;
   index iSubItem;
   if(_001HitTest_(point, iItem, iSubItem))
   {
      ::user::list_item item(this);
      item.m_plist = this;
      item.m_iItem = iItem;
      item.m_iSubItem = 0;
      item.m_iListItem = -1;
      m_listdata._001GetItemText(&item);
      ::user::print_job * pprintjob = new ::user::print_job(get_app());
      pprintjob->m_phprinter = Cube.get_printer(item.m_strText);
      m_pview->collaborate(pprintjob);
      pprintjob->begin();
   }
}

