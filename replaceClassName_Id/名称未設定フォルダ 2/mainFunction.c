
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

#define TRUE 1
#define FALSE 0

/*
 * #ifdef DEBUG
 * 		printf("value = %d\n", i);
 * #endif
 */

void bubbleSortString(char targetArr[128][30], int length);
void getUniqueClassName(char targetArr[128][30], char targetUniqueArr[128][30], int length);
void getShortClassName(char targetArr[128][30], char targetShortArr[128][3]);

int main(){
	FILE *fp, *outputFp;
	char s[256];
	char *findClassStrP;
	char *beginClassNameP;
	char *endClassNameP;
	char *tok;

	char className[128][30] = {"\0"};
	char uniqueClassName[128][30] = {"\0"};
	char shortClassName[128][3]  = {"\0"};
	//char tmpClassName[128];
	//int  classNameCnt[128] = {0};

	int k = 0;
	int cnt = 0;
	int strLen;
	char tmpStr[256];

	//int a = 0;
	/*
	int styleFlg = FALSE;
	*/
	int bodyFlg = FALSE;

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

#ifdef DEBUG
		/*
		a++;

		if(a < 20){
			printf("%s\n", s);
		}
		*/
#endif

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

#ifdef DEBUG
/*
 	for(int ax = 0; ax < 36; ax++){
		printf("idx = %d, before = %s, after = %s\n", ax, uniqueClassName[ax], shortClassName[ax]);
	}
	*/
#endif

	fseek(fp, 0, SEEK_SET);
/*
	char *findStartStyleP;
	char *findEndStyleP;
	*/
	char *findStartBodyStyleP;
	char *findEndBodyStyleP;

	//replace class name with short name
	while(fgets(s, 256, fp) != NULL){
#ifdef DEBUG
//		fputs(s, outputFp);
//		fputs("\n", outputFp);
#endif

		findStartBodyStyleP = strstr(s, "<body");
		findEndBodyStyleP = strstr(s, "</body");

		//printf("flg = %d, string = %s\n, startP = %s, endP = %s\n", bodyFlg, s, findStartBodyStyleP, findEndBodyStyleP);

		if(findStartBodyStyleP != NULL){
			//printf("passed, bodyFlg = TRUE, s = %s\n", s);
			bodyFlg = TRUE;
		}

		if(findEndBodyStyleP != NULL){
			//printf("passed, bodyFlg = FALSE, s = %s\n", s);
			bodyFlg = FALSE;
		}

		if(bodyFlg){

			findClassStrP = strstr(s, "class=");

			// don't have to replace
			if(findClassStrP == NULL){
				fputs(s, outputFp);

			// have to replace
			}else{
				beginClassNameP = strstr(findClassStrP + 1, "\"");
				endClassNameP = strstr(beginClassNameP + 1, "\"");

				strLen = endClassNameP - beginClassNameP - 1;

				// class=""
				if(strLen == 0){
				//	printf("pass, strLen = 0\n");
					fputs(s, outputFp);

				// class="exampleName"
				}else{

					while(s + k < beginClassNameP + 1){
				//		printf("%c\n",s[k]);
						fputc(s[k], outputFp);
						k++;
					}

					//replace class name with short class name
					strncpy(tmpStr, beginClassNameP + 1, strLen);
					tmpStr[strLen] = '\0';

					tok = strtok(tmpStr, " ");

					while(tok != NULL){
						//strcpy(className[cnt], tok);
						int z = 0;

						while(strcmp(uniqueClassName[z], "\0") != 0){

							if(strcmp(uniqueClassName[z], tok) == 0){
								break;
							}
							z++;
						}

						if(strcmp(uniqueClassName[z], "\0") == 0){
							//unexpected case
							fputs(tok, outputFp);

				//			printf("success, null\n");

						}else{
							fputs(shortClassName[z], outputFp);
							printf("success, replace, before = %s, after = %s\n", uniqueClassName[z], shortClassName[z]);
						}

						tok = strtok(NULL, " ");

						//when existing two class name or more, add blank
						if(tok != NULL){
							fputs(" ", outputFp);
						}
					}

					printf("successed , class name\n");

					// output string after class name.
					fputs(endClassNameP, outputFp);

					printf("successed , after class name\n");

				}		// }else{, strlen != 0
			}	//}else{, findClassStrP == NULL
		}	// if(bodyFlg){

		//not need
		//fputs("\n", outputFp);
	}


#ifdef DEBUG
/*
	for(k = 0; k < cnt; k++){
		printf("idx = %d, value = %s\n", k, className[k]);
	}
	*/
#endif

	fclose(fp);
	fclose(outputFp);
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

void getShortClassName(char targetArr[128][30], char targetShortArr[128][3]){
	int i = 0;
	char tmp[3];

	printf("Called, getShortClassName\n");

	while(strcmp(targetArr[i], "\0") != 0){
//		printf("idx = %d\n", i);

		sprintf(tmp, "%c%d", 'a' + i / 10, i % 10);

//		printf("i = %d, tmp = %s\n", i, tmp);

		strcpy(targetShortArr[i], strcat(tmp, "\0"));

//		printf("arr[%d] = %s\n", i, targetShortArr[i]);
		i++;
	}
/*
	for(i = 0; i < 10; i++){
		printf("%d, %s\n", i, targetShortArr[i]);
	}
	*/
}


