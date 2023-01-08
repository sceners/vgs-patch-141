//-----------------------------------------------------
#include"crc32.h"
//-----------------------------------------------------
unsigned long CRC32TAB[256];
//-----------------------------------------------------
void __stdcall InitCRC32(void)
{
unsigned int i,j;
unsigned long crc;
    for (i=0;i!=256;i++) {
	crc=i;	
        for (j=0;j!=8;j++)
            crc = (crc&1) ? (crc>>1)^CRC32poly : (crc>>1);
        CRC32TAB[i]=crc;
    }
}
//-----------------------------------------------------
unsigned long __stdcall CRC32(unsigned long InitCRC,void *buf,unsigned int lenbuf)
{
unsigned int i;
unsigned long ul,crc;
crc=InitCRC;
for (i=0; i!=lenbuf; i++) {
    ul=crc>>8;
    crc = CRC32TAB[(crc^((unsigned char *)buf)[i])&0xFF]^ul;
}
return crc;
}
//-----------------------------------------------------