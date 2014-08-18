#pragma once




class CLASS_DECL_BASE stringa :
   virtual public string_array,
   virtual public ::file::serializable
{
public:


   stringa(sp(::base::application) papp = NULL);
   stringa(const char * psz);
   stringa(const string & str);
   stringa(const var & var);
   stringa(const stringa & array);
   virtual ~stringa();



   comparable_array < id > get_comparable_ida() const;

   void add(const var & var);

   void add(const property & prop);



   void get_quick_sort_ci(raw_index_array & ia)

   void write(::file::output_stream & ostream);
   void read(::file::input_stream & istream);




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
   public spa(stringa)
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
