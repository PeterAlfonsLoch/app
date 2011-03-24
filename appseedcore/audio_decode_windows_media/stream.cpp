#include "StdAfx.h"

namespace audio_decode_window_media
{

   stream::stream(::ca::application * papp) :
      ca(papp)
   {
      m_ulRef = 0;
   }

   stream::~stream()
   {

   }

   HRESULT STDMETHODCALLTYPE stream::QueryInterface( 
      /* [in] */ REFIID riid,
      /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
   {
      if(riid == IID_IStream)
      {
         *ppvObject = this;
         return NOERROR;
      }
      else if(riid == IID_ISequentialStream)
      {
         *ppvObject = this;
         return NOERROR;
      }
      else
      {
         return  E_NOINTERFACE;
      }
   }

   ULONG STDMETHODCALLTYPE stream::AddRef( void)
   {
      m_ulRef++;
      return m_ulRef;
   }

   ULONG STDMETHODCALLTYPE stream::Release( void)
   {
      if(m_ulRef == 0)
         return 0;
      m_ulRef--;
      if(m_ulRef == 0)
         delete this;
      return m_ulRef;
   }

   HRESULT STDMETHODCALLTYPE stream::Seek( 
      /* [in] */ LARGE_INTEGER dlibMove,
      /* [in] */ DWORD dwOrigin,
      /* [out] */ ULARGE_INTEGER __RPC_FAR *plibNewPosition)
   {
      switch(dwOrigin)
      {
      case STREAM_SEEK_SET:
         dwOrigin = ::ex1::seek_begin;
         break;
      case STREAM_SEEK_CUR:
         dwOrigin = ::ex1::seek_current;
         break;
      case STREAM_SEEK_END:
         dwOrigin = ::ex1::seek_end;
         break;
      default:
         return E_INVALIDARG;
      }

      if(dlibMove.HighPart || (dlibMove.LowPart & 0x8000000))
         return E_INVALIDARG;

      ULONG ul;
      try
      {
         ul = m_pfile->seek(dlibMove.LowPart, dwOrigin);
      }
      catch(ex1::file_exception_sp *)
      {
         return ERROR;
      }
      if(plibNewPosition != NULL)
      {
         plibNewPosition->LowPart  = ul;
         plibNewPosition->HighPart = 0;
      }
      return NOERROR;
   }

   HRESULT STDMETHODCALLTYPE stream::SetSize( 
     /* [in] */ ULARGE_INTEGER libNewSize)
   {
      UNREFERENCED_PARAMETER(libNewSize);
      return E_NOTIMPL;
   }

   /* [local] */ HRESULT STDMETHODCALLTYPE stream::CopyTo( 
      /* [unique][in] */ IStream __RPC_FAR *pstm,
      /* [in] */ ULARGE_INTEGER cb,
      /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbRead,
      /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbWritten)
   {
      UNREFERENCED_PARAMETER(pstm);
      UNREFERENCED_PARAMETER(cb);
      UNREFERENCED_PARAMETER(pcbRead);
      UNREFERENCED_PARAMETER(pcbWritten);
      return E_NOTIMPL;
   }

   HRESULT STDMETHODCALLTYPE stream::Commit( 
      /* [in] */ DWORD grfCommitFlags)
   {
      UNREFERENCED_PARAMETER(grfCommitFlags);
      m_pfile->Flush();
      return NOERROR;
   }

   HRESULT STDMETHODCALLTYPE stream::Revert( void)
   {
      ASSERT(FALSE);
      return E_NOTIMPL;
   }

   HRESULT STDMETHODCALLTYPE stream::LockRegion( 
      /* [in] */ ULARGE_INTEGER libOffset,
      /* [in] */ ULARGE_INTEGER cb,
      /* [in] */ DWORD dwLockType)
   {
      UNREFERENCED_PARAMETER(libOffset);
      UNREFERENCED_PARAMETER(cb);
      UNREFERENCED_PARAMETER(dwLockType);
      ASSERT(FALSE);
      return E_NOTIMPL;
   }

   HRESULT STDMETHODCALLTYPE stream::UnlockRegion( 
      /* [in] */ ULARGE_INTEGER libOffset,
      /* [in] */ ULARGE_INTEGER cb,
      /* [in] */ DWORD dwLockType)
   {
      UNREFERENCED_PARAMETER(libOffset);
      UNREFERENCED_PARAMETER(cb);
      UNREFERENCED_PARAMETER(dwLockType);
      ASSERT(FALSE);
      return E_NOTIMPL;
   }

   HRESULT STDMETHODCALLTYPE stream::Stat( 
      /* [out] */ STATSTG __RPC_FAR *pstatstg,
      /* [in] */ DWORD grfStatFlag)
   {
      ASSERT(m_pfile != NULL);

      if(pstatstg == NULL)
         return E_INVALIDARG;
      if((grfStatFlag & STATFLAG_NONAME) == 0)
      {
         pstatstg->pwcsName = m_pfile->GetFileName().AllocSysString();
      }
      ::ex1::file_status status;
      if(!m_pfile->GetStatus(status))
      {
         // The file did not returned a status. What to do?
         ASSERT(FALSE);
         return NOERROR;
      }
      pstatstg->type = STGTY_LOCKBYTES;
      pstatstg->cbSize.HighPart = 0;
      pstatstg->cbSize.LowPart = status.m_size;
      win::TimeToFileTime(get_app(), status.m_mtime, &pstatstg->mtime);
      win::TimeToFileTime(get_app(), status.m_ctime, &pstatstg->ctime);
      win::TimeToFileTime(get_app(), status.m_atime, &pstatstg->atime);
      pstatstg->grfMode = 0;
      pstatstg->grfLocksSupported = LOCK_EXCLUSIVE;
      pstatstg->clsid = CLSID_NULL;
      pstatstg->grfStateBits = 0;
      pstatstg->reserved = 0;
      
      return NOERROR;
   }

   HRESULT STDMETHODCALLTYPE stream::Clone( 
      /* [out] */ IStream __RPC_FAR *__RPC_FAR *ppstm)
   {
      UNREFERENCED_PARAMETER(ppstm);
      ASSERT(FALSE);
      return E_NOTIMPL;
   }


   HRESULT STDMETHODCALLTYPE stream::Read(
     void * pv,
     ULONG cb,
     ULONG* pcbRead
     )
   {
      ULONG ul;
      try
      {
         ul = m_pfile->read(pv, cb);
      }
      catch(ex1::file_exception_sp *)
      {
         return ERROR;
      }
      if(pcbRead)
      {
         *pcbRead = ul;
      }
      return NOERROR;
   }



   HRESULT STDMETHODCALLTYPE stream::Write(
     void const* pv,
     ULONG cb,
     ULONG* pcbWritten
   )
   {
      UNREFERENCED_PARAMETER(pv);
      UNREFERENCED_PARAMETER(cb);
      UNREFERENCED_PARAMETER(pcbWritten);
      return E_NOTIMPL;
   }


} // namespace audio_decode_window_media
