#pragma once


#include "gen/gen_var.h"
#include "ca/collection/string_array.h"


class CLASS_DECL_ca stringa :
   virtual public string_array,
   virtual public ex1::byte_serializable
{
public:
   stringa(::ca::application * papp = NULL);
   stringa(const stringa & base_array);
   virtual ~stringa();
   LPTSTR GetFormatV004();
   count remove_empty();
   index add_normal(const char * lpcsz);
   void trim_right();
   void trim_left();
   void trim();
   index add_unique(const char * lpcsz);
   count add_unique(const string_array & stra);
   index add_unique_ci(const char * lpcsz);
   count add_unique_ci(const string_array & stra);

   void make_lower();
   void make_upper();


   index get_random_index() const;

   string & random_element();
   const string & random_element() const;

   string pop_random_element();

   string pop(index i = 0);
   void slice(stringa & stra, index index);
   void slice(stringa & stra, index index, count count);
   void remove(index index, count count);
   void splice(const stringa & stra, index index);
   void splice(const stringa & stra, index index, count count);
   void splice(const stringa & stra, index index, stringa & straRemoved);
   void splice(const stringa & stra, index index, count count, stringa & straRemoved);


   // if string is found, move it to specified position
   bool move_ci(const char * lpcsz, index iIndex);

   // move preferred in order
   bool preferred(const char * lpcsz);
   count preferred(stringa & stra);

   index find_first_ci(const char * lpcsz, index find = 0, index last = -1) const;
   index find_first(const char * lpcsz, index find = 0, index last = -1) const;

   index find_first_begins_ci(const char * lpcsz, index find = 0, index last = -1) const;
   index find_first_begins(const char * lpcsz, index find = 0, index last = -1) const;

   index str_find_first_begins_ci(const char * lpcsz, index find = 0, index last = -1) const;
   index str_find_first_begins(const char * lpcsz, index find = 0, index last = -1) const;

   bool contains_ci(const char * lpcsz, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;
   bool contains(const char * lpcsz, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;

   count get_begins_ci(stringa & stra, const char * lpcsz, index first = 0, index last = -1);

   count filter_begins_ci(const char * lpcsz, index first = 0, index last = -1);

   count remove_first_ci(const char * lpcsz, index find = 0, index last = -1);
   count remove_first(const char * lpcsz, index find = 0, index last = -1);

   count remove_ci(const char * lpcsz, index find = 0, index last = -1, count countMin = 0, count countMax = -1);
   count remove(const char * lpcsz, index find = 0, index last = -1, count countMin = 0, count countMax = -1);

   count remove_ci(const string_array & stra);
   count remove(const string_array & stra);

   void explode(const char * lpcszSeparator, const char * psz);
   void implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;
   string implode(const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;
   void reverse_implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;
   string reverse_implode(const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;

   void surround(const char * pszPrefix = NULL, const char * pszSuffix = NULL, int iStart = 0, int iCount = -1);

//   void XFV001Expand();

   stringa & operator =(const var var);
   stringa & operator =(const stringa & stra);
   stringa & operator =(const string_array & stra);
   stringa & operator -=(const string_array & stra);
   stringa & operator +=(const string_array & stra);

   stringa operator -(const string_array & stra) const;
   stringa operator +(const string_array & stra) const;

   void replace(const char * lpszSearch, const char * lpszReplace);

   void write(ex1::byte_output_stream & ostream);
   void read(ex1::byte_input_stream & istream);


   void get_format_string(string & str, const char * lpcszSeparator) const;
   void add_tokens(const char * lpcsz, const char * lpcszSeparator, BOOL bAddEmpty);
   void add_smallest_tokens(const char * lpcsz, stringa & straSeparator, BOOL bAddEmpty, BOOL bWithSeparator = FALSE);


   bool is_empty(count countMinimum = 1);
   bool has_elements(count countMinimum = 1);

};


template <class ARRAYCOMPARE, class ARRAYRELATION>
void SortEx(ARRAYCOMPARE * pacompare,
            int fCompare(const char *, const char *),
            ARRAYRELATION * parelation)
{
   dword_array stackLowerBound;
   dword_array stackUpperBound;
   int iLowerBound;
   int iUpperBound;
   int iLPos, iUPos, iMPos;
   string str;

    if(pacompare->get_size() >= 2)
   {
        stackLowerBound.push(0);
      stackUpperBound.push(pacompare->get_size() - 1);
        while(true)
      {
         iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
                    if(fCompare(pacompare->element_at(iMPos), pacompare->element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                        pacompare->swap(iMPos, iUPos);
                        parelation->swap(iMPos, iUPos);
                  break;
               }
            }
                if(iMPos == iUPos)
               break;
                iMPos = iUPos;
            while(true)
            {
                    if(iMPos == iLPos)
                  break;
                    if(fCompare(pacompare->element_at(iLPos), pacompare->element_at(iMPos)) <= 0)
                  iLPos++;
                    else
               {
                        pacompare->swap(iMPos, iLPos);
                        parelation->swap(iMPos, iLPos);
                        break;
               }
            }
                if(iMPos == iLPos)
               break;
                iMPos = iLPos;
            }
            if(iLowerBound < iMPos - 1)
         {
                stackLowerBound.push(iLowerBound);
                stackUpperBound.push(iMPos - 1);
            }
         if(iMPos + 1 < iUpperBound)
         {
                stackLowerBound.push(iMPos + 1);
                stackUpperBound.push(iUpperBound);
         }
            if(stackLowerBound.get_size() == 0)
            break;
        }
   }
   //for(int i = 0; i < pacompare->get_size(); i++)
   //{
//      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
   //}
}

template <class ARRAYCOMPARE, class ARRAYRELATION>
void SortEx(ARRAYCOMPARE * pacompare,
            int fCompare(const wchar_t *, const wchar_t *),
            ARRAYRELATION * parelation)
{
   dword_array stackLowerBound;
   dword_array stackUpperBound;
   int iLowerBound;
   int iUpperBound;
   int iLPos, iUPos, iMPos;
   string str;

    if(pacompare->get_size() >= 2)
   {
        stackLowerBound.push(0);
      stackUpperBound.push(pacompare->get_size() - 1);
        while(true)
      {
         iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
                    if(fCompare(pacompare->element_at(iMPos), pacompare->element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                        pacompare->swap(iMPos, iUPos);
                        parelation->swap(iMPos, iUPos);
                  break;
               }
            }
                if(iMPos == iUPos)
               break;
                iMPos = iUPos;
            while(true)
            {
                    if(iMPos == iLPos)
                  break;
                    if(fCompare(pacompare->element_at(iLPos), pacompare->element_at(iMPos)) <= 0)
                  iLPos++;
                    else
               {
                        pacompare->swap(iMPos, iLPos);
                        parelation->swap(iMPos, iLPos);
                        break;
               }
            }
                if(iMPos == iLPos)
               break;
                iMPos = iLPos;
            }
            if(iLowerBound < iMPos - 1)
         {
                stackLowerBound.push(iLowerBound);
                stackUpperBound.push(iMPos - 1);
            }
         if(iMPos + 1 < iUpperBound)
         {
                stackLowerBound.push(iMPos + 1);
                stackUpperBound.push(iUpperBound);
         }
            if(stackLowerBound.get_size() == 0)
            break;
        }
   }
   //for(int i = 0; i < pacompare->get_size(); i++)
   //{
//      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
   //}
}


class string2a :
   public array_ptr_alloc < stringa, stringa & >
{
public:
};

