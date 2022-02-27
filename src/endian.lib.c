/*
  library routines for dealing with word endianess

  See the struct at the bottom for the Endian library programmer's interface. This interface is stateless.

  To change the namespace for this librarey, do a global string replace 'Endian' with a different string, then recompile.

*/
#ifndef Endian__
#define Endian__ 

  #include <stdint.h>

  #if !defined(IFACE__)

    #define IFACE__
    #include <stdio.h>
    #include <stdbool.h>
    #undef IFACE__

    const uint8_t bits_in_byte = 0x08;

    const uint8_t uint16_bytes = 0x02;
    const uint8_t uint32_bytes = 0x04;
    const uint8_t uint64_bytes = 0x08;

    const uint16_t uint16_one = 1;
    const uint32_t uint32_one = 1;
    const uint64_t uint64_one = 1;

    const uint16_t uint16_byte_mask = (uint16_one << bits_in_byte) - uint16_one;
    const uint32_t uint32_byte_mask = (uint32_one << bits_in_byte) - uint32_one;
    const uint64_t uint64_byte_mask = (uint64_one << bits_in_byte) - uint64_one;

    /* --------------------------------------------------------------------------------
    byte_order

    pt0 is a byte array that holds one word.
    m is the largest byte index.
    Sets each byte to have a value equal to its index in the word.
    For example,  0x03020100 will be returned for when m = 3
    */
      void count_bytes(uint32_t m ,uint8_t *pt0)
      {
        uint8_t *pt = pt0;
        uint32_t i;
        i=0; do{
          *pt = i;
          if( i == m ) break;
          i++;
          pt++;
        }while(true);
      }

      uint16_t uint16_byte_order()
      {
        uint8_t pt0[2];
        count_bytes(1 ,pt0);
        return *(uint16_t *)pt0;
      }

      uint32_t uint32_byte_order()
      {
        uint8_t pt0[4];
        count_bytes(3 ,pt0);
        return *(uint32_t *)pt0;
      }

      uint64_t uint64_byte_order()
      {
        uint8_t pt0[8];
        count_bytes(7 ,pt0);
        return *(uint64_t *)pt0;
      }

    /* --------------------------------------------------------------------------------
    from little endian
    bytes is a pointer to a little endian word.
    The return value is in the correct order for the native machine.
    */
      uint16_t uint16_from_little_endian(uint8_t *bytes_0)
      {
        uint16_t order = uint16_byte_order();
        if( order == 0x0100 ) return *(uint16_t *)bytes_0;

        uint8_t bytes_1[uint16_bytes];
        uint8_t i0 ,i1;
        i0 = 0;
        do{
          i1 = order & uint16_byte_mask;
          bytes_1[i1] = bytes_0[i0];
          if( i0 == uint16_bytes-1 ) break;
          order >>= bits_in_byte;
          i0++;
        } while(true);

        return *(uint16_t *)bytes_1;
      }

      uint32_t uint32_from_little_endian(uint8_t *bytes_0)
      {
        uint32_t order = uint32_byte_order();
        if( order == 0x03020100 ) return *(uint32_t *)bytes_0;

        uint8_t bytes_1[uint32_bytes];
        uint8_t i0 ,i1;
        i0 = 0;
        do{
          i1 = order & uint32_byte_mask;
          bytes_1[i1] = bytes_0[i0];
          if( i0 == uint32_bytes-1 ) break;
          order >>= bits_in_byte;
          i0++;
        } while(true);

        return *(uint32_t *)bytes_1;
      }

      uint64_t uint64_from_little_endian(uint8_t *bytes_0)
      {
        uint64_t order = uint64_byte_order();
        if( order == 0x0706050403020100 ) return *(uint64_t *)bytes_0;

        uint8_t bytes_1[uint64_bytes];
        uint8_t i0 ,i1;
        i0 = 0;
        do{
          i1 = order & uint64_byte_mask;
          bytes_1[i1] = bytes_0[i0];
          if( i0 == uint64_bytes-1 ) break;
          order >>= bits_in_byte;
          i0++;
        } while(true);

        return *(uint64_t *)bytes_1;
      }

    /* --------------------------------------------------------------------------------
    from big endian
    bytes is a pointer to a big endian word.
    The return value is in the correct order for the native machine.
    */
      uint16_t uint16_from_big_endian(uint8_t *bytes_0)
      {
        uint16_t order = uint16_byte_order();
        if( order == 0x0001020304050607) return *(uint64_t *)bytes_0;

        uint8_t bytes_1[uint16_bytes];
        uint8_t i0 ,i1;
        i0 = uint16_bytes-1;
        do{
          i1 = order & uint16_byte_mask;
          bytes_1[i1] = bytes_0[i0];
          if( i0 == 0 ) break;
          order >>= bits_in_byte;
          i0--;
        } while(true);

        return *(uint16_t *)bytes_1;
      }

      uint32_t uint32_from_big_endian(uint8_t *bytes_0)
      {
        uint32_t order = uint32_byte_order();
        if( order == 0x00010203) return *(uint32_t *)bytes_0;

        uint8_t bytes_1[uint32_bytes];
        uint8_t i0 ,i1;
        i0 = uint32_bytes-1;
        do{
          i1 = order & uint32_byte_mask;
          bytes_1[i1] = bytes_0[i0];
          if( i0 == 0 ) break;
          order >>= bits_in_byte;
          i0--;
        } while(true);

        return *(uint32_t *)bytes_1;
      }

      uint64_t uint64_from_big_endian(uint8_t *bytes_0)
      {
        uint64_t order = uint64_byte_order();
        if( order == 0x0001) return *(uint16_t *)bytes_0;

        uint8_t bytes_1[uint64_bytes];
        uint8_t i0 ,i1;
        i0 = uint64_bytes-1;
        do{
          i1 = order & uint64_byte_mask;
          bytes_1[i1] = bytes_0[i0];
          if( i0 == 0 ) break;
          order >>= bits_in_byte;
          i0--;
        } while(true);

        return *(uint64_t *)bytes_1;
      }
  #endif

  // define the interface
  //
    typedef struct {
      uint8_t bits_in_byte;

      uint8_t uint16_bytes;
      uint8_t uint32_bytes;
      uint8_t uint64_bytes;

      uint16_t uint16_byte_mask;
      uint32_t uint32_byte_mask;
      uint64_t uint64_byte_mask;

      uint16_t (*uint16_byte_order)();
      uint32_t (*uint32_byte_order)();
      uint64_t (*uint64_byte_order)();

      uint16_t (*uint16_from_little_endian)(uint8_t *bytes_0);
      uint32_t (*uint32_from_little_endian)(uint8_t *bytes_0);
      uint64_t (*uint64_from_little_endian)(uint8_t *bytes_0);

      uint16_t (*uint16_from_big_endian)(uint8_t *bytes_0);
      uint32_t (*uint32_from_big_endian)(uint8_t *bytes_0);
      uint64_t (*uint64_from_big_endian)(uint8_t *bytes_0);

    } Endian_t;

  // export the interface
  //
    #if defined(IFACE__)
      extern const Endian_t Endian;
    #else
      const Endian_t Endian = {
        .bits_in_byte = bits_in_byte

        ,.uint16_bytes = uint16_bytes
        ,.uint32_bytes = uint32_bytes
        ,.uint64_bytes = uint64_bytes

        ,.uint16_byte_mask = uint16_byte_mask
        ,.uint32_byte_mask = uint32_byte_mask
        ,.uint64_byte_mask = uint64_byte_mask

        ,.uint16_byte_order = uint16_byte_order
        ,.uint32_byte_order = uint32_byte_order
        ,.uint64_byte_order = uint64_byte_order

        ,.uint16_from_little_endian = uint16_from_little_endian
        ,.uint32_from_little_endian = uint32_from_little_endian
        ,.uint64_from_little_endian = uint64_from_little_endian

        ,.uint16_from_big_endian = uint16_from_big_endian
        ,.uint32_from_big_endian = uint32_from_big_endian
        ,.uint64_from_big_endian = uint64_from_big_endian
      };
    #endif


#endif
