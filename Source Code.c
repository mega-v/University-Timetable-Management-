#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

void input(int);
void allotlab(int,int);
void allotperiod(int,int);
void staff_time_tabel(int);
int find_index(int,int,int);

struct inputx
{
    int number_of_subject;
    int number_of_theory;
    int number_of_lab;
    char semester[25];
    char subject[200][100];
    char staff[200][100];
    char labarr[10][25];
    int frequency[200];
    char timetable[5][8][100];
    
}x[100];

struct staff{
	char staff_timetable[5][8][100];
}s[100];

struct lab{
	char lab_timetable[5][8][100];
}l[100];

struct stafflist{
	int count;
	char staffarr[10][25];
}sl;

void input(int noc)
{
    int i,j,periods,labs;
    
    for(j=0;j<noc;j++)
    {   
        printf("    * *  *           *      * * *     * * *         * * *    *  * *   * * * *     *       * * * *  *        * * * \n ");
        printf("  *     *          * *    *         *              *    *   *           *       * *         *     *       *      \n  ");
        printf(" *     *         * * *    * * *     * * *         *     *  *  * *      *      * * *        *     *        * * * \n  ");
        printf(" *     *        *     *        *         *        *    *   *           *     *     *       *     *             * \n  ");
        printf("  * *  * * * * *       *  * * *     * * *         * * *    *  * *      *    *       *   * * * *  * * * *  * * *  \n");
        
        printf("Enter number of subjects: ");  
        scanf("%d",&x[j].number_of_subject);
        printf("Enter number of theory classes: ");
        scanf("%d",&x[j].number_of_theory);
        printf("Enter number of lab sections: ");
        scanf("%d",&x[j].number_of_lab);
        
        for(i=0;i<x[j].number_of_subject;i++)
        { 
             
            if(i<x[j].number_of_theory)
            {
                printf("Enter theory subject %d: ",i+1);
                scanf("%s",x[j].subject[i]);
            }
            else
            {
                printf("Enter lab subject %d : ",i-x[j].number_of_theory+1);
                scanf("%s",x[j].subject[i]);
                printf("Enter lab name : ");
                scanf("%s",x[j].labarr[i-x[j].number_of_theory]);
            }
            printf("Enter faculty for %s: ",x[j].subject[i]);
            scanf("%s",x[j].staff[i]);
        }
        periods=0;
        printf("Enter number of periods per weeks\n");
        for(i=0;i<x[j].number_of_subject;i++)
        {
            printf("Enter number of period for %s: ",x[j].subject[i]);
            scanf("%d:",&x[j].frequency[i]);
            periods=periods+x[j].frequency[i];
        }
        if(periods>30){
        	printf("Sorry we can't assign timetable.Give another input for assign timetable\n");
            input(noc);
		}
    }
}

void allotlab(int n,int h)
{
    int day,period,i,j;
    int flag=0,count=0;
    char string[11][25]={"1-CSE-A","1-CSE-B","2-CSE-A","2-CSE-B","3-CSE-A","3-CSE-B","4-CSE-A","4-CSE-B",};
    
    day=rand()%5;
    period=rand()%6;
    
    for(i=0;i<6;i++)
    {
            if(strcmp(x[h].timetable[day][i],x[h].subject[n])==0)
            {
                count+=1;
                break;
            }
    }
    if(period==4)
	{
        if((strlen(x[h].timetable[day][period])==0) && (strlen(x[h].timetable[day][period+1])==0))
        { 
            if(h%2==0){
                if(count!=0)
                {
                    allotlab(n,h);
                }
                else
                {
                    strcpy(x[h].timetable[day][period],x[h].subject[n]);
                    strcpy(x[h].timetable[day][period+1],x[h].subject[n]);
                    if(n==x[h].number_of_theory){
                    	strcpy(l[h].lab_timetable[day][period],string[h]);
                        strcpy(l[h].lab_timetable[day][period+1],string[h]);
					}
					else if(n==x[h].number_of_theory+1){
						strcpy(l[h+1].lab_timetable[day][period],string[h]);
                        strcpy(l[h+1].lab_timetable[day][period+1],string[h]);
					}
                } 
            }
            else{
            	if((strcmp(x[h].staff[n],x[h-1].staff[n])==0) || (strcmp(x[h].subject[n],x[h-1].subject[n])==0)){
            		for(i=0;i<3;i++){
            			if(strcmp(x[h].subject[n],x[h-1].timetable[day][period-1+i])==0){
            				flag=flag+1;
						}
					}
				}
				else{
					strcpy(x[h].timetable[day][period],x[h].subject[n]);
                    strcpy(x[h].timetable[day][period+1],x[h].subject[n]);	
                    if(n==x[h].number_of_theory){
                    	strcpy(l[h-1].lab_timetable[day][period],string[h]);
                        strcpy(l[h-1].lab_timetable[day][period+1],string[h]);
					}
					else if(n==x[h].number_of_theory+1){
						strcpy(l[h].lab_timetable[day][period],string[h]);
                        strcpy(l[h].lab_timetable[day][period+1],string[h]);
					}
				}
            	if(flag!=0){
            		allotlab(n,h);
				}
				else{
					strcpy(x[h].timetable[day][period],x[h].subject[n]);
                    strcpy(x[h].timetable[day][period+1],x[h].subject[n]);	
                    if(n==x[h].number_of_theory){
                    	strcpy(l[h-1].lab_timetable[day][period],string[h]);
                        strcpy(l[h-1].lab_timetable[day][period+1],string[h]);
					}
					else if(n==x[h].number_of_theory+1){
						strcpy(l[h].lab_timetable[day][period],string[h]);
                        strcpy(l[h].lab_timetable[day][period+1],string[h]);
					}
				}
			}
       }
        else
        {
            allotlab(n,h);
        }
    }
    else
    {
        allotlab(n,h);
    }
}

void allotperiod(int n,int h)
{
    int day,period,i,j,k=1;
    int flag=0,iflag=0,count=0;
    
    day=rand()%5;
    period=rand()%6;
    
    if(strlen(x[h].timetable[day][period])==0)
    {    		
		for(i=0;i<6;i++)
        {
            if(strcmp(x[h].timetable[day][i],x[h].subject[n])==0)
            {
                flag+=1;
                break;
            }
        }
        if(flag!=0)
        {
            allotperiod(n,h);
        }
        else{
            if(h%2==0){

            strcpy(x[h].timetable[day][period],x[h].subject[n]);
            }
            
            else{
                if(strcmp(x[h].subject[n],x[h-1].timetable[day][period])==0 && strcmp(x[h].staff[n],x[h-1].staff[n])==0)
                {
                	if(period==0)
		            {  
		                for(i=2;i<6;i++){
		                	if(strlen(x[h].timetable[day][period])==0)
		                	{
		                		strcpy(x[h].timetable[day][i],x[h].subject[n]);
		                		break;
							}
						}
					}
					else if(period==5)
		            {  
		                for(i=0;i<4;i++){
		                	if(strlen(x[h].timetable[day][period])==0)
		                	{
		                		strcpy(x[h].timetable[day][i],x[h].subject[n]);
		                		break;
							}
						}
					}
					else if(period==1)
		            {  
		                for(i=3;i<6;i++){
		                	if(strlen(x[h].timetable[day][period])==0)
		                	{
		                		strcpy(x[h].timetable[day][i],x[h].subject[n]);
		                		break;
							}
						}
					}
	
					else if(period==4)
		            {  
		                for(i=0;i<3;i++){
		                	if(strlen(x[h].timetable[day][period])==0)
		                	{
		                		strcpy(x[h].timetable[day][i],x[h].subject[n]);
		                		break;
							}
						}
					}
					else
                    {
                        allotperiod(n,h);
                    }
                }
                else{
                	
                	if(period==0)
		            {  
		                if(strcmp(x[h-1].timetable[day][period+1],x[h].subject[n])==0)
                        {
                           iflag+=1;
                        }  
		            }
		            if(period==5)
		            {
		               if(strcmp(x[h-1].timetable[day][period-1],x[h].subject[n])==0)
                       {
                           iflag+=1;
                       }
		            }
		            if(period==1 || period==2 || period==3 || period==4)
		            { 
                        if((strcmp(x[h-1].timetable[day][period-1],x[h].subject[n])==0) || (strcmp(x[h-1].timetable[day][period+1],x[h].subject[n])==0)) 
                        {
                            iflag+=1;
                        }  
		            }
		            if(iflag==0){
		            	strcpy(x[h].timetable[day][period],x[h].subject[n]);
		            }
		            else{
		            	allotperiod(n,h);
					}
                	
				}
		    }
	    }				
    }
    else
    {
        allotperiod(n,h);
    }
}

void staff_time_tabel(int noc){
	int i,j,k,l,count,index;
	char string[11][25]={"1-CSE-A","1-CSE-B","2-CSE-A","2-CSE-B","3-CSE-A","3-CSE-B","4-CSE-A","4-CSE-B",};
	
	count=0;
    for(k=0;k<noc;k++){
   	    for(j=0;j<x[k].number_of_subject;j++){
   	        strcpy(sl.staffarr[count],x[k].staff[j]);
   	        count++;
   	    }
    }

    for(i=0;i<count;i++){
    	for(j=i+1;j<count;j++){
    		if(strcmp(sl.staffarr[i],sl.staffarr[j])==0){
    			for(k=j;k<count-1;k++){
    				strcpy(sl.staffarr[k],sl.staffarr[k+1]);
				}
				count--;
				j--;
			}
		}
	}
	
    sl.count=count;
    
	for(l=0;l<count;l++){
		for(k=0;k<noc;k++)
        {
            for(i=0;i<5;i++)
            {
                for(j=0;j<6;j++)
                {
                	index=find_index(k,i,j);
                    if(strcmp(sl.staffarr[l],x[k].staff[index])==0){
                    	strcpy(s[l].staff_timetable[i][j],string[k]);
					}
               }
           }
       }
	}	
}

int find_index(int class, int day,int period){
	int i,j,k,index;
	
	index=0;
	for(i=0;i<x[class].number_of_subject;i++){
		if(strlen(x[class].timetable[day][period])!=0){
		    if(strcmp(x[class].timetable[day][period],x[class].subject[i])==0){
			    return i;
		    }
		}
	}
}

int main()
{ 
    int number_of_class,number_of_days,number_of_periods;
    int i,j,k,days,periods,count;
    char arr[][81]={"Project","Mentor","Library"};
    char string[11][25]={"1-CSE-A","1-CSE-B","2-CSE-A","2-CSE-B","3-CSE-A","3-CSE-B","4-CSE-A","4-CSE-B",};
    
    FILE *fptr;
	char filename[]="project.txt";
	fptr=fopen("output.txt","w");
	if(fptr==NULL){
		printf("Error in opening File\n");
	} 
	else{
		
        printf("Enter number of Sections : ");
        scanf("%d",&number_of_class);
        printf("Enter number of Days : ");
        scanf("%d",&days);
		printf("Enter number of Periodss : ");
        scanf("%d",&periods);
        
        input(number_of_class);
    
        srand(time(NULL));
    
        for(k=0;k<number_of_class;k++)
        {
            for(i=x[k].number_of_theory;i<x[k].number_of_subject;i++)
            {
                for(j=0;j<x[k].frequency[i];j++)
                { 
                    allotlab(i,k);
                }
            }
        }
    
        for(k=0;k<number_of_class;k++)
        {
            for(i=0;i<x[k].number_of_theory;i++)
            {
                for(j=0;j<x[k].frequency[i];j++)
                {
                    allotperiod(i,k);
                }
            }
        }
    
        staff_time_tabel(number_of_class);
    
        for(k=0;k<number_of_class;k++)
        {
            count=0;
		    for(i=0;i<5;i++)
            {
               for(j=0;j<6;j++)
               {
                    if(strlen(x[k].timetable[i][j])==0){
               	        strcpy(x[k].timetable[i][j],arr[count]);
               	        count++;
			        }
                }
            }
        }   
	
        for(k=0;k<number_of_class;k++)
        {
            fprintf(fptr,"-----------------------------------------------------------\n");
            fprintf(fptr,"                    %s Class Timetable                 \n",string[k]);
            fprintf(fptr,"-----------------------------------------------------------\n");
            
            for(i=0;i<5;i++)
            { 
               for(j=0;j<6;j++)
               {
                   fprintf(fptr,"%-10s",x[k].timetable[i][j]);
               }
            fprintf(fptr,"\n");
            }
        }
        
        for(k=0;k<number_of_class;k++){

        	fprintf(fptr,"-----------------------------------------------------------\n");
            fprintf(fptr,"                    %s Lab Timetable                 \n",x[k].labarr[k%2]);
            fprintf(fptr,"-----------------------------------------------------------\n");
            
            for(i=0;i<5;i++)
            { 
               for(j=0;j<6;j++)
               {
                   fprintf(fptr,"%-10s",l[k].lab_timetable[i][j]);
               }
            fprintf(fptr,"\n");
            }
		}
    
        for(k=0;k<sl.count;k++){
    	    fprintf(fptr,"-----------------------------------------------------------\n");
    	    fprintf(fptr,"                 Staff %s's Timetable           \n",sl.staffarr[k]);
    	    fprintf(fptr,"-----------------------------------------------------------\n");
            for(i=0;i<5;i++)
            {
               for(j=0;j<6;j++)
               {
                   fprintf(fptr,"%-10s",s[k].staff_timetable[i][j]);
               }
            fprintf(fptr,"\n");  
            }
	    }
    }
}
