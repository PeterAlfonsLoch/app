#pragma once


int32_t AmIBeingDebugged();


#include "ios_ns_exception.h"


#include "ios_thread.h"

/*#ifdef cplusplus

template < class T >
class thread_pointer
{
public:
    
    
    const char * name;
    
    thread_pointer(const char * pszName)
    {
        name = pszName;
    }
    
    
    operator T *()
    {
        
        return (T *) get_thread_ptr(name);
        
    }
    
    T * operator ->()
    {
        return operator T *();
    }
    
    thread_pointer & operator = (T * pt)
    {
        
        set_thread_ptr(name, pt);
        
        return *this;
        
    }
    
};


template < class T >
class thread_var
{
public:
    
    const char * name;
    
    thread_var(const char * pszName)
    {
        name = pszName;
    }
    
    
    operator T ()
    {
        
        return (T) get_thread_int(name);
        
    }
    
    thread_var & operator = (T t)
    {
        
        set_thread_int(name, t);
        
        return *this;
        
    }
    
    
};


#endif



*/