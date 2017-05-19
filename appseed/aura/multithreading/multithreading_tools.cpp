
thread_tools::thread_tools(::aura::application * papp) :
   ::object(papp)
{
   
   m_cCount                         = 0;
   m_cIteration                     = 0;
   m_cSpan                          = 0;

   int cOrder = get_current_process_affinity_order();

   //cOrder = 1;

   while (m_threada.get_size() < cOrder)
   {

      ::tool_thread * ptoolthread = canew(::tool_thread(this));

      m_synca.add(&ptoolthread->m_evReady);

      ptoolthread->m_iThread = m_threada.get_count();

      ptoolthread->m_dwThreadAffinityMask = translate_processor_affinity(ptoolthread->m_iThread);

      m_threada.add(ptoolthread);

//      ptoolthread->begin(::multithreading::priority_highest);
      //ptoolthread->begin();
      ptoolthread->begin(::multithreading::priority_time_critical);
//      ptoolthread->begin();

   }


}


thread_tools::~thread_tools()
{


}



bool thread_tools::prepare(::thread::e_op eop, ::count cIteration)
{

   for (auto & pthread : m_threada)
   {

      pthread->reset();

   }

   if (eop == ::thread::op_pred || eop == ::thread::op_fork_count)
   {

      m_cCount = 0;

   }
   else
   {

      m_cCount = MIN(m_threada.get_count(), cIteration);

   }

   m_eop = eop;

   m_cIteration = cIteration;

   m_cSpan = MAX(1, cIteration / get_count());

   return true;

}


//bool thread_toolset::add_tool(::thread_tool * ptool)
//{
//
//   add(ptool);
//
//   ptool->m_ptoolset = this;
//
//   return true;
//
//}


bool thread_tools::add_pred(::pred_holder_base * ppred)
{

   ASSERT((m_eop == ::thread::op_pred || m_eop == ::thread::op_fork_count) && !is_full());

   if (is_full())
   {

      return false;

   }

   m_threada[m_cCount]->set_pred(ppred);

   m_cCount++;

   return true;

}


bool thread_tools::start()
{

   ASSERT(m_cCount > 0);

   if (m_cCount <= 0)
   {

      return false;

   }

   m_cSpan = m_cIteration / m_cCount;

   for (index i = 0; i < m_cCount; i++)
   {

      m_threada[i]->start();

   }

   return true;

}


bool thread_tools::wait()
{

   multi_lock ml(m_cCount, m_synca);

   return ml.lock().succeeded();

}


bool thread_tools::operator()()
{

   start();
   wait();

   return true;

}

bool thread_tools::select_toolset(thread_toolset * pset)
{

   m_ptoolset = pset;

   return true;

}











tool_thread::tool_thread(::thread_tools * ptools) :
   object(ptools->get_app()),
   ::thread(ptools->get_app()),
   m_evStart(ptools->get_app()),
   m_evReady(ptools->get_app()),
   m_ptools(ptools)
{

   m_iIndex = 0;
   m_evStart.ResetEvent();
   m_evReady.ResetEvent();

}


//bool tool_thread::set_tool(::thread_tool * ptool)
//{
//
//   try
//   {
//      
//      ptool->m_pthreadtool = this;
//      
//      m_ptool = ptool;
//
//      return true;
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return false;
//
//
//}


bool tool_thread::set_pred(::pred_holder_base * ppred)
{

   try
   {

      ppred->m_ptoolthread = this;

      m_ppred = ppred;

      return true;

   }
   catch (...)
   {

   }

   return false;

}






int tool_thread::run()
{

   while (true)
   {

      m_evStart.wait();

      m_evStart.ResetEvent();

      if (m_ptools->m_eop == ::thread::op_pred || m_ptools->m_eop == ::thread::op_fork_count)
      {

         m_ppred->run();

      }
      else if (m_ptools->m_eop == ::thread::op_tool)
      {

         m_ptools->m_ptoolset->element_at(m_iThread)->run();

      }

      m_evReady.SetEvent();

   }

   return 0;

}


void tool_thread::reset()
{

   m_evStart.ResetEvent();

   m_evReady.ResetEvent();

}


void tool_thread::start()
{

   m_evStart.SetEvent();

}



CLASS_DECL_AURA ::thread_tools & get_thread_tools()
{

   return  ::get_thread()->tools();

}


CLASS_DECL_AURA ::thread_toolset & get_thread_toolset(::thread::e_tool etool)
{

   return ::get_thread()->toolset(etool);

}



thread_toolset::thread_toolset(::thread_tools * ptools) :
   object(ptools->get_app()),
   m_pthreadtools(ptools)
{


}

bool thread_toolset::add_tool(::thread_tool * ptool)
{

   ptool->m_ptoolset = this;

   add(ptool);

   return true;

}

bool thread_toolset::prepare(::count cIteration)
{

   if (!m_pthreadtools->prepare(::thread::op_tool, cIteration))
   {

      return false;

   }

   return true;

}


//pred_set::pred_set(::thread_tools * ptools) :
//   object(ptools->get_app()),
//   m_pthreadtools(ptools)
//{
//
//
//}
//
//bool pred_set::add_pred(::pred_holder_base * ppred)
//{
//
//   ppred->m_pset = this;
//
//   add(ppred);
//
//   return true;
//
//}
//
//
//
//
