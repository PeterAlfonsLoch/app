

thread_tools::thread::thread(::aura::application * papp) :
   object(papp),
   ::thread(papp),
   m_evStart(papp),
   m_evReady(papp)
{
   m_iIndex = 0;
   m_evStart.ResetEvent();
   m_evReady.ResetEvent();
}



sp(thread_tools) & thread_tools::get()
{

   sp(thread_tools) & ptools = ::get_thread()->m_ptools;

   if (ptools.is_null())
   {

      ptools = new thread_tools;

      while (ptools->m_threada.get_size() < get_processor_count())
      {

         thread_tools::thread * p = new thread_tools::thread(::get_thread_app());

         ptools->m_synca.add(&p->m_evReady);

         ptools->m_threada.add(p);

         p->begin();

      }

   }

   return ptools;

}


::count thread_tools::get_count()
{

   return m_threada.get_count();

}

bool thread_tools::is_full()
{

   return m_cCount >= m_thread_get_count();

}

void thread_tools::prepare(e_op eop, ::count cIteration)
{

   for (auto & pthread : m_threada)
   {

      p->m_evStart.ResetEvent();

      p->m_evReady.ResetEvent();

   }

   m_cCount = 0;

   m_eop = eop;

   m_cIteration = cIteration;

   m_cSpan = MAX(1, cIteration / get_count());

}


bool thread_tools::add_tool(::thread_tool * ptool)
{

   ASSERT(m_eop == op_tool && !is_full());

   if (is_full())
   {

      return false;

   }

   m_threada[m_cCount]->m_ptool = ptool;

   m_cCount++;

   return true;

}


bool thread_tools::add_pred(::pred_holder_base * pbase)
{

   ASSERT((m_eop == op_pred || m_eop == op_fork_count) && !is_full());

   if (is_full())
   {

      return false;

   }

   m_threada[m_cCount]->m_ppred = pbase;

   m_cCount++;

   return true;

}


void thread_tools::execute()
{

   ASSERT(m_cCount > 0);

   if (m_cCount <= 0)
   {

      return;

   }

   m_cSpan = cIteration / m_cCount;

   for (index i = 0; i < m_cCount; i++)
   {

      m_threada[i]->m_evStart.SetEvent();

   }

   multi_lock ml(m_cCount, m_synca, true);

}






int thread_tools::thread::run()
{
   
   ::multithreading::set_priority(::multithreading::priority_time_critical);

   while (true)
   {
      m_evStart.wait();
      m_evStart.ResetEvent();

      if (m_eop == op_pred || m_eop == op_fork_count)
      {

         m_ppredholder->run();

      }
      else if (m_eop == op_tool)
      {

         m_ptool->run();

      }

      m_evReady.SetEvent();

   }

   return 0;

}





