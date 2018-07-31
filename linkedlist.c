#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	struct node* next;
}node;

node* createNewNode()
{
	node* nn = (node*)malloc(sizeof(node));
	return nn;
}
void addAtBeg(node **h, int d)
{
	node *nn = createNewNode();
	nn->data = d;
	nn->next = *h;
	*h = nn;
}
void addAtLast(node **h, char d)
{
	node *nn = createNewNode();
	nn->data = d;
	nn->next=NULL;
	if(*h==NULL)
	{
		*h=nn;
	}
	else
	{
		node *curr = *h;
		while(curr->next)
		{
			curr=curr->next;
		}
		curr->next=nn;
	}	
}
void addAtPosition(node **h,int d, int pos)
{
	if(pos==1)
	{
		addAtBeg(h,d);
	}
	else
	{
		node *curr=*h;
		int p=1;
		while(p<pos-1&&curr)
		{
			curr=curr->next;
			p++;	
		}
		if(curr==NULL)
		{
			printf("Position does not exist\n");
		}
		else
		{
			node *nn = createNewNode();
			nn->next = curr->next;
			curr->next = nn;
		}
	}
}

int deleteAtBeg(node **h)
{
	int data;
	if(*h==NULL)
		return -1;
	else
	{
		node *temp = *h;
		*h = (*h)->next;
		data = temp->data;
		free(temp);
		temp=NULL;	
	}
	return data;	 
}
char deleteAtLast(node **h)
{
	char data;
	node *temp;
	if(*h==NULL)
		return 0;
	else if((*h)->next==NULL)
	{
		deleteAtBeg(h);
	}
	else
	{
		node *curr = *h;
		while(curr&&curr->next&&curr->next->next)
		{
			curr = curr->next;
		}
		if(curr==NULL) {
			printf("Position doesnot exist\n");
		}
		else {
			temp = curr->next;
			data = temp->data;
			curr->next = NULL;
			free(temp);
			temp = NULL;
		}
	}
	return data;
}

void push(node **h, int d)
{
	addAtBeg(h, d);
}

char pop(node **h)
{
	return deleteAtBeg(h);
}

char peek(node **h)
{
	return (*h)->data;
}
int isEmpty(node **h)
{
	return !h;
}
int balanced(node **h, char *str, int len)
{
	int i=0,j=0;
	char open[] = {'{','[','<','('};
	char close[] = {'}',']','>', ')'};
	while(i<len) {
		j=0;
		while(j<4) {
			if(str[i]==close[j]) {
				break;
			}
			j++;		
		}
		if(j!=4&&peek(h)==open[j]) {
			pop(h);	
		}
		else {
			push(h, str[i]);
		}
		i++;
	}
	if(pop(h)==0)
		return 1;
	else
		return 0;
}

node* middle(node **h)
{
	if(*h==NULL)
		return NULL;
	else
	{
		node *fastptr = *h;
		node *slowptr = *h;
		while(fastptr&&fastptr->next)
		{
			fastptr = fastptr->next->next;
			slowptr = slowptr->next;
		}
		return slowptr;
	}
}

int circularList(node **h)
{
	node *fastptr = *h;
	node *slowptr = *h;
	if(fastptr->next){
		fastptr = fastptr->next->next;
		slowptr = slowptr->next;
	}
	while(fastptr&&fastptr->next&&(fastptr->next!=slowptr->next))
	{
		fastptr = fastptr->next->next;
		slowptr = slowptr->next;
	}
	if(fastptr==NULL||fastptr->next==NULL)
		return 0;
	else
		return 1;
}
void print(node *h)
{
	if(h==NULL) {}
	else {
		node *curr = h;
		while(curr)
		{
			printf("%d\n", curr->data);
			curr=curr->next;	
		}	
	}
}
void reverse(node **h, node **newList)
{
	node *curr = *h;
	if(curr->next==NULL)
	{
//		printf("%d\n", curr->data);
		addAtBeg(newList, curr->data);
	}
	else
	{
		addAtBeg(newList, curr->data);
		curr = curr->next;
		reverse(&curr, newList);
//		printf("%d\n", curr->data);
	}
}

int checkPalindrome(node **h)
{
	node *h2 = NULL;
	reverse(h, &h2);
	node *curr = *h;
	node *reverseList = h2;
	while(curr->next)
	{
		if(curr->data!=reverseList->data)
			break;
		curr = curr->next;
		reverseList = reverseList->next;
	}
	if(curr->next==NULL)
		return 1;
	else
		return 0;
}

node* specifyNext(node **h, int d, node *add)
{
	node *nn = createNewNode();
	nn->data = d;
	nn->next = add;
	node *curr = *h;
	while(curr->next)
	{
		curr=curr->next;
	}
	curr->next=nn;
	return nn;
}


int main()
{
	node *head = NULL;
	addAtBeg(&head, 10);
	node *Add = specifyNext(&head, 20, NULL);
	specifyNext(&head, 30, NULL);
	specifyNext(&head, 40, NULL);
	specifyNext(&head, 50, Add);
//	print(head);
//	node *newList = NULL;
//	reverse(&head, &newList);
//	print(newList);
//	printf("%d\n", checkPalindrome(&head));
//	printf("%d\n", middle(&head));
	printf("%d\n", circularList(&head));
	return 0;

}
