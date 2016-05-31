#pragma once


template <class TYPE> class restore
{
public:


   TYPE *  m_pKept;
   TYPE    m_valueRestore;

   restore(TYPE * pKept);
   restore(TYPE * pKept,const TYPE & valueRestore);
   virtual ~restore();

   void Restore();

};


template <class TYPE>
restore<TYPE>::restore(TYPE * pKept):
restore(pKept, *pKept)
{
   
}


template <class TYPE>
restore<TYPE>::restore(TYPE * pKept,const TYPE & valueRestore) : 
m_pKept(pKept),
m_valueRestore(valueRestore)
{
   
}



template <class TYPE>
restore<TYPE>::~restore()
{

   Restore();
   
}


template <class TYPE>
void restore<TYPE>::Restore()
{

   *m_pKept = m_valueRestore;

}



#define RESTORE(var) ::restore < decltype(var) > TOKEN_CONCAT(restore, __COUNTER__) (&var);