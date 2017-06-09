#pragma once


#include "collection_iterable.h"


template < class TYPE, class ARG_TYPE  = const TYPE&, class LIST_TYPE = ::list < TYPE, ARG_TYPE > >
class list :
   public LIST_TYPE
{
public:
  
   typedef typename LIST_TYPE::iterator iterator;

   typedef typename LIST_TYPE::const_iterator const_iterator;

   typedef typename LIST_TYPE::node node;


   list();
   list(const list & array);


   iterator find_first(const TYPE &t, iterator pos = NULL, iterator posLast = NULL);
   iterator find_last(const TYPE &t, iterator pos = NULL, iterator posLast = NULL);

   const_iterator find_first(const TYPE &t, const_iterator pos = NULL, const_iterator posLast = NULL) const;
   const_iterator find_last(const TYPE &t, const_iterator pos = NULL, const_iterator posLast = NULL) const;

   ::count get_count() const;
   ::count get_count(const TYPE & t, const_iterator start = NULL, const_iterator last = NULL, ::count countMax = -1) const;
   bool contains(const TYPE & t, const_iterator posStart = NULL, const_iterator posLast = NULL, ::count countMin = 1, ::count countMax = -1) const;
   bool rcontains(const TYPE & t, const_iterator posStart = NULL, const_iterator posLast = NULL, ::count countMin = 1, ::count countMax = -1) const;
   ::count remove(const TYPE & t, iterator pos = NULL, iterator posLast = NULL, ::count countMin = 0, ::count countMax = -1);
   //::count rremove(const TYPE & t, iterator pos = NULL, iterator posLast = NULL, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const list & l);



   // add
   bool add_tail_unique(ARG_TYPE t);
   bool add_head_unique(ARG_TYPE t);


   // set
   void merge_tail(const list & l); // add
   void merge_head(const list & l); // add

   // set operators
   list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const TYPE & t);
   list< TYPE, ARG_TYPE, LIST_TYPE > & operator &= (const list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   list< TYPE, ARG_TYPE, LIST_TYPE > & operator |= (const list< TYPE, ARG_TYPE, LIST_TYPE > & l); // add

   list< TYPE, ARG_TYPE, LIST_TYPE > operator -(const list< TYPE, ARG_TYPE, LIST_TYPE > & l) const;

};




template < class TYPE, class ARG_TYPE, class LIST_TYPE>
list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
list()
{
}

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
list(const list<  TYPE,  ARG_TYPE,  LIST_TYPE> & l) :
LIST_TYPE(l)
{
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename list < TYPE, ARG_TYPE, LIST_TYPE >::const_iterator list < TYPE, ARG_TYPE, LIST_TYPE >::
find_first(const TYPE & t, const_iterator pos, const_iterator posLast) const
{
   
   if (pos == end())
   {
    
      pos = this->begin();

   }
   
   for(; pos != posLast; pos++)
   {
      
      if (*pos == t)
      {
         
         return pos;

      }
      
   }

   return NULL;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename list < TYPE, ARG_TYPE, LIST_TYPE >::const_iterator list < TYPE, ARG_TYPE, LIST_TYPE >::
find_last(const TYPE & t, const_iterator pos, const_iterator posLast) const
{

   if (pos == this->end())
   {

      pos = this->upper_bound();

   }

   if (posLast == this->end())
   {

      posLast = this->begin();

   }

   if (pos == this->end())
   {

      return this->end();

   }
   
   while(true)
   {

      if (*pos == t)
      {

         return pos;

      }
      
      if (pos == posLast)
      {

         break;

      }

   } 

   return pos;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename list < TYPE, ARG_TYPE, LIST_TYPE >::iterator list < TYPE, ARG_TYPE, LIST_TYPE >::
find_first(const TYPE & t, iterator pos, iterator posLast)
{

   if (pos == end())
   {

      pos = this->begin();

   }

   for (; pos != posLast; pos++)
   {

      if (*pos == t)
      {

         return pos;

      }

   }

   return NULL;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename list < TYPE, ARG_TYPE, LIST_TYPE >::iterator list < TYPE, ARG_TYPE, LIST_TYPE >::
find_last(const TYPE & t, iterator pos, iterator posLast)
{

   if (pos == NULL)
   {

      pos = this->upper_bound();

   }

   if (posLast == NULL)
   {

      posLast = this->begin();

   }

   if (pos == this->end())
   {

      return this->end();

   }

   while (true)
   {

      if (*pos == t)
      {

         return pos;

      }

      if (pos == posLast)
      {

         break;

      }

   }

   return pos;

}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline ::count list < TYPE, ARG_TYPE, LIST_TYPE >::
get_count() const
{
   return LIST_TYPE::get_count();
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count list < TYPE, ARG_TYPE, LIST_TYPE >::
get_count(const TYPE & t, const_iterator find, const_iterator last, ::count countMax) const
{
   ::count count = 0;
   while((countMax >= 0 && count <= countMax)
      && (find = find_first(t, find, last)) != end())
      count++;
   return count;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool list < TYPE, ARG_TYPE, LIST_TYPE >::
contains(const TYPE & t, const_iterator find, const_iterator last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(t, find, last)) != NULL)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool list < TYPE, ARG_TYPE, LIST_TYPE >::
rcontains(const TYPE & t, const_iterator find, const_iterator last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_last(t, find, last)) != NULL)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool list<TYPE, ARG_TYPE, LIST_TYPE>::add_tail_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   this->add(t);
   return true;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool list<TYPE, ARG_TYPE, LIST_TYPE>::add_head_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   this->insert_first(t);
   return true;
}



template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void list<TYPE, ARG_TYPE, LIST_TYPE>::
merge_tail(const list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   
   auto pos = l.begin();

   for(;pos != l.end(); pos++)
   {
      
      if(!contains(*pos))
      {
         
         this->add(*pos);

      }

   }

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void list<TYPE, ARG_TYPE, LIST_TYPE>::
merge_head(const list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   
   auto pos = l.begin();

   while(pos != this->end())
   {

      if(!contains(*pos))
      {

         insert_first(*pos);

      }

   }

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline list<TYPE, ARG_TYPE, LIST_TYPE> &  list<TYPE, ARG_TYPE, LIST_TYPE>::
operator &= (const list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   
   iter::intersect(*this, l);
   
   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline list<TYPE, ARG_TYPE, LIST_TYPE> &  list<TYPE, ARG_TYPE, LIST_TYPE>::
operator -= (const TYPE & t)
{
   
   remove(t);
   
   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline list<TYPE, ARG_TYPE, LIST_TYPE> &  list<TYPE, ARG_TYPE, LIST_TYPE>::
operator -= (const list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   
   remove(l);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline list<TYPE, ARG_TYPE, LIST_TYPE> list<TYPE, ARG_TYPE, LIST_TYPE>::
operator - (const list<TYPE, ARG_TYPE, LIST_TYPE> & l) const
{
   list<TYPE, ARG_TYPE, LIST_TYPE> aRet(*this);
   aRet.remove(l);
   return aRet;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline list<TYPE, ARG_TYPE, LIST_TYPE> &  list<TYPE, ARG_TYPE, LIST_TYPE>::
operator |= (const list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   merge_tail(l);
   return *this;
}

//template <class TYPE, class ARG_TYPE, class LIST_TYPE>
//bool list < TYPE, ARG_TYPE , LIST_TYPE >::
//remove_first(const TYPE & t)
//{
//   iterator find = this->find_first(t);
//   if(find != NULL)
//   {
//      this->remove_at(find);
//      return true;
//   }
//   return false;
//}
//
//
//template <class TYPE, class ARG_TYPE, class LIST_TYPE>
//bool list < TYPE, ARG_TYPE , LIST_TYPE >::
//remove_first(const TYPE & t, iterator & find, iterator last)
//{
//   if((find = this->find_first(t, find, last)) != end())
//   {
//      iterator posRemove = find;
//      find++;
//      this->remove_at(posRemove);
//      return true;
//   }
//   return false;
//}


//template <class TYPE, class ARG_TYPE, class LIST_TYPE>
//bool list < TYPE, ARG_TYPE , LIST_TYPE >::
//remove_last(const TYPE & t)
//{
//   iterator find = find_last(t);
//   if(find != NULL)
//   {
//      this->remove_at(find);
//      return true;
//   }
//   return false;
//}
//
//
//template <class TYPE, class ARG_TYPE, class LIST_TYPE>
//bool list < TYPE, ARG_TYPE , LIST_TYPE >::
//remove_last(const TYPE & t, iterator & find, iterator last)
//{
//   if((find = find_last(t, find, last)) != end())
//   {
//      iterator posRemove = find;
//      find--;
//      this->remove_at(posRemove);
//      return true;
//   }
//   return false;
//}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count list < TYPE, ARG_TYPE , LIST_TYPE >::
remove(const list & l)
{
   
   ::count count = 0;
   
   auto pos = l.begin();
   
   while(pos != l.end())
   {

      count += remove(*pos);

      pos++;

   }

   return count;

}
