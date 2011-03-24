#include "StdAfx.h"
#include "XfplayerFrameWndInterface.h"

XfplayerFrameWndInterface::XfplayerFrameWndInterface()
{
   m_bCompactMode = false;
   m_bCompactModeEnable = true;
}

XfplayerFrameWndInterface::~XfplayerFrameWndInterface()
{

}

bool XfplayerFrameWndInterface::IsCompactMode()
{
   return m_bCompactMode;
}

bool XfplayerFrameWndInterface::SetCompactMode(bool bCompact)
{
   if(m_bCompactModeEnable)
   m_bCompactMode = bCompact;
   OnCompactModeChange(bCompact);
   return true;
}

void XfplayerFrameWndInterface::OnCompactModeChange(bool bCompact)
{

}

bool XfplayerFrameWndInterface::IsCompactModeEnabled()
{
   return m_bCompactModeEnable;
}

void XfplayerFrameWndInterface::EnableCompactMode(bool bEnable)
{
   m_bCompactModeEnable = bEnable;
}

void XfplayerFrameWndInterface::ToggleCompactMode()
{
   SetCompactMode(!IsCompactMode());
}
