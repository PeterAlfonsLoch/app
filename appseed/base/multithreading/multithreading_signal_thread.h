#pragma once


template < class DST, class SRC >
class signal_thread :
   public thread
{
public:


   DST * m_psignalizableDst;
   void (DST::* m_pfnDst)(signal_details *);
   SRC * m_psignalizableSrc;
   void (SRC::* m_pfnSrc)(signal_details *);
   signal_details * m_pobj;


   signal_thread(sp(::base::application) papp,
      DST * psignalizableDst, void (DST::* pfnDst)(signal_details *),
      SRC * psignalizableSrc, void (SRC::* pfnSrc)(signal_details *),
      signal_details * pobj) :
      element(papp),
      thread(papp)
   {
      m_bAutoDelete = true;
      m_pimpl->m_bAutoDelete = true;
      m_psignalizableDst = psignalizableDst;
      m_pfnDst = pfnDst;
      m_psignalizableSrc = psignalizableSrc;
      m_pfnSrc = pfnSrc;
      m_pobj = pobj;
   }


   int32_t run()
   {
      try
      {
         (m_psignalizableSrc->*m_pfnSrc)(m_pobj);
         (m_psignalizableDst->*m_pfnDst)(m_pobj);
      }
      catch (...)
      {
      }
      delete m_pobj;
      return 0;
   }


};

template < class DST, class SRC >
void emit(sp(::base::application) papp,
   DST * psignalizableDst, void (DST::* pfnDst)(signal_details *),
   SRC * psignalizableSrc, void (SRC::* pfnSrc)(signal_details *),
   signal_details * pobj)
{
   signal_thread < DST, SRC > * pthread = new signal_thread < DST, SRC >(papp, psignalizableDst, pfnDst, psignalizableSrc, pfnSrc, pobj);
   pthread->begin();
}

