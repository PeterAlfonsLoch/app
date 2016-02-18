#pragma once


class verisimple_wstring;
class string;


typedef stdstring < verisimple_wstring > wstring;


CLASS_DECL_AURA verisimple_wstring operator + (const verisimple_wstring & wstr1, const verisimple_wstring & wstr2);
CLASS_DECL_AURA verisimple_wstring operator + (const verisimple_wstring & str, const unichar * psz);
CLASS_DECL_AURA verisimple_wstring operator + (const unichar * psz, const verisimple_wstring & str);


CLASS_DECL_AURA wstring gen_utf8_to_16(const char * psz);


class CLASS_DECL_AURA wstring_data
{
protected:


   friend class verisimple_wstring;
   friend class wtostring;


   static unichar * get_nil();


public:


   ::count m_iAllocation; // in chars "with NULL characters"
   ::count m_iLength; // in chars without NULL character
   unichar        m_wchFirst;


   // nil constructor
   inline wstring_data()
   {
      m_iAllocation  = 0;
      m_iLength      = 0;
      m_wchFirst     = L'\0';
   }

   inline wstring_data * clone() const
   {
      wstring_data * pdata = (wstring_data *) memory_alloc(((m_iAllocation + 1) * sizeof(unichar)) + sizeof(count) + sizeof(count) + sizeof(unichar));
      memcpy(pdata, this, ((m_iAllocation + 1) * sizeof(unichar)) + sizeof(count) + sizeof(count) + sizeof(unichar));
      return pdata;
   }


   inline static unichar * alloc(::count iCount)
   {

      wstring_data * pdata = (wstring_data *) memory_alloc(((iCount + 1) * sizeof(unichar)) + sizeof(count) + sizeof(count) + sizeof(unichar));
      pdata->m_iAllocation = iCount;
      pdata->m_iLength = 0;
      pdata->m_wchFirst = L'\0';
      return &pdata->m_wchFirst;

   }

   inline static void _free(unichar * pwsz)
   {
      if(pwsz == NULL)
         return;
      if (pwsz == get_nil())
         return;
      wstring_data * pdata = (wstring_data *) (((byte *) pwsz) - sizeof(count) - sizeof(count));
      if(pdata->m_iAllocation <= 0)
         return;
      ::memory_free(pdata);

   }


   inline operator const unichar * () const { return &m_wchFirst; }
   inline operator unichar * () { return &m_wchFirst; }


};


class wstring_manager;

#ifdef WINDOWS
#define unilen wcslen
#else
#define unilen wcslen_dup
#endif

class CLASS_DECL_AURA verisimple_wstring
{
public:

   static const int npos;
   typedef wstring_manager manager;
   typedef unichar value_type;
   typedef wstring_data data_type;


protected:



   friend class wtostring;

   // it is and should be really a pointer to the m_pwsz of a wstring_data alloced in heap
   // better always use wstring_data::alloc and wstring_data::free
   unichar * m_pwsz;

   inline wstring_data * get_data()
   {
      return (wstring_data *)(((byte *) m_pwsz) - sizeof(count) - sizeof(count));
   }

   inline const wstring_data * get_data() const
   {
      return (wstring_data *)(((byte *) m_pwsz) - sizeof(count) - sizeof(count));
   }

public:

   verisimple_wstring(for_moving){};
   verisimple_wstring(manager * pstringmanager);
   void construct(manager * pstringmanager = NULL);
   verisimple_wstring(const verisimple_wstring & strSrc,manager * pstringmanager = NULL);
   verisimple_wstring(const char * pszSrc,manager * pstringmanager = NULL);
   verisimple_wstring(const byte * pszSrc,manager * pstringmanager = NULL);
   verisimple_wstring(const unichar * pchSrc, manager * pstringmanager = NULL);
   verisimple_wstring(const unichar * pchSrc, strsize nLength,manager * pstringmanager = NULL);
   inline verisimple_wstring(const wstring_data * pdata,manager * pstringmanager = NULL)
   {
      UNREFERENCED_PARAMETER(pstringmanager);
      m_pwsz = (unichar *) &pdata->m_wchFirst;
   }
   ~verisimple_wstring();


   inline void attach(wstring_data * pdata)
   {
      if(m_pwsz != NULL)
      {
         wstring_data::_free(m_pwsz);
      }
      m_pwsz = &pdata->m_wchFirst;
   }

   inline wstring_data * detach()
   {
      wstring_data * pdata = get_data();
      m_pwsz = wstring_data::get_nil();
      return pdata;
   }


   void reserve(strsize n) { UNREFERENCED_PARAMETER(n); } // wstring does not prereserve

   verisimple_wstring & operator = (const verisimple_wstring & wstr);
   verisimple_wstring & operator = (const unichar * pwsz);
   verisimple_wstring & operator = (const char * psz);


   inline operator const unichar * () const { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }
   inline operator const unichar * () { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }

   inline operator unichar * () const { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }
   inline operator unichar * () { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }


   inline const unichar * c_str() const { return this->operator const unichar *();  }

#if defined(METROWIN) && defined(__cplusplus_winrt)
   inline operator String ^ () const { return ref new String(operator const unichar *()); }
   inline operator String ^ () { return ref new String(operator const unichar *()); }
#endif

   inline verisimple_wstring & operator += (unichar wch) { append(wch); return *this; }
   inline verisimple_wstring & operator += (const unichar * pwsz) { append(pwsz); return *this; }



   inline unichar operator [] (index iIndex) const
   {
      return m_pwsz[iIndex];
   }

   inline unichar & operator [] (index iIndex)
   {
      return m_pwsz[iIndex];
   }

   unichar * alloc(::count iCount);

   inline ::count get_length() const
   {
      return get_data()->m_iLength;
   }

   inline ::count length() const
   {
      return get_data()->m_iLength;
   }

   inline ::count size() const
   {
      return get_data()->m_iLength;
   }

   inline ::count storage_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline ::count allocation_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline ::count get_storage_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline ::count get_allocation_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline bool operator == (const unichar * pwsz) const
   {
      return Compare(pwsz) == 0;
   }

   inline bool operator == (const wstring & wstr) const
   {
      return Compare(wstr) == 0;
   }

   inline int32_t Compare(const unichar * psz) const
   {
      return wcscmp_dup(m_pwsz, psz);
   }

   inline int32_t Compare(const verisimple_wstring &str) const
   {
      return wcscmp_dup(m_pwsz, str);
   }

   inline int32_t CompareNoCase(const unichar * psz) const
   {
      return wcsicmp_dup(m_pwsz, psz);
   }

   inline int32_t CompareNoCase(const verisimple_wstring &str) const
   {
      return wcsicmp_dup(m_pwsz, str);
   }


   inline bool is_empty() const
   {
      return get_data()->m_iLength <= 0 || *m_pwsz == L'\0';
   }


   inline void set_length(::count iLength)
   {

      if(iLength <= get_data()->m_iAllocation)
      {
         get_data()->m_iLength = iLength;
      }
      else
      {
         get_data()->m_iLength = 0;
      }
      m_pwsz[iLength] = L'\0';
   }

   inline void release_buffer()
   {

      set_length(wcslen_dup(m_pwsz));

   }


   inline static verisimple_wstring empty_string()
   {
      unichar push[]={0};
      return push;
   }

   inline verisimple_wstring & append(unichar wch)
   {

      unichar wsz[2];

      wsz[0] = wch;

      wsz[1] = L'\0';

      return *this = (*this + wsz);

   }

   inline verisimple_wstring & append(unichar wch, ::count c)
   {

      while(c > 0)
      {

         append(wch);

         c--;

      }

      return *this;

   }

   inline verisimple_wstring & append(const unichar * pwsz) { assign(*this + pwsz); return *this; }

   verisimple_wstring substr(::index iStart, ::count c = -1);
   verisimple_wstring & replace(::index iStart,::count c, const unichar * psz);


   verisimple_wstring & operator = (const string & str);

   void assign(const unichar * pwsz);
   void assign(const char * psz);


   strsize find(unichar ch,strsize start = 0,strsize count = -1) const RELEASENOTHROW;
   strsize find(const unichar * pszSub,strsize start = 0,strsize count = -1,const unichar ** pszTail = NULL) const RELEASENOTHROW;

   bool empty() const { return is_empty();  }


};


