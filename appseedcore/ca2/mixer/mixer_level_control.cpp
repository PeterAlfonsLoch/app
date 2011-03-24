#include "StdAfx.h"

namespace mixer
{

   LevelControl::LevelControl(void) :
      control(new MixerCtrlDataVolume())
   {
   }

   LevelControl::~LevelControl(void)
   {
   }

   void LevelControl::SetOrientation(e_orientation eorientation)
   {
      UNREFERENCED_PARAMETER(eorientation);
   ASSERT(FALSE);
   }

   void LevelControl::SetRange(int iMin, int iMax)
   {
      UNREFERENCED_PARAMETER(iMin);
      UNREFERENCED_PARAMETER(iMax);

   ASSERT(FALSE);
   }

   void LevelControl::SetLineSize(int iSize)
   {
      UNREFERENCED_PARAMETER(iSize);
   ASSERT(FALSE);
   }

   void LevelControl::SetPageSize(int iPage)
   {
      UNREFERENCED_PARAMETER(iPage);
   ASSERT(FALSE);
   }


   int LevelControl::GetPos() const
   {
      ASSERT(FALSE);
      return -1;
   }

   void LevelControl::SetPos(int iPos)
   {
      UNREFERENCED_PARAMETER(iPos);
      ASSERT(FALSE);
   }

   MixerCtrlDataVolume & LevelControl::get_data()
   {
      return *(MixerCtrlDataVolume* ) m_pdata;
   }


} // namespace mixer