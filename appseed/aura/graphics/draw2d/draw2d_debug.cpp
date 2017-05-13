

dump_context & operator<<(dump_context & dumpcontext,SIZE size)
{
   return dumpcontext << "(" << size.cx << " x " << size.cy << ")";
}

dump_context & operator<<(dump_context & dumpcontext,POINT point)
{
   return dumpcontext << "(" << point.x << ", " << point.y << ")";
}

dump_context & operator<<(dump_context & dumpcontext,const RECT& rect)
{
   return dumpcontext << "(L " << rect.left << ", T " << rect.top << ", R " <<
      rect.right << ", B " << rect.bottom << ")";
}


