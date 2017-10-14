/**
Big Number Division

Write a C++ Program to know if Division is possible of two BigNum or not
**/

#include <iostream>
#include <string> 

using namespace std;

struct node
{
	int num;
	struct node *next;
};
typedef struct node *NODEPTR;

NODEPTR head1=NULL;
NODEPTR head2=NULL;
NODEPTR head3=NULL;

struct node* node_creation()
{
	struct node *p;
	p=(NODEPTR)malloc(sizeof(struct node));
	return p;
}

void enter_elements(struct node *temp, int n)
{
	struct node *p;
	p=node_creation();
	p->num=n;
	p->next=NULL;
		
	if(temp->next==NULL)
	{
		temp->next=p;
	}
	else
	{
		while(temp->next != NULL)
		{	
			temp=temp->next;
		}
	temp->next=p;
	}
}

void display(struct node *temp)
{
	struct node *n;
	n = temp->next;
	
	if(n==NULL)
	{}
	else
	{
		while(n != NULL)
		{	
			cout<<n->num;
			n=n->next;
		}
	}
}

int count_nodes(struct node *temp)
{
	int count = 0;
	struct node *n, *t;
	
	t = temp->next;

	if(t->num == 0)
	{
		while(t->next != NULL)
		{
			if(t->num != 0)
			{break;}
			else
			{delete(t);}
			t = t->next;
		}
		temp->next=t;
	}
	n = temp->next;
	while(n != NULL)
	{	
		
		count = count+1;
		n=n->next;
	}
	return count;
}

void reverse(struct node *temp)
{
	struct node *previous = NULL;
	struct node *current = temp->next;
	struct node *forward;
	
	while(current !=NULL)
	{
		forward = current->next;
		current->next = previous;
		previous = current;
		current = forward;
	}
	temp->next = previous;
}

void delete_ll(struct node *temp)
{
	struct node *t, *n;
	t=temp->next;
	
	while(t != NULL)
	{
		delete(t);
		t = t->next;
	}
	
	temp->next=NULL;
}



string removeZero(string str)
{
	int i = 0;
	while (str[i] == '0')
	{i++;}

	str.erase(0, i);

	return str;
}

int get_bigger_list(struct node *temp1, struct node *temp2)
{
	struct node *n1, *n2;
	int nodes_list1 = count_nodes(temp1);
	int nodes_list2 = count_nodes(temp2);

	if(nodes_list1 > nodes_list2)
	{
		return 1;
	}
	else if(nodes_list1 < nodes_list2)
	{
		cout << "CANNOT BE DIVIDED" << endl;
		exit(0);
	}
	else
	{
		n1=temp1->next;
		n2=temp2->next;
		
		while(n1 != NULL && n2 !=NULL)
		{
			if (n1->num > n2->num)
			{
				return 1;
			}
			else if (n1->num < n2->num)
			{
				cout << "CANNOT BE DIVIDED" << endl;
				exit(0);
			}
			else 
			{
				n1=n1->next; n2=n2->next;
			}
		}
		cout << "BOTH CAN BE DIVIDED" << endl;
		exit(0);
	}	
}

void copylist(struct node *temp3)
{
	struct node *list3, *list1;
	delete_ll(head1);

	list3 = temp3->next;

	while (list3 != NULL)
	{
		int num = list3->num;
		enter_elements(head1, num);
		list3 = list3->next;
	}
	
	delete_ll(head3);
}

void minus_two(struct node *temp1, struct node *temp2)
{
	int bigger = get_bigger_list(temp1, temp2);

	if(bigger == 1)
	{
		reverse(temp1);
		reverse(temp2);
		struct node *list1, *list2, *t;
		list1 = temp1->next;
		list2 = temp2->next;
		int num;
	
		while (list2 != NULL)
		{
			if (list1->num < list2->num)
			{
				list1->num = list1->num + 10;
				t=list1->next;
				if(t->num == 0)
				{
					while(t->next != NULL)
					{
						if(t->num != 0)
						{break;}
						else
						{t->num = 9;}
						t = t->next;
					}
					t->num = t->num - 1;
				}
				else
				list1->next->num = list1->next->num - 1;
				num = list1->num - list2->num;
				enter_elements(head3, num);
			}
			else
			{
				num = list1->num - list2->num;
				enter_elements(head3, num);	
			}
			list2=list2->next;
			list1=list1->next;
		}

		while (list1 != NULL)
		{
			num = list1->num;
			enter_elements(head3, num);
			list1=list1->next; 
		}
	}
	
	reverse(head1);
	reverse(head2);
	reverse(head3);
	count_nodes(head3);
	//display(head1);	cout << " - "; display(head2);cout << "= ";display(head3);
	//cout << "\n";	
	copylist(head3);
}

int main()
{
head1 = (NODEPTR)malloc(sizeof(struct node));
head2 = (NODEPTR)malloc(sizeof(struct node));
head3 = (NODEPTR)malloc(sizeof(struct node));

string str1, str2;

cout<<"Enter Numerator: ";
cin>>str1;

cout<<"Enter Denominator: ";
cin>>str2;

str1 = removeZero(str1);
str2 = removeZero(str2);

for(char& c : str1) 
{
	int i = c - '0';
	enter_elements(head1, i);
}

for(char& c : str2) {
	int i = c - '0';
	enter_elements(head2, i);
}

while(1)
{
	minus_two(head1, head2);
}

return 0;
}
