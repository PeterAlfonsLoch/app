#include "framework.h"


CLASS_DECL_c long width(LPCRECT lpcrect)
{
   return lpcrect->right - lpcrect->left;
}

CLASS_DECL_c long height(LPCRECT lpcrect)
{
   return lpcrect->bottom - lpcrect->top;
}

CLASS_DECL_c long width(const RECT & rect)
{
   return rect.right - rect.left;
}

CLASS_DECL_c long height(const RECT & rect)
{
   return rect.bottom - rect.top;
}
