#pragma once




class CLASS_DECL_AURA stringa :
   virtual public string_array,
   virtual public ::file::serializable
{
public:


   stringa(sp(::aura::application) papp = NULL);
   stringa(const char * psz);
   stringa(const string & str);
   stringa(const var & var);
   stringa(const stringa & array);
   virtual ~stringa();


   primitive::memory GetFormatV004();
   ::count remove_empty();
   index add_normal(const char * lpcsz);
   void trim_right(const char * pszChars);
   void trim_left(const char * pszChars);
   void trim(const char * pszChars);
   void trim_right();
   void trim_left();
   void trim();
   index add_unique(const char * lpcsz);
   ::count add_unique(const string_array & stra);
   index add_unique_ci(const char * lpcsz);
   ::count add_unique_ci(const string_array & stra);

   void make_lower();
   void make_upper();

   operator ::count() const {
      return get_count();
   }


   index get_random_index() const;

   string & random_element();
   const string & random_element() const;

   string pop_random_element();

   string pop(index i = -1);
   void slice(stringa & stra, index index, ::count ca = -1);
   void remove(index index, ::count count);
   void splice(const stringa & stra, index index, ::count ca = -1);
   void splice(const stringa & stra, index index, stringa & straRemoved, ::count ca = -1);


   // if string is found, move it to specified position
   bool move_ci(const char * lpcsz, index iIndex);

   // move preferred in order
   bool preferred(const char * lpcsz);
   ::count preferred(stringa & stra);

   index find_first_ci(const char * lpcsz, index find = 0, index last = -1) const;
   index find_first(const char * lpcsz, index find = 0, index last = -1) const;

   index reverse_find_ci(const char * lpcsz, index find = -1, index last = 0) const;
   index reverse_find(const char * lpcsz, index find = -1, index last = 0) const;


   index find_first_begins_ci(const char * lpcsz, index find = 0, index last = -1) const;
   index find_first_begins(const char * lpcsz, index find = 0, index last = -1) const;

   index str_find_first_begins_ci(const char * lpcsz, index find = 0, index last = -1) const;
   index str_find_first_begins(const char * lpcsz, index find = 0, index last = -1) const;

   bool contains_ci(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;
   bool contains(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   ::count get_begins_ci(stringa & stra, const char * lpcsz, index first = 0, index last = -1);

   ::count filter_begins_ci(const char * lpcsz, index first = 0, index last = -1);

   ::count remove_first_ci(const char * lpcsz, index find = 0, index last = -1);
   ::count remove_first(const char * lpcsz, index find = 0, index last = -1);

   ::count remove_ci(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count remove_ci(const string_array & stra);
   ::count remove(const string_array & stra);

   stringa & explode(const string & strSeparator, const string & str);

   // csstidy: Same as explode, but not within a string
   stringa & csstidy_explode_ws(char sep, const char * psz);

   void implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   string implode(const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   void reverse_implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   string reverse_implode(const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;

   void surround(const char * pszPrefix = NULL, const char * pszSuffix = NULL, index iStart = 0, ::count iCount = -1);
   string surround_and_implode(const char * lpcszSeparator = NULL, const char * pszPrefix = NULL, const char * pszSuffix = NULL, index iStart = 0, ::count iCount = -1);

   comparable_array < id > get_comparable_ida() const;

   ::count explode_command_line(const string & str, raw_array < char * > * argv = NULL);



//   void XFV001Expand();

   stringa & operator =(const var var);
   stringa & operator =(const stringa & stra);
   stringa & operator =(const int64_array & ia);
   stringa & operator =(const string_array & stra);
   stringa & operator -=(const string_array & stra);
   stringa & operator +=(const string_array & stra);

   stringa operator -(const string_array & stra) const;
   stringa operator +(const string_array & stra) const;
   stringa operator -(const stringa & stra) const;
   stringa operator +(const stringa & stra) const;





   void replace(const char * lpszSearch, const char * lpszReplace);

   void write(::file::output_stream & ostream);
   void read(::file::input_stream & istream);


   void get_format_string(string & str, const char * lpcszSeparator) const;
   void add_tokens(const char * lpcsz, const char * lpcszSeparator, bool bAddEmpty = true);
   void add_smallest_tokens(const char * lpcsz, stringa & straSeparator, bool bAddEmpty = true, bool bWithSeparator = FALSE);
   void add_lines(const string & str);


   bool is_empty(::count countMinimum = 1);
   bool has_elements(::count countMinimum = 1);

   string encode_v16();


   void decode_v16(const char * psz);

   ::count get_count_except(const char * psz);
   ::count get_count_except(const string & str);
   ::count get_count_except(const stringa & stra);

   ::count get_count_except_ci(const char * psz);
   ::count get_count_except_ci(const string & str);
   ::count get_count_except_ci(const stringa & stra);

   string get_json();

};


template <class ARRAYCOMPARE, class ARRAYRELATION>
void SortEx(ARRAYCOMPARE * pacompare,
            int32_t fCompare(const char *, const char *),
            ARRAYRELATION * parelation)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
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
   //for(int32_t i = 0; i < pacompare->get_size(); i++)
   //{
//      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
   //}
}

template <class ARRAYCOMPARE, class ARRAYRELATION>
void SortEx(ARRAYCOMPARE * pacompare,
            int32_t fCompare(const wchar_t *, const wchar_t *),
            ARRAYRELATION * parelation)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
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
   //for(int32_t i = 0; i < pacompare->get_size(); i++)
   //{
//      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
   //}
}


class string2a :
   public array < stringa >
{
public:
};

inline ::count stringa::get_count_except(const char * psz)
{

   return get_count_except(string(psz));

}

inline ::count stringa::get_count_except_ci(const char * psz)
{

   return get_count_except_ci(string(psz));

}
