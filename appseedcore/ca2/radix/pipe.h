#pragma once


namespace gen
{

   class CLASS_DECL_ca pipe
   {
   public:

      class overlapped
      {
      public:
         pipe * m_ppipe;
         OVERLAPPED m_overlapped;
         inline overlapped * from(OVERLAPPED * poverlapped)
         {
            return (overlapped * ) ((BYTE *) poverlapped - sizeof(pipe *));
         }
      };

      pipe(bool bInherit);
      virtual ~pipe();

      bool create();

      SECURITY_ATTRIBUTES m_sa;
      HANDLE m_hRead;
      HANDLE m_hWrite;

      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();

      void readex();

      overlapped m_overlapped;

      char * m_pchBuf;
      string m_strRead;

      static void WINAPI read_complete(
         DWORD dwErrorCode,
         DWORD dwNumberOfBytesTransfered,
         LPOVERLAPPED lpOverlapped
         );
   


   };

   class CLASS_DECL_ca cross_pipe
   {
   public:
      cross_pipe(bool bInherit);
      bool create();
      pipe m_pipeIn;
      pipe m_pipeOut;
   };

} // namespace gen