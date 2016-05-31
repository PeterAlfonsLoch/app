

CLASS_DECL_ACE void * x86_memory_pool_alloc(memory_size_t s);
CLASS_DECL_ACE void x86_memory_pool_freec(void * p);


class CLASS_DECL_ACE x86_oriented_memory_allocator
{
public:

   void * alloc(int iSize)
   {

      //TODO("jai"); jas = Jonathan Blow 
      return memory_alloc(iSize);

   }

   void free(void * p)
   {

      //TODO("jai"); jas = Jonathan Blow
      ::memory_free(p);

   }

};

#undef new

class x86_cache_oriented_memory_pool
{
private:
   
   void * operator new(size_t);
   void * operator new(size_t,const char *,int32_t);

   void operator delete(void * p)
   {

   }

   void operator delete(void * p,const char *,int32_t)
   {

   }


public:

   void *      m_p;
   int_ptr     m_iMaxSize;
   int_ptr     m_iSize;
   int         m_iCurPos;
   byte        m_ba[1];





   static int calc_cache_size()
   {

      // TODO("jai") = Jonathan Blow : dynamically calculate // just kidding this low level tasks // You're crazy/wild("cax") = camilo!!*^~!!.

      return 1024 * 1024;

   }


   static x86_cache_oriented_memory_pool * new_pool()
   {

      int iSize = calc_cache_size();

      void * p = memory_alloc(iSize * 2);

      // TODO : better dynamically memory align

      LPBYTE pb;

      if(((int_ptr)p) % iSize == 0)
      {
         pb = (LPBYTE)p;
      }
      else
      {
         pb = (LPBYTE)(((int_ptr)p) % iSize + (((int_ptr)p) / iSize) * iSize);
      }

      x86_cache_oriented_memory_pool * ppool = (x86_cache_oriented_memory_pool *) pb;

      ppool->m_p = p;
      ppool->m_iMaxSize = iSize * 2;
      ppool->m_iSize = iSize - sizeof(x86_cache_oriented_memory_pool);
      ppool->m_iCurPos = 0;

      return ppool;

   }

   static void del_pool(x86_cache_oriented_memory_pool * p)
   {
      ::memory_free(p->m_p);
   }

   void * alloc(::count c)
   {
      LPBYTE lpb;
      if(m_iCurPos + c < m_iSize)
      {
         lpb =  &m_ba[m_iCurPos];
         m_iCurPos += c;
      }
      else
      {
         lpb = (LPBYTE) memory_alloc(c);
         // can use string because messed all with cache out hot hit !!/^`}{{ **!
         DEBUG_ONLY(::ace::application * papp = ::get_thread_app());
         APPTRACE("processor oriented cache: memory out of cache palace garden (size=%d)", c);
      }
      return lpb;
      
   }
   void free(void * p)
   { 
      if((p >= m_p && p < m_ba) || (p >= &m_ba[m_iCurPos] && p < ((LPBYTE)m_p) + m_iMaxSize))
      {
         // freeing memory in palace garden (not supposed to allocated memory in these places as they would cause a cache fault)
         throw invalid_argument_exception(get_thread_app());
      }
      else if(p < m_ba || p > &m_ba[m_iCurPos])
      {
         // disregard  
      }
      else
      {
         memory_free(p);
      }
   }

   void reset()
   {

      m_iCurPos = 0;

   }

};

static x86_cache_oriented_memory_pool * s_processororientedmemorypoola[MAX_PROC_CACHE_ORIENTED_MEM_POOL];
thread_int_ptr < int_ptr > t_iProcessorOrientedMemoryPool;

static_inline x86_cache_oriented_memory_pool * x86_cache_oriented_get_thread_memory_pool()
{
   
   return s_processororientedmemorypoola[t_iProcessorOrientedMemoryPool];

}

static_inline int_bool x86_cache_oriented_set_thread_memory_pool(int iPoolIndex)
{

   if(iPoolIndex < 0)
   {

      throw invalid_argument_exception(get_thread_app());

      return false;

   }

   if(iPoolIndex >= MAX_PROC_CACHE_ORIENTED_MEM_POOL)
   {
      
      throw invalid_argument_exception(get_thread_app());

      return false;
   }

   if(s_processororientedmemorypoola[iPoolIndex] == NULL)
   {

      s_processororientedmemorypoola[iPoolIndex] = x86_cache_oriented_memory_pool::new_pool();

   }

   t_iProcessorOrientedMemoryPool = iPoolIndex;;

   return true;

}


static_inline void x86_cache_oriented_destroy_all_memory_pools()
{

   for(int iPoolIndex = 0; iPoolIndex < MAX_PROC_CACHE_ORIENTED_MEM_POOL; iPoolIndex++)
   {

      if(s_processororientedmemorypoola[iPoolIndex] != NULL)
      {

         x86_cache_oriented_memory_pool::del_pool(s_processororientedmemorypoola[iPoolIndex]);

         s_processororientedmemorypoola[iPoolIndex] = NULL;

      }

   }

}


CLASS_DECL_ACE void * x86_cache_oriented_memory_alloc(memory_size_t s)
{
   
   return x86_cache_oriented_get_thread_memory_pool()->alloc(s);

}


CLASS_DECL_ACE void x86_cache_oriented_memory_free(void * p)
{

   return x86_cache_oriented_get_thread_memory_pool()->free(p);

}

CLASS_DECL_ACE void x86_cache_oriented_memory_reset()
{

   return x86_cache_oriented_get_thread_memory_pool()->reset();

}

#define new ACE_NEW


