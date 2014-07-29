#pragma once


/////////////////////////////////////////////////////////////////////////////
// size - An extent, similar to Windows SIZE structure.

class CLASS_DECL_BASE size : public tagSIZE
{
public:

// Constructors
   // construct an uninitialized size
   size() throw();
   // create from two integers
   size(int64_t initCX, int64_t initCY) throw();
   // create from another size
   size(const SIZE * pinitSize) throw();
   size(SIZE initSize) throw();
   size(__size64 initSize) throw();
   size(const __size64 * pinitSize) throw();
   // create from a point
   size(POINT initPt) throw();
   // create from a uint32_t: cx = LOWORD(dw) cy = HIWORD(dw)
   size(uint32_t dwSize) throw();

   operator SIZE *() throw();
   operator const SIZE *() const throw();


// Operations
   bool operator==(SIZE size) const throw();
   bool operator!=(SIZE size) const throw();
   void operator+=(SIZE size) throw();
   void operator-=(SIZE size) throw();
   void set_size(int32_t CX, int32_t CY) throw();

// Operators returning size values
   size operator+(SIZE size) const throw();
   size operator-(SIZE size) const throw();
   size operator-() const throw();

// Operators returning point values
   point operator+(POINT point) const throw();
   point operator-(POINT point) const throw();

// Operators returning rect values
   rect operator+(LPCRECT lpRect) const throw();
   rect operator-(LPCRECT lpRect) const throw();

   int64_t area() const throw();
   inline bool is_empty() const throw();

   uint32_t    ui32() const throw();
   uint64_t    ui64() const throw();
   LPARAM    lparam() const throw();
   POINT &        pt() throw() { return (POINT &)*this; }
   const POINT &  pt() const throw() { return (const POINT &)*this; }

   inline LONG get_dimension(e_orientation eorientation) const throw();
   inline LONG get_orthogonal_dimension(e_orientation eorientation) const throw();
   inline LONG get_orthogonal(e_orientation eorientation)const throw() { return get_orthogonal_dimension(eorientation); } 
   inline LONG get_normal_dimension(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); } 
   inline LONG get_normal(e_orientation eorientation) const throw(){ return get_orthogonal_dimension(eorientation); } 

   inline LONG set_dimension(e_orientation eorientation, LONG l) throw();
   inline LONG set_orthogonal_dimension(e_orientation eorientation, LONG l) throw();
   inline LONG set_orthogonal(e_orientation eorientation,LONG l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal_dimension(e_orientation eorientation,LONG l)  throw(){ return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal(e_orientation eorientation,LONG l) throw() { return set_orthogonal_dimension(eorientation,l); } 

};


inline bool size::is_empty() const throw()
{
   return cx <= 0 || cy <= 0;
}

/////////////////////////////////////////////////////////////////////////////
// size64 - An extent, similar to Windows SIZE structure.

class CLASS_DECL_BASE size64 : public __size64
{
public:

// Constructors
   // construct an uninitialized size64
   size64() throw();
   // create from two integers
   size64(int64_t initCX, int64_t initCY) throw();
   // create from another size64
   size64(__size64 initSize) throw();
   size64(const __size64 *pinitSize) throw();
   // create from a point
   size64(__point64 initPt) throw();
   // create from a uint32_t: cx = LODWORD(dw) cy = HIDWORD(dw)
   size64(uint64_t dwSize) throw();


   operator __size64 *() throw();
   operator const __size64 *() const throw();

// Operations
   bool operator==(__size64 size64) const throw();
   bool operator!=(__size64 size64) const throw();
   void operator+=(__size64 size64) throw();
   void operator-=(__size64 size64) throw();
   void set_size(int64_t CX, int64_t CY) throw();

// Operators returning size64 values
   size64 operator+(__size64 size64) const throw();
   size64 operator-(__size64 size64) const throw();
   size64 operator-() const throw();

// Operators returning point values
   point64 operator+(__point64 point) const throw();
   point64 operator-(__point64 point) const throw();

// Operators returning rect values
   rect64 operator+(const __rect64 * lpRect) const throw();
   rect64 operator-(const __rect64 * lpRect) const throw();

   int64_t area() const throw();
   inline bool is_empty() const throw();

   uint32_t    ui32() const throw();
   uint64_t    ui64() const throw();
   LPARAM    lparam() const throw();


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


inline bool size64::is_empty() const throw()
{
   return cx <= 0 || cy <= 0;
}


/////////////////////////////////////////////////////////////////////////////
// sized - An extent, similar to Windows SIZE structure.

class CLASS_DECL_BASE sized : public tagSIZED
{
public:

// Constructors
   // construct an uninitialized sized
   sized() throw();
   // create from two integers
   sized(double initCX, double initCY) throw();
   // create from another sized
   sized(const SIZED * pinitSize) throw();
   sized(SIZED initSize) throw();
   sized(__size64 initSize) throw();
   sized(const __size64 * pinitSize) throw();
   // create from a pointd
   sized(POINT initPt) throw();
   // create from a uint32_t: cx = LOWORD(dw) cy = HIWORD(dw)
   sized(uint32_t dwSize) throw();

   operator SIZED *() throw();
   operator const SIZED *() const throw();

// Operations
   bool operator==(SIZED size) const throw();
   bool operator!=(SIZED size) const throw();
   void operator+=(SIZED size) throw();
   void operator-=(SIZED size) throw();
   void set_size(int32_t CX, int32_t CY) throw();

// Operators returning sized values
   sized operator+(SIZED size) const throw();
   sized operator-(SIZED size) const throw();
   sized operator-() const throw();

// Operators returning pointd values
   pointd operator+(POINTD point) const throw();
   pointd operator-(POINTD point) const throw();

// Operators returning rectd values
   rectd operator+(LPCRECTD lpRect) const throw();
   rectd operator-(LPCRECTD lpRect) const throw();

   double area() const throw();
   inline bool is_empty() const throw();

   uint32_t    ui32() const throw();
   uint64_t    ui64() const throw();
   LPARAM    lparam() const throw();


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


inline bool sized::is_empty() const throw()
{
   return cx <= 0 || cy <= 0;
}



inline LONG size::get_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cx;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy;
   }
   else
   {
      return 0;
   }
}


inline LONG size::get_orthogonal_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cy;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx;
   }
   else
   {
      return 0;
   }
}


inline LONG size::set_dimension(e_orientation eorientation, LONG l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cx = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy = l;
   }
   else
   {
      return 0;
   }
}


inline LONG size::set_orthogonal_dimension(e_orientation eorientation, LONG l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cy = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx = l;
   }
   else
   {
      return 0;
   }
}



inline int64_t size64::get_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cx;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy;
   }
   else
   {
      return 0;
   }
}


inline int64_t size64::get_orthogonal_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cy;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx;
   }
   else
   {
      return 0;
   }
}


inline int64_t size64::set_dimension(e_orientation eorientation,int64_t l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cx = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy = l;
   }
   else
   {
      return 0;
   }
}


inline int64_t size64::set_orthogonal_dimension(e_orientation eorientation,int64_t l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cy = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx = l;
   }
   else
   {
      return 0;
   }
}


inline double sized::get_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cx;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy;
   }
   else
   {
      return 0;
   }
}


inline double sized::get_orthogonal_dimension(e_orientation eorientation) const throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cy;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx;
   }
   else
   {
      return 0;
   }
}


inline double sized::set_dimension(e_orientation eorientation,double l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cx = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy = l;
   }
   else
   {
      return 0;
   }
}


inline double sized::set_orthogonal_dimension(e_orientation eorientation,double l) throw()
{
   if(eorientation == orientation_horizontal)
   {
      return cy = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx = l;
   }
   else
   {
      return 0;
   }
}