#ifndef CODE_H
#define CODE_H

#include <stdint.h>
#include <stdbool.h>

#define ACK_TOKEN_LEN 4
#define COAP_HEADER 5
#define MAX_MESSAGE_SIZE 1024
#define MAX_PAYLOAD_SIZE (MAX_MESSAGE_SIZE - COAP_HEADER - ACK_TOKEN_LEN)

typedef enum {
  COMPRESSED_PAYLOAD = 0,
  HAS_MORE_MESSAGES,
  RESERVED2,
  RESERVED3,
  RESERVED4,
  RESERVED5,
  RESERVED6,
  RESERVED7
} CodeFlag;

/**
 * Return the code constructed by the flags
 */
uint8_t ConstructCode(bool compressedPayload, bool hasMore);

/**
 * Returns true if the flag is present is the code
 */
bool IsFlagInCode(uint8_t code, CodeFlag codeFlag);

int CompressPayload(const uint8_t* src, int srcSize, uint8_t* dst, int dstCapacity);
int DecompressPayload(const uint8_t* src, int srcSize, uint8_t* dst);

#endif /* CODE_H */