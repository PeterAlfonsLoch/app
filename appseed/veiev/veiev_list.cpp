#include "StdAfx.h"

namespace veiev
{

   list::list(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::userbase::view(papp),
      m_headerctrl(papp),
      list_interface(papp),
      m_scrollbarHorz(papp),
      m_scrollbarVert(papp),
      user::list(papp)
   {
      m_pheaderctrl = &m_headerctrl;
      m_pscrollbarHorz = &m_scrollbarHorz;
      m_pscrollbarVert = &m_scrollbarVert;

      m_headerctrl.m_dataid = "veiev::list::header_ctrl";
      m_pheaderctrl->m_plistctrlinterface = this;

      string str;
      str = "<veiev>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 04 de veiev de 2008</span>\n";
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
      str += "</veiev>\n";

      m_etranslucency = TranslucencyPresent;

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
      veiev::list_interface::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list::_001OnTimer);
   }

   void list::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      ::veiev::application * papp = dynamic_cast < ::veiev::application * > (get_app());
      papp->m_pveievlist = this;
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
         class var var;
         if(m_pdata->get_record(itemrange.GetLBound(), var))
         {
            pdoc->open_veiev_profile(var["datetime"] + "/" + var["index"]);
         }
      }
   }

   void list::open_folder(const char * pszFolder)
   {
      m_pprofile = get_document()->m_pprofile;
      string strFolder(pszFolder);
      if(strFolder.is_empty())
         return;
      _001OnUpdateItemCount();
      m_pprofile->start_veiev_synch();
   }

} // namespace veiev