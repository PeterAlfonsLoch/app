#pragma once


#include "collection_map_association.h"
#include "collection_sort.h"


template < typename T > class numeric_array;
typedef numeric_array < index > index_array;
typedef numeric_array < count > count_array;


namespace iter
{

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::const_iterator find_first(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::const_iterator find = NULL, typename ITERABLE::const_iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   bool icontains(const ITERABLE & iterable, const TYPE & t, index first = 0, ::count count = -1);

   template < typename ITERABLE, typename TYPE >
   bool contains(const ITERABLE & iterable, const TYPE & t, typename ITERABLE::const_iterator pos, typename ITERABLE::const_iterator posLast = NULL, ::count countMin = 0, ::count countMax = -1);

   template < typename ITERABLE, typename TYPE >
   bool contains(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator pos, typename ITERABLE::iterator posLast = NULL, ::count countMin = 0, ::count countMax = -1);

   template < typename ITERABLE, typename ITERABLE2 >
   void copy(ITERABLE & iterable, const ITERABLE2 & iterable2);


   template < typename ITERABLE, typename TYPE >
   ITERABLE & add_lines(ITERABLE & iterable, const TYPE & str, bool bAddEmpty = true);

   template < typename ITERABLE, typename TYPE >
   typename bool add_unique(ITERABLE & iterable, const TYPE & lpcsz);

   template < typename ITERABLE, typename TYPE >
   typename bool add_unique_ci(ITERABLE & iterable, const TYPE & lpcsz);

   template < typename ITERABLE, typename ITERABLE2, typename TYPE >
   typename ::count add_unique_iter(ITERABLE & iterable, const ITERABLE & stra);

   template < typename ITERABLE, typename ITERABLE2, typename TYPE >
   typename ::count add_unique_iter_ci(ITERABLE & iterable, const ITERABLE & stra);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & add(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & copy_iter(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERATOR >
   ITERABLE & copy_iter(ITERABLE & iterable, const ITERATOR & iteratorSrc, const ITERATOR & limit);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & insert_iter_at(ITERABLE & iterable, typename ITERABLE::iterator nStartIndex, const ITERABLE2 & iterable2);

   template < typename ITERABLE >
   ::count remove_empty(ITERABLE & iterable);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   ITERABLE & replace(ITERABLE & iterable, const TYPE & lpszSearch, const TYPE2 & lpszReplace);

   // if TYPE is found, move it to specified position
   template < typename ITERABLE, typename TYPE, typename ITERABLE2 >
   bool move_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator iIndex);

   template < typename ITERABLE >
   ITERABLE & copy(ITERABLE & iterable, const var var);

   template < typename ITERABLE, typename TYPE, typename ITERABLE2 >
   ITERABLE & add_shortest_tokens(ITERABLE & iterable, const TYPE & lpcsz, const ITERABLE2 & iterableSeparator, bool bAddEmpty = true, bool bWithSeparator = FALSE);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & slice(ITERABLE & iterable, ITERABLE2 & iterable2, typename ITERABLE::iterator first, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & islice(ITERABLE & iterable, ITERABLE2 & iterable2, index first, ::count count = -1);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & add_iter(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE diff(const ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE sum(const ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE >
   void make_lower(ITERABLE & iterable);

   template < typename ITERABLE >
   void make_upper(ITERABLE & iterable);

   template < typename ITERABLE >
   void erase(ITERABLE & iterable, typename ITERABLE::iterator typename first = NULL, typename ITERABLE::iterator typename last = NULL);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void implode(const ITERABLE & iterable, TYPE & rwstr, const TYPE2 & lpcszSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void reverse_implode(const ITERABLE & iterable, TYPE & rwstr, const TYPE & lpcszSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE, typename TYPE2, typename TYPE3 >
   void implode_ex(const ITERABLE & iterable, TYPE & rwstr, const TYPE2 & lpcszSeparator = "", const TYPE3 & lpcszLastSeparator = NULL, typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE >
   void if_prefix_implode_ex(const ITERABLE & iterable, TYPE & rwstr, const TYPE & lpcszIfHasElementPrefix = NULL, const TYPE & lpcszSeparator = NULL, const TYPE & lpcszLastSeparator = NULL, bool bUseLast = true, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE >
   void prefix(ITERABLE & iterable, const ITERABLE & iterableSrc, const TYPE & pszPrefix, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE >
   void suffix(ITERABLE & iterable, const ITERABLE & iterableSrc, const TYPE & pszSuffix, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void surround(ITERABLE & iterable, const ITERABLE & iterableSrc, const TYPE & pszPrefix = NULL, const TYPE2 & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE >
   void prefix(ITERABLE & iterable, const TYPE & pszPrefix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE >
   void suffix(ITERABLE & iterable, const TYPE & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void surround(ITERABLE & iterable, const TYPE & pszPrefix = NULL, const TYPE & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   template < typename ITERABLE, typename TYPE, typename TYPE2, typename TYPE3 >
   void surround_and_implode(const ITERABLE & iterable, TYPE & str, const TYPE2 & lpcszSeparator = NULL, const TYPE3 & pszPrefix = NULL, const TYPE2 & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL);

   //template < typename ITERABLE, typename ITERABLE2>
   //void get_comparable_ida(const ITERABLE & iterable, ITERABLE2 & iterable2);

   template < typename ITERABLE, typename TYPE >
   ::count explode_command_line(const ITERABLE & iterable, const TYPE & str, char ** argv = NULL);

   template < typename ITERABLE, typename ITERABLE2 >
   bool operator == (const ITERABLE & iterable, const ITERABLE & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   bool operator != (const ITERABLE & iterable, const ITERABLE & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ::count remove_iter_ci(ITERABLE & iterable, const ITERABLE & iterableRemove);

   template < typename ITERABLE, typename ITERABLE2 >
   ::count remove_iter(ITERABLE & iterable, const ITERABLE2 & iterableRemove);

   template < typename ITERABLE, typename TYPE >
   ITERABLE & trim_right(ITERABLE & iterable, const TYPE & pszChars);

   template < typename ITERABLE, typename TYPE >
   ITERABLE & trim_left(ITERABLE & iterable, const TYPE & pszChars);

   template < typename ITERABLE, typename TYPE >
   ITERABLE & trim(ITERABLE & iterable, const TYPE & pszChars);

   template < typename ITERABLE >
   ITERABLE & trim_right(ITERABLE & iterable);

   template < typename ITERABLE >
   ITERABLE & trim_left(ITERABLE & iterable);

   template < typename ITERABLE >
   ITERABLE & trim(ITERABLE & iterable);

   // move preferred in order
   template < typename ITERABLE, typename TYPE >
   ITERABLE & preferred(ITERABLE & iterable, const TYPE & lpcsz);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & preferred_iter(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename PRED >
   bool pred_remove_first(ITERABLE & iterable, PRED pred);
   
   template < typename ITERABLE, typename PRED >
   typename ITERABLE::const_iterator pred_find_first(const ITERABLE & iterable, PRED pred);
   
   template < typename ITERABLE, typename PRED >
   typename ITERABLE::iterator pred_find_first(ITERABLE & iterable, PRED pred);

   template < typename ITERABLE, typename TYPE >
   typename index ifind_first_ci(const ITERABLE & iterable, const TYPE & lpcsz, index first, ::count count = -1);

   template < typename ITERABLE, typename TYPE >
   typename index ifind_first_begins(const ITERABLE & iterable, const TYPE & lpcsz, index find, ::count count = -1);

   template < typename ITERABLE, typename TYPE >
   typename index ifind_first_begins_ci(const ITERABLE & iterable, const TYPE & lpcsz, index find = 0, ::count count = -1);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_last_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_last(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator reverse_find_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator reverse_find(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_suffixes(const ITERABLE & iterable, const TYPE & lpcszIsSuffixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_suffixes_ci(const ITERABLE & iterable, const TYPE & lpcszIdSuffixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_prefixes(const ITERABLE & iterable, const TYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_prefixes_ci(const ITERABLE & iterable, const TYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends(const ITERABLE & iterable, const TYPE & lpcszSuffix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends_ci(const ITERABLE & iterable, const TYPE & lpcszSuffix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends_eat(const ITERABLE & iterable, TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends_eat_ci(const ITERABLE & iterable, TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins(const ITERABLE & iterable, const TYPE & lpcszPrefix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins_ci(const ITERABLE & iterable, const TYPE & lpcszPrefix, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins_eat(const ITERABLE & iterable, TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins_eat_ci(const ITERABLE & iterable, TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   bool contains_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last = NULL, ::count countMin = 1, ::count countMax = -1);

   template < typename ITERABLE, typename TYPE >
   bool icontains_ci(const ITERABLE & iterable, const TYPE & lpcsz, index first, ::count count = -1, ::count countMin = 1, ::count countMax = -1);

   template < typename ITERABLE, typename STRITERABLE, typename TYPE >
   ::count get_begins_ci(ITERABLE & iterable, STRITERABLE & stra, const TYPE & lpcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   ::count filter_begins_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename PRED >
   ::count filter(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename PRED >
   ::count filter_out(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename PRED, typename ArrayOut >
   ::count filter_out(ITERABLE & iterable, PRED pred, ArrayOut & a, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   ::count remove_first_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   ::count remove_first(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE >
   void remove_first(ITERABLE & iterable);

   template < typename ITERABLE, typename TYPE >
   ::count remove_last_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   ::count remove_last(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE >
   void remove_last(ITERABLE & iterable);

   template < typename ITERABLE, typename TYPE >
   ::count remove_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax = -1);

   template < typename ITERABLE, typename TYPE >
   ::count remove(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax = -1);

   template < typename ITERABLE, typename TYPE >
   ::count remove_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   ::count remove(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last = NULL);

   template < typename ITERABLE, typename TYPE >
   ::count remove_ci(ITERABLE & iterable, const TYPE & lpcsz);

   template < typename ITERABLE, typename TYPE >
   ::count remove(ITERABLE & iterable, const TYPE & lpcsz);

   template < typename ITERABLE, typename TYPE >
   ::count iremove_ci(ITERABLE & iterable, const TYPE & lpcsz, index first = 0, ::count count = -1);

   template < typename ITERABLE, typename TYPE >
   ::count iremove(ITERABLE & iterable, const TYPE & lpcsz, index first = 0, ::count count = -1);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   ITERABLE & explode(ITERABLE & iterable, const TYPE & strSeparator, const TYPE2 & str);

   // csstidy: Same as explode, but not within a TYPE
   template < typename ITERABLE, typename TYPE >
   ITERABLE & csstidy_explode_ws(const ITERABLE & iterable, char sep, const TYPE & psz);

   template < typename ITERABLE, typename TYPE >
   void get_format_string(const ITERABLE & iterable, TYPE & str, const TYPE & lpcszSeparator);

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   ITERABLE & add_tokens(ITERABLE & iterable, const TYPE & lpcsz, const TYPE2 & lpcszSeparator, bool bAddEmpty = true);

   template < typename ITERABLE, typename TYPE >
   TYPE encode_v16(const ITERABLE & iterable);

   template < typename ITERABLE, typename TYPE >
   void decode_v16(ITERABLE & iterable, const TYPE & psz);

   template < typename ITERABLE, typename TYPE >
   ::count get_count_except(const ITERABLE & iterable, const TYPE & psz);

   template < typename ITERABLE, typename TYPE >
   ::count get_count_except(const ITERABLE & iterable, const TYPE & str);

   template < typename ITERABLE, typename ITERABLE2 >
   ::count get_count_except_iter(const ITERABLE & iterable, const ITERABLE & iterable2);

   template < typename ITERABLE, typename TYPE >
   ::count get_count_except_ci(const ITERABLE & iterable, const TYPE & psz);

   template < typename ITERABLE, typename TYPE >
   ::count get_count_except_ci(const ITERABLE & iterable, const TYPE & str);

   template < typename ITERABLE, typename ITERABLE2 >
   ::count get_count_except_iter_ci(const ITERABLE & iterable, const ITERABLE & set);

   template < typename ITERABLE, typename TYPE >
   TYPE & get_json(const ITERABLE & iterable, TYPE & str, bool bNewLine = true);

   template < typename ITERABLE, typename TYPE >
   void c_add(ITERABLE & iterable, char ** ppsz, ::count iCount);

   template < typename ITERABLE, typename TYPE >
   void c_add(ITERABLE & iterable, char ** ppsz);

   template < typename ITERABLE, typename TYPE >
   void c_add(ITERABLE & iterable, wchar_t ** ppsz, ::count iCount);

   template < typename ITERABLE, typename TYPE >
   void c_add(ITERABLE & iterable, wchar_t ** ppsz);



   template < typename ITERABLE, typename TYPE >
   bool contains(const ITERABLE & iterable, const TYPE & value)
   {

      for (auto & item : iterable)
      {

         if (item == value)
         {

            return true;

         }

      }

      return false;

   }


   template < typename ITERABLE, typename PAIR >
   bool contains(ITERABLE & iterable, const map_association < PAIR > & assoc)
   {

      for (auto item : iterable1)
      {

         if (item == assoc.m_element1)
         {

            return true;

         }

      }

      return false;

   }


   template < typename ITERABLE, typename ITERABLE2, typename PRED >
   ITERABLE & intersect(ITERABLE & iterable, const ITERABLE2 & iterable2, PRED pred)
   {

      for (auto it = iterable.begin(); it != iterable.end();)
      {

         if (contains(iterable2, *it, pred))
         {

            iterable.remove_at(it);

         }
         else
         {

            it++;

         }

      }

      return iterable;

   }


   template < typename ITERABLE1, typename ITERABLE2 >
   ITERABLE1 & intersect(ITERABLE1 & iterable, const ITERABLE2 & iterable2)
   {

      for (auto it = iterable.begin(); it != iterable.end();)
      {

         if (contains(iterable2, *it))
         {

            iterable.erase(it);

         }
         else
         {

            it++;

         }

      }

   }


   template < typename ITERABLE, typename TYPE >
   typename TYPE maximum(const ITERABLE & iterable, TYPE maximum)
   {

      for (auto & item : iterable)
      {

         if (item > maximum)
         {

            maximum = item;

         }

      }

      return maximum;

   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_value(ITERABLE & iterable, const TYPE & value)
   {

      auto it = iterable.begin();

      for (; it != iterable.end(); it++)
      {

         if (it->m_element2 == value)
         {

            break;

         }

      }

      return it;

   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::const_iterator find_first_value(const ITERABLE & iterable, const TYPE & value)
   {

      auto it = iterable.begin();

      for (; it != iterable.end(); it++)
      {

         if (it->m_element2 == value)
         {

            break;

         }

      }

      return it;

   }


   template < typename ITERABLE >
   typename ITERABLE::const_iterator find_first_value(const ITERABLE & iterable, const typename ITERABLE::VALUE & value)
   {

      for (auto & item : iterable)
      {

         if (item.m_element2 == value)
         {

            return item;

         }

      }

      return iterable.end();

   }

   template < typename ITERABLE, typename TYPE >
   bool contains_key(const ITERABLE & iterable, const TYPE & value)
   {

      return iterable.find_first_key(value) != iterable.end();

   }

   template < typename ITERABLE, typename TYPE >
   bool contains_value(const ITERABLE & iterable, const TYPE & value)
   {

      return find_first_value(iterable, value) != iterable.end();

   }


   template < typename ITERABLE >
   bool remove_first(ITERABLE & iterable, const typename ITERABLE::TYPE & t)
   {

      auto find = find_first(iterable, t);

      if (find != iterable.end())
      {

         iterable.remove(find);

         return true;

      }

      return false;

   }


   template < typename ITERABLE >
   bool remove_last(ITERABLE & iterable, const typename ITERABLE::TYPE & t)
   {

      auto find = find_last(iterable, t);

      if (find != iterable.end())
      {

         iterable.remove(find);

         return true;

      }

      return false;
   }


   template < typename ITERABLE, typename TYPE >
   bool remove_first(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator pos = NULL, typename ITERABLE::iterator posLast = NULL)
   {

      if ((find = find_first(iterable, t, find, last)) != iterable.end())
      {

         auto posRemove = find;

         find++;

         iterable.remove_at(posRemove);

         return true;

      }

      return false;

   }


   template < typename ITERABLE, typename TYPE >
   bool remove_last(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator pos = NULL, typename ITERABLE::iterator posLast = NULL)
   {
      if ((find = find_last(iterable, t, find, last)) != iterable.end())
      {
         auto posRemove = find;
         find--;
         iterable.remove_at(posRemove);
         return true;
      }
      return false;
   }


   template < typename ITERABLE >
   void remove_first(ITERABLE & iterable)
   {

      iterable.erase(iterable.begin());

   }


   template < typename ITERABLE >
   void remove_last(ITERABLE & iterable)
   {

      iterable.erase(iterable.upper_bound());

   }


   //template < typename ITERABLE, typename TYPE >
   //bool contains_ci(const ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator pos, typename ITERABLE::iterator posLast, ::count countMin, ::count countMax)
   //{
   //   ::count count = 0;
   //   while ((count < countMin || (countMax >= 0 && count <= countMax))
   //      && (find = find_first_ci(lpcsz, find, last)) != iterable.end())
   //      count++;
   //   return count >= countMin && conditional(countMax >= 0, count <= countMax);
   //}

   
   template < typename ITERABLE, typename TYPE >
   index ifind_first(const ITERABLE & iterable, const TYPE & t, index first, ::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (iterable.element_at(first) == t)
         {

            return first;

         }

      }

      return -1;

   }


   template < typename ITERABLE, typename TYPE >
   bool icontains(const ITERABLE & iterable, const TYPE & t, index first, ::count count)
   {

      return ifind_first(iterable, t, first, count) >= 0;
      
   }


   template < typename ITERABLE, typename TYPE >
   bool contains(const ITERABLE & iterable, const TYPE & t, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last, ::count countMin, ::count countMax)
   {
      ::count count = 0;
      while ((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(iterable, t, find, last)) != iterable.end())
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }



   template < typename ITERABLE, typename TYPE >
   bool contains(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax)
   {
      ::count count = 0;
      while ((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(iterable, t, find, last)) != iterable.end())
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::const_iterator find_first(const ITERABLE & iterable, const TYPE & t, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(find, last);

      for (; iterable.valid_iter(find, last); find++)
      {

         if (*find == t)
         {

            return find;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(find, last);

      for (; iterable.is_end(find, last); find++)
      {

         if (find == t)
         {

            return find;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, class TYPE >
   ::count remove(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax)
   {
      ::count count = 0;
      if (contains(iterable, t, find, last, countMin, countMax))
         while (conditional(countMax >= 0, count < countMax) && remove_first(iterable, t, find, last))
            count++;
      return count;
   }


   template < typename ITERABLE, class TYPE >
   ::count remove_ci(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax)
   {
      ::count count = 0;
      if (contains_ci(iterable, t, find, last, countMin, countMax))
         while (conditional(countMax >= 0, count < countMax) && remove_first_ci(iterable, t, find, last))
            count++;
      return count;
   }


   //template < typename ITERABLE, class TYPE >
   //::count remove_ci(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   //{

   //   ::count c = 0;

   //   prepare_first_count(first, last);

   //   decltype(first) itRemove;

   //   for (; iterable.valid_iter(first, last);)
   //   {

   //      if (stricmp(*first, t) == 0)
   //      {

   //         itRemove = first;

   //         first++;

   //         iterable.remove_at(itRemove);

   //         c++;

   //      }
   //      else
   //      {

   //         first++;

   //      }

   //   }

   //   return c;

   //}


   template < typename ITERABLE, class TYPE >
   ::count remove(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      ::count c = 0;

      prepare_first_count(first, last);

      decltype(first) itRemove;

      for (; iterable.valid_iter(first, last);)
      {

         if (*first == t)
         {

            itRemove = first;

            first++;

            iterable.remove_at(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }


   template < typename ITERABLE, class TYPE >
   ::count remove_ci(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      ::count c = 0;

      prepare_first_count(first, last);

      decltype(first) itRemove;

      for (; iterable.valid_iter(first, last);)
      {

         if (stricmp(*first, t) == 0)
         {

            itRemove = first;

            first++;

            iterable.remove_at(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }

   template < typename ITERABLE, class TYPE >
   ::count remove(ITERABLE & iterable, const TYPE & t)
   {

      ::count c = 0;

      auto first = iterable.begin();

      for (; iterable.valid_iter(first, iterable.end());)
      {

         if (*first == t)
         {

            auto itRemove = first;

            first++;

            iterable.erase(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }


   template < typename ITERABLE, class TYPE >
   ::count remove_ci(ITERABLE & iterable, const TYPE & t)
   {

      ::count c = 0;

      auto first = iterable.begin();

      for (; iterable.valid_iter(first, iterable.end());)
      {

         if (stricmp(*first, t) == 0)
         {

            itRemove = first;

            first++;

            iterable.remove_at(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }



   template < typename ITERABLE, class TYPE >
   ::count rremove(ITERABLE & iterable, const TYPE & t, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax)
   {
      ::count count = 0;
      if (contains(iterable, t, find, last, countMin, countMax))
         while (conditional(countMax >= 0, count < countMax) && remove_last(iterable, t, find, last))
            count++;
      return count;
   }


   template < typename ITERABLE, typename ITERABLE2 >
   void copy(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      iterable.remove_all();

      for (auto & item : iterable2)
      {

         iterable.add(item);

      }

   }


   //template < typename ITERABLE, typename TYPE >
   //bool contains_value(const ITERABLE & map, const TYPE & value)
   //{


   //   auto it = map.begin();

   //   for (; it != map.end(); it++)
   //   {

   //      if (it->m_element2 == value)
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}



   //template < typename ITERABLE, typename TYPE >
   //ITERABLE()
   //{
   //
   //
   //}

   //template < typename ITERABLE, typename TYPE >
   //ITERABLE(const ITERABLE & iterable)
   //{
   //
   //   copy(iterable);
   //
   //}


   //template < typename ITERABLE, typename TYPE >
   //template < typename ITERABLE >
   //ITERABLE(const ITERABLE & iterable)
   //{
   //
   //   copy_iter(iterable);
   //
   //}
   //


   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void reverse_implode(const ITERABLE & iterable, TYPE & str, const TYPE2 & lpcszSeparator, typename ITERABLE::iterator first, ::count last)
   {

      str.Empty();

      string strSeparator(lpcszSeparator);

      if (first == NULL)
      {

         first = begin();

      }

      if (last == NULL)
      {

         last = upper_bound();

      }

      if (last == )

         for (auto i = last; i >= start; i--)
         {

            if (i < last)
            {
               str += strSeparator;
            }

            str += get_at(pos);

            get_previous(pos);

         }

   }



   template < typename ITERABLE, typename ITERABLE2 >
   ::count remove_iter_ci(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::count count = 0;

      for (auto & item : iterable2)
      {

         count += remove_ci(iterable, item);

      }

      return count;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::count remove_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::count count = 0;

      for (auto & item : iterable)
      {

         count += remove(iterable, item);

      }

      return count;

   }



   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void implode(const ITERABLE & iterable, TYPE & str, const TYPE2 & lpcszSeparator, typename ITERABLE::iterator start, ::count count)
   {
      str.Empty();
      TYPE strSeparator(lpcszSeparator);
      if (start < 0)
      {
         start += iterable.get_size();
      }
      typename ITERABLE::iterator last;
      if (count < 0)
      {
         last = iterable.get_size() + count;
      }
      else
      {
         last = start + count - 1;
      }
      for (typename ITERABLE::iterator i = start; i <= last; i++)
      {
         if (i > start)
         {
            str += strSeparator;
         }
         str += iterable.element_at(i);
      }
   }



   //template < typename ITERABLE, typename TYPE >
   //void reverse_implode(TYPE & str, const TYPE & lpcszSeparator, typename ITERABLE::iterator start, ::count count)
   //{
   //   str.Empty();
   //   TYPE strSeparator(lpcszSeparator);
   //   if (start < 0)
   //   {
   //      start += iterable.get_size();
   //   }
   //   typename ITERABLE::iterator last;
   //   if (count < 0)
   //   {
   //      last = iterable.get_size() + count;
   //   }
   //   else
   //   {
   //      last = start + count - 1;
   //   }
   //   for (typename ITERABLE::iterator i = last; i >= start; i--)
   //   {
   //      if (i < last)
   //      {
   //         str += strSeparator;
   //      }
   //      str += iterable.element_at(i);
   //   }
   //}


   //template < typename ITERABLE, typename TYPE >
   //TYPE reverse_implode(const TYPE & lpcszSeparator, typename ITERABLE::iterator iStart, typename ITERABLE::iterator iEnd)
   //{
   //   TYPE str;
   //   reverse_implode(str, lpcszSeparator, iStart, iEnd);
   //   return str;
   //}
   //



   //template < typename ITERABLE, typename ITERABLE >
   //bool is_equal (const ITERABLE & iterable, const ITERABLE2 & iterable2)
   //{

   //   if (iterable.get_count() != get_count())
   //   {

   //      return false;

   //   }

   //   for (auto i = iterable.begin(), auto j = iterable.begin(); i < iterable.end(); i++, j++)
   //   {

   //      if (*i != *j)
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //template < typename ITERABLE, typename TYPE >
   //template < typename ITERABLE >
   //bool operator != (const ITERABLE & iterable, const ITERABLE & iterable)
   //{

   //   return !operator == (iterable);

   //}



   template < typename ITERABLE, typename TYPE >
   ::count explode_command_line(ITERABLE & iterable, const TYPE & str, char ** argv)
   {

      TYPE strParse(str);

      while (strParse.has_char())
      {

         iterable.add((TYPE)::str::consume_command_line_argument(strParse));

      }

      if (argv != NULL)
      {

         for (typename ITERABLE::iterator i = 0; i < get_count(); i++)
         {

            char * pch = (char *)(const TYPE &)element_at(i);

            argv->add(pch);

         }

         argv->add(NULL);

      }

      return get_count();


   }




   template < typename ITERABLE, typename TYPE, typename ITERABLE2 >
   ITERABLE & add_shortest_tokens(ITERABLE & iterable, const TYPE & lpcsz, const ITERABLE2 & iterableSeparator, bool bAddEmpty, bool bWithSeparator)
   {

      ::str::tokenizer strTokenizer(lpcsz);

      TYPE strToken;

      if (bAddEmpty)
      {

         while (strTokenizer.next_shortest_token(strToken, iterableSeparator, bWithSeparator))
         {

            iterable.add(strToken);

         }

      }
      else
      {

         while (strTokenizer.next_shortest_token(strToken, iterableSeparator, bWithSeparator))
         {

            if (!strToken.is_empty())
            {

               iterable.add(strToken);

            }

         }

      }

      return iterable;

   }



   template < typename ITERABLE, typename TYPE >
   ITERABLE & add_lines(ITERABLE & iterable, const TYPE & str, bool bAddEmpty)
   {

      strsize iPos = 0;

      strsize iFindA;

      strsize iFindB;

      strsize iFind1;

      strsize iFind2;

      do
      {

         iFindA = str.find('\n', iPos);

         if (iFindA < 0)
            goto r_only;

         iFindB = str.find('\r', iPos);

         if (iFindB < 0)
            goto n_only;

         iFind1 = MIN(iFindA, iFindB);

         iFind2 = MAX(iFindA, iFindB);

         if (iFind1 > iPos)
         {

            iterable.add((TYPE)TYPE(&str[iPos], iFind1 - iPos));

         }
         else if (bAddEmpty)
         {

            iterable.add(TYPE());

         }

         if (iFind2 - iFind1 == 1)
         {

            iPos = iFind2 + 1;

         }
         else
         {

            iPos = iFind1 + 1;

         }

      } while (true);

      goto end;

   n_only:

      do
      {

         iFindA = str.find('\n', iPos);

         if (iFindA < 0)
            goto end;

         if (iFindA > iPos)
         {

            iterable.add((TYPE)TYPE(&str[iPos], iFindA - iPos));

         }
         else if (bAddEmpty)
         {

            iterable.add(TYPE());

         }

         iPos = iFindA + 1;


      } while (true);
      goto end;
   r_only:
      do
      {

         iFindB = str.find('\r', iPos);

         if (iFindB < 0)
            goto end;

         if (iFindB > iPos)
         {

            iterable.add((TYPE)TYPE(&str[iPos], iFindB - iPos));

         }
         else if (bAddEmpty)
         {

            iterable.add(TYPE());

         }

         iPos = iFindB + 1;


      } while (true);

   end:

      if (str.get_length() > iPos)
      {

         iterable.add((TYPE)TYPE(&str[iPos], str.get_length() - iPos));

      }
      else if (bAddEmpty)
      {

         iterable.add(TYPE());

      }

      return iterable;

   }





   template < typename ITERABLE, typename TYPE >
   void get_format_string(const ITERABLE & iterable, TYPE & str, const TYPE & lpcszSeparator)
   {
      str.Empty();
      if (iterable.m_nSize > 0)
      {
         str = get_at(0);
      }
      for (int32_t i = 1; i < iterable.m_nSize; i++)
      {
         str += lpcszSeparator + get_at(i);
      }
   }






   /*void XFV001Expand()
   {
   ITERABLE  strArray;
   uint_array dwa;
   for(int32_t i = 0; i < iterable.m_nSize; i++)
   {
   strArray.add_tokens(get_at(i), "/", FALSE);
   if(strArray.get_size() > 1)
   {
   for(int32_t j = 0; j < strArray.get_size(); j++)
   {
   add_unique(strArray.get_at(j));
   }
   if(strArray.get_size() > 1)
   {
   dwa.add(i);
   }
   }
   strArray.remove_all();
   }
   for(i = dwa.get_size(); --i >= 0 ;)
   {
   remove_at(dwa.get_at(i));
   }
   Sort(Compare);

   }*/


   template < typename ITERABLE, typename TYPE >
   typename bool add_unique(ITERABLE & iterable, const TYPE & str)
   {

      if (::iter::contains(iterable, str))
      {

         return false;

      }

      iterable.add((const TYPE &)str);

      return true;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::count add_unique_iter(ITERABLE & iterable, const typename ITERABLE2 & stra)
   {

      ::count count = 0;

      for (auto & str : stra)
      {

         if (iterable.add_unique(str))
         {

            count++;

         }

      }

      return count;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::count add_unique_iter_ci(ITERABLE & iterable, const typename ITERABLE2 & iterable2)
   {

      ::count count = 0;

      for (auto & str : iterable2)
      {

         if (iterable.add_unique_ci(str) != iterable.end())
         {

            count++;

         }

      }

      return count;

   }

   template < typename ITERABLE, typename PRED>
   bool pred_remove_first(ITERABLE & iterable, PRED pred)
   {

      auto it = pred_find_first(iterable, pred);

      if (it == iterable.end())
      {

         return false;

      }

      iterable.erase(it);
   
      return true;
   
   }
   
   template < typename ITERABLE, typename PRED >
   typename ITERABLE::const_iterator pred_find_first(const ITERABLE & iterable, PRED pred)
   {

      auto it = iterable.begin();

      for (; it != iterable.end(); it++)
      {

         if (pred(*it))
         {

            break;

         }

      }

      return it;

   }


   template < typename ITERABLE, typename PRED >
   typename ITERABLE::iterator pred_find_first(ITERABLE & iterable, PRED pred)
   {

      auto it = iterable.begin();

      for (; it != iterable.end(); it++)
      {

         if (pred(*it))
         {

            break;

         }

      }

      return it;

   }


   //template<class TYPE, class ARG_TYPE>
   //void list<TYPE, ARG_TYPE>::remove(iterator & it)
   //{
   //   
   //   this->remove_at(it);

   //}


   template < typename ITERABLE, typename TYPE >
   typename index ifind_first_ci(const ITERABLE & iterable, const TYPE & lpcsz, index find, ::count count)
   {

      iterable.iprepare_first_count(first, count);
      
      for (; find < count; find++)
      {
         
         if (stricmp(iterable.element_at(find), lpcsz) == 0)
         {

            return find;

         }

      }

      return -1;

   }


   template < typename ITERABLE, typename TYPE >
   typename index find_first_begins(const ITERABLE & iterable, const TYPE & lpcsz, index find, ::count count)
   {

      iterable.iprepare_first_count(find, count);
      
      for (; find < count; find++)
      {

         if (::str::begins(iterable.element_at(find), lpcsz))
         {

            return find;

         }

      }

      return -1;

   }

   template < typename ITERABLE, typename TYPE >
   typename index find_first_begins_ci(const ITERABLE & iterable, const TYPE & lpcsz, index find, ::count count)
   {

      iterable.iprepare_first_count(find, count);

      for (; find < count; find++)
      {

         if (::str::begins_ci(iterable.element_at(find), lpcsz))
         {

            return find;

         }

      }

      return -1;

   }



   template < typename ITERABLE, typename TYPE >
   index find_first_ci(const ITERABLE & iterable, const TYPE & lpcsz, index find, ::count count)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find <= last; find++)
      {
         if (iterable.element_at(find).CompareNoCase(lpcsz) == 0)
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      return ::iter::find_first(iterable, lpcsz, find, last);
   }

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_last_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      return reverse_find_ci(lpcsz, find, last);
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_last(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      return reverse_find(lpcsz, find, last);
   }



   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator reverse_find_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find >= last; find--)
      {
         if (iterable.element_at(find).CompareNoCase(lpcsz) == 0)
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator reverse_find(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find >= last; find--)
      {
         if (iterable.element_at(find).Compare(lpcsz) == 0)
            return find;
      }
      return -1;
   }




   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::ends(iterable.element_at(find), lpcsz))
            return find;
      }
      return -1;
   }

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::ends_ci(iterable.element_at(find), lpcsz))
            return find;
      }
      return -1;
   }



   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends_eat(ITERABLE & iterable, string & str, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = find_first_ends(lpcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).Left(element_at(find).length() - strlen(lpcsz));

      return find;

   }



   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_ends_eat_ci(ITERABLE & iterable, string & str, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = find_first_ends_ci(lpcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).Left(element_at(find).length() - strlen(lpcsz));

      return find;

   }



   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::begins(iterable.element_at(find), lpcsz))
            return find;
      }
      return -1;
   }

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins_ci(const ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::begins_ci(iterable.element_at(find), lpcsz))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins_eat(ITERABLE & iterable, string & str, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = find_first_begins(lpcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).Mid(strlen(lpcsz));

      return find;

   }



   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator find_first_begins_eat_ci(ITERABLE & iterable, string & str, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = find_first_begins_ci(lpcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).Mid(strlen(lpcsz));

      return find;

   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_suffixes(const ITERABLE & iterable, const TYPE & lpcszIdSuffixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::ends(lpcszIdSuffixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }

   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_suffixes_ci(const ITERABLE & iterable, const TYPE & lpcszIdSuffixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::ends_ci(lpcszIdSuffixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_prefixes(const ITERABLE & iterable, const TYPE & lpcszIdPrefixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::begins(lpcszIdPrefixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator any_prefixes_ci(const ITERABLE & iterable, const TYPE & lpcszIdPrefixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (::str::begins_ci(lpcszIdPrefixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }






   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator remove_first_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      
      if ((find = find_first_ci(lpcsz, find, last)) == iterable.end())
      {

         return false;

      }

      iterable.remove_at(find);

      return true;

   }


   //template < typename ITERABLE, typename TYPE >
   //bool remove_first(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   //{
   //   
   //   if ((find = find_first(lpcsz, find, last)) == iterable.end())
   //   {

   //      return false;

   //   }
   //   
   //   iterable.remove_at(find);

   //   return true;

   //}


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator remove_last_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      
      if ((find = find_last_ci(lpcsz, find, last)) == iterable.end())
      {

         return false;

      }
      
      iterable.remove_at(find);

      return true;

   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::iterator remove_last(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      
      if ((find = find_last(lpcsz, find, last)) == iterable.end())
      {

         return false;

      }
      
      iterable.remove_at(find);

      return true;

   }


   //template < typename ITERABLE, typename TYPE >
   //::count remove_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::count countMin, ::count countMax)
   //{
   //   ::count count = 0;
   //   if (contains_ci(lpcsz, find, last, countMin, countMax))
   //      while (conditional(countMax >= 0, count < countMax)
   //         && (find = remove_first_ci(lpcsz, find, last)) >= 0)
   //         count++;
   //   return count;
   //}






   template < typename ITERABLE, typename TYPE >
   void trim_left(ITERABLE & iterable, const TYPE & pszChars)
   {
      for (int32_t i = 0; i < iterable.m_nSize; i++)
      {
         operator[](i).trim_left(pszChars);
      }
   }


   template < typename ITERABLE, typename TYPE >
   void trim_right(ITERABLE & iterable, const TYPE & pszChars)
   {
      for (int32_t i = 0; i < iterable.m_nSize; i++)
      {
         operator[](i).trim_right(pszChars);
      }
   }


   template < typename ITERABLE, typename TYPE >
   void trim(ITERABLE & iterable, const TYPE & pszChars)
   {
      for (int32_t i = 0; i < iterable.m_nSize; i++)
      {
         operator[](i).trim(pszChars);
      }
   }



   template < typename ITERABLE, typename TYPE >
   void trim_left(ITERABLE & iterable)
   {
      for (int32_t i = 0; i < iterable.m_nSize; i++)
      {
         operator[](i).trim_left();
      }
   }


   template < typename ITERABLE, typename TYPE >
   void trim_right(ITERABLE & iterable)
   {
      for (int32_t i = 0; i < iterable.m_nSize; i++)
      {
         operator[](i).trim_right();
      }
   }


   template < typename ITERABLE, typename TYPE >
   void trim(ITERABLE & iterable)
   {
      for (int32_t i = 0; i < iterable.m_nSize; i++)
      {
         operator[](i).trim();
      }
   }


   //template < typename ITERABLE, typename TYPE >
   //typename ITERABLE::iterator add_normal(const TYPE & lpcsz)
   //{

   //   return ITERABLE::add(lpcsz);

   //}


   template < typename ITERABLE, typename TYPE >
   ::count remove_empty(ITERABLE & iterable)
   {
      ::count count = 0;
      for (typename ITERABLE::iterator i = 0; i < iterable.get_size();)
      {
         if (iterable.element_at(i).is_empty())
         {
            iterable.remove_at(i);
            count++;
         }
         else
         {
            i++;
         }
      }
      return count;
   }


















   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   ITERABLE  & explode(ITERABLE & iterable, const TYPE & strSeparator, const TYPE2 & str)
   {

      iterable.remove_all();

      return add_tokens(iterable, str, strSeparator, true);

   }

   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   ITERABLE & add_tokens(ITERABLE & iterable, const TYPE & lpcsz, const TYPE2 & lpcszSeparator, bool bAddEmpty)
   {

      ::str::tokenizer strTokenizer(lpcsz);

      string strToken;

      if (bAddEmpty)
      {

         while (strTokenizer.next_token(strToken, lpcszSeparator, false))
         {

            iterable.add(strToken);

         }

      }
      else
      {

         while (strTokenizer.next_token(strToken, lpcszSeparator, false))
         {

            if (!strToken.is_empty())
            {

               iterable.add(strToken);

            }

         }

      }

      return iterable;

   }



   template < typename ITERABLE, typename TYPE >
   ITERABLE  & csstidy_explode_ws(ITERABLE & iterable, char sep, const TYPE & psz)
   {

      TYPE istring(psz);

      // 1 = st // 2 = str
      int32_t status = 1;
      char to = '\0';

      add("");
      strsize num = 0;
      strsize len = istring.length();
      for (strsize i = 0; i < len; i++)
      {

         switch (status)
         {
         case 1:
            if (istring[i] == sep && !::str::simple_escaped(istring, i))
            {
               ++num;
               add("");
            }
            else if ((istring[i] == '"' || istring[i] == '\'' || istring[i] == '(') && !::str::simple_escaped(istring, i))
            {
               status = 2;
               to = (istring[i] == '(') ? ')' : istring[i];
               element_at(num) += (TYPE)TYPE(istring[i]);
            }
            else
            {
               element_at(num) += (TYPE)TYPE(istring[i]);
            }
            break;

         case 2:
            if (istring[i] == to && !::str::simple_escaped(istring, i))
            {
               status = 1;
            }
            element_at(num) += (TYPE)TYPE(istring[i]);
            break;
         }

      }

      return iterable;

   }




   template < typename ITERABLE, typename TYPE >
   void replace(ITERABLE & iterable, const TYPE & lpszSearch, const TYPE & lpszReplace)
   {

      for (int32_t i = 0; i < iterable.get_size(); i++)
      {

         iterable.element_at(i).replace(lpszSearch, lpszReplace);

      }

   }




   template < typename ITERABLE, typename TYPE >
   void prefix(const ITERABLE & stra, const TYPE & pszPrefix, typename ITERABLE::iterator iStart, ::count iCount)
   {

      TYPE strPrefix(pszPrefix);

      strsize iEnd;

      if (iStart < 0)
         iStart = stra.get_size() + iStart;

      if (iCount < 0)
         iEnd = stra.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (auto & str : stra)
      {

         add(strPrefix + str);

      }

   }


   template < typename ITERABLE, typename TYPE >
   void suffix(const ITERABLE & stra, const TYPE & pszSuffix, typename ITERABLE::iterator iStart, ::count iCount)
   {

      TYPE strSuffix(pszSuffix);

      strsize iEnd;

      if (iStart < 0)
         iStart = stra.get_size() + iStart;

      if (iCount < 0)
         iEnd = stra.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         add(stra.element_at(i) + strSuffix);

      }

   }


   template < typename ITERABLE, typename TYPE >
   void surround(const ITERABLE & stra, const TYPE & pszPrefix, const TYPE & pszSuffix, typename ITERABLE::iterator iStart, ::count iCount)
   {

      TYPE strPrefix(pszPrefix);

      TYPE strSuffix(pszSuffix);

      strsize iEnd;

      if (iStart < 0)
         iStart = stra.get_size() + iStart;

      if (iCount < 0)
         iEnd = stra.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         add(strPrefix + stra.element_at(i) + strSuffix);

      }

   }


   template < typename ITERABLE, typename TYPE >
   void surround(ITERABLE & iterable, const TYPE & pszPrefix, const TYPE & pszSuffix, typename ITERABLE::iterator iStart, ::count iCount)
   {

      TYPE strPrefix(pszPrefix);

      TYPE strSuffix(pszSuffix);

      strsize iEnd;

      if (iStart < 0)
         iStart = iterable.get_size() + iStart;

      if (iCount < 0)
         iEnd = iterable.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         iterable.element_at(i) = strPrefix + iterable.element_at(i);

      }

   }


   template < typename ITERABLE, typename TYPE >
   void suffix(ITERABLE & iterable, const TYPE & pszSuffix, typename ITERABLE::iterator iStart, ::count iCount)
   {

      TYPE strSuffix(pszSuffix);

      strsize iEnd;

      if (iStart < 0)
         iStart = iterable.get_size() + iStart;

      if (iCount < 0)
         iEnd = iterable.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         iterable.element_at(i) = iterable.element_at(i) + strSuffix;

      }

   }





   template < typename ITERABLE, typename TYPE, typename TYPE2, typename TYPE3 >
   void surround_and_implode(const ITERABLE & iterable, TYPE & str, const TYPE2 & pszSeparator, const TYPE3 & pszPrefix, const TYPE & pszSuffix, typename ITERABLE::iterator iStart, ::count iCount)
   {
      TYPE str;
      TYPE strSeparator(pszSeparator);
      TYPE strPrefix(pszPrefix);
      TYPE strSuffix(pszSuffix);

      typename ITERABLE::iterator iEnd;

      if (iStart < 0)
         iStart = iterable.get_size() + iStart;

      if (iCount < 0)
         iEnd = iterable.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      if (iStart <= iEnd)
      {

         str = strPrefix + iterable.element_at(iStart) + strSuffix;

         iStart++;

         for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
         {

            str += strSeparator + strPrefix + iterable.element_at(i) + strSuffix;

         }

      }

      return str;

   }



   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE diff(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ITERABLE contanerSubtracted(iterable);

      contanerSubtracted.remove_iter(iterable2);

      return contanerSubtracted;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE sum(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ITERABLE contanerAdded(iterable);

      contanerAdded += iterable2;

      return contanerAdded;

   }


   template < typename ITERABLE, typename TYPE >
   bool move_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator iIndex)
   {
      typename ITERABLE::iterator i = find_first_ci(lpcsz);
      if (i < 0)
         return false;
      iterable.remove_at(i);
      insert_at(iIndex, lpcsz);
      return true;
   }


   template < typename ITERABLE, typename TYPE >
   bool preferred(ITERABLE & iterable, const TYPE & lpcsz)
   {

      return move_ci(lpcsz, 0);

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::count preferred_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::count count = 0;

      for (auto i = upper_bound(); i >= begin(); i--)
      {

         if (preferred(*i))
            count++;

      }

      return count;

   }




   //template < typename ITERABLE, typename TYPE >
   //template < typename ITERABLE >
   //void slice(ITERABLE & stra, const_iterator iOffset, ::count count)
   //{
   //
   //   typename ITERABLE::iterator iEnd;
   //
   //   if (count < 0)
   //      iEnd = get_upper_bound(count);
   //   else
   //      iEnd = iOffset + count - 1;
   //
   //   for (typename ITERABLE::iterator i = iOffset; i <= iEnd; i++)
   //   {
   //      stra.add(iterable.element_at(i));
   //   }
   //
   //}
   //

   template < typename ITERABLE, typename TYPE >
   void erase(ITERABLE & iterable, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      
      while(iterable.valid_iter(first, last))
      {

         iterable.remove_at(first);

      }

   }





   //template < typename ITERABLE, typename TYPE >
   //bool is_empty(::count countMinimum)
   //{
   //   return iterable.get_size() < countMinimum;
   //}


   //template < typename ITERABLE, typename TYPE >
   //bool has_elements(::count countMinimum)
   //{
   //   return iterable.get_count() >= countMinimum;
   //}



   template < typename ITERABLE, typename STRITERABLE, typename TYPE >
   ::count get_begins_ci(const ITERABLE & iterable, STRITERABLE & stra, const TYPE & lpcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      typename ITERABLE::iterator i = first;
      typename ITERABLE::iterator iFind;
      ::count count = 0;
      while (true)
      {
         iFind = find_first_begins_ci(lpcsz, i, last);
         if (iFind < 0)
            return count;
         stra.add(iterable.element_at(iFind));
         i = iFind + 1;
         count++;
      }
   }


   template < typename ITERABLE, typename TYPE >
   ::count filter_begins_ci(ITERABLE & iterable, const TYPE & lpcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      typename ITERABLE::iterator i = first;
      typename ITERABLE::iterator iFind;
      ::count count = 0;
      while (true)
      {
         iFind = find_first_begins_ci(lpcsz, i, last);
         if (iFind < 0)
         {
            iterable.remove_at(i, last - i + 1);
            return count;
         }
         iterable.remove_at(i, iFind - i);
         last -= iFind - i;
         i++;
         count++;

      }
   }

   template < typename ITERABLE, typename TYPE, typename PRED >
   ::count filter(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      //   typename ITERABLE::iterator i = first;
      ::count count = 0;
      for (typename ITERABLE::iterator i = first; i <= last;)
      {
         if (pred(element_at(i)))
         {
            i++;
         }
         else
         {
            iterable.remove_at(i);
            count++;
            last--;
         }

      }
      return count;
   }


   template < typename ITERABLE, typename TYPE, typename PRED >
   ::count filter_out(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      //   typename ITERABLE::iterator i = first;
      ::count count = 0;
      for (typename ITERABLE::iterator i = first; i <= last;)
      {
         if (!pred(element_at(i)))
         {
            i++;
         }
         else
         {
            iterable.remove_at(i);
            count++;
            last--;
         }

      }
      return count;
   }

   template < typename ITERABLE, typename TYPE, typename PRED, typename ArrayOut >
   ::count filter_out(ITERABLE & iterable, PRED pred, ArrayOut & a, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      //   typename ITERABLE::iterator i = first;
      ::count count = 0;
      for (typename ITERABLE::iterator i = first; i <= last;)
      {
         if (!pred(element_at(i)))
         {
            i++;
         }
         else
         {
            a.add(iterable.element_at(i));
            iterable.remove_at(i);
            count++;
            last--;
         }

      }
      return count;
   }






   template < typename ITERABLE >
   void make_lower(ITERABLE & iterable)
   {
      for (typename ITERABLE::iterator i = 0; i < iterable.get_count(); i++)
      {
         iterable.element_at(i).make_lower();
      }
   }


   template < typename ITERABLE >
   void make_upper(ITERABLE & iterable)
   {
      for (typename ITERABLE::iterator i = 0; i < iterable.get_count(); i++)
      {
         iterable.element_at(i).make_upper();
      }
   }



   //template < typename ITERABLE, typename ITERABLE2 >
   //void get_comparable_ida(const ITERABLE & iterable, ITERABLE2 & iterable2)
   //{

   //   array < id > ida;

   //   for (int32_t i = 0; i < get_count(); i++)
   //   {
   //      iterable2.add(element_at(i));
   //   }

   //   return ida;

   //}




   template < typename ITERABLE, typename TYPE >
   TYPE encode_v16(const ITERABLE & iterable)
   {
      TYPE strEncode;
      for (int32_t ui = 0; ui < iterable.get_count(); ui++)
      {
         TYPE & str = iterable.element_at(ui);
         strEncode += hex::lower_from((const char*)str, str.get_length());
         strEncode += "00";
         /*      for(int32_t uj = 0; uj < str.length(); uj++)
         {
         char sz[32];
         itoa_dup(sz, str[uj], 16);
         if(strlen_dup(sz) == 0)
         {
         strEncode += "00";
         }
         else if(strlen_dup(sz) == 1)
         {
         strEncode += "0";
         strEncode += sz;
         }
         else if(strlen_dup(sz) == 2)
         {
         strEncode += sz;
         }
         }*/

      }
      return strEncode;
   }




   template < typename ITERABLE, typename TYPE >
   void decode_v16(const ITERABLE & iterable, const TYPE & psz)
   {
      int32_t iSize = 1024;
      char * str = NULL;
      if (psz == NULL)
         return;
      while (*psz != '\0')
      {
         psz++;
         if (*psz == '\0')
            break;
         char sz[3];
         sz[0] = psz[-1];
         sz[1] = psz[0];
         sz[2] = '\0';
         const TYPE & pszEnd;
         int32_t iConversion = ::atoi_dup(sz, &pszEnd, 16);
         char ch = static_cast <char> (iConversion);
         if (ch == '\0')
         {
            add(str);
            str = NULL;
            iSize = 1024;
         }
         else
         {
            if (str == NULL)
            {
               str = (char *)memory_alloc(iSize);
            }
            else if (iSize < (strlen_dup(str) + 1))
            {
               char * strOld = str;
               iSize += 1024;
               char * strNew = (char *)memory_alloc(iSize);
               strcpy_dup(strNew, strOld);
               str = strNew;
            }
            sz[0] = ch;
            sz[1] = '\0';
            strcat_dup(str, sz);
         }
         psz++;
      }

   }



   template < typename ITERABLE, typename TYPE >
   ::count get_count_except(const ITERABLE & iterable, const TYPE & str)
   {

      ::count c = get_count();

      for (typename ITERABLE::iterator i = 0; i < get_count(); i++)
      {

         if (element_at(i) == str)
            c--;

      }

      return c;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::count get_count_except_iter(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::count c = get_count();

      for (auto & item : iterable)
      {

         if (stra.contains(item))
            c--;

      }

      return c;

   }



   template < typename ITERABLE, typename TYPE >
   ::count get_count_except_ci(const ITERABLE & iterable, const TYPE & str)
   {

      ::count c = get_count();

      for (typename ITERABLE::iterator i = 0; i < get_count(); i++)
      {

         if (element_at(i).CompareNoCase(str) == 0)
            c--;

      }

      return c;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::count get_count_except_iter_ci(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::count c = get_count();

      for (auto & item : iterable)
      {

         if (stra.contains_ci(item))
            c--;

      }

      return c;

   }



   template < typename ITERABLE, typename TYPE >
   TYPE & get_json(const ITERABLE & iterable, TYPE & str, bool bNewLine)
   {

      str += "[";

      auto it = iterable.begin();

      if (iterable.get_count() > 0)
      {

         str += "\"";

         str += *it;

         str += "\"";

         it++;

      }

      for (; iterable.valid_iter(it, iterable.end()); it++)
      {

         if (bNewLine)
         {

            str += ", \r\n";

         }
         else
         {

            str += ", ";

         }

         str += "\"";

         str += *it;

         str += "\"";

      }

      if (bNewLine)
      {

         str += "\r\n";

      }

      str += "]";

      return str;

   }





   template < typename ITERABLE, typename TYPE, typename TYPE2, typename TYPE3 >
   void implode_ex(const ITERABLE & iterable, TYPE & str, const TYPE2 & lpcszSeparator, const TYPE3 & lpcszLastSeparator, typename ITERABLE::const_iterator start, typename ITERABLE::const_iterator end)
   {

      str.Empty();

      TYPE strSeparator(lpcszSeparator);

      if (start == NULL)
      {

         start = iterable.upper_bound();

      }

      typename ITERABLE::iterator last;

      if (end == NULL)
      {

         start = iterable.upper_bound();

      }

      auto i = start;

      if (i != last)
      {

         str = *i;

         i++;

         if (i != iterable.end())
         {

            for (; i != last; i++)
            {

               str += strSeparator;

               str += *i;

            }

            str += lpcszLastSeparator;

            str += *i;

         }

      }

   }




   template < typename ITERABLE, typename TYPE >
   void if_prefix_implode_ex(const ITERABLE & iterable, TYPE & str, const TYPE & lpcszIfHasElementPrefix, const TYPE & lpcszSeparator, const TYPE & lpcszLastSeparator, bool bUseLast, typename ITERABLE::iterator start, ::count count)
   {

      str.Empty();

      TYPE strSeparator(lpcszSeparator);

      if (start < 0)
      {
         start += iterable.get_size();
      }
      typename ITERABLE::iterator last;
      if (count < 0)
      {
         last = iterable.get_size() + count;
      }
      else
      {
         last = start + count - 1;
      }
      if (last >= start)
      {
         str += lpcszIfHasElementPrefix;
      }
      for (typename ITERABLE::iterator i = start; i <= last; i++)
      {
         if (i > start)
         {
            if (i == last && bUseLast)
            {
               str += lpcszLastSeparator;
            }
            else
            {
               str += strSeparator;
            }
         }
         str += iterable.element_at(i);
      }
   }


   template < typename ITERABLE, typename TYPE >
   typename ITERABLE::TYPE if_prefix_implode_ex(const ITERABLE & iterable, const TYPE & lpcszIfHasElementPrefix, const TYPE & lpcszSeparator, const TYPE & lpcszLastSeparator, bool bUseLast, typename ITERABLE::iterator iStart, typename ITERABLE::iterator iEnd)
   {
      TYPE str;
      if_prefix_implode_ex(str, lpcszIfHasElementPrefix, lpcszSeparator, lpcszLastSeparator, bUseLast, iStart, iEnd);
      return str;
   }


   /// expect strings allocated with malloc (sic, not memory_alloc) or strdup and array allocated with malloc (sic, not memory_alloc)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, char ** ppsz, ::count c)
   {

      for (typename ITERABLE::iterator i = 0; i < c; i++)
      {

         iterable.add(ppsz[i]);

         free((void *)ppsz[i]);

      }

      free((void *)ppsz);

   }

   /// expect strings allocated with malloc (sic, not memory_alloc) or strdup and array allocated with malloc (sic, not memory_alloc)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, char ** ppszParam)
   {

      char ** ppsz = ppszParam;

      while (ppsz != NULL)
      {

         char * psz = *ppsz;

         iterable.add(psz);

         free((void *)psz);

         ppsz++;

      }

      free((void *)ppsz);

   }

   /// expect strings allocated with malloc (sic, not memory_alloc) or wcsdup and array allocated with malloc (sic, not memory_alloc)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, wchar_t ** ppsz, ::count c)
   {

      for (typename ITERABLE::iterator i = 0; i < c; i++)
      {

         iterable.add(ppsz[i]);

         free((void *)ppsz[i]);

      }

      free((void *)ppsz);

   }

   /// expect strings allocated with malloc (sic, not memory_alloc) or wcsdup and array allocated with malloc (sic, not memory_alloc)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, wchar_t ** ppszParam)
   {

      wchar_t ** ppsz = ppszParam;

      while (ppsz != NULL)
      {

         wchar_t * psz = *ppsz;

         iterable.add(psz);

         free((void *)psz);

         ppsz++;

      }

      free((void *)ppsz);

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & copy_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      return copy_iter(iterable, iterable2.begin(), iterable2.end());

   }


   template < typename ITERABLE, typename ITERATOR >
   ITERABLE & copy_iter(ITERABLE & iterable, ITERATOR & iterator, ITERATOR & limit)
   {

      ASSERT_VALID(this);

      iterable.provision(iterator, limit);

      for (; iterator != limit; iterator++)
      {

         iterable.add(*iterator);

      }

      return *iterable;

   }



   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & copy_from(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      return copy_iter(iterable, iterable2.begin(), iterable2.end());

   }


   template < typename ITERABLE, typename ITERATOR >
   ITERABLE & copy_from(ITERABLE & iterable, ITERATOR & iterator, ITERATOR & limit)
   {

      ASSERT_VALID(this);

      iterable.provision(iterator, limit);

      for (; iterator != limit; iterator++)
      {

         iterable.add(::str::from(*iterator));

      }

      return *iterable;

   }


   template < typename ITERABLE >
   ITERABLE  & copy(ITERABLE & iterable, var varSrc)
   {

      iterable.remove_all();

      if (varSrc.get_type() == var::type_stra)
      {

         varSrc.get_array(iterable);

      }
      else
      {
         if (varSrc.get_count() == 1)
         {

            add((TYPE)varSrc.get_string());

         }
         else if (varSrc.get_count() > 1)
         {

            varSrc.get_array(iterable);

         }

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & slice(ITERABLE & iterable, ITERABLE2 & iterable2, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         iterable2.add(*first);

      }

      iterable.erase(first, last);

      return iterable2;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & islice(ITERABLE & iterable, ITERABLE2 & iterable2, index first, ::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         iterable2.add(iterable.element_at(first));

      }

      iterable.remove_at(first, count-first);

      return iterable2;

   }

   template < typename ITERABLE, typename TYPE >
   ITERABLE & add_data(ITERABLE & iterable, const TYPE * pdata, ::count count)
   {

      for (index i = 0; i < count; i++)
      {

         iterable.add(pdata[i]);

      }

   }


   template < typename ITERABLE, typename TYPE >
   ITERABLE & add_item(ITERABLE & iterable, const TYPE & t, ::count n)
   {

      while (n > 0)
      {

         iterable.add(t);

         n--;

      }

   }


} // namespace iter



template < typename ITERABLE >
class iterable :
   public ITERABLE
{
public:

   typedef typename ITERABLE::iterator          iterator;
   typedef typename ITERABLE::const_iterator    const_iterator;
   typedef typename ITERABLE                    Iterable;
   typedef typename Iterable::BASE_TYPE         Type;
   typedef iterable                             Container;


   template < typename TYPE >
   bool add_unique(const TYPE & str)
   {

      return ::iter::add_unique(*this, str);

   }


   template < typename TYPE >
   bool add_unique_ci(const TYPE & str)
   {

      return ::iter::add_unique_ci(*this, str);

   }


   template < typename TYPE >
   bool contains_iter_ci(const TYPE & str, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL, ::count countMin = 1, ::count countMax = -1) const
   {

      return ::iter::contains_ci(*this, str, find, last, countMin, countMax);

   }


   template < typename TYPE >
   bool contains_iter(const TYPE & str, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL, ::count countMin = 1, ::count countMax = -1) const
   {

      return ::iter::contains(*this, str, find, last, countMin, countMax);

   }


   template < typename TYPE >
   bool icontains_ci(const TYPE & str, index find, ::count count, ::count countMin /*= 1*/, ::count countMax = -1) const
   {

      return ::iter::icontains_ci(*this, str, find, last, countMin, countMax);

   }


   template < typename TYPE >
   bool icontains(const TYPE & str, index find, ::count count, ::count countMin /*= 1*/, ::count countMax = -1) const
   {

      return ::iter::icontains(*this, str, find, last, countMin, countMax);

   }

   template < typename TYPE >
   Type implode(const TYPE & lpcszSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL) const
   {

      Type value;

      ::iter::implode(*this, value, lpcszSeparator, iStart, iEnd);

      return value;

   }

   template < typename TYPE, typename TYPE2 >
   Type implode_ex(const TYPE & lpcszSeparator = "", const TYPE2 & lpcszLastSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL) const
   {

      Type value;

      ::iter::implode_ex(*this, value, lpcszSeparator, lpcszLastSeparator, iStart, iEnd);

      return value;

   }




   template < typename ITERABLE, typename TYPE >
   void prefix(ITERABLE & iterable, const ITERABLE & iterableSrc, const TYPE & pszPrefix, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL)
   {

      ::iter::prefix(*this, iterableSrc, pszPrefix, iStart, iEnd);

   }

   template < typename ITERABLE, typename TYPE >
   void suffix(ITERABLE & iterable, const ITERABLE & iterableSrc, const TYPE & pszSuffix, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL) 
   {

      ::iter::suffix(*this, iterableSrc, pszPrefix, iStart, iEnd);

   }


   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void surround(ITERABLE & iterable, const ITERABLE & iterableSrc, const TYPE & pszPrefix = NULL, const TYPE2 & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL)
   {

      ::iter::surround(*this, iterableSrc, pszPrefix, iStart, iEnd);

   }


   template < typename ITERABLE, typename TYPE >
   void prefix(ITERABLE & iterable, const TYPE & pszPrefix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL)
   {

      ::iter::prefix(*this, pszPrefix, iStart, iEnd);

   }


   template < typename ITERABLE, typename TYPE >
   void suffix(ITERABLE & iterable, const TYPE & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL)
   {

      ::iter::suffix(*this, pszPrefix, iStart, iEnd);

   }


   template < typename ITERABLE, typename TYPE, typename TYPE2 >
   void surround(ITERABLE & iterable, const TYPE & pszPrefix = NULL, const TYPE & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL)
   {

      ::iter::surround(*this, pszPrefix, iStart, iEnd);

   }


   template < typename ITERABLE, typename TYPE, typename TYPE2, typename TYPE3 >
   void surround_and_implode(const ITERABLE & iterable, TYPE & str, const TYPE2 & lpcszSeparator = NULL, const TYPE3 & pszPrefix = NULL, const TYPE2 & pszSuffix = NULL, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = NULL)
   {

      ::iter::surround_and_implode(*this, pszPrefix, iStart, iEnd);

   }



   template < typename TYPE, typename TYPE2 >
   Container & add_tokens(const TYPE & lpcsz, const TYPE2 & lpcszSeparator, bool bAddEmpty = true)
   {

      return ::iter::add_tokens(*this, lpcsz, lpcszSeparator, bAddEmpty);

   }

   template < typename TYPE >
   Container & add_lines(const TYPE & str, bool bAddEmpty = true)
   {

      return ::iter::add_lines(*this, str, bAddEmpty);

   }

   template < typename TYPE, typename ITERABLE2 >
   Container & add_shortest_tokens(const TYPE & lpcsz, const ITERABLE2 & iterableSeparator, bool bAddEmpty = true, bool bWithSeparator = FALSE)
   {

      return ::iter::add_shortest_tokens(*this, lpcsz, iterableSeparator, bAddEmpty, bWithSeparator);

   }

   template < typename TYPE >
   Container & trim_right(const TYPE & pszChars)
   {

      return ::iter::trim_right(*this, pszChars);

   }

   template < typename TYPE >
   Container & trim_left(const TYPE & pszChars)
   {

      return ::iter::trim_left(*this, pszChars);

   }

   template < typename TYPE >
   Container & trim(const TYPE & pszChars)
   {

      return ::iter::trim(*this, pszChars);

   }

   Container & trim_right()
   {

      return ::iter::trim_right(*this);

   }

   Container & trim_left()
   {

      return ::iter::trim_left(*this);

   }


   Container & trim()
   {

      return ::iter::trim(*this);

   }


   // move preferred in order
   template < typename TYPE >
   Container & preferred(const TYPE & lpcsz)
   {

      return ::iter::preferred(*this, lpcsz);

   }


   template < typename ITERABLE2 >
   Container & preferred_iter(const ITERABLE2 & iterable2)
   {

      return ::iter::preferred_iter(*this, iterable2);

   }

   template < typename ITERABLE2 >
   ::count remove_iter(const ITERABLE2 & iterable2)
   {

      return ::iter::remove_iter(*this, iterable2);

   }


   template < typename ITERABLE2 >
   Container & add_iter(const ITERABLE2 & iterable2)
   {

      return ::iter::add_iter(*this, iterable2);

   }


   template < typename ITERABLE2 >
   Container diff(const ITERABLE2 & iterable2) const
   {

      return ::iter::diff(*this, iterable2);

   }


   template < typename ITERABLE2 >
   Container sum(const ITERABLE2 & iterable2) const
   {

      return ::iter::sum(*this, iterable2);

   }

   template < typename TYPE >
   ::count remove_element_iter_ci(const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL, ::count countMin = 0, ::count countMax = -1)
   {

      return ::iter::remove_ci(lpcsz, find, last, countMin, countMax);

   }

   template < typename TYPE >
   ::count remove_element_iter(const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL, ::count countMin = 0, ::count countMax = -1)
   {

      return ::iter::remove_ci(lpcsz, find, last, countMin, countMax);

   }


   template < typename TYPE >
   typename ITERABLE::iterator reverse_find_ci(const TYPE & lpcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0)
   {

      return ::iter::reverse_find_ci(*this, lpcsz, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator reverse_find(const TYPE & lpcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0)
   {

      return ::iter::reverse_find(*this, lpcsz, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator any_suffixes(const TYPE & lpcszIsSuffixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::any_suffixes(*this, lpcszIsSuffixed, find, last);

   }

   template < typename TYPE >
   bool any_suffixes_ci(const TYPE & lpcszIsSuffixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::any_suffixes_ci(*this, lpcszIsSuffixed, find, last) != end();

   }

   template < typename TYPE >
   typename ITERABLE::iterator any_prefixes(const TYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::any_prefixes(*this, lpcszIsPrefixed, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator any_prefixes_ci(const TYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::any_prefixes_ci(*this, lpcszIsPrefixed, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_ends(const TYPE & lpcszSuffix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_ends(*this, lpcszSuffix, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_ends_ci(const TYPE & lpcszSuffix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_ends_ci(*this, lpcszSuffix, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_ends_eat(TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_ends_eat(*this, str, lpcsz, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_ends_eat_ci(TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_ends_eat_ci(*this, str, lpcsz, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_begins(const TYPE & lpcszPrefix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_begins(*this, lpclpcszPrefixsz, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_begins_ci(const TYPE & lpcszPrefix, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_begins_ci(*this, lpcszPrefix, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_begins_eat(TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_begins_eat(*this, str, lpcsz, find, last);

   }

   template < typename TYPE >
   typename ITERABLE::iterator find_first_begins_eat_ci(TYPE & str, const TYPE & lpcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::find_first_begins_eat_ci(*this, str, lpcsz, find, last);

   }

   template < typename STRITERABLE, typename TYPE >
   ::count get_begins_ci(STRITERABLE & stra, const TYPE & lpcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::get_begins_ci(*this, stra, lpcsz, first, last);

   }

   
   template < typename TYPE >
   ::count filter_begins_ci(const TYPE & lpcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::filter_begins_ci(*this, lpcsz, first, last);

   }


   template < typename PRED >
   ::count filter(PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::filter(*this, pred, first, last);

   }

   template < typename PRED >
   ::count filter_out(PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::filter_out(*this, pred, first, last);

   }

   template < typename PRED, typename ArrayOut >
   ::count filter_out(PRED pred, ArrayOut & a, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::filter_out(*this, pred, a, first, last);

   }

   template < typename TYPE >
   ::count remove_first_ci(const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::remove_first_ci(*this, lpcsz, first, last);

   }

   template < typename TYPE >
   ::count remove_first(const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::remove_first(*this, lpcsz, first, last);

   }

   template < typename TYPE >
   ::count remove_last_ci(const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::remove_last_ci(*this, lpcsz, first, last);

   }

   template < typename TYPE >
   ::count remove_last(const TYPE & lpcsz, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   {

      return ::iter::remove_last(*this, lpcsz, first, last);

   }


   
   void remove_first()
   {

      ::iter::remove_first(*this);

   }


   void remove_last()
   {

      ::iter::remove_last(*this);

   }


   Type pop_first()
   {

      Type t = first();

      remove_first();

      return t;

   }


   Type pop_last()
   {

      Type t = last();

      remove_last();

      return t;

   }

   template < typename TYPE, typename TYPE2 >
   Container & explode(const TYPE & strSeparator, const TYPE2 & str)
   {

      return ::iter::explode(*this, strSeparator, str);

   }

   // csstidy: Same as explode, but not within a TYPE
   template < typename TYPE >
   Container & csstidy_explode_ws(const char sep, const TYPE & psz)
   {

      return ::iter::csstidy_explode_ws(*this, sep, psz);

   }

   template < typename TYPE >
   void get_format_string(const TYPE & str, const TYPE & lpcszSeparator) const
   {

      return ::iter::get_format_string(*this, str, lpcszSeparator);

   }

   template < typename TYPE >
   TYPE & get_json(TYPE & str, bool bNewLine = true) const
   {

      return ::iter::get_json(*this, str, bNewLine);

   }

   template < typename TYPE >
   void c_add(char ** ppsz, ::count iCount)
   {

      return ::iter::c_add(*this, ppsz, iCount);

   }

   template < typename TYPE >
   void c_add(char ** ppsz)
   {

      return ::iter::c_add(*this, ppsz);

   }

   template < typename TYPE >
   void c_add(wchar_t ** ppsz, ::count iCount)
   {

      return ::iter::c_add(*this, ppsz, iCount);

   }

   template < typename TYPE >
   void c_add(wchar_t ** ppsz)
   {

      return ::iter::c_add(ppsz);

   }


   template < typename TYPE >
   bool contains_key(const TYPE & key) const
   {

      return ::iter::contains_key(*this, key);

   }


   template < typename TYPE >
   bool contains_value(const TYPE & value) const
   {

      return ::iter::contains_value(*this, value);

   }


   template < typename TYPE >
   bool contains(const TYPE & value) const
   {

      return ::iter::contains(*this, value);

   }


   template < typename TYPE >
   bool contains(const TYPE & value, const_iterator first, const_iterator last = NULL) const
   {

      return ::iter::contains(*this, value, first, last);

   }

   template < typename TYPE >
   bool icontains_ci(const TYPE & value, index first = 0, ::count count = -1) const
   {

      return ::iter::icontains_ci(*this, value, first, count);

   }


   template < typename TYPE >
   bool icontains(const TYPE & value, index first = 0, ::count count = -1) const
   {

      return ::iter::icontains(*this, value, first, count);

   }

   template < typename TYPE >
   bool remove(const TYPE & value)
   {

      return ::iter::remove(*this, value);

   }


   bool remove_empty()
   {

      return ::iter::remove_empty(*this);

   }


   template < typename ITERABLE2 >
   ITERABLE & intersect(const ITERABLE2 & iterable2)
   {

      return ::iter::intersect(*this, iterable2);

   }

   template < typename ITERABLE2 >
   typename ::count add_unique_iter(const ITERABLE2 & stra)
   {

      return ::iter::add_unique_iter(*this, stra);

   }

   template < typename ITERABLE2 >
   typename ::count add_unique_iter_ci(const ITERABLE2 & stra)
   {

      return ::iter::add_unique_iter_ci(*this, stra);

   }

   template < typename PRED >
   bool pred_remove_first(PRED pred)
   {

      return ::iter::pred_remove_first(*this, pred);

   }

   template < typename PRED >
   typename ITERABLE::const_iterator pred_find_first(PRED pred) const
   {

      return ::iter::pred_find_first(*this, pred);

   }

   template < typename PRED >
   typename ITERABLE::iterator pred_find_first(PRED pred)
   {

      return ::iter::pred_find_first(*this, pred);

   }

   Container slice(typename ITERABLE::iterator first, typename ITERABLE::iterator last = NULL)
   {

      Container iterableSlice;

      ::iter::slice(*this, iterableSlice, first, last);

      return iterableSlice;


   }

   Container islice(index first, ::count count = -1)
   {

      Container iterableSlice;

      ::iter::islice(*this, iterableSlice, first, count);

      return iterableSlice;


   }

   //template < typename TYPE >
   //typename ITERABLE::const_iterator find_first_begins(const TYPE & lpcszPrefix, typename ITERABLE::const_iterator find = NULL, typename ITERABLE::const_iterator last = NULL) const
   //{

   //   return ::iter::find_first_begins(*this, lpcszPrefix, find, last);

   //}

   //template < typename TYPE >
   //typename ITERABLE::iterator find_first_begins(const TYPE & lpcszPrefix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   //{

   //   return ::iter::find_first_begins(*this, lpcszPrefix, find, last);

   //}

   //template < typename TYPE >
   //typename ITERABLE::const_iterator find_first_begins_ci(const TYPE & lpcszPrefix, typename ITERABLE::const_iterator find = NULL, typename ITERABLE::const_iterator last = NULL) const
   //{

   //   return ::iter::find_first_begins_ci(*this, lpcszPrefix, find, last);

   //}

   //template < typename TYPE >
   //typename ITERABLE::iterator find_first_begins_ci(const TYPE & lpcszPrefix, typename ITERABLE::iterator find = NULL, typename ITERABLE::iterator last = NULL)
   //{

   //   return ::iter::find_first_begins_ci(*this, lpcszPrefix, find, last);

   //}

   template < typename TYPE >
   typename index ifind_first_begins(const TYPE & lpcszPrefix, typename ITERABLE::const_iterator find = NULL, typename ITERABLE::const_iterator last = NULL) const
   {

      return ::iter::ifind_first_begins(*this, lpcszPrefix, find, last);

   }

   
   template < typename TYPE >
   typename index ifind_first_begins(const TYPE & lpcszPrefix, index first = 0, ::count count = -1)
   {

      return ::iter::ifind_first_begins(*this, lpcszPrefix, first, count);

   }


   template < typename TYPE >
   typename index ifind_first(const TYPE & lpcszPrefix, index find = 0, ::count count = -1) const
   {

      return ::iter::ifind_first(*this, lpcszPrefix, first, count);

   }


   template < typename TYPE >
   typename index ifind_first(const TYPE & lpcszPrefix, index find = 0, ::count count = -1)
   {

      return ::iter::ifind_first(*this, lpcszPrefix, find, count);

   }


   template < typename TYPE >
   typename index ifind_first_ci(const TYPE & lpcszPrefix, index find = 0, ::count count = -1) const
   {

      return ::iter::ifind_first_ci(*this, lpcszPrefix, find, count);

   }

   template < typename TYPE >
   typename index ifind_first_ci(const TYPE & lpcszPrefix, index find = 0, ::count count = -1)
   {

      return ::iter::ifind_first_ci(*this, lpcszPrefix, find, count);

   }

   template < typename SWAP >
   typename void quick_sort(SWAP swap, bool bAsc = true)
   {

      ::sort::quick_sort(*this, swap, bAsc)

   }

};




