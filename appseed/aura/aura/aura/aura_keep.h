#pragma once

template <class TYPE> class keep
{
public:


   TYPE    m_keepValue;
   TYPE    m_keepAwayValue;
   TYPE *  m_pKept;
   bool    m_bKept;

   keep(TYPE * pKept,TYPE keepValue,TYPE keepAwayValue,bool bStartKept);
   virtual ~keep();

   void Keep();
   void KeepAway();


};



template <class TYPE>
keep<TYPE>::keep(TYPE * pKept,TYPE keepValue,TYPE keepAwayValue,bool bStartKept):
m_keepValue(keepValue),
m_keepAwayValue(keepAwayValue),
m_pKept(pKept)
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
keep<TYPE>::~keep()
{
   if(m_bKept)
   {
      KeepAway();
   }
}

template <class TYPE>
void keep<TYPE>::Keep()
{
   if(m_pKept)
   {
      *m_pKept = m_keepValue;
      m_bKept = true;
   }
}

template <class TYPE>
void keep<TYPE>::KeepAway()
{
   if(m_pKept)
   {
      *m_pKept = m_keepAwayValue;
      m_bKept = false;
   }
}


class CLASS_DECL_AURA keep_bool :
   public keep < bool >
{
public:

   keep_bool(bool * pKept, bool keepValue = true, bool keepAwayValue = false, bool bStartKept = true) :keep < bool >(pKept, keepValue, keepAwayValue, bStartKept)
   {}
   
   ~keep_bool(){}

};
