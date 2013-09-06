#pragma once


class CLASS_DECL_ca launcher
{
public:


   virtual bool ensure_executable() = 0;

   virtual string get_executable_path() = 0;

   virtual string get_params() { return ""; }

   virtual bool start();

};


