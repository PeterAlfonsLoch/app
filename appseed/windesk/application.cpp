#include "StdAfx.h"
#include "frame.h"

namespace windesk
{

   application::application()
   {
      m_strAppName            = "windesk";
      m_strLicense            = "_set_windesk";
      m_strBaseSupportId      = "votagus_ca2_windesk";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
   }

   application::~application(void)
   {
   }



   bool application::initialize_instance()
   {

   factory().creatable_small < document >();
   factory().creatable_small < frame >();
   factory().creatable_small < view >();
   factory().creatable_small < windesk::pane_view >();
   factory().creatable_small < windesk::menu_right_view >();
   factory().creatable_small < windesk::menu_view >();

      if(!ca84::application::initialize_instance())
         return false;



      GetStdFileManagerTemplate()->m_strLevelUp = "1000";


      SetRegistryKey("ca2core");

	   ::userbase::multiple_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::multiple_document_template(
         this,
		   "system/form",
		   &typeid(document),
		   &typeid(frame),
		   &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;



      return true;
   }

   int application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      try
      {

   #ifdef DEBUG
         if (command_line().m_varQuery.has_property("debugbreak"))
         {
            ::DebugBreak();
         }
   #endif
         if (command_line().m_varQuery.has_property("run"))
         {
         }
      }
      catch (const _template::CAtlException& e)
      {
         System.log().print("Error: %x", e.m_hr);
      }
      ::ca::rgn_sp rgn(get_app());
      rgn->CreateRectRgn(0, 0, 0, 0);
      for(int iDisplay = 0; iDisplay < m_monitorinfoaDesk.get_size(); iDisplay++)
      {
         ::ca::rgn_sp rgnThis(get_app());
         rgnThis->CreateRectRgnIndirect(&m_monitorinfoaDesk[iDisplay].rcMonitor);
         ::ca::rgn_sp rgnDiff(get_app());
         rgnDiff->CreateRectRgn(0, 0, 0, 0);
         int iCombine = rgnDiff->CombineRgn(rgnThis, rgn, RGN_DIFF);
         if(iCombine == COMPLEXREGION)
            continue;
         if(iCombine == NULLREGION)
            continue;
         rgn->CombineRgn(rgn, rgnDiff, RGN_OR);
         windesk::document * pdocument = 
            dynamic_cast < document * > 
               (m_ptemplate_html->open_document_file(NULL, FALSE));
         if(pdocument != NULL)
         {
            pane_view * pview = pdocument->get_typed_view < pane_view > ();
            if(pview != NULL)
            {
               pview->set_display(iDisplay);
               frame * pframe =
                  dynamic_cast < frame * > 
                     (pview->GetParentFrame());
               rect rectMonitor;
               rgnDiff->GetRgnBox(&rectMonitor);
               if(pframe != NULL)
               {
                  m_hwndaDesktop.add(pframe->get_safe_handle());
                  m_rectaMonitor.add(rectMonitor);
                  pframe->CheckLayout();
               }
               pview->set_cur_tab_by_id(windesk::PaneViewWinActionArea);
            }
         }
      }
      return true;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * application::get_app() const
   {
      return m_papp;
   }


   bool application::on_assert_failed_line(const char * lpszFileName, int iLine)
   {
      if(m_pwndMain != NULL)
      {
         m_pwndMain->PostMessage(12578);
      }
      return true;
   }


   bool application::final_handle_exception(::ca::exception & e)
   {

      return ca84::application::final_handle_exception(e);
   }


      // IUnknown
   HRESULT STDMETHODCALLTYPE application::QueryInterface( 
          /* [in] */ REFIID riid,
          /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
   {
      if(riid == IID_IDropTarget)
      {
         *ppvObject = (void *) dynamic_cast < IDropTarget * >(this);
         return S_OK;
      }
      return E_NOINTERFACE;
   }

   ULONG STDMETHODCALLTYPE application::AddRef( void)
   {
      return 1;
   }

   ULONG STDMETHODCALLTYPE application::Release( void)
   {
      return 1;
   }



      // IDropTarget
   HRESULT STDMETHODCALLTYPE application::DragEnter( 
         /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL pt,
         /* [out][in] */ __RPC__inout DWORD *pdwEffect)
   {
      point point;
      point.x = pt.x;
      point.y = pt.y;
      IDropTarget * ptarget = i_drop_target_from_point(point);
      if(ptarget == NULL)
         return E_FAIL;
      return ptarget->DragEnter(pDataObj, grfKeyState, pt, pdwEffect);
   }
     
   HRESULT STDMETHODCALLTYPE application::DragOver( 
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL pt,
         /* [out][in] */ __RPC__inout DWORD *pdwEffect)
   {
      return E_FAIL;
   }
     
   HRESULT STDMETHODCALLTYPE application::DragLeave( void)
   {
      return E_FAIL;
   }
     
   HRESULT STDMETHODCALLTYPE application::Drop( 
         /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL pt,
         /* [out][in] */ __RPC__inout DWORD *pdwEffect)
   {
      return E_FAIL;
   }

   IDropTarget * application::i_drop_target_from_point(point pt)
   {
      ::user::interaction * puie = uie_from_point(pt);
      if(puie == NULL)
         return NULL;
      IDropTarget * ptarget = NULL;
      while(true)
      {
         ptarget = dynamic_cast < IDropTarget * > (puie);
         if(ptarget != NULL)
            return ptarget;
         puie = puie->GetParent();
         if(puie == NULL)
            return NULL;
      }
   }

   void application::data_on_after_change(gen::signal_object * pobj)
   {
      ca84::application::data_on_after_change(pobj);
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2_fontopus_votagus")
      {
         if(pchange->m_key.m_idIndex  == "windesk")
         {
            pchange->data_get(m_flags);
         }
      }
   }

} // namespace windesk


CLASS_DECL_CA2_WINDESK ::ca::application * get_new_app()
{
   return new ::windesk::application;
}


