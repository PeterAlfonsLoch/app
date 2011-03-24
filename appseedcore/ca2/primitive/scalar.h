#pragma once


class CLASS_DECL_ca DoubleScalar
{
public:

   void SetScalar(int i, double d);
   virtual void OnSetScalar(int i, double d);
   virtual double GetMinScalar(int i);
   virtual double GetScalar(int i);
   virtual double GetMaxScalar(int i);
};


class CLASS_DECL_ca IntScalar
{
public:

   void SetScalar(int i, int iValue);
   virtual void OnSetScalar(int i, int iValue);
   virtual void GetMinScalar(int i, int &iValue);
   virtual void GetScalar(int i, int &iValue);
   virtual void GetMaxScalar(int i, int &iValue);
};

