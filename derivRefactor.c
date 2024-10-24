// derivative calculator by Strydr Silverberg
// done sophomore year at Colorado School of Mines
// https://github.com/StrydrS/deriv
// not yet licensed (is shit)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrev(char *input) { 
  char *p1, *p2;

  if(!input || !*input) return input;
  for(p1 = input, p2 = input + strlen(input) - 1; p2 > p1; ++p1, --p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return input;
}

int isFunctionOfX(char *startFunction) {
  
  int flag = 0;
  int len = strlen(startFunction);
  for(int i = 0; i < len; i++) {
    if(startFunction[i] == 'x') { 
      flag = 1; 
      return flag;
    }
  } return flag;
}

char *getInsideFunction(char *startFunction) { 
  int len = strlen(startFunction);
  char* result = (char *)malloc(sizeof(char) * len);
  int flag = 0;
  
  
  while((len > 0) & (flag == 0)) { 
    if((startFunction[len] != 'x') & (startFunction[len] != '^')) {
      if(startFunction[len] != ')') {
        strncat(result, &startFunction[len], 1);
      }
    } else {
      flag = 1;
    } len --;
  } 

  return result;

}

char *floatToFrac(float f, int divisor) {
  int dividend = 0;
  int completeFlag = 0;
  float epsilon = 0.001;
  float test;
  char test1[32], test2[32];
  char *frac = (char *)malloc(sizeof(char) * 64);
  
  sprintf(test2, "%.3f", f);

  while(completeFlag != 1) { 
    test = (float)dividend/(float)divisor;
    sprintf(test1, "%.3f", test);
    if(f <= 1.0) {
      dividend -= 1;
      if(strcmp(test1, test2) == 0) {
        completeFlag = 1;
      }
    } else if(f > 1.0) { 
      dividend +=1;
      if(strcmp(test1,test2) == 0) { 
        completeFlag = 1;
      }
    }
  }
  sprintf(frac, "%d/%d", dividend + 1, divisor); 
  return frac; 
}

char *parsePowerFloat(char *insideFunction) { 

  int len = strlen(insideFunction); 
  char *tempDividend = (char *)malloc(sizeof(char) * len); 
  char *result = (char *)malloc(sizeof(char) * len);
  char *tempDivisor = (char *)malloc(sizeof(char) * len);
  int divisor, dividend;
  int divFlag = 1;
  
  insideFunction = strrev(insideFunction);

  for(int i = 0; i < len + 1; i++) {
    if((insideFunction[i] != '/') & (divFlag ==1)) {
      strncat(tempDividend, &insideFunction[i], 1);
    } else if(insideFunction[i] == '/') {
      divFlag = 0;
    } else if((insideFunction[i] != '/') & (divFlag == 0)) {
      strncat(tempDivisor, &insideFunction[i], 1);
    } 
  }

  divisor = atoi(tempDivisor);
  dividend = atoi(tempDividend);
  float frac = (float)dividend / (float)divisor;
  frac = frac - 1.0;
  result = floatToFrac(frac, divisor);

  return result;
}

int parsePower(char *startFunction) { 
  
  char *result = getInsideFunction(startFunction);
  result = strrev(result);

  int ret = atoi(result);
  free(result);
  result = NULL;
  return ret;

}

int parseBase(char *startFunction) { 
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);
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
  return ret;
}

int isPowerFrac(char *startFunction) {
  int len = strlen(startFunction); 
  int isFraction = 0; 
  char* result = getInsideFunction(startFunction); 

  for(int i = 0; i < len; i++) { 
    if(result[i] == '/') {
      isFraction = 1;
    }
  }
  return isFraction;
}

char *mulByConst(char *startFunction) { 
  
  printf("start function: %s", startFunction);


} 

char *powerRule(char *startFunction) { 
  
  int len = strlen(startFunction);
  int base, power;
  char *newFracPower = (char *)malloc(sizeof(char) * len);
  char *result = (char *)malloc(sizeof(char) * len);
  char *insideFunction = getInsideFunction(startFunction);
  int fractionFlag = isPowerFrac(startFunction);

  if(fractionFlag) {
    newFracPower = parsePowerFloat(insideFunction);
    sprintf(result, "%sx^%s", insideFunction, newFracPower);
    return result;
  } else { 
    power =  parsePower(startFunction);
    printf("power: %d\n", power);
    base = parseBase(startFunction);
    if(power == 0) {
      if(base == 0) {
        base = 1;
      }
    sprintf(result, "%d", base);
      printf("%d", power);
    return result; 
  } else if(power != 0) {
      if(base == 0) base = 1;
      base = base * power; 
      power = power - 1;
      
      if(power == 1) {
        sprintf(result, "%dx", base);
        return result;
      } else if(power != 0) {
        sprintf(result, "%dx^%d", base, power);
        return result;
    }
  }

  }
  sprintf(result, "%d", base);
  mulByConst(result);
  return result; 
}

int isTrigFunction(char *startFunction) { 
  
  int len = strlen(startFunction); 
  if(strstr(startFunction, "cos") != NULL) { 
    return 1; 
  } else if(strstr(startFunction, "sin") != NULL) { 
    return 1;
  } else if(strstr(startFunction, "tan") != NULL) {
    return 1;
  } else if(strstr(startFunction, "csc") != NULL) {
    return 1;
  } else if(strstr(startFunction, "sec") != NULL) {
    return 1;
  } else if(strstr(startFunction, "cot") != NULL) {
    return 1;
  }

  return 0;
}

int isNegative(char *startFunction) {
  int flag = 0;
  if(startFunction[0] == '-') {
    flag = 1;
    return flag;
  }
  return flag;
}

char *parseTrigFunction(char *startFunction) { 
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);

  for(int i = 0; i < len; i++) {
    if(startFunction[i] == '(') {
      strcat(result, &startFunction[i]);
    }
  }
  
  result++;
  len = strlen(result);
  result[len-1] = '\0';

  return result;
}

char *trigDerivative(char *startFunction) {
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);
  char *insideFunction = parseTrigFunction(startFunction);
  int xFlag = 0;
  int signFlag = isNegative(startFunction);

  if(signFlag == 1) { 
    startFunction++;
  }
  
  //logic for trig derivatives
  if(strstr(startFunction, "cos") != NULL) { 
    if(signFlag == 1) { sprintf(result, "sin(%s)", insideFunction); } 
    else { sprintf(result, "-sin(%s)", insideFunction); }
  } else if(strstr(startFunction, "sin") != NULL) { 
    if(signFlag == 1) { sprintf(result, "-cos(%s)", insideFunction); } 
    else { sprintf(result, "cos(%s)", insideFunction); }
  } else if(strstr(startFunction, "tan") != NULL) {
    if(signFlag == 1) { sprintf(result, "-sec^2(%s)", insideFunction); } 
    else { sprintf(result, "sec^2(%s)", insideFunction); }
  } else if(strstr(startFunction, "csc") != NULL) {
    if(signFlag == 1) { sprintf(result, "csc(%s)cot(%s)", insideFunction, insideFunction); } 
    else { sprintf(result, "-csc(%s)cot(%s)", insideFunction, insideFunction); }
  } else if(strstr(startFunction, "sec") != NULL) {
    if(signFlag == 1) { sprintf(result, "-sec(%s)tan(%s)", insideFunction, insideFunction); } 
    else { sprintf(result, "sec(%s)tan(%s)", insideFunction, insideFunction); }
  } else if(strstr(startFunction, "cot") != NULL) {
    if(signFlag == 1) { sprintf(result, "csc^2(%s)", insideFunction); } 
    else { sprintf(result, "-csc^2(%s)", insideFunction); }
  }
  
  if(!strcmp(insideFunction, "x\0")) {
    return result;
  }

  printf("power rule returns: %s\n", powerRule(startFunction));

  return result;
}

char *differentiate(char *startFunction) {
  int len = strlen(startFunction);
  char *result = (char *)malloc(sizeof(char) * len);
  
  //case input is integer, result is 0
  int isFofX = isFunctionOfX(startFunction); 
  if(isFofX == 0) { strcpy(result, "0"); return result; }
  
  if(strstr(startFunction, "^") != NULL) { result = powerRule(startFunction); } 
  if(startFunction[len-1] == 'x') { startFunction[len-1] = '\0'; return startFunction; }
  int isTrigFlag = isTrigFunction(startFunction);
  if(isTrigFlag == 1) { result = trigDerivative(startFunction); }
  return result;
}


int main() { 
  
  char testFunction[256];
  
  while(strcmp(testFunction, "quit")) { 
    printf("Function to differentiate: ");
    scanf("%s", testFunction);
    if(!strcmp(testFunction, "quit")) { 
      return 0;
    }
    printf("Derivative: %s\n", differentiate(testFunction));
  }

  return 0;

}
