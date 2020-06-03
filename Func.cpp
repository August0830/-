#pragma GCC diagnostic error "-std=c++11"
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#include <stack>
#include <sstream>
#include "Calculator.h"
Poly Mod(Poly p, int power)
{
	Poly answ;
	answ.len=power;
	answ.val= new double[answ.len];
	for(int i=0;i<answ.len;++i)
		answ.val[i]=p.val[i];
	return answ;
}
Poly ReverOrder(Poly p)
{
	Poly pr;
	pr.len=p.len;
	pr.val=new double[pr.len];
	for(int i=0;i<pr.len;++i)
		pr.val[i]=p.val[p.len-i-1];
	return pr;
}
void Divis(Poly divid, Poly divisor, Poly &quo, Poly &remain)
{//divid/divisor=quo...remain
	Poly dividr;
	dividr=ReverOrder(divid);
	//PrintSing(dividr);
	Poly divisr=ReverOrder(divisor);
	//PrintSing(divisr);
	Poly divisrv=Rever(divisr);
	//PrintSing(divisrv);
	Poly mul =Mul(divisrv,dividr);//PrintSing(mul);
	Poly quor=Mod(mul,divid.len-divisor.len+1);
	//PrintSing(quor);
	quo=ReverOrder(quor);
	//PrintSing(Mul(quo,divisor));
	remain=Sub(divid,Mul(quo,divisor));
}
Poly Rever(Poly a)
{
	Poly b;
	b.len=a.len;
	b.val=new double[b.len];
	b.val[0]=1/a.val[0];
	for(int k=1;k<a.len;++k)
	{
		b.val[k]=0;
		for(int i=0;i<=k-1;++i)
			b.val[k]+=-b.val[i]*a.val[k-i]/a.val[0];
	}
	return b;
}
double Root(Poly F)
{
	double x0,x1;
	Poly F1=Deriv(F);
	PrintSing(F1);
	x1=1e-10;
	do
	{
		x0=x1;
		if(x0==0)
			x0=1e-10;
		x1=x0-Value(F,x0)/Value(F1,x0);
	}while(Value(F,x1)<-1e-5 || Value(F,x1)>1e-5);
	return x1;
}
/*bool MixedCal(vector<Poly> polylist)
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
}*/
double Inte(Poly p,string range)
{
        double res,lower,higher;
        Range(range,lower,higher);
        Poly orig=IntePoly(p);
        res=Value(orig,higher)-Value(orig,lower);
        return res;
}
void Range(string test, double &lower, double &higher)
{
        string newrange;
        for(int i=0;i<test.length();++i)
        {
                newrange.append(1,test[i]);
                if(i+1<test.length() && (test[i+1]=='.' || (test[i+1]>='0' && test[i+1]<='9')) &&
                (test[i]=='.' || (test[i]>='0' && test[i]<='9')))
                        continue;
                newrange.append(" ");
        }
        //cout<<test<<endl<<newrange<<endl;//test 
        istringstream strm(test);
        char ctmp;
        strm>>ctmp;
        //cout<<"1c"<<ctmp<<" ";
        strm>>ctmp;
        //cout<<"2c"<<ctmp<<" ";
        strm>>lower;strm>>ctmp;strm>>higher;
        //cout<<"lower "<<lower<<" higher "<<higher<<" "<<ctmp;
        strm>>ctmp;
        //cout<<" "<<ctmp<<endl;
}
Poly IntePoly(Poly p)
{
        Poly origp;
        origp.len=p.len+1;
        origp.val=new double[origp.len];
        origp.val[0]=0;
        for(int i=1;i<origp.len;++i)
        {
                origp.val[i]=p.val[i-1]/i;
        }
        return origp;
}
double Value(Poly p, double x0)
{
        double res=0;
        for(int i=0;i<p.len;++i)
        {
                double x=1;
                for(int j=0;j<i;++j)
                {
                        x=x0*x;
                }
                res+=p.val[i]*x;
        }
        return res;
}
bool HeadTail(string infix,vector<Poly> polylist)
{
	bool head=false,tail=false;
	int last=infix.length()-1;
	if(infix[0]=='(' || infix[0]=='$')
		head=true;
	else
	{
		int i=0;
		string name;
		while((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                {
			if(i>last)
				break;
                        name.append(1,infix[i++]);
                }//cout<<"first poly name:"<<name;
		Poly p;
		for(auto &p:polylist)
		{
			if(p.name==name)
				head=true;
		}
	}
	
	if(infix[last]==')' || infix[last]=='!')
                tail=true;
        else
        {
                int i=last;
		string name;
                while((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                {
                        if(i<0)
                                break;
                        name.append(1,infix[i--]);
                }
		int namelen=name.length()-1;
		for(int j=0;j<namelen/2;++j)
			name[j]=name[namelen-j];//reverse;
		//cout<<"last poly name:"<<name;
                Poly p;
                for(auto &p:polylist)
                {
                        if(p.name==name)
                                tail=true;
                }
        }
        return head&&tail;
}
bool AfterPoly(string infix, vector<Poly> polylist)
{
	bool res=true;
	string oper="+-*!)";
	for(int i=0;i<infix.length();++i)
        {
   
                if((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                {
                        string name;      
                        while((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                                name.append(1,infix[i++]);//停在多项式下一个字符
                        Poly p;
			bool exist=false;
			for(auto &p:polylist)
				if(p.name==name)
					exist=true;
			if(!exist)
				return false;
			if(oper.find(infix[i])==oper.npos)
				return false;
                }
	}
	return true;
}
bool AfterPlusMul(string infix, vector<Poly> polylist)
{
	int len=infix.length();
	for(int i=0;i<len;++i)
	{
		if(infix[i]=='+' || infix[i]=='*')
		{
			if(infix[i+1]!='(' || infix[i+1]!='$')
				return false;
			else
			{
				string name;++i;
                        	while((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
                                	name.append(1,infix[i++]);//停在多项式下一个字符
                        	if(name.empty())
					return false;
				Poly p;
                        	bool exist=false;
                        	for(auto &p:polylist)
                                	if(p.name==name)
                                        	exist=true;
                        	if(!exist)
                                	return false;
			}
		}
	}
        return true;
}
bool InteLegal(string infix,vector<Poly> polylist)
{
	int len=infix.length();
	for(int i=0;i<len;++i)
	{
		if(infix[i]=='$')
		{
			if(infix[++i]!='[')
				return false;
			while((infix[i]>='0' && infix[i]<='9')||infix[i]=='.') ++i;
			if(infix[i]!=']')
				return false;
			++i;
			if(infix[i]=='(')
				return true;
			else
			{
				string name;
                        	while(((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z')) && i<len)
                                	name.append(1,infix[i++]);//停在多项式下一个字符
                        	--i;
				if(name.empty())
					return false;
				Poly p;
				bool exist=false;
				for(auto &p:polylist)
				if(p.name==name)
					exist=true;
				if(!exist)
					return false;
			}
		}
	}
        return true;
}
bool DerivLegal(string infix)
{
	int len=infix.length();
	string oper="+-*)";
	for(int i=0;i<len;++i)
	{
		if(infix[i]=='!')
			if(oper.find(infix[i+1])==oper.npos)
				return false;
	}
        return true;
}
bool Junior(string  a,string b)//判断符号优先级a 小于等于 b 是返回true
{
        string oper[5]={"-","+","*","$","!"};
        int aval=-1,bval=-1;
        for(int i=0;i<5;++i)
        {
                if(a[0]==oper[i][0])
                        aval=i;
                if(b[0]==oper[i][0])
                        bval=i;
        }
        if(aval<=bval)
                return true;
        if(aval==1 && bval==0)
                return true;
        return false;
}
Poly Deriv(Poly orig)
{
        Poly der;
        der.len=orig.len-1;
        der.val=new double[der.len];
        for(int i=1;i<orig.len;++i)
        {
                if(orig.val[i]==0)
                        der.val[i-1]=0;
                else
                {
                        der.val[i-1]=i*orig.val[i];
                }
        }
        return der;
}
/*bool ToSuffix(string infix, string &suffix, vector<Poly> polylist)
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
                }//
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
}*/
Poly Mul(Poly p1, Poly p2)
{
        Poly res;
        res.len=(p1.len-1)+(p2.len-1)+1;
//      cout<<res.len<<endl;
        res.val=new double[res.len];
        for(int i=0;i<res.len;++i)
                res.val[i]=0;
        for(int i=0;i<p1.len;++i)
        {
                for(int j=0;j<p2.len;++j)
                        res.val[i+j]+=p1.val[i]*p2.val[j];
        }
        return res;
}
/*void Print(vector<Poly> polylist)
{
        Poly p;
        cout<<"多项式名为：";
        string name;
        cin>>name;
        for(auto &p:polylist)
        {
                if(p.name!=name)
                        continue;
                for(int i=p.len-1;i>-1;--i)
                {
                if(i!=p.len-1 && p.val[i]>0)
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
}*/
void PrintSing(Poly p)
{
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
Poly Add(Poly p1, Poly p2)
{
        Poly res;
        res.len=(p1.len>p2.len)?p1.len:p2.len;
        res.val=new double[res.len];
        for(int i=0;i<p1.len+p2.len-res.len;++i)
        {
                res.val[i]=p1.val[i]+p2.val[i];
        }
        Poly left;
        if(p1.len>p2.len)
                left=p1;
        else
                left=p2;
        for(int i=p1.len+p2.len-res.len;i<res.len;++i)
        {
                res.val[i]=left.val[i];
        }
        return res;
}
Poly Sub(Poly p1, Poly p2)
{
        Poly res;
        res.len=(p1.len>p2.len)?p1.len:p2.len;
        res.val=new double[res.len];
        for(int i=0;i<p1.len+p2.len-res.len;++i)
        {
                res.val[i]=p1.val[i]-p2.val[i];
        }
        Poly left;
        for(int i=p1.len+p2.len-res.len;i<res.len;++i)
        {
                if(p1.len>p2.len)
                        res.val[i]=p1.val[i];//被减多项式最高项更大
                else
                        res.val[i]=-p2.val[i];
        }
        return res;
}
/*void newPoly(vector<Poly> &list)
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
}*/
bool LegalName(string name, vector<Poly> polylist)
{
        char s;
        for(auto &s:name)
        {
                if(!((s>='A'&& s<='Z')||(s>='a' && s<='z')))
                        return false;
        }
	Poly ptmp;
	for(auto &ptmp:polylist)
	{
		if(ptmp.name==name)
			return false;
	}
        return true;
}
Poly CalExpress(string suffix, vector<Poly> polylist)
{
        Poly answ;
        stack<Poly> pst;
        string str;
        istringstream strm(suffix);
        while(strm>>str)
        {
                //cout<<str<<endl;
                if(str[0]=='$')
                {
                        Poly p;
                        p.len=1;
                        p.val=new double[p.len];
			if(pst.empty())
                                break;
                        p.val[0]=Inte(pst.top(),str);
                        pst.pop();
                        pst.push(p);
                }
                else if(str[0]=='!')
                {
                        Poly pder;
			if(pst.empty())
                                break;
                        pder=Deriv(pst.top());
                        pst.pop();
                        pst.push(pder);
                }
                else if(str[0]=='+')
                {
                        Poly pa,pb,plus;
			if(pst.empty())
                                break;
                        pa=pst.top();pst.pop();
			if(pst.empty())
                                break;
                        pb=pst.top();pst.pop();
                        plus=Add(pa,pb);
                        pst.push(plus);
                }
		else if(str[0]=='-')
                {
                        Poly substr,minu;//减数 被减数
			if(pst.empty())
                                break;
                        substr=pst.top();pst.pop();
			if(pst.empty())
                                break;
                        minu=pst.top();pst.pop();
                        Poly psub=Sub(minu,substr);
                        pst.push(psub);
                }
                else if(str[0]=='*')
                {
                        Poly p1,p2;
			if(pst.empty())
                                break;
                        p1=pst.top();pst.pop();
			if(pst.empty())
                                break;
                        p2=pst.top();pst.pop();
                        Poly pmul=Mul(p1,p2);
                        pst.push(pmul);
                }
                else
                {
                        Poly ptmp;
                        for(auto &ptmp:polylist)
                        {
                                if(ptmp.name==str)
                                        pst.push(ptmp);
                        }
                }
        }
	if(!pst.empty())
        {
		answ=pst.top();
		pst.pop();
	}
	else
		answ.name="表达式错误，是否重新输入(y/n): ";
	if(!pst.empty())
	{
		answ.name="表达式错误，是否重新输入(y/n): ";
		delete answ.val;
	}
        return answ;
}

