/*
for now, specifically for listening to tun_rt


*/




while(1) {

if(FD_ISSET(tun_fd, &rd_set)) { // if data is there on the tunnel file descriptor

/* data from tun/tap: just read it and write it to the network */

dread = read(tun_fd, buffer, BUFSIZE); //read data from the tun device via the fd

// start writng the data to the network file descriptor (this is the UDP connection to the server)

// if needed here encryption can be applied

dwrite = write(net_fd, buffer, nread);

}

if(FD_ISSET(net_fd, &rd_set)) { //reverse flow. That is if data is coming on the network interface

/* data from the network: read it, and write it to the tun interface.

* We need to read the length first, and then the packet */

/* Read length */

dread = read_n(net_fd, (char *)&plength, sizeof(plength));

if(dread == 0) {

/* ctrl-c at the other end */

break;

}

/* read packet */

dread = read_n(net_fd, buffer, ntohs(plength)); //read the packet over the network interface. Here we can apply decryption

/* now buffer[] contains a full packet or frame, write it into the tun interface */

dwrite = write(tun_fd, buffer, nread);

}

}
