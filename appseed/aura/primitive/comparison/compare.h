#pragma once


namespace compare
{

	template < typename A, typename B >
	inline bool eq(A a, B b)
	{
		return a == b;
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
	inline bool eq(long long ll, unsigned int ui)
	{
		return ll < 0 ? false : ll == (long long)ui;
	}

	template < >
	inline bool lt(int i, unsigned long long ull)
	{
		return i < 0 ? true : (unsigned long long) i < ull;
	}

	template < >
	inline bool le(int i, unsigned long long ul)
	{
		return i < 0 ? true : ((unsigned long)i) <= ul;
	}

	template < >
	inline bool ge(int i, unsigned long long ul)
	{
		return i < 0 ? false : ((unsigned long)i) >= ul;
	}

	template < >
	inline bool ge(long long l, unsigned long long ul)
	{
		return l < 0 ? false : ((unsigned long long) l) >= ul;
	}

	template < >
	inline bool ge(unsigned int ui, unsigned long long ul)
	{
		return ui >= ul;
	}

	template < >
	inline bool ge(unsigned long long ul1, unsigned long long ul2)
	{
		return ul1 >= ul2;
	}

	template < >
	inline bool ge(unsigned int ui, short sh)
	{
		return sh < 0 ? false : ui <= (unsigned int)sh;
	}


} // namespace compare


