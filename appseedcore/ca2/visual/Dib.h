#pragma once

namespace visual
{

   class CLASS_DECL_ca dib_sp :
      public ::ca::dib_sp
   {
   public:
	   bool From(HDC hdc, FIBITMAP * pfibitmap, bool bUnloadFI);
      dib_sp(::ca::application * papp);
	   virtual ~dib_sp();
   };

}

