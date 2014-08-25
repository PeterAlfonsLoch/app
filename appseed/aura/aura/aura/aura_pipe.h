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


      pipe();
      virtual ~pipe();


      bool set_inherit(

      bool create(bool bBlock = true);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();


   };

   
   class CLASS_DECL_AURA cross_pipe :
      virtual public ::object
   {
   public:


      sp(pipe)    m_sppipeIn;
      sp(pipe)    m_sppipeOut;


      cross_pipe(sp(::aura::application) papp);

      virtual void set_inherit(bool bInherit);


      bool create(bool bBlock = true);


   };


} // namespace aura


































