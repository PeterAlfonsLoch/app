#pragma once
#pragma once

namespace user
{


} // namespace user


   template < class TOOLBAR >
   bool simple_frame_window::LoadToolBar(id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle,uint32_t dwStyle)
   {
      return LoadToolBar(System.type_info < TOOLBAR >(),idToolBar,pszToolBar,dwCtrlStyle,dwStyle);
   }
