#pragma once

class CLASS_DECL_VMSWIN WinFileSet : 
   public ex2::file_set
{
public:

   AStrArray		m_straSearch;
   AStrArray		m_straFilter;
	AStrArray		m_straFile;

   WinFileSet(::ca::application * papp);
	virtual ~WinFileSet();

   virtual void add_search(AStrArray & stra);
   virtual void add_filter(AStrArray & stra);
   virtual int get_file_count();
   virtual void file_at(int i, string & wstr);
   virtual int find_first_file(const char * lpcszFilePath);
   virtual void clear_search();
   virtual void clear_filter();
   virtual void clear_file();
   virtual void refresh();
};

