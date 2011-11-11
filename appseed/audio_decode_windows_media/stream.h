#pragma once

namespace audio_decode_window_media
{

   class stream : 
      virtual public IStream,
      virtual public ::radix::object
   {
   public:
	   stream(::ca::application * papp);
	   virtual ~stream();

      ex1::file * m_pfile;

      ULONG    m_ulRef;

      virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
      /* [in] */ REFIID riid,
      /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

      virtual ULONG STDMETHODCALLTYPE AddRef( void);

      virtual ULONG STDMETHODCALLTYPE Release( void);


      public:
      virtual /* [local] */ HRESULT STDMETHODCALLTYPE Seek( 
         /* [in] */ LARGE_INTEGER dlibMove,
         /* [in] */ DWORD dwOrigin,
         /* [out] */ ULARGE_INTEGER __RPC_FAR *plibNewPosition);

      virtual HRESULT STDMETHODCALLTYPE SetSize( 
         /* [in] */ ULARGE_INTEGER libNewSize);

      virtual /* [local] */ HRESULT STDMETHODCALLTYPE CopyTo( 
         /* [unique][in] */ IStream __RPC_FAR *pstm,
         /* [in] */ ULARGE_INTEGER cb,
         /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbRead,
         /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbWritten);

      virtual HRESULT STDMETHODCALLTYPE Commit( 
         /* [in] */ DWORD grfCommitFlags);

      virtual HRESULT STDMETHODCALLTYPE Revert( void);

      virtual HRESULT STDMETHODCALLTYPE LockRegion( 
         /* [in] */ ULARGE_INTEGER libOffset,
         /* [in] */ ULARGE_INTEGER cb,
         /* [in] */ DWORD dwLockType);

      virtual HRESULT STDMETHODCALLTYPE UnlockRegion( 
         /* [in] */ ULARGE_INTEGER libOffset,
         /* [in] */ ULARGE_INTEGER cb,
         /* [in] */ DWORD dwLockType);

      virtual HRESULT STDMETHODCALLTYPE Stat( 
         /* [out] */ STATSTG __RPC_FAR *pstatstg,
         /* [in] */ DWORD grfStatFlag);

      virtual HRESULT STDMETHODCALLTYPE Clone( 
         /* [out] */ IStream __RPC_FAR *__RPC_FAR *ppstm);

      virtual HRESULT STDMETHODCALLTYPE Read(
        void * pv,
        ULONG cb,
        ULONG* pcbRead
      );

      virtual HRESULT STDMETHODCALLTYPE Write(
        void const* pv,
        ULONG cb,
        ULONG* pcbWritten
      );


   };

} // namespace audio_decode_windows_media