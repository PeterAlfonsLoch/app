#pragma once

class CLASS_DECL_ca wait_cursor :
   virtual public ::ca::object
{
public:
   wait_cursor(sp(::ca::application) papp);
   virtual ~wait_cursor();

public:
   void Restore();
};
