// Windows/Defs.h

#pragma once

inline bool LRESULTToBool(LRESULT v) { return (v != FALSE); }
inline bool WINBOOLToBool(bool v) { return (v != FALSE); }
inline bool BoolToBOOL(bool v) { return (v ? TRUE: FALSE); }

