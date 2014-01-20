// Common/IntToString.h
// adapted from 7-zip
#pragma once


string convert_to_string(uint64 value, uint32 base = 10);
string convert_to_string(int64 value, uint32 base = 10);
string convert_to_string(uint32 value, uint32 base = 10);
string convert_to_zero_padded_hex(uint32 value);

