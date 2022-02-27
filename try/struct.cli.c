    #include <stdint.h>
    #include <stdio.h>

typedef struct {
  uint8_t bits_in_byte;
    
  uint8_t uint16_bytes;
  uint8_t uint32_bytes;
  uint8_t uint64_bytes;
    
  uint16_t uint16_one;
  uint32_t uint32_one;
  uint64_t uint64_one;
    
  uint16_t uint16_byte_mask;
  uint32_t uint32_byte_mask;
  uint64_t uint64_byte_mask;
} ENDIAN__constants_t;

const static ENDIAN__constants_t ENDIAN__constants = {
  .bits_in_byte = 0x08
    
  ,.uint16_bytes = 0x02
  ,.uint32_bytes = 0x04
  ,.uint64_bytes = 0x08
  
  ,.uint16_one = 1
  ,.uint32_one = 1
  ,.uint64_one = 1
  
  // ah too bad, can't use the dot notation on the right hand side
  ,.uint16_byte_mask = (.uint16_one << .bits_in_byte) - .uint16_one
  ,.uint32_byte_mask = (.uint32_one << .bits_in_byte) - .uint32_one
  ,.uint64_byte_mask = (.uint64_one << .bits_in_byte) - .uint64_one
};

int main(){
}

/*
2022-02-08T14:22:10Z
> gcc -o struct struct.c
struct.c:32:25: error: expected expression before ‘.’ token
   32 |   ,.uint16_byte_mask = (.uint16_one << .bits_in_byte) - .uint16_one
      |                         ^
struct.c:32:57: error: expected expression before ‘.’ token
   32 |   ,.uint16_byte_mask = (.uint16_one << .bits_in_byte) - .uint16_one
      |                                                         ^
*/
