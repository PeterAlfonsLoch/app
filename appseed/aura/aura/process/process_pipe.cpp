#include "framework.h"


namespace process
{


   pipe::pipe(sp(::aura::application) papp) :
      element(papp)
   {

      m_bBlock = false;

      m_bInherit = false;

      m_pchBuf = NULL;

   }


   pipe::~pipe()
   {

      if(m_pchBuf != NULL)
      {

         free(m_pchBuf);

      }

   }


   bool pipe::create(bool bBlock, bool bInherit)
   {

      m_bBlock = bBlock;

      m_bInherit = bInherit;

      return true;

   }


   bool pipe::not_inherit_read()
   {

      return true;

   }

   bool pipe::not_inherit_write()
   {

      return true;

   }


   bool pipe::write(const char * psz)
   {

      return true;

   }


   string pipe::read()
   {

      return "";

   }


   string pipe::one_pass_read()
   {

      return "";

   }


#ifdef WINDOWS

   void pipe::readex()
   {
      
   }

#endif


   cross_pipe::cross_pipe(sp(::aura::application) papp) :
      element(papp),
      m_sppipeIn(allocer()),
      m_sppipeOut(allocer())
   {

   }



} // namespace process





































