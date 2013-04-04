#pragma once

/*
template < class MANAGED > 
class PointerManager :
   public spa(MANAGED)
{
public:
   PointerManager(MANAGED * pmanaged = ::null(), bool bAutoDelete = false);
   virtual ~PointerManager();
   
   virtual void on_delete(MANAGED * p);

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
   m_pmanaged = ::null();
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
      m_pmanaged = ::null();
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
   if(m_pmanaged != ::null())
   {
      m_pmanaged->remove_listener(this);
      if(m_bAutoDelete)
      {
         delete m_pmanaged;
      }
   }
   m_pmanaged = ::null();
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
   if(pmanaged != ::null())
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

*/