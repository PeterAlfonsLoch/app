#pragma once

class CLASS_DECL_ca wait_cursor :
   virtual public ::radix::object
{
public:
   wait_cursor(::ca::application * papp);
   virtual ~wait_cursor();

public:
   void Restore();
};
