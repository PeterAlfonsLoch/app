// Common/IntToString.h
// adapted from 7-zip
#pragma once


string convert_to_string(uint64_t value, uint32_t base = 10);
string convert_to_string(int64_t value, uint32_t base = 10);
string convert_to_string(uint32_t value, uint32_t base = 10);
string convert_to_zero_padded_hex(uint32_t value);

