#pragma once


namespace aura
{


   class CLASS_DECL_AURA pipe :
      virtual public ::object
   {
   public:

      
      char *               m_pchBuf;
      string               m_strRead;

      bool                 m_bInherit;
      bool                 m_bBlock;


      pipe(sp(::aura::application) papp);
      virtual ~pipe();


      virtual bool create(bool bBlock = true, bool bInherit = false);


      virtual bool not_inherit_read();
      virtual bool not_inherit_write();

      virtual bool write(const char * psz);
      virtual string read();
      virtual string one_pass_read();


   };

   
   class CLASS_DECL_AURA cross_pipe :
      virtual public ::object
   {
   public:


      sp(pipe)    m_sppipeIn;
      sp(pipe)    m_sppipeOut;


      cross_pipe(sp(::aura::application) papp);

      virtual bool create(bool bBlock = true, bool bInherit = false);


   };


} // namespace aura


































