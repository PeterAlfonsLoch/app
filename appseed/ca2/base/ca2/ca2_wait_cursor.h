#pragma once

class CLASS_DECL_ca2 wait_cursor :
   virtual public ::ca2::object
{
public:
   wait_cursor(sp(::ca2::application) papp);
   virtual ~wait_cursor();

public:
   void Restore();
};
