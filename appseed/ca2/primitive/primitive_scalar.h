#pragma once


class CLASS_DECL_ca DoubleScalar
{
public:

   void SetScalar(int32_t i, double d);
   virtual void OnSetScalar(int32_t i, double d);
   virtual double GetMinScalar(int32_t i);
   virtual double GetScalar(int32_t i);
   virtual double GetMaxScalar(int32_t i);
};


class CLASS_DECL_ca IntScalar
{
public:

   void SetScalar(int32_t i, int32_t iValue);
   virtual void OnSetScalar(int32_t i, int32_t iValue);
   virtual void GetMinScalar(int32_t i, int32_t &iValue);
   virtual void GetScalar(int32_t i, int32_t &iValue);
   virtual void GetMaxScalar(int32_t i, int32_t &iValue);
};

