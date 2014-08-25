#pragma once


namespace windows
{


   class CLASS_DECL_AURA pipe :
      virtual public ::aura::pipe
   {
   public:


      class overlapped
      {
      public:
         pipe * m_ppipe;
         OVERLAPPED m_overlapped;
         inline overlapped * from(OVERLAPPED * poverlapped)
         {
            return (overlapped *)((BYTE *)poverlapped - sizeof(pipe *));
         }
      };


      char *               m_pchBuf;
      string               m_strRead;

      overlapped           m_overlapped;

      SECURITY_ATTRIBUTES  m_sa;
      HANDLE               m_hRead;
      HANDLE               m_hWrite;


      pipe(sp(::aura::application) papp);
      virtual ~pipe();


      virtual bool create(bool bBlock = true, bool bInherit = false);


      virtual bool not_inherit_read();
      virtual bool not_inherit_write();

      virtual bool write(const char * psz);
      virtual string read();
      virtual string one_pass_read();


      virtual void readex();


      static void WINAPI read_complete(
         uint32_t dwErrorCode,
         uint32_t dwNumberOfBytesTransfered,
         LPOVERLAPPED lpOverlapped
         );

   };


} // namespace windows

































