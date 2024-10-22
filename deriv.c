// derivative calculator by Strydr Silverberg
// done sophomore year at Colorado School of Mines
// https://github.com/StrydrS/deriv
// not yet licensed (is shit)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

  if (strlen(result) <= 1) {
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
  int flag = isNegative(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);

  //iterates pointer to remove first character
  if(flag == 1) { 
    startFunction++;
  }
  
  switch(startFunction[0]) { 
    case 'c':
      if(startFunction[2] == 's') {
        if(flag == 1) { 
          strcpy(result, "sin(x)");
          return result;
          break;
        } else { 
          strcpy(result, "-sin(x)");
          return result;
          break; 
        }
      } else if(startFunction[2] == 't') { 
          if(flag == 1) { 
            strcpy(result, "csc^2(x)");
            return result;
            break;
          } else { 
            strcpy(result, "-csc^2(x)");
            return result;
            break; 
        }
      } else { 
          if(flag == 1) { 
            strcpy(result, "csc(x)cot(x)");
            return result;
            break;
          } else { 
            strcpy(result, "-csc(x)cot(x)");
            return result;
            break; 
          }
      }
    case 's':
      if(startFunction[1] == 'i') { 
        if(flag == 1) { 
          strcpy(result, "-cos(x)");
          return result;
          break;
        } else { 
          strcpy(result, "cos(x)");
          return result;
          break;
        } 
      } else {     
        if(flag == 1) { 
          strcpy(result, "-sec(x)tan(x)");
          return result;
          break;
        } else { 
          strcpy(result, "sec(x)tan(x)");
          return result;
          break;
        }
      }
    case 't':
      if(flag == 1) { 
        strcpy(result, "-sec^2(x)");
        return result;
        break;
      } else { 
        strcpy(result, "sec^2(x)");
        return result;
        break;
      } 
  }
  return NULL;
}

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

int main() {
  char testFunction[256];
  printf("Function to differentiate: ");
  scanf("%s", testFunction);

  printf("Inside function: %s\n", parseFunction(testFunction));
  printf("Trig Derivative: %s\n", trigFunction(testFunction));
  printf("Power Rule Derivative: %s\n", powerRule(testFunction));
}
