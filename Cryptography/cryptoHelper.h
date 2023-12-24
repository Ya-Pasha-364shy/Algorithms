#ifndef CRYPTO_HELPER_H
#define CRYPTO_HELPER_H

#include <stdlib.h>
#include <string.h>

/** CIPHER BY BLOCKS WITH SOME CHAIN **/

#define BLOCK_SIZE 20
#define byte unsigned char

byte * gen_rand_bytestream(size_t byteCount)
{
	byte * bytestream = malloc(byteCount);
	for (size_t i = 0; i < byteCount; i++)
		bytestream[i] = rand();
	return bytestream;
}

void get_byte_array(const char * sourceText, byte * byteArray)
{
	size_t sourceLen = strlen(sourceText);
	for (size_t i = 0; i < sourceLen; i++)
		byteArray[i] = sourceText[i];
}

void xor_byte_arrays(const byte * in1, const byte * in2, byte * out)
{
	for (size_t i = 0; i < BLOCK_SIZE; i++)
		out[i] = in1[i] ^ in2[i];
}

void bytecpy(byte * dest, const byte * src)
{
	for (size_t i = 0; i < BLOCK_SIZE; i++)
		dest[i] = src[i];
}

void encdec(const byte * in1, const byte * in2, byte * out)
{
	for (size_t i = 0; i < BLOCK_SIZE; i++)
		out[i] = in1[i] ^ in2[i];
}

#endif // CRYPTO_HELPER_H