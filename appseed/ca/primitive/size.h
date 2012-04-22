#pragma once


/////////////////////////////////////////////////////////////////////////////
// size - An extent, similar to Windows SIZE structure.

class CLASS_DECL_ca size : public tagSIZE
{
public:

// Constructors
   // construct an uninitialized size
   size() throw();
   // create from two integers
   size(__int64 initCX, __int64 initCY) throw();
   // create from another size
   size(const SIZE * pinitSize) throw();
   size(SIZE initSize) throw();
   size(__size64 initSize) throw();
   size(const __size64 * pinitSize) throw();
   // create from a point
   size(POINT initPt) throw();
   // create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
   size(DWORD dwSize) throw();

   operator SIZE *() throw();
   operator const SIZE *() const throw();

// Operations
   bool operator==(SIZE size) const throw();
   bool operator!=(SIZE size) const throw();
   void operator+=(SIZE size) throw();
   void operator-=(SIZE size) throw();
   void set_size(int CX, int CY) throw();

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

   __int64 area();
   inline bool is_empty() const throw();
};


inline bool size::is_empty() const throw()
{
   return cx <= 0 || cy <= 0;
}

/////////////////////////////////////////////////////////////////////////////
// size64 - An extent, similar to Windows SIZE structure.

class CLASS_DECL_ca size64 : public __size64
{
public:

// Constructors
   // construct an uninitialized size64
   size64() throw();
   // create from two integers
   size64(__int64 initCX, __int64 initCY) throw();
   // create from another size64
   size64(__size64 initSize) throw();
   size64(const __size64 *pinitSize) throw();
   // create from a point
   size64(__point64 initPt) throw();
   // create from a DWORD: cx = LODWORD(dw) cy = HIDWORD(dw)
   size64(__uint64_t dwSize) throw();


   operator __size64 *() throw();
   operator const __size64 *() const throw();

// Operations
   BOOL operator==(__size64 size64) const throw();
   BOOL operator!=(__size64 size64) const throw();
   void operator+=(__size64 size64) throw();
   void operator-=(__size64 size64) throw();
   void set_size(__int64 CX, __int64 CY) throw();

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

   __int64 area();
   inline bool is_empty() const throw();
};


inline bool size64::is_empty() const throw()
{
   return cx <= 0 || cy <= 0;
}




/////////////////////////////////////////////////////////////////////////////
// sized - An extent, similar to Windows SIZE structure.

class CLASS_DECL_ca sized : public tagSIZED
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
   // create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
   sized(DWORD dwSize) throw();

   operator SIZED *() throw();
   operator const SIZED *() const throw();

// Operations
   bool operator==(SIZED size) const throw();
   bool operator!=(SIZED size) const throw();
   void operator+=(SIZED size) throw();
   void operator-=(SIZED size) throw();
   void set_size(int CX, int CY) throw();

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

   double area();
   inline bool is_empty() const throw();
};


inline bool sized::is_empty() const throw()
{
   return cx <= 0 || cy <= 0;
}
