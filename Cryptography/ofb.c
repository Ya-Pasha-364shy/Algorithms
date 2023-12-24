#include <stdio.h>
#include <time.h>

#include "cryptoHelper.h"

// Chipher 

int main(int argc, char * argv[])
{
	srand(time(NULL));
	const char key[] = "This is a super secret, very very secret key!";
	const size_t keyLen = strlen(key);

	if (keyLen < BLOCK_SIZE)
	{
		fprintf(stderr, "length of key is smaller than block size !\n");
		return EXIT_FAILURE;
	}
	byte keyBytes[keyLen];
	get_byte_array(key, keyBytes);

	// Init vector (IV).
	const byte * IV = gen_rand_bytestream(BLOCK_SIZE);

	const char plaintext[] = "Try to imagine a life without timekeeping. You probably can't. You know the month, the year, the day of the week. There is a clock on your wall or the dashboard of your car. You have a schedule, a calendar, a time for dinner or a movie. Yet all around you, timekeeping is ignored. Birds are not late. A dog does not check its watch. Deer do not fret over passing birthdays. Man alone measures time. Man alone chimes the hour. And, because of this, man alone suffers a paralyzing fear that no other creature endures";
	const size_t sourceLen = strlen(plaintext);
	// performing plain text into bytes.
	byte plaintextBytes[sourceLen];
	get_byte_array(plaintext, plaintextBytes);

	// Split plaintext into blocks, prepare blocks to store texts in.
	const size_t blockCount = sourceLen / BLOCK_SIZE + 1;
	byte byteBlocks[blockCount][BLOCK_SIZE];

	size_t bytePos = 0;
	for (size_t i = 0; i < blockCount; i++)
	{
		for (size_t j = 0; j < BLOCK_SIZE && bytePos < sourceLen; j++)
		{
			byteBlocks[i][j] = plaintextBytes[bytePos++];
		}
	}

	printf("Original plaintext: %s\n\n", plaintext);
	printf("Plaintext blocks (concatenated): ");
	for (size_t i = 0; i < blockCount; i++)
	{
		for (size_t j = 0; j < BLOCK_SIZE; j++)
		{
			printf("%c", byteBlocks[i][j]);
		}
	}
	printf("\n\n");

	// OFB encryption process.
  byte tempStore[BLOCK_SIZE] = { 0 };
  byte result[BLOCK_SIZE] = { 0 };
  for (size_t i = 0; i < blockCount; i++)
  {
    if (i == 0)
    {
      encdec(IV, key, tempStore);
    }
    else
    {
      encdec(tempStore, key, tempStore);
    }
    xor_byte_arrays(tempStore, byteBlocks[i], result);
    bytecpy(byteBlocks[i], result);
  }

	printf("Encrypted block output (hex):\n");
	for (size_t i = 0; i < blockCount; i++)
	{
		for (size_t j = 0; j < BLOCK_SIZE; j++)
		{
			printf("%02x", byteBlocks[i][j]);
		}
		if ((i + 1) % 3 == 0)
			printf("\n");
		else
			printf(" ");
	}
	printf("\n\n");

	// OFB decryption process.
  for (size_t i = 0; i < blockCount; i++)
  {
    if (i == 0)
    {
      encdec(IV, key, tempStore);
    }
    else
    {
      encdec(tempStore, key, tempStore);
    }
    xor_byte_arrays(tempStore, byteBlocks[i], byteBlocks[i]);
  }

	printf("Decrypted blocks (concatenated):\n");
	for (size_t i = 0; i < blockCount; i++)
	{
		for (size_t j = 0; j < BLOCK_SIZE; j++)
		{
			printf("%c", byteBlocks[i][j]);
		}
	}
	printf("\n\n");

	return EXIT_SUCCESS;
}