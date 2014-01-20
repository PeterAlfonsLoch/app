#pragma once


/////////////////////////////////////////////////////////////////////////////
// typed_pointer_list<BASE_CLASS, TYPE>

template<class BASE_CLASS, class TYPE>
class _typed_pointer_list :
   virtual public BASE_CLASS
{
public:

/*   _typed_pointer_list(::count nBlockSize = 10) :
      BASE_CLASS(nBlockSize)
   {
   }*/

   // peek at head or tail
   TYPE& get_head()
      { return (TYPE&)BASE_CLASS::get_head(); }
   TYPE get_head() const
      { return (TYPE)BASE_CLASS::get_head(); }
   TYPE& get_tail()
      { return (TYPE&)BASE_CLASS::get_tail(); }
   TYPE get_tail() const
      { return (TYPE)BASE_CLASS::get_tail(); }

   // get head or tail (and remove it) - don't call on is_empty list!
   TYPE remove_head()
      { return (TYPE)BASE_CLASS::remove_head(); }
   TYPE remove_tail()
      { return (TYPE)BASE_CLASS::remove_tail(); }

   // iteration
   TYPE& get_next(POSITION& rPosition)
      { return (TYPE&)BASE_CLASS::get_next(rPosition); }
   TYPE get_next(POSITION& rPosition) const
      { return (TYPE)BASE_CLASS::get_next(rPosition); }
   TYPE& get_previous(POSITION& rPosition)
      { return (TYPE&)BASE_CLASS::get_previous(rPosition); }
   TYPE get_previous(POSITION& rPosition) const
      { return (TYPE)BASE_CLASS::get_previous(rPosition); }

   // getting/modifying an element at a given position
   TYPE& get_at(POSITION position)
      { return (TYPE&)BASE_CLASS::get_at(position); }
   TYPE get_at(POSITION position) const
      { return (TYPE)BASE_CLASS::get_at(position); }
   void set_at(POSITION pos, TYPE newElement)
      { BASE_CLASS::set_at(pos, newElement); }

   // inserting before or after a given position
   POSITION insert_before(POSITION position, TYPE newElement)
      { return BASE_CLASS::insert_before(position, newElement); }
   POSITION insert_after(POSITION position, TYPE newElement)
      { return BASE_CLASS::insert_after(position, newElement); }

   // transfer before or after a given position
   // Transfer semantics ensure no leakage by deleting the element in the case of an exception
   POSITION TransferInsertBefore(POSITION position, TYPE newElement)
   {
      try
      {
         return BASE_CLASS::insert_before(position, newElement);
      }
      catch(...)
      {
         delete newElement;
         throw;
      }
   }

   POSITION TransferInsertAfter(POSITION position, TYPE newElement)
   {
      try
      {
         return BASE_CLASS::insert_after(position, newElement);
      }
      catch(...)
      {
         delete newElement;
         throw;
      }
   }
};



template<class BASE_CLASS, class TYPE>
class typed_pointer_list :
   virtual public _typed_pointer_list<BASE_CLASS, TYPE>
{
public:

   typed_pointer_list(::count nBlockSize = 10) :
      BASE_CLASS(nBlockSize)
   {
   }

   // add before head or after tail
   POSITION add_head(TYPE newElement)
      { return BASE_CLASS::add_head(newElement); }
   POSITION add_tail(TYPE newElement)
      { return BASE_CLASS::add_tail(newElement); }

   // transfer add before head or tail
   POSITION TransferAddHead(TYPE newElement)
   {
      try
      {
         return BASE_CLASS::add_head(newElement);
      }
      catch(...)
      {
         delete newElement;
         throw;
      }
   }
   POSITION TransferAddTail(TYPE newElement)
   {
      try
      {
         return BASE_CLASS::add_tail(newElement);
      }
      catch(...)
      {
         delete newElement;
         throw;
      }
   }

   // add another list of elements before head or after tail
   void add_head(typed_pointer_list<BASE_CLASS, TYPE>* pNewList)
      { BASE_CLASS::add_head(pNewList); }
   void add_tail(typed_pointer_list<BASE_CLASS, TYPE>* pNewList)
      { BASE_CLASS::add_tail(pNewList); }
};

// need specialized version for object_list because of add_head/Tail ambiguity
template<> class typed_pointer_list<object_list, object_list*> :
   virtual public _typed_pointer_list<object_list, object_list*>
{
public:
// Construction
   typed_pointer_list(::count nBlockSize = 10) :
      object_list(nBlockSize)
   {
   }

   // add before head or after tail
   POSITION add_head(object_list* newElement)
      { return _typed_pointer_list<object_list, object_list*>::add_head((object*)newElement); }
   POSITION add_tail(object_list* newElement)
      { return _typed_pointer_list<object_list, object_list*>::add_tail((object*)newElement); }

   // add another list of elements before head or after tail
   void add_head(typed_pointer_list<object_list, object_list*>* pNewList)
      { _typed_pointer_list<object_list, object_list*>::add_head(pNewList); }
   void add_tail(typed_pointer_list<object_list, object_list*>* pNewList)
      { _typed_pointer_list<object_list, object_list*>::add_tail(pNewList); }
};

// need specialized version for pointer_list because of add_head/Tail ambiguity
template<> class typed_pointer_list<pointer_list, pointer_list*> :
   public _typed_pointer_list<pointer_list, pointer_list*>
{
public:
   typed_pointer_list(::count nBlockSize = 10) :
      pointer_list(nBlockSize)
   {
   }

   // add before head or after tail
   POSITION add_head(pointer_list* newElement)
      { return _typed_pointer_list<pointer_list, pointer_list*>::add_head((void *)newElement); }
   POSITION add_tail(pointer_list* newElement)
      { return _typed_pointer_list<pointer_list, pointer_list*>::add_tail((void *)newElement); }

   // add another list of elements before head or after tail
   void add_head(typed_pointer_list<pointer_list, pointer_list*>* pNewList)
      { _typed_pointer_list<pointer_list, pointer_list*>::add_head(pNewList); }
   void add_tail(typed_pointer_list<pointer_list, pointer_list*>* pNewList)
      { _typed_pointer_list<pointer_list, pointer_list*>::add_tail(pNewList); }
};






