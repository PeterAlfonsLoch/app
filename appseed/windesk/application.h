#pragma once

namespace windesk
{

   enum eflag
   {
      flag_enable_wallpaper,
   };

   class CLASS_DECL_CA2_WINDESK flags :
      virtual public ::flags < eflag >
   {
   };


   class CLASS_DECL_CA2_WINDESK application :
      public ::cube::application,
      public IDropTarget
   {
   public:
      
      
      flags                            m_flags;
      ::userbase::multiple_document_template *   m_ptemplate_html;
      comparable_array < HWND >        m_hwndaDesktop;
      base_array < rect >         m_rectaMonitor;

      
      application(void);
      virtual ~application(void);


      // IUnknown
      virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
          /* [in] */ REFIID riid,
          /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

      virtual ULONG STDMETHODCALLTYPE AddRef( void);

      virtual ULONG STDMETHODCALLTYPE Release( void);



      // IDropTarget
     virtual HRESULT STDMETHODCALLTYPE DragEnter( 
         /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL pt,
         /* [out][in] */ __RPC__inout DWORD *pdwEffect);
     
     virtual HRESULT STDMETHODCALLTYPE DragOver( 
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL pt,
         /* [out][in] */ __RPC__inout DWORD *pdwEffect);
     
     virtual HRESULT STDMETHODCALLTYPE DragLeave( void);
     
     virtual HRESULT STDMETHODCALLTYPE Drop( 
         /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL pt,
         /* [out][in] */ __RPC__inout DWORD *pdwEffect);


     virtual IDropTarget * i_drop_target_from_point(point pt);


      

      bool initialize_instance();
      int exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   		

      virtual ::ca::application * get_app() const;

      virtual bool on_assert_failed_line(const char * lpszFileName, int iLine);


      virtual bool final_handle_exception(::ca::exception & e);


      DECL_GEN_VSIGNAL(data_on_after_change);

   };

   inline CLASS_DECL_CA2_WINDESK application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace windesk