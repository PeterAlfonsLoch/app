#pragma once


namespace ansios
{


   class CLASS_DECL_CORE pipe :
      virtual public ::aura::pipe
   {
   public:

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


} // namespace core


#endif


