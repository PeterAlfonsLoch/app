#pragma once

class CLASS_DECL_NETSHARESERVER netshareserverApp :
   public ca84::application
{
public:
   netshareserverApp(void);
   virtual ~netshareserverApp(void);

   bool InitInstance();
   BOOL Run();
   BOOL ExitInstance();

   Ex1FactoryImpl * Ex1AppGetFactoryImpl();
   int CreateService();
   int RemoveService();
   int RunService();
   bool RunShellLink();
   bool InstallStartupLinks();
};
