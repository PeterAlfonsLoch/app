#pragma once


inline void * fixed_alloc_sync::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   int32_t i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   void * p = NULL;
   m_protectptra.get_data()[i]->lock();
   try
   {
      p = m_allocptra.get_data()[i]->Alloc();
   }
   catch(...)
   {
   }
   m_protectptra.get_data()[i]->unlock();
   if(p == NULL)
      return NULL;
   ((int32_t *) p)[0] = i;
   return &((int32_t *)p)[1];
}

inline void fixed_alloc_sync::Free(void * p)
{
   if (p == NULL)
      return;
   int32_t i = ((int32_t *)p)[-1];
   m_protectptra.get_data()[i]->lock();
   try
   {
      m_allocptra.get_data()[i]->Free(&((int32_t *)p)[-1]);
   }
   catch(...)
   {
   }
   m_protectptra.get_data()[i]->unlock();
}



inline void * fixed_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   int32_t i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   void * p  = m_allocptra.get_data()[i]->Alloc();

   ((int32_t *) p)[0] = i;

   return &((int32_t *)p)[1];

}

inline void fixed_alloc::Free(void * p)
{

   if (p == NULL)
      return;

   int32_t i = ((int32_t *)p)[-1];

   m_allocptra.get_data()[i]->Free(&((int32_t *)p)[-1]);

}






extern CLASS_DECL_AXIS fixed_alloc_array g_fixedalloca;
