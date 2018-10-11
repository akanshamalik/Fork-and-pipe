/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/
#include<stdio.h>

void Clock(int reference_string[],int frames)
{
int n,f[10],ava,hit=0,usebit[10],i,j;

for(i=0;i<10;i++)
{
ava=0;
// found
for(j=0;j<frames;j++)
{
if(reference_string[i]==f[j])
{
ava=1;
hit++;
usebit[j]=1;
break;
}
}
//search for usebit 0
if(ava==0)
{
for(j=0;j<frames;j++)
{
if(usebit[j]==0)
{
f[j]=reference_string[i];
usebit[j]=1;
ava=1;
break;
}
}
}
  
if(ava==0)
{
for(j=0;j<frames;j++)
usebit[j]=0;
}
f[0]=reference_string[i];
usebit[0]=1;
}
printf("\nClock:The number of PageFault: %d",10-hit);
printf("\nClock PageFault in %%=%d",((10-hit)/10)*100);

}

void Optimal(int reference_string[],int frames)
{
int Frames[10],temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
for(i = 0; i < frames; ++i)
{
Frames[i] = -1;
}
  
for(i = 0; i <10; ++i){
flag1 = flag2 = 0;
  
for(j = 0; j <frames; ++j){
if(Frames[j] == reference_string[i]){
flag1 = flag2 = 1;
break;
}
}
  
if(flag1 == 0){
for(j = 0; j < frames; ++j){
if(Frames[j] == -1){
faults++;
Frames[j] = reference_string[i];
flag2 = 1;
break;
}
}   
}
  
if(flag2 == 0){
flag3 =0;
  
for(j = 0; j < frames; ++j){
temp[j] = -1;
  
for(k = i + 1; k <10; ++k){
if(Frames[j] ==reference_string[k]){
temp[j] = k;
break;
}
}
}
  
for(j = 0; j <frames; ++j){
if(temp[j] == -1){
pos = j;
flag3 = 1;
break;
}
}
  
if(flag3 ==0){
max = temp[0];
pos = 0;
  
for(j = 1; j < frames; ++j){
if(temp[j] > max){
max = temp[j];
pos = j;
}
}   
}
  
Frames[pos] = reference_string[i];
faults++;
}

  
}
  
printf("\n Optimsl: Total Page Faults = %d", faults);
printf("\n Optimsl: Total Page Faults in%% =%d", (faults/10)*100);
  
  
}
void FIFO(int reference_string[],int frames)
{
int page_faults = 0, m, n, s, pages;
  
int temp[frames];
for(m = 0; m < frames; m++)
{
temp[m] = -1;
}
for(m = 0; m <10; m++)
{
s = 0;
for(n = 0; n < frames; n++)
{
if(reference_string[m] == temp[n])
{
s++;
page_faults--;
}
}
page_faults++;
if((page_faults <= frames) && (s == 0))
{
temp[m] = reference_string[m];
}
else if(s == 0)
{
temp[(page_faults - 1) % frames] = reference_string[m];
}

  
}
printf("\nFIFO Total Page Faults:\t%d\n", page_faults);
printf("\nFIFO Total Page Faults in %%=%d",(page_faults/10)*100);
}


void LRU(int reference_String[],int frame)
{
int q[20],c=0,i,j,k=0,n,r,t,b[20],c2[20],c1,d;

q[k]=reference_String[k];
c++;
k++;
for(i=1;i<10;i++)
{
c1=0;
for(j=0;j<frame;j++)
{
if(reference_String[i]!=q[j])
c1++;
}
if(c1==frame)
{
c++;
if(k<frame)
{
q[k]=reference_String[i];
k++;
}
else
{
for(r=0;r<frame;r++)
{
c2[r]=0;
for(j=i-1;j<n;j--)
{
if(q[r]!=reference_String[j])
c2[r]++;
else
break;
}
}
for(r=0;r<frame;r++)
b[r]=c2[r];
for(r=0;r<frame;r++)
{
for(j=r;j<frame;j++)
{
if(b[r]<b[j])
{
t=b[r];
b[r]=b[j];
b[j]=t;
}
}
}
  
}
}
}
printf("\nThe no LRU of page faults is %d",c);
printf("\nThe no LRU of page faults in %% =%d",((c/10)*100));

}


void main()
{
int n ,reference_string[10],frame,i;
printf("Enter no of pages:");
scanf("%d",&n);
printf("Enter the reference string:");
for(i=0;i<n;i++)
scanf("%d",&reference_string[i]);
printf("Enter no of frames:");
scanf("%d",&frame);
LRU(reference_string,frame);
FIFO(reference_string,frame);
Optimal(reference_string,frame);
Clock(reference_string,frame);
}

