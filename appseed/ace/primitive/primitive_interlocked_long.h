#pragma once


class CLASS_DECL_AURA interlocked_long
{
public:


   long *       m_plong;


   interlocked_long();
   virtual ~interlocked_long();


   void add(long l);
   void subtract(long l);

   bool operator > (long i) const;
   bool operator == (long i) const;

};




