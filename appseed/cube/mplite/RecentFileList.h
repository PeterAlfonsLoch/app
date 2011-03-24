#pragma once

#define AFX_ABBREV_FILENAME_LEN 30

class RecentFileList :
   public ::database::client
{
// Constructors
public:
   RecentFileList(UINT nStart, const char * lpszSection,
      const char * lpszEntryFormat, int nSize,
      ::database::id key,
      int nMaxDispLen = AFX_ABBREV_FILENAME_LEN);

// Attributes
   int get_size() const;
   string & operator[](int nIndex);

// Operations
   virtual void remove(int nIndex);
   virtual void add(const char * lpszPathName);
   BOOL GetDisplayName(string & strName, int nIndex,
      const char * lpszCurDir, int nCurDir, BOOL bAtLeastName = TRUE) const;
   virtual void UpdateMenu(cmd_ui * pcmdui);
   virtual void ReadList();    // reads from registry or ini file
   virtual void WriteList();   // writes to registry or ini file

// Implementation
   virtual ~RecentFileList();

   //int m_nSize;                // contents of the MRU list
   //string* m_arrNames;
   stringa  m_arrNames;
   //string m_strSectionName;   // for saving
   string m_strEntryFormat;
   UINT m_nStart;              // for displaying
   int m_nMaxDisplayLength;
   string m_strOriginal;      // original menu item contents
   ::database::id       m_datakey;
};

inline int RecentFileList::get_size() const
   { return m_arrNames.get_size(); }
inline string & RecentFileList::operator[](int nIndex)
   { ASSERT(nIndex < get_size()); return m_arrNames[nIndex]; }
