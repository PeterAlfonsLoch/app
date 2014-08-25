#pragma once


namespace ansios
{


   class CLASS_DECL_CORE pipe :
      virtual public ::aura::pipe
   {
   public:


      char *               m_pchBuf;
      string               m_strRead;

      int32_t                  m_fd[2];


      pipe(bool bInherit);
      virtual ~pipe();


      bool create(bool bBlock = true);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();



   };


} // namespace core


#endif


