#include "StdAfx.h"
#include "mixeruserbase_document.h"
#include "mixeruserbase_control_view.h"
#include "mixeruserbase_control_data.h"
#include "mixeruserbase_central.h"
#include "mixeruserbase_mute_control.h"

#define IDC_MIXER_SLIDER 1000
#define IDC_BUTTON_RESERVE 1002
#define ID_VIEW_UPDATE 1003
#define IDI_ALBUM 1004
#define IDS_MIXER_DIALOG_TITLEFORMAT 1006
#define IDS_MIXER_SPEAKERSCONTROLS 1007
#define IDS_MIXER_WAVEINCONTROLS 1008


namespace mixeruserbase
{


   const int main_view::cnListCount = 9;


   main_view::main_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      m_brushBackground(papp),
      place_holder_container(papp)
   {


      m_pcontrol = NULL;

      m_etranslucency = TranslucencyPresent;

      m_bInitialized = false;
      m_uiNextSliderID = IDC_MIXER_SLIDER;

      //m_crForeground = GetSysColor(COLOR_BTNTEXT);
      //m_crForeground = RGB(255, 255, 255);
      //m_crForeground = RGB(255, 255, 255)
      //m_crBackground = RGB(58,80,110);
      //m_crBackground = GetSysColor(COLOR_3DFACE);
      m_crBackground = RGB(74, 70, 64);

      //m_brushBackground.CreateSolidBrush(m_crBackground);
      //m_crForeground = RGB(255, 255, 255);
   
      m_brushBackground->CreateStockObject(NULL_BRUSH);
      m_crForeground = RGB(0, 0, 0);


      m_dwUpdateTime = 0;
      TRACE("AlbumFormView this = %x \n", this);
   }

   main_view::~main_view()
   {

   }

   void main_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &main_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &main_view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &main_view::_001OnCreate);
   //   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &main_view::_001OnTimer);
     // IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &main_view::_001OnContextMenu);
   //   IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &main_view::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_CTLCOLOR, pinterface, this, &main_view::_001OnCtlColor);

   //   IGUI_WIN_ON_NOTIFY(LVN_COLUMNCLICK  , IDC_LIST, this, this, &main_view::_001OnColumnclickList);
     // IGUI_WIN_ON_NOTIFY(NM_DBLCLK        , IDC_LIST, this, this, &main_view::_001OnDblclkList);
      //IGUI_WIN_ON_NOTIFY(LVN_GETDISPINFO  , IDC_LIST, this, this, &main_view::_001OnGetdispinfoList);

      IGUI_WIN_ON_CONTROL(BN_CLICKED, IDC_BUTTON_RESERVE     , this, this, &main_view::_001OnButtonReserve);

      connect_update_cmd_ui(ID_VIEW_UPDATE, &main_view::_001OnUpdateViewUpdate);
   }



   #ifdef _DEBUG
   void main_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void main_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }

   document* main_view::get_document() // non-debug version is inline
   {
      ASSERT(base < document > :: bases(::view::get_document()));
      return dynamic_cast < document * > (::view::get_document());
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // main_view message handlers

   void main_view::_001OnSize(gen::signal_object * pobj) 
   {
      if(!m_bInitialized)
         return;
      if(pobj->previous())
         return;

      LayoutControl();
   }

   void main_view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void main_view::_001OnGetdispinfoList(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::notify, pnotify, pobj)
   }

   void main_view::_001OnDestroy(gen::signal_object * pobj) 
   {
   
   
      UNREFERENCED_PARAMETER(pobj);
   
   }

   void main_view::_001OnColumnclickList(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   void main_view::_001OnDblclkList(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::notify, pnotify, pobj)
   }

   void main_view::_001OnButtonReserve(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   }






   void main_view::pre_translate_message(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == MM_MIXM_CONTROL_CHANGE)
       {
         ASSERT(FALSE);
       }
       else if(pbase->m_uiMessage == MM_MIXM_LINE_CHANGE)
       {
         ASSERT(FALSE);
       }
      if(pbase->m_uiMessage == WM_DISPLAYCHANGE)
      {
   //      SetImageLists();
      }

      return ::userbase::view::pre_translate_message(pobj);
   }

   void main_view::_001OnCreate(gen::signal_object * pobj) 
   {
      
      wait_cursor cwc(get_app());
      
      if(pobj->previous())
         return ;

      m_enhmetafile = GetEnhMetaFile(Application.dir().matter("vmp/image/vector/vmp.emf"));
      GetEnhMetaFileHeader(m_enhmetafile, sizeof(m_emh), &m_emh);

      rect clientRect(0, 0, 0, 0);

      central & central = Bergedge.get_mixeruserbase_central();

      add_image_tab(central.m_strPlaybackTitle, central.m_strPlaybackIcon, central.m_idPlaybackPane);
      add_image_tab(central.m_strRecordingTitle, central.m_strRecordingIcon, central.m_idRecordingPane);

      set_cur_tab_by_id(central.m_idPlaybackPane);

      ::userbase::view::_001OnInitialUpdate(NULL);

      m_bInitialized = true;

   }


   BOOL main_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.style = cs.style;
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
      cs.style |= WS_CLIPCHILDREN;
      return ::userbase::view::PreCreateWindow(cs);
   }



   void main_view::_001OnUpdateViewUpdate(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable();
      pupdatecmdui->m_bRet = true;
   }







   void main_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(pHint);
      UNREFERENCED_PARAMETER(lHint);
   
   }



   void main_view::_001OnCtlColor(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);

   }


   void main_view::_001OnMixerSpeakerscontrols(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      central & central = Bergedge.get_mixeruserbase_central();
      if(get_cur_tab_id() != central.m_idPlaybackPane)
      {
         set_cur_tab_by_id(central.m_idPlaybackPane);
      }
   }

   void main_view::_001OnUpdateMixerSpeakerscontrols(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
      central & central = Bergedge.get_mixeruserbase_central();
      if(get_cur_tab_id() == central.m_idPlaybackPane)
      {
         pupdatecmdui->m_pcmdui->_001SetCheck();
         pupdatecmdui->m_pcmdui->Enable(TRUE);
      }
      else
      {
         pupdatecmdui->m_pcmdui->_001SetCheck(check::unchecked);
         pupdatecmdui->m_pcmdui->Enable(TRUE);
      }
      pupdatecmdui->m_bRet = true;
   }

   void main_view::_001OnMixerWaveincontrols(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      central & central = Bergedge.get_mixeruserbase_central();
      if(get_cur_tab_id() != central.m_idRecordingPane)
      {
         set_cur_tab_by_id(central.m_idRecordingPane);
      }
   }

   void main_view::_001OnUpdateMixerWaveincontrols(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
      central & central = Bergedge.get_mixeruserbase_central();
      if(get_cur_tab_id() == central.m_idRecordingPane)
      {
         pupdatecmdui->m_pcmdui->_001SetCheck();
         pupdatecmdui->m_pcmdui->Enable(TRUE);
      }
      else
      {
         pupdatecmdui->m_pcmdui->_001SetCheck(check::unchecked);
         pupdatecmdui->m_pcmdui->Enable(TRUE);
      }   
      pupdatecmdui->m_bRet = true;
   }



   BOOL main_view::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
   {
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(pResult);
      return FALSE;
   }

   void main_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      MMRESULT mmrc;
      control_view * pcontrol = create_view < control_view > ();
      central & central = Bergedge.get_mixeruserbase_central();
      if(pcreatordata->m_id == central.m_idPlaybackPane)
      {
         pcontrol->get_data()->Initialize();
         pcontrol->get_data()->SetNewDevice(0);
         mmrc = pcontrol->get_data()->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
         if(mmrc != MMSYSERR_NOERROR)
         {
            mmrc = pcontrol->get_data()->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_HEADPHONES);
            if(mmrc != MMSYSERR_NOERROR)
            {
               System.simple_message_box(NULL, "Could not open default mixer destination!");
            }
         }
      }
      else if(pcreatordata->m_id == central.m_idRecordingPane)
      {
         pcontrol->get_data()->Initialize();
         pcontrol->get_data()->SetNewDevice(0);
         pcontrol->get_data()->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_WAVEIN);
      }
      pcreatordata->m_pwnd = pcontrol;
      pcreatordata->m_pdoc = get_document();
   }

   void main_view::LayoutControl()
   {
      if(m_pcontrol != NULL)
      {
         rect rectClient;

         rect rectTabClient;
         GetClientRect(rectClient);
         m_pcontrol->SetWindowPos(
            NULL,
            rectClient.left, rectClient.top, 
            rectClient.width(), rectClient.height(),
            SWP_SHOWWINDOW);
         m_pcontrol->layout();
      }
   }

   void main_view::_000OnDraw(::ca::graphics * pgraphics)
   {

      rect rectMeta;
      rect rectDib;

      rect rectClient;

      GetClientRect(rectClient);

      if(System.savings().is_trying_to_save(gen::resource_processing))
      {
         pgraphics->FillSolidRect(rectClient, RGB(255,255,255));
      }
      else
      {
         System.imaging().color_blend(pgraphics, rectClient, RGB(255,255,255), 32);
      }

      rect rect;

      rect = rectClient;
      rect.ScaleHeightAspect(min(rectClient.height(), rectClient.height() - 333), rectClient.right, rectClient.bottom);

      if(m_enhmetafile != NULL)
      {
         rectMeta.left = 0;
         rectMeta.top = 0;
         rectMeta.right = m_emh.rclBounds.right - m_emh.rclBounds.left;
         rectMeta.bottom = m_emh.rclBounds.bottom - m_emh.rclBounds.top;
         //rectMeta.FitOnCenter(rectClient);
         rectMeta.FitOnCenterOf(rectClient);
         //rectMeta.Align(gen::AlignBottom | gen::AlignRight, rectClient);

         rectDib = rectMeta;
         rectDib -= rectMeta.top_left();

         ::ca::dib_sp dib(get_app());
         dib->create(rectDib.size());
         dib->get_graphics()->FillSolidRect(rectDib, RGB(0, 0, 0));
         dib->get_graphics()->PlayMetaFile(m_enhmetafile, rectDib);
         dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);
         dib->channel_multiply(visual::rgba::channel_alpha, 0.84);
         System.imaging().true_blend(pgraphics, rectMeta.top_left(), rectMeta.size(), dib->get_graphics(), null_point() );
      }
      ::userex::pane_tab_view::_000OnDraw(pgraphics);
   }

   void main_view::_001OnDraw(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);



   }


} // namespace mixeruserbase


