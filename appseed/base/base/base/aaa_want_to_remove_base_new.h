#define __NORMAL_BLOCK    1



#if defined(SOLARIS)

#define inplace_new_throw_spec
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()

#elif defined(MACOS)

#define inplace_new_throw_spec throw ()
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()

#else

#define inplace_new_throw_spec
#define new_throw_spec
#define del_throw_spec 

#endif


