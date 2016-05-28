


















// size
inline size::size() throw()
{

   /* NOT random filled ANYMORE */
   /* with you want a random filled, or more properly a not explicitly initialized size, pass noinit dummy class as argument */

   cx = 0;
   cy = 0;

}


inline size::size(no_init) throw()
{

   /* random filled*/
   /* with you want a random filled, or more properly a not explicitly initialized size, pass noinit dummy class as argument */

}


inline size::size(int64_t initCX,int64_t initCY) throw()
{

   cx = (int32_t)initCX; 
   
   cy = (int32_t)initCY;

}


inline size::size(SIZE initSize) throw()
{
   
   *(SIZE*)this = initSize;

}


inline size::size(const SIZE * pinitSize) throw()
{

   *this = *pinitSize;

}


inline size::size(const RECT & rect) throw()
{
   
   cx = width(rect);

   cy = height(rect);

}


inline size::size(LPCRECT lpcrect) throw()
{
   
   if(lpcrect == NULL)
   {

      cx = 0;

      cy = 0;

   }
   else
   {

      cx = width(lpcrect);

      cy = height(lpcrect);

   }

}


inline size::size(SIZE64  initSize) throw()
{

   cx = (int32_t)initSize.cx; 
   
   cy = (int32_t)initSize.cy;

}


inline size::size(const SIZE64 *  pinitSize) throw()
{

   cx = (int32_t)pinitSize->cx; 
   
   cy = (int32_t)pinitSize->cy;

}


inline size::size(SIZED  initSize) throw()
{
   
   cx = (int32_t)initSize.cx; 
   
   cy = (int32_t)initSize.cy;

}


inline size::size(const SIZED *  pinitSize) throw()
{
   
   cx = (int32_t)pinitSize->cx; 
   
   cy = (int32_t)pinitSize->cy;

}


inline size::size(POINT initPt) throw()
{

   *(POINT*)this = initPt;

}


inline size::size(uint32_t dwSize) throw()
{

   cx = (int16_t)LOWORD(dwSize);

   cy = (int16_t)HIWORD(dwSize);

}


inline size::operator SIZE *() throw()
{

   return this;

}


inline size::operator const SIZE *() const throw()
{

   return this;

}


inline bool size::operator==(SIZE size) const throw()
{

   return (cx == size.cx && cy == size.cy);

}


inline bool size::operator!=(SIZE size) const throw()
{

   return (cx != size.cx || cy != size.cy);

}


inline void size::operator+=(SIZE size) throw()
{

   cx += size.cx; 
   
   cy += size.cy;

}


inline void size::operator-=(SIZE size) throw()
{

   cx -= size.cx; 
   
   cy -= size.cy;

}

inline void size::set_size(int32_t CX,int32_t CY) throw()
{

   cx = CX; 
   
   cy = CY;

}


inline class size size::operator+(SIZE size) const throw()
{

   class size sizeRet;

   sizeRet.cx = cx + size.cx;

   sizeRet.cy = cy + size.cy;

   return sizeRet;

}


inline size size::operator-(SIZE size) const throw()
{

   class size sizeRet;

   sizeRet.cx = cx - size.cx;

   sizeRet.cy = cy - size.cy;

   return sizeRet;

}


inline size size::operator-() const throw()
{

   return size(-cx,-cy);

}


inline point size::operator+(POINT point) const throw()
{

   class point pointRet;

   pointRet.x = cx + point.x;

   pointRet.y = cy + point.y;

   return pointRet;

}


inline point size::operator-(POINT point) const throw()
{

   class point pointRet;

   pointRet.x = cx - point.x;

   pointRet.y = cy - point.y;

   return pointRet;

}


inline rect size::operator+(LPCRECT lpRect) const throw()
{

   return rect(lpRect) + *this;

}


inline rect size::operator-(LPCRECT lpRect) const throw()
{

   return rect(lpRect) - *this;

}


inline int64_t size::area() const throw()
{

   return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy;

}


inline uint32_t  size::  ui32() const throw()
{

   return MAKELONG((int32_t)cx,(int32_t)cy);

}


inline uint64_t  size::  ui64() const throw()
{

   return MAKELONG64((int32_t)cx,(int32_t)cy);

}


inline LPARAM    size::lparam() const throw()
{

   return MAKELPARAM((int32_t)cx,(int32_t)cy);

}




inline size64::operator SIZE()
{
   
   SIZE sz = { (LONG)cx, (LONG)cy };

   return sz;

}



