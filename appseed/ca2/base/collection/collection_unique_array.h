#pragma once

template < class TYPE >
class unique_sort_array :
   protected array < typename TYPE >
{
public:
   unique_sort_array(sp(::ca::application) papp = NULL);
   unique_sort_array(const unique_sort_array & array);

   virtual index add(TYPE newElement)
   {
      index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(const TYPE &t, index & find) const
   {
      index iL = find;
      index iU = get_upper_bound();
      while(iU - iL > 5)
      {
         find = (iL + iU) / 2;
         TYPE tCmp = t - this->element_at(find);
         if(tCmp == (TYPE) 0)
         {
            return true;
         }
         else if(tCmp > (TYPE) 0)
         {
            iL = find + 1;
         }
         else
         {
            iU = find - 1;
         }
      }
      for(; find < this->get_size(); find++)
      {
         TYPE tCmp = t - this->element_at(find);
         if(tCmp == (TYPE) 0)
         {
            return true;
         }
         else if(tCmp < (TYPE) 0)
         {
            return false;
         }
      }
      return false;
   }


};


template < class TYPE >
class unique_array :
   protected array < typename TYPE >
{
public:
   unique_array(sp(::ca::application) papp = NULL);
   unique_array(const unique_array & array);

   virtual index add(TYPE newElement)
   {
      index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(const TYPE &t, index & find) const
   {
      for(; find < this->get_size(); find++)
      {
         if(this->element_at(find) == t)
            break;
      }
      return find;
   }

};
