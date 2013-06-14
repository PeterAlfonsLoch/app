// _vmsgenTimer.h: interface for the C_vmsgenTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(___VMSGENTIMER_H__1CB5622E_03B6_4227_BF09_C336375C28B7__INCLUDED_)
#define ___VMSGENTIMER_H__1CB5622E_03B6_4227_BF09_C336375C28B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ca2
{

   class TimerCallback;

class CLASS_DECL_ca2 Timer  
{
public:
   class CCreate
   {
   public:
      TimerCallback *   m_ptimercallback;
      UINT            m_uiElapse;
      UINT            m_uiIDEvent;
   };

public:
   Timer();
   virtual ~Timer();
   static const UINT ID_HOVER;
};
} // namespace ca2
#endif // !defined(___VMSGENTIMER_H__1CB5622E_03B6_4227_BF09_C336375C28B7__INCLUDED_)
