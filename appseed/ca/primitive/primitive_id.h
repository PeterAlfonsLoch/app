#pragma once



#define IDTYPE_TYPE_NULL 0
// is zero, or positive and integer with no space, in other words, has only digits
#define IDTYPE_TYPE_NUMBER 1
#define IDTYPE_TYPE_TEXT 2

class string_interface;


class id_space;

namespace ca
{
   class type_info;
}

class CLASS_DECL_ca id
{
public:


   union
   {
      const string *       m_pstr;
      int_ptr              m_i;
   };

   char m_chType;


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
   void raw_set(int_ptr user);


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
   id & operator = (const gen::property & prop);


   inline operator int_ptr() const;


   inline operator const char *() const;
   inline operator string () const;
   inline string to_string() const;



   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline void Empty();
   inline void clear();
   inline bool is_number() const;
   inline bool is_text() const;


   friend CLASS_DECL_ca int_ptr id_cmp(const id * pid, int_ptr user);
   friend CLASS_DECL_ca int_ptr id_cmp(const id * pid, const char * psz);
   friend CLASS_DECL_ca int_ptr id_cmp(const id * pid, const string & str);
   friend CLASS_DECL_ca int_ptr id_cmp(const id * pid1, const id * pid2);
   friend CLASS_DECL_ca int_ptr id_strcmp(const id * pid1, const id * pid2);
   friend class id_space;
   friend class ::ca::type_info;

};


inline void id::raw_set(int_ptr i)
{
   m_chType    = IDTYPE_TYPE_NUMBER;
   m_i         = i;
}



inline id::id()
{
   m_i = 0;
   m_chType = IDTYPE_TYPE_NULL;
}

inline id::id(const id & id)
{
   m_i = id.m_i;
   m_chType = id.m_chType;
}




inline bool id::operator == (const id & id) const
{
   return m_i == id.m_i && m_chType == id.m_chType;
}
inline bool id::operator != (const id & id) const
{
   return ! operator == (id);
}
inline bool id::operator < (const id & id) const
{
   return id_cmp(this, &id) < 0;
}
inline bool id::operator <= (const id & id) const
{
   return id_cmp(this, &id) <= 0;
}
inline bool id::operator > (const id & id) const
{
   return id_cmp(this, &id) > 0;
}
inline bool id::operator >= (const id & id) const
{
   return id_cmp(this, &id) >= 0;
}

inline id & id::operator = (const id & id)
{
   m_i       = id.m_i;
   m_chType    = id.m_chType;
   return *this;
}


inline bool id::operator == (const char * psz) const
{
   return !id_cmp(this, psz);
}
inline bool id::operator != (const char * psz) const
{
   return id_cmp(this, psz) != 0;
}
inline bool id::operator < (const char * psz) const
{
   return id_cmp(this, psz) < 0;
}
inline bool id::operator <= (const char * psz) const
{
   return id_cmp(this, psz) <= 0;
}
inline bool id::operator > (const char * psz) const
{
   return id_cmp(this, psz) > 0;
}
inline bool id::operator >= (const char * psz) const
{
   return id_cmp(this, psz) >= 0;
}

#if defined(_LP64) || defined(_AMD64_)

inline bool id::operator == (int32_t i) const
{
   return !id_cmp(this, i);
}
inline bool id::operator != (int32_t i) const
{
   return id_cmp(this, i) != 0;
}
inline bool id::operator < (int32_t i) const
{
   return id_cmp(this, i) < 0;
}
inline bool id::operator <= (int32_t i) const
{
   return id_cmp(this, i) <= 0;
}
inline bool id::operator > (int32_t i) const
{
   return id_cmp(this, i) > 0;
}
inline bool id::operator >= (int32_t i) const
{
   return id_cmp(this, i) >= 0;
}
inline id & id::operator = (int32_t i)
{
   m_i        = i;
   m_chType    = IDTYPE_TYPE_NUMBER;
   return *this;
}
#endif


inline bool id::operator == (int_ptr i) const
{
   return !id_cmp(this, i);
}
inline bool id::operator != (int_ptr i) const
{
   return id_cmp(this, i) != 0;
}
inline bool id::operator < (int_ptr i) const
{
   return id_cmp(this, i) < 0;
}
inline bool id::operator <= (int_ptr i) const
{
   return id_cmp(this, i) <= 0;
}
inline bool id::operator > (int_ptr i) const
{
   return id_cmp(this, i) > 0;
}
inline bool id::operator >= (int_ptr i) const
{
   return id_cmp(this, i) >= 0;
}
inline id & id::operator = (int_ptr i)
{
   m_i        = i;
   m_chType    = IDTYPE_TYPE_NUMBER;
   return *this;
}

inline id::operator int_ptr() const
{
   if(is_number())
      return m_i;
   else
      return 0;
}

//inline id::operator int_ptr()
//{
//   if(is_number())
//      return m_i;
//   else
//      return 0;
//}

inline bool id::is_null() const
{
   return this == NULL || m_chType == IDTYPE_TYPE_NULL || (m_chType == IDTYPE_TYPE_TEXT && m_pstr == NULL);
}

inline bool id::has_char() const
{
   return !is_empty();
}

inline void id::Empty()
{
   m_i = 0;
}

inline void id::clear()
{
   m_i = 0;
}

inline bool id::is_number() const
{
   return m_chType == IDTYPE_TYPE_NUMBER;
}

inline bool id::is_text() const
{
   return m_chType == IDTYPE_TYPE_TEXT;
}


inline CLASS_DECL_ca bool id_is_number(const char * psz)
{
   if(*psz == '\0')
      return false;
   while(*psz != '\0')
   {
      if(!gen::ch::is_digit(psz))
         return false;
      psz = gen::str::utf8_inc(psz);
   }
   return true;
}

inline CLASS_DECL_ca bool id_is_text(const char * psz)
{
   return !id_is_number(psz);
}

inline CLASS_DECL_ca bool id_is_null(const char * psz)
{
   return psz == NULL;
}

inline CLASS_DECL_ca int_ptr id_cmp(const id * pid, int_ptr i)
{
   if(pid->is_null())
   {
      return -1;
   }
   else if(pid->is_number())
   {
      return pid->m_i - i;
   }
   else
   {
      return 1; // non-numerical string is greater than numerical string
   }
}



inline CLASS_DECL_ca int_ptr id_cmp(const id * pid1, const id * pid2)
{
   char register chCompare = pid1->m_chType - pid2->m_chType;
   if(chCompare != 0) return chCompare;
   return pid1->m_i - pid2->m_i;
}




