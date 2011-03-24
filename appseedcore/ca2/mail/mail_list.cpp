#include "StdAfx.h"

namespace mail
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

      m_headerctrl.m_dataid = "mail::list::header_ctrl";
      m_pheaderctrl->m_plistctrlinterface = this;

      string str;
      str = "<mail>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 04 de mail de 2008</span>\n";
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
      str += "</mail>\n";


   }

   list::~list()
   {
   }

   document * list::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


   void list::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);
      mail::list_interface::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list::_001OnTimer);
   }

   void list::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      System.m_pmaillist = this;
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
         document * pdoc = get_document();
         string strId = m_pdata->m_straId[itemrange.GetLBound()];
         pdoc->open_email(strId);
      }
   }

   void list::open_folder(const char * pszFolder)
   {
      m_paccount = get_document()->m_paccount;
      string strFolder(pszFolder);
      if(strFolder.is_empty())
         return;
      CSingleLock slDataset(&get_document()->m_paccount->m_pop3.m_csDataset, TRUE);
      _001OnUpdateItemCount();
      get_document()->m_paccount->m_pop3.start();
   }

} // namespace mail