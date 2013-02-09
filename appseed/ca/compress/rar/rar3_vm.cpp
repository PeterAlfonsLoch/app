// Rar3Vm.cpp
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives

/*
Note:
Due to performance considerations Rar VM may set Flags C incorrectly
for some operands (SHL x, 0, ... ).
Check implementation of concrete VM command
to see if it sets flags right.
*/
// from 7-zip on 2012-12-23, dawn

#include "framework.h"

/*#include "../../../C/7zCrc.h"
#include "../../../C/Alloc.h"*/

//#include "Rar3Vm.h"

namespace libcompress
{
   namespace rar3
   {

      uint32_t mem_bit_decoder::ReadBits(int32_t numBits)
      {
         uint32_t res = 0;
         for (;;)
         {
            byte b = _bitPos < _bitSize ? _data[_bitPos >> 3] : 0;
            int32_t avail = (int32_t)(8 - (_bitPos & 7));
            if (numBits <= avail)
            {
               _bitPos += numBits;
               return (res | (b >> (avail - numBits))) & ((1 << numBits) - 1);
            }
            numBits -= avail;
            res |= (uint32_t)(b & ((1 << avail) - 1)) << numBits;
            _bitPos += avail;
         }
      }

      uint32_t mem_bit_decoder::ReadBit() { return ReadBits(1); }

      namespace vm
      {

         static const uint32_t kStackRegIndex = kNumRegs - 1;

         static const uint32_t FLAG_C = 1;
         static const uint32_t FLAG_Z = 2;
         static const uint32_t FLAG_S = 0x80000000;

         static const byte CF_OP0 = 0;
         static const byte CF_OP1 = 1;
         static const byte CF_OP2 = 2;
         static const byte CF_OPMASK = 3;
         static const byte CF_BYTEMODE = 4;
         static const byte CF_JUMP = 8;
         static const byte CF_PROC = 16;
         static const byte CF_USEFLAGS = 32;
         static const byte CF_CHFLAGS = 64;

         static byte kCmdFlags[]=
         {
            /* CMD_MOV   */ CF_OP2 | CF_BYTEMODE,
            /* CMD_CMP   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_ADD   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_SUB   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_JZ    */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_JNZ   */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_INC   */ CF_OP1 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_DEC   */ CF_OP1 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_JMP   */ CF_OP1 | CF_JUMP,
            /* CMD_XOR   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_AND   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_OR    */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_TEST  */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_JS    */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_JNS   */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_JB    */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_JBE   */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_JA    */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_JAE   */ CF_OP1 | CF_JUMP | CF_USEFLAGS,
            /* CMD_PUSH  */ CF_OP1,
            /* CMD_POP   */ CF_OP1,
            /* CMD_CALL  */ CF_OP1 | CF_PROC,
            /* CMD_RET   */ CF_OP0 | CF_PROC,
            /* CMD_NOT   */ CF_OP1 | CF_BYTEMODE,
            /* CMD_SHL   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_SHR   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_SAR   */ CF_OP2 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_NEG   */ CF_OP1 | CF_BYTEMODE | CF_CHFLAGS,
            /* CMD_PUSHA */ CF_OP0,
            /* CMD_POPA  */ CF_OP0,
            /* CMD_PUSHF */ CF_OP0 | CF_USEFLAGS,
            /* CMD_POPF  */ CF_OP0 | CF_CHFLAGS,
            /* CMD_MOVZX */ CF_OP2,
            /* CMD_MOVSX */ CF_OP2,
            /* CMD_XCHG  */ CF_OP2 | CF_BYTEMODE,
            /* CMD_MUL   */ CF_OP2 | CF_BYTEMODE,
            /* CMD_DIV   */ CF_OP2 | CF_BYTEMODE,
            /* CMD_ADC   */ CF_OP2 | CF_BYTEMODE | CF_USEFLAGS | CF_CHFLAGS ,
            /* CMD_SBB   */ CF_OP2 | CF_BYTEMODE | CF_USEFLAGS | CF_CHFLAGS ,
            /* CMD_PRINT */ CF_OP0
         };

         vm::vm(): Mem(NULL) {}

         bool vm::Create()
         {
            if (Mem == NULL)
               Mem = (byte *)::MyAlloc(kSpaceSize + 4);
            return (Mem != NULL);
         }

         vm::~vm()
         {
            ::MyFree(Mem);
         }

         // vm::Execute can change CProgram object: it clears progarm if VM returns error.

         bool vm::Execute(CProgram *prg, const CProgramInitState *initState,
            CBlockRef &outBlockRef, byte_array &outGlobalData)
         {
            memcpy(R, initState->InitR, sizeof(initState->InitR));
            R[kStackRegIndex] = kSpaceSize;
            R[kNumRegs] = 0;
            Flags = 0;

            uint32_t globalSize = min((uint32_t)initState->GlobalData.get_size(), kGlobalSize);
            if (globalSize != 0)
               memcpy(Mem + kGlobalOffset, &initState->GlobalData[0], globalSize);
            uint32_t staticSize = min((uint32_t)prg->StaticData.get_size(), kGlobalSize - globalSize);
            if (staticSize != 0)
               memcpy(Mem + kGlobalOffset + globalSize, &prg->StaticData[0], staticSize);

            bool res = true;
#ifdef RARVM_STANDARD_FILTERS
            if (prg->StandardFilterIndex >= 0)
               ExecuteStandardFilter(prg->StandardFilterIndex);
            else
#endif
            {
               res = ExecuteCode(prg);
               if (!res)
                  prg->Commands[0].OpCode = CMD_RET;
            }
            uint32_t newBlockPos = GetFixedGlobalValue32(NGlobalOffset::kBlockPos) & kSpaceMask;
            uint32_t newBlockSize = GetFixedGlobalValue32(NGlobalOffset::kBlockSize) & kSpaceMask;
            if (newBlockPos + newBlockSize >= kSpaceSize)
               newBlockPos = newBlockSize = 0;
            outBlockRef.Offset = newBlockPos;
            outBlockRef.Size = newBlockSize;

            //outGlobalData.remove_all();
            uint32_t dataSize = GetFixedGlobalValue32(NGlobalOffset::kGlobalMemOutSize);
            dataSize = min(dataSize, kGlobalSize - kFixedGlobalSize);
            if (dataSize != 0)
            {
               dataSize += kFixedGlobalSize;
               outGlobalData.set_size(0, dataSize);
               for (uint32_t i = 0; i < dataSize; i++)
                  outGlobalData.add(Mem[kGlobalOffset + i]);
            }
            return res;
         }


#define SET_IP(IP) \
   if ((IP) >= numCommands) return true; \
   if (--maxOpCount <= 0) return false; \
   cmd = commands + (IP);

#define GET_FLAG_S_B(res) (((res) & 0x80) ? FLAG_S : 0)
#define SET_IP_OP1 { uint32_t val = GetOperand32(&cmd->Op1); SET_IP(val); }
#define FLAGS_UPDATE_SZ Flags = res == 0 ? FLAG_Z : res & FLAG_S
#define FLAGS_UPDATE_SZ_B Flags = (res & 0xFF) == 0 ? FLAG_Z : GET_FLAG_S_B(res)

         uint32_t vm::GetOperand32(const COperand *op) const
         {
            switch(op->Type)
            {
            case OP_TYPE_REG: return R[op->Data];
            case OP_TYPE_REGMEM: return GetValue32(&Mem[(op->Base + R[op->Data]) & kSpaceMask]);
            default: return op->Data;
            }
         }

         void vm::SetOperand32(const COperand *op, uint32_t val)
         {
            switch(op->Type)
            {
            case OP_TYPE_REG: R[op->Data] = val; return;
            case OP_TYPE_REGMEM: SetValue32(&Mem[(op->Base + R[op->Data]) & kSpaceMask], val); return;
            default: return;
            }
         }

         byte vm::GetOperand8(const COperand *op) const
         {
            switch(op->Type)
            {
            case OP_TYPE_REG: return (byte)R[op->Data];
            case OP_TYPE_REGMEM: return Mem[(op->Base + R[op->Data]) & kSpaceMask];;
            default: return (byte)op->Data;
            }
         }

         void vm::SetOperand8(const COperand *op, byte val)
         {
            switch(op->Type)
            {
            case OP_TYPE_REG: R[op->Data] = (R[op->Data] & 0xFFFFFF00) | val; return;
            case OP_TYPE_REGMEM: Mem[(op->Base + R[op->Data]) & kSpaceMask] = val; return;
            default: return;
            }
         }

         uint32_t vm::GetOperand(bool byteMode, const COperand *op) const
         {
            if (byteMode)
               return GetOperand8(op);
            return GetOperand32(op);
         }

         void vm::SetOperand(bool byteMode, const COperand *op, uint32_t val)
         {
            if (byteMode)
               SetOperand8(op, (byte)(val & 0xFF));
            else
               SetOperand32(op, val);
         }

         bool vm::ExecuteCode(const CProgram *prg)
         {
            int32_t maxOpCount = 25000000;
            const CCommand *commands = &prg->Commands[0];
            const CCommand *cmd = commands;
            uint32_t numCommands = (uint32_t) prg->Commands.get_size();
            for (;;)
            {
               switch(cmd->OpCode)
               {
#ifndef RARVM_NO_VM

               case CMD_MOV:
                  SetOperand32(&cmd->Op1, GetOperand32(&cmd->Op2));
                  break;
               case CMD_MOVB:
                  SetOperand8(&cmd->Op1, GetOperand8(&cmd->Op2));
                  break;
               case CMD_CMP:
                  {
                     uint32_t v1 = GetOperand32(&cmd->Op1);
                     uint32_t res = v1 - GetOperand32(&cmd->Op2);
                     Flags = res == 0 ? FLAG_Z : (res > v1) | (res & FLAG_S);
                  }
                  break;
               case CMD_CMPB:
                  {
                     byte v1 = GetOperand8(&cmd->Op1);
                     byte res = v1 - GetOperand8(&cmd->Op2);
                     res &= 0xFF;
                     Flags = res == 0 ? FLAG_Z : (res > v1) | GET_FLAG_S_B(res);
                  }
                  break;
               case CMD_ADD:
                  {
                     uint32_t v1 = GetOperand32(&cmd->Op1);
                     uint32_t res = v1 + GetOperand32(&cmd->Op2);
                     SetOperand32(&cmd->Op1, res);
                     Flags = (res < v1) | (res == 0 ? FLAG_Z : (res & FLAG_S));
                  }
                  break;
               case CMD_ADDB:
                  {
                     byte v1 = GetOperand8(&cmd->Op1);
                     byte res = v1 + GetOperand8(&cmd->Op2);
                     res &= 0xFF;
                     SetOperand8(&cmd->Op1, (byte)res);
                     Flags = (res < v1) | (res == 0 ? FLAG_Z : GET_FLAG_S_B(res));
                  }
                  break;
               case CMD_ADC:
                  {
                     uint32_t v1 = GetOperand(cmd->ByteMode, &cmd->Op1);
                     uint32_t FC = (Flags & FLAG_C);
                     uint32_t res = v1 + GetOperand(cmd->ByteMode, &cmd->Op2) + FC;
                     if (cmd->ByteMode)
                        res &= 0xFF;
                     SetOperand(cmd->ByteMode, &cmd->Op1, res);
                     Flags = ((res < v1 || res == v1) && FC) | (res == 0 ? FLAG_Z : (res & FLAG_S));
                  }
                  break;
               case CMD_SUB:
                  {
                     uint32_t v1 = GetOperand32(&cmd->Op1);
                     uint32_t res = v1 - GetOperand32(&cmd->Op2);
                     SetOperand32(&cmd->Op1, res);
                     Flags = res == 0 ? FLAG_Z : (res > v1) | (res & FLAG_S);
                  }
                  break;
               case CMD_SUBB:
                  {
                     uint32_t v1 = GetOperand8(&cmd->Op1);
                     uint32_t res = v1 - GetOperand8(&cmd->Op2);
                     SetOperand8(&cmd->Op1, (byte)res);
                     Flags = res == 0 ? FLAG_Z : (res > v1) | (res & FLAG_S);
                  }
                  break;
               case CMD_SBB:
                  {
                     uint32_t v1 = GetOperand(cmd->ByteMode, &cmd->Op1);
                     uint32_t FC = (Flags & FLAG_C);
                     uint32_t res = v1 - GetOperand(cmd->ByteMode, &cmd->Op2) - FC;
                     // Flags = res == 0 ? FLAG_Z : (res > v1 || res == v1 && FC) | (res & FLAG_S);
                     if (cmd->ByteMode)
                        res &= 0xFF;
                     SetOperand(cmd->ByteMode, &cmd->Op1, res);
                     Flags = (res > v1 || (res == v1 && FC)) | (res == 0 ? FLAG_Z : (res & FLAG_S));
                  }
                  break;
               case CMD_INC:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) + 1;
                     SetOperand32(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ;
                  }
                  break;
               case CMD_INCB:
                  {
                     byte res = GetOperand8(&cmd->Op1) + 1;
                     SetOperand8(&cmd->Op1, res);;
                     FLAGS_UPDATE_SZ_B;
                  }
                  break;
               case CMD_DEC:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) - 1;
                     SetOperand32(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ;
                  }
                  break;
               case CMD_DECB:
                  {
                     byte res = GetOperand8(&cmd->Op1) - 1;
                     SetOperand8(&cmd->Op1, res);;
                     FLAGS_UPDATE_SZ_B;
                  }
                  break;
               case CMD_XOR:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) ^ GetOperand32(&cmd->Op2);
                     SetOperand32(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ;
                  }
                  break;
               case CMD_XORB:
                  {
                     byte res = GetOperand8(&cmd->Op1) ^ GetOperand8(&cmd->Op2);
                     SetOperand8(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ_B;
                  }
                  break;
               case CMD_AND:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) & GetOperand32(&cmd->Op2);
                     SetOperand32(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ;
                  }
                  break;
               case CMD_ANDB:
                  {
                     byte res = GetOperand8(&cmd->Op1) & GetOperand8(&cmd->Op2);
                     SetOperand8(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ_B;
                  }
                  break;
               case CMD_OR:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) | GetOperand32(&cmd->Op2);
                     SetOperand32(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ;
                  }
                  break;
               case CMD_ORB:
                  {
                     byte res = GetOperand8(&cmd->Op1) | GetOperand8(&cmd->Op2);
                     SetOperand8(&cmd->Op1, res);
                     FLAGS_UPDATE_SZ_B;
                  }
                  break;
               case CMD_TEST:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) & GetOperand32(&cmd->Op2);
                     FLAGS_UPDATE_SZ;
                  }
                  break;
               case CMD_TESTB:
                  {
                     byte res = GetOperand8(&cmd->Op1) & GetOperand8(&cmd->Op2);
                     FLAGS_UPDATE_SZ_B;
                  }
                  break;
               case CMD_NOT:
                  SetOperand(cmd->ByteMode, &cmd->Op1, ~GetOperand(cmd->ByteMode, &cmd->Op1));
                  break;
               case CMD_NEG:
                  {
                     uint32_t res = 0 - GetOperand32(&cmd->Op1);
                     SetOperand32(&cmd->Op1, res);
                     Flags = res == 0 ? FLAG_Z : FLAG_C | (res & FLAG_S);
                  }
                  break;
               case CMD_NEGB:
                  {
                     byte res = (byte)(0 - GetOperand8(&cmd->Op1));
                     SetOperand8(&cmd->Op1, res);
                     Flags = res == 0 ? FLAG_Z : FLAG_C | GET_FLAG_S_B(res);
                  }
                  break;

               case CMD_SHL:
                  {
                     uint32_t v1 = GetOperand32(&cmd->Op1);
                     int32_t v2 = (int32_t)GetOperand32(&cmd->Op2);
                     uint32_t res = v1 << v2;
                     SetOperand32(&cmd->Op1, res);
                     Flags = (res == 0 ? FLAG_Z : (res & FLAG_S)) | ((v1 << (v2 - 1)) & 0x80000000 ? FLAG_C : 0);
                  }
                  break;
               case CMD_SHLB:
                  {
                     byte v1 = GetOperand8(&cmd->Op1);
                     int32_t v2 = (int32_t)GetOperand8(&cmd->Op2);
                     byte res = (byte)(v1 << v2);
                     SetOperand8(&cmd->Op1, res);
                     Flags = (res == 0 ? FLAG_Z : GET_FLAG_S_B(res)) | ((v1 << (v2 - 1)) & 0x80 ? FLAG_C : 0);
                  }
                  break;
               case CMD_SHR:
                  {
                     uint32_t v1 = GetOperand32(&cmd->Op1);
                     int32_t v2 = (int32_t)GetOperand32(&cmd->Op2);
                     uint32_t res = v1 >> v2;
                     SetOperand32(&cmd->Op1, res);
                     Flags = (res == 0 ? FLAG_Z : (res & FLAG_S)) | ((v1 >> (v2 - 1)) & FLAG_C);
                  }
                  break;
               case CMD_SHRB:
                  {
                     byte v1 = GetOperand8(&cmd->Op1);
                     int32_t v2 = (int32_t)GetOperand8(&cmd->Op2);
                     byte res = (byte)(v1 >> v2);
                     SetOperand8(&cmd->Op1, res);
                     Flags = (res == 0 ? FLAG_Z : GET_FLAG_S_B(res)) | ((v1 >> (v2 - 1)) & FLAG_C);
                  }
                  break;
               case CMD_SAR:
                  {
                     uint32_t v1 = GetOperand32(&cmd->Op1);
                     int32_t v2 = (int32_t)GetOperand32(&cmd->Op2);
                     uint32_t res = uint32_t(((int32_t)v1) >> v2);
                     SetOperand32(&cmd->Op1, res);
                     Flags= (res == 0 ? FLAG_Z : (res & FLAG_S)) | ((v1 >> (v2 - 1)) & FLAG_C);
                  }
                  break;
               case CMD_SARB:
                  {
                     byte v1 = GetOperand8(&cmd->Op1);
                     int32_t v2 = (int32_t)GetOperand8(&cmd->Op2);
                     byte res = (byte)(((signed char)v1) >> v2);
                     SetOperand8(&cmd->Op1, res);
                     Flags= (res == 0 ? FLAG_Z : GET_FLAG_S_B(res)) | ((v1 >> (v2 - 1)) & FLAG_C);
                  }
                  break;

               case CMD_JMP:
                  SET_IP_OP1;
                  continue;
               case CMD_JZ:
                  if ((Flags & FLAG_Z) != 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JNZ:
                  if ((Flags & FLAG_Z) == 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JS:
                  if ((Flags & FLAG_S) != 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JNS:
                  if ((Flags & FLAG_S) == 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JB:
                  if ((Flags & FLAG_C) != 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JBE:
                  if ((Flags & (FLAG_C | FLAG_Z)) != 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JA:
                  if ((Flags & (FLAG_C | FLAG_Z)) == 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;
               case CMD_JAE:
                  if ((Flags & FLAG_C) == 0)
                  {
                     SET_IP_OP1;
                     continue;
                  }
                  break;

               case CMD_PUSH:
                  R[kStackRegIndex] -= 4;
                  SetValue32(&Mem[R[kStackRegIndex] & kSpaceMask], GetOperand32(&cmd->Op1));
                  break;
               case CMD_POP:
                  SetOperand32(&cmd->Op1, GetValue32(&Mem[R[kStackRegIndex] & kSpaceMask]));
                  R[kStackRegIndex] += 4;
                  break;
               case CMD_CALL:
                  R[kStackRegIndex] -= 4;
                  SetValue32(&Mem[R[kStackRegIndex] & kSpaceMask], (uint32_t)(cmd - commands + 1));
                  SET_IP_OP1;
                  continue;

               case CMD_PUSHA:
                  {
                     for (uint32_t i = 0, SP = R[kStackRegIndex] - 4; i < kNumRegs; i++, SP -= 4)
                        SetValue32(&Mem[SP & kSpaceMask], R[i]);
                     R[kStackRegIndex] -= kNumRegs * 4;
                  }
                  break;
               case CMD_POPA:
                  {
                     for (uint32_t i = 0, SP = R[kStackRegIndex]; i < kNumRegs; i++, SP += 4)
                        R[kStackRegIndex - i] = GetValue32(&Mem[SP & kSpaceMask]);
                  }
                  break;
               case CMD_PUSHF:
                  R[kStackRegIndex] -= 4;
                  SetValue32(&Mem[R[kStackRegIndex]&kSpaceMask], Flags);
                  break;
               case CMD_POPF:
                  Flags = GetValue32(&Mem[R[kStackRegIndex] & kSpaceMask]);
                  R[kStackRegIndex] += 4;
                  break;

               case CMD_MOVZX:
                  SetOperand32(&cmd->Op1, GetOperand8(&cmd->Op2));
                  break;
               case CMD_MOVSX:
                  SetOperand32(&cmd->Op1, (uint32_t)(int32_t)(signed char)GetOperand8(&cmd->Op2));
                  break;
               case CMD_XCHG:
                  {
                     uint32_t v1 = GetOperand(cmd->ByteMode, &cmd->Op1);
                     SetOperand(cmd->ByteMode, &cmd->Op1, GetOperand(cmd->ByteMode, &cmd->Op2));
                     SetOperand(cmd->ByteMode, &cmd->Op2, v1);
                  }
                  break;
               case CMD_MUL:
                  {
                     uint32_t res = GetOperand32(&cmd->Op1) * GetOperand32(&cmd->Op2);
                     SetOperand32(&cmd->Op1, res);
                  }
                  break;
               case CMD_MULB:
                  {
                     byte res = GetOperand8(&cmd->Op1) * GetOperand8(&cmd->Op2);
                     SetOperand8(&cmd->Op1, res);
                  }
                  break;
               case CMD_DIV:
                  {
                     uint32_t divider = GetOperand(cmd->ByteMode, &cmd->Op2);
                     if (divider != 0)
                     {
                        uint32_t res = GetOperand(cmd->ByteMode, &cmd->Op1) / divider;
                        SetOperand(cmd->ByteMode, &cmd->Op1, res);
                     }
                  }
                  break;

#endif

               case CMD_RET:
                  {
                     if (R[kStackRegIndex] >= kSpaceSize)
                        return true;
                     uint32_t ip = GetValue32(&Mem[R[kStackRegIndex] & kSpaceMask]);
                     SET_IP(ip);
                     R[kStackRegIndex] += 4;
                     continue;
                  }
               case CMD_PRINT:
                  break;
               }
               cmd++;
               --maxOpCount;
            }
         }


         //////////////////////////////////////////////////////
         // Read program

         uint32_t ReadEncodedUInt32(mem_bit_decoder &inp)
         {
            switch(inp.ReadBits(2))
            {
            case 0:
               return inp.ReadBits(4);
            case 1:
               {
                  uint32_t v = inp.ReadBits(4);
                  if (v == 0)
                     return 0xFFFFFF00 | inp.ReadBits(8);
                  else
                     return (v << 4) | inp.ReadBits(4);
               }
            case 2:
               return inp.ReadBits(16);
            default:
               return inp.ReadBits(32);
            }
         }

         void vm::DecodeArg(mem_bit_decoder &inp, COperand &op, bool byteMode)
         {
            if (inp.ReadBit())
            {
               op.Type = OP_TYPE_REG;
               op.Data = inp.ReadBits(kNumRegBits);
            }
            else if (inp.ReadBit() == 0)
            {
               op.Type = OP_TYPE_INT;
               if (byteMode)
                  op.Data = inp.ReadBits(8);
               else
                  op.Data = ReadEncodedUInt32(inp);
            }
            else
            {
               op.Type = OP_TYPE_REGMEM;
               if (inp.ReadBit() == 0)
               {
                  op.Data = inp.ReadBits(kNumRegBits);
                  op.Base = 0;
               }
               else
               {
                  if (inp.ReadBit() == 0)
                     op.Data = inp.ReadBits(kNumRegBits);
                  else
                     op.Data = kNumRegs;
                  op.Base = ReadEncodedUInt32(inp);
               }
            }
         }

         void vm::ReadVmProgram(const byte *code, uint32_t codeSize, CProgram *prg)
         {
            mem_bit_decoder inp;
            inp.Init(code, codeSize);

            prg->StaticData.remove_all();
            if (inp.ReadBit())
            {
               uint32_t dataSize = ReadEncodedUInt32(inp) + 1;
               for (uint32_t i = 0; inp.Avail() && i < dataSize; i++)
                  prg->StaticData.add((byte)inp.ReadBits(8));
            }
            while (inp.Avail())
            {
               prg->Commands.add(CCommand());
               CCommand *cmd = &prg->Commands.last_element();
               if (inp.ReadBit() == 0)
                  cmd->OpCode = (ECommand)inp.ReadBits(3);
               else
                  cmd->OpCode = (ECommand)(8 + inp.ReadBits(5));
               if (kCmdFlags[cmd->OpCode] & CF_BYTEMODE)
                  cmd->ByteMode = (inp.ReadBit()) ? true : false;
               else
                  cmd->ByteMode = 0;
               int32_t opNum = (kCmdFlags[cmd->OpCode] & CF_OPMASK);
               if (opNum > 0)
               {
                  DecodeArg(inp, cmd->Op1, cmd->ByteMode);
                  if (opNum == 2)
                     DecodeArg(inp, cmd->Op2, cmd->ByteMode);
                  else
                  {
                     if (cmd->Op1.Type == OP_TYPE_INT && (kCmdFlags[cmd->OpCode] & (CF_JUMP | CF_PROC)))
                     {
                        int32_t Distance = cmd->Op1.Data;
                        if (Distance >= 256)
                           Distance -= 256;
                        else
                        {
                           if (Distance >= 136)
                              Distance -= 264;
                           else if (Distance >= 16)
                              Distance -= 8;
                           else if (Distance >= 8)
                              Distance -= 16;
                           Distance += (int32_t) (prg->Commands.get_size() - 1);
                        }
                        cmd->Op1.Data = Distance;
                     }
                  }
               }
               if (cmd->ByteMode)
               {
                  switch (cmd->OpCode)
                  {
                  case CMD_MOV: cmd->OpCode = CMD_MOVB; break;
                  case CMD_CMP: cmd->OpCode = CMD_CMPB; break;
                  case CMD_ADD: cmd->OpCode = CMD_ADDB; break;
                  case CMD_SUB: cmd->OpCode = CMD_SUBB; break;
                  case CMD_INC: cmd->OpCode = CMD_INCB; break;
                  case CMD_DEC: cmd->OpCode = CMD_DECB; break;
                  case CMD_XOR: cmd->OpCode = CMD_XORB; break;
                  case CMD_AND: cmd->OpCode = CMD_ANDB; break;
                  case CMD_OR: cmd->OpCode = CMD_ORB; break;
                  case CMD_TEST: cmd->OpCode = CMD_TESTB; break;
                  case CMD_NEG: cmd->OpCode = CMD_NEGB; break;
                  case CMD_SHL: cmd->OpCode = CMD_SHLB; break;
                  case CMD_SHR: cmd->OpCode = CMD_SHRB; break;
                  case CMD_SAR: cmd->OpCode = CMD_SARB; break;
                  case CMD_MUL: cmd->OpCode = CMD_MULB; break;
                  default: break;
                  }
               }
            }
         }

#ifdef RARVM_STANDARD_FILTERS

         enum EStandardFilter
         {
            SF_E8,
            SF_E8E9,
            SF_ITANIUM,
            SF_RGB,
            SF_AUDIO,
            SF_DELTA,
            SF_UPCASE
         };

         struct StandardFilterSignature
         {
            uint32_t Length;
            uint32_t CRC;
            EStandardFilter Type;
         }
         kStdFilters[]=
         {
            {  53, 0xad576887, SF_E8 },
            {  57, 0x3cd7e57e, SF_E8E9 },
            { 120, 0x3769893f, SF_ITANIUM },
            {  29, 0x0e06077d, SF_DELTA },
            { 149, 0x1c2c5dc8, SF_RGB },
            { 216, 0xbc85e701, SF_AUDIO },
            {  40, 0x46b9c560, SF_UPCASE }
         };

         static int32_t FindStandardFilter(const byte *code, uint32_t codeSize)
         {
            uint32_t crc = crc_calc(code, codeSize);
            for (int32_t i = 0; i < sizeof(kStdFilters) / sizeof(kStdFilters[0]); i++)
            {
               StandardFilterSignature &sfs = kStdFilters[i];
               if (sfs.CRC == crc && sfs.Length == codeSize)
                  return i;
            }
            return -1;
         }

#endif

         void vm::PrepareProgram(const byte *code, uint32_t codeSize, CProgram *prg)
         {
            byte xorSum = 0;
            for (uint32_t i = 1; i < codeSize; i++)
               xorSum ^= code[i];

            prg->Commands.remove_all();
#ifdef RARVM_STANDARD_FILTERS
            prg->StandardFilterIndex = -1;
#endif

            if (xorSum == code[0] && codeSize > 0)
            {
#ifdef RARVM_STANDARD_FILTERS
               prg->StandardFilterIndex = FindStandardFilter(code, codeSize);
               if (prg->StandardFilterIndex >= 0)
                  return;
#endif
               // 1 byte for checksum
               ReadVmProgram(code + 1, codeSize - 1, prg);
            }
            prg->Commands.add(CCommand());
            CCommand *cmd = &prg->Commands.last_element();
            cmd->OpCode = CMD_RET;
         }

         void vm::SetMemory(uint32_t pos, const byte *data, uint32_t dataSize)
         {
            if (pos < kSpaceSize && data != Mem + pos)
               memmove(Mem + pos, data, min(dataSize, kSpaceSize - pos));
         }

#ifdef RARVM_STANDARD_FILTERS

         static void E8E9Decode(byte *data, uint32_t dataSize, uint32_t fileOffset, bool e9)
         {
            if (dataSize <= 4)
               return;
            dataSize -= 4;
            const uint32_t kFileSize = 0x1000000;
            byte cmpByte2 = (e9 ? 0xE9 : 0xE8);
            for (uint32_t curPos = 0; curPos < dataSize;)
            {
               byte curByte = *(data++);
               curPos++;
               if (curByte == 0xE8 || curByte == cmpByte2)
               {
                  uint32_t offset = curPos + fileOffset;
                  uint32_t addr = (int32_t)GetValue32(data);
                  if (addr < kFileSize)
                     SetValue32(data, addr - offset);
                  else if ((int32_t)addr < 0 && (int32_t)(addr + offset) >= 0)
                     SetValue32(data, addr + kFileSize);
                  data += 4;
                  curPos += 4;
               }
            }
         }

         static inline uint32_t ItaniumGetOpType(const byte *data, int32_t bitPos)
         {
            return (data[(uint32_t)bitPos >> 3] >> (bitPos & 7)) & 0xF;
         }


         static void ItaniumDecode(byte *data, uint32_t dataSize, uint32_t fileOffset)
         {
            uint32_t curPos = 0;
            fileOffset >>= 4;
            while (curPos < dataSize - 21)
            {
               int32_t b = (data[0] & 0x1F) - 0x10;
               if (b >= 0)
               {
                  static byte kCmdMasks[16] = {4,4,6,6,0,0,7,7,4,4,0,0,4,4,0,0};
                  byte cmdMask = kCmdMasks[b];
                  if (cmdMask != 0)
                     for (int32_t i = 0; i < 3; i++)
                        if (cmdMask & (1 << i))
                        {
                           int32_t startPos = i * 41 + 18;
                           if (ItaniumGetOpType(data, startPos + 24) == 5)
                           {
                              const uint32_t kMask = 0xFFFFF;
                              byte *p = data + ((uint32_t)startPos >> 3);
                              uint32_t bitField =  ((uint32_t)p[0]) | ((uint32_t)p[1] <<  8) | ((uint32_t)p[2] << 16);
                              int32_t inBit = (startPos & 7);
                              uint32_t offset = (bitField >> inBit) & kMask;
                              uint32_t andMask = ~(kMask << inBit);
                              bitField = ((offset - fileOffset) & kMask) << inBit;
                              for (int32_t j = 0; j < 3; j++)
                              {
                                 p[j] &= andMask;
                                 p[j] |= bitField;
                                 andMask >>= 8;
                                 bitField >>= 8;
                              }
                           }
                        }
               }
               data += 16;
               curPos += 16;
               fileOffset++;
            }
         }

         static void DeltaDecode(byte *data, uint32_t dataSize, uint32_t numChannels)
         {
            uint32_t srcPos = 0;
            uint32_t border = dataSize * 2;
            for (uint32_t curChannel = 0; curChannel < numChannels; curChannel++)
            {
               byte prevByte = 0;
               for (uint32_t destPos = dataSize + curChannel; destPos < border; destPos += numChannels)
                  data[destPos] = (prevByte = prevByte - data[srcPos++]);
            }
         }

         static void RgbDecode(byte *srcData, uint32_t dataSize, uint32_t width, uint32_t posR)
         {
            byte *destData = srcData + dataSize;
            const uint32_t numChannels = 3;
            for (uint32_t curChannel = 0; curChannel < numChannels; curChannel++)
            {
               byte prevByte = 0;

               for (uint32_t i = curChannel; i < dataSize; i+= numChannels)
               {
                  uint32_t predicted;
                  if (i < width)
                     predicted = prevByte;
                  else
                  {
                     uint32_t upperLeftByte = destData[i - width];
                     uint32_t upperByte = destData[i - width + 3];
                     predicted = prevByte + upperByte - upperLeftByte;
                     int32_t pa = abs((int32_t)(predicted - prevByte));
                     int32_t pb = abs((int32_t)(predicted - upperByte));
                     int32_t pc = abs((int32_t)(predicted - upperLeftByte));
                     if (pa <= pb && pa <= pc)
                        predicted = prevByte;
                     else
                        if (pb <= pc)
                           predicted = upperByte;
                        else
                           predicted = upperLeftByte;
                  }
                  destData[i] = prevByte = (byte)(predicted - *(srcData++));
               }
            }
            if (dataSize < 3)
               return;
            for (uint32_t i = posR, border = dataSize - 2; i < border; i += 3)
            {
               byte g = destData[i + 1];
               destData[i] = destData[i] + g;
               destData[i + 2] = destData[i + 2] + g;
            }
         }

         static void AudioDecode(byte *srcData, uint32_t dataSize, uint32_t numChannels)
         {
            byte *destData = srcData + dataSize;
            for (uint32_t curChannel = 0; curChannel < numChannels; curChannel++)
            {
               uint32_t prevByte = 0, prevDelta = 0, dif[7];
               int32_t D1 = 0, D2 = 0, D3;
               int32_t K1 = 0, K2 = 0, K3 = 0;
               memset(dif, 0, sizeof(dif));

               for (uint32_t i = curChannel, byteCount = 0; i < dataSize; i += numChannels, byteCount++)
               {
                  D3 = D2;
                  D2 = prevDelta - D1;
                  D1 = prevDelta;

                  uint32_t predicted = 8 * prevByte + K1 * D1 + K2 * D2 + K3 * D3;
                  predicted = (predicted >> 3) & 0xFF;

                  uint32_t curByte = *(srcData++);

                  predicted -= curByte;
                  destData[i] = (byte)predicted;
                  prevDelta = (uint32_t)(int32_t)(signed char)(predicted - prevByte);
                  prevByte = predicted;

                  int32_t D = ((int32_t)(signed char)curByte) << 3;

                  dif[0] += abs(D);
                  dif[1] += abs(D - D1);
                  dif[2] += abs(D + D1);
                  dif[3] += abs(D - D2);
                  dif[4] += abs(D + D2);
                  dif[5] += abs(D - D3);
                  dif[6] += abs(D + D3);

                  if ((byteCount & 0x1F) == 0)
                  {
                     uint32_t minDif = dif[0], numMinDif = 0;
                     dif[0] = 0;
                     for (int32_t j = 1; j < sizeof(dif) / sizeof(dif[0]); j++)
                     {
                        if (dif[j] < minDif)
                        {
                           minDif = dif[j];
                           numMinDif = j;
                        }
                        dif[j] = 0;
                     }
                     switch (numMinDif)
                     {
                     case 1: if (K1 >= -16) K1--; break;
                     case 2: if (K1 <   16) K1++; break;
                     case 3: if (K2 >= -16) K2--; break;
                     case 4: if (K2 <   16) K2++; break;
                     case 5: if (K3 >= -16) K3--; break;
                     case 6: if (K3 <   16) K3++; break;
                     }
                  }
               }
            }
         }

         static uint32_t UpCaseDecode(byte *data, uint32_t dataSize)
         {
            uint32_t srcPos = 0, destPos = dataSize;
            while (srcPos < dataSize)
            {
               byte curByte = data[srcPos++];
               if (curByte == 2 && (curByte = data[srcPos++]) != 2)
                  curByte -= 32;
               data[destPos++] = curByte;
            }
            return destPos - dataSize;
         }

         void vm::ExecuteStandardFilter(int32_t filterIndex)
         {
            uint32_t dataSize = R[4];
            if (dataSize >= kGlobalOffset)
               return;
            EStandardFilter filterType = kStdFilters[filterIndex].Type;

            switch (filterType)
            {
            case SF_E8:
            case SF_E8E9:
               E8E9Decode(Mem, dataSize, R[6], (filterType == SF_E8E9));
               break;
            case SF_ITANIUM:
               ItaniumDecode(Mem, dataSize, R[6]);
               break;
            case SF_DELTA:
               if (dataSize >= kGlobalOffset / 2)
                  break;
               SetBlockPos(dataSize);
               DeltaDecode(Mem, dataSize, R[0]);
               break;
            case SF_RGB:
               if (dataSize >= kGlobalOffset / 2)
                  break;
               {
                  uint32_t width = R[0];
                  if (width <= 3)
                     break;
                  SetBlockPos(dataSize);
                  RgbDecode(Mem, dataSize, width, R[1]);
               }
               break;
            case SF_AUDIO:
               if (dataSize >= kGlobalOffset / 2)
                  break;
               SetBlockPos(dataSize);
               AudioDecode(Mem, dataSize, R[0]);
               break;
            case SF_UPCASE:
               if (dataSize >= kGlobalOffset / 2)
                  break;
               uint32_t destSize = UpCaseDecode(Mem, dataSize);
               SetBlockSize(destSize);
               SetBlockPos(dataSize);
               break;
            }
         }

#endif

         uint32_t GetValue32(const void *addr)
         {
            return GetUi32(addr);
         }

         void SetValue32(void *addr, uint32_t value)
         {
            SetUi32(addr, value);
         }

      } // namespace vm

   } // namespace rar3

} // namespace libcompress
