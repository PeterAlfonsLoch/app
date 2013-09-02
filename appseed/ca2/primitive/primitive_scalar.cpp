#include "framework.h"

void DoubleScalar::SetScalar(int32_t i, double d)
{
   OnSetScalar(i, d);
}
void DoubleScalar::OnSetScalar(int32_t i, double d)
{
   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(d);
   // does nothing.
}

double DoubleScalar::GetMinScalar(int32_t i)
{
   UNREFERENCED_PARAMETER(i);
   return 1.0; // by default
}

double DoubleScalar::GetScalar(int32_t i)
{
   UNREFERENCED_PARAMETER(i);
   return 1.0; // by default
}

double DoubleScalar::GetMaxScalar(int32_t i)
{
   UNREFERENCED_PARAMETER(i);
   return 1.0; // by default
}



























void IntScalar::SetScalar(int32_t i, int32_t iValue)
{
   OnSetScalar(i, iValue);
}
void IntScalar::OnSetScalar(int32_t i, int32_t iValue)
{
   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(iValue);
   // does nothing.
}

void IntScalar::GetMinScalar(int32_t i, int32_t & iValue)
{
   UNREFERENCED_PARAMETER(i);
   iValue = 0; // by default
}

void IntScalar::GetScalar(int32_t i, int32_t & iValue)
{
   UNREFERENCED_PARAMETER(i);
   iValue = 1; // by default
}

void IntScalar::GetMaxScalar(int32_t i, int32_t & iValue)
{
   UNREFERENCED_PARAMETER(i);
   iValue = 1; // by default
}

