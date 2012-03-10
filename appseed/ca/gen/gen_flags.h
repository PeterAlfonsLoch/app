#pragma once

#include "ex1/ex1_byte_serializable.h"
#include "radix/DispatchPtrArray.h"
#include "collection/sort_array.h"

class CLASS_DECL_ca base_sort_serializable_int_ptr_array :
   virtual public ex1::byte_serializable_array < sort_array < INT_PTR, INT_PTR > >
{
   virtual void on_after_read();
};


template < class ENUM >
class flags :
   virtual public base_sort_serializable_int_ptr_array
{
public:
   flags();
   flags(ENUM eenum);
   flags(const flags & f);
   virtual ~flags();


   virtual bool signalize(ENUM eenum);
   virtual int signalize(flags < ENUM > & f);
   bool is_signalized(ENUM eenum) const;
   virtual bool unsignalize(ENUM eenum);
   virtual bool unsignalize_all();
   virtual bool toggle_signalization(ENUM eenum);

   flags < ENUM > & operator = (const flags < ENUM >  & f);
   bool operator == (const flags < ENUM >  & f);
   bool operator != (const flags < ENUM >  & f);

};

template < class ENUM >
flags < ENUM > ::flags()
{
}

template < class ENUM >
flags < ENUM > ::flags(ENUM eenum)
{
   signalize(eenum);
}

template < class ENUM >
flags < ENUM > ::flags(const flags < ENUM > & f)
{
   operator = (f);
}

template < class ENUM >
flags < ENUM > ::~flags()
{
}

template < class ENUM >
bool flags < ENUM > ::signalize(ENUM eenum)
{
   index i = 0;
   if(!BaseSortFind((INT_PTR &) eenum, i))
   {
      BaseSortInsert((INT_PTR) eenum);
      return true;
   }
   else
   {
      return false;
   }
}

template < class ENUM >
int flags < ENUM > ::signalize(flags < ENUM > & f)
{
   int iCount = 0;
   for(int i = 0; i < f.get_size(); i++)
   {
      if(signalize((ENUM) f[i]))
         iCount++;
   }
   return iCount;
}

template < class ENUM >
bool flags < ENUM > ::is_signalized(ENUM eenum) const
{
   index i = 0;
   return BaseSortFind((DWORD) eenum, i);
}

template < class ENUM >
bool flags < ENUM > ::unsignalize(ENUM eenum)
{
   index i = 0;
   bool bRemove = false;
   while(BaseSortFind((INT_PTR) eenum, i))
   {
      remove_at(i);
      bRemove = true;
   }
   return bRemove;
}

template < class ENUM >
bool flags < ENUM > ::toggle_signalization(ENUM eenum)
{
   ASSERT(((int) eenum) < 128);
   if(is_signalized(eenum))
   {
      return unsignalize(eenum);
   }
   else
   {
      return signalize(eenum);
   }
}

template < class ENUM >
bool flags < ENUM > ::unsignalize_all()
{
   remove_all();
   return true;
}

template < class ENUM >
flags < ENUM > & flags < ENUM > ::operator = (const flags < ENUM > & f)
{
   sort_array < INT_PTR, INT_PTR >::copy(f);
   return *this;
}

template < class ENUM >
bool flags < ENUM > ::operator == (const flags < ENUM > & f)
{
   return sort_array < INT_PTR, INT_PTR >::operator == (f);
}

template < class ENUM >
bool flags < ENUM > ::operator != (const flags < ENUM > & f)
{
   return sort_array < INT_PTR, INT_PTR >::operator != (f);
}

template < class ENUM >
class flags_ex;

template < class ENUM >
class flags_listener
{
   friend class flags_ex < ENUM >;
protected:
   virtual void on_change_signalization(ENUM eenum);
   void on_change_signalization(int iEnum);
};

template < class ENUM >
void flags_listener < ENUM > ::on_change_signalization(ENUM)
{
}

template < class ENUM >
void flags_listener < ENUM > ::on_change_signalization(int iEnum)
{
   on_change_signalization((ENUM) iEnum);
}


template < class ENUM >
class flags_ex :
   public flags < ENUM >
{
public:
   flags_ex();
   flags_ex(flags_ex & flags);
   virtual ~flags_ex();

   virtual bool signalize(ENUM eenum);
   virtual bool unsignalize(ENUM eenum);
   virtual bool unsignalize_all();
   virtual bool toggle_signalization(ENUM eenum);

   virtual void on_change_signalization(ENUM eenum);

protected:
   DispatchPtrArray < flags_listener < ENUM >, flags_listener < ENUM > * > m_dispptra;
};

template < class ENUM >
flags_ex < ENUM > ::flags_ex()
{
}

template < class ENUM >
flags_ex < ENUM > ::flags_ex(flags_ex < ENUM > & f)
{
   operator = (f);
}

template < class ENUM >
flags_ex < ENUM > ::~flags_ex()
{
}

template < class ENUM >
bool flags_ex < ENUM > ::signalize(ENUM eenum)
{
   if(flags<ENUM>::signalize(eenum))
   {
      on_change_signalization(eenum);
      return true;
   }
   else
   {
      return false;
   }
}

template < class ENUM >
bool flags_ex < ENUM > ::unsignalize(ENUM eenum)
{
   if(flags<ENUM>::unsignalize(eenum))
   {
      on_change_signalization(eenum);
      return true;
   }
   else
   {
      return false;
   }
}

template < class ENUM >
bool flags_ex < ENUM > ::toggle_signalization(ENUM eenum)
{
   if(flags<ENUM>::toggle_signalization(eenum))
   {
      on_change_signalization(eenum);
      return true;
   }
   else
   {
      return false;
   }
}

template < class ENUM >
bool flags_ex < ENUM > ::unsignalize_all()
{
   return flags<ENUM>::unsignalize_all();
}


template < class ENUM >
void flags_ex < ENUM > ::on_change_signalization(ENUM eenum)
{
   m_dispptra.PtrCallAll(&flags_listener<ENUM>::on_change_signalization, (int) eenum);
}


