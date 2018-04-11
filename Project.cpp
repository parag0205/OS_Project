#include<stdio.h>
int main()
{
	int hp[20],mp[20],lp[20],bt[20],pr[20],rt[20],at[20],p[20],wt[20],tat[20],total=0,pos,temp,j,time,wait_time,remain,flag=0,time_quantum=4,i,n;
	
	printf("Enter the number of process(less than 20) : \n");
	scanf("%d",&n);
	
	printf("Enter Burst Time and Priority of the process.\n");
	for(i=0;i<n;i++)
	{
		printf("\nP[%d]\n",i+1);
		printf("Enter Burst Time :");
		scanf("%d",&bt[i]);
		printf("Enter Priority :");
		scanf("%d",&pr[i]);
		printf("Enter Arrival Time :");
		scanf("%d",&at[i]);
		p[i]=i+1;
	}
	
	wt[0]=0;
	
	printf("\nProcess\t       Burst Time       \tWaiting Time\tTurnaround Time");
	
	//range for highest priority 1-5,medium priority 5-10 and lowest priority with above 10
	
	for(i=0;i<n;i++)
	{
		if(pr[i]<6) //for round robin
		{
			remain=n;
			rt[i]=bt[i];
			
			for(time=0,i=0;remain!=0;)
			{
				if(rt[i]<=time_quantum && rt[i]>0)
				{
					time+=rt[i];
					rt[i]=0;
					flag=1;
				}
				else if(rt[i]>0)
				{
					rt[i]-=time_quantum;
					time+=time_quantum;
				}
				if(rt[i]==0 && flag==1)
				{
					remain--;
					printf("\nP[%d]\t\t    %d\t\t      %d\t\t\t%d",i+1,bt[i],time-at[i],time-at[i]-bt[i]);
					wait_time+=time-at[i]-bt[i];
					flag=0;
				}
				if(i==n-1)
				{
					i=0;
				}
				else if(at[i+1]<=time)
				{
					i++;
				}
				else
				i=0;
			}		
	
		}
		
		else if(pr[i]>=6&&pr[i]<=10)
		{
			pos=i;
			for(j=i+1;j<n;j++)
			{
				if(pr[j]<pr[pos])
				{
					pos=j;
				}
			}
		
			temp=pr[i];
			pr[i]=pr[pos];
			pr[pos]=temp;
		
			temp=bt[i];
			bt[i]=bt[pos];
			bt[pos]=temp;
				
			temp=p[i];
			p[i]=p[pos];
			p[pos]=temp;
		}
		
		else
		{
			wt[i]=0;
			for(j=0;j<i;j++)
			{
				wt[i]+=bt[j];
			}
		}
	}
	//waiting time for priority scheduling
	for(i=1;i<n;i++)
	{
		wt[i]=0;
		for(j=0;j<i;j++)
		{
			wt[i]+=bt[j];
		}
		
		total+=wt[i];
	}
	//turnaround time for priority scheduling
	total=0;
	
	for(i=0;i<n;i++)
	{
		tat[i]=bt[i]+wt[i];
		total+=tat[i];
		printf("\nP[%d]\t\t    %d\t\t      %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
	}
	
	//waiting time for fcfs scheduling
	for(i=0;i<n;i++)
	{
		wt[i]=0;
		for(j=0;j<i;j++)
		{
			wt[i]+=bt[j];
		}
	}
	
	//turnaround time for fcfs scheduling
	for(i=0;i<n;i++)
	{
		tat[i]=bt[i]+wt[i];
		printf("\nP[%d]\t\t    %d\t\t      %d\t\t\t%d",i+1,bt[i],wt[i],tat[i]);
	}
}
