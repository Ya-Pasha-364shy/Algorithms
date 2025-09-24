/** Description:
 *
 * Вам дается строка, например:
 * "example(unwanted thing)example"
 * Ваша задача — удалить все, что находится внутри скобок,
 * а также сами скобки.
 * 
 * Приведенный выше пример вернет:
 * "exampleexample" 
 * 
 * Примечания
 * Кроме круглых скобок в строке могут встречаться только буквы и пробелы.
 * Не беспокойтесь о других квадратных скобках, таких как «[]» и «{}», поскольку они никогда не появятся.
 * Может быть несколько скобок.
 * Скобки могут быть вложенными.
 * {"example(unwanted thing)example", "exampleexample"},
 * {"example(unwanted thing)example", "exampleexample"},
 * {"example (unwanted thing) example", "example  example"},
 * {"a (bc d)e", "a e"},
 * {"a(b(c))", "a"},
 * {"hello example (words(more words) here) something", "hello example  something"},
 * {"(first group) (second group) (third group)", "  "},
 * {"no parentheses", "no parentheses"},
 * {"empty () parentheses", "empty  parentheses"}};
*/

#include <stdio.h>
#include <string.h>

#define OPEN_PARENTHESES  '('
#define CLOSE_PARENTHESES ')'

void remove_parentheses(const char *str_in, char *str_out)
{
  size_t str_out_iterator = 0;
  char * l = strchr(str_in, OPEN_PARENTHESES);
  char * r = strrchr(str_in, CLOSE_PARENTHESES);
  if (!l || !r) {
    str_out = str_in;
    return;
  }

  while (1) {
    if (!strchr(str_in, OPEN_PARENTHESES) || !strchr(str_in, CLOSE_PARENTHESES))
      break;

    size_t l = strchr(str_in, OPEN_PARENTHESES) - str_in;
    size_t r = strchr(str_in, CLOSE_PARENTHESES) - str_in + 1;

    for (int i = 0; i < strlen(str_in); i++) {
      if (i == l) {
        for (; i < r; i++);
      }
      str_out[str_out_iterator++] = str_in[i];
    }
    str_in += r;
  }

  return;
}

int main(void) { 
  char* input1 = "example(unwanted thing)example";
  char output1[strlen(input1)];
  remove_parentheses(input1, output1);
  printf("result1 = %s\n", output1);

  char* input2 = "hello example (words(more words) here) something";
  char output2[strlen(input2)];
  remove_parentheses(input2, output2);
  printf("result2 = %s\n", output2);

  char* input4 = "(first group) (second group) (third group)";
  char output4[strlen(input4)];
  remove_parentheses(input4, output4);
  printf("result4 = %s\n", output4);

  return 0;
}
