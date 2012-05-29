#pragma once


class CLASS_DECL_ca dump_context : 
   virtual public ::ca::ca
{
public:
   dump_context(ex1::file * pFile = NULL);

// Attributes
   int GetDepth() const;      // 0 => this object, 1 => children objects
   void SetDepth(int nNewDepth);

// Operations
   dump_context& operator<<(const char * lpsz);
   dump_context& operator<<(const wchar_t * lpsz); // automatically thinned
   dump_context& operator<<(const string & str);
   dump_context& operator<<(const void * lp);
   dump_context& operator<<(const ::radix::object* pOb);
   dump_context& operator<<(const ::radix::object& ob);
   dump_context& operator<<(BYTE by);
   dump_context& operator<<(WORD w);
   dump_context& dumpAsHex(BYTE b);
   dump_context& dumpAsHex(WORD w);
#if defined(_LP64)
   dump_context& operator<<(int_ptr i);
   dump_context& operator<<(uint_ptr ui);
   dump_context& operator<<(long_ptr l);
   dump_context& operator<<(dword_ptr dw);
   dump_context& operator<<(int n);
#if !defined(MACOS)
   dump_context& operator<<(UINT u);
#endif
   dump_context& dumpAsHex(int_ptr i);
   dump_context& dumpAsHex(long_ptr l);
   dump_context& dumpAsHex(dword_ptr dw);
   dump_context& dumpAsHex(int n);
#if !defined(MACOS)
   dump_context& dumpAsHex(UINT u);
#endif
#elif defined(_WIN64)
   dump_context& operator<<(LONG l);
   dump_context& operator<<(DWORD dw);
   dump_context& operator<<(int n);
   dump_context& operator<<(UINT u);
   dump_context& dumpAsHex(LONG l);
   dump_context& dumpAsHex(DWORD dw);
   dump_context& dumpAsHex(int n);
   dump_context& dumpAsHex(UINT u);
#else
#ifdef WINDOWS
   dump_context& operator<<(long_ptr l);
   dump_context& operator<<(dword_ptr dw);
#endif
   dump_context& operator<<(int_ptr n);
   dump_context& operator<<(uint_ptr u);
#ifdef WINDOWS
   dump_context& dumpAsHex(long_ptr l);
   dump_context& dumpAsHex(dword_ptr dw);
#endif
   dump_context& dumpAsHex(int_ptr n);
   dump_context& dumpAsHex(uint_ptr u);
#endif
   dump_context& operator<<(float f);
   dump_context& operator<<(double d);
#ifdef WINDOWS
   dump_context& operator<<(LONGLONG n);
   dump_context& operator<<(ULONGLONG n);
   dump_context& dumpAsHex(LONGLONG n);
   dump_context& dumpAsHex(ULONGLONG n);
#endif
   dump_context& operator<<(HWND h);
   dump_context& operator<<(HDC h);
#ifdef WINDOWS
   dump_context& operator<<(HMENU h);
   dump_context& operator<<(HACCEL h);
#endif
   dump_context& operator<<(HFONT h);
   void Hexdump(const char * lpszLine, BYTE* pby, int nBytes, int nWidth);
   void Flush();

// Implementation
protected:
   // dump context objects cannot be copied or assigned
   dump_context(const dump_context& graphicsSrc);
   void operator=(const dump_context& graphicsSrc);
   void OutputString(const char * lpsz);

   int m_nDepth;

public:
   ex1::file * m_pFile;
};

