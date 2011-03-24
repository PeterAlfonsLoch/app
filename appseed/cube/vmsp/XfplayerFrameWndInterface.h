#pragma once

class CLASS_DECL_CA2_CUBE XfplayerFrameWndInterface  
{
   // Attributes
public:
protected:
   bool     m_bCompactMode;
   bool     m_bCompactModeEnable;
protected:
   void EnableCompactMode(bool bEnable);
public:
   void ToggleCompactMode();
   bool IsCompactModeEnabled();
   virtual void OnCompactModeChange(bool bCompact);
   bool SetCompactMode(bool bCompact);
   bool IsCompactMode();
   XfplayerFrameWndInterface();
   virtual ~XfplayerFrameWndInterface();

};

