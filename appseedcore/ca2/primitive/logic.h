#pragma once

inline bool xor(bool b1, bool b2)
{
   return (!b1 && b2) || (b1 && !b2);
}

inline bool is_different(bool b1, bool b2)
{
   return xor(b1, b2);
}

inline bool is_equivalent(bool b1, bool b2)
{
   return (b1 && b2) || (!b1 && !b2);
}

inline bool is_lesser(bool b1, bool b2)
{
   return !b1 && b2;
}

inline bool is_lesser_or_equal(bool b1, bool b2)
{
   return !(b1 && b2);
}

inline bool is_greater_or_equal(bool b1, bool b2)
{
   return !b1 || b2;
}

inline bool is_greater(bool b1, bool b2)
{
   return b1 && !b2;
}


inline bool conditional(bool p, bool q)
{
   return is_greater_or_equal(p, q);
}