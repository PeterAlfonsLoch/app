#pragma once


class CLASS_DECL_ca copydesk : 
   public ::ca::window_sp
{
public:

   copydesk();
   ~copydesk();

   bool initialize();

   void set_filea(stringa & stra);

   int get_file_count();
   void get_filea(stringa & stra);

   void set_plain_text(const char * psz);
   string get_plain_text();

   
   bool desk_to_dib(::ca::dib * pdib);
   // todo
   //bool dib_to_desk(::ca::dib * pdib);
   
};