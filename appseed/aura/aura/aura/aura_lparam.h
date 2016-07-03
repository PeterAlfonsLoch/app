#pragma once

//class cnull
//{
//public: 
//};


class object;


class CLASS_DECL_AURA lparam
{
public:


   LPARAM m_lparam;

   lparam(LPARAM lparam = 0) { m_lparam = lparam; }

#ifndef VSNORD

   lparam(int i) { m_lparam = (LPARAM) i; }

#endif

#if OSBIT != 64

   lparam(int64_t i) { m_lparam = (LPARAM)i; }

#endif

   inline lparam(::object * pobject);

   //template < class T >
   //lparam(const smart_pointer < T > & sp);

   lparam(const lparam & lparam)
   {
      m_lparam = lparam.m_lparam;
   }

   operator LPARAM &()
   {
      return m_lparam;
   }

   template < typename T >
   operator T * () const
   {
      return (T *) m_lparam;
   }

   lparam & operator = (const lparam & lparam)
   {
      m_lparam = lparam.m_lparam;
      return *this;
   }

   lparam & operator = (LPARAM lparam)
   {
      m_lparam = lparam;
      return *this;
   }

   inline int x() const
   {
      return GET_X_LPARAM(m_lparam);
   }

   inline int y() const
   {
      return GET_Y_LPARAM(m_lparam);
   }

};



//template < class T >
//inline lparam::lparam(const smart_pointer < T > & sp)
//{
//   sp->add_ref();
//   this->m_lparam = (LPARAM) sp.m_p;
//}
//
//
