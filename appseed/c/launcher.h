#pragma once


class CLASS_DECL_____ launcher
{
public:


   virtual bool ensure_executable() = 0;

   virtual vsstring get_executable_path() = 0;

   virtual bool start();

};