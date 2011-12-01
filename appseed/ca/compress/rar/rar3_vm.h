// Rar3Vm.h
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives
// from 7-zip on 2012-12-23, dawn
#pragma once

/*#include "../../../C/CpuArch.h"

#include "Common/MyVector.h"
#include "Common/Types.h"*/

#define RARVM_STANDARD_FILTERS

namespace compress
{
   namespace rar3 
   {

      class mem_bit_decoder
      {
         const byte *_data;
         uint32 _bitSize;
         uint32 _bitPos;
      public:
         void Init(const byte *data, uint32 byteSize)
         {
            _data = data;
            _bitSize = (byteSize << 3);
            _bitPos = 0;
         }
         uint32 ReadBits(int numBits);
         uint32 ReadBit();
         bool Avail() const { return (_bitPos < _bitSize); }
      };

      namespace vm
      {

         uint32 GetValue32(const void *addr);
         void SetValue32(void *addr, uint32 value);

         uint32 ReadEncodedUInt32(mem_bit_decoder &inp);

         const int kNumRegBits = 3;
         const uint32 kNumRegs = 1 << kNumRegBits;
         const uint32 kNumGpRegs = kNumRegs - 1;

         const uint32 kSpaceSize = 0x40000;
         const uint32 kSpaceMask = kSpaceSize -1;
         const uint32 kGlobalOffset = 0x3C000;
         const uint32 kGlobalSize = 0x2000;
         const uint32 kFixedGlobalSize = 64;

         namespace NGlobalOffset
         {
            const uint32 kBlockSize = 0x1C;
            const uint32 kBlockPos  = 0x20;
            const uint32 kExecCount = 0x2C;
            const uint32 kGlobalMemOutSize = 0x30;
         }

         enum ECommand
         {
            CMD_MOV,  CMD_CMP,  CMD_ADD,  CMD_SUB,  CMD_JZ,   CMD_JNZ,  CMD_INC,  CMD_DEC,
            CMD_JMP,  CMD_XOR,  CMD_AND,  CMD_OR,   CMD_TEST, CMD_JS,   CMD_JNS,  CMD_JB,
            CMD_JBE,  CMD_JA,   CMD_JAE,  CMD_PUSH, CMD_POP,  CMD_CALL, CMD_RET,  CMD_NOT,
            CMD_SHL,  CMD_SHR,  CMD_SAR,  CMD_NEG,  CMD_PUSHA,CMD_POPA, CMD_PUSHF,CMD_POPF,
            CMD_MOVZX,CMD_MOVSX,CMD_XCHG, CMD_MUL,  CMD_DIV,  CMD_ADC,  CMD_SBB,  CMD_PRINT,

            CMD_MOVB, CMD_CMPB, CMD_ADDB, CMD_SUBB, CMD_INCB, CMD_DECB,
            CMD_XORB, CMD_ANDB, CMD_ORB,  CMD_TESTB,CMD_NEGB,
            CMD_SHLB, CMD_SHRB, CMD_SARB, CMD_MULB
         };

         enum EOpType {OP_TYPE_REG, OP_TYPE_INT, OP_TYPE_REGMEM, OP_TYPE_NONE};

         // Addr in COperand object can link (point) to vm object!!!

         struct COperand
         {
            EOpType Type;
            uint32 Data;
            uint32 Base;
            COperand(): Type(OP_TYPE_NONE), Data(0), Base(0) {}
         };

         struct CCommand
         {
            ECommand OpCode;
            bool ByteMode;
            COperand Op1, Op2;
         };

         struct CBlockRef
         {
            uint32 Offset;
            uint32 Size;
         };

         struct CProgram
         {
            base_array<CCommand> Commands;
#ifdef RARVM_STANDARD_FILTERS
            int StandardFilterIndex;
#endif
            byte_array StaticData;
         };

         struct CProgramInitState
         {
            uint32 InitR[kNumGpRegs];
            byte_array GlobalData;

            void AllocateEmptyFixedGlobal()
            {
               GlobalData.set_size(0, kFixedGlobalSize);
               for (uint32 i = 0; i < kFixedGlobalSize; i++)
                  GlobalData.add(0);
            }
         };

         class vm
         {
            static uint32 GetValue(bool byteMode, const void *addr)
            {
               if (byteMode)
                  return(*(const byte *)addr);
               else
                  return GetUi32(addr);
            }

            static void SetValue(bool byteMode, void *addr, uint32 value)
            {
               if (byteMode)
                  *(byte *)addr = (byte)value;
               else
                  SetUi32(addr, value);
            }

            uint32 GetFixedGlobalValue32(uint32 globalOffset) { return GetValue(false, &Mem[kGlobalOffset + globalOffset]); }

            void SetBlockSize(uint32 v) { SetValue(&Mem[kGlobalOffset + NGlobalOffset::kBlockSize], v); }
            void SetBlockPos(uint32 v) { SetValue(&Mem[kGlobalOffset + NGlobalOffset::kBlockPos], v); }
         public:
            static void SetValue(void *addr, uint32 value) { SetValue(false, addr, value); }
         private:
            uint32 GetOperand32(const COperand *op) const;
            void SetOperand32(const COperand *op, uint32 val);
            byte GetOperand8(const COperand *op) const;
            void SetOperand8(const COperand *op, byte val);
            uint32 GetOperand(bool byteMode, const COperand *op) const;
            void SetOperand(bool byteMode, const COperand *op, uint32 val);

            void DecodeArg(mem_bit_decoder &inp, COperand &op, bool byteMode);

            bool ExecuteCode(const CProgram *prg);

#ifdef RARVM_STANDARD_FILTERS
            void ExecuteStandardFilter(int filterIndex);
#endif

            byte *Mem;
            uint32 R[kNumRegs + 1]; // R[kNumRegs] = 0 always (speed optimization)
            uint32 Flags;
            void ReadVmProgram(const byte *code, uint32 codeSize, CProgram *prg);
         public:
            vm();
            ~vm();
            bool Create();
            void PrepareProgram(const byte *code, uint32 codeSize, CProgram *prg);
            void SetMemory(uint32 pos, const byte *data, uint32 dataSize);
            bool Execute(CProgram *prg, const CProgramInitState *initState,
               CBlockRef &outBlockRef, byte_array &outGlobalData);
            const byte *GetDataPointer(uint32 offset) const { return Mem + offset; }

         };


      } // namespace vm

   } // namespace rar3

} // namespace compress
