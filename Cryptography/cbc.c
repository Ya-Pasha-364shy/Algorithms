#include <stdio.h>
#include <time.h>

#include "cryptoHelper.h"

// Chipher Block Chaining

int main()
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

	// CBC encryption process.
	// Temporarily store the result of ciphertext XOR plaintext.
	byte tempStore[BLOCK_SIZE] = { 0 };
	for (size_t i = 0; i < blockCount; i++)
	{
		if (i == 0)
		{
			// XOR the first block with the IV.
			xor_byte_arrays(IV, byteBlocks[0], tempStore);
		}
		else
		{
			// XOR encryption result of previous block with current block plaintext.
			xor_byte_arrays(byteBlocks[i - 1], byteBlocks[i], tempStore);
		}
		// Encrypt the XOR result and store in the encrypted blocks.
		encdec(tempStore, keyBytes, byteBlocks[i]);
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

	// CBC decryption process.
	// Temporarily store the result of decrypted ciphertext, and its XOR with previous ciphertext.
	byte plainStore[BLOCK_SIZE] = { 0 };
  // Temporarily store the result of encrypted ciphertext.
  byte encPrevBlock[BLOCK_SIZE] = { 0 };
	for (size_t i = 0; i < blockCount; i++)
	{
		// Decrypt the encrypted block.
		encdec(byteBlocks[i], keyBytes, tempStore);

		if (i == 0)
		{
			// XOR the first decryption result with the IV.
			xor_byte_arrays(IV, tempStore, plainStore);
		}
		else
		{
			// XOR decryption result of current ciphertext block with the previous ciphertext block.
			xor_byte_arrays(encPrevBlock, tempStore, plainStore);
		}

		// Store the ciphertext for the next iteration.
		bytecpy(encPrevBlock, byteBlocks[i]);
		// Replace ciphertext with plaintext.
		bytecpy(byteBlocks[i], plainStore);
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