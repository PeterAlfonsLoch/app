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


      pipe(sp(::aura::application) papp);
      virtual ~pipe();


      virtual bool create(bool bBlock = true, bool bInherit = false);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();



   };


} // namespace core





































