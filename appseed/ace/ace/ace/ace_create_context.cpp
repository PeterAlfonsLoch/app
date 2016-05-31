//#include "framework.h" // previously ace/user/user.h


namespace ace
{


   create_context::create_context()
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


} // namespace ace





