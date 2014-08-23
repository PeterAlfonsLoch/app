#include "framework.h"




/// This class represents a collection of waitable items. A collection can be mixed
/// of any kind of waitable items (threads, events, semaphores, ...).
///  \brief		default constructor
event_collection::event_collection(sp(::aura::application) papp) :
   element(papp),
   callback_cnt(0)
{

}

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
void	event_collection::clear()
{ m_objecta.clear(); m_waitableelementa.clear(); callback_cnt=0;	}

size_t event_collection::size() const
{ return m_objecta.get_size(); }

///  \brief		checks if collection is empty
///  \return	true : collection empty
///  			false : collection not empty
bool event_collection::is_empty() const
{ return m_objecta.is_empty(); }

///  \brief		adds a waitable to the collection
///  \param		waitableItem item to add
///  \return	true : success
///  			false : failure
bool event_collection::add(event_base& waitableItem)
{
   if(m_objecta.size() >= MAXIMUM_WAIT_OBJECTS)
      return false;
   waitable_element wStruct;
   wStruct.item=&waitableItem;
   wStruct.callback=static_cast<waitable_callback*>(0);
#ifdef WINDOWS
   m_objecta.add(waitableItem.item());
#else
   m_objecta.add(&waitableItem);
#endif
   m_waitableelementa.add(wStruct);
   return true;
}

///  \brief		adds a waitable wit a callback to the collection
///  \param		waitableItem item to add
///  \param		waitableCallback for this item
///  \return	true : success
///  			false : failure
bool event_collection::add(event_base& waitableItem, waitable_callback *waitCallback)
{
   if ( m_objecta.size() >= MAXIMUM_WAIT_OBJECTS )
      return false;
   waitable_element wStruct;
   wStruct.item=&waitableItem;
   wStruct.callback=waitCallback;

#ifdef WINDOWS
   m_objecta.add(waitableItem.item());
#else
   m_objecta.add(&waitableItem);
#endif
   m_waitableelementa.add(wStruct);
   callback_cnt++;
   return true;
}

///  \brief		merges two collections into one
///  \param		waitableCollection collection to merge with
///  \return	true : success
///  			false : failure
bool event_collection::merge(const event_collection& collection)
{
   if ( m_objecta.size() + collection.m_objecta.get_size() >= MAXIMUM_WAIT_OBJECTS )
      return false;
   m_objecta.add(collection.m_objecta);
   m_waitableelementa.add(collection.m_waitableelementa);
   callback_cnt+=collection.callback_cnt;
   return true;
}

///  \brief		removes a waitable from the collection
///  \param		waitableItem item to remove
///  \return	true : success
///  			false : failure
void event_collection::remove(const event_base& waitableItem)
{
   for(index i=0;i<m_waitableelementa.size();i++) {
      if(m_waitableelementa[i].item==&waitableItem) {
         remove(i);
         break;
      }
   }
}

///  \brief		removes a waitable from the collection
///  \param		index index of item to remove
///  \return	true : success
///  			false : failure
void event_collection::remove(index index)
{

   if ( index > m_objecta.size() )
      throw range_error(get_app(), "event_collection::remove: index out of bounds");

   if(m_waitableelementa[index].callback!=0)
      callback_cnt--;

   m_objecta.erase( m_objecta.begin()+index );

   m_waitableelementa.erase( m_waitableelementa.begin()+index );

}

///  \brief		waits for the collection forever
void event_collection::wait()
{
   wait(false, duration::infinite());
}

///  \brief		waits for the collection for a specified time,
///				returns when the first item is signaled
///  \param		duration time period to wait for collection
///  \return	waiting action result as wait_result
wait_result event_collection::wait(const duration & duration)
{
   return wait(false, duration);
}


/////  \brief		waits for the collection for a specified time and if wanted,
/////				returns when all items are signaled
/////  \param		waitForAll if true, returns when all items are signaled, if false,
/////				returns when first item is signaled
/////  \param		duration time period to wait for collection
/////  \return	waiting action result as wait_result
wait_result event_collection::wait(bool waitForAll, const duration & duration)
{
   if ( m_objecta.is_empty() )
      return wait_result( wait_result::Failure );
   os_lock_duration timeout = duration;

   for (int32_t i = 0; i < m_waitableelementa.get_size(); i++)
      m_waitableelementa[i].item->init_wait();

   uint32_t start(get_tick_count());

   uint32_t winResult;
   bool FoundExternal=false;
   do {
      //std_cout << "Start waiting in wc :" << m_objecta.size() << std::endl;

      if (timeout)  {
         // if ANY timeout available
         do {
            uint32_t ticks = get_tick_count();

            if (ticks-start >= timeout)
               winResult = WAIT_TIMEOUT;
            else
               winResult = ::WaitForMultipleObjectsEx(static_cast<uint32_t>(m_objecta.size()), &*m_objecta.begin(), waitForAll, start + timeout - ticks, true);

         } while (winResult == WAIT_IO_COMPLETION);
      }
      else
         winResult = ::WaitForMultipleObjectsEx(static_cast<uint32_t>(m_objecta.size()), &*m_objecta.begin(), waitForAll, 0, FALSE);

      //std_cout << "Finished waiting in wc" << std::endl;
      if(callback_cnt>0 && winResult!=WAIT_TIMEOUT && winResult!=WAIT_FAILED) {
         // if events with callback are signaled call callback
         wait_result result=wait_result(winResult,m_objecta.size());

         if(waitForAll) {
            // just call all callbacks
            for ( index position = 0 ; position<m_objecta.size(); ++position )
               if(m_waitableelementa[position].callback)
                  m_waitableelementa[position].callback->callback(*m_waitableelementa[position].item);
               else if(!FoundExternal)
                  FoundExternal=true;
         }
         else {
            index position = result.abandoned() ? result.abandoned_index() : result.signaled_index();

            if(m_waitableelementa[position].callback) {
               //std_cout << "Calling callback" << std::endl;
               m_waitableelementa[position].callback->callback(*m_waitableelementa[position].item);
            }
            else
               FoundExternal=true;

            for ( ++position; position<m_objecta.size(); ++position ) {
               if(m_waitableelementa[position].callback) {
                  int32_t res = ::WaitForSingleObjectEx(m_objecta[position], 0, FALSE);

                  if ( res != WAIT_TIMEOUT )
                     m_waitableelementa[position].callback->callback(*m_waitableelementa[position].item);
               }
               else if(!FoundExternal) {
                  int32_t res = ::WaitForSingleObjectEx(m_objecta[position], 0, FALSE);

                  if ( res != WAIT_TIMEOUT ) {
                     winResult= (uint32_t) (res + position);
                     FoundExternal=true;
                  }
               }
            }
         }
      }
      else if(callback_cnt==0)
         FoundExternal=true;

   } while (winResult!=WAIT_TIMEOUT && winResult!= WAIT_FAILED && FoundExternal==false);

   //MBO: remove events to avoid double signalization
   comparable_array < waitable_element >::iterator it;
   for (it = m_waitableelementa.begin(); it != m_waitableelementa.end(); ++it)
      (*it).item->exit_wait();

   //std_cout << "Leaving wait in wc:" << std::endl;
   return wait_result(winResult,m_objecta.size());
}

///  \brief		searches for next item in collection with specified waiting result
///  \param		result result value to search for
///  \return	waiting result of found item or failure
wait_result event_collection::find_next( const wait_result& result ) const
{
   if ( !result.abandoned() && !result.signaled() )
      throw range_error(get_app(), "no element signaled");

   index position = result.abandoned() ? result.abandoned_index() : result.signaled_index();
   for ( ++position; position<m_objecta.get_size(); ++position ) {
      if(!m_waitableelementa[position].callback) {
         int32_t res = ::WaitForSingleObjectEx(m_objecta[position], 0, FALSE);
         if ( res == WAIT_TIMEOUT )
            continue;
         return wait_result( static_cast<int32_t>(position), m_objecta.get_size() );
      }
   }
   
   return wait_result( wait_result::Failure );
   
}


event_collection::event_collection( const event_collection& )
{
    
   throw void_implementation_exception(get_app());
   
}


const event_collection& event_collection::operator=( const event_collection& )
{

    throw void_implementation_exception(get_app());
   
   return *this;
   
}




