#pragma once


/////////////////////////////////////////////////////////////////////////////
// point - A 2-D point, similar to Windows POINT structure.

class CLASS_DECL_BASE point : public tagPOINT
{
public:
// Constructors

   // create an uninitialized point
   point() throw();
   // create from two integers
   point(int64_t initX, int64_t initY) throw();
   // create from another point
   point(POINT initPt) throw();
   point(const POINT * pinitPt) throw();
   point(__point64 initPt) throw();
   point(const __point64 * pinitPt) throw();
   // create from a size
   point(SIZE initSize) throw();
   // create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
   point(const lparam & dwPoint) throw();


   operator POINT *() throw();
   operator const POINT *() const throw();

// Operations

// translate the point
   void offset(int32_t xOffset, int32_t yOffset) throw();
   void offset(POINT point) throw();
   void offset(SIZE size) throw();
   void SetPoint(int32_t X, int32_t Y) throw();

   bool operator==(POINT point) const throw();
   bool operator!=(POINT point) const throw();
   void operator+=(SIZE size) throw();
   void operator-=(SIZE size) throw();
   void operator+=(POINT point) throw();
   void operator-=(POINT point) throw();

// Operators returning point values
   point operator+(SIZE size) const throw();
   point operator-(SIZE size) const throw();
   point operator-() const throw();
   point operator+(POINT point) const throw();

// Operators returning size values
   size operator-(POINT point) const throw();

// Operators returning rect values
   rect operator+(LPCRECT lpRect) const throw();
   rect operator-(LPCRECT lpRect) const throw();

   uint32_t ui32() const throw();
   uint64_t ui64() const throw();
   LPARAM   lparam() const throw();

   inline LONG get_dimension(e_orientation eorientation) const throw();
   inline LONG get_orthogonal_dimension(e_orientation eorientation) const throw();
   inline LONG get_orthogonal(e_orientation eorientation)const throw() { return get_orthogonal_dimension(eorientation); }
   inline LONG get_normal_dimension(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); }
   inline LONG get_normal(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); }

   inline LONG set_dimension(e_orientation eorientation,LONG l) throw();
   inline LONG set_orthogonal_dimension(e_orientation eorientation,LONG l) throw();
   inline LONG set_orthogonal(e_orientation eorientation,LONG l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal_dimension(e_orientation eorientation,LONG l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal(e_orientation eorientation,LONG l) throw() { return set_orthogonal_dimension(eorientation,l); }


};


inline point null_point() { return point(0, 0); }

/////////////////////////////////////////////////////////////////////////////
// point64 - A 2-D point64, similar to Windows __point64 structure.

class CLASS_DECL_BASE point64 : public __point64
{
public:
// Constructors

   // create an uninitialized point64
   point64() throw();
   // create from two integers
   point64(int64_t initX, int64_t initY) throw();
   // create from another point64
   point64(__point64 initPt) throw();
   point64(POINT pt) throw();
   point64(const __point64 * pinitPt) throw();
   // create from a size
   point64(__size64 initSize) throw();
   // create from an UINT64: x = LODWORD(dw) y = HIDWORD(dw)
   point64(uint64_t dwPoint) throw();

   operator __point64 *() throw();
   operator const __point64 *() const throw();

// Operations

// translate the point64
   void offset(int64_t xOffset, int64_t yOffset) throw();
   void offset(__point64 point64) throw();
   void offset(__size64 size) throw();
   void SetPoint(int64_t X, int64_t Y) throw();

   bool operator==(__point64 point64) const throw();
   bool operator!=(__point64 point64) const throw();
   void operator+=(__size64 size) throw();
   void operator-=(__size64 size) throw();
   void operator+=(__point64 point64) throw();
   void operator-=(__point64 point64) throw();

// Operators returning point64 values
   point64 operator+(__size64 size) const throw();
   point64 operator-(__size64 size) const throw();
   point64 operator-() const throw();
   point64 operator+(__point64 point64) const throw();

// Operators returning size values
   size64 operator-(__point64 point64) const throw();

// Operators returning rect values
   rect64 operator+(const __rect64 * lpRect) const throw();
   rect64 operator-(const __rect64 * lpRect) const throw();

   uint32_t ui32() const throw();
   uint64_t ui64() const throw();
   LPARAM   lparam() const throw();

   inline int64_t get_dimension(e_orientation eorientation) const throw();
   inline int64_t get_orthogonal_dimension(e_orientation eorientation) const throw();
   inline int64_t get_orthogonal(e_orientation eorientation)const throw() { return get_orthogonal_dimension(eorientation); }
   inline int64_t get_normal_dimension(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); }
   inline int64_t get_normal(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); }

   inline int64_t set_dimension(e_orientation eorientation,int64_t l) throw();
   inline int64_t set_orthogonal_dimension(e_orientation eorientation,int64_t l) throw();
   inline int64_t set_orthogonal(e_orientation eorientation,int64_t l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline int64_t set_normal_dimension(e_orientation eorientation,int64_t l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline int64_t set_normal(e_orientation eorientation,int64_t l) throw() { return set_orthogonal_dimension(eorientation,l); }


};







/////////////////////////////////////////////////////////////////////////////
// pointd - A 2-D pointd, similar to Windows POINTD structure.

class CLASS_DECL_BASE pointd : public tagPOINTD
{
public:
// Constructors

   // create an uninitialized pointd
   pointd() throw();
   // create from two integers
   pointd(double initX, double initY) throw();
   // create from another pointd
   pointd(POINTD initPt) throw();
   pointd(const POINTD * pinitPt) throw();
   pointd(__point64 initPt) throw();
   pointd(const __point64 * pinitPt) throw();
   // create from a sized
   pointd(SIZED initSize) throw();
   // create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
   pointd(LPARAM dwPoint) throw();


   operator POINTD *() throw();
   operator const POINTD *() const throw();

// Operations

// translate the pointd
   void offset(int32_t xOffset, int32_t yOffset) throw();
   void offset(POINTD pointd) throw();
   void offset(SIZED sized) throw();
   void SetPoint(int32_t X, int32_t Y) throw();

   bool operator==(POINTD pointd) const throw();
   bool operator!=(POINTD pointd) const throw();
   void operator+=(SIZED sized) throw();
   void operator-=(SIZED sized) throw();
   void operator+=(POINTD pointd) throw();
   void operator-=(POINTD pointd) throw();

// Operators returning pointd values
   pointd operator+(SIZED sized) const throw();
   pointd operator-(SIZED sized) const throw();
   pointd operator-() const throw();
   pointd operator+(POINTD pointd) const throw();

// Operators returning sized values
   sized operator-(POINTD pointd) const throw();

// Operators returning rectd values
   rectd operator+(LPCRECTD lpRect) const throw();
   rectd operator-(LPCRECTD lpRect) const throw();

   uint32_t ui32() const throw();
   uint64_t ui64() const throw();
   LPARAM   lparam() const throw();

   inline double get_dimension(e_orientation eorientation) const throw();
   inline double get_orthogonal_dimension(e_orientation eorientation) const throw();
   inline double get_orthogonal(e_orientation eorientation)const throw() { return get_orthogonal_dimension(eorientation); }
   inline double get_normal_dimension(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); }
   inline double get_normal(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); }

   inline double set_dimension(e_orientation eorientation,double l) throw();
   inline double set_orthogonal_dimension(e_orientation eorientation,double l) throw();
   inline double set_orthogonal(e_orientation eorientation,double l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline double set_normal_dimension(e_orientation eorientation,double l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline double set_normal(e_orientation eorientation,double l) throw() { return set_orthogonal_dimension(eorientation,l); }

};


inline pointd null_pointd() { return pointd(0.0, 0.0); }



inline LONG point::get_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return x;
   }
   else if(eorientation == orientation_vertical)
   {
      return y;
   }
   else
   {
      return 0;
   }
}


inline LONG point::get_orthogonal_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return y;
   }
   else if(eorientation == orientation_vertical)
   {
      return x;
   }
   else
   {
      return 0;
   }
}


inline LONG point::set_dimension(e_orientation eorientation,LONG l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return x = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return y = l;
   }
   else
   {
      return 0;
   }
}


inline LONG point::set_orthogonal_dimension(e_orientation eorientation,LONG l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return y = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return x = l;
   }
   else
   {
      return 0;
   }
}



inline int64_t point64::get_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return x;
   }
   else if(eorientation == orientation_vertical)
   {
      return y;
   }
   else
   {
      return 0;
   }
}


inline int64_t point64::get_orthogonal_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return y;
   }
   else if(eorientation == orientation_vertical)
   {
      return x;
   }
   else
   {
      return 0;
   }
}


inline int64_t point64::set_dimension(e_orientation eorientation,int64_t l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return x = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return y = l;
   }
   else
   {
      return 0;
   }
}


inline int64_t point64::set_orthogonal_dimension(e_orientation eorientation,int64_t l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return y = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return x = l;
   }
   else
   {
      return 0;
   }
}


inline double pointd::get_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return x;
   }
   else if(eorientation == orientation_vertical)
   {
      return y;
   }
   else
   {
      return 0;
   }
}


inline double pointd::get_orthogonal_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return y;
   }
   else if(eorientation == orientation_vertical)
   {
      return x;
   }
   else
   {
      return 0;
   }
}


inline double pointd::set_dimension(e_orientation eorientation,double l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return x = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return y = l;
   }
   else
   {
      return 0;
   }
}


inline double pointd::set_orthogonal_dimension(e_orientation eorientation,double l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return y = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return x = l;
   }
   else
   {
      return 0;
   }
}