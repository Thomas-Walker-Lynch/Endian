/*
Note: https://backreference.org/2010/03/26/tuntap-interface-tutorial/
*/

#if !defined(TUN__)
#define TUN__

  #if !defined(IFACE__)
    // external ifaces needed only for function definitions (not the calls)
    #define _IFACE
      #include <sys/types.h>
      #include <string.h>
      #include <sys/stat.h>
      #include <fcntl.h>
      #include <unistd.h>
      #include <sys/ioctl.h>
      #include <linux/if.h>
      #include <linux/if_tun.h>
    #undef _IFACE
  #endif


  /*
  dev must point to a string buffer that either
    a) is a non-zero length string taken as the dev name
    b) the string buffer is long enough to hold a name returned by the kernel

  flags tell is either IFF_TUN to indicate a TUN device or IFF_TAP. | IFF_NO_PI tells the kernel not to add the 4 extra
  bytes, as it otherwise will do.

  */
  int tun_alloc(char *dev, int flags)
  #if !defined(_IFACE)
  {
      struct ifreq ifr;
      int fd, err;
      char *clonedev = "/dev/net/tun";

      /* Arguments taken by the function:
       *
       * char *dev: the name of an interface (or '\0'). MUST have enough
       *   space to hold the interface name if '\0' is passed
       * int flags: interface flags (eg, IFF_TUN etc.)
       */

       /* open the clone device */
       if( (fd = open(clonedev, O_RDWR)) < 0 ) {
         return fd;
       }

       /* preparation of the struct ifr, of type "struct ifreq" */
       memset(&ifr, 0, sizeof(ifr));

       ifr.ifr_flags = flags;   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */

       if (*dev) {
         /* if a device name was specified, put it in the structure; otherwise,
          * the kernel will try to allocate the "next" device of the
          * specified type */
         strncpy(ifr.ifr_name, dev, IFNAMSIZ);
       }

       /* try to create the device */
       if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
         close(fd);
         return err;
       }

      /* if the operation was successful, write back the name of the
       * interface to the variable "dev", so the caller can know
       * it. Note that the caller MUST reserve space in *dev (see calling
       * code below) */
      strcpy(dev, ifr.ifr_name);

      /* this is the special file descriptor that the caller will use to talk
       * with the virtual interface */
      return fd;
  }
  #endif
  ;

#endif
