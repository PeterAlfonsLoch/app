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

   template < >
   inline bool lt(int i,unsigned long long ull)
   {
      return i < 0 ? true : (unsigned long long) i < ull;
   }

   template < >
   inline bool lt(int i,unsigned long ul)
   {
      return i < 0 ? true : (unsigned long)i < ul;
   }


   template < >
   inline bool lt(int i,unsigned int ui)
   {
      return i < 0 ? true : (unsigned int)i < ui;
   }

   template < >
   inline bool lt(unsigned int ui,int i)
   {
      return i < 0 ? false : ui < (unsigned int)i;
   }

   template < >
   inline bool lt(uint64_t ui64,uint32_t ui32)
   {
      return ui64 > 0xffffffffull ? false : (uint64_t)ui64 < ui32;
   }

#if defined(WINDOWS) 

   template < >
   inline bool lt(int64_t i,unsigned __int64 ui)
   {
      return i < 0 ? true : (unsigned __int64)i < ui;
   }

   template < >
   inline bool lt(DWORD dw, int i)
   {
      return i < 0 ? false : dw < (DWORD)i;
   }

#endif


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


   template < >
   inline bool gt(int i,unsigned int ui)
   {

      return i < 0 ? false : ((unsigned int)i) > ui;

   }


   template < >
   inline bool gt(int i,unsigned long ul)
   {

      return i < 0 ? false : ((unsigned int)i) > ul;

   }



   template < >
   inline bool gt(unsigned int ui, int i)
   {

      return i < 0 ? true : ui >((unsigned int)i);

   }


   template < >
   inline bool gt(int64_t i, uint64_t ui)
   {

      return i < 0 ? false : ((uint64_t)i) > ui;

   }

   template < >
   inline bool gt(int i, long long unsigned int llui)
   {

      return i < 0 ? false : ((long long unsigned int)i) > llui;

   }

#ifdef WINDOWS
   template < >
   inline bool gt(DWORD dw,int i)
   {
      return i < 0 ? true : dw >((unsigned int)dw);
   }

   //template < >
   //inline bool gt(count i,uint64_t ui)
   //{

   //   return i < 0 ? false : ((uint64_t)i) > ui;

   //}

#endif

	template < typename A, typename B >
	inline bool ge(A a, B b)
	{
		return a >= b;
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
   inline bool ge(unsigned long long ul1, long long l2)
   {
      return l2 < 0 ? true : ul1 >= (unsigned long long) l2;
   }

   template < >
   inline bool ge(unsigned int ui,short sh)
   {
      return sh < 0 ? true : ui >= (unsigned int)sh;
   }

   template < >
   inline bool ge(int i,unsigned int ui)
   {
      return i < 0 ? false : (unsigned int) i >= ui;
   }

   template < >
   inline bool ge(unsigned int ui, int i)
   {
      return i < 0 ? true : ui >= (unsigned int)i;
   }


   

	template < >
	inline bool le(int i, unsigned long long ul)
	{
		return i < 0 ? true : ((unsigned long)i) <= ul;
	}

} // namespace compare


