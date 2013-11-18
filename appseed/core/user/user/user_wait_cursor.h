#pragma once

class CLASS_DECL_CORE wait_cursor :
   virtual public object
{
public:
   wait_cursor(sp(base_application) papp);
   virtual ~wait_cursor();

public:
   void Restore();
};
