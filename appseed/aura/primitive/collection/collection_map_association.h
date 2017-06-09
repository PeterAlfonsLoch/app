#pragma once


template <  typename PAIR >
class map_association : 
   public PAIR
{
public:


   typedef PAIR                        pair;
   typedef typename PAIR::TYPE1        TYPE1;
   typedef typename PAIR::ARG_TYPE1    ARG_TYPE1;
   typedef typename PAIR::TYPE2        TYPE2;
   typedef typename PAIR::ARG_TYPE2    ARG_TYPE2;
   

   map_association *                   m_pprev;
   map_association *                   m_pnext;
   map_association *                   m_pnextHash;
   map_association **                  m_ppprevHash;

   map_association()
   {
   }
   map_association(ARG_TYPE1 element1) :
      pair(element1)
   {
   }
   map_association(ARG_TYPE1 element1, ARG_TYPE2 element2):
      pair(element1, element2)
   {
   }

};


template <  typename PAIR >
class map_iterator
{
public:

   typedef map_association < PAIR > TYPE;

   TYPE *                     m_passoc;


   map_iterator()
   {
      m_passoc = NULL;
   }

   map_iterator(TYPE * passoc)
   {
      m_passoc = passoc;
   }

   map_iterator(const map_iterator & iterator)
   {
      m_passoc = iterator.m_passoc;
   }

   bool is_null() const
   {

      return m_passoc == NULL;

   }


   bool is_set() const
   {

      return !is_null();

   }

   map_iterator & operator ++ ()
   {
      m_passoc = m_passoc->m_pnext;
      return *this;
   }

   map_iterator & operator -- ()
   {
      m_passoc = m_passoc->m_pprev;
      return *this;
   }

   bool operator == (const map_iterator & it) const
   {

      return m_passoc == it.m_passoc;

   }


   bool operator != (const map_iterator & it) const
   {

      return !operator == (it);

   }


   bool operator < (const map_iterator & it) const
   {

      return operator!=(it);

   }


   map_iterator & operator = (const map_iterator & it)
   {
      
      m_passoc = it.m_passoc;

      return *this;

   }

   bool operator != (const map_iterator & it)
   {

      return !operator==(it);

   }


   map_iterator operator ++(int)
   {

      map_iterator it = *this;
      operator ++();
      return it;

   }


   map_iterator operator --(int)
   {

      map_iterator it = *this;
      operator --();
      return it;

   }


   TYPE & operator * ()
   {

      return *(operator->());

   }

   TYPE & operator * () const
   {

      return *(operator->());

   }

   TYPE * operator -> ()
   {

      return m_passoc;

   }


   const TYPE * operator -> () const
   {

      return m_passoc;

   }


   operator TYPE * ()
   {

      return m_passoc;

   }


   operator const TYPE * () const
   {

      return m_passoc;

   }




};


template < typename PAIR >
class const_map_iterator 
{
public:


   typedef map_association < PAIR > TYPE;

   const TYPE *   m_passoc;

   const_map_iterator()
   {
      m_passoc = NULL;
   }

   const_map_iterator(const TYPE * passoc)
   {
      m_passoc = passoc;
   }

   const_map_iterator(const map_iterator < PAIR > & map_iterator)
   {
      m_passoc = map_iterator.m_passoc;
   }

   const_map_iterator(const const_map_iterator & const_map_iterator)
   {
      m_passoc = const_map_iterator.m_passoc;
   }

   const_map_iterator & operator ++ ()
   {
      m_passoc = m_passoc->m_pnext;
      return *this;
   }

   const_map_iterator & operator -- ()
   {
      m_passoc = m_passoc->m_pprev;
      return *this;
   }

   bool is_null() const
   {

      return m_passoc == NULL;

   }

   bool is_set() const
   {

      return !is_null();

   }



   bool operator == (const const_map_iterator & it) const
   {
      return m_passoc == it.m_passoc;
   }

   const_map_iterator & operator = (const const_map_iterator & it)
   {
      m_passoc = it.m_passoc;
      return *this;
   }

   bool operator != (const const_map_iterator & it)
   {

      return !operator==(it);

   }

   bool operator < (const const_map_iterator & it) const
   {

      return operator!=(it);

   }


   const_map_iterator operator ++(int)
   {

      const_map_iterator it = *this;
      operator ++();
      return it;

   }


   const_map_iterator operator --(int)
   {

      const_map_iterator it = *this;
      operator --();
      return it;

   }


   const TYPE & operator * ()
   {

      return *(operator->());

   }

   const TYPE & operator * () const
   {

      return *(operator->());

   }


   const TYPE * operator -> ()
   {
      return m_passoc;
   }


   const TYPE * operator -> () const
   {
      return m_passoc;
   }

   operator const TYPE * ()
   {

      return m_passoc;

   }

};



