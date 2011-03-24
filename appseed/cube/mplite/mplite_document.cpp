#include "StdAfx.h"

namespace mplite
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::mediaplay::document(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
      m_pdata = NULL;
      m_bPlay = false;
   }

   document::~document()
   {

   }

   BOOL document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

      // TODO: add reinitialization code here
      // (SDI documents will reuse this document)

      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // document server implementation

   /*OleServerItem* document::OnGetEmbeddedItem()
   {
      // OnGetEmbeddedItem is called by the framework to get the COleServerItem
      //  that is associated with the document.  It is only called when necessary.
      MusicalPlayerLightServerItem * pItem = new MusicalPlayerLightServerItem(this);
      ASSERT_VALID(pItem);
      return pItem;
   }
   */


   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*
   void document::Serialize(CArchive& ar)
   {
      MMRESULT mmr;
      if (ar.IsStoring())
      {
         get_data()->HelperGetMidiSequence().SaveFile(ar);
      }
      else
      {
         
         mmr = get_data()->HelperGetMidiSequence().OpenFile(ar, ::mus::midi::OpenForPlaying);
         if(mmr != MMSYSERR_NOERROR)
         {
            midi_exception * pe = new midi_exception();
            pe->SetMMResult(mmr);
            ::ca::rethrow(pe);;
         }
      }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // document diagnostics

   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // document commands


   /*::thread * document::HelperGetMidiPlayerCallbackThread()
   {
      return &gen::ThreadContainer::AppGetHighThread();
   }*/



   bool document::on_open_document(var varFile) 
   {
      return mediaplay::document::on_open_document(varFile);
   }

   void document::delete_contents() 
   {
      ::mediaplay::document::delete_contents();
   }

   void document::AttachPlaylist(PlaylistDoc *pdoc)
   {
      view_update_hint uh;
      uh.set_type(view_update_hint::TypeAttachPlaylist);
      uh.m_pplaylistdoc = pdoc;
      update_all_views(NULL, 0, &uh);
   }


   BOOL document::OpenFile(const char * bstrFilePath, BOOL bMakeVisible) 
   {
      UNREFERENCED_PARAMETER(bMakeVisible);
      string str;
      str = bstrFilePath;
      return cast(get_app()).open_document_file(str) != NULL;
   }


   EPaneView document::GetViewId()
   {
      pane_view_update_hint uh;

      uh.m_eview = PaneViewNone;
      uh.set_type(pane_view_update_hint::TypeGetView);
      update_all_views(NULL, 0, &uh);
      return uh.m_eview;

   }


   pane_view * document::GetPaneView()
   {
      return get_typed_view < pane_view > ();
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::userbase::document::CPersistStorage

   /*STDMETHODIMP_(ULONG) document::XViewObject::AddRef()
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return pThis->ExternalAddRef();
   }

   STDMETHODIMP_(ULONG) document::XViewObject::Release()
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return pThis->ExternalRelease();
   }

   STDMETHODIMP document::XViewObject::QueryInterface(
      REFIID iid, LPVOID* ppvObj)
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return pThis->ExternalQueryInterface(&iid, ppvObj);
   }

   STDMETHODIMP document::XViewObject::draw(
     DWORD dwAspect,   //Aspect to be drawn
     LONG lindex,      //Part of the object of interest in the draw 
                       //operation
     void * pvAspect,  //Pointer to DVASPECTINFO structure or NULL
     DVTARGETDEVICE * ptd,
                       //Pointer to target device in a structure
     HDC hicTargetDev, //Information context for the target device
     HDC hdcDraw,      //Device context on which to draw
     const LPRECTL lprcBounds,
                       //Pointer to the rectangle in which the object 
                       //is drawn
     const LPRECTL lprcWBounds,
                       //Pointer to the ::ca::window extent and ::ca::window origin 
                       //when drawing a metafile
     BOOL (*) (DWORD) pfnContinue,
                       //Pointer to the callback function for canceling 
                       //or continuing the drawing
     DWORD dwContinue  //Value to pass to the callback function
   )
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return S_OK;
   }

   STDMETHODIMP document::XViewObject::GetColorSet(
     DWORD dwAspect,   //How the object is to be represented
     LONG lindex,      //Part of the object of interest in the draw 
                       //operation
     void * pvAspect,  //Always NULL
     DVTARGETDEVICE * ptd,
                       //Pointer to target device in a structure
     HDC hicTargetDev, //Information context for the target device
     LOGPALETTE ** ppColorSet
                       //Address of output var that receives a 
                       //pointer to the requested LOGPALETTE structure
   )
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return S_OK;
   }

   STDMETHODIMP document::XViewObject::HRESULT Freeze(
     DWORD dwAspect,   //How the object is to be represented
     LONG lindex,      //Part of the object of interest in the draw 
                       //operation
     void * pvAspect,  //Always NULL
     DWORD * pdwFreeze //Points to location containing an identifying 
                       //key
   )
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return S_OK;
   }

   STDMETHODIMP document::XViewObject::UnFreeze(
    DWORD dwFreeze  //Contains key that determines ::view object to 
                     //unfreeze
   )
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return S_OK;
   }

   STDMETHODIMP document::XViewObject::SetAdvise(
     DWORD dwAspect,  //::view for which notification is being requested
     DWORD advf,      //Information about the advise sink
     IAdviseSink * pAdvSink
                      //Pointer to the advise sink that is to receive 
                      //change notifications
   )
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return S_OK;
   }


   STDMETHODIMP document::XViewObject::GetAdvise(
     DWORD * pdwAspect,  //Pointer to where dwAspect parameter from 
                         //previous SetAdvise call is returned
     DWORD * padvf,      //Pointer to where advf parameter from 
                         //previous SetAdvise call is returned
     IAdviseSink ** ppAdvSink
                         //Address of output var that receives the 
                         //IAdviseSink interface pointer
   )
   {
      METHOD_PROLOGUE_EX_(document, ViewObject)
      return S_OK;
   }*/

   /*DocObjectServer* document::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
   {
      return new DocObjectServer(this, pDocSite);
   }
   */

} // namespace mplite
