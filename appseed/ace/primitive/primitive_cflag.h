#pragma once


template < typename ENUM, typename TYPE = int64_t >
class cflag
{
public:


   TYPE m_i;

   cflag() { m_i = 0; }
   cflag(ENUM e) { m_i = e; }
   cflag(const cflag & e) { m_i = e.m_i; }

   inline cflag & operator |= (ENUM e) { m_i = (e | m_i); return *this; }
   inline cflag & operator &= (ENUM e) { m_i = (m_i & e); return *this; }

   inline cflag & operator += (ENUM e) { return operator |= (e); }
   inline cflag & operator -= (ENUM e) { return operator &= ((ENUM)~(TYPE)(e)); }

   inline cflag operator + (ENUM e) { return (ENUM)(m_i | e); }
   inline cflag operator - (ENUM e) { return (ENUM)(m_i & ~((TYPE)e)); }

   inline cflag operator | (ENUM e) { return (ENUM)(m_i | e); }
   inline cflag operator & (ENUM e) { return (ENUM)(m_i & e); }

   inline bool is(ENUM e) const { return (TYPE)(m_i & e) == (TYPE)e; }
   inline bool is_signalized(ENUM e) const { return is(e); }

   void signalize(ENUM e) { operator += (e); }
   void unsignalize_all() { m_i = 0; }

   cflag & operator = (const cflag & e) { m_i = e.m_i; return *this; }


   operator ENUM & ()
   {
      return (ENUM &)m_i;
   }

   operator ENUM() const
   {

      return (ENUM)m_i;
   }

};






