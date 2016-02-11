
lparam::lparam(::object * p)
{
   p->add_ref();
   m_lparam = (LPARAM)p;
}
