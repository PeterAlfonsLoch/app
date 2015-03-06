#pragma once

//#include <stdio.h>
//#include <string>
//#include <tuple>

template<class TYPE>
struct add_const
{	
   typedef const TYPE type;
};


template<class TYPE>
struct add_volatile
{	
   typedef volatile TYPE type;
};

template<class TYPE>
struct add_cv
{	
   typedef const volatile TYPE type;
};


template<class TYPE>
struct add_reference
{	
   typedef TYPE& type;
};

template<class TYPE>
struct add_lvalue_reference
{	
   typedef typename add_reference<TYPE>::type type;
};


template<class TYPE>
struct add_rvalue_reference
{	// add rvalue reference
   typedef TYPE&& type;
};



// CLASS _Unrefwrap
template<class TYPE>
class reference_wrapper;


//#define _ADD_RVALUE_REFERENCE_VOID(CV_OPT) \
//template<> \
//	struct add_rvalue_reference<CV_OPT void> \
//	{	/* add reference */ \
//	typedef CV_OPT void type; \
//	};
//
//_CLASS_DEFINE_CV(_ADD_RVALUE_REFERENCE_VOID)
//#undef _ADD_RVALUE_REFERENCE_VOID
//
//// TEMPLATE FUNCTION declval
//template<class TYPE>
//typename add_rvalue_reference<TYPE>::type
//declval() _NOEXCEPT;


template < typename TYPE >
void swap(const TYPE & t1,const TYPE & t2)
{
   
   TYPE t = t1;

   t1 = t2;

   t2 = t;
   
}


template<class... TYPES>
class tuple;

template<>
class tuple<>
{	
public:
   typedef tuple<> TUPLE_TYPE;

   tuple()
   {
   }

   tuple(const tuple&) throw()
   {
   }

   void swap(TUPLE_TYPE&) throw()
   {
   }

   bool equals(const TUPLE_TYPE&) throw()
   {
      return true;
   }

   bool less(const TUPLE_TYPE&)throw()
   {
      return false;
   }
};



template<class TYPE,
class... REST>
class tuple<TYPE,REST...>
   : public tuple<REST...>
{	
public:
   typedef TYPE THIS_TYPE;
   typedef tuple<TYPE,REST...> TUPLE_TYPE;
   typedef tuple<REST...> BASE_TYPE;
   static const size_t TYPE_SIZE = 1 + sizeof...(REST);

   TYPE     m_val;


   tuple()
   {	
   }

   template < class... OTHER >
   tuple(const tuple<OTHER...>& right)
      : BASE_TYPE(right.get_rest()),m_val(right.m_val)
   {
   }

   template < class... OTHER >
   tuple(tuple<OTHER...>&& right)
      : BASE_TYPE(::move(right.get_rest())),m_val(::move(right.m_val))
   {
   }

   explicit tuple(const TYPE& val,const REST&... rest)
      : BASE_TYPE(rest...),
      m_val(val)
   {	
   }

   explicit tuple(TYPE && val,const REST &&... rest)
      : BASE_TYPE(::move(right.get_rest())),m_val(::move(right.m_val))
   {
   }


   template<class... OTHER>
   TUPLE_TYPE& operator=(const tuple<OTHER...>& right)
   {	
      m_val = right.m_val;
      (BASE_TYPE&)*this = right.get_rest();
      return (*this);
   }

   template<class... OTHER>
   TUPLE_TYPE& operator=(tuple<OTHER...>&& right)
   {	
      m_val = ::move(right.m_val);
      BASE_TYPE::operator = (::move(right.get_rest()));
      return *this;
   }

   template<class... OTHER>
   bool equals(const tuple<OTHER...>& right) const
   {	
      return m_val == right.m_val && BASE_TYPE::equals(right.get_rest());
   }

   template<class... OTHER>
   bool less(const tuple<OTHER...>& right) const
   {	
      return m_val < right.m_val || (!(right.m_val < m_val) && BASE_TYPE::less(right.get_rest()));
   }

   template < class TYPE1, class TYPE2>
   tuple(const pair < TYPE1 , TYPE2 > & right) :
      BASE_TYPE( tuple < TYPE2 > ( right.m_element2 ) ),
      m_val(right.m_element1)
   {	
      
   }


   TUPLE_TYPE & operator=(const TUPLE_TYPE & right)
   {	
      
      m_val = right.m_val;
   
      BASE_TYPE::operator =(right.get_rest());

      return *this;

   }


   template < class TYPE1, class TYPE2>
      TUPLE_TYPE & operator=(const pair < TYPE1, TYPE2 >& right)
   {	
      
      m_val = right.first;
      
      BASE_TYPE::operator =(tuple<TYPE2>(right.m_element2));
      
      return *this;

   }


   template < class TYPE1, class TYPE2 >
   tuple(pair < TYPE1, TYPE2 > && right) :
      BASE_TYPE(tuple<TYPE2>(::move(right.second))),
      m_val(::move(right.first))
   {	
      
   }


   TUPLE_TYPE & operator=(TUPLE_TYPE&& right)
   {	

      m_val = ::move(right.m_val);

      BASE_TYPE::operator = (::move(right.get_rest()));

      return (*this);

   }


   template < class TYPE1, class TYPE2>
   TUPLE_TYPE& operator=(pair<TYPE1,TYPE2>&& right)
   {

      m_val = ::move(right.m_element1);
      
      BASE_TYPE::operator = (tuple<TYPE2>(::move(right.second)));
      
      return *this;

   }

   
   BASE_TYPE & get_rest()
   {	
      
      return *this;

   }

   const BASE_TYPE & get_rest() const
   {	

      return *this;

   }


   void swap(tuple& right)
   {	
      
      swap(m_val,right.m_val);

      BASE_TYPE::swap((BASE_TYPE&)right);

   }

};


template<class... TYPES1, class... TYPES2> 
inline bool operator==(const tuple<TYPES1...>& left, const tuple<TYPES2...>& right)
{	
   return left.equals(right);
}

template<class... TYPES1, class... TYPES2> 
inline bool operator!=(const tuple<TYPES1...>& left, const tuple<TYPES2...>& right)
{	
   return !(left == right);
}

template<class... TYPES1, class... TYPES2> 
inline bool operator<(const tuple<TYPES1...>& left, const tuple<TYPES2...>& right)
{	
   return left.less(right);
}

template<class... TYPES1, class... TYPES2> 
inline bool operator>=(const tuple<TYPES1...>& left, const tuple<TYPES2...>& right)
{	
   return !(left < right);
}

template<class... TYPES1, class... TYPES2> 
inline bool operator>(const tuple<TYPES1...>& left, const tuple<TYPES2...>& right)
{	
   return right < left;
}

template<class... TYPES1, class... TYPES2> 
inline bool operator<=(const tuple<TYPES1...>& left, const tuple<TYPES2...>& right)
{	
   return !(right < left);
}

template<class... TYPES> 
inline void swap(tuple<TYPES...>& left, tuple<TYPES...>& right)
{	
   return left.swap(right);
}


template<size_t m_iIndex, class TUPLE>
struct tuple_element;

template<class TYPE, class... REST>
struct tuple_element<0,tuple<TYPE,REST...> >
{	
   typedef TYPE type;
   typedef typename add_lvalue_reference<const TYPE>::type _Ctype;
   typedef typename add_lvalue_reference<TYPE>::type _Rtype;
   typedef typename add_rvalue_reference<TYPE>::type _RRtype;
   typedef tuple<TYPE,REST...> TUPLE_TYPE;
};

template<size_t m_iIndex, class TYPE, class... REST>
struct tuple_element<m_iIndex,tuple<TYPE,REST...> >
   : public tuple_element<m_iIndex - 1,tuple<REST...> >
{	
};


template<size_t m_iIndex, class TUPLE>
struct tuple_element<m_iIndex,const TUPLE>
   : public tuple_element<m_iIndex,TUPLE>
{	
   typedef tuple_element<m_iIndex,TUPLE> BASE_TYPE;
   typedef typename add_const<typename BASE_TYPE::type>::type type;
};

template<size_t m_iIndex, class TUPLE>
struct tuple_element<m_iIndex,volatile TUPLE>
   : public tuple_element<m_iIndex,TUPLE>
{	
   typedef tuple_element<m_iIndex,TUPLE> BASE_TYPE;
   typedef typename add_volatile<typename BASE_TYPE::type>::type type;
};

template<size_t m_iIndex,
class TUPLE>
struct tuple_element<m_iIndex,const volatile TUPLE>
   : public tuple_element<m_iIndex,TUPLE>
{
   typedef tuple_element<m_iIndex,TUPLE> BASE_TYPE;
   typedef typename add_cv<typename BASE_TYPE::type>::type type;
};


template<size_t m_iIndex, class... TYPES> 
inline typename tuple_element<m_iIndex,tuple<TYPES...> >::_Rtype  get(tuple<TYPES...>& TUPLE)
{	
   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::TUPLE_TYPE     TUPLE_TYPE;
   return (((TUPLE_TYPE&)TUPLE).m_val);
}

template<size_t m_iIndex, class... TYPES> 
inline typename tuple_element<m_iIndex,tuple<TYPES...> >::_Ctype get(const tuple<TYPES...>& TUPLE)
{	
   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::TUPLE_TYPE TUPLE_TYPE;
   return (((TUPLE_TYPE&)TUPLE).m_val);
}


template<size_t m_iIndex, class... TYPES> 
inline  typename tuple_element<m_iIndex,tuple<TYPES...> >::_RRtype  get(tuple<TYPES...>&& TUPLE)
{	

   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::TUPLE_TYPE TUPLE_TYPE;
   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::_RRtype  _RRtype;
   return (::move(((TUPLE_TYPE&)TUPLE).m_val));

}


template<class... TYPES> inline
tuple < TYPES&&... > make_tuple(TYPES&&... args)
{	

   return ::move(args);

}


template<class... TYPES> inline
tuple<TYPES&...>
tie(TYPES&... args) throw()
{	
   
   typedef tuple<TYPES&...> TUPLE_TYPE;

   return (TUPLE_TYPE(args...));

}


// TEMPLATE FUNCTION forward_as_tuple

//template<class... TYPES> inline
//tuple<TYPES&&...>
//forward_as_tuple(TYPES&&... args) _NOEXCEPT
//{	// forward arguments in a tuple
//   return (tuple<TYPES&&...>(_STD forward<TYPES>(args)...));
//}

//
//// TEMPLATE STRUCT _Make_arg_idx AND HELPERS
//template<class _Arg_idx_type,
//class... TYPES>
//struct _Make_arg_idx1
//{	// ends recursion and defines type
//   typedef _Arg_idx_type type;
//};

//template<size_t... _Indexes,
//class TYPE,
//class... TYPES>
//struct _Make_arg_idx1<ARG_INDEX<_Indexes...>,TYPE,TYPES...>
//   : _Make_arg_idx1<ARG_INDEX<sizeof...(TYPES),_Indexes...>,TYPES...>
//{	// counts a type and recurses
//};
//
//template<class... TYPES>
//struct _Make_arg_idx
//   : _Make_arg_idx1<ARG_INDEX<>,TYPES...>
//{	// defines type as ARG_INDEX<0, 1, 2... (sizeof...(TYPES))-1>
//};
//
//template<class _Arg_idx_type1,
//class _Arg_idx_type2>
//struct _Cat_arg_idx;
//
//template<size_t... INDEXES1,
//   size_t... INDEXES2>
//struct _Cat_arg_idx<ARG_INDEX<INDEXES1...>,ARG_INDEX<INDEXES2...> >
//{	// concatenates two ARG_INDEX types
//   typedef ARG_INDEX<INDEXES1...,INDEXES2...> type;
//};

//template<size_t _Nx,
//class TYPE>
//struct _Repeat_for
//   : integral_constant<size_t,_Nx>
//{	// repeats _Nx for each TYPE in a parameter pack
//};
//
//// FUNCTION tuple_cat
//template<class _Ret,
//class _Kx_arg,
//class _Ix_arg,
//   size_t _Ix_next,
//class... TUPLES>
//struct tuple_cat2
//{	
//   typedef _Ret type;
//   typedef _Kx_arg _Kx_arg_idx;
//   typedef _Ix_arg _Ix_arg_idx;
//};
//
//template<class... TYPES1,
//class _Kx_arg,
//   size_t... _Ix,
//   size_t _Ix_next,
//class... TYPES2,
//class... REST>
//struct tuple_cat2<tuple<TYPES1...>,_Kx_arg,ARG_INDEX<_Ix...>,_Ix_next,
//   tuple<TYPES2...>,REST...>
//   : tuple_cat2<
//   tuple<TYPES1...,TYPES2...>,
//   typename _Cat_arg_idx<_Kx_arg,
//   typename _Make_arg_idx<TYPES2...>::type>::type,
//   ARG_INDEX<_Ix...,_Repeat_for<_Ix_next,TYPES2>::value...>,
//   _Ix_next + 1,
//   REST...>
//{	// determine tuple_cat's return type and _Kx/_Ix indices
//};
//
//template<class... TUPLES>
//struct tuple_cat1
//   : tuple_cat2<tuple<>,ARG_INDEX<>,ARG_INDEX<>,0,
//   typename decay<TUPLES>::type...>
//{	// prepare to determine tuple_cat's return type and _Kx/_Ix indices
//};
//
//template<class _Ret, size_t... _Kx, size_t... _Ix, class TYPE>
// inline _Ret tuple_cat(ARG_INDEX<_Kx...>,ARG_INDEX<_Ix...>,TYPE&& _Arg)
//{	// concatenate tuples
//   return (_Ret(_STD get<_Kx>(_STD get<_Ix>(_STD forward<TYPE>(_Arg)))...));
//}
//
//template<class... TUPLES> inline
//typename tuple_cat1<TUPLES...>::type
//tuple_cat(TUPLES&&... _Tpls)
//{	// concatenate tuples
//   typedef tuple_cat1<TUPLES...> _Cat1;
//   return (tuple_cat<typename _Cat1::type>(
//      typename _Cat1::_Kx_arg_idx(),typename _Cat1::_Ix_arg_idx(),
//      _STD forward_as_tuple(_STD forward<TUPLES>(_Tpls)...)));
//}


//// TEMPLATE CONSTRUCTOR pair::pair(tuple, tuple, ARG_INDEX, ARG_INDEX)
//template<class TYPE1,
//class _Ty2>
//   template<class _Tuple1,
//class _Tuple2,
//   size_t... INDEXES1,
//   size_t... INDEXES2> inline
//   pair<TYPE1,_Ty2>::pair(_Tuple1& _Val1,
//   _Tuple2& _Val2,
//   ARG_INDEX<INDEXES1...>,
//   ARG_INDEX<INDEXES2...>)
//   : first(_STD get<INDEXES1>(_STD move(_Val1))...),
//   second(_STD get<INDEXES2>(_STD move(_Val2))...)
//{	// construct from pair of tuples
//}

//// TEMPLATE CONSTRUCTOR pair::pair(piecewise_construct_t, tuple, tuple)
//template<class TYPE1,
//class _Ty2>
//   template<class... TYPES1,
//class... TYPES2> inline
//   pair<TYPE1,_Ty2>::pair(piecewise_construct_t,
//   tuple<TYPES1...> _Val1,
//   tuple<TYPES2...> _Val2)
//   _NOEXCEPT_OP((is_nothrow_constructible<TYPE1,TYPES1&&...>::value
//   && is_nothrow_constructible<_Ty2,TYPES2&&...>::value))
//   : pair(_Val1,_Val2,
//   typename _Make_arg_idx<TYPES1...>::type(),
//   typename _Make_arg_idx<TYPES2...>::type())
//{	// construct from pair of tuples
//}
//_STD_END
//
//
//
//#include <type_traits>
//#include <assert.h>
//#include <utility>

//#ifndef MAKE
//#error "-DMAKE= make1, make2, or make3"
//#endif
//#ifndef PARAMETER
//#error "-DPARAMETER= 1,2,4,8,16,32,64,128,256, or 512"
//#endif
//#ifndef SPACESHIP
//#error "-DSPACESHIP= spaceship1 or spaceship2"
//#endif

//#if 1
//#define INDEX_SEQUENCE(NN) std::index_sequence<NN>
//#define MAKE_INDEX_SEQUENCE(N) std::make_index_sequence<N>
//#else
//#define INDEX_SEQUENCE(NN) std::__tuple_indices<NN>
//#define MAKE_INDEX_SEQUENCE(N) typename std::__make_tuple_indices<N>::type
//#endif

// The easy part.
//

template < typename TYPE1, typename TYPE2 >
inline int cmp(const TYPE1 & t1,const TYPE2 & t2)
{
   return (t1 < t2) ? -1 : (t1 < t2) ? 1 : 0;
}


template < typename TYPE1,typename TYPE2 >
inline int icmp(const TYPE1 & t1,const TYPE2 & t2)
{
   return cmp(t1, t2);
}

template < >
inline int cmp(const string & str1, const string & str2)
{
   return str1.Compare(str2);
}


template < >
inline int icmp(const string & str1,const string & str2)
{
   return str1.CompareNoCase(str2);
}

template<size_t TUPLE_SIZE> struct cmp_tuple
{
   template < typename T1, typename T2>
     int operator()(const T1 & t1,const T2 & t2) const
   {
      int r = cmp_tuple<TUPLE_SIZE - 1>()(y1,t2);
      return (r != 0) ? r : cmp(get<TUPLE_SIZE - 1>(t1),get<TUPLE_SIZE - 1>(t2));
   }
};


template<size_t TUPLE_SIZE> struct icmp_tuple
{
   template < typename T1,typename T2>
   int operator()(const T1 & t1,const T2 & t2) const
   {
      int r = icmp_tuple<TUPLE_SIZE - 1>()(y1,t2);
      return (r != 0) ? r : icmp(get<TUPLE_SIZE - 1>(t1),get<TUPLE_SIZE - 1>(t2));
   }
};

template<> struct cmp_tuple<0>
{
   template < typename T1,typename T2>
    int operator()(const T1&,const T2&) const
   {
      return 0;
   }
};

template<> struct icmp_tuple<0>
{
   template < typename T1,typename T2>
    int operator()(const T1&,const T2&) const
   {
      return 0;
   }
};

//template <class ..._Tp,class ..._Up>
// int cmp1(const tuple<_Tp...>& __x,const tuple<_Up...>& __y)
//{
//   static_assert(sizeof...(_Tp) == sizeof...(_Up),"");
//   return __tuple_spaceship1<sizeof...(_Tp)>()(__x,__y);
//}

//template <class _Tp,class _Up,size_t ..._Ip>
// int cmp2(const _Tp& __x,const _Up& __y,const INDEX_SEQUENCE(_Ip...)&)
//{
//   int __r = 0;
//   std::initializer_list<int> x ={
//      (__r != 0) ? 0 : (__r = spaceship(get<_Ip>(__x),get<_Ip>(__y))) ...
//   };
//   return __r;
//}
//
//template <class ..._Tp,class ..._Up>
// int cmp2(const tuple<_Tp...>& __x,const tuple<_Up...>& __y)
//{
//   static_assert(sizeof...(_Tp) == sizeof...(_Up),"");
//   return __tuple_spaceship2(__x,__y,MAKE_INDEX_SEQUENCE(sizeof...(_Tp)){});
//}



//namespace Foo {
//   class Widget {
//      int value;
//   public:
//      Widget(int v): value(v) {}
//      friend int spaceship(const Widget& w1,const Widget& w2) { return std::spaceship(w1.value,w2.value); }
//      void operator< (const Widget&) const { printf("BAAAD\n"); assert(false); }
//      void operator== (const Widget&) const { printf("BAAAD\n"); assert(false); }
//      void operator> (const Widget&) const { printf("BAAAD\n"); assert(false); }
//   };
//}
//
//
//template<int N> auto make1() { return tuple_cat(make1<N / 2>(),make1<N / 2>()); }
//template<> auto make1<1>() { return tuple<std::string>("hello"); }
//template<> auto make1<0>() { return tuple<>(); }
//#define make1(N) make1<N>()
//
//template<size_t... N> auto make2(const INDEX_SEQUENCE(N...)&) { return tuple<decltype(N,std::string{})...>((N,"hello")...); }
//template<int N> auto make2() { return make2(MAKE_INDEX_SEQUENCE(N){}); }
//#define make2(N) make2<N>()
//
//#define S1(X) X
//#define S2(X) X,X
//#define S4(X) X,X,X,X
//#define S8(X) S4(X),S4(X)
//#define S16(X) S8(X),S8(X)
//#define S32(X) S16(X),S16(X)
//#define S64(X) S32(X),S32(X)
//#define S128(X) S64(X),S64(X)
//#define S256(X) S128(X),S128(X)
//#define S512(X) S256(X),S256(X)
//#define TOKEN_PASTE(x,y) x##y
//#define S(N,X) TOKEN_PASTE(S,N)(X)
//#define make3(N) std::tuple<S(N,std::string)>{S(N,"hello")}





template < typename TYPE1,typename TYPE2 >
inline int cmp(const int & i1,const int & i2)
{
   return i1 - i2;
}


template < typename TYPE1,typename TYPE2 >
inline  int cmp(const short & sh1,const short & sh2)
{
   return sh1 - sh2;
}


template < typename TYPE1,typename TYPE2 >
inline int cmp(const char & ch1,const char & ch2)
{
   return ch1 - ch2;
}

template < typename TYPE1,typename TYPE2 >
inline int cmp(const unsigned int & i1,const unsigned int & i2)
{
   return i1 - i2;
}

template < typename TYPE1,typename TYPE2 >
inline  int cmp(const unsigned short & sh1,const short & sh2)
{
   return sh1 - sh2;
}


template < typename TYPE1,typename TYPE2 >
inline  int cmp(const unsigned char & ch1,const unsigned char & ch2)
{
   return ch1 - ch2;
}


template < typename TYPE1,typename TYPE2 >
inline  int cmp(const double & d1,const double & d2)
{
   return sgn(d1 - d2);
}


template < typename TYPE1,typename TYPE2 >
inline  int cmp(const float & f1,const float & f2)
{
   return sgn(f1 - f2);
}
