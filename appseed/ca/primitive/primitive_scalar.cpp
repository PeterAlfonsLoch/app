#include "framework.h"

void DoubleScalar::SetScalar(int i, double d)
{
   OnSetScalar(i, d);
}
void DoubleScalar::OnSetScalar(int i, double d)
{
   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(d);
   // does nothing.
}

double DoubleScalar::GetMinScalar(int i)
{
   UNREFERENCED_PARAMETER(i);
   return 1.0; // by default
}

double DoubleScalar::GetScalar(int i)
{
   UNREFERENCED_PARAMETER(i);
   return 1.0; // by default
}

double DoubleScalar::GetMaxScalar(int i)
{
   UNREFERENCED_PARAMETER(i);
   return 1.0; // by default
}



























void IntScalar::SetScalar(int i, int iValue)
{
   OnSetScalar(i, iValue);
}
void IntScalar::OnSetScalar(int i, int iValue)
{
   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(iValue);
   // does nothing.
}

void IntScalar::GetMinScalar(int i, int & iValue)
{
   UNREFERENCED_PARAMETER(i);
   iValue = 0; // by default
}

void IntScalar::GetScalar(int i, int & iValue)
{
   UNREFERENCED_PARAMETER(i);
   iValue = 1; // by default
}

void IntScalar::GetMaxScalar(int i, int & iValue)
{
   UNREFERENCED_PARAMETER(i);
   iValue = 1; // by default
}

