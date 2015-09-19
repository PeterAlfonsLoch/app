#pragma once


#include <math.h>


class CLASS_DECL_AURA q4 :
   public Q4
{
public:


   q4(double a1,double x1,double y1,double z1)
   {

      a = a1;
      x = x1;
      y = y1;
      z = z1;

   }


   double sqsize()
   {
      
      return a * a + x * x + y * y + z * z;

   }


   double size()
   {

      return sqrt(sqsize());

   }


   q4 operator * (const q4 & q2)
   {
      if(this == &q)
      {
         return operator *(q4(q2));
      }

      q4 q;

      q.a = a * q2.a - x * q2.x - y * q2.y - z * q2.z;
      q.x = a * q2.x + x * q2.a + y * q2.z - z * q2.y;
      q.y = a * q2.y - x * q2.z + y * q2.a + z * q2.x;
      q.z = a * q2.z + x * q2.y - y * q2.x + z * q2.w;

      return q;

   }

   q4 & operator *= (const q4 & q2)
   {

      q4 q1(*this);

      return operator = (q1 * q2);

   }


   q4 & operator = (const q4 & q2)
   {

      a = q2.a;
      x = q2.x;
      y = q2.y;
      z = q2.z;

      return *this;

   }

};
