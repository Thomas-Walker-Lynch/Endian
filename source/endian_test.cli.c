
#define IFACE__
  #include "stdint.h"
  #include "stdbool.h"
  #include "stdio.h"
  #include "endian.lib.c"
  #include "endian.lib.c"
#undef IFACE__

bool test_0(){
  uint16_t uint16_order = Endian.uint16_byte_order();
  uint32_t uint32_order = Endian.uint32_byte_order();
  uint64_t uint64_order = Endian.uint64_byte_order();

  #if 1
  printf("%.4x\n" ,uint16_order);
  printf("%.8x\n" ,uint32_order);
  printf("%.16lx\n" ,uint64_order);
  #endif

  // little-endian return:
  // read indexes from left to right (European scribes did not reverse numbers)
  bool passedq =
    uint16_order == 0x0100
    && uint32_order == 0x03020100
    && uint64_order == 0x0706050403020100
    ;

  /* big-endian return:
  // read indexes from left to right (European scribes did not reverse numbers)
  bool passedq =
    uint16_order == 0x0001
    && uint32_order == 0x00010203
    && uint64_order == 0x0001020304050607
    ;
  */

  if( !passedq ){ printf("test_0 failed\n"); }
  return passedq;
}

uint8_t packet_0[] = {
0x45 ,0x00 ,0x00 ,0x32 ,0x97 ,0x9c ,0x00 ,0x00 ,0xff ,0x11 ,0x39 ,0x21 ,0x0a ,0x00 ,0x00 ,0x01 ,0xe0 ,0x00 ,0x00 ,0xfc ,0x14 ,0xeb ,0x14 ,0xeb ,0x00 ,0x1e ,0xd4 ,0x6b ,0x3b ,0x98 ,0x00 ,0x00 ,0x00 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x04 ,0x67 ,0x64 ,0x70 ,0x72 ,0x00 ,0x00 ,0x01 ,0x00 ,0x01
};

bool test_1(){
  int8_t *length_pt = packet_0 + 2;
  int8_t *check_pt = packet_0 + 0xa;
  int8_t *src_pt = packet_0 + 0xc;

  int16_t length = Endian.uint16_from_big_endian(length_pt);
  int16_t check = Endian.uint16_from_big_endian(check_pt);
  int32_t src = Endian.uint32_from_big_endian(src_pt);

  bool passedq =
    length == 0x0032
    && check == 0x3921
    && src == 0x0a000001
    ;

  if( !passedq ){ printf("test_1 failed\n"); }
  return passedq;
}

bool test_2(){
  return true;
  //return Endian_LIB(bits_in_byte) == 8;
}

bool (*(tests[]))() = {test_0 ,test_1 ,test_2 ,0};
//bool (*(tests[]))() = {test_0 ,0};

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


