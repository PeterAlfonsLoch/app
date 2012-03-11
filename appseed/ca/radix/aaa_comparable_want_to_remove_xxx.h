#pragma once

class CLASS_DECL_ca BaseComparableEq
{
public:
   BaseComparableEq(void);

   virtual bool operator ==(const BaseComparableEq & comparableeq) const;
   virtual bool operator !=(const BaseComparableEq & comparableeq) const;

   
public:
   ~BaseComparableEq(void);
};

class CLASS_DECL_ca BaseComparable :
   public BaseComparableEq
{
public:
   BaseComparable(void);

   virtual int Compare(const BaseComparable & comparable) const;
   virtual bool operator ==(const BaseComparableEq & comparableeq) const;
   virtual bool operator !=(const BaseComparableEq & comparableeq) const;
   virtual bool operator >(const BaseComparable & comparable) const;
   virtual bool operator <(const BaseComparable & comparable) const;
   virtual bool operator >=(const BaseComparable & comparable) const;
   virtual bool operator <=(const BaseComparable & comparable) const;

   static int ComparePtr(const BaseComparable * pcomparable1, const BaseComparable * pcomparable2);
public:
   ~BaseComparable(void);

};


