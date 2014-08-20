#include "framework.h"

namespace nature
{

   database::database(sp(::axis::application) papp) :
      element(papp)
   {
      m_bInitialized = false;
   }

   database::~database()
   {
      Finalize();
   }

   bool database::Initialize()
   {
      ASSERT(!m_bInitialized);
      if(m_bInitialized)
         return false;
      m_bInitialized = true;

      return true;
   }

   void database::Finalize()
   {
      ASSERT(m_bInitialized);
      if(!m_bInitialized)
         return;
      m_bInitialized = false;
      if(m_pimagefileset != NULL)
         delete m_pimagefileset;
      m_pimagefileset = NULL;
   }


   void database::UpdateImagePaths()
   {
      GetImageFileSet()->refresh();
   }

   simpledb::file_set * database::GetImageFileSet()
   {
      return m_pimagefileset;
   }

} // namespace mplite
