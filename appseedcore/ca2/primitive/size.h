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

   operator SIZE *();
   operator const SIZE *() const;

// Operations
   BOOL operator==(SIZE size) const throw();
   BOOL operator!=(SIZE size) const throw();
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
   rect operator+(const RECT* lpRect) const throw();
   rect operator-(const RECT* lpRect) const throw();

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
   size64(unsigned __int64 dwSize) throw();


   operator __size64 *();
   operator const __size64 *() const;

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
