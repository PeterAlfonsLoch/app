#pragma once


namespace process
{


   class CLASS_DECL_AURA bidi_pipe:
      virtual public ::object
   {
   public:


      sp(pipe)    m_sppipeIn;
      sp(pipe)    m_sppipeOut;


      bidi_pipe(sp(::aura::application) papp);
      virtual ~bidi_pipe();

      virtual bool create(bool bBlock = true,bool bInherit = false);


   };


} // namespace process


































