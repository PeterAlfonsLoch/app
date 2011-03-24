#pragma once

namespace ex1
{

   class CLASS_DECL_ca buffered_file : 
      public ::ex1::file
   {
   public:


      ex1::filesp          m_pfile;

      DWORD_PTR            m_uiBufferSize;
      DWORD_PTR            m_uiPosition;
      DWORD_PTR            m_uiBufLPos;
      DWORD_PTR            m_uiBufUPos;
      bool                 m_bDirty;
      DWORD_PTR            m_uiWriteLPos;
      DWORD_PTR            m_uiWriteUPos;
      primitive::memory    m_storage;



      buffered_file(::ca::application * papp, ex1::filesp pfile, DWORD_PTR iBufferSize = 1024 * 128);
      virtual ~buffered_file();

      virtual bool IsValid() const;
      INT_PTR seek(INT_PTR lOff, UINT nFrom);
      DWORD_PTR GetPosition() const;
      DWORD_PTR get_length() const;

      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);
      virtual void write(const void * lpBuf, DWORD_PTR nCount);
      virtual void Flush();
      virtual bool buffer(DWORD_PTR uiGrow = 0);
      virtual void SetLength(DWORD_PTR dwNewLen);

      DWORD_PTR      GetBufferSize();

   };

} // namespace ex1