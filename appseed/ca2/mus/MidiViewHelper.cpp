#include "StdAfx.h"
#include "midi_view_helper.h"
#include "midi_document_helper.h"


midi_view_helper::midi_view_helper()
{

}

midi_view_helper::~midi_view_helper()
{

}

MidiDocHelper * midi_view_helper::HelperGetMidiDocHelper()
{
   ::view * pview = dynamic_cast<::view *>(this);
   ASSERT(pview);
   document * pdoc = pview->get_document();
   ASSERT(pdoc);
   MidiDocHelper * phelper = dynamic_cast<MidiDocHelper *>(pdoc);
   ASSERT(phelper);
   return phelper;

}
