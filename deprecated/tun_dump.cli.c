/*
 */

#define _IFACE
  #include <sys/types.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <errno.h>
  #include <string.h>
  #include <linux/if.h>
  #include <linux/if_tun.h>
  #include "tun_alloc.lib.c"
#undef _IFACE

size_t group_i = 4;

int main(int argc ,char *argv[]){
  /* Connect to the device */
  char tun_name[IFNAMSIZ];
  tun_name[0] = '\0';
  int tun_fd;
  tun_fd = tun_alloc(tun_name, IFF_TUN | IFF_NO_PI);  /* tun interface */
  if(tun_fd < 0){
    perror("cloning interface\n");
    exit(1);
  }else{
    printf("%s of %s\n" ,argv[0] ,tun_name);
  }
  /* Now read data coming from the kernel */
  // note get_mtu.lib.c, but for now
  size_t MTU = 1600;
  unsigned char buffer[MTU];
  ssize_t nread;
  size_t i;
  while(1) {
    nread = read(tun_fd,buffer,MTU);
    if(nread < 0) {
      perror("tun read error\n");
      close(tun_fd);
      exit(1);
    }
    printf("%04x: " ,nread);
    printf("%02x" ,buffer[0]);
    i = 1;
    while( i < nread ){
      putchar(' ');
      if( i % group_i == 0 ) putchar(' ');
      printf("%02x", buffer[i]);
      i++;
    }
    putchar('\n');
  }
}


