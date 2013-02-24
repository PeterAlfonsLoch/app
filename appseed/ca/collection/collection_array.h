#pragma once


namespace ca
{

   template < class A, class T >
   A array(T t1)
   {
      A a;
      a.add(t1);
      return a;
   }

} // namespace ca
