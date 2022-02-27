//https://serverfault.com/questions/361503/getting-interface-mtu-under-linux-with-pcap

int getMTU(char *name) {
FILE *f;
char buf[128];
char *line = NULL;
ssize_t count;
size_t len = 0;
int mtu;

snprintf(buf, sizeof(buf), "/sys/class/net/%s/mtu", name);
f = fopen(buf, "r");
if(!f) {
    perror("Error opening:");
    exit(EXIT_FAILURE);
}
count = getline(&line, &len, f);

if (count == -1) {
    perror("Error opening:");
    exit(EXIT_FAILURE);
}
sscanf(line, "%d\n", &mtu);
fclose(f);

return mtu;
}
