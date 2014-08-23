#pragma once

class CLASS_DECL_AXIS wait_cursor :
   virtual public ::object
{
public:
   wait_cursor(sp(::aura::application) papp);
   virtual ~wait_cursor();

public:
   void Restore();
};
