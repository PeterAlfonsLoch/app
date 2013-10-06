#pragma once


class CLASS_DECL_c memory_exception : 
   virtual public simple_exception
{
public:


   memory_exception(sp(base_application) papp);
   memory_exception(sp(base_application) papp, const char * pszMessage);
   virtual ~memory_exception();


};


#ifndef SOLARIS


namespace std
{

    
        typedef ::memory_exception bad_alloc;
        
        
} // namespace std



#endif




