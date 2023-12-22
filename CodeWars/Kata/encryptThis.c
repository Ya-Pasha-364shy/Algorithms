#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "testlib.h"

/**
 * Description:
 * 
 * Encrypt this!
 *
 * You want to create secret messages which can be deciphered by the Decipher this! kata. Here are the conditions:
 * Your message is a string containing space separated words.
 * You need to encrypt each word in the message using the following rules:
 * The first letter must be converted to its ASCII code.
 * The second letter must be switched with the last letter
 * Keepin' it simple: There are no special characters in the input.
*/

// https://www.codewars.com/kata/5848565e273af816fb000449/train/c

#define SPACE_SEPARATOR " "
#define SPACE_CHARACTER ' '

void encrypt(char * enc_str, size_t * enc_counter, size_t enc_size, char * string)
{
	size_t strlen_ = strlen(string), i;
	unsigned int first_character_tmp_ = *string;
	(*enc_counter) += snprintf(enc_str + (*enc_counter), enc_size, "%u", first_character_tmp_);
	enc_str[(*enc_counter)++] = string[strlen_ - 1];

	for (i = 2; i <= strlen_ - 2; i++)
	{
		enc_str[(*enc_counter)++] = string[i];
	}
	enc_str[(*enc_counter)++] = string[1];
}

char * encrypt_this(const char * str)
{
	// if string is empty or pointer is invalid
	if (!str || (str && !str[0]))
		return "";

	char * tmp_ = NULL, * enc_str = NULL;
	const char * read_string = NULL;
	size_t strlen_ = strlen(str), word_count_ = 1, enc_counter = 0, enc_size = 0;

	read_string = str;
	for (; *read_string != '\0'; read_string++)
	{
		// for allocate memory for string, that will returned
		if (*read_string == SPACE_CHARACTER)
			++word_count_;
	}
	enc_size = strlen_ + (2 * word_count_);
	enc_str = (char *)calloc(enc_size, sizeof(char));

	char maybe_modified_string[strlen_]; strncpy(maybe_modified_string, str, strlen_+1);
	tmp_ = strtok(maybe_modified_string, SPACE_SEPARATOR);
	// encryption algorithm
	do
	{
		encrypt(enc_str, &enc_counter, enc_size, tmp_);
		tmp_ = strtok(NULL, SPACE_SEPARATOR);
		if (tmp_)
		{
			enc_str[enc_counter++] = SPACE_CHARACTER;
		}
	} while (tmp_ != NULL);

	return enc_str;
}

int main(int argc, char * argv[])
{
	char * rs0 = encrypt_this("Hello"); char * rs0_expected = "72olle";
	char * rs1 = encrypt_this("good");  char * rs1_expected = "103doo";
	char * rs2 = encrypt_this("hello world"); char * rs2_expected = "104olle 119drlo";

	IS_STR_EQUALS(rs0, rs0_expected, strlen(rs0));
	IS_STR_EQUALS(rs1, rs1_expected, strlen(rs1));
	IS_STR_EQUALS(rs2, rs2_expected, strlen(rs2));

	free(rs0); free(rs1); free(rs2);

	return EXIT_SUCCESS;
}