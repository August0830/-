#pragma GCC diagnostic error "-std=c++11"
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#include <stack>
#include <sstream>
#include "Calculator.h"
using namespace std;
/*struct Poly
{
	string name;
	double *val;
	int len;//数组长度 最高项+1
};*/
int main()
{
	mainstream();
	/*vector<Poly> polylist;
	newPoly(polylist);
	PrintSing(polylist[0]);
	Poly mod=Mod(polylist[0],2);
	PrintSing(mod);*/
	//Poly p0r=ReverOrder(polylist[0]);
	//PrintSing(p0r);
	//PrintSing(polylist[1]);
	/*cout<<"input infix:";cin>>infix;
	if(ToSuffix(infix,suffix,polylist))
		cout<<suffix;
	else
		cout<<"n";*/
	//MixedCal(polylist);
	/*if(Junior("+","$[0,6]"))
		cout<<"y";*/
	//mainstream();
	/*infix="((ahc+bdef)!+C)*D+$[1,2](B+C)";
	if(infix[0]=='(')
		cout<<"(dan"<<endl;
	if(ToSuffix(infix,suffix))
		cout<<infix<<"\n"<<suffix<<endl;*/
	//Print(polylist);
	/*string range;cout<<"range: ";cin>>range;
	cout<<endl<<Inte(polylist[0],range);
	Poly sum=IntePoly(polylist[0]);
	polylist.push_back(sum);
	Print(polylist);*/
	//cout<<Value(polylist[0],2)<<endl;
	return 0;
}
bool CalDiv(vector<Poly> polylist)
{
	string dname,dvname,stmp;
	char c;
	bool next=false;
	do
	{
		cout<<"请输入表达式（F/G）:";
		cin>>stmp;
		for(auto &c:stmp)
		{
			if(c=='/')
				next=true;
			else
			{
				if(!next)
					dname.append(1,c);
				else
					dvname.append(1,c);
			}	
		}
		if(!next) 
			cout<<"输入错误！"<<endl;
	}while(!next);
	Poly divid,divis,ptmp,p1;
        for(auto &ptmp:polylist)
        {
                if(ptmp.name==dname)
                        divid=ptmp;
                if(ptmp.name==dvname)
                        divis=ptmp;
        }
        if(divid.val==NULL)
        {
                cout<<dname<<":该多项式不存在！"<<endl;
                return false;
        }
        if(divis.len<0)
        {
                cout<<dvname<<":该多项式不存在！"<<endl;
                return false;
        }
	Poly quo,remain;
        Divis(divid,divis,quo,remain);
        cout<<"商为：";PrintSing(quo);
        cout<<"余数为：";PrintSing(remain);
	return true;
}
void CalRev(vector<Poly> polylist)
{
	string name;
        cout<<"多项式名为：";
        cin>>name;
        Poly f,ptmp;
        for(auto &ptmp:polylist)
                if(ptmp.name==name)
                        f=ptmp;
        if(f.val==NULL)
                cout<<"该多项式不存在！"<<endl;
        else if(f.val[0]==0)
                cout<<"该多项式不存在逆元"<<endl;
        else
        {
                Poly prev=Rever(f);
                cout<<"逆元为：";
                PrintSing(prev);
        }

}
void CalRoot(vector<Poly> polylist)
{
	cout<<"多项式名为：";
        string name;
        cin>>name;
        Poly f,ptmp;
        for(auto &ptmp:polylist)
                if(ptmp.name==name)
                        f=ptmp;
        if(f.val==NULL)
                cout<<"该多项式不存在！";
        else
        {
                PrintSing(f);
                cout<<f.name<<"的存在实数根为："<<Root(f)<<endl;
        }
}
void mainstream()
{
	cout<<"=========================多项式计算器======================"<<endl;
	cout<<"1.输入 2.混合运算 3.求逆元 4.除法/取模运算 5.求根 6.查看"<<endl;
	cout<<"==========================================================="<<endl;
	int cmd;
	cout<<"请选择：(退出请输入-1)";
	cin>>cmd;
	vector<Poly> polylist;
	while(cmd!=-1)
	{
	switch(cmd)
	{
		case 1:newPoly(polylist);break;
		case 2:
		{
			if(polylist.empty())
				newPoly(polylist);
			MixedCal(polylist);break;
		}
		case 3:
		{
			if(polylist.empty())
                                newPoly(polylist);
			CalRev(polylist);
			break;
		}
		case 4:
		{
			if(polylist.empty())
				newPoly(polylist);
			CalDiv(polylist);
			break;
		}
		case 5:
		{
			if(polylist.empty())
                                newPoly(polylist);
			CalRoot(polylist);	
			break;
		}
		case 6:Print(polylist);break;//最后需要修改为输出指定多项式 判断不为空
		default:
		{
			cout<<"无法识别指令，需要退出请输入-1："<<endl;	
		}
	}
	cout<<"请选择：(退出请输入-1)";
	cin>>cmd;
	}
}
bool MixedCal(vector<Poly> polylist)
{
        char next;
        do
        {
                string infix,suffix;
                Poly res;
                cout<<"请输入表达式：";
                cin>>infix;
                if(!ToSuffix(infix,suffix,polylist))
                {
                        cout<<"表达式错误，是否重新输入(y/n):";
                }
                else
                {
                        res=CalExpress(suffix,polylist);
                        if(res.val!=NULL)
                        {
                                cout<<infix<<" = ";
                                PrintSing(res);
                                cout<<"运算成功！是否继续运算(y/n)：";
                        }
                        else
                                cout<<res.name;
                }
                cin>>next;
                while(next != 'y' && next!='n')
                {
                        cout<<"指令错误，请重新输入"<<endl;
                        cin>>next;
                }
        }while(next!='n');
        return true;
}
bool ToSuffix(string infix, string &suffix, vector<Poly> polylist)
{
        //if(!HeadTail(infix,polylist) || !AfterPlusMul(infix,polylist) || !InteLegal(infix,polylist) || !DerivLegal(infix) || 
        //!AfterPoly(infix,polylist))
        if(!InteLegal(infix,polylist) || !DerivLegal(infix))
                return false;
        stack<string> oper;
        for(int i=0;i<infix.length();++i)
        {
                string operlist="!*+-";
                if((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                {
                        string name;
                        //name.append(infix[i]);        
                        while((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                                name.append(1,infix[i++]);
                        suffix.append(name+" ");
                        --i;
                }
                else if(operlist.find(infix[i])!=operlist.npos||infix[i]=='('||infix[i]==')')
                {
                        if(i<infix.length()-1 && infix[i]=='(' && infix[i+1]==')')
                                return false;
                        if(infix[i]==')')
                        {
                                string op=oper.top();oper.pop();
                                while(!oper.empty()&& op!="(")
                                {
                                        suffix.append(op);suffix.append(" ");
                                        op=oper.top();oper.pop();
                                }
                                if(oper.empty() && op!="(")
                                        return false;
                        }
			else//
                        {
                                string str;str.append(1,infix[i]);
                                while(!oper.empty() && Junior(str,oper.top()) && infix[i]!='('&& infix[i]!=')')
                                {
                                        string op=oper.top();oper.pop();//取出栈顶符号
                                        suffix.append(op);suffix.append(" ");
                                }
                                string str1;str1.append(1,infix[i]);
                                oper.push(str1);
                        }
                }
                else if(infix[i]=='$')
                {
                        string inte;
                        while(infix[i]!=']')
                        {
                                inte.append(1,infix[i++]);
                        }
                        string st="]";
                        inte.append(st);cout<<inte<<endl;
                        while(!oper.empty() && Junior("$",oper.top()))
                        {
                                string op=oper.top();oper.pop();//取出栈顶符号
                                suffix.append(op);suffix.append(" ");
                        }
                        oper.push(inte);
                }
		else
                {
                        cout<<"混入不可识别的符号"<<endl;
                        return false;
                }
        }
        while(!oper.empty())
        {
                suffix.append(oper.top()+" ");
                oper.pop();
        }
        return true;
}
void Print(vector<Poly> polylist)
{
        Poly p;
        cout<<"多项式名为：";
        string name;
        cin>>name;
	bool isfind=false;
        for(auto &p:polylist)
        {
                if(p.name!=name)
                        continue;
		isfind=true;
                for(int i=p.len-1;i>-1;--i)
                {
                if(i!=p.len-1 && p.val[i]>0 && p.val[i+1]!=0)
                        cout<<"+";
                if((i==0 && p.val[i]!=0)||(p.val[i]!=1 && p.val[i]!=0))
                {
                        if(p.val[i]==-1 && i!=0)
                                cout<<"-";
                        else
                                cout<<p.val[i];//面对负号
                }
                if(i!=0 && p.val[i]!=0)
                        cout<<"x";
                if(i>1 && p.val[i]!=0)
                        cout<<"^"<<i;
                }
                cout<<endl;
        }
	if(!isfind)
		cout<<"该多项式不存在！"<<endl;
}
void newPoly(vector<Poly> &list)
{
        while(1)
        {
                Poly p;
                cout<<"多项式名为："<<endl;
                cin>>p.name;//需要检查修改checkname();
                while(!LegalName(p.name,list))
                {
                        cout<<"命名不合法请重新输入：";
                        cin>>p.name;
                }
                cout<<"多项式长度："<<endl;
                cin>>p.len;
                p.val=new double[p.len];
                cout<<"请输入："<<endl;
                double dtmp;
                for(int i=0;i<p.len;++i)
                {
                        cin>>dtmp;
                        p.val[p.len-1-i]=dtmp;
                }
                list.push_back(p);
                cout<<"输入成功，是否继续输入（y/n）";
                char next;
                cin>>next;
                while(next!='y' && next !='n')
                {
                        cout<<endl<<"指令错误，请重新输入（y/n）：";
                        cin>>next;
                }
                if(next=='n')
                        break;
        }
}
