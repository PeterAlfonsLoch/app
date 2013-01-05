#include "framework.h"


#ifdef LINUX

inline int32_t _stprintf_s(char * pszBuffer, int32_t iBufferLen, const char * pszFormat, ...)
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

int32_t dump_context::GetDepth() const
{
   return m_nDepth;
}

void dump_context::SetDepth(int32_t nNewDepth)
{
   m_nDepth = nNewDepth;
}

void dump_context::output_string(const char * lpsz)
{
   // use C-runtime/OutputDebugString when m_pfile is NULL
   if (m_pfile == NULL)
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
   m_pfile->write(lpsz, lstrlen(lpsz)*sizeof(char));
#else
   m_pfile->write(lpsz, strlen(lpsz)*sizeof(char));
#endif
}

dump_context::dump_context(ex1::file * pFile)
{
   if (pFile)
      ASSERT_VALID(pFile);

   m_pfile = pFile;
   m_nDepth = 0;
}

void dump_context::flush()
{
   if (m_pfile)
      m_pfile->flush();
}

dump_context & dump_context::operator<<(const char * lpsz)
{
   if (lpsz == NULL)
   {
      output_string("NULL");
      return *this;
   }

   ASSERT( lpsz != NULL );
   if( lpsz == NULL )
      throw user_exception(get_app());

   if (m_pfile == NULL)
   {
      char szBuffer[512];
      LPSTR lpBuf = szBuffer;
      while (*lpsz != '\0')
      {
         if (lpBuf > szBuffer + _countof(szBuffer) - 3)
         {
            *lpBuf = '\0';
            output_string(szBuffer);
            lpBuf = szBuffer;
         }
         if (*lpsz == '\n')
            *lpBuf++ = '\r';
         *lpBuf++ = *lpsz++;
      }
      *lpBuf = '\0';
      output_string(szBuffer);
      return *this;
   }

   m_pfile->write(lpsz, strlen(lpsz)*sizeof(char));
   return *this;
}

dump_context & dump_context::operator<<(BYTE by)
{

   string str;

   str.Format("%d", (uint32_t)by);

   output_string(str);

   return *this;

}

dump_context & dump_context::hex_dump(BYTE b)
{

   string str;

   str.Format("0x%02x", (uint32_t)b);

   output_string(str);

   return *this;

}

dump_context & dump_context::operator<<(WORD w)
{

   string str;

   str.Format("%u", (UINT) w);

   output_string(str);

   return *this;

}

dump_context & dump_context::hex_dump(WORD w)
{

   string str;

   str.Format("0x%04x", (uint32_t) w);

   output_string(str);

   return *this;

}


#if defined(LINUX)

dump_context & dump_context::operator<<(uint32_t ui)
{

   string str;

   str.Format("%u", ui);

   output_string(str);

   return *this;

}

#endif


#if defined(_WIN64) && !defined(_LP64)
dump_context & dump_context::operator<<(UINT u)
#else
dump_context & dump_context::operator<<(uint_ptr u)
#endif
{

   string str;

   str.Format("%u", u);

   output_string(str);

   return *this;

}

#ifdef _WIN64
dump_context & dump_context::operator<<(LONG l)
#else
dump_context & dump_context::operator<<(int_ptr l)
#endif
{

   string str;

   str.Format("%d", l);

   output_string(str);

   return *this;

}

#if !defined(_LP64)

#ifdef _WIN64
dump_context & dump_context::operator<<(uint32_t dw)
#else
dump_context & dump_context::operator<<(uint_ptr dw)
#endif
{

   string str;

   str.Format("%u", dw);

   output_string(str);

   return *this;

}

#endif

#if defined(_WIN64) && !defined(LINUX) && !defined(_LP64)
dump_context & dump_context::operator<<(int32_t n)
#else
dump_context & dump_context::operator<<(int_ptr n)
#endif
{

   string str;

   str.Format("%d", n);

   output_string(str);

   return *this;

}

#if !defined(_LP64)

#ifdef _WIN64
dump_context & dump_context::hex_dump(UINT u)
#else
dump_context & dump_context::hex_dump(uint_ptr u)
#endif
{

   string str;

   str.Format("0x%08x", u);

   output_string(str);

   return *this;
}

#endif

#ifdef _WIN64
dump_context & dump_context::hex_dump(LONG l)
#else
dump_context & dump_context::hex_dump(int_ptr l)
#endif
{

   string str;

   str.Format("0x%08x", l);

   output_string(str);

   return *this;

}

#if defined(_WIN64) && !defined(_LP64)
dump_context & dump_context::hex_dump(uint32_t dw)
#else
dump_context & dump_context::hex_dump(uint_ptr dw)
#endif
{

   string str;

   str.Format("0x%08x", dw);

   output_string(str);

   return *this;

}

#if defined(_WIN64) && !defined(LINUX) && !defined(_LP64)
dump_context & dump_context::hex_dump(int32_t n)
#else
dump_context & dump_context::hex_dump(int_ptr n)
#endif
{

   string str;

   str.Format("0x%08x", n);

   output_string(str);

   return *this;

}

#if !defined(_LP64)

dump_context & dump_context::operator<<(LONGLONG n)
{

   string str;

   str.Format("%I64d", n);

   output_string(str);

   return *this;

}

dump_context & dump_context::operator<<(ULONGLONG n)
{

   string str;

   str.Format("%I64u", n);

   output_string(str);

   return *this;

}

dump_context & dump_context::hex_dump(LONGLONG n)
{

   string str;

   str.Format("0x%016I64x", n);

   output_string(str);

   return *this;

}

dump_context & dump_context::hex_dump(ULONGLONG n)
{

   string str;

   str.Format("0x%016I64x", n);

   output_string(str);

   return *this;

}

#endif

dump_context & dump_context::operator<<(const ::radix::object* pOb)
{

   if (pOb == NULL)
      *this << "NULL";
   else
      pOb->dump(*this);

   return *this;

}

dump_context & dump_context::operator<<(const ::radix::object& ob)
{

   return *this << &ob;

}

dump_context & dump_context::operator<<(const void * lp)
{

   string str;

   // prefix a pointer with "$" and print in hex
   str.Format("$%p", lp);

   output_string(str);

   return *this;

}

dump_context & dump_context::operator<<(oswindow h)
{
   return *this << (void *)h;
}

dump_context & dump_context::operator<<(HDC h)
{
   return *this << (void *)h;
}


#ifdef WINDOWS


dump_context & dump_context::operator<<(HMENU h)
{
   return *this << (void *)h;
}

dump_context & dump_context::operator<<(HACCEL h)
{
   return *this << (void *)h;
}


#endif


dump_context & dump_context::operator<<(HFONT h)
{
   return *this << (void *)h;
}

/////////////////////////////////////////////////////////////////////////////
// Formatted output

void dump_context::hex_dump(const char * lpszLine, BYTE* pby, int32_t nBytes, int32_t nWidth)
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

   int32_t nRow = 0;
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

dump_context & dump_context::operator<<(const wchar_t * lpsz)
{

   if (lpsz == NULL)
   {
      output_string("(NULL)");
      return *this;
   }

   return *this << gen::international::unicode_to_utf8(lpsz);

}
