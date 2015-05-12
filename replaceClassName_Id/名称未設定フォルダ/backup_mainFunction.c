/*
 * mainFunction.c
 *
 *  Created on: 2015/05/06
 *      Author: hikozuma
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 1

/*
 * #ifdef DEBUG
 * 		printf("value = %d\n", i);
 * #endif
 */

void bubbleSortString(char targetArr[128][30], int length);
void getUniqueClassName(char targetArr[128][30], char targetUniqueArr[128][30], int length);
void getShortClassName(char targetArr[128][30], char targetShortArr[128][2]);

int main(){
	FILE *fp, *outputFp;
	char s[256];
	char *findClassStrP;
	char *beginClassNameP;
	char *endClassNameP;
	char *tok;

	char className[128][30] = {"\0"};
	char uniqueClassName[128][30] = {"\0"};
	char shortClassName[128][2]  = {"\0"};
	//int  classNameCnt[128] = {0};

	int k = 0;
	int cnt = 0;
	int strLen;
	char tmpStr[256];

	if((fp = fopen("google.html", "r")) == NULL){
		printf("file open error\n");
		return 0;
	}

	if((outputFp = fopen("googleReplace.html", "w")) == NULL){
		printf("new file open error\n");
		return 0;
	}

	//read all class name, including duplication
	while(fgets(s,256, fp) != NULL){
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
	getUniqueClassName(className, uniqueClassName, cnt);
	getShortClassName(uniqueClassName, shortClassName);

	fseek(fp, 0, SEEK_SET);

	//replace class name with short name
	while(fgets(s, 256, fp) != NULL){

		findClassStrP = strstr(s, "class=");

		// don't have to replace
		if(findClassStrP == NULL){

		// have to replace
		}else{

		}


	}




	for(k = 0; k < cnt; k++){
		printf("idx = %d, value = %s\n", k, className[k]);
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

void getUniqueClassName(char targetArr[128][30], char targetUniqueArr[128][30], int length){
	int i;
	int compareIdx = 0;

	if(length < 1){
		return;
	}

	strcpy(targetUniqueArr[0], targetArr[0]);

	for(i = 1; i < length; i++){
		if(strcmp(targetUniqueArr[compareIdx], targetArr[i]) != 0){
			compareIdx++;
			strcpy(targetUniqueArr[compareIdx], targetArr[i]);
		}
	}
}

void getShortClassName(char targetArr[128][30], char targetShortArr[128][2]){
	int i = 0;
	char tmp[3];

	while(strcmp(targetArr[i], "\0") != 0){
		sprintf(tmp, "%c%d", 'a' + i / 10, i % 10);

		printf("i = %d, tmp = %s\n", i, tmp);
		strcmp(targetShortArr[i], tmp);
		i++;
	}
}


