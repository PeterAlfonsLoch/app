#include "StdAfx.h"
#include "AlbumBuildThread.h"
#include "AlbumBuildWnd.h"

namespace  mediamanager
{

   AlbumBuildThread::AlbumBuildThread(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
      m_pwnd = NULL;
      m_heventSynch = ::CreateEvent(NULL, TRUE, FALSE, NULL);
   }

   AlbumBuildThread::~AlbumBuildThread()
   {
   }

   bool AlbumBuildThread::initialize_instance()
   {
      m_pwnd = new AlbumBuildWnd(get_app());
      m_pwnd->create();
      if(m_heventSynch != NULL)
      {
         ::SetEvent(m_heventSynch);
      }
      return true;
   }

   int AlbumBuildThread::exit_instance()
   {
      return thread::exit_instance();
   }

   void AlbumBuildThread::Initialize(AlbumBuild *palbumbuild)
   {
      ASSERT(m_pwnd != NULL);
      m_pwnd->Initialize(palbumbuild);
      m_palbumbuild = palbumbuild;
   }

}

