#pragma once

#if FALSE

class CLASS_DECL_AURA WinResource :
   virtual public ::ca2::resource
{
public:


   WinResource(::aura::application * papp);
   virtual ~WinResource();
   
   bool ReadResource(string & str, HINSTANCE hinst, UINT nID, const char * lpcszType);
   bool ReadResource(::file::stream_buffer & file, HINSTANCE hinst, UINT nID, const char * lpcszType);


};

#endif