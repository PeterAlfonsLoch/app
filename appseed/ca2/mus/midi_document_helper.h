#pragma once

class primitive::memory;
class ::mus::midi::sequence;
class KaraokeUtil;
class mus::microke1;

class CLASS_DECL_ca MidiDocHelper :
   public virtual ::radix::object
{
public:

   ::mus::midi::sequence         m_sequenceHelper;
   bool                          m_bSavingHelper;
   KaraokeUtil                   m_karaokeutilHelper;
   mus::microke1 *               m_pmicroke1;
   bool                          m_bIsSoftKaraokeFile;
   ::mus::midi::e_file_type      m_efiletype;
   CXFInfoHeaders                m_xfInfoHeaders;

   
   MidiDocHelper(::ca::application * papp);
   virtual ~MidiDocHelper();

   bool HelperOpenFile(primitive::memory & storage);

   virtual ::mus::midi::sequence & GetMidiSequence();
   virtual void SetLyricDelay(int iDelay);
   virtual void SetTempoShift(int iShift);
   CXFInfoHeaders * HelperGetXFInfoHeaderSet();
   document * HelperGetDocument();
   XFInfoHeader * HelperGetXFInfoHeader();
   BOOL SuperHelperOnOpenDocument(const char * lpcszPath);
   void HelperDeleteContents();
   BOOL HelperOnOpenDocument(var varFile);
   void HelperSetModifiedFlag(BOOL bModified = TRUE );
   bool HelperIsSaving();

    virtual ::radix::thread * HelperGetMidiPlayerCallbackThread() = 0;

   inline ::mus::midi::sequence & HelperGetMidiSequence();


};
