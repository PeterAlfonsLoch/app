#pragma once


class CLASS_DECL_ca dump_context :
   virtual public ::ca::ca
{
public:
   dump_context(::ca::file * pFile = NULL);

// Attributes
   int32_t GetDepth() const;      // 0 => this object, 1 => children objects
   void SetDepth(int32_t nNewDepth);

// Operations
   dump_context & operator<<(const char * lpsz);
   dump_context & operator<<(const wchar_t * lpsz); // automatically thinned
   dump_context & operator<<(const string & str);
   dump_context & operator<<(const void * lp);
   dump_context & operator<<(const ::ca::object* pOb);
   dump_context & operator<<(const ::ca::object& ob);
   dump_context & operator<<(int8_t i);
   dump_context & operator<<(uint8_t ui);
   dump_context & operator<<(int16_t i);
   dump_context & operator<<(uint16_t ui);
   dump_context & operator<<(int32_t i);
   dump_context & operator<<(uint32_t ui);
   dump_context & operator<<(int64_t i);
   dump_context & operator<<(uint64_t ui);
   dump_context & hex_dump(int8_t i);
   dump_context & hex_dump(uint8_t i);
   dump_context & hex_dump(int16_t i);
   dump_context & hex_dump(uint16_t i);
   dump_context & hex_dump(int32_t i);
   dump_context & hex_dump(uint32_t i);
   dump_context & hex_dump(int64_t i);
   dump_context & hex_dump(uint64_t i);
   dump_context & operator<<(float f);
   dump_context & operator<<(double d);
   dump_context & operator<<(oswindow h);
   dump_context & operator<<(HDC h);

#ifdef WINDOWS
   dump_context & operator<<(HMENU h);
   dump_context & operator<<(HACCEL h);
   dump_context & operator<<(HFONT h);
#endif

   void hex_dump(const char * lpszLine, BYTE* pby, int32_t nBytes, int32_t nWidth);
   void flush();

// Implementation
protected:
   // dump context objects cannot be copied or assigned
   dump_context(const dump_context & graphicsSrc);
   void operator=(const dump_context & graphicsSrc);
   void output_string(const char * lpsz);

   int32_t m_nDepth;

public:
   ::ca::file * m_pfile;
};

