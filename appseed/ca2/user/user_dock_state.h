// BaseDockState.h: interface for the BaseDockState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__BASEDOCKSTATE_H__52052722_AD80_4582_9A7A_018C284FB04C__INCLUDED_)
#define __BASEDOCKSTATE_H__52052722_AD80_4582_9A7A_018C284FB04C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// BaseDockState - used for docking serialization

class CLASS_DECL_ca2 BaseDockState : public ::ca2::object
{
   // DECLARE_SERIAL(BaseDockState)
   BaseDockState();

public:
// Attributes
   CPtrArray m_arrBarInfo;

public:
// Operations
   void LoadState(const char * lpszProfileName);
   void SaveState(const char * lpszProfileName);
   void clear(); //deletes all the barinfo's
   uint32_t GetVersion();

// Implementation
protected:
   bool m_bScaling;
   rect m_rectDevice;
   rect m_rectClip;
   size m_sizeLogical;
   uint32_t m_dwVersion;

public:
   ~BaseDockState();
//   virtual void Serialize(CArchive& ar);

   // scaling implementation
   void ScalePoint(point& pt);
   void ScaleRectPos(rect& rect);
   size GetScreenSize();
   void SetScreenSize(size& size);
};

#endif // !defined(__BASEDOCKSTATE_H__52052722_AD80_4582_9A7A_018C284FB04C__INCLUDED_)
