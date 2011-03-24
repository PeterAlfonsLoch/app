#pragma once


namespace iexca2
{

   class plugin : 
      public IUnknown,
      public npca2::plugin
   {

   public:

   
      HWND           m_hwnd;
      bool           m_bStream;
      std::string    m_strBaseUrl;


      plugin(class_factory *p_class, LPUNKNOWN pUnkOuter);

      /* IUnknown methods */
      STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
      STDMETHODIMP_(ULONG) AddRef(void);
      STDMETHODIMP_(ULONG) Release(void);

      virtual HWND get_host_window();


      /* custom methods */
      HRESULT getTypeLib(LCID lcid, ITypeLib **pTL) { return LoadRegTypeLib(LIBID_iexca2, 1, 0, lcid, pTL); };
      REFCLSID getClassID(void) { return _p_class->getClassID(); };
      REFIID getDispEventID(void) { return (REFIID)DIID_iexca2_events_dispatch; };

      void setBackColor(OLE_COLOR backcolor);
      OLE_COLOR getBackColor(void) { return _i_backcolor; };

      void setTestString(BSTR str)
      {
         SysFreeString(_bstr_testString);
         _bstr_testString = SysAllocStringLen(str, SysStringLen(str)); 
         setTestStringEditBox();
      };

      const BSTR getTestString(void) 
      {         
         return _bstr_testString; 
      };

      // control size in HIMETRIC
      inline void setExtent(const SIZEL& extent)
      {
         _extent = extent;
         setDirty(TRUE);
      };
      const SIZEL& getExtent(void) { return _extent; };

      inline void setPicture(LPPICTURE pict)
      {
         if( NULL != _p_pict )
            _p_pict->Release();
         if( NULL != pict )
            _p_pict->AddRef();
         _p_pict = pict;
      };

      inline LPPICTURE getPicture(void)
      {
         if( NULL != _p_pict )
            _p_pict->AddRef();
         return _p_pict;
      };

      BOOL hasFocus(void);
      void setFocus(BOOL fFocus);

      inline UINT getCodePage(void) { return _i_codepage; };
      inline void setCodePage(UINT cp)
      {
         // accept new codepage only if it works on this system
         size_t mblen = WideCharToMultiByte(cp,
            0, L"test", -1, NULL, 0, NULL, NULL);
         if( mblen > 0 )
            _i_codepage = cp;
      };

      inline BOOL isUserMode(void) { return _b_usermode; };
      inline void setUserMode(BOOL um) { _b_usermode = um; };

      inline BOOL isDirty(void) { return _b_dirty; };
      inline void setDirty(BOOL dirty) { _b_dirty = dirty; };

      void setErrorInfo(REFIID riid, const char *description);

      // control geometry within container
      RECT getPosRect(void) { return m_rect; };
      inline HWND getInPlaceWindow(void) const { return _inplacewnd; };
      BOOL isInPlaceActive(void);

      /*
      ** container events
      */
      HRESULT onInit(void);
      HRESULT onLoad(void);
      HRESULT onActivateInPlace(LPMSG lpMesg, HWND hwndParent, LPCRECT lprcPosRect, LPCRECT lprcClipRect);
      HRESULT onInPlaceDeactivate(void);
      HRESULT onAmbientChanged(LPUNKNOWN pContainer, DISPID dispID);
      HRESULT onClose(DWORD dwSaveOption);
      void onPositionChange(LPCRECT lprcPosRect, LPCRECT lprcClipRect);
      void onDraw(DVTARGETDEVICE * ptd, HDC hicTargetDev, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds);



      /*
      ** control events
      */
      void freezeEvents(BOOL freeze);
      void firePropChangedEvent(DISPID dispid);
      void fireOnPlayEvent(void);
      void fireOnPauseEvent(void);
      void fireOnStopEvent(void);

      /**
      *  Example Control
      */
      //show main ActiveX window
      void show();
      //hide main ActiveX window
      void hide();
      //fill string from edit box
      void getTestStringEditBox();
      //clear Edit box
      void clearEditBox();

      // controlling IUnknown interface
      LPUNKNOWN pUnkOuter;


      virtual bool open_url(const char * psz);
      virtual void redraw();
      virtual bool is_ok();
      virtual void post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);
      virtual void get_window_rect(__rect64 * lprect);
      virtual void get_window_rect(LPRECT lprect);
      virtual npca2::host_interaction * create_host_interaction();
      virtual void on_prepare_memory();


   protected:

      void setTestStringEditBox();    
      virtual ~plugin();

   public:

      //implemented interfaces
      class ole_object *vlcOleObject;
      class ole_control *vlcOleControl;
      //class ole_inplace_object *vlcOleInPlaceObject;
      //class ole_inplace_active_object *vlcOleInPlaceActiveObject;
      class ole_inplace_object_windowless  * vlcOleInPlaceObjectWindowless;
      class persist_stream_init *vlcPersistStreamInit;
      class persist_storage *vlcPersistStorage;
      class persist_property_bag *vlcPersistPropertyBag;
      class provide_class_info *vlcProvideClassInfo;
      class connection_point_container *vlcConnectionPointContainer;
      class object_safety *vlcObjectSafety;
      class control *vlcControl2;
      class view_object *vlcViewObject;
      class data_object *vlcDataObject;
      class support_error_info *vlcSupportErrorInfo;

      std::string                      m_strSrc;

      HWND                             m_hwndSite;
      IOleInPlaceSiteWindowless *      m_psite;

      // in place activated window (Plugin window)
      HWND                            _inplacewnd;

      class_factory*                 _p_class;
      ULONG                           _i_ref;

      UINT                            _i_codepage;
      BOOL                            _b_usermode;
      LPPICTURE                       _p_pict;

      SIZEL                           _extent;
      OLE_COLOR                       _i_backcolor;
      // indicates whether properties needs persisting
      BOOL                            _b_dirty;

      //Example with params
      BSTR                            _bstr_testString;
   };


} // namespace iexca2