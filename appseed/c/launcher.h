#pragma once


class CLASS_DECL_c launcher
{
public:


   virtual bool ensure_executable() = 0;

   virtual vsstring get_executable_path() = 0;

   virtual vsstring get_params() { return ""; }

   virtual bool start();

};


