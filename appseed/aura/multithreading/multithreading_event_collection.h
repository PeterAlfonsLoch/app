#pragma once


/// This class represents a collection of waitable items. A collection can be mixed
/// of any kind of waitable items (threads, events, semaphores, ...).
class CLASS_DECL_AXIS event_collection : public waitable
{
public:
#ifdef WINDOWS
   typedef comparable_array < HANDLE > CollectionType;
#else
    typedef comparable_array < waitable * > CollectionType;
#endif

private:
   CollectionType    m_objecta;

   typedef struct
   {
      event_base*  item; // abstract class -> compiler errors on usage of references
      waitable_callback* callback;
   } waitable_element;
   //public:
   //	waitable_element(event_base* item, waitable_callback* methodholder):item_(item),methodholder_(methodholder)
   //	{}

   //	event_base* item() const
   //	{ return item_; }

   //	waitable_callback * callback() const
   //	{ return methodholder_; }

   //};

   comparable_array < waitable_element > m_waitableelementa;

   /// number of callback events
   size_t callback_cnt;

public:
   ///  \brief		default constructor
   event_collection(sp(::axis::application) papp);

   //template<typename InIt>
   //event_collection( InIt first, InIt last )
   //	: m_objecta(first,last)
   //{
   //	if ( m_objecta.size() > MAXIMUM_WAIT_OBJECTS ) {
   //		m_objecta.clear();
   //		throw invalid_argument_exception("event_collection: too many wait objects");
   //	}
   //}

   ///  \brief		returns size of collection
   ///  \return	collection size
   void	clear();

   size_t size() const;

   ///  \brief		checks if collection is empty
   ///  \return	true : collection empty
   ///  			false : collection not empty
   bool is_empty() const;

   ///  \brief		adds a waitable to the collection
   ///  \param		waitableItem item to add
   ///  \return	true : success
   ///  			false : failure
   bool add(event_base& waitableItem);
   ///  \brief		adds a waitable wit a callback to the collection
   ///  \param		waitableItem item to add
   ///  \param		waitableCallback for this item
   ///  \return	true : success
   ///  			false : failure
   bool add(event_base& waitableItem, waitable_callback *waitCallback);

   ///  \brief		merges two collections into one
   ///  \param		waitableCollection collection to merge with
   ///  \return	true : success
   ///  			false : failure
   bool merge(const event_collection& collection);

   ///  \brief		removes a waitable from the collection
   ///  \param		waitableItem item to remove
   ///  \return	true : success
   ///  			false : failure
   void remove(const event_base& waitableItem);

   ///  \brief		removes a waitable from the collection
   ///  \param		index index of item to remove
   ///  \return	true : success
   ///  			false : failure
   void remove(index index);

   ///  \brief		waits for the collection forever
   virtual void wait();

   ///  \brief		waits for the collection for a specified time,
   ///				returns when the first item is signaled
   ///  \param		duration time period to wait for collection
   ///  \return	waiting action result as wait_result
   virtual wait_result wait(const duration & duration);

   /////  \brief		waits for the collection for a specified time and if wanted,
   /////				returns when all items are signaled
   /////  \param		waitForAll if true, returns when all items are signaled, if false,
   /////				returns when first item is signaled
   /////  \param		duration time period to wait for collection
   /////  \return	waiting action result as wait_result
   wait_result wait(bool waitForAll, const duration & duration);

   ///  \brief		searches for next item in collection with specified waiting result
   ///  \param		result result value to search for
   ///  \return	waiting result of found item or failure
   wait_result find_next( const wait_result& result ) const;

private:
   event_collection( const event_collection& );
   const event_collection& operator=( const event_collection& );
};


