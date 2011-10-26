#pragma once


namespace iexca2
{


   class ole_inplace_object_windowless : public IOleInPlaceObjectWindowless
   {
   public:


      host * m_pinstance;


      ole_inplace_object_windowless(host *pinstance) :
         m_pinstance(pinstance) 
      {
      }

      virtual ~ole_inplace_object_windowless()
      {
      }


      // IUnknown methods
      STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
      {
         if( NULL == ppv )
            return E_POINTER;
         if( (IID_IUnknown == riid)
            || (IID_IOleWindow == riid)
            || (IID_IOleInPlaceObject == riid)
            || (IID_IOleInPlaceObjectWindowless == riid) )
         {
            AddRef();
            *ppv = reinterpret_cast<LPVOID>(this);
            return NOERROR;
         }
         return m_pinstance->pUnkOuter->QueryInterface(riid, ppv);
      }

      STDMETHODIMP_(ULONG) AddRef(void) { return m_pinstance->pUnkOuter->AddRef(); }
      STDMETHODIMP_(ULONG) Release(void) { return m_pinstance->pUnkOuter->Release(); }

      // IOleWindow methods
      STDMETHODIMP GetWindow(HWND *);
      STDMETHODIMP ContextSensitiveHelp(BOOL);

      // IOleInPlaceObject methods
      STDMETHODIMP InPlaceDeactivate(void);
      STDMETHODIMP UIDeactivate(void);
      STDMETHODIMP SetObjectRects(LPCRECT, LPCRECT);
      STDMETHODIMP ReactivateAndUndo(void);

      // IOleInPlaceActiveObject methods
      STDMETHODIMP OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult);
      STDMETHODIMP GetDropTarget(IDropTarget **ppDropTarget);

   };

} // namespace iexca2