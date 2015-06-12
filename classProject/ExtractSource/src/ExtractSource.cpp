#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define START_BODY_TAG "<body"
#define END_BODY_TAG "</body>"

using namespace std;

bool isIncludedTargetClass(string classNameStr, string keyClassName);

/*
class ExtractSource{

public:
	unsigned long startBodyTagIdx;
	unsigned long endBodyTagIdx;

	long getStartBodyIdx(string targetSource);
	long getEndBodyTagIdx();

};
*/

int main(){
	ifstream ifs("itd_canada.html");
	ofstream ofs("output.txt");
	string sourceStr = "";
	string keyClassName = "LOGIN";

	char ch;

	unsigned long foundBodyIdx, foundBodyEndIdx;
	unsigned long startclassIdx, startTagIdx;
	unsigned long endDoubleQuotIdx, endTagIdx;
	unsigned long blankIdx;
	string classNameStr;
	string tagName;
	int cnt = 1;
	string quotationMark;

	//ExtractSource es;

	if (!ifs.is_open()){
		cout << "Unable to open file" << endl;
	}

	while (ifs.get(ch)){
		sourceStr += ch;
	}

	foundBodyIdx = sourceStr.find(START_BODY_TAG, 0);

	//es.startBodyTagIdx = es.getStartBodyIdx(sourceStr);

	if (foundBodyIdx == string::npos){
		cout << "Error, not found starting body tag";
		return -1;
	}

	sourceStr = sourceStr.substr(foundBodyIdx);
	foundBodyEndIdx = sourceStr.find(END_BODY_TAG, 0);

	if (foundBodyEndIdx == string::npos){
		cout << "Error, not found ending body tag" << endl;
		return -1;
	}

	// 7 = </body>.length
	sourceStr = sourceStr.substr(0, foundBodyEndIdx + 7);

	//cout << "sourceStr = " << sourceStr << endl;

	startclassIdx = sourceStr.find("class=", 0);

	while (true){
		if(startclassIdx == string::npos){
			break;
		}

		quotationMark = sourceStr.substr(startclassIdx + 6, 1);

		//cout << "quotationMark = " << quotationMark << endl;

		// get class name string
		startclassIdx += 7; //skip string, class="

		//endDoubleQuotIdx = sourceStr.find("\"", startclassIdx);
		endDoubleQuotIdx = sourceStr.find(quotationMark, startclassIdx);


		classNameStr = sourceStr.substr(startclassIdx, endDoubleQuotIdx - startclassIdx);

		if(isIncludedTargetClass(classNameStr, keyClassName)){
			startTagIdx = sourceStr.find_last_of('<', startclassIdx);
			blankIdx = sourceStr.find(" ", startTagIdx);

			tagName = sourceStr.substr(startTagIdx + 1, blankIdx - startTagIdx - 1);
			endTagIdx = sourceStr.find("</" + tagName + ">");

			sourceStr = sourceStr.substr(startTagIdx);

			//cout << "sourceStr = " << sourceStr;

			//cout << "startTagIdx = " << startTagIdx << endl;
			//cout << "blankIdx = " << blankIdx << endl;
			//cout << "tagName = " << tagName << endl;
			cout << "endTagIdx = " << endTagIdx << endl;

			string tmpStr;
			unsigned long tmpIdx = 0;
			long startTagCnt = 0;
			long endTagCnt = 0;

			// cnt start tag
			while(true){
				tmpIdx = sourceStr.find("<" + tagName, tmpIdx);

				if(tmpIdx == string::npos){
					//cout << "tmpIdx = " << tmpIdx << " startTagCnt = " << startTagCnt << endl << endl;
					break;
				}

				startTagCnt++;
				tmpIdx++;
			}

			for(endTagCnt = 0, tmpIdx = 0; endTagCnt < startTagCnt; endTagCnt++){

				tmpIdx = sourceStr.find("</" + tagName + ">", tmpIdx);
				tmpIdx += tagName.length() + 3;
			}

			endTagIdx = tmpIdx;

			ofs << "No. " << cnt << endl << endl;
			ofs << sourceStr.substr(0, endTagIdx) << endl << endl << endl;

			cnt++;
		}

		// remove string including "class=" for avoiding reading.
		sourceStr = sourceStr.substr(startclassIdx);
		startclassIdx = sourceStr.find("class=", 0);
	}

	//ofs << sourceStr;

	cout << "finished." << endl;
}


bool isIncludedTargetClass(string classNameStr, string keyClassName){
	int blankFoundIdx;
	int startIdx = 0;
	string tmpClassName;

	//cout << "classNameStr = " << classNameStr << endl;
	transform(keyClassName.begin(), keyClassName.end(), keyClassName.begin(), ::tolower);

	while(true){
		blankFoundIdx = classNameStr.find(" ", 0);

		if(blankFoundIdx == string::npos){
			break;
		}

		tmpClassName = classNameStr.substr(startIdx, blankFoundIdx);
		transform(tmpClassName.begin(), tmpClassName.end(), tmpClassName.begin(), ::tolower);

		//cout << "tmpClassName = " << tmpClassName << ", keyClassName = " << keyClassName << endl;

		if(keyClassName == tmpClassName){
			return true;
		}

		//blankFoundIdx = classNameStr.find(" ", blankFoundIdx + 1);
		classNameStr = classNameStr.substr(blankFoundIdx + 1);
	}

	//cout << "classNameStr = " << classNameStr << ", keyClassName = " << keyClassName << endl;

	if(classNameStr == keyClassName){
		return true;
	}

	return false;
}
