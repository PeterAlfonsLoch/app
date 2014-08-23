#include "framework.h"


namespace draw2d_cairo
{


   pen::pen(sp(::aura::application) papp) :
      element(papp)
   {
   }
   pen::~pen()
   {
   }


   /*   void pen::construct(int32_t nPenStyle, int32_t nWidth, COLORREF crColor)
   {
      if (!Attach(::CreatePen(nPenStyle, nWidth, crColor)))
         AfxThrowResourceException();
   }
*/
/*
   void pen::construct(int32_t nPenStyle, int32_t nWidth, const LOGBRUSH* pLogBrush,
      int32_t nStyleCount, const DWORD* lpStyle)
   {
      if (!Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
         lpStyle)))
         AfxThrowResourceException();
   }
*/
   /////////////////////////////////////////////////////////////////////////////


#ifdef DEBUG

   void pen::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);
//
  //    if (get_handle() == NULL)
    //     return;

/*      if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
      {
         // not a valid object
         dumpcontext << "has ILLEGAL HPEN!";
         return;
      }
*/
  /*    LOGPEN lp;
      VERIFY(GetObject(sizeof(lp), &lp));
      dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
      dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
      dumpcontext << "\nlgpn.lopnColor = " << (void *)(dword_ptr)lp.lopnColor;

      dumpcontext << "\n";
*/
   }

#endif




      // IMPLEMENT_DYNAMIC(resource_exception, ::exception::base)
      //resource_exception _simpleResourceException(FALSE, __IDS_RESOURCE_EXCEPTION);

      // IMPLEMENT_DYNAMIC(user_exception, ::exception::base)
      //user_exception _simpleUserException(FALSE, __IDS_USER_EXCEPTION);

      // IMPLEMENT_DYNCREATE(::draw2d::graphics_sp, object)
      // IMPLEMENT_DYNAMIC(CClientDC, ::draw2d::graphics_sp)
      // IMPLEMENT_DYNAMIC(CWindowDC, ::draw2d::graphics_sp)
      // IMPLEMENT_DYNAMIC(CPaintDC, ::draw2d::graphics_sp)
      // IMPLEMENT_DYNCREATE(object, object)

      // IMPLEMENT_DYNAMIC(pen, object)
      // IMPLEMENT_DYNAMIC(::draw2d::brush, object)
      // IMPLEMENT_DYNAMIC(::draw2d::font, object)
      // IMPLEMENT_DYNAMIC(::draw2d::bitmap, object)
      // IMPLEMENT_DYNAMIC(::draw2d::palette, object)
      // IMPLEMENT_DYNAMIC(::core::rgn, object)

      /////////////////////////////////////////////////////////////////////////////
      // Standard exception processing



} // namespace draw2d_cairo




