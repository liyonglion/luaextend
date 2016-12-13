//md5.h
#ifndef MD5_H
#define MD5_H
/**
 * \file
 * This file defines functions and structures to compute MD5 digests
 */
char* GetMd5String(const char*str,int length);
char*GetMd5StringByFile(const char*filename);
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
struct md5_s
{
    uint32_t A, B, C, D;          /* chaining variables */
    uint32_t nblocks;
    uint8_t buf[64];
    int count;
};

void InitMD5( struct md5_s * );
void AddMD5( struct md5_s *, const void *, size_t );
void EndMD5( struct md5_s * );
char * psz_md5_hash( struct md5_s *md5_s );
#endif
