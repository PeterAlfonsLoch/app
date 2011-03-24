// _vmsmusAttributes.h: interface for the C_vmsmusAttributes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSMUSATTRIBUTES_H__51E835B9_3A70_4B39_B9C0_6D00A88D8695__INCLUDED_)
#define AFX__VMSMUSATTRIBUTES_H__51E835B9_3A70_4B39_B9C0_6D00A88D8695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace mus
{

   class CAttributes  
   {
   public:
      CAttributes();
      virtual ~CAttributes();

   };

   enum EMidiCentralAttribute
   {
      MidiCentralAttributeMidiOutDevice,
   };
}

#endif // !defined(AFX__VMSMUSATTRIBUTES_H__51E835B9_3A70_4B39_B9C0_6D00A88D8695__INCLUDED_)
