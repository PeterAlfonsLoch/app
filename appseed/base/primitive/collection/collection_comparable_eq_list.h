#pragma once

template < class TYPE, class ARG_TYPE  = const TYPE&, class LIST_TYPE = list < TYPE, ARG_TYPE > >
class comparable_eq_list :
   virtual public LIST_TYPE
{
public:
   comparable_eq_list();
   comparable_eq_list(const comparable_eq_list & array);

   POSITION find_first(const TYPE &t, POSITION pos = NULL, POSITION posLast = NULL) const;
   POSITION find_last(const TYPE &t, POSITION pos = NULL, POSITION posLast = NULL) const;
   ::count get_count() const;
   ::count get_count(const TYPE & t, POSITION start = NULL, POSITION last = NULL, ::count countMax = -1) const;
   bool contains(const TYPE & t, POSITION posStart = NULL, POSITION posLast = NULL, ::count countMin = 1, ::count countMax = -1) const;
   bool rcontains(const TYPE & t, POSITION posStart = NULL, POSITION posLast = NULL, ::count countMin = 1, ::count countMax = -1) const;
   bool remove_first(const TYPE & t);
   bool remove_last(const TYPE & t);
   bool remove_first(const TYPE & t, POSITION & pos, POSITION posLast = NULL);
   bool remove_last(const TYPE & t, POSITION & pos, POSITION posLast = NULL);
   ::count remove(const TYPE & t, POSITION pos = NULL, POSITION posLast = NULL, ::count countMin = 0, ::count countMax = -1);
   ::count rremove(const TYPE & t, POSITION pos = NULL, POSITION posLast = NULL, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const comparable_eq_list & l);



   // add
   bool add_tail_unique(ARG_TYPE t);
   bool add_head_unique(ARG_TYPE t);


   // set
   void merge_tail(const comparable_eq_list & l); // add_tail
   void merge_head(const comparable_eq_list & l); // add_tail
   void intersect(const comparable_eq_list & l);

   // set operators
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const TYPE & t);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator &= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator |= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l); // add_tail

   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > operator -(const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l) const;

};




template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_eq_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_eq_list()
{
}

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_eq_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_eq_list(const comparable_eq_list<  TYPE,  ARG_TYPE,  LIST_TYPE> & l) :
LIST_TYPE(l)
{
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
POSITION comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
find_first(const TYPE & t, POSITION pos, POSITION posLast) const
{
   if(pos == NULL)
      pos = this->get_head_position();
   if(pos == NULL)
      pos = this->get_tail_position();
   for(; pos != NULL;)
   {
      if(this->get_at(pos) == t)
         return pos;
      if(pos == posLast)
         break;
      this->get_next(pos);
   }
   return NULL;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
POSITION comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
find_last(const TYPE & t, POSITION pos, POSITION posLast) const
{
   if(pos == NULL)
      pos = this->get_tail_position();
   if(pos == NULL)
      pos = this->get_head_position();
   for(; pos != NULL;)
   {
      if(this->get_at(pos) == t)
         return pos;
      if(pos == posLast)
         break;
      this->get_previous(pos);
   }
   return NULL;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline ::count comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
get_count() const
{
   return LIST_TYPE::get_count();
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
get_count(const TYPE & t, POSITION find, POSITION last, ::count countMax) const
{
   ::count count = 0;
   while((countMax >= 0 && count <= countMax)
      && (find = find_first(t, find, last)) >= 0)
      count++;
   return count;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
contains(const TYPE & t, POSITION find, POSITION last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(t, find, last)) != NULL)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
rcontains(const TYPE & t, POSITION find, POSITION last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_last(t, find, last)) != NULL)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::add_tail_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   this->add_tail(t);
   return true;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::add_head_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   this->add_head(t);
   return true;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
intersect(const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & a)
{
   POSITION pos = this->get_head_position();
   for(; pos != NULL;)
   {
      if(!a.contains(this->get_next(pos)))
      {
         this->remove_at(pos);
      }
   }
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
merge_tail(const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   POSITION pos = l.get_head_position();
   while(pos != NULL)
   {
      if(!contains(l.get_at(pos)))
      {
         this->add_tail(l.get_next(pos));
      }
   }
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
merge_head(const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   POSITION pos = l.get_tail_position();
   while(pos != NULL)
   {
      if(!contains(l.get_at(pos)))
      {
         add_head(l.get_previous(pos));
      }
   }
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator &= (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   intersect(l);
   return *this;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator -= (const TYPE & t)
{
   remove(t);
   return *this;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator -= (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   remove(l);
   return *this;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator - (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l) const
{
   comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> aRet(*this);
   aRet.remove(l);
   return aRet;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator |= (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{
   merge_tail(l);
   return *this;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
remove_first(const TYPE & t)
{
   POSITION find = this->find_first(t);
   if(find != NULL)
   {
      this->remove_at(find);
      return true;
   }
   return false;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
remove_first(const TYPE & t, POSITION & find, POSITION last)
{
   if((find = this->find_first(t, find, last)) != NULL)
   {
      POSITION posRemove = find;
      this->get_next(find);
      this->remove_at(posRemove);
      return true;
   }
   return false;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
remove(const TYPE & t, POSITION find, POSITION last, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(t, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax) && remove_first(t, find, last))
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
remove_last(const TYPE & t)
{
   POSITION find = find_last(t);
   if(find != NULL)
   {
      this->remove_at(find);
      return true;
   }
   return false;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
remove_last(const TYPE & t, POSITION & find, POSITION last)
{
   if((find = find_last(t, find, last)) != NULL)
   {
      POSITION posRemove = find;
      this->get_previous(find);
      this->remove_at(posRemove);
      return true;
   }
   return false;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
rremove(const TYPE & t, POSITION find, POSITION last, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(t, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax) && remove_last(t, find, last))
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
remove(const comparable_eq_list & l)
{
   ::count count = 0;
   POSITION pos = l.get_head_position();
   while(pos != NULL)
   {
      count += remove(l.get_next(pos));
   }
   return count;
}
