#include<stdio.h>
#include<memory.h>
#include<stdlib.h>

#define FOR(i,n) for(i=0;i<n;i++)
#define NUM 110

struct employee
{
  int no;
	int size;
	int *lan;
};

struct learner
{
	int employee;
	struct learner *next;
};

struct language
{
	int no;
	struct learner *pt;
};

void initstructs(struct employee *employees,struct language *languages,int n)
{
	int i;
	FOR(i,n)
	{
		
		employees[i].no=i+1;
		employees[i].lan=NULL;
		languages[i].no=i+1;
		languages[i].pt=NULL;
	};
};

int insert(struct employee *employees,struct language *languages,int lang,int ler,int index)
{
	employees[ler].lan[index]=lang-1;

	struct learner *flag=languages[lang-1].pt;
	struct learner *preflag=flag;
	
	while(flag!=NULL)
	{
		preflag=flag;
		flag=flag->next;
	};
	
	if(flag==preflag && flag==NULL)
	{
		if(!(languages[lang-1].pt = (struct learner*)malloc(sizeof(struct learner))))
			{return -1;printf("fff");};
		languages[lang-1].pt->employee=ler;
		languages[lang-1].pt->next=NULL;
	}else
	{
		if(!(preflag->next = (struct learner*)malloc(sizeof(struct learner))))
			return -1;
		flag=preflag->next;
		flag->employee=ler;
		flag->next=NULL;
	};
	return 0;
};

int dsf(struct employee *employees,struct language *languages,int *search_tag,int ler)
{
	int i,j,l,n;
	
	struct learner *ptr;
	if(search_tag[ler]==0)
		search_tag[ler]=1;
	else
		return 0;

	n = employees[ler].size;
	FOR(i,n)
	{
		l=employees[ler].lan[i];
		ptr=languages[l].pt;
		while(ptr!=NULL)
		{
			dsf(employees,languages,search_tag,ptr->employee);
			ptr=ptr->next;
		};
	};

	return 0;
};

int main()
{
	int n,m;
	int i,j,l,data,zeronum;
	struct employee *employees = (struct employee*)malloc(NUM*sizeof(struct employee));
	struct language *languages = (struct language*)malloc(NUM*sizeof(struct language));
	int search_tag[NUM];

	while(~scanf("%d%d",&n,&m))
	{
		initstructs(employees,languages,n);
		zeronum=0;
		
		memset(search_tag,0,sizeof(search_tag));
		FOR(i,n)
		{
			scanf("%d",&j);
			if(!(employees[i].lan = (int *)malloc((j+1)*sizeof(int))))
				printf("memory alloc failed\n");
			employees[i].size=j;
			if(j==0)
				zeronum++;
			FOR(l,j)
			{
				scanf("%d",&data);
				insert(employees,languages,data,i,l);
			}
		};

		l=0;
		FOR(i,n)
		{
			if(search_tag[i]==0)
			{
				l++;
				dsf(employees,languages,search_tag,i);
			};
		};
		
		if(zeronum==n)
			l++;
		printf("%d\n",l-1);
	};

	return 0;
}
