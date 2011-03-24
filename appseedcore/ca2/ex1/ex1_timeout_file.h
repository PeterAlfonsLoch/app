#pragma once

namespace ex1
{

   class CLASS_DECL_ca timeout_file : 
      public ::ex1::file
   {
   public:


      ex1::file *    m_pfile;
      DWORD_PTR      m_uiExpectedSize;
      DWORD          m_dwTimeOut;
      DWORD          m_dwLastCall;
      DWORD          m_dwSleep;

      timeout_file(::ca::application * papp, ex1::file * pfile, DWORD_PTR uiExpectedSize = ((DWORD_PTR) -1));
      virtual ~timeout_file();

      virtual bool IsValid() const;
      INT_PTR seek(INT_PTR lOff, UINT nFrom);
      DWORD_PTR GetPosition() const;
      DWORD_PTR get_length() const;

      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);
      virtual void write(const void * lpBuf, DWORD_PTR nCount);
      virtual void Flush();
      virtual void SetLength(DWORD_PTR dwNewLen);

   };

} // namespace ex1