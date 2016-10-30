#include <fstream.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

int selFactor[14] = {1};
float fp[5][3], cp[14], fpw[5][3]= {
{3,4,6},
{4,5,7},
{3,4,6},
{7,10,15},
{5,7,10}
};

char *factors[]={"Data Communication",
"Distributed Data Processing",
"Performance",
"Heavily Used Configuration ",
"Transaction Role",
"Online Data Entry",
"End-User Efficiency",
"Online Update",
"Complex Processing",
"Reusability",
"Installation Ease",
"Operational Ease",
"Multiple Sites",
"Facilitate Change"
};

void inputFactors(){
	cout << "Enter the complexity of the factors you selected:\n\
	1. No influence [0]\n\
	2. Incidental [1]\n\
	3. Moderate [2]\n\
	4. Average [3]\n\
	5. Significant [4]\n\
	6. Essential [6]\n";

	for(int i=0; i<14; i++){
		if(selFactor[i] == 0){
			cout << "Factor: " << factors[i] << ": ";
			cin >> cp[i];
		} else {
			cp[i] = 0;
		}
	}
}

void isOk(){
	cout << "\nall inputs is OK!\n";
}

void getFactors(){
	int i, j;
	cout << endl << "Enter a comma seperated list of complexity factors:" << endl;
	for(i=0; i<14; i++){
		cout << factors[i] << " [" << i+1 << "]" << endl;
	}
	char str[100];
	cin >> str;
	for(i=0; i<14; i++){
		selFactor[i] = -1;
	}

	i=0, j=0;
	while(str[i] != '\0'){
		char c1 = str[i], c2 = str[i+1], num[3];
//		selFactor[j] = -1;
		if(!isdigit(c1)){
			continue;
		}

		num[0] = c1;
		num[1] = '\0';
		if(isdigit(c2)){
			num[1] = c2;
			num[2] = '\0';
		}

		selFactor[atoi(num)] = 0;
		cout << atoi(num) << "parsed! :";
		i++;
	}

}

float UFP=0, CAF=0.65;

void parseFile(fstream *f){
int c;
for(int i=0; i<5 && !f->eof(); i++){
	for(int j=0; j<3 && !f->eof(); j++){
		*f >> c;
		fpw[i][j] = c;
	}
}
}

float evaluateUFP(){
float s=0;
for(int i=0; i<5; i++){
	for(int j=0; j<3; j++){
	      s+= fp[i][j] * fpw[i][j];
	}
}
return s;
}

float evaluateCAF(){
float s=0;
for(int i=0; i<14; i++){
	s+= cp[i];
}

CAF += (0.01*s);
return CAF;
}

void input1(int ch){
int i, j, val[]={0,0,0};
char *fac[] = {
"Input files",
"Output files",
"Enquiry Files",
"Internal Logical Files",
"External Interface Files",
};

for(j=0; j<5; j++){
	switch(ch){
	case 1:
		cout << "Enter low value for";
		break;

	case 2:
		cout << "Enter average value for";
		break;

	case 3:
		cout << "Enter high value for";
		break;

	case 4:
		cout << "Enter [low, average, high] values for";
		break;

	}

	cout << " " << fac[j] << ": ";
	for(i=0; i<3; i++){
		if(ch == 4){
			cin >> fp[j][i];
		} else {
			fp[j][i] = val[i];
		}
	}

	if(ch < 4 && ch > 0){
		cin >> fp[j][ch-1];
	}
	} // switch
}

void main(){
clrscr();
int ch=0;
fstream f("fp.txt", ios::in);
if(f){
	//cout << "reading";
	parseFile(&f);
}

/**
// file testing code:

for(int k=0; k<5; k++){
	for(int l =0; l<3; l++){
		cout << "\t" << fpw[k][l];
	}
	cout << endl;
}

//*/

cout << "Hello user!" << endl << "How would like to enter your function point values?" << endl\
<< "1. All low [1]\n"\
<< "2. All average [2]\n"\
<< "3. All high [3]\n"\
<< "4. Ask me for every factor[4]\n"\

<< "\nEnter a choice [1-4]:";

cin >> ch;

input1(ch);
getFactors();
isOk();
inputFactors();
/*
 cout << "Input your function points (15 integers) \
in the following order:\n\
\
\n3 values for each factor (low, average, high):\n";

for(int i=0; i<5; i++){
	for(int j=0; j<3; j++){
		cin >> fp[i][j];
	}
}

cout << "The values you enter \"is ok!\". Now input complexity factors (14 integers)\
(one of the 6 values [0-5] for each factor):\n";

for(i=0; i<14; i++){
	cin >> cp[i];
}
*/
UFP = evaluateUFP();
CAF = evaluateCAF();

cout << "\n\nResults:\n\
1. Unadjusted Function Point: " << UFP << "\n\
2. Complexity Adjustment Factor: " << CAF << "\n\
3. Function Point: " << UFP * CAF << endl;

getch();
}