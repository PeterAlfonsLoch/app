#pragma once


namespace core
{

   class CLASS_DECL_AURE pipe :
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


      pipe(bool bInherit);
      virtual ~pipe();


      bool create(bool bBlock = true);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();


      void readex();


      static void WINAPI read_complete(
         uint32_t dwErrorCode,
         uint32_t dwNumberOfBytesTransfered,
         LPOVERLAPPED lpOverlapped
         );

   };


} // namespace core



