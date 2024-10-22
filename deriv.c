#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// only works for functions of x at this time
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

int parseBase(char *startFunction) { 
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char)*len);
  int ret = 0;

  for(int i = 0; i < len; i++) {
    result[i] = '\0';
    if(startFunction[i] != 'x') { 
      strncat(result, &startFunction[i], 1);
    } else { 
      ret = atoi(result);
      free(result);
      return ret; 
    } 
  }
  return 0;
}
int parsePower(char *startFunction) {
  
  int i = strlen(startFunction);
  int flag = 0;
  char *result = (char *)malloc(sizeof(char)*i);
  int ret = 0; 

  while((i > 0) & (flag == 0)) { 
    if((startFunction[i] != 'x') & (startFunction[i] != '^')) {
      strncat(result, &startFunction[i], 1);    
    } else { 
      flag = 1;
    }
    i--;
  }

  if(strlen(result) <= 1) { 
    ret = atoi(result);
    free(result);
    return ret;
  } else { 
    result = strrev(result);
    ret = atoi(result);
    free(result);
  }
  
  return ret;
}

char *powerRule(char *startFunction) {

  int base, power;
  char *result = (char *)malloc(sizeof(char));
  
  printf("power: %d\n", parsePower(startFunction)); 
  
  printf("base: %d\n", parseBase(startFunction)); 
  return NULL; 

}

int main() {

  char *testFunction = "2x";
  char *testFunction3 = "2x^200";
  char *testFunction2 = "5x^2";
  
  char *testFunction5 = "7012x^2013";
  char *testFunction4 = "909090900x^2";
  powerRule(testFunction);
  powerRule(testFunction3); 
  powerRule(testFunction2);
  powerRule(testFunction4);
  powerRule(testFunction5);
}
