#include "StdAfx.h"
#include "MidiViewHelper.h"

#include "MidiDocHelper.h"

MidiViewHelper::MidiViewHelper()
{

}

MidiViewHelper::~MidiViewHelper()
{

}

MidiDocHelper * MidiViewHelper::HelperGetMidiDocHelper()
{
   ::view * pview = dynamic_cast<::view *>(this);
   ASSERT(pview);
   document * pdoc = pview->get_document();
   ASSERT(pdoc);
   MidiDocHelper * phelper = dynamic_cast<MidiDocHelper *>(pdoc);
   ASSERT(phelper);
   return phelper;

}
