#pragma once



class CLASS_DECL_AXIS id
{
public:


   const string *       m_pstr;


   inline id();
   inline id(const id & id);
   id(const char * psz);
   id(int_ptr i);
   id(uint_ptr ui);
#if defined(_LP64) || defined(_AMD64_)
   id(int32_t i);
   id(uint32_t ui);
#endif
   id(const string & str);
   id(const string_interface & str);
   id(const var & var);


   void raw_set(const string * pstr);


   string str() const;


   inline bool operator == (const id & id) const;
   inline bool operator != (const id & id) const;
   inline bool operator < (const id & id) const;
   inline bool operator <= (const id & id) const;
   inline bool operator > (const id & id) const;
   inline bool operator >= (const id & id) const;
   inline id & operator = (const id & id);


   inline bool operator == (const char * psz) const;
   inline bool operator != (const char * psz) const;
   inline bool operator < (const char * psz) const;
   inline bool operator <= (const char * psz) const;
   inline bool operator > (const char * psz) const;
   inline bool operator >= (const char * psz) const;
   id & operator = (const char * psz);


   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;
   id & operator = (const string & str);


   inline bool operator == (int_ptr i) const;
   inline bool operator != (int_ptr i) const;
   inline bool operator < (int_ptr i) const;
   inline bool operator <= (int_ptr i) const;
   inline bool operator > (int_ptr i) const;
   inline bool operator >= (int_ptr i) const;
   inline id & operator = (int_ptr i);


#if defined(_LP64) || defined(_AMD64_)


   inline bool operator == (int32_t i) const;
   inline bool operator != (int32_t i) const;
   inline bool operator < (int32_t i) const;
   inline bool operator <= (int32_t i) const;
   inline bool operator > (int32_t i) const;
   inline bool operator >= (int32_t i) const;
   inline id & operator = (int32_t i);


#endif


   inline bool operator == (const string_interface & str) const;
   inline bool operator != (const string_interface & str) const;
   inline bool operator < (const string_interface & str) const;
   inline bool operator <= (const string_interface & str) const;
   inline bool operator > (const string_interface & str) const;
   inline bool operator >= (const string_interface & str) const;

   id & operator = (const string_interface & str);
   id & operator = (const var & var);
   id & operator = (const property & prop);


   inline operator int64_t() const;


   inline operator const char *() const;
   inline string to_string() const;



   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline void Empty();
   inline void clear();


   inline int_ptr CompareNoCase(const char * psz) { return compare_ci(psz); }
   inline int_ptr compare_ci(const char * psz);

};




inline id::id()
{

   m_pstr = NULL;

}

inline id::id(const id & id)
{
   m_pstr = id.m_pstr;
}

inline bool id::operator == (const id & id) const
{
   return m_pstr == id.m_pstr;
}

inline bool id::operator != (const id & id) const
{
   return ! operator == (id);
}

inline bool id::operator < (const id & id) const
{
   return m_pstr < id.m_pstr;
}
inline bool id::operator <= (const id & id) const
{
   return m_pstr <= id.m_pstr;
}
inline bool id::operator > (const id & id) const
{
   return m_pstr > id.m_pstr;
}
inline bool id::operator >= (const id & id) const
{
   return m_pstr >= id.m_pstr;
}

inline id & id::operator = (const id & id)
{
   m_pstr         = id.m_pstr;
   return *this;
}





