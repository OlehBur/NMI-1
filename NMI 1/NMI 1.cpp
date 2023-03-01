﻿#include <Windows.h>
#include <cmath>
#include <iostream>

using namespace std;

int GetNumCntDecimal(const float& num) {
	float buff = num;
	int numbCnt = 0;
	while ((int)buff != buff) {
		buff *= 10;
		numbCnt++;
	}
	return numbCnt;
}

int GetIntCnt(const float& num) {
	int n = num, cnt = 0;
	while (n > 0) {
		n /= 10;
		cnt++;
	}
	return cnt;
}

float NarrowTrunc(const float &num, const float &errNum) {//кількість десятків після коми
	int cntNumbAftDec = GetNumCntDecimal(errNum);
	float narrowTruncNum = num;
	int cntCorrectNumbAftDec = ((errNum) < (0.5 / 10 * cntNumbAftDec)) ?//вірні знаки після коми
		cntNumbAftDec : 0/*всі числа сумнівні*/;

	int cntCorrectInt = GetIntCnt(num);//чи вірні цілі числа
		
	if (cntCorrectInt)//якщо не нуль (коректна ціла частина)
		return int(narrowTruncNum * 10 * cntCorrectNumbAftDec) / float(10 * cntCorrectNumbAftDec);
		/*(int)narrowTruncNum + cntCorrectNumbAftDec) << narrowTruncNum - (int)narrowTruncNum)*//*/(10*cntCorrectNumbAftDec)*/;
	//від цілої ч. віднімаєм остачу поділену на колво існуючих елемів після коми
	return ceil(num);
}

int main(){
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
			
			//1)
	const int sqrtNum = 10, dividible = 15, divider = 7;
	const float sqrtNumResult = 3.16, divResult=2.14;
	
	const float realSqrtResult = sqrt(sqrtNum),
		realDivResult = (float)dividible / divider,
		AbsoluteErr_Sqrt = realSqrtResult - sqrtNumResult,
		RelativeErr_Sqrt = (AbsoluteErr_Sqrt / realSqrtResult) * 100,
		AbsoluteErr_Div = realDivResult - divResult,
		RelativeErr_Div = (AbsoluteErr_Div / realDivResult) * 100;

	printf("\n 1)Визначити яка рівність точніша:\n\ta) №%d = %g;\n", sqrtNum, sqrtNumResult);
	printf("\tb) %d/%d = %g.\n", dividible, divider, divResult);
	printf("\tОскільки рівність 'а)' має похибку у %g%%, а рівність 'b)' - %g%%, то рівність '%c)' точніша.\n", 
		RelativeErr_Sqrt, RelativeErr_Div, (RelativeErr_Sqrt < RelativeErr_Div) ? 'a' : 'b');

			//2)
	const float floatNumb = 2.3165, numDeviations = 0.0042,
		floatNumb1 = 0.34484, percentDeviations = 0.4;
	const float floatNumbResul = trunc (floatNumb);

	printf("\n 2)Округлити сумнівні цифри числа, залишивши вірні знаки (у вузьклому/широкому розумінні):\n\ta) %g (+-%g);\n", floatNumb, numDeviations);
	printf("\tb) %g, б=%g%%.\n", floatNumb1, percentDeviations);
	printf("\ta) у вузькому розумінні округлюється до: %g\n", NarrowTrunc(floatNumb, numDeviations));
	
			//3)
	const float floatNumb2 = 2.3445, floatNumb3 = 0.745;
	printf("\n 3)Знайти граничні абсолютні та відносні похибки чисел, якщо вони мають лише вірні цифри:\n\ta) %g;\n", floatNumb2);
	printf("\tb) %g.\n", floatNumb3);
}