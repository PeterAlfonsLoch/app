#include "StdAfx.h"

namespace acube
{

   application::application()
   {
   }

   application::~application()
   {
   }

   ::ca::application * application::get_system()
   {
      return new application();
   }



} //namespace cube


