#include <Windows.h>
#include <cmath>
#include <iostream>

using namespace std;

int GetNumCntDecimal(const float& num) {
	float buff = num;
	int numbCnt = 0;
	if ((int)buff) {
		while ((int)buff != buff) {
			buff *= 10;
			numbCnt++;
		}
		return numbCnt;
	}
	else {

	}
}

int GetIntCnt(const float& num) {
	int n = num, cnt = 0;
		while (n > 0) {
			n /= 10;
			cnt++;
		}
		return cnt;
}

float MarginAbsoluteErr(const float& num) {
	return 0.00005 / num;
}

float MarginRelativeErr(const float& num) {
	return 0.001 / num;
}

float TruncByNumb(const float &num, const int& cntAftDec) {//округ після коми на к-сть знаків
	//float truncNum = num;
	//int cntr = 0;

	//if (GetIntCnt(truncNum))
	//	truncNum = int(num * 10 * cntAftDec) / float(10 * cntAftDec);
	//else {//якщо нуль ціла частина то треба погратись з повним висуванням ненулевих чисел в цілу ч на к-сть потрібних знаків
	//	while (GetIntCnt(truncNum) != cntAftDec) {
	//		truncNum *= 10;
	//		cntr++;
	//	}
	//	truncNum = int(num * 10 * cntAftDec) / float(10 * cntAftDec);
	//	truncNum /= 10 * cntr;
	//}



	//ПІД ПИТАННЯМ
	if ((int)num)
		return int(num * 10 * cntAftDec) / float(10 * cntAftDec);
	else {
		return int(num * 10 * (cntAftDec)) / float(10 * (cntAftDec));

	}

	//return ((int)num) ?
	//	int(num * 10 * cntAftDec) / float(10 * cntAftDec) :
	//	num;// int(TruncByNumb(num * 10 * 2 * GetNumCntDecimal(num), cntAftDec)) / float(10 * GetNumCntDecimal(num));
}

double TruncByNumb1(const float& num, const int& cntAftDec) {
	const float multiplier = pow(10.0, cntAftDec);

	return ceil(num * multiplier) / multiplier;
}


float BroadTruc1(const float& num, const float& relativeErr) {
	float absoluteErr = num* relativeErr;
	if (absoluteErr < 0.01)
		return ceil(num * 10000.0f) / 10000.0f; //TruncByNumb1(num, 3);
	return ceil(num * 1000.0) / 1000.0;
}

float NarrowTrunc(const float&, const float&);

float NarrowTrunc1(const float& num, const float& absoluteErr) {
	if (absoluteErr < 0.05)
		return ceil(num * 100.0f) / 100.0f;
	return ceil(num * 10.0f) / 10.0f;
}


float NarrowTrunc(const float &num, const float &absoluteErr) {//кількість десятків після коми
	int cntNumbAftDec = GetNumCntDecimal(absoluteErr);
	float narrowTruncNum = num;
	int cntCorrectNumbAftDec = ((absoluteErr) < (0.5 / 10 * cntNumbAftDec)) ?//вірні знаки після коми
		cntNumbAftDec : 0/*всі числа сумнівні*/;

	int cntCorrectInt = GetIntCnt(num);//чи вірні цілі числа
		
	if (cntCorrectInt)//якщо не нуль (коректна ціла частина)
		return TruncByNumb(narrowTruncNum, cntCorrectNumbAftDec);//int(narrowTruncNum * 10 * cntCorrectNumbAftDec) / float(10 * cntCorrectNumbAftDec);
		/*(int)narrowTruncNum + cntCorrectNumbAftDec) << narrowTruncNum - (int)narrowTruncNum)*//*/(10*cntCorrectNumbAftDec)*/;
	//від цілої ч. віднімаєм остачу поділену на колво існуючих елемів після коми
	return ceil(num);
}

float BroadTruc(const float& num, const float& relativeErr) {
		float AbsoluteErr = num * relativeErr / 100;
		//return NarrowTrunc(num, AbsoluteErr);
		float allCorrectNumb = GetNumCntDecimal(relativeErr)+2;
		if (AbsoluteErr < (10 / pow(10, allCorrectNumb)))//приблизна формула ~~похибка менш 0.01 при 3 знаках після коми у відносній
			return TruncByNumb(num, allCorrectNumb - //округлюєм до вірниx знаків після коми, тому вірні перед віднімаєм
				((int)num) ?
				GetIntCnt(num) : 1);
		else return AbsoluteErr;
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
	const float floatNumbResul = NarrowTrunc1(floatNumb, numDeviations),
		floatNumb1Result= BroadTruc1(floatNumb1, percentDeviations);

	printf("\n 2)Округлити сумнівні цифри числа, залишивши вірні знаки (у вузьклому/широкому розумінні):\n\ta) %g (+-%g);\n", floatNumb, numDeviations);
	printf("\tb) %g, б=%g%%.\n", floatNumb1, percentDeviations);

	printf("\ta) у вузькому розумінні округлюється до: %g\n", floatNumbResul);
	printf("\tb) у широкому розумінні округлюється до: %g\n", floatNumb1Result);
	

			//3)
	const float floatNumb2 = 2.3445, floatNumb3 = 0.745;
	const float floatNumb2Result = MarginRelativeErr(floatNumb2),
		floatNumb3Result = MarginAbsoluteErr(floatNumb3);

	printf("\n 3)Знайти граничні абсолютні та відносні похибки чисел, якщо вони мають лише вірні цифри:\n\ta) %g;\n", floatNumb2);
	printf("\tb) %g.\n", floatNumb3);

	printf("\ta) Гранична відносна похибкa:\t %g %%;", floatNumb2Result);
	printf("\n\tb) Гранична абсолютна похибка:\t %g %%.\n\n", floatNumb3Result);
}