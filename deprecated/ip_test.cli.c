
#define _IFACE
  #include "ip.lib.c"
  #include "stdint.h"
  #include "stdbool.h"
  #include "stdio.h"
#undef _IFACE

uint16_t packet_0[] = {0x4500 ,0x003c ,0x1c46 ,0x4000 ,0x4006 ,0xb1e6 ,0xac10 ,0x0a63 ,0xac10 ,0x0a0c};
  //  return ip_4_computed_checksum( packet_0 ) == 0x4E19;

bool test_0(){
  uint16_t bow2 = byte_order_w2();
  uint32_t bow4 = byte_order_w4();
  uint64_t bow8 = byte_order_w8();

  #if 0
  printf("%.4x\n" ,bow2);
  printf("%.8x\n" ,bow4);
  printf("%.16lx\n" ,bow8);
  #endif

  // little-endian return:
  return
    bow2 == 0x0100
    && bow4 == 0x03020100
    && bow8 == 0x0706050403020100
    ;
}


int main(int arc ,char**argv){
  
  if( test_0() )
    printf("passed\n");
  else
    printf("failed\n");
      
}


