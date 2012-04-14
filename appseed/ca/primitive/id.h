#pragma once

#include "gen/gen_ch.h"
#include "gen/gen_str.h"


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
   id(const char * psz);
   id(int i);
   id(unsigned int ui);
   id(int64_t i);
   id(uint64_t ui);
   id(const string & str);
   id(const string_interface & str);
   id(const var & var);

   inline id()
   {
      m_i = 0;
      m_chType = IDTYPE_TYPE_NULL;
   }

   inline id(const id & id)
   {
      m_i = id.m_i;
      m_chType = id.m_chType;
   }

   string str() const;

   inline bool operator == (const id & id) const
   {
      return m_i == id.m_i && m_chType == id.m_chType;
   }
   inline bool operator != (const id & id) const
   {
      return ! operator == (id);
   }
   inline bool operator < (const id & id) const
   {
      return id_cmp(this, &id) < 0;
   }
   inline bool operator <= (const id & id) const
   {
      return id_cmp(this, &id) <= 0;
   }
   inline bool operator > (const id & id) const
   {
      return id_cmp(this, &id) > 0;
   }
   inline bool operator >= (const id & id) const
   {
      return id_cmp(this, &id) >= 0;
   }
   inline id & operator = (const id & id)
   {
      m_i       = id.m_i;
      m_chType    = id.m_chType;
      return *this;
   }
   inline bool operator == (const char * psz) const
   {
      return !id_cmp(this, (const string &) psz);
   }
   inline bool operator != (const char * psz) const
   {
      return id_cmp(this, (const string &) psz) != 0;
   }
   inline bool operator < (const char * psz) const
   {
      return id_cmp(this, (const string &) psz) < 0;
   }
   inline bool operator <= (const char * psz) const
   {
      return id_cmp(this, (const string &) psz) <= 0;
   }
   inline bool operator > (const char * psz) const
   {
      return id_cmp(this, (const string &) psz) > 0;
   }
   inline bool operator >= (const char * psz) const
   {
      return id_cmp(this, (const string &) psz) >= 0;
   }
   id & operator = (const char * psz);
   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;
   id & operator = (const string & str);
   inline bool operator == (int i) const
   {
      return !id_cmp(this, i);
   }
   inline bool operator != (int i) const
   {
      return id_cmp(this, i) != 0;
   }
   inline bool operator < (int i) const
   {
      return id_cmp(this, i) < 0;
   }
   inline bool operator <= (int i) const
   {
      return id_cmp(this, i) <= 0;
   }
   inline bool operator > (int i) const
   {
      return id_cmp(this, i) > 0;
   }
   inline bool operator >= (int i) const
   {
      return id_cmp(this, i) >= 0;
   }
   inline id & operator = (int i)
   {
      m_i        = i;
      m_chType    = IDTYPE_TYPE_NUMBER;
      return *this;
   }
    inline bool operator <= (long l) const
    {
        return id_cmp(this, l) <= 0;
    }
    inline bool operator >= (long l) const
    {
        return id_cmp(this, l) >= 0;
    }
    #if !defined(LINUX)
   inline bool operator == (int64_t i) const
   {
      return !id_cmp(this, i);
   }
   inline bool operator != (int64_t i) const
   {
      return id_cmp(this, i) != 0;
   }
   inline bool operator < (int64_t i) const
   {
      return id_cmp(this, i) < 0;
   }
   inline bool operator <= (int64_t i) const
   {
      return id_cmp(this, i) <= 0;
   }
   inline bool operator > (int64_t i) const
   {
      return id_cmp(this, i) > 0;
   }
   inline bool operator >= (int64_t i) const
   {
      return id_cmp(this, i) >= 0;
   }
   inline id & operator = (int64_t i)
   {
      m_i        = i;
      m_chType    = IDTYPE_TYPE_NUMBER;
      return *this;
   }
   #endif
   inline bool operator == (const string_interface & str) const;
   inline bool operator != (const string_interface & str) const;
   inline bool operator < (const string_interface & str) const;
   inline bool operator <= (const string_interface & str) const;
   inline bool operator > (const string_interface & str) const;
   inline bool operator >= (const string_interface & str) const;

   id & operator = (const string_interface & str);

   id & operator = (const var & var);

   inline operator int64_t() const
   {
      if(is_number())
         return m_i;
      else
         return 0;
   }

   inline operator int64_t()
   {
      if(is_number())
         return m_i;
      else
         return 0;
   }

   inline operator const char *() const;

   inline operator const string & () const
   {
      return *m_pstr;
   }

   inline bool is_null() const
   {
      return this == NULL || m_chType == IDTYPE_TYPE_NULL || (m_chType == IDTYPE_TYPE_TEXT && m_pstr == NULL);
   }

   inline bool is_empty() const;

   inline bool has_char() const
   {
      return !is_empty();
   }

   inline void Empty()
   {
      m_i = 0;
   }

   inline void clear()
   {
      m_i = 0;
   }

   inline bool is_number() const
   {
      return m_chType == IDTYPE_TYPE_NUMBER;
   }

   inline bool is_text() const
   {
      return m_chType == IDTYPE_TYPE_TEXT;
   }

   friend CLASS_DECL_ca int64_t id_cmp(const id * pid, int64_t user);
   friend CLASS_DECL_ca int64_t id_cmp(const id * pid, const string & str);
   friend CLASS_DECL_ca int64_t id_cmp(const id * pid1, const id * pid2);
   friend CLASS_DECL_ca int64_t id_strcmp(const id * pid1, const id * pid2);
   friend class id_space;
   friend class ::ca::type_info;

   void raw_set(const string * pstr);
   void raw_set(int64_t user);
   union
   {
      const string *       m_pstr;
      int64_t              m_i;
   };
   char m_chType;
};


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

inline CLASS_DECL_ca int64_t id_cmp(const id * pid, int64_t i)
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



inline CLASS_DECL_ca int64_t id_cmp(const id * pid1, const id * pid2)
{
   char register chCompare = pid1->m_chType - pid2->m_chType;
   if(chCompare != 0) return chCompare;
   return pid1->m_i - pid2->m_i;
}




inline void id::raw_set(int64_t i)
{
   m_chType    = IDTYPE_TYPE_NUMBER;
   m_i         = i;
}
