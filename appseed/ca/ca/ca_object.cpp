#include "StdAfx.h"


namespace ca
{


   object::object()
   {
      m_pptraListener = NULL;
   }

   object::~object()
   {
      if(m_papp != NULL)
      {
         try
         {
            m_papp->on_delete(this);
         }
         catch(...)
         {
         }
         try
         {
            if(m_papp->m_psystem != NULL)
            {
                  m_papp->m_psystem->on_delete(this);
            }
         }
         catch(...)
         {
         }
      }

      if(m_pptraListener != NULL)
      {
         for(int i = 0; i < m_pptraListener->get_size(); i++)
         {
            ::ca::ca * plistener = m_pptraListener->element_at(i);
            if(plistener != NULL)
            {
               try
               {
                  plistener->on_delete(this);
               }
               catch(...)
               {
               }
               try
               {
                  if(plistener->m_pptraListened != NULL)
                  {
                     plistener->m_pptraListened->remove(this);
                  }
               }
               catch(...)
               {
               }
            }
         }
         try
         {
            delete m_pptraListener;
         }
         catch(...)
         {
         }
         m_pptraListener = NULL;
      }
      if(m_pptraListened != NULL)
      {
         for(int i = 0; i < m_pptraListened->get_size(); i++)
         {
            ::ca::ca * plistened = m_pptraListened->element_at(i);
            if(plistened != NULL)
            {
               try
               {
                  if(plistened->m_pptraListener != NULL)
                  {
                     plistened->m_pptraListener->remove(this);
                  }
               }
               catch(...)
               {
               }
            }
         }
         try
         {
            delete m_pptraListened;
         }
         catch(...)
         {
         }
         m_pptraListened = NULL;
      }


   }

   object::object(const object & o)
   {
      operator = (o);
   }

   object & object::operator =(const object & o)
   {
      if(this != &o)
      {
         ::ca::ca::operator = (o);
      }
      return *this;
   }

   void object::delete_this()
   {
      if(m_pfactoryitembase != NULL && m_pfactoryitembase->m_pallocator)
      {

         m_pfactoryitembase->m_pallocator->discard(this);
      }
      else if(m_ulFlags & flag_discard_to_factory)
      {
         m_papp->m_psystem->discard_to_factory(this);
      }
//      else if(m_ulFlags & flag_heap_alloc)
      else
      {
         delete this;
      }
   }


   ::ca::ca * object::clone()
   {
      if(m_pfactoryitembase != NULL)
         return m_pfactoryitembase->clone(this);
      else
         return m_papp->m_psystem->clone(this);
   }


   ptra * object::new_ptra()
   {
      return new ptra();
   }


} // namespace ca


