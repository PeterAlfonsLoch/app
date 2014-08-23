#pragma once


class CLASS_DECL_AURA sort_int_ptr_array
{
public:

   typedef sort_array < int_ptr, int_ptr, array < int_ptr, int_ptr >, &numeric_compare < int_ptr > > type;

};

class CLASS_DECL_AURA base_sort_serializable_int_ptr_array :
   virtual public ::file::serializable_array < sort_int_ptr_array::type >
{
public:

   base_sort_serializable_int_ptr_array() { }

#if defined(MOVE_SEMANTICS)

   base_sort_serializable_int_ptr_array(base_sort_serializable_int_ptr_array && a) :
      array < int_ptr, int_ptr >(a)
   {

   }

   inline base_sort_serializable_int_ptr_array & operator = (base_sort_serializable_int_ptr_array && a)
   {

      array < int_ptr, int_ptr >::operator = (a);

      return *this;

   }

#endif

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
   virtual int32_t signalize(flags < ENUM > & f);
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
   return add_unique((int_ptr)eenum);
}

template < class ENUM >
int32_t flags < ENUM > ::signalize(flags < ENUM > & f)
{
   int32_t iCount = 0;
   for (int32_t i = 0; i < f.get_size(); i++)
   {
      if (signalize((ENUM)f[i]))
         iCount++;
   }
   return iCount;
}

template < class ENUM >
bool flags < ENUM > ::is_signalized(ENUM eenum) const
{
   return contains((int_ptr)eenum);
}

template < class ENUM >
bool flags < ENUM > ::unsignalize(ENUM eenum)
{
   return remove((int_ptr)eenum) > 0;
}

template < class ENUM >
bool flags < ENUM > ::toggle_signalization(ENUM eenum)
{
   ASSERT(((int32_t)eenum) < 128);
   if (is_signalized(eenum))
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
   sort_int_ptr_array::type::copy(f);
   return *this;
}

template < class ENUM >
bool flags < ENUM > ::operator == (const flags < ENUM > & f)
{
   return sort_int_ptr_array::type::operator == (f);
}

template < class ENUM >
bool flags < ENUM > ::operator != (const flags < ENUM > & f)
{
   return sort_int_ptr_array::type::operator != (f);
}

template < class ENUM >
class flags_ex;

template < class ENUM >
class flags_listener
{
   friend class flags_ex < ENUM >;
protected:
   virtual void on_change_signalization(ENUM eenum);
   void on_change_signalization(int32_t iEnum);
};

template < class ENUM >
void flags_listener < ENUM > ::on_change_signalization(ENUM)
{
}

template < class ENUM >
void flags_listener < ENUM > ::on_change_signalization(int32_t iEnum)
{
   on_change_signalization((ENUM)iEnum);
}


template < class ENUM >
class flags_ex :
   public flags < ENUM >
{
public:


   flags_ex();
   flags_ex(flags_ex & flags);
   virtual ~flags_ex();

   using ::flags < ENUM >::signalize;
   virtual bool signalize(ENUM eenum);
   virtual bool unsignalize(ENUM eenum);
   virtual bool unsignalize_all();
   virtual bool toggle_signalization(ENUM eenum);

   virtual void on_change_signalization(ENUM eenum);

protected:

   class ::signal        m_signal;

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
   if (flags<ENUM>::signalize(eenum))
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
   if (flags<ENUM>::unsignalize(eenum))
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
   if (flags<ENUM>::toggle_signalization(eenum))
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

class flag_change_signalization :
   public signal_details
{
public:

   int32_t m_iEnum;


   flag_change_signalization(class ::signal * psignal) :
      signal_details(psignal)
   {
   }


};

template < class ENUM >
void flags_ex < ENUM > ::on_change_signalization(ENUM eenum)
{

   flag_change_signalization obj(&m_signal);

   obj.m_iEnum = (int32_t)eenum;

   m_signal.emit(&obj);

}



