#pragma once


namespace aura
{


   class CLASS_DECL_AURA pipe
   {
   public:

      
      char *               m_pchBuf;
      string               m_strRead;


      pipe(bool bInherit);
      virtual ~pipe();


      bool create(bool bBlock = true);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();


   };

   
   class CLASS_DECL_AURA cross_pipe
   {
   public:


      spipe m_pipeIn;
      pipe m_pipeOut;


      cross_pipe(bool bInherit);


      bool create(bool bBlock = true);


   };


} // namespace aura





















