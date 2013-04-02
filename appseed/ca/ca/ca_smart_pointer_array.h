#pragma once


namespace ca
{


   template < class T >
   class smart_pointer_array :
      virtual public base_array < ::ca::smart_pointer < T > >
   {
   public:

      smart_pointer_array()
      {
      }

      smart_pointer_array(::ca::application * papp) :
         ca(papp),
         base_array < ::ca::smart_pointer < T > >(papp)
      {
      }


      ::ca::smart_pointer < T > & add_new()
      {

         base_array < ::ca::smart_pointer < T > >::add_new();

         last_element().create(get_app());

         return last_element();

      }


      ::count set_size(::count nNewSize, ::count nGrowBy = -1)
      {
         UNREFERENCED_PARAMETER(nGrowBy);
         while(nNewSize > get_size())
         {
            add_new();
         }
         if(get_size() > nNewSize)
         {
            base_array < ::ca::smart_pointer < T > >::set_size(nNewSize);
         }
         return get_size();
      }


      template < class DERIVED >
      DERIVED * get(index iStart = 0)
      {

         DERIVED * pderived = NULL;

         for(index i = iStart; i < this->get_count(); i++)
         {

            try
            {

               pderived = dynamic_cast < DERIVED * > (this->element_at(i).m_p);

            }
            catch(...)
            {

            }

            if(pderived != NULL)
               return pderived;

         }

         return NULL;

      }

      template < class DERIVED >
      DERIVED * typed_ptr_at(index iIndex)
      {

         return dynamic_cast < DERIVED * > (this->element_at(iIndex).m_p);

      }

      bool add_unique(T * p)
      {
         
         if(contains(p))
            return false;

         add(p);

         return true;

      }


      bool contains(T * p, index iStart = 0, ::count nCount = -1)
      {

         return find_first(p, iStart, nCount) >= 0;

      }

      ::index find_first(T * p, index iStart = 0, ::count nCount = -1)
      {
         
         ::count c = 0;

         index iEnd;

         if(nCount < 0)
            iEnd = get_upper_bound(nCount);
         else 
            iEnd = iStart + nCount - 1;

         for(int i = iStart; i <= iEnd; i++)
         {
            
            if(element_at(i).m_p == p)
               return i;

         }

         return -1;

      }


      ::index find_first(T & t, index (* lpfnCompare)(T *, T *), index iStart = 0, ::count nCount = -1)
      {

         return find_first(&t, lpfnCompare, iStart, nCount);

      }


      ::index find_first(T * p, index (* lpfnCompare)(T *, T *), index iStart = 0, ::count nCount = -1)
      {

         ::count c = 0;

         index iEnd;

         if(nCount < 0)
            iEnd = get_upper_bound(nCount);
         else 
            iEnd = iStart + nCount - 1;

         for(int i = iStart; i <= iEnd; i++)
         {
            
            if(lpfnCompare(element_at(i).m_p, p) == 0)
               return i;

         }

         return -1;

      }



      ::count remove(T * p)
      {

         ::count c = 0;

         index iFind = 0;

         while((iFind = find_first(p, iFind)) >= 0)
         {

            c++;

            remove_at(iFind);

         }

         return c;

      }

      // overloaded operator helpers
      const T & operator[](index nIndex) const
      {

         return *base_array < ::ca::smart_pointer < T > >::operator[](nIndex).m_p;

      }

      T & operator[](index nIndex)
      {

         return *base_array < ::ca::smart_pointer < T > >::operator[](nIndex).m_p;

      }

      const ::ca::smart_pointer < T > & sp_at(index nIndex) const
      {

         return base_array < ::ca::smart_pointer < T > >::element_at(nIndex);

      }


      ::ca::smart_pointer < T > & sp_at(index nIndex)
      {

         return base_array < ::ca::smart_pointer < T > >::element_at(nIndex);

      }


      const ::ca::smart_pointer < T > & first_sp(index n = 0) const
      {

         return base_array < ::ca::smart_pointer < T > >::first_element(n);

      }


      ::ca::smart_pointer < T > & first_sp(index n = 0)
      {

         return base_array < ::ca::smart_pointer < T > >::first_element(n);

      }

      
      const ::ca::smart_pointer < T > & last_sp(index n = 0) const
      {

         return base_array < ::ca::smart_pointer < T > >::last_element(n);

      }


      ::ca::smart_pointer < T > & last_sp(index n = 0)
      {

         return base_array < ::ca::smart_pointer < T > >::last_element(n);

      }

      const ::ca::smart_pointer < T > & operator() (index nIndex) const
      {

         return sp_at(nIndex);

      }


      ::ca::smart_pointer < T > & operator() (index nIndex)
      {

         return sp_at(nIndex);

      }


   };


} // namespace ca




#define spa(TYPE) ::ca::smart_pointer_array < TYPE >
