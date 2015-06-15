//============================================================================
// Name        : SearchAppearance.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class CountingWord{

public:
	int wordCnt;
	int maxWordLen;
	string wordList[50000];
	int cntList[26][50];
	double percentageList[26][50];

	CountingWord();
	void importWordList(ifstream targetIfs);
};

CountingWord::CountingWord(){
	wordCnt = 0;
	maxWordLen = 0;

	for(int i = 0; i < 26; i++){
		for(int j = 0; j < 50; j++){
			cntList[i][j] = 0;
		}
	}
}

int main() {

	ifstream ifs("dictionaly.txt");
	ofstream ofs("output.txt");

	CountingWord cw;

	string str;
	const char *tmpStr;
	char alphabet;

	int foundBlankIdx;
	int i, j, k = 0;
	int wordLen;

	if (!ifs.is_open()){
		cout << "Unable to open file" << endl;
	}

	while(getline(ifs, str)){
		foundBlankIdx = str.find(" ");

		if(foundBlankIdx != string::npos){
			str = str.substr(0, foundBlankIdx);
		}

		cw.wordList[cw.wordCnt] = str;
		cw.wordCnt++;

		if(cw.maxWordLen < str.length()){
			cw.maxWordLen = str.length();
		}
	}

	for(i = 0; i < cw.wordCnt; i++){
		wordLen = cw.wordList[i].length();
		transform(cw.wordList[i].begin(), cw.wordList[i].end(), cw.wordList[i].begin(), ::tolower);
		tmpStr = cw.wordList[i].c_str();

		for(j = 0; j < wordLen; j++){

			if('a' <= tmpStr[j] && tmpStr[j] <= 'z'){

				alphabet = 'a';

				for(k = 0; k < 26; k++){
					if(tmpStr[j] == alphabet){
						cw.cntList[k][j] += 1;
						break;
					}

					alphabet++;
				}
			}
		}
	}

	for(i = 0; i < 26; i++){
		for(j = 0; j < cw.maxWordLen; j++){
			cw.percentageList[i][j] = (double)cw.cntList[i][j] / cw.wordCnt * 100;
		}
	}

	alphabet = 'a';

	ofs << "wordCnt = " << cw.wordCnt << endl << endl;

	// output result to file
	for(i = 0; i < 26; i++){
		double minPercentage = 100;
		double maxPercentage = 0;

		for(j = 0; j < cw.maxWordLen; j++){

			if(cw.percentageList[i][j] < minPercentage){
				minPercentage = cw.percentageList[i][j];
			}

			if(cw.percentageList[i][j] > maxPercentage){
				maxPercentage = cw.percentageList[i][j];
			}

			if(cw.cntList[i][j] > 0){
				if((j + 1 == 1) || (j + 1 > 20 && (j + 1) % 10 == 1)){
					ofs << "char = " << alphabet << ", " <<
							j + 1 << "st, cnt = " << cw.cntList[i][j] <<
							", rate = " << fixed << setprecision(2) << cw.percentageList[i][j] << "%" << endl;

				}else if((j + 1 == 2) || (j + 1 > 20 && (j + 1) % 10 == 2)){
					ofs << "char = " << alphabet << ", " <<
							j + 1 << "nd, cnt = " << cw.cntList[i][j] <<
							", rate = " << fixed << setprecision(2) << cw.percentageList[i][j] << "%" << endl;

				}else if((j + 1 == 3) || (j + 1 > 20 && (j + 1) % 10 == 3)){
					ofs << "char = " << alphabet << ", " <<
							j + 1 << "rd, cnt = " << cw.cntList[i][j] <<
							", rate = " << fixed << setprecision(2) << cw.percentageList[i][j] << "%" << endl;
				}else{
					ofs << "char = " << alphabet << ", " <<
							j + 1 << "th, cnt = " << cw.cntList[i][j] <<
							", rate = " << fixed << setprecision(2) << cw.percentageList[i][j] << "%" << endl;
				}
			}

		}

		ofs << endl << "Max percentage is " << maxPercentage << "% "<< endl;
		ofs << "Min percentage is " << minPercentage << "%" << endl;
		ofs << "------------------------------------" << endl << endl;

		alphabet++;
	}

	cout << "finished" << endl;

	return 0;
}
