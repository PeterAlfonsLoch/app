#pragma once


class verisimple_wstring;


typedef stdstring < verisimple_wstring > wstring;


CLASS_DECL_AURA verisimple_wstring operator + (const verisimple_wstring & wstr1, const verisimple_wstring & wstr2);
CLASS_DECL_AURA verisimple_wstring operator + (const verisimple_wstring & str, const wchar_t * psz);
CLASS_DECL_AURA verisimple_wstring operator + (const wchar_t * psz, const verisimple_wstring & str);


CLASS_DECL_AURA wstring gen_utf8_to_16(const char * psz);


class CLASS_DECL_AURA wstring_data
{
protected:


   friend class verisimple_wstring;
   friend class wtostring;


   static wchar_t * get_nil();


public:


   ::count m_iAllocation; // in chars "with NULL characters"
   ::count m_iLength; // in chars without NULL character
   wchar_t        m_wchFirst;


   // nil constructor
   inline wstring_data()
   {
      m_iAllocation  = 0;
      m_iLength      = 0;
      m_wchFirst     = L'\0';
   }


   inline static wchar_t * alloc(::count iCount)
   {

      wstring_data * pdata = (wstring_data *) memory_alloc(((iCount + 1) * sizeof(wchar_t)) + sizeof(count) + sizeof(count) + sizeof(wchar_t));
      pdata->m_iAllocation = iCount;
      pdata->m_iLength = 0;
      pdata->m_wchFirst = L'\0';
      return &pdata->m_wchFirst;

   }

   inline static void free(wchar_t * pwsz)
   {
      if(pwsz == NULL)
         return;
      wstring_data * pdata = (wstring_data *) (((byte *) pwsz) - sizeof(count) - sizeof(count));
      if(pdata->m_iAllocation <= 0)
         return;
      memory_free(pdata);

   }


   inline operator const wchar_t * () const { return &m_wchFirst; }
   inline operator wchar_t * () { return &m_wchFirst; }


};


class wstring_manager;


class CLASS_DECL_AURA verisimple_wstring
{
protected:

   typedef wstring_manager manager;
   typedef wchar_t value_type;


   friend class wtostring;

   // it is and should be really a pointer to the m_pwsz of a wstring_data alloced in heap
   // better always use wstring_data::alloc and wstring_data::free
   wchar_t * m_pwsz;

   inline wstring_data * get_data()
   {
      return (wstring_data *)(((byte *) m_pwsz) - sizeof(count) - sizeof(count));
   }

   inline const wstring_data * get_data() const
   {
      return (wstring_data *)(((byte *) m_pwsz) - sizeof(count) - sizeof(count));
   }

public:

   verisimple_wstring(manager * pstringmanager);
   void construct(manager * pstringmanager = NULL);
   verisimple_wstring(const verisimple_wstring & strSrc,manager * pstringmanager = NULL);
   verisimple_wstring(const char * pszSrc,manager * pstringmanager = NULL);
   verisimple_wstring(const byte * pszSrc,manager * pstringmanager = NULL);
   verisimple_wstring(const wchar_t * pchSrc, manager * pstringmanager = NULL);
   verisimple_wstring(const wchar_t * pchSrc, strsize nLength,manager * pstringmanager = NULL);
   inline verisimple_wstring(wstring_data * pdata,manager * pstringmanager = NULL)
   {
      UNREFERENCED_PARAMETER(pstringmanager);
      m_pwsz = &pdata->m_wchFirst;
   }
   ~verisimple_wstring();


   inline void attach(wstring_data * pdata)
   {
      if(m_pwsz != NULL)
      {
         wstring_data::free(m_pwsz);
      }
      m_pwsz = &pdata->m_wchFirst;
   }

   inline wstring_data * detach()
   {
      wstring_data * pdata = get_data();
      m_pwsz = wstring_data::get_nil();
      return pdata;
   }


   verisimple_wstring & operator = (const verisimple_wstring & wstr);
   verisimple_wstring & operator = (const wchar_t * pwsz);
   verisimple_wstring & operator = (const char * psz);


   inline operator const wchar_t * () const { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }
   inline operator const wchar_t * () { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }

   inline operator wchar_t * () const { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }
   inline operator wchar_t * () { return get_data()->m_iAllocation <= 0 ? NULL : m_pwsz; }


   inline const wchar_t * c_str() const { return this->operator const wchar_t *();  }

#if defined(METROWIN) && defined(__cplusplus_winrt)
   inline operator Platform::String ^ () const { return ref new Platform::String(operator const wchar_t *()); }
   inline operator Platform::String ^ () { return ref new Platform::String(operator const wchar_t *()); }
#endif


   inline wchar_t operator [] (index iIndex) const
   {
      return m_pwsz[iIndex];
   }

   inline wchar_t & operator [] (index iIndex)
   {
      return m_pwsz[iIndex];
   }

   wchar_t * alloc(::count iCount);

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

   inline bool operator == (const wchar_t * pwsz) const
   {
      return Compare(pwsz) == 0;
   }

   inline bool operator == (const wstring & wstr) const
   {
      return Compare(wstr) == 0;
   }

   inline int32_t Compare(const wchar_t * psz) const
   {
      return wcscmp_dup(m_pwsz, psz);
   }

   inline int32_t Compare(const verisimple_wstring &str) const
   {
      return wcscmp_dup(m_pwsz, str);
   }

   inline int32_t CompareNoCase(const wchar_t * psz) const
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
      return L"";
   }

   inline verisimple_wstring & append(wchar_t wch)
   {
      
      wchar_t wsz[2];
      
      wsz[0] = wch;
      
      wsz[1] = L'\0';
      
      return *this = (*this + wsz);

   }

   inline verisimple_wstring & append(wchar_t wch, ::count c)
   {

      while(c > 0)
      {

         append(wch);

         c--;

      }

      return *this;

   }

   verisimple_wstring substr(::index iStart, ::count c = -1);
   verisimple_wstring & replace(::index iStart,::count c, const wchar_t * psz);

};



