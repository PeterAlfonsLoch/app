// Windows/Defs.h

#pragma once

inline bool LRESULTToBool(LRESULT v) { return (v != FALSE); }
inline bool WINBOOLToBool(int_bool v) { return (v != FALSE); }
inline int_bool BoolToWINBOOL(bool v) { return (v ? TRUE: FALSE); }

