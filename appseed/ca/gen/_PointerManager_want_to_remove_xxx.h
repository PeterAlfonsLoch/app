#pragma once

#include "gen/gen_template.h"
#include "collection/collection_template.h"


template < class MANAGED > 
class PointerManager :
   public pointer_array < MANAGED >
{
public:
	PointerManager(MANAGED * pmanaged = NULL, bool bAutoDelete = false);
	virtual ~PointerManager();
   
   virtual void OnPointerClear(MANAGED * p);

   MANAGED * operator ->() const;

   MANAGED * operator = (MANAGED * pmanaged);

   bool  operator != (MANAGED * p);
   bool  operator == (MANAGED * p);

   void Attrib(MANAGED * pmanaged, bool bAutoDelete = false);

protected:

   void _DeferDelete();

   pointer < MANAGED > *   m_pmanaged;
   bool                             m_bAutoDelete;

};

template < class MANAGED > 
PointerManager < MANAGED >::PointerManager(MANAGED * pmanaged, bool bAutoDelete)
{
   m_pmanaged = NULL;
   m_bAutoDelete = false;
   Attrib(pmanaged, bAutoDelete);
}

template < class MANAGED > 
PointerManager < MANAGED >::~PointerManager()
{
   _DeferDelete();
}


template < class MANAGED > 
void PointerManager < MANAGED >::OnPointerClear(MANAGED * p)
{
   if(p == m_pmanaged)
   {
      m_pmanaged = NULL;
   }
}

template < class MANAGED > 
MANAGED * PointerManager < MANAGED >::operator ->() const
{
   return dynamic_cast < MANAGED * > (m_pmanaged);
}

template < class MANAGED > 
void PointerManager < MANAGED >::_DeferDelete()
{
   if(m_pmanaged != NULL)
   {
      m_pmanaged->remove_listener(this);
      if(m_bAutoDelete)
      {
         delete m_pmanaged;
      }
   }
   m_pmanaged = NULL;
}

template < class MANAGED > 
MANAGED * PointerManager < MANAGED >::operator = (MANAGED * pmanaged)
{
   Attrib(pmanaged, m_bAutoDelete);
   return operator->();
}

template < class MANAGED > 
void PointerManager < MANAGED >::Attrib(MANAGED * pmanaged, bool bAutoDelete)
{
   _DeferDelete();
   m_pmanaged = dynamic_cast < pointer < MANAGED > * > (pmanaged);
   m_bAutoDelete = bAutoDelete;
   if(pmanaged != NULL)
      pmanaged->add_listener(this);
}

template < class MANAGED > 
bool PointerManager < MANAGED >::operator != (MANAGED * p)
{
   return p != m_pmanaged;
}

template < class MANAGED > 
bool PointerManager < MANAGED >::operator == (MANAGED * p)
{
   return p == m_pmanaged;
}

