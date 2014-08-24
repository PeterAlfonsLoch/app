#include "framework.h"


namespace user
{


   create_context::create_context(sp(::aura::application) papp) :
      element(papp)
   {

      m_pCurrentDoc        = NULL;
      m_pNewDocTemplate    = NULL;
      m_pLastView          = NULL;
      m_pCurrentFrame      = NULL;
      m_puiNew             = NULL;

   }

   create_context::~create_context()
   {

   }


   void create_context::void_delete(void * pvoid)
   {

      ::user::create_context * pcreatecontext = (::user::create_context *) pvoid;

      try
      {

         delete pcreatecontext;

      }
      catch(...)
      {

      }

   }


} // namespace user





