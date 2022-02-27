/*
some helper functions to be used with IP packets

Simplify debugging rather than making the fastest code possible.
*/
#ifndef IP4__
#define IP4__

  #include<stdint.h>

  typedef struct{
    uint8_t version;
    uint8_t length_packed_header;
    uint8_t TOS;
    uint16_t length_packet;
    uint16_t identification;
    uint8_t flags;
    uint16_t fragment_offset;
    uint8_t TTL;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t source;
    uint32_t destination;
  } IP4__unpacked_header_t;

  // perhaps unpacked_header_expanded_1 uses 32 bit fields only, and unpacked_header is unpacked in a single operation

  #if !defined(_IFACE)

    #define IFACE__
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <endian.lib.c>
    #undef IFACE__

    uint8_t version(uint8_t *unpacked_header){ 
      return (*unpacked_header & 0xf0) >> 4;
    }

    uint8_t length_packed_header(uint8_t *unpacked_header){ 
      return *unpacked_header & 0x0f;
    }

    uint8_t TOS(uint8_t *unpacked_header){ 
      return *((uint8_t *)unpacked_header + 1);
    }

    uint16_t length_packet(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 2;
      return Endian.uint16_from_big_endian(pt);
    }

    uint16_t identification(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 4;
      return Endian.uint16_from_big_endian(pt);
    }

    uint8_t flags(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 6;
      return (*pt >> 4);
    }

    uint16_t fragment_offset(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 6;
      return  0x0FFF & Endian.uint16_from_big_endian(pt);
    }

    uint8_t TTL(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 8;
      return *pt;
    }

    uint8_t protocol(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 9;
      return *pt;
    }

    uint16_t checksum(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 0xa;
      return Endian.uint16_from_big_endian(pt);
    }

    uint32_t source(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 0xc;
      return Endian.uint32_from_big_endian(pt);
    }

    uint32_t destination(uint8_t *unpacked_header){ 
      uint8_t *pt = unpacked_header + 0x10;
      return Endian.uint32_from_big_endian(pt);
    }

    IP4__unpacked_header_t unpacked_header_make(){
      IP4__unpacked_header_t unpacked_header;
      memset(&unpacked_header ,0 ,sizeof(IP4__unpacked_header_t));
      return unpacked_header;
    }

    IP4__unpacked_header_t unpacked_header_parse(uint8_t *unpacked_header_bytes){
      IP4__unpacked_header_t unpacked_header = unpacked_header_make();
      unpacked_header.version = version(unpacked_header_bytes);
      unpacked_header.length_packed_header = length_packed_header(unpacked_header_bytes);
      unpacked_header.TOS = TOS(unpacked_header_bytes);
      unpacked_header.length_packet = length_packet(unpacked_header_bytes);
      unpacked_header.identification = identification(unpacked_header_bytes);
      unpacked_header.flags = flags(unpacked_header_bytes);
      unpacked_header.fragment_offset = fragment_offset(unpacked_header_bytes);
      unpacked_header.TTL = TTL(unpacked_header_bytes);
      unpacked_header.protocol = protocol(unpacked_header_bytes);
      unpacked_header.checksum = checksum(unpacked_header_bytes);
      unpacked_header.source = source(unpacked_header_bytes);
      unpacked_header.destination = destination(unpacked_header_bytes);
      return unpacked_header;
    }

    bool unpacked_header_eq( IP4__unpacked_header_t *unpacked_header_0, IP4__unpacked_header_t *unpacked_header_1){
      return memcmp( unpacked_header_0 ,unpacked_header_1 ,sizeof(IP4__unpacked_header_t)) == 0;
    }

    void print_addr( uint32_t ipaddr){
      printf( "%u"   ,(ipaddr & 0xFF000000) >> 0x18);
      printf( ".%u" ,(ipaddr & 0x00FF0000) >> 0x10);
      printf( ".%u" ,(ipaddr & 0x0000FF00) >> 0x08);
      printf( ".%u" ,ipaddr & 0x000000FF);
    }

    void unpacked_header_print(IP4__unpacked_header_t *unpacked_header){
      printf("version: %x\n" ,unpacked_header->version);
      printf("length_packed_header: %x\n" ,unpacked_header->length_packed_header);
      printf("identification: %x\n", unpacked_header->identification);
      printf("flags %x\n", unpacked_header->flags);
      printf("fragment_offset %x\n" ,unpacked_header->fragment_offset);
      printf("TTL %x\n" ,unpacked_header->TTL);
      printf("protocol: %x\n" ,unpacked_header->protocol);
      printf("checksum: %x\n" ,unpacked_header->checksum);

      printf("source: ");
      print_addr( unpacked_header->source);
      printf("\n");

      printf("destination: ");
      print_addr( unpacked_header->destination);
      printf("\n");
    }

  #endif

  typedef struct{
    uint8_t (*version)(uint8_t *unpacked_header);
    uint8_t (*length_packed_header)(uint8_t *unpacked_header); 
    uint8_t (*TOS)(uint8_t *unpacked_header); 
    uint16_t (*length_packet)(uint8_t *unpacked_header); 
    uint16_t (*identification)(uint8_t *unpacked_header); 
    uint8_t (*flags)(uint8_t *unpacked_header); 
    uint16_t (*fragment_offset)(uint8_t *unpacked_header); 
    uint8_t (*TTL)(uint8_t *unpacked_header); 
    uint8_t (*protocol)(uint8_t *unpacked_header); 
    uint16_t (*checksum)(uint8_t *unpacked_header); 
    uint32_t (*source)(uint8_t *unpacked_header); 
    uint32_t (*destination)(uint8_t *unpacked_header); 
    IP4__unpacked_header_t (*unpacked_header_make)();
    bool (* unpacked_header_eq)( IP4__unpacked_header_t *unpacked_header, IP4__unpacked_header_t *unpacked_header_1);
    IP4__unpacked_header_t (*unpacked_header_parse)(uint8_t *unpacked_header);
    void (*unpacked_header_print)(IP4__unpacked_header_t *unpacked_header);
  } IP4_t;

 
  #if defined(IFACE__)
    extern const IP4_t IP4
  #else
    const IP4_t IP4 = {
      .version = version
      ,.length_packed_header = length_packed_header
      ,.TOS = TOS
      ,.length_packet = length_packet
      ,.identification = identification
      ,.flags = flags
      ,.fragment_offset = fragment_offset
      ,.TTL = TTL
      ,.protocol = protocol
      ,.checksum = checksum
      ,.source = source
      ,.destination = destination
      ,.unpacked_header_make = unpacked_header_make
      ,.unpacked_header_eq = unpacked_header_eq
      ,.unpacked_header_parse = unpacked_header_parse
      ,.unpacked_header_print = unpacked_header_print
    };
  #endif

#endif
