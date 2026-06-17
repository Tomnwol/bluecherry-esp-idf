#include "code.h"
#include "lz4/lz4.h"

uint8_t ConstructCode(bool compressedPayload, bool hasMore)
{
  return ((uint8_t) compressedPayload << COMPRESSED_PAYLOAD) |
         ((uint8_t) hasMore << HAS_MORE_MESSAGES);
}

bool IsFlagInCode(uint8_t code, CodeFlag codeFlag)
{
  return (code & (1U << codeFlag)) != 0;
}

static LZ4_stream_t lz4_compress_state;

int CompressPayload(const uint8_t* src, int srcSize, uint8_t* dst, int dstCapacity)
{
  // LZ4_compress_default() allocates ~16 KiB LZ4_stream_t on the stack; use static state instead.
  return LZ4_compress_fast_extState(&lz4_compress_state, (const char*) src, (char*) dst, srcSize,
                                    dstCapacity, 1);
}

int DecompressPayload(const uint8_t* src, int srcSize, uint8_t* dst)
{
  // returns the amount of decompressed bytes, negative if error
  return LZ4_decompress_safe((const char*) src, (char*) dst, srcSize, MAX_PAYLOAD_SIZE);
}