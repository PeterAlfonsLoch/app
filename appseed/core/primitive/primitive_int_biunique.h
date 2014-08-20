#pragma once

template < class T, class T_to_T = attrib_map < map < T, T, T, T > > >
class  biunique :
   public object,
   public ::file::serializable
{
public:
   biunique(sp(::axis::application) papp = NULL);

   bool has_a(T a) const;
   bool has_b(T b) const;


   T calc_max_a();
   T calc_max_b();


   T remove_a(T a);
   T remove_b(T b);

   T translate_a(T a1, T a2);
   T translate_b(T b1, T b2);


   T get_a(T b) const;
   T get_b(T a) const;
   void set(T a, T b);

   void swap(T a1, T a2);

   T operator [](T a) const
   {
      return get_b(a);
   }

   T get_max_a() const;
   T get_max_b() const;

   void remove_all();

   void set_empty_a(T iEmpty);
   void set_empty_b(T iEmpty);

   T get_free_a() const;
   T get_free_b() const;

   T add(T b);
   T add_b_in_first_free_a(T b);
   T add_b_in_first_free_a_mod_w(T b, T w, T mod);
   T add_unique(T b);
   T get_size() const;

   void copy_data(const biunique & ia);

   virtual void write(::file::output_stream & ostream);
   virtual void read(::file::input_stream & ostream);

   biunique & operator = (const biunique & ia);

   void biunivoca(bool b = true);

protected:
   bool m_bBiunivoca;
   T m_iMaxA;
   T m_iMaxB;
   T m_iEmptyA;
   T m_iEmptyB;
   T_to_T m_ab;
   T_to_T m_ba;
};



template < class T, class T_to_T >
biunique < T, T_to_T > ::biunique(sp(::axis::application) papp) :
   element(papp)
{
   m_bBiunivoca = true;
   m_iEmptyA = -1;
   m_iEmptyB = -1;
   m_iMaxA = -1;
   m_iMaxB = -1;
}


template < class T, class T_to_T >
void biunique < T, T_to_T > ::biunivoca(bool b)
{
   m_bBiunivoca = b;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_a (T b) const
{
   T a;
   if(m_ba.Lookup(b, a))
      return a;
   return m_iEmptyA;
}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_b (T a) const
{
   T b;
   if(m_ab.Lookup(a, b))
      return b;
   return m_iEmptyB;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::remove_a(T a)
{
   if(has_a(a))
   {
      T b = get_b(a);
      m_ba.remove_key(b);
      m_ab.remove_key(a);
      m_iMaxA = calc_max_a();
      m_iMaxB = calc_max_b();
      return b;
   }
   return m_iEmptyB;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::remove_b(T b)
{
   if(has_b(b))
   {
      T a = get_a(b);
      m_ab.remove_key(a);
      m_ba.remove_key(b);
      m_iMaxA = calc_max_a();
      m_iMaxB = calc_max_b();
      return a;
   }
   return m_iEmptyA;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::translate_a(T a1, T a2)
{
   T b = remove_a(a2);
   set(a1, b);
   return b;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::translate_b(T b1, T b2)
{
   T a = remove_b(b2);
   set(a, b1);
   return a;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::set(T a, T b)
{
   if(m_bBiunivoca)
   {
      if(has_a(a))
         remove_a(a);
      if(has_b(b))
         remove_b(b);
   }
   m_ab.set_at(a, b);
   m_ba.set_at(b, a);
   m_iMaxA = calc_max_a();
   m_iMaxB = calc_max_b();
}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_max_a() const
{
   return m_iMaxA;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_max_b() const
{
   return m_iMaxB;
}



template < class T, class T_to_T >
void biunique < T, T_to_T > ::remove_all()
{
   m_ab.remove_all();
   m_ba.remove_all();
   m_iMaxA = -1;
   m_iMaxB = -1;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::set_empty_a(T iEmpty)
{
   m_iEmptyA = iEmpty;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::set_empty_b(T iEmpty)
{
   m_iEmptyB = iEmpty;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::copy_data(const biunique & function)
{
   if(&function != this)
   {
      m_ab = function.m_ab;
      m_ba = function.m_ba;
   }
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::add(T b)
{
   T a = get_max_a() + 1;
   set(a, b);
   return a;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::add_b_in_first_free_a(T b)
{
   T a = get_free_a();
   set(a, b);
   return a;
}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::add_b_in_first_free_a_mod_w(T b, T w, T mod)
{
   if(mod <= 1)
      return add_b_in_first_free_a(b);
   if(w <= 0)
      return add_b_in_first_free_a(b);
   T ca = get_max_a() + 1;
   T a;
   for(a = 0; a < ca ; a++)
   {
      if((a % mod) >= w)
      {
         a = ((a / mod) + 1) * mod;
      }
      if(get_b(a) == m_iEmptyB)
      {
         set(a, b);
         return a;
      }
   }
   set(a, b);
   return a;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::add_unique(T b)
{
   T a;
   if(m_ba.Lookup(b, a))
      return a;
   a = get_max_a() + 1;
   set(a, b);
   return a;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_size() const
{
   return get_max_a() + 1;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::swap(T a1, T a2)
{
   // because of Biunivoca
   T b1 = get_b(a1);
   T b2 = get_b(a2);
   set(a1, b2);
   set(a2, b1);

}

template < class T, class T_to_T >
bool biunique < T, T_to_T > ::has_a(T a) const
{
   T b;
   return m_ab.Lookup(a, b) != FALSE;
}


template < class T, class T_to_T >
bool biunique < T, T_to_T > ::has_b(T b) const
{
   T a;
   return m_ba.Lookup(b, a) != FALSE;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_free_a() const
{
   for(T a = 0; a <= m_iMaxA; a++)
   {
      if(!has_a(a))
         return a;
   }
   return m_iMaxA + 1;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_free_b() const
{
   for(T b = 0; b <= m_iMaxB; b++)
   {
      if(!has_b(b))
         return b;
   }
   return m_iMaxB + 1;
}

template < class T, class T_to_T >
biunique < T, T_to_T > & biunique < T, T_to_T > ::operator = (const biunique & ia)
{
   if(this != &ia)
   {
      m_bBiunivoca = ia.m_bBiunivoca;
      m_iMaxA = ia.m_iMaxA;
      m_iMaxB = ia.m_iMaxB;
      m_iEmptyA = ia.m_iEmptyA;
      m_iEmptyB = ia.m_iEmptyB;
      m_ab = ia.m_ab;
      m_ba = ia.m_ba;
   }
   return *this;
}


template < class t1, class t2, class t3, class t4 >
void serialize_write(::file::output_stream & ostream, map < t1, t2, t3, t4 > & m)
{
   ::count count = m.get_count();
   typename map < t1, t2, t3, t4 >::pair * ppair = m.PGetFirstAssoc();
   ostream << count;
   while(ppair != NULL)
   {
      ostream << ppair->m_element1;
      ostream << ppair->m_element2;
      ppair = m.PGetNextAssoc(ppair);
   }
}

template < class t1, class t2, class t3, class t4 >
void serialize_read(::file::input_stream & istream, map < t1, t2, t3, t4 > & m)
{
   try
   {
      t1 iCount;
//      class map < t1, t2, t3, t4 >::pair * ppair =
  //       m.PGetFirstAssoc();
      istream >> iCount;
      t1 key;
      t3 value;
      m.remove_all();
      for(int32_t i = 0; i < iCount; i++)
      {
         istream >> key;
         istream >> value;
         m.set_at(key, value);
      }
   }
   catch(const char * psz)
   {
      m.remove_all();
      throw psz;
   }
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::write(::file::output_stream & ostream)
{
   ostream << m_bBiunivoca;
   ostream << m_iMaxA;
   ostream << m_iMaxB;
   ostream << m_iEmptyA;
   ostream << m_iEmptyB;
   if(m_bBiunivoca)
   {
      serialize_write(ostream, m_ab);
   }
   else
   {
      serialize_write(ostream, m_ab);
      serialize_write(ostream, m_ba);
   }
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::read(::file::input_stream & istream)
{
   try
   {
      istream >> m_bBiunivoca;
      istream >> m_iMaxA;
      istream >> m_iMaxB;
      istream >> m_iEmptyA;
      istream >> m_iEmptyB;
      if(m_bBiunivoca)
      {
         T_to_T ab;
         serialize_read(istream, ab);
         typename T_to_T::pair * ppair = ab.PGetFirstAssoc();
         while(ppair != NULL)
         {
            set(ppair->m_element1, ppair->m_element2);
            ppair = ab.PGetNextAssoc(ppair);
         }
      }
      else
      {
         serialize_read(istream, m_ab);
         serialize_read(istream, m_ba);
      }
   }
   catch(const char * psz)
   {
      m_ab.remove_all();
      m_ba.remove_all();
      m_bBiunivoca = true;
      m_iEmptyA = - 1;
      m_iEmptyB = - 1;
      m_iMaxA = -1;
      m_iMaxB = -1;
      throw psz;
   }
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::calc_max_a()
{
   typename T_to_T::pair * ppair =
      m_ab.PGetFirstAssoc();
   T iMaxA = -1;
   while(ppair != NULL)
   {
      if(ppair->m_element1 > iMaxA)
         iMaxA = ppair->m_element1;
      ppair = m_ab.PGetNextAssoc(ppair);
   }
   return iMaxA;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::calc_max_b()
{
   typename T_to_T::pair * ppair =
      m_ba.PGetFirstAssoc();
   T iMaxB = -1;
   while(ppair != NULL)
   {
      if(ppair->m_element1 > iMaxB)
         iMaxB = ppair->m_element1;
      ppair = m_ba.PGetNextAssoc(ppair);
   }
   return iMaxB;
}



class CLASS_DECL_CORE index_biunique :
   public biunique < index >
{
public:
   index_biunique(sp(::axis::application) papp = NULL);
};

class CLASS_DECL_CORE int_biunique :
   public biunique < int32_t, int_to_int >
{
public:
   int_biunique(sp(::axis::application) papp = NULL);

};















