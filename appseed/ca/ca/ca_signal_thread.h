#pragma once

namespace ca
{

   template < class DST, class SRC >
   class signal_thread :
      public ::ca::thread
   {
   public:


      DST * m_psignalizableDst;
      void (DST::* m_pfnDst)(::ca::signal_object *);
      SRC * m_psignalizableSrc;
      void (SRC::* m_pfnSrc)(::ca::signal_object *);
      ::ca::signal_object * m_pobj;
      
      
      signal_thread(::ca::application * papp,
         DST * psignalizableDst, void (DST::* pfnDst)(::ca::signal_object *), 
         SRC * psignalizableSrc, void (SRC::* pfnSrc)(::ca::signal_object *), 
         ::ca::signal_object * pobj) :
         ca(papp),
         thread(papp)
      {
         m_bAutoDelete        = true;
         m_p->m_bAutoDelete   = true;
         m_psignalizableDst   = psignalizableDst;
         m_pfnDst             = pfnDst;
         m_psignalizableSrc   = psignalizableSrc;
         m_pfnSrc             = pfnSrc;
         m_pobj               = pobj;
      }


      int32_t run()
      {
         try
         {
            (m_psignalizableSrc->*m_pfnSrc)(m_pobj);
            (m_psignalizableDst->*m_pfnDst)(m_pobj);
         }
         catch(...)
         {
         }
         delete m_pobj;
         return 0;
      }


   };

   template < class DST, class SRC >
   void emit(::ca::application * papp,
      DST * psignalizableDst, void (DST::* pfnDst)(::ca::signal_object *), 
      SRC * psignalizableSrc, void (SRC::* pfnSrc)(::ca::signal_object *), 
      ::ca::signal_object * pobj)
   {
      signal_thread < DST, SRC > * pthread = new signal_thread < DST, SRC > (papp, psignalizableDst, pfnDst, psignalizableSrc, pfnSrc, pobj);
      pthread->begin();
   }

} // namespace ca