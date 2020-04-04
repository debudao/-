#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

#define MAXSIZE 1000


typedef struct linkNode
{
	int coefficient;//系数
	int exponent;//指数
	linkNode *next;

}linkNode, *linkList;

void sortL(linkList &l)
{
	linkList s, q;

	if (!l->next)
		return;

	for (s = l->next;s->next;s = s->next)
	{
		for (q = s->next;q;q = q->next)
		{
			if (q->exponent > s->exponent)
			{
				int coe = q->coefficient, ex = q->exponent;
				q->coefficient = s->coefficient;
				q->exponent = s->exponent;
				s->coefficient = coe;
				s->exponent = ex;
			}
		}
	}
}

//删除系数为0的节点
void deleL(linkList &l)
{
	linkList p = l;
	linkList k = p;
	while (p->next)
	{
		
		p = p->next;
		if (p->coefficient == 0)
		{
			k->next = p->next;
		}
		else
			k = k->next;
	}
}

void printL(linkList &l)
{
	linkList p = l;

	if (!p->next)
		cout << 0;
	else
	{
		while (p->next)
		{
			p = p->next;
			if (p->next)
			{
				if (p->next->coefficient > 0)
				{
					if (p->exponent == 0)
						printf("%d+", p->coefficient);
					else 
						printf("%dx^%d+", p->coefficient, p->exponent);
				}
				else
				{
					if (p->exponent == 0)
						printf("%d", p->coefficient);
					else 
						printf("%dx^%d", p->coefficient, p->exponent);
				}
			}
			else
			{
				if (p->exponent == 0)
					printf("%d", p->coefficient);
				else
					printf("%dx^%d", p->coefficient, p->exponent);
			}
			/*if (p->coefficient != 0)
			{
				if (p->next&&p->next->coefficient != 0)
				{
					if (p->exponent == 0)
						printf("%d+", p->coefficient);
					else if (p->next->coefficient > 0)
						printf("%dx^%d+", p->coefficient, p->exponent);
				}
				else
				{
					if (p->exponent == 0)
						printf("%d", p->coefficient);
					else
						printf("%dx^%d", p->coefficient, p->exponent);
				}

			}*/
		}
	}

	
	cout << "\n";
}

//相加
linkList addL(linkList &one, linkList &two)
{
	linkList p1 = one, p2 = two;
	

	while (p1->next)
	{
		bool isExist = false;
		p2 = two;

		p1 = p1->next;
		while (p2->next)
		{
			p2 = p2->next;
			if (p1->exponent == p2->exponent)
			{
				p2->coefficient += p1->coefficient;
				isExist = true;
				break;
			}
		}

		if (!isExist)
		{
			linkList s = new linkNode;
			s->coefficient = p1->coefficient;
			s->exponent = p1->exponent;
			s->next = two->next;
			two->next = s;
		}

	}

	return two;
}

//相减
linkList reduceL(linkList &one, linkList &two)
{
	linkList p1 = two, p2 = one;


	while (p1->next)
	{
		bool isExist = false;
		p2 = one;

		p1 = p1->next;
		while (p2->next)
		{
			p2 = p2->next;
			if (p1->exponent == p2->exponent)
			{
				p2->coefficient -= p1->coefficient;
				isExist = true;
				break;
			}
		}

		if (!isExist)
		{
			linkList s = new linkNode;
			s->coefficient = -p1->coefficient;
			s->exponent = p1->exponent;
			s->next = one->next;
			one->next = s;
		}

	}

	return one;
}

//求导
void derivative(linkList &l)
{
	linkList p = l;
	while (p->next)
	{
		p = p->next;

		if (p->exponent == 0)
			p->coefficient = 0;
		else
		{
			p->coefficient *= p->exponent;
			p->exponent -= 1;
		}
	}

}


//乘法
linkList multL(linkList &one, linkList &two)
{
	linkList p1 = two, p2 = one, res = new linkNode;
	res->next = NULL;

	while (p1->next)
	{
		p1 = p1->next;
		p2 = one;
		while (p2->next)
		{
			p2 = p2->next;
			linkList  r = res;
			int coe, ex;
			bool isExist = false;

			coe = p1->coefficient*p2->coefficient;
			ex = p1->exponent + p2->exponent;

			while (r->next)
			{
				r = r->next;
				if (r->exponent ==ex)
				{
					r->coefficient += coe;
					isExist = true;
					break;
				}
			}

			if (!isExist)
			{
				linkList l = new linkNode;
				l->coefficient = coe;
				l->exponent = ex;
				l->next = res->next;
				res->next = l;
			}

		}
	}

	return res;

}


int main()
{
	int n;
	cin >> n;

	while (n--)
	{
		linkList one = new linkNode, two = new linkNode;
		linkList s1 = one, s2 = two;
		char op;
		int a, b;
		cin >> a >> b;

		for (int i = 0;i < a;i++)
		{
			int a1, a2;
			cin >> a1 >> a2;
			
			linkList p = new linkNode;
			p->coefficient = a1;
			p->exponent = a2;
			p->next = NULL;
			s1->next = p;
			s1 = s1->next;

		}
		

		for (int i = 0;i < b;i++)
		{
			int b1, b2;
			cin >> b1 >> b2;

			linkList p = new linkNode;
			p->coefficient = b1;
			p->exponent = b2;
			p->next = NULL;
			s2->next = p;
			s2 = s2->next;
		}		

		cin >> op;

		if (op == '+')
		{
			linkList res = addL(one, two);
			sortL(res);
			deleL(res);
			printL(res);
		}
		else if (op == '-')
		{

			linkList res = reduceL(one, two);
			sortL(res);
			deleL(res);
			printL(res);
		}
		else if (op == '\'')
		{
			derivative(one);
			sortL(one);
			deleL(one);
			printL(one);
			derivative(two);
			sortL(two);
			deleL(two);
			printL(two);
		}
		else if (op == '*')
		{
			linkList res = multL(one, two);
			deleL(res);
			sortL(res);
			
			printL(res);
		}



	}

	return 0;
}
