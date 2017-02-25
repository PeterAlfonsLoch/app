#pragma once


template < class t1, class t2, class t3, class t4 >
void serialize_write(::file::ostream & ostream, map < t1, t2, t3, t4 > & m)
{
   ::count count = m.get_count();
   typename map < t1, t2, t3, t4 >::pair * ppair = m.PGetFirstAssoc();
   ostream << count;
   while (ppair != NULL)
   {
      ostream << ppair->m_element1;
      ostream << ppair->m_element2;
      ppair = m.PGetNextAssoc(ppair);
   }
}

template < class t1, class t2, class t3, class t4 >
void serialize_read(::file::istream & istream, map < t1, t2, t3, t4 > & m)
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
      for (int32_t i = 0; i < iCount; i++)
      {
         istream >> key;
         istream >> value;
         m.set_at(key, value);
      }
   }
   catch (const char * psz)
   {
      m.remove_all();
      throw psz;
   }
}


template < class T, class T_to_T = map < T, T, T, T > >
::file::ostream & operator <<(::file::ostream & ostream, const biunique< T, T_to_T > & b)
{
   ostream << m_bBiunivoca;
   ostream << m_iMaxA;
   ostream << m_iMaxB;
   ostream << m_iEmptyA;
   ostream << m_iEmptyB;
   if (m_bBiunivoca)
   {
      ostream << m_ab;
   }
   else
   {
      ostream << m_ab;
      ostream << m_ba;
   }

   return ostream;

}

::file::istream & operator >> (::file::istream & istream, biunique< T, T_to_T > & b)
{
   try
   {
      istream >> m_bBiunivoca;
      istream >> m_iMaxA;
      istream >> m_iMaxB;
      istream >> m_iEmptyA;
      istream >> m_iEmptyB;
      if (m_bBiunivoca)
      {
         T_to_T ab;
         istream >> ab;
         typename T_to_T::pair * ppair = ab.PGetFirstAssoc();
         while (ppair != NULL)
         {
            set(ppair->m_element1, ppair->m_element2);
            ppair = ab.PGetNextAssoc(ppair);
         }
      }
      else
      {
         istream >> m_ab;
         istream >> m_ba;
      }
   }
   catch (const char * psz)
   {
      m_ab.remove_all();
      m_ba.remove_all();
      m_bBiunivoca = true;
      m_iEmptyA = -1;
      m_iEmptyB = -1;
      m_iMaxA = -1;
      m_iMaxB = -1;
      throw psz;
   }
return istream;
}



