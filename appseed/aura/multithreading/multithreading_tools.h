#pragma once



class tool_thread :
   virtual public ::thread
{
public:


   e_op                    m_eop;
   manual_reset_event      m_evStart;
   manual_reset_event      m_evReady;
   void *                  m_pdata;
   sp(::thread_tool)       m_ptool;
   sp(::pred_holder_base)  m_ppredholder;
   index                   m_cCount;
   index                   m_iIndex;
   ::count                 m_iScan;
   ::count                 m_iCount;
   sp(object)              m_pholdref;


   tool_thread(::aura::application * papp);

   virtual int run() override;


};


class thread_tool :
   virtual public ::object
{
public:

   tool_thread * m_ptoolthread;

   virtual void run() {}

};


class thread_tools :
   virtual public ::object
{
public:


   spa(thread)             m_threada;
   sync_object_ptra        m_synca;
   ::count                 m_cCount;
   ::count                 m_cIteration;
   ::count                 m_cSpan;


   thread_tools(::aura::application * papp);
   virtual ~thread_tools();

   
   static sp(thread_tools) & get();


   ::count get_count() { return m_threada.get_count(); }
   bool is_full() { return m_cCount >= m_threada.get_count(); }


   bool prepare(::thread::e_op eop, ::count cIteration = 0);
   bool add_tool(::thread_tool * ptool);
   bool add_pred(::pred_holder_base * pbase);
   bool execute();

};




template < typename PRED >
::count fork_count_end(::aura::application * papp, ::count iCount, PRED pred, index iStart = 0)
{

   if (iCount <= 0)
   {

      return -1;

   }

   sp(::thread_tools) & ptools = ::thread_tools::get();

   if (!ptools->prepare(::thread::op_fork_count, iCount - iStart))
   {

      return -1;

   }

   index i = 0;

   sync_object_ptra ptra;

   ::count iScan = MAX(1, MIN(iCount - iStart, ptools->get_count()));

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      sp(pred_holder_base) pbase = canew(forking_count_pred < PRED >(papp, iOrder, iOrder + iStart, iScan, iCount, pred));

      ptools->add_pred(pbase);

   }

   if (!ptools->execute())
   {

      return -1;

   }

   return iScan;

}





