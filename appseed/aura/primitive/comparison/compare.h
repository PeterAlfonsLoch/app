#pragma once


namespace compare
{

	template < typename A, typename B >
	inline bool eq(A a, B b)
	{
		return a == b;
	}

   template < >
   inline bool eq(int i,unsigned int ui)
   {
      return i < 0 ? false : (unsigned int) i == ui;
   }


   
   template < typename A, typename B >
	inline bool lt(A a, B b)
	{
		return a < b;
	}
	template < typename A, typename B >
	inline bool le(A a, B b)
	{
		return a <= b;
	}
	template < typename A, typename B >
	inline bool gt(A a, B b)
	{
		return a > b;
	}
	template < typename A, typename B >
	inline bool ge(A a, B b)
	{
		return a > b;
	}

   template < >
   inline bool ge(int i,unsigned long long ul)
   {
      return i < 0 ? false : ((unsigned long)i) >= ul;
   }

   template < >
   inline bool ge(long long l,unsigned long long ul)
   {
      return l < 0 ? false : ((unsigned long long) l) >= ul;
   }

   template < >
   inline bool ge(unsigned int ui,unsigned long long ul)
   {
      return ui >= ul;
   }

   template < >
   inline bool ge(unsigned long long ul1,unsigned long long ul2)
   {
      return ul1 >= ul2;
   }

   template < >
   inline bool ge(unsigned int ui,short sh)
   {
      return sh < 0 ? false : ui <= (unsigned int)sh;
   }

   template < >
   inline bool ge(int i,unsigned int ui)
   {
      return i < 0 ? false : (unsigned int) i <= ui;
   }


	template < >
	inline bool lt(int i, unsigned long long ull)
	{
		return i < 0 ? true : (unsigned long long) i < ull;
	}

   template < >
   inline bool lt(int i,unsigned int ui)
   {
      return i < 0 ? true : (unsigned int) i < ui;
   }

   template < >
   inline bool lt(unsigned int ui, int i)
   {
      return i < 0 ? false : ui < (unsigned int)i;
   }

	template < >
	inline bool le(int i, unsigned long long ul)
	{
		return i < 0 ? true : ((unsigned long)i) <= ul;
	}

   template < >
   inline bool gt(int i,unsigned int ui)
   {
      return i < 0 ? false : ((unsigned int)i) > ui;
   }
} // namespace compare


