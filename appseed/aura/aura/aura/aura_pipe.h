#pragma once


namespace core
{

   class CLASS_DECL_CORE pipe
   {
   public:

      
      public:
         pipe * m_ppipe;
         OVERLAPPED m_overlapped;
         inline overlapped * from(OVERLAPPED * poverlapped)
         {
            return (overlapped *)((BYTE *)poverlapped - sizeof(pipe *));
         }
      };

#endif


      char *               m_pchBuf;
      string               m_strRead;

#ifdef WINDOWS

      overlapped           m_overlapped;

      SECURITY_ATTRIBUTES  m_sa;
      HANDLE               m_hRead;
      HANDLE               m_hWrite;

#else

      int32_t                  m_fd[2];

#endif

      pipe(bool bInherit);
      virtual ~pipe();


      bool create(bool bBlock = true);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();


#ifdef WINDOWS

      void readex();


      static void WINAPI read_complete(
         uint32_t dwErrorCode,
         uint32_t dwNumberOfBytesTransfered,
         LPOVERLAPPED lpOverlapped
         );

#endif

   };

   class CLASS_DECL_CORE cross_pipe
   {
   public:


      pipe m_pipeIn;
      pipe m_pipeOut;


      cross_pipe(bool bInherit);


      bool create(bool bBlock = true);


   };


} // namespace core


#endif


