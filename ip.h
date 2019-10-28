typedef struct {
	char* address;
	char mask;
	unsigned int realMask;
} IP;

IP* createIP(const char a, const char b, const char c, const char d, const unsigned int mask);
void releaseIP(IP* ipPtr);
void printIP(const IP* ipPtr, const char showMask);
void printAsIP(unsigned int ip, char* originalIP);
void calculateSubRed(unsigned int sub, const IP* ipPtr);
void showInRange(const unsigned int low, const unsigned int high, IP* ipPtr);
void showRoutingTable(IP* ipPtr, unsigned int* subs, int size);