#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;
struct Poly
{
        string name;
        double *val;
	int len;//多项式数组长度
};
bool CalDiv(vector<Poly> polylist);
Poly Mod(Poly p, int power);
Poly Rever(Poly a);
void CalRev(vector<Poly> polylist);
bool MixedCal(vector<Poly> polylist);
bool LegalName(string name, vector<Poly> polylist);
void newPoly(vector<Poly> &list);
void Print(vector<Poly> polylist);
void PrintSing(Poly p);
Poly Add(Poly p1, Poly p2);
Poly Sub(Poly p1, Poly p2);//p1-p2
Poly Mul(Poly p1, Poly p2);
bool HeadTail(string infix,vector<Poly> polylist);
bool AfterPlusMul(string infix,vector<Poly> polylist);
bool AfterPoly(string infix,vector<Poly> polylist);
bool InteLegal(string infix,vector<Poly> polylist);
bool DerivLegal(string infix);
bool Junior(string a,string b);
bool ToSuffix(string infix, string &suffix, vector<Poly> polylist);
Poly Deriv(Poly orig);
double Value(Poly p, double x0);
Poly IntePoly(Poly p);
void Range(string test, double &lower, double &higher);
double Inte(Poly p,string range);
Poly CalExpress(string suffix, vector<Poly> polylist);
void mainstream();
double Root(Poly F);
void CalRoot(vector<Poly> polylist);
void Divis(Poly divid, Poly divisor, Poly &quo, Poly &remain);
Poly ReverOrder(Poly p);
