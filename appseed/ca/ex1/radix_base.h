#pragma once


template < class T >
class base 
{
public:


   template < class T2 >
   inline static bool bases(T2 * p) 
   {
      return dynamic_cast < T * > (p) != NULL; 
   }


   template < class T2 >
   inline static bool bases(const ::gen::holder < T2 > & holder) 
   { 
      return dynamic_cast < T * > ((T2 *) holder) != NULL; 
   }


};


