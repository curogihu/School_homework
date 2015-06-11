#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//using namespace string;

bool isIncludedTargetClass(string classNameStr, string keyClassName);

int main(){
	ifstream ifs("Google.html");
	ofstream ofs("output.txt");
	string sourceStr = "";
	string keyClassName = "hp";
	char ch;
	unsigned long foundBodyIdx, foundBodyEndIdx;
	unsigned long startclassIdx, startTagIdx;
	unsigned long endDoubleQuotIdx;
	string classNameStr;

	if (!ifs.is_open()){
		cout << "Unable to open file" << endl;
	}

	// import html file
	while (ifs.get(ch)){
		sourceStr += ch;
	}

	foundBodyIdx = sourceStr.find("<body", 0);
	//foundBodyEndIdx = sourceStr.find("</body>", 0);

	if (foundBodyIdx == string::npos){
		cout << "Error, not found starting body tag";
		return -1;
	}

	sourceStr = sourceStr.substr(foundBodyIdx);

	foundBodyEndIdx = sourceStr.find("</body>", 0);

	if (foundBodyEndIdx == string::npos){
		cout << "Error, not found ending body tag" << endl;
		return -1;
	}

	sourceStr = sourceStr.substr(0, foundBodyEndIdx + 7);
	cout << "sourceStr: " << sourceStr << endl << endl;

	startclassIdx = sourceStr.find("class=", 0);

	while (true){
		if(startclassIdx == string::npos){
			break;
		}

		// get class name string
		startclassIdx += 7; //skip class="
		endDoubleQuotIdx = sourceStr.find("\"", startclassIdx);

		//cout << sourceStr.substr(startclassIdx, endDoubleQuotIdx - startclassIdx);
		classNameStr = sourceStr.substr(startclassIdx, endDoubleQuotIdx - startclassIdx);

		// check whether including class name
		if(!isIncludedTargetClass(classNameStr, keyClassName)){

		// if found target class name
		}else{
			startTagIdx = sourceStr.find_last_of('<', startclassIdx);
			int aaa = sourceStr.find(" ");

			//cout << sourceStr.substr(startTagIdx);

			cout << "startTagIdx = " << startTagIdx << endl;
			cout << "aaa = " << aaa << endl;

			cout << "tag name = " << sourceStr.substr(startTagIdx + 1, aaa - 1);
		}

		break;


		// 1. looking for "class="
		// 2. get class name string
		// 2-1. if not including, ignored
		// 2-2. if including, get tag name by looking for "<".
		// 2-2-1. looking for end tag </div>
		// if including other start tag among ranges, adding looking for
		// if not including, output range from start tag to end one.
	}

	ofs << sourceStr;
}


bool isIncludedTargetClass(string classNameStr, string keyClassName){
	int blankFoundIdx;
	int startIdx = 0;
	string tmpClassName;

	cout << "classNameStr = " << classNameStr << endl;

	while(true){
		blankFoundIdx = classNameStr.find(" ", 0);

		if(blankFoundIdx == string::npos){
			break;
		}

		tmpClassName = classNameStr.substr(startIdx, blankFoundIdx);

		cout << "tmpClassName = " << tmpClassName << ", keyClassName = " << keyClassName << endl;

		if(keyClassName == tmpClassName){
			return true;
		}

		//blankFoundIdx = classNameStr.find(" ", blankFoundIdx + 1);
		classNameStr = classNameStr.substr(blankFoundIdx + 1);
	}

	cout << "classNameStr = " << classNameStr << ", keyClassName = " << keyClassName << endl;

	if(classNameStr == keyClassName){
		return true;
	}

	return false;
}
