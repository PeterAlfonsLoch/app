#pragma once

class MixerCtrlDataVolume;

namespace mixer
{


   class CLASS_DECL_ca LevelControl :
      public control
   {
   public:
      LevelControl(void);
   public:
      ~LevelControl(void);

      virtual void SetPos(int iPos);
      virtual int GetPos() const;

      enum e_orientation
      {
         orientation_vertical,
         orientation_horizontal,
      };

      virtual void SetOrientation(e_orientation eorientation);
      virtual void SetRange(int iMin, int iMax);
      virtual void SetPageSize(int iPage);
      virtual void SetLineSize(int iSize);

      MixerCtrlDataVolume & get_data();
   };


} // namespace mixer