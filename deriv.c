// derivative calculator by Strydr Silverberg
// done sophomore year at Colorado School of Mines
// https://github.com/StrydrS/deriv
// not yet licensed (is shit)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *parseFunction(char *startFunction) { 
  printf("%s", startFunction);
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);
 
  for(int i = 0; i < len - 1; i++) {
    if(startFunction[i] == '(') { 
        strcat(result, &startFunction[i]);
      }
    }
  
  result++;
  len = strlen(result);

  result[len - 1] = '\0';
  return result;

}
//returns 1 if function starts with a - 
int isNegative(char *startFunction) { 
  int flag = 0;
  if(startFunction[0] == '-') { 
    flag = 1; 
    return flag;
  } return flag;
}

// reverses strings
char *strrev(char *str) {
  char *p1, *p2;

  if (!str || !*str)
    return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return str;
}

// parses startFunction for the base
int parseBase(char *startFunction) {
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);
  int ret = 0;

  for (int i = 0; i < len; i++) {
    result[i] = '\0';
    if (startFunction[i] != 'x') {
      strncat(result, &startFunction[i], 1);
    } else {
      ret = atoi(result);
      free(result);
      return ret;
    }
  }
  return ret;
}

// parses startFunction for the power
int parsePower(char *startFunction) {

  int i = strlen(startFunction);
  int flag = 0;
  char *result = (char *)malloc(sizeof(char) * i);
  int ret = 0;

  while ((i > 0) & (flag == 0)) {
    if ((startFunction[i] != 'x') & (startFunction[i] != '^')) {
      strncat(result, &startFunction[i], 1);
    } else {
      flag = 1;
    }
    i--;
  }

  int isFraction = 0;
  int len = strlen(result);
  
  for(int z = 0; z < len; z++) { 
    if(result[z] == '/') { 
      isFraction = 1;
      break;
    }
  }

  if((len <= 1) & (isFraction == 0)) {
    ret = atoi(result);
    free(result);
    return ret;
  }

  result = strrev(result);

  if(isFraction == 1) {
    char *tempDividend = (char *)malloc(sizeof(char) * len);
    char *tempDivisor = (char *)malloc(sizeof(char) * len);
    int divisor, dividend; 
    int divFlag = 1;

    for(int q = 0; q < len + 1; q++) { 
      if((result[q] != '/') & (divFlag == 1)) { 
        strncat(tempDivisor, &result[q], 1);
      } else if(result[q] == '/') {
        divFlag = 0;
        printf("divisor: %d\n", divisor);
      } else
      if((result[q] != '/') & (divFlag == 0)) { 
        strncat(tempDividend, &result[q], 1);
      }
    }

  dividend = atoi(tempDividend);
  divisor = atoi(tempDivisor);
  printf("dividend: %d\n", dividend);
  printf("divisor: %d\n", divisor);
  float frac = (float)divisor / (float)dividend;
  printf("%f", frac);
   
  result = strrev(result);
  ret = atoi(result);
  free(result);
  }
  return ret;
}

int isFunctionOfX(char *startFunction) {

  int flag = 0;
  int len = strlen(startFunction);
  for (int i = 0; i < len; i++) {
    if (startFunction[i] == 'x') {
      flag = 1;
      return flag;
    }
  }
  return flag;
}
// uses parsePower and parseBase to create a calculate power rule for given
// function

char *powerRule(char *startFunction) {

  int len = strlen(startFunction);
  int base, power, flag;
  char *result = (char *)malloc(sizeof(char) * len);

  power = parsePower(startFunction);
  base = parseBase(startFunction);
  flag = isFunctionOfX(startFunction);
  
  if ((power == 0) & (flag == 1)) {
    if(base == 0) { 
      base = 1;
    }
    sprintf(result, "%d", base);
    return result;
  } else if ((power == 0) & (flag == 0)) {
    return NULL;
  } else if ((power != 0) & (flag == 1)) {
    if(base == 0) { 
      base = 1;
    } else if(power == 0) { 
      power = 1;
    } else if(power == 0 & base == 0) {
      base = 1;
      power = 1;
    }

    base = base * power;
    power = power - 1;
    if (power == 1) {
      sprintf(result, "%dx", base);
      return result;
    } else if(power == 0) {
      sprintf(result, "%d", base);
      return result;
    } else {
      sprintf(result, "%dx^%d", base, power);
      return result;
    }
  }
  return NULL;
}

// function calculates trig derivatives, assumes given function is a trig function
char *trigFunction(char *startFunction) { 
  
  int len = strlen(startFunction);
  int signFlag = isNegative(startFunction);
  int xFlag = 0;
  char *result = (char *)malloc(sizeof(char) * len);
  char *insideFunction = parseFunction(startFunction);
  if(strcmp(insideFunction, "x") == 1) { 
     
  }
  //iterates pointer to remove first character
  if(signFlag == 1) { 
    startFunction++;
  }
  switch(startFunction[0]) { 
    case 'c':
       
      if(startFunction[2] == 's') {
        if(signFlag == 1) { 
          sprintf(result, "sin(%s)", insideFunction);
          break;
        } else { 
          sprintf(result, "-sin(%s)", insideFunction); 
          break; 
        }
      } else if(startFunction[2] == 't') { 
          if(signFlag == 1) { 
            sprintf(result, "csc^2(%s)", insideFunction); 
            break;
          } else {  
            sprintf(result, "-csc^2(%s)", insideFunction); 
            break; 
        }
      } else { 
          if(signFlag == 1) { 
            sprintf(result, "csc(%s)cot(%s)", insideFunction, insideFunction); 
            break;
          } else { 
            sprintf(result, "-csc(%s)cot(%s)", insideFunction, insideFunction); 
            break; 
          }
      }
    case 's':
      if(startFunction[1] == 'i') { 
        if(signFlag == 1) {  
          sprintf(result, "-cos(%s)", insideFunction); 
          break;
        } else {  
          sprintf(result, "cos(%s)", insideFunction); 
          break;
        } 
      } else {     
        if(signFlag == 1) {  
          sprintf(result, "-sec(%s)tan(%s)", insideFunction, insideFunction); 
          break;
        } else {  
          sprintf(result, "sec(%s)tan(%s)", insideFunction, insideFunction); 
          break;
        }
      }
    case 't':
      if(signFlag == 1) {  
        sprintf(result, "sec^2(%s)", insideFunction); 
        break;
      } else {  
        sprintf(result, "-sec^2(%s)", insideFunction); 
        break;
      } 
  }
  if(strcmp(insideFunction, "x\0") == 1) { 
    return result;
  } else {
    if(result[0] == '-') {
      signFlag = 1;
    } else {
      signFlag = 0;
    }
    char *insideDeriv = powerRule(insideFunction);
    char *temp = result;
    if(signFlag == 1) { 
      result++;
      strcat(insideDeriv, result);
      memmove(insideDeriv + 1, insideDeriv, strlen(insideDeriv) + 1);
      insideDeriv[0] = '-';
    } else { 
      strcat(insideDeriv, result);
    }
    return insideDeriv;
  } 
  return result;
}


int main() {
  char testFunction[256];

  // runs prompt until user enters quit
  while(strcmp(testFunction, "quit")) {  
    printf("Function to differentiate: ");
    scanf("%s", testFunction);   
    if(!strcmp(testFunction, "quit\0")) { 
      return 0;
    }
    printf("Trig Derivative: %s\n", trigFunction(testFunction));
  }
  return 0;
}
