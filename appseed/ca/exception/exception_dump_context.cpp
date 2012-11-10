#include "framework.h"


#ifdef LINUX

inline int _stprintf_s(char * pszBuffer, int iBufferLen, const char * pszFormat, ...)
{

   UNREFERENCED_PARAMETER(iBufferLen);

   va_list args;

   va_start (args, pszFormat);

   vsprintf(pszBuffer, pszFormat, args);

   va_end (args);

}

inline size_t lstrlen(const char * psz)
{
   return strlen(psz);
}

#endif


dump_context::dump_context(const dump_context &)
{

}

void dump_context::operator = (const dump_context &)
{

}

int dump_context::GetDepth() const
{
   return m_nDepth;
}

void dump_context::SetDepth(int nNewDepth)
{
   m_nDepth = nNewDepth;
}

void dump_context::OutputString(const char * lpsz)
{
   // use C-runtime/OutputDebugString when m_pFile is NULL
   if (m_pFile == NULL)
   {
      ::OutputDebugStringW(gen::international::utf8_to_unicode(lpsz));
      //     TRACE(::radix::trace::category_dumpContext, 0, "%s", lpsz);
      return;
   }

   ASSERT( lpsz != NULL );
   if( lpsz == NULL )
      throw user_exception(get_app());
   // otherwise, write the string to the file
#ifdef WINDOWSEX
   m_pFile->write(lpsz, lstrlen(lpsz)*sizeof(char));
#else
   m_pFile->write(lpsz, strlen(lpsz)*sizeof(char));
#endif
}

dump_context::dump_context(ex1::file * pFile)
{
   if (pFile)
      ASSERT_VALID(pFile);

   m_pFile = pFile;
   m_nDepth = 0;
}

void dump_context::Flush()
{
   if (m_pFile)
      m_pFile->Flush();
}

dump_context& dump_context::operator<<(const char * lpsz)
{
   if (lpsz == NULL)
   {
      OutputString("NULL");
      return *this;
   }

   ASSERT( lpsz != NULL );
   if( lpsz == NULL )
      throw user_exception(get_app());

   if (m_pFile == NULL)
   {
      char szBuffer[512];
      LPSTR lpBuf = szBuffer;
      while (*lpsz != '\0')
      {
         if (lpBuf > szBuffer + _countof(szBuffer) - 3)
         {
            *lpBuf = '\0';
            OutputString(szBuffer);
            lpBuf = szBuffer;
         }
         if (*lpsz == '\n')
            *lpBuf++ = '\r';
         *lpBuf++ = *lpsz++;
      }
      *lpBuf = '\0';
      OutputString(szBuffer);
      return *this;
   }

   m_pFile->write(lpsz, strlen(lpsz)*sizeof(char));
   return *this;
}

dump_context& dump_context::operator<<(BYTE by)
{

   string str;

   str.Format("%d", (DWORD)by);

   OutputString(str);

   return *this;

}

dump_context& dump_context::dumpAsHex(BYTE b)
{

   string str;

   str.Format("0x%02x", (DWORD)b);

   OutputString(str);

   return *this;

}

dump_context& dump_context::operator<<(WORD w)
{

   string str;

   str.Format("%u", (UINT) w);

   OutputString(str);

   return *this;

}

dump_context& dump_context::dumpAsHex(WORD w)
{

   string str;

   str.Format("0x%04x", (DWORD) w);

   OutputString(str);

   return *this;

}

#if defined(_WIN64) && !defined(_LP64)
dump_context& dump_context::operator<<(UINT u)
#else
dump_context& dump_context::operator<<(uint_ptr u)
#endif
{

   string str;

   str.Format("%u", u);

   OutputString(str);

   return *this;

}

#ifdef _WIN64
dump_context& dump_context::operator<<(LONG l)
#else
dump_context& dump_context::operator<<(long_ptr l)
#endif
{

   string str;

   str.Format("%d", l);

   OutputString(str);

   return *this;

}

#if !defined(_LP64)

#ifdef _WIN64
dump_context& dump_context::operator<<(DWORD dw)
#else
dump_context& dump_context::operator<<(dword_ptr dw)
#endif
{

   string str;

   str.Format("%u", dw);

   OutputString(str);

   return *this;

}

#endif

#if defined(_WIN64) && !defined(LINUX) && !defined(_LP64)
dump_context& dump_context::operator<<(int n)
#else
dump_context& dump_context::operator<<(int_ptr n)
#endif
{

   string str;

   str.Format("%d", n);

   OutputString(str);

   return *this;

}

#if !defined(_LP64)

#ifdef _WIN64
dump_context& dump_context::dumpAsHex(UINT u)
#else
dump_context& dump_context::dumpAsHex(uint_ptr u)
#endif
{

   string str;

   str.Format("0x%08x", u);

   OutputString(str);

   return *this;
}

#endif

#ifdef _WIN64
dump_context& dump_context::dumpAsHex(LONG l)
#else
dump_context& dump_context::dumpAsHex(long_ptr l)
#endif
{

   string str;

   str.Format("0x%08x", l);

   OutputString(str);

   return *this;

}

#if defined(_WIN64) && !defined(_LP64)
dump_context& dump_context::dumpAsHex(DWORD dw)
#else
dump_context& dump_context::dumpAsHex(dword_ptr dw)
#endif
{

   string str;

   str.Format("0x%08x", dw);

   OutputString(str);

   return *this;

}

#if defined(_WIN64) && !defined(LINUX) && !defined(_LP64)
dump_context& dump_context::dumpAsHex(int n)
#else
dump_context& dump_context::dumpAsHex(int_ptr n)
#endif
{

   string str;

   str.Format("0x%08x", n);

   OutputString(str);

   return *this;

}

#if !defined(_LP64)

dump_context& dump_context::operator<<(LONGLONG n)
{

   string str;

   str.Format("%I64d", n);

   OutputString(str);

   return *this;

}

dump_context& dump_context::operator<<(ULONGLONG n)
{

   string str;

   str.Format("%I64u", n);

   OutputString(str);

   return *this;

}

dump_context& dump_context::dumpAsHex(LONGLONG n)
{

   string str;

   str.Format("0x%016I64x", n);

   OutputString(str);

   return *this;

}

dump_context& dump_context::dumpAsHex(ULONGLONG n)
{

   string str;

   str.Format("0x%016I64x", n);

   OutputString(str);

   return *this;

}

#endif

dump_context& dump_context::operator<<(const ::radix::object* pOb)
{

   if (pOb == NULL)
      *this << "NULL";
   else
      pOb->dump(*this);

   return *this;

}

dump_context& dump_context::operator<<(const ::radix::object& ob)
{

   return *this << &ob;

}

dump_context& dump_context::operator<<(const void * lp)
{

   string str;

   // prefix a pointer with "$" and print in hex
   str.Format("$%p", lp);

   OutputString(str);

   return *this;

}

dump_context& dump_context::operator<<(oswindow h)
{
   return *this << (void *)h;
}

dump_context& dump_context::operator<<(HDC h)
{
   return *this << (void *)h;
}


#ifdef WINDOWS


dump_context& dump_context::operator<<(HMENU h)
{
   return *this << (void *)h;
}

dump_context& dump_context::operator<<(HACCEL h)
{
   return *this << (void *)h;
}


#endif


dump_context& dump_context::operator<<(HFONT h)
{
   return *this << (void *)h;
}

/////////////////////////////////////////////////////////////////////////////
// Formatted output

void dump_context::Hexdump(const char * lpszLine, BYTE* pby, int nBytes, int nWidth)
// do a simple hex-dump (8 per line) to a dump_context
//  the "lpszLine" is a string to print at the start of each line
//    (%lx should be used to expand the current address)
{
   ASSERT(nBytes > 0);
   if( nBytes <= 0 )
      throw invalid_argument_exception(get_app());
   ASSERT(nWidth > 0);
   if( nWidth <= 0 )
      throw invalid_argument_exception(get_app());
   ASSERT(__is_valid_string(lpszLine));
   if( lpszLine == NULL )
      throw invalid_argument_exception(get_app());
   ASSERT(__is_valid_address(pby, nBytes, FALSE));
   if( pby == NULL )
      throw invalid_argument_exception(get_app());

   int nRow = 0;
   string str;


   while (nBytes--)
   {

      if (nRow == 0)
      {
         str.Format(lpszLine, pby);
         *this << str;
      }

      str.Format(" %02X", *pby);
      *this << str;

      pby++;

      if (++nRow >= nWidth)
      {
         *this << "\n";
         nRow = 0;
      }
   }
   if (nRow != 0)
      *this << "\n";
}

dump_context& dump_context::operator<<(const wchar_t * lpsz)
{

   if (lpsz == NULL)
   {
      OutputString("(NULL)");
      return *this;
   }

   return *this << gen::international::unicode_to_utf8(lpsz);

}
