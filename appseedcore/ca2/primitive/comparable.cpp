#include "StdAfx.h"


BaseComparableEq::BaseComparableEq(void)
{
}


BaseComparableEq::~BaseComparableEq(void)
{
}


bool BaseComparableEq::operator ==(const BaseComparableEq & comparableeq) const
{
   return typeid(*this) == typeid(comparableeq);
}


bool BaseComparableEq::operator !=(const BaseComparableEq & comparableeq) const
{
   return typeid(*this) != typeid(comparableeq);
}


BaseComparable::BaseComparable(void)
{
}


BaseComparable::~BaseComparable(void)
{
}


int BaseComparable::Compare(const BaseComparable & comparable) const
{
   return strcmp(typeid(*this).raw_name(), typeid(comparable).raw_name());
}


bool BaseComparable::operator ==(const BaseComparableEq & comparableeq) const
{
   const BaseComparable * pcomparable = dynamic_cast < const BaseComparable * > (&comparableeq);
   if(pcomparable == NULL)
      return false;
   return Compare(*pcomparable) == 0;
}


bool BaseComparable::operator !=(const BaseComparableEq & comparableeq) const
{
   const BaseComparable * pcomparable = dynamic_cast < const BaseComparable * > (&comparableeq);
   if(pcomparable == NULL)
      return true;
   return Compare(*pcomparable) != 0;
}


bool BaseComparable::operator >(const BaseComparable & comparable) const
{
   return Compare(comparable) > 0;
}


bool BaseComparable::operator <(const BaseComparable & comparable) const
{
   return Compare(comparable) < 0;
}


bool BaseComparable::operator >=(const BaseComparable & comparable) const
{
   return Compare(comparable) >= 0;
}


bool BaseComparable::operator <=(const BaseComparable & comparable) const
{
   return Compare(comparable) <= 0;
}


int BaseComparable::ComparePtr(const BaseComparable * pcomparable1, const BaseComparable * pcomparable2)
{
   if(pcomparable1 == NULL)
   {
      if(pcomparable2 == NULL)
      {
         return 0;
      }
      else
      {
         return -1;
      }
   }
   else
   {
      if(pcomparable2 == NULL)
      {
         return 1;
      }
      else
      {
         return pcomparable1->Compare(*pcomparable2);
      }
   }
}

