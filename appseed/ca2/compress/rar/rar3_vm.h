// Rar3Vm.h
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives
// from 7-zip on 2012-12-23, dawn
#pragma once

/*#include "../../../C/CpuArch.h"

#include "Common/MyVector.h"
#include "Common/Types.h"*/

#define RARVM_STANDARD_FILTERS

namespace libcompress
{
   namespace rar3
   {

      class mem_bit_decoder
      {
         const byte *_data;
         uint32_t _bitSize;
         uint32_t _bitPos;
      public:
         void Init(const byte *data, uint32_t byteSize)
         {
            _data = data;
            _bitSize = (byteSize << 3);
            _bitPos = 0;
         }
         uint32_t ReadBits(int32_t numBits);
         uint32_t ReadBit();
         bool Avail() const { return (_bitPos < _bitSize); }
      };

      namespace vm
      {

         uint32_t GetValue32(const void *addr);
         void SetValue32(void *addr, uint32_t value);

         uint32_t ReadEncodedUInt32(mem_bit_decoder &inp);

         const int32_t kNumRegBits = 3;
         const uint32_t kNumRegs = 1 << kNumRegBits;
         const uint32_t kNumGpRegs = kNumRegs - 1;

         const uint32_t kSpaceSize = 0x40000;
         const uint32_t kSpaceMask = kSpaceSize -1;
         const uint32_t kGlobalOffset = 0x3C000;
         const uint32_t kGlobalSize = 0x2000;
         const uint32_t kFixedGlobalSize = 64;

         namespace NGlobalOffset
         {
            const uint32_t kBlockSize = 0x1C;
            const uint32_t kBlockPos  = 0x20;
            const uint32_t kExecCount = 0x2C;
            const uint32_t kGlobalMemOutSize = 0x30;
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
            uint32_t Data;
            uint32_t Base;
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
            uint32_t offset;
            uint32_t Size;
         };

         struct CProgram
         {
            array<CCommand> Commands;
#ifdef RARVM_STANDARD_FILTERS
            int32_t StandardFilterIndex;
#endif
            byte_array StaticData;
         };

         struct CProgramInitState
         {
            uint32_t InitR[kNumGpRegs];
            byte_array GlobalData;

            void AllocateEmptyFixedGlobal()
            {
               GlobalData.set_size(0, kFixedGlobalSize);
               for (uint32_t i = 0; i < kFixedGlobalSize; i++)
                  GlobalData.add(0);
            }
         };

         class vm
         {
            static uint32_t GetValue(bool byteMode, const void *addr)
            {
               if (byteMode)
                  return(*(const byte *)addr);
               else
                  return GetUi32(addr);
            }

            static void SetValue(bool byteMode, void *addr, uint32_t value)
            {
               if (byteMode)
                  *(byte *)addr = (byte)value;
               else
                  SetUi32(addr, value);
            }

            uint32_t GetFixedGlobalValue32(uint32_t globalOffset) { return GetValue(false, &Mem[kGlobalOffset + globalOffset]); }

            void SetBlockSize(uint32_t v) { SetValue(&Mem[kGlobalOffset + NGlobalOffset::kBlockSize], v); }
            void SetBlockPos(uint32_t v) { SetValue(&Mem[kGlobalOffset + NGlobalOffset::kBlockPos], v); }
         public:
            static void SetValue(void *addr, uint32_t value) { SetValue(false, addr, value); }
         private:
            uint32_t GetOperand32(const COperand *op) const;
            void SetOperand32(const COperand *op, uint32_t val);
            byte GetOperand8(const COperand *op) const;
            void SetOperand8(const COperand *op, byte val);
            uint32_t GetOperand(bool byteMode, const COperand *op) const;
            void SetOperand(bool byteMode, const COperand *op, uint32_t val);

            void DecodeArg(mem_bit_decoder &inp, COperand &op, bool byteMode);

            bool ExecuteCode(const CProgram *prg);

#ifdef RARVM_STANDARD_FILTERS
            void ExecuteStandardFilter(int32_t filterIndex);
#endif

            byte *Mem;
            uint32_t R[kNumRegs + 1]; // R[kNumRegs] = 0 always (speed optimization)
            uint32_t Flags;
            void ReadVmProgram(const byte *code, uint32_t codeSize, CProgram *prg);
         public:
            vm();
            ~vm();
            bool Create();
            void PrepareProgram(const byte *code, uint32_t codeSize, CProgram *prg);
            void SetMemory(uint32_t pos, const byte *data, uint32_t dataSize);
            bool Execute(CProgram *prg, const CProgramInitState *initState,
               CBlockRef &outBlockRef, byte_array &outGlobalData);
            const byte *GetDataPointer(uint32_t offset) const { return Mem + offset; }

         };


      } // namespace vm

   } // namespace rar3

} // namespace libcompress
