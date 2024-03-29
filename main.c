#include <stdio.h>
#include <stdlib.h>
#include "ip.h"

void printBinary(unsigned int number){
	char temp;
	for(char i = 31; i >= 0; i--){
		temp = number >> i;
		if(temp & 1) printf("1");
		else printf("0");
		if( i % 8 == 0 ) printf(" ");
	}
	printf("\n");
}


int main(){

	IP* ipPtr = createIP(192, 0, 0, 0, 25);
	unsigned int subs[] = {
		14, 810, 910, 1150, 2015, 3020, 4050, 5175
	};
	printIP(ipPtr, 1);

	int size = sizeof(subs) / sizeof(unsigned int);

	puts("");
	//calculateSubRed(810, ipPtr);
	showRoutingTable(ipPtr, subs, size);

	releaseIP(ipPtr);
	return 0;
}

void printAsIP(unsigned int ip, unsigned char* originalIP){
	//printBinary(ipPtr->realMask);
	void* ipp = &ip;
	printf("%d.%d.%d.%d",
		*((unsigned char*)(ipp + 3)) + originalIP[0],
		*((unsigned char*)(ipp + 2)) + originalIP[1],
		*((unsigned char*)(ipp + 1)) + originalIP[2],
		*((unsigned char*)(ipp + 0)) + originalIP[3]
	);
}

void calculateSubRed(unsigned int sub, const IP* ipPtr){
	char zeros = 32 - ipPtr->mask;
	unsigned int brodcast = -1, tmp = -1;
	brodcast <<= zeros;
	brodcast ^= tmp;

	//subred
	printf("%d \t| ", sub);
	sub <<= zeros;
	// ip
	printAsIP(sub, ipPtr->address);
	printf("\t| ");
	//range first
	printAsIP(sub + 1, ipPtr->address);
	printf("\t- ");
	//range last
	printAsIP(brodcast + sub - 1, ipPtr->address);
	printf("\t| ");
	//brodcast
	printAsIP(brodcast + sub, ipPtr->address);
	printf("\n");
}

void showRoutingTable(IP* ipPtr, unsigned int* subs, int size){
	printf("Subred\t\tIP\t\t\tRango\t\t\tBrodcast\n");
	for(int i = 0; i < size; i++){
		calculateSubRed(subs[i], ipPtr);
	}
}

void showInRange(const unsigned int low, const unsigned int high, IP* ipPtr){

	printf("Subred\tIP\n");
	for(unsigned int i = low; i <= high; i++){
		calculateSubRed(i, ipPtr);
	}
}

void printIP(const IP* ipPtr, const char showMask){
	printf("%d.%d.%d.%d/%d\n",
	ipPtr->address[0],
	ipPtr->address[1],
	ipPtr->address[2],
	ipPtr->address[3],
	ipPtr->mask);
	char zeros[] = {0,0,0,0};
	if(showMask){ printAsIP(ipPtr->realMask, zeros); printf("\n");}
}

void releaseIP(IP* ipPtr){
	free(ipPtr->address);
	free(ipPtr);
	ipPtr = NULL;
}

IP* createIP(const unsigned char a, const unsigned char b, const unsigned char c, const unsigned char d, const unsigned int mask){

	IP* newIp = malloc(sizeof(IP));

	newIp->address = calloc(4, sizeof(unsigned char));
	newIp->address[0] = a;
	newIp->address[1] = b;
	newIp->address[2] = c;
	newIp->address[3] = d;
	newIp->mask = mask;

	newIp->realMask = -1;
	newIp->realMask <<= (32 - newIp->mask);

	return newIp;
}
