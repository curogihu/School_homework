/*
 * mainFunction.c
 *
 *  Created on: 2015/05/06
 *      Author: hikozuma
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubbleSortString(char targetArr[128][30], int length);
void getAppearanceCnt(char targetArr[128][30], int targetCntArr[128], int length);

int main(){
	FILE *fp, *beginFp;
	char s[256];
	char *findClassStrP;
	char *beginClassNameP;
	char *endClassNameP;
	char *tok;

	char className[128][30] = {"\0"};
	int  classNameCnt[128] = {0};

	int j, k, cnt = 0;
	int strLen;
	char tmpStr[256];

	if((fp = fopen("google.html", "r")) == NULL){
		printf("file open error\n");
		return 0;
	}

	beginFp = fp;

	while(fgets(s,256, beginFp) != NULL){
		findClassStrP = strstr(s, "class=");

		if(findClassStrP != NULL){
			beginClassNameP = strstr(findClassStrP + 1, "\"");
			endClassNameP = strstr(beginClassNameP + 1, "\"");

			strLen = endClassNameP - beginClassNameP - 1;

			if(strLen > 0){
				strncpy(tmpStr, beginClassNameP + 1, strLen);
				tmpStr[strLen] = '\0';

				tok = strtok(tmpStr, " ");

				while(tok != NULL){
					strcpy(className[cnt], tok);
					tok = strtok(NULL, " ");

					cnt++;
				}
			}

		}
	}

	bubbleSortString(className, cnt);
	getAppearanceCnt(className, classNameCnt, cnt);

	//replace class name with short word, such as a, b, c;

	for(k = 0; k < cnt; k++){
		printf("cnt = %d, value = %s\n", classNameCnt[k], className[k]);
	}

	fclose(fp);
	return 0;
}

void bubbleSortString(char targetArr[128][30], int length){
	int i, j;
	char swapTmp[30];

	for(i = 0; i < length - 1; i++){
		for(j = i + 1; j < length; j++){
			if(strcmp(targetArr[i], targetArr[j]) > 0){
				strcpy(swapTmp, targetArr[i]);
				strcpy(targetArr[i], targetArr[j]);
				strcpy(targetArr[j], swapTmp);
			}
		}
	}
}

void getAppearanceCnt(char targetArr[128][30], int targetCntArr[128], int length){
	int i;

	if(length > 0){
		targetCntArr[0] = 1;
	}

	for(i = 1; i < length; i++){
		if(strcmp(targetArr[i - 1], targetArr[i]) == 0){
			targetCntArr[i] = targetCntArr[i - 1] + 1;

		}else{
			targetCntArr[i] = 1;
		}
	}
}
