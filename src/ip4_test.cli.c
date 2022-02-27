
#define IFACE__
  #include "stdint.h"
  #include "stdbool.h"
  #include "stdio.h"
  #include "ip4.lib.c"
#undef IFACE__

uint8_t packet_0[] = {
  0x45 ,0x00 ,0x00 ,0x32  //0
  ,0x97 ,0x9c ,0x00 ,0x00 //4
  ,0xff ,0x11 ,0x39 ,0x21 //8
  ,0x0a ,0x00 ,0x00 ,0x01 //c
  ,0xe0 ,0x00 ,0x00 ,0xfc //10
  ,0x14 ,0xeb ,0x14 ,0xeb //14
  ,0x00 ,0x1e ,0xd4 ,0x6b //18
  ,0x3b ,0x98 ,0x00 ,0x00 //1c
  ,0x00 ,0x01 ,0x00 ,0x00 //20
  ,0x00 ,0x00 ,0x00 ,0x00 //24
  ,0x04 ,0x67 ,0x64 ,0x70 //28
  ,0x72 ,0x00 ,0x00 ,0x01 //2c
  ,0x00 ,0x01             //30
};

bool test_0(){
  //IP4.print_0(packet_0);
    
  IP4__unpacked_header_t unpacked_header_0 = IP4.unpacked_header_parse(packet_0);

  IP4__unpacked_header_t unpacked_header_1 = IP4.unpacked_header_make();
  unpacked_header_1.version = 4;
  unpacked_header_1.length_packed_header = 5;
  unpacked_header_1.TOS = 0;
  unpacked_header_1.length_packet = 0x32;
  unpacked_header_1.identification = 0x979c;
  unpacked_header_1.flags = 0;
  unpacked_header_1.fragment_offset = 0;
  unpacked_header_1.TTL = 0xff;
  unpacked_header_1.protocol = 0x11;
  unpacked_header_1.checksum = 0x3921;
  unpacked_header_1.source = 0x0a000001;
  unpacked_header_1.destination = 0xe00000fc;

  bool passed = IP4.unpacked_header_eq(&unpacked_header_0 ,&unpacked_header_1);
  if( !passed ){
    fprintf(stderr ,"test_0 failed\n");
  }
  return passed;
}

bool test_2(){
  return true;
  //return Endian_LIB(bits_in_byte) == 8;
}

bool (*(tests[]))() = {test_0 ,0};

int main(int arc ,char**argv){

  uint16_t passed_cnt=0 ,failed_cnt=0;
  
  bool (**fpt)() = tests;
  do{
    if( (**fpt)() )
      passed_cnt++;
    else
      failed_cnt++;
    fpt++;
  }while(*fpt);

  printf("\nfailed:%d\npassed:%d\n" ,failed_cnt ,passed_cnt);
}


