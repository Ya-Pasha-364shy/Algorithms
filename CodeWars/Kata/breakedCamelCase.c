#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "testlib.h"

/*
 * Description:
 * Complete the solution so that the function
 * will break up camel casing, using a space between words.
*/

// need to allocate some memory in heap before returning...
char * solution(const char * camelCase) {
  if (camelCase[0] == '\0')
    return (char *)calloc(1, sizeof(char));

  size_t bytes_for_spaces = 0; 
  size_t camelCaseStrLen = strlen(camelCase);
  size_t breakedCamelCaseLen = camelCaseStrLen;
  
  for (size_t i = 1; i < camelCaseStrLen; i++) {
    if (isupper(camelCase[i])) bytes_for_spaces++;
  }

  breakedCamelCaseLen += bytes_for_spaces;
  
  size_t breakedCounter = 0;
  char * breakedCamelCase = (char *)calloc(breakedCamelCaseLen, sizeof(char));
  if (!bytes_for_spaces) {
    strncpy(breakedCamelCase, camelCase, camelCaseStrLen);
    return breakedCamelCase;
  }
  
  for (size_t i = 0; i < camelCaseStrLen; i++) {
    if (isupper(camelCase[i])) {
      breakedCamelCase[breakedCounter++] = ' ';
      breakedCamelCase[breakedCounter++] = camelCase[i];
    } else breakedCamelCase[breakedCounter++] = camelCase[i];
  }
  breakedCamelCase[breakedCounter] = '\0';
  return breakedCamelCase;
}

int main() {
	char * rs1 = solution("camelCase");
	IS_STR_EQUALS(rs1, "camel Case", strlen(rs1));
	free(rs1);

	char * rs2 = solution("thisIsAVeryLongIdentifierName");
	IS_STR_EQUALS(rs2, "this Is A Very Long Identifier Name", strlen(rs2));
	free(rs2);

	char * rs3 = solution("unshift");
	IS_STR_EQUALS(rs3, "unshift", strlen(rs1));
	free(rs3);

	char * rs4 = solution("dcdgdcaHhagFgeghahgGfbgBaegGbecdecgeCbacfgCgadafe");
	IS_STR_EQUALS(rs4, "dcdgdca Hhag Fgeghahg Gfbg Baeg Gbecdecge Cbacfg Cgadafe", strlen(rs4));
	free(rs4);

	return EXIT_SUCCESS;
}
