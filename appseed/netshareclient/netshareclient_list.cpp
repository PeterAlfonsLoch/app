#include "StdAfx.h"

namespace netshareclient
{

   list::list(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      m_headerctrl(papp),
      list_interface(papp),
      m_scrollbarHorz(papp),
      m_scrollbarVert(papp),
      user::list(papp)
   {
      m_pheaderctrl = &m_headerctrl;
      m_pscrollbarHorz = &m_scrollbarHorz;
      m_pscrollbarVert = &m_scrollbarVert;

      m_headerctrl.m_dataid = "netshareclient::list::header_ctrl";
      m_pheaderctrl->m_plistctrlinterface = this;

      string str;
      str = "<netshareclient>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 04 de netshareclient de 2008</span>\n";
      str += unitext("<h1>Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>");
      str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
      str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
      str += "<br />";
      str += unitext("<span>Voc・conhece o ca2?</span>");
      str += "<br />";
      str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
      str += "<br />";
      str += "<input type=\"text\" />";
      str += "</body>\n";
      str += "</netshareclient>\n";

   }

   list::~list()
   {
   }

   document * list::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


   void list::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);
      netshareclient::list_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list::_001OnTimer);
   }

   void list::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      ::netshareclient::application * papp = dynamic_cast < ::netshareclient::application * > (get_app());
      papp->m_pnetshareclientlist = this;
      if(pobj->m_bRet)
         return;
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }


   void list::_001OnTimer(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::win::message::timer, ptimer, pobj)

   }


   void list::_001OnClick(UINT uiFlags, point point)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      Range range;
      _001GetSelection(range);
      if(range.get_item_count() > 0)
      {
         ItemRange & itemrange = range.ItemAt(0);
         ::user::list_item item(this);
         item.m_iItem = itemrange.GetLBound();
         item.m_iSubItem = 0;
         item.m_iListItem = 0;
         m_pdata->_001GetItemText(&item);
         get_document()->netshare(item.m_strText);
      }
   }

   void list::open_profile(const char * pszFolder)
   {
      UNREFERENCED_PARAMETER(pszFolder);
      _001OnUpdateItemCount();
   }

} // namespace netshareclient