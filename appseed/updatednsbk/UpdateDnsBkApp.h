#pragma once

class __declspec(dllexport) UpdateDnsBkApp :
   public ::icube::application
{
public:
   UpdateDnsBkApp(void);
   virtual ~UpdateDnsBkApp(void);

   bool initialize_instance();
   BOOL run();
   BOOL exit_instance();

   int CreateService();
   int RemoveService();
};
