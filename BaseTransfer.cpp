#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define scale 1024

using namespace std;

int getSrcNum(int srcBase, char num) {

  if (srcBase >= 2 && srcBase <= 10) {
    return num - '0';
  }

  return 10 + (num - 'A' + 1);
}

char getDestChar(int num) {

  // 数字
  if (num >= 0 && num <= 9) {
    return '0' + num;
  }

  // 字母
  return 'A' + (num - 10);
}

void translateMagicNum(int magicNum, int destBase, char dest[]) {

  // Translate
  int i = 0;
  while (magicNum > 0) {

    int curDestNum = magicNum % destBase;

    char curDestChar = getDestChar(curDestNum);

    magicNum /= destBase;
    dest[i] = curDestChar;
    i++;
  }

  // Reverse.
  reverse(dest, dest + strlen(dest));
}

void transXtoY(char src[], int srcBase, int destBase, char dest[]) {

  // Calc MagicNum.
  reverse(src, src + strlen(src));

  int magicNum = 0;

  for (int i = 0; i < strlen(src); i++) {

    int curSrcNum = getSrcNum(srcBase, src[i]);
    magicNum += curSrcNum * (pow(srcBase, i));
  }

  // Translate
  translateMagicNum(magicNum, destBase, dest);
}

int main() {

  // I.
  char src[scale] = {0};
  char dest[scale] = {0};
  printf("please enter src number:\n");
  scanf("%s", &src);

  int src_base, dest_base;
  printf("please enter the base of src number:\n");
  scanf("%d", &src_base);
  printf("please enter the base of dest number:\n");
  scanf("%d", &dest_base);

  // A.
  transXtoY(src, src_base, dest_base, dest);

  printf("answer:\n");
  printf("%s\n", dest);

  // O.
  return 0;
}
