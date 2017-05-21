#pragma once


CLASS_DECL_AURA int get_current_process_affinity_order();

#undef new

#define new AURA_NEW

template < typename PRED >
class forking_thread:
   virtual public thread
{
public:

   PRED m_pred;

   sp(object) m_pholdref;

   forking_thread(::aura::application * papp, sp(object) pholdref, PRED pred) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred)
   {

   }

   forking_thread(::aura::application * papp,PRED pred) :
      object(papp),
      thread(papp),
      m_pred(pred)
   {

   }


   virtual ~forking_thread()
   {

   }

   int32_t run()
   {

      m_pred();

      return 0;

   }

};


template < typename PRED >
::thread * fork(::aura::application * papp, sp(object) pholdref, PRED pred)
{

   auto pforkingthread = canew(forking_thread < PRED >(papp, pholdref, pred));

   ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

   pthread->begin();

   return pthread;

}







template < typename PRED >
::thread * fork(::aura::application * papp, PRED pred)
{

   auto pforkingthread = canew(forking_thread < PRED >(papp, pred));

   ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

   pthread->begin();

   return pthread;

}


template < typename PRED >
inline ::thread * object::fork(PRED pred)
{

   return ::fork(get_app(),pred);

}


template < typename T >
inline void fork_release(::aura::application * papp, sp(T) & t)
{

   try
   {

      T * pt;

      pt = t.m_p;

      pt->add_ref();

      t.release();

      ::fork(papp, [&]()
      {

         ::release(pt);

      });

   }
   catch (...)
   {


   }

}

CLASS_DECL_AURA DWORD_PTR translate_processor_affinity(int i);



template < typename PRED >
class forking_count_pred :
   virtual public pred_holder_base
{
public:

   PRED m_pred;
   index m_iOrder;
   index m_iIndex;
   index m_iScan;
   ::count m_cCount;

   
   forking_count_pred(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count cCount, PRED pred) :
      ::object(papp),
      ::pred_holder_base(papp),
      m_pred(pred)
   {
      m_iOrder = iOrder;
      m_iIndex = iIndex;
      m_iScan = iScan;
      m_cCount = cCount;

   }

   virtual void run()
   {
   
      m_pred(m_iOrder, m_iIndex, m_cCount, m_iScan);
   
   }

};


template < typename PRED >
class forking_count_thread :
   virtual public thread
{
public:

   PRED     m_pred;

   

   index    m_iOrder;
   index    m_iIndex;
   ::count  m_iScan;
   ::count  m_iCount;

   sp(object) m_pholdref;

   forking_count_thread(::aura::application * papp, sp(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred),
      m_iOrder(iOrder),
      m_iIndex(iIndex),
      m_iScan(iScan),
      m_iCount(iCount)
   {
      construct();
   }

   forking_count_thread(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
      object(papp),
      thread(papp),
      m_pred(pred),
      m_iOrder(iOrder),
      m_iIndex(iIndex),
      m_iScan(iScan),
      m_iCount(iCount)
   {
      construct();
   }

   void construct()
   {

      m_dwThreadAffinityMask = translate_processor_affinity(m_iOrder);

   }

   virtual ~forking_count_thread()
   {

   }

   int32_t run()
   {

      m_pred(m_iOrder, m_iIndex, m_iCount, m_iScan);

      return 0;

   }

};



template < typename PRED >
::count fork_count(::aura::application * papp, ::count iCount, PRED pred, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == NULL || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));
     
   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto pforkingthread = canew(forking_count_thread < PRED >(papp, iOrder, iOrder + iStart, iScan, iCount, pred));

      ::thread * pthread = dynamic_cast <::thread *> (pforkingthread);

      pthread->begin();

   }

   return iScan;

}

CLASS_DECL_AURA uint32_t random_processor_index_generator();

template < typename PRED >
spa(::thread) fork_proc(::aura::application * papp, PRED pred, index iCount = -1)
{

   spa(::thread) threadptra;

   int iProcCount = get_current_process_affinity_order();

   if (iCount < 0 || iCount > iProcCount)
   {

      iCount = iProcCount;

   }

   iCount = MAX(1, iCount);

   if (::get_thread() == NULL || ::get_thread()->m_bAvoidProcFork)
   {

      iCount = 1;

   }

   for (index iProcessor = 0; iProcessor < iCount; iProcessor++)
   {

      auto pforkingthread = canew(forking_thread < PRED >(papp, pred));

      ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

      pthread->m_dwThreadAffinityMask = translate_processor_affinity(random_processor_index_generator() % iProcCount);

      pthread->m_bThreadToolsForIncreasedFps = false;

      pthread->m_bAvoidProcFork = true;

      threadptra.add(pthread);

      pthread->begin();

   }

   return threadptra;

}



//template < typename PRED >
//class forking_count_thread_end :
//   virtual public forking_count_thread < PRED >
//{
//public:
//
//   manual_reset_event m_evEnd;
//
//   forking_count_thread_end(::aura::application * papp, sp(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
//      object(papp),
//      thread(papp),
//      forking_count_thread<PRED>(papp, pholdref, iOrder, iIndex, iScan, iCount, pred),
//      m_evEnd(papp)
//   {
//      construct();
//   }
//
//   forking_count_thread_end(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
//      object(papp),
//      thread(papp),
//      forking_count_thread<PRED>(papp, iOrder, iIndex, iScan, iCount, pred),
//      m_evEnd(papp)
//   {
//      construct();
//   }
//
//   void construct()
//   {
//
//      m_evEnd.ResetEvent();
//
//      forking_count_thread<PRED>::construct();
//
//   }
//
//   virtual ~forking_count_thread_end()
//   {
//
//   }
//
//   int32_t run()
//   {
//
//      try
//      {
//
//         m_pred(this->m_iOrder, this->m_iIndex, this->m_iCount, this->m_iScan);
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//      m_evEnd.SetEvent();
//
//      return 0;
//
//   }
//
//};







//class pred_base
//{
//public:
//
//   virtual void run() = 0;
//
//};
//
//template < typename PRED >
//class pred_holder
//{
//public:
//
//   PRED m_pred;
//
//   virtual void run()
//   {
//
//      m_pred();
//
//   }
//
//};



//class pred_holder_ptra :
//   virtual public array < pred_holder_base * >
//{
//public:
//
//   pred_holder_ptra(::aura::application * papp) :
//      object(papp)
//   {
//
//
//   }
//
//   virtual ~pred_holder_ptra()
//   {
//
//   }
//
//   virtual ::count release()
//   {
//      ::count c = m_countReference - 1;
//      if (m_countReference >= 2)
//      {
//         dec_ref();
//      }
//      else if (m_countReference == 1)
//      {
//
//         ::fork(get_app(), [&]()
//         {
//
//            for (index i = 0; i < get_size(); i++)
//            {
//
//               try
//               {
//
//                  element_at(i)->run();
//
//               }
//               catch (...)
//               {
//
//                  break;
//
//               }
//
//            }
//
//            for (index i = 0; i < get_size(); i++)
//            {
//
//               try
//               {
//
//                  delete element_at(i);
//
//               }
//               catch (...)
//               {
//
//                  break;
//
//               }
//
//            }
//
//            delete this;
//
//         });
//
//
//      }
//
//      return c;
//
//   }
//
//   template < typename PRED >
//   sp(pred_holder_ptra) then(PRED pred)
//   {
//
//      add(new pred_holder <PRED>(get_app(), pred));
//
//      return this;
//
//   }
//
//};
//
//
//template < typename PRED >
//sp(pred_holder_ptra) then(::aura::application * papp, PRED pred)
//{
//
//   sp(pred_holder_ptra) pptra = canew(pred_holder_ptra(papp));
//
//   pptra->add(new pred_holder <PRED>(papp, pred));
//
//   return pptra;
//
//}


