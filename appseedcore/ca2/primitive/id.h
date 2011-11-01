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
#if defined(_AMD64_) || defined(VC6)
   id(int i);
#endif
   id(unsigned int i);
   id(index i);
   id(const string & str);
   id(const string_interface & str);

   inline id()
   {
      m_psz = NULL;
      m_chType = IDTYPE_TYPE_NULL;
   }

   inline id(const id & id)
   {
      m_psz = id.m_psz;
      m_chType = id.m_chType;
   }

   string str();

   inline bool operator == (const id & id) const
   {
      if(is_null())
      {
         if(id.is_null())
         {
            return true;
         }
      }
      else if(is_text())
      {
         if(id.is_text())
         {
            return m_psz == id.m_psz;
         }
      }
      else if(is_number())
      {
         if(id.is_number())
         {
            return m_ui == id.m_ui;
         }
      }
      return false;
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
      m_psz       = id.m_psz;
      m_chType    = id.m_chType;
      return *this;
   }
   inline bool operator == (const char * psz) const
   {
      return !id_cmp(this, psz);
   }
   inline bool operator != (const char * psz) const
   {
      return id_cmp(this, psz) != 0;
   }
   inline bool operator < (const char * psz) const
   {
      return id_cmp(this, psz) < 0;
   }
   inline bool operator <= (const char * psz) const
   {
      return id_cmp(this, psz) <= 0;
   }
   inline bool operator > (const char * psz) const
   {
      return id_cmp(this, psz) > 0;
   }
   inline bool operator >= (const char * psz) const
   {
      return id_cmp(this, psz) >= 0;
   }
   id & operator = (const char * psz);
   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;
   id & operator = (const string & str);
#if defined(_AMD64_) || defined(VC6)
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
   inline id & operator = (index i)
   {
      m_ui        = i;
      m_chType    = IDTYPE_TYPE_NUMBER;
      return *this;
   }
#endif
   inline bool operator == (index user) const
   {
      return !id_cmp(this, user);
   }
   inline bool operator != (index user) const
   {
      return id_cmp(this, user) != 0;
   }
   inline bool operator < (index user) const
   {
      return id_cmp(this, user) < 0;
   }
   inline bool operator <= (index user) const
   {
      return id_cmp(this, user) <= 0;
   }
   inline bool operator > (index user) const
   {
      return id_cmp(this, user) > 0;
   }
   inline bool operator >= (index user) const
   {
      return id_cmp(this, user) >= 0;
   }
   inline id & operator = (int i)
   {
      m_ui        = i;
      m_chType    = IDTYPE_TYPE_NUMBER;
      return *this;
   }
   inline bool operator == (const string_interface & str) const;
   inline bool operator != (const string_interface & str) const;
   inline bool operator < (const string_interface & str) const;
   inline bool operator <= (const string_interface & str) const;
   inline bool operator > (const string_interface & str) const;
   inline bool operator >= (const string_interface & str) const;

   id & operator = (const string_interface & str);

   inline operator index() const
   {
      if(is_number())
         return m_ui;
      else
         return 0;
   }

   inline operator index()
   {
      if(is_number())
         return m_ui;
      else
         return 0;
   }

   inline operator const char *() const
   {
      return m_psz;
   }

   inline operator const char *()
   {
      return m_psz;
   }

   inline bool is_null() const
   {
      return m_chType == IDTYPE_TYPE_NULL || (m_chType == IDTYPE_TYPE_TEXT && m_psz == NULL);
   }

   inline bool is_empty() const
   {
      return is_null() || (is_text() && (m_psz == NULL || m_psz[0] == '\0'));
   }

   inline bool has_char() const
   {
      return !is_empty();
   }

   inline void Empty()
   {
      m_psz = NULL;
   }

   inline void clear()
   {
      m_psz = NULL;
   }

   inline bool is_number() const
   {
      return m_chType == IDTYPE_TYPE_NUMBER;
   }

   inline bool is_text() const
   {
      return m_chType == IDTYPE_TYPE_TEXT;
   }

   friend CLASS_DECL_ca index id_cmp(const id * pid, index user);
   friend CLASS_DECL_ca index id_cmp(const id * pid, const char * psz);
   friend CLASS_DECL_ca index id_cmp(const id * pid1, const id * pid2);
   friend index BaseSortCompare(id f1, id f2);
   friend class id_space;
   friend class ::ca::type_info;
protected:
   void raw_set(const char * psz);
   void raw_set(index user);
   union
   {
      const char *         m_psz;
#ifdef _AMD64_
      uint64_t     m_ui;
#else
      unsigned int         m_ui;
#endif
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

inline CLASS_DECL_ca index id_cmp(const id * pid, index user)
{
   if(pid->is_null())
   {
      return -1;
   }
   else if(pid->is_number())
   {
      return pid->m_ui - user;
   }
   else
   {
      return 1; // non-numerical string is greater than numerical string
   }
}

inline CLASS_DECL_ca index id_cmp(const id * pid, const char * psz)
{
   if(pid->is_null())
   {
      if(id_is_null(psz))
      {
         return 0;
      }
      else
      {
         return -1;
      }
   }
   else if(pid->is_text())
   {
      if(id_is_null(psz))
      {
         return 1;
      }
      else if(id_is_text(psz))
      {
         return strcmp(pid->m_psz, psz);
      }
      else
      {
         return 1;
      }
   }
   else // if(pid->is_number())
   {
      if(id_is_null(psz))
      {
         return 1;
      }
      else if(id_is_text(psz))
      {
         return 1;
      }
      else
      {
         return pid->m_ui - atoi(psz);
      }
   }
}


inline CLASS_DECL_ca index id_cmp(const id * pid1, const id * pid2)
{
   if(pid1->is_null() || (pid1->is_text() && pid1->m_psz == NULL))
   {
      if(pid2->is_null() || (pid2->is_text() && pid2->m_psz == NULL))
      {
         return 0;
      }
      else
      {
         return -1;
      }
   }
   else if(pid1->is_text())
   {
      if(pid2->is_null() || (pid2->is_text() && pid2->m_psz == NULL))
      {
         return 1;
      }
      else if(pid2->is_text())
      {
         return strcmp(pid1->m_psz, pid2->m_psz);
      }
      else
      {
         return 1;
      }
   }
   else
   {
      if(pid2->is_null() || (pid2->is_text() && pid2->m_psz == NULL))
      {
         return 1;
      }
      else if(pid2->is_text())
      {
         return -1;
      }
      else
      {
         return pid1->m_ui - pid2->m_ui;
      }
   }
}


