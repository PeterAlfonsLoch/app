#pragma once

template <class TYPE> class keeper  
{
public:
   

   TYPE    m_keepValue;
   TYPE    m_keepAwayValue;
   TYPE *  m_pKept;
   bool    m_bKept;

   
   keeper(TYPE * pKept, TYPE keepValue, TYPE keepAwayValue, bool bStartKept);
   virtual ~keeper();

   void Keep();
   void KeepAway();


};

template <class TYPE>
keeper<TYPE>::keeper(TYPE * pKept, TYPE keepValue, TYPE keepAwayValue, bool bStartKept) :
   m_pKept(pKept),
   m_keepValue(keepValue),
   m_keepAwayValue(keepAwayValue)
{
   if(bStartKept)
   {
      m_bKept = false;
      Keep();
   }
   else
   {
      m_bKept = true;
      KeepAway();
   }

}
template <class TYPE>
keeper<TYPE>::~keeper()
{
   if(m_bKept)
   {
      KeepAway();
   }
}

template <class TYPE>
void keeper<TYPE>::Keep()
{
   if(m_pKept)
   {
      *m_pKept = m_keepValue;
      m_bKept = true;
   }
}

template <class TYPE>
void keeper<TYPE>::KeepAway()
{
   if(m_pKept)
   {
      *m_pKept = m_keepAwayValue;
      m_bKept = false;
   }
}
