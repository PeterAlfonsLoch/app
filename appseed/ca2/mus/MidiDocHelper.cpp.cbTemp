#include "StdAfx.h"
#include "midi_document_helper.h"
#include "Star350File.h"


MidiDocHelper::MidiDocHelper(::ca::application * papp) :
   m_sequenceHelper(papp),
   m_karaokeutilHelper(papp),
   ca(papp)
{
   m_bSavingHelper = false;

   m_pmicroke1 = new mus::microke1(papp);
}

MidiDocHelper::~MidiDocHelper()
{

   if(m_pmicroke1 != NULL)
   {
      delete m_pmicroke1;
      m_pmicroke1 = NULL;
   }

}

bool MidiDocHelper::HelperIsSaving()
{
    return m_bSavingHelper;
}

void MidiDocHelper::HelperSetModifiedFlag(BOOL bModified)
{

    HelperGetDocument()->set_modified_flag(bModified);
}

document * MidiDocHelper::HelperGetDocument()
{
    document * pdoc = dynamic_cast<document *>(this);
    ASSERT(pdoc);
    return pdoc;
}


void MidiDocHelper::HelperDeleteContents()
{
   ::mus::midi::file & file = HelperGetMidiSequence().GetFile();
   file.delete_contents();
}

BOOL MidiDocHelper::SuperHelperOnOpenDocument(const char * lpcszPath)
{
   UNREFERENCED_PARAMETER(lpcszPath);
   ASSERT(FALSE);
   return FALSE;
}

XFInfoHeader * MidiDocHelper::HelperGetXFInfoHeader()
{
   return &m_xfInfoHeaders.m_xfInfoHeader;

}

CXFInfoHeaders * MidiDocHelper::HelperGetXFInfoHeaderSet()
{
   return &m_xfInfoHeaders;
}

void MidiDocHelper::SetTempoShift(int iShift)
{
   UNREFERENCED_PARAMETER(iShift);
}

void MidiDocHelper::SetLyricDelay(int iDelay)
{
   UNREFERENCED_PARAMETER(iDelay);
}





::mus::midi::sequence & MidiDocHelper::GetMidiSequence()
{
   return m_sequenceHelper;
}

bool MidiDocHelper::HelperOpenFile(primitive::memory & storage)
{
   if(storage.get_data() == NULL || storage.get_size() <= 0)
      return false;
   if(m_pmicroke1->IsMicroke1File(storage))
   {
      primitive::memory storageExtract;
      if(!m_pmicroke1->ExtractFile(storage, storageExtract))
         return false;
      return HelperOpenFile(storageExtract);
   }
   else if(m_karaokeutilHelper.IsStar350File(storage))
   {
      Star350File starFile(get_app());
      starFile.OpenFile(&storage, 0, mus::StorageAttach);
      m_karaokeutilHelper.ConvertStar350ToXF(&starFile, &HelperGetMidiSequence(), ::mus::midi::OpenForPlaying);
      HelperGetMidiSequence().GetFile().ToWorkStorage();
   }
   else
   {
      MMRESULT mmr = HelperGetMidiSequence().OpenFile(&storage, ::mus::midi::OpenForPlaying, mus::StorageOwn);
      if(mmr != MMSYSERR_NOERROR)
         return false;
      midi_util midiutil(get_app());
      midiutil.ConvertToXF(HelperGetMidiSequence(), ::mus::midi::OpenForPlaying);
   }
   HelperGetMidiSequence().GetFile().GetTracks().GetXFInfoHeaders(&m_xfInfoHeaders);
   return TRUE;
}

BOOL MidiDocHelper::HelperOnOpenDocument(var varFile)
{


   primitive::memory storage;

   try
   {
      Application.file().as_memory(varFile, storage);
   }
   catch(not_licensed & e)
   {
      System.open_link(e.m_strUrl, "ca2-licensing");
      return FALSE;
   }
   catch(...)
   {
      return FALSE;
   }


   return HelperOpenFile(storage) ? TRUE : FALSE;


}

::mus::midi::sequence & MidiDocHelper::HelperGetMidiSequence()
{
   return m_sequenceHelper;
}
