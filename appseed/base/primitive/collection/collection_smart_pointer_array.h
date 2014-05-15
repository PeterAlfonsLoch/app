#pragma once


template < class T >
class smart_pointer_array :
   virtual public array < smart_pointer < T > >
{
public:

   smart_pointer_array() { }

#if defined(MOVE_SEMANTICS)

   smart_pointer_array(smart_pointer_array && a) 
   {
      
      array < smart_pointer < T > >::operator = (a);

   }

   inline smart_pointer_array & operator = (smart_pointer_array && a)
   {

      array < smart_pointer < T > >::operator = (a);

      return *this;

   }

#endif

   smart_pointer_array(const smart_pointer_array & a) :
      array < smart_pointer < T > >(a)
   {

      array < smart_pointer < T > >::operator = (a);

   }

   inline smart_pointer_array & operator = (const smart_pointer_array & a)
   {

      copy(a);

      return *this;

   }


   smart_pointer_array(sp(::base::application) papp) :
      element(papp),
      array < smart_pointer < T > >(papp)
   {
   }

   sp(T) & add_new()
   {

      sp(T) & sp = array < smart_pointer < T > >::add_new();

      sp.create(this->allocer());

      return sp;

   }


   ::count set_size(::count nNewSize, ::count nGrowBy = -1)
   {

      return array < smart_pointer < T > > :: set_size(nNewSize);

   }

   ::count set_size_create(::count nNewSize, ::count nGrowBy = -1)
   {
      index i = this->get_size();
      array < smart_pointer < T > > :: set_size(nNewSize);
      ::count ca = this->get_size();
      for(; i < ca; i++)
      {
         this->element_at(i).create(this->allocer());
      }
      return ca;
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

      this->add(p);

      return true;

   }

   ::count add_unique(const smart_pointer_array & a)
   {

      ::count c = 0;

      for (index i = 0; i < a.get_count(); i++)
      {

         if (add_unique((T *) &a[i]))
            c++;

      }

      return c;

   }

   bool contains(const T * p, index iStart = 0, ::count nCount = -1) const
   {

      return find_first(p, iStart, nCount) >= 0;

   }

   ::index find_first(const T * p, index iStart = 0, ::count nCount = -1) const
   {

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         if(this->element_at(i).m_p == p)
            return i;

      }

      return -1;

   }


   ::index find_first(const T & t, index (* lpfnCompare)(const T *, const T *), index iStart = 0, ::count nCount = -1) const
   {

      return this->find_first(&t, lpfnCompare, iStart, nCount);

   }


   ::index find_first(const T * p, index (* lpfnCompare)(const T *, const T *), index iStart = 0, ::count nCount = -1) const
   {

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         if(lpfnCompare(this->element_at(i).m_p, p) == 0)
            return i;

      }

      return -1;

   }

   template < class DERIVED >
   smart_pointer_array & operator -= (DERIVED * p)
   {

      this->remove(dynamic_cast < T * > (p));

      return *this;

   }

   ::count remove(T * p)
   {

      ::count ca = 0;

      index iFind = 0;

      while((iFind = this->find_first(p, iFind)) >= 0)
      {

         ca++;

         this->remove_at(iFind);

      }

      return ca;

   }


   template < typename TYPE >
   ::count remove_type(TYPE *)
   {

      ::count c = 0;

      for (index i = this->get_upper_bound(); i >= 0; i--)
      {

         if (typeid(*this->element_at(i).m_p) == typeid(TYPE))
         {

            this->remove_at(i);

            c++;

         }

      }

      return c;

   }

   // overloaded operator helpers
   const T & operator[](index nIndex) const
   {

      return *this->array < smart_pointer < T > >::operator[](nIndex).m_p;

   }

   T & operator[](index nIndex)
   {

      return *this->array < smart_pointer < T > >::operator[](nIndex).m_p;

   }

   const smart_pointer < T > & sp_at(index nIndex) const
   {

      return this->array < smart_pointer < T > >::element_at(nIndex);

   }


   smart_pointer < T > & sp_at(index nIndex)
   {

      return this->array < smart_pointer < T > >::element_at(nIndex);

   }


   T * ptr_at(index nIndex) const
   {

      return this->sp_at(nIndex);

   }


   T * ptr_at(index nIndex)
   {

      return this->sp_at(nIndex);

   }


   T & at(index nIndex) const
   {

      return *this->ptr_at(nIndex);

   }


   T & at(index nIndex)
   {

      return *this->ptr_at(nIndex);

   }

   const smart_pointer < T > & first_sp(index n = 0) const
   {

      return this->array < smart_pointer < T > >::first_element(n);

   }


   smart_pointer < T > & first_sp(index n = 0)
   {

      return this->array < smart_pointer < T > >::first_element(n);

   }


   T * first_ptr(index n = 0) const
   {

      return this->first_sp(n);

   }


   T * first_ptr(index n = 0)
   {

      return this->first_sp(n);

   }


   T & first(index n = 0) const
   {

      return *this->first_ptr(n);

   }


   T & first(index n = 0)
   {

      return *this->first_ptr(n);

   }


   T * last_sp(index n = -1) const
   {

      return this->array < smart_pointer < T > >::last_element(n);

   }


   smart_pointer < T > & last_sp(index n = -1)
   {

      return this->array < smart_pointer < T > >::last_element(n);

   }


   T * last_ptr(index n = -1) const
   {

      return this->last_sp(n);

   }


   T * last_ptr(index n = -1)
   {

      return this->last_sp(n);

   }


   T & last(index n = -1) const
   {

      return *last_ptr(n);

   }


   T & last(index n = -1)
   {

      return *this->last_ptr(n);

   }


   const smart_pointer < T > & operator() (index nIndex) const
   {

      return this->sp_at(nIndex);

   }


   smart_pointer < T > & operator() (index nIndex)
   {

      return this->sp_at(nIndex);

   }


   template < class ARRAY >
   smart_pointer_array & append(const ARRAY * pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(pa->element_at(i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & append(const sp(ARRAY) & pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(pa->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & append(const ARRAY & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(a.element_at(i));
      }

      return *this;

   }

   smart_pointer_array & append(const smart_pointer_array & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(a(i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & append_ptra(const ARRAY * pptra)
   {

      ::count c = pptra->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(*pptra->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy(const ARRAY * pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy(const sp(ARRAY) & pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy(const ARRAY & a)
   {

      if(&a == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   smart_pointer_array & copy(const smart_pointer_array & a)
   {

      if(&a == this)
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy_ptra(const ARRAY * pptra)
   {

      if(pptra == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pptra);

      return *this;

   }



};


namespace xml
{


   template < int32_t m_iNodeNameIndex, class TYPE >
   class smart_pointer_array :
      public ::smart_pointer_array < TYPE >,
      public exportable,
      public importable
   {
   public:


      smart_pointer_array();
      smart_pointer_array(const array & xmla);


      virtual void xml_export(output_tree & xmlof);
      virtual void xml_import(input_tree & xmlif);


   };


   template < int32_t m_iNodeNameIndex,class TYPE >
   smart_pointer_array<m_iNodeNameIndex,TYPE>::
      smart_pointer_array()
   {
      }

   template < int32_t m_iNodeNameIndex,class TYPE >
   smart_pointer_array<m_iNodeNameIndex,TYPE>::
      smart_pointer_array(const array & xmla)
   {

      operator = (xmla);

   }

   template < int32_t m_iNodeNameIndex,class TYPE >
   void
      smart_pointer_array<m_iNodeNameIndex,TYPE>::
      xml_export(output_tree & xmlof)
   {
         xmlof.set_attr("count",this->get_size());
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex),this->operator[](i));
            pnode->add_attr("array_index",i);
         }
      }


   template < int32_t m_iNodeNameIndex,class TYPE >
   void
      smart_pointer_array<m_iNodeNameIndex,TYPE>::
      xml_import(input_tree & xmlif)
   {
         int32_t iSize;
         xmlif.get_attr("count",iSize);
         set_size_create(iSize);
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            attr_array attra(this->get_app());
            attra.add("array_index",i);
            xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex),attra,this->operator[](i));
         }
      }



} // namespace xml







#define spa(TYPE) ::smart_pointer_array < TYPE >
#define xmlspa(TYPE) ::smart_pointer_array < TYPE >

typedef spa(waitable) sync_object_ptra;
