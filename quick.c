#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include<time.h>

int x[10000];
int i1,j,check=1,size;
int usf[1000],usl[1000];
clock_t start, end;
double time_spent;
#define NOT 2
//pthread_barrier_t barrier;
//pthread_barrier_init (&barrier, NULL, 2);


//void quicksort(int [10],int,int);
int partition(int a[], int p, int r);

pthread_mutex_t lock,lock1,lock2,lock3,lock4;

typedef struct
{ 
 int x;
 int counter;
}t_data;

void *init1 (void*arg)
{
  int id,c;
  t_data *t=(t_data*)arg;
  id=t->x;
  c=t->counter;
  c=0;
  printf("\nentering thread %d\n",id); 
  int f,i,l,r,c1,c2,c3,c4,c5,c6; 
  //usleep(200);
  //pthread_barrier_wait (&barrier);
  while(check){
   printf("entered the first loop in thread 1\n");
   pthread_mutex_lock(&lock1);
   c1=i1;
   c2=j;
   pthread_mutex_unlock(&lock1);
  //while(check==1){
  
   while(c1>=0 && c2>=0){
    pthread_mutex_lock(&lock2);
    f=usf[c1];l=usl[c2];i1=--c1;j=--c2;
    if((i1==-1)&&(usf[i1]>=usl[j]))
      check=0;
    pthread_mutex_unlock(&lock2);
  // printf("ft%d= %d , lt%d= %d \n ",id,f,id,l);
  // printf("i1t%d= %d , jt%d= %d \n ",id,i1,id,j);
    if(f<l){
    //printf("\nft%d and lt%d = %d %d",id,id,f,l);
    r=partition(x,f,l);
    c++;
   // printf("returned value : %d\n",r);
   // printf("Sorted elements:\n ");
   // for(i=0;i<size;i++)
   // printf(" %d\n",x[i]);
    pthread_mutex_lock(&lock3);
    c1=++i1;c2=++j;
    usf[i1]=f;usl[j]=r-1;
    c1=++i1;c2=++j;
    usf[i1]=r+1;usl[j]=l;

   // printf("i1t%d= %d , jt%d= %d \n ",id,i1,id,j);
   // printf("usf%d:\n ",id);
   // for(i=0;i<=i1;i++)
   // printf(" %d\n",usf[i]);
   // printf("usl%d:\n ",id);
   // for(i=0;i<=j;i++)
   // printf(" %d\n",usl[i]);
    pthread_mutex_unlock(&lock3);
    
   //if(usf[i1]>=usl[j] && usf[i1-1]>=usl[j-1])
    }

   }
  
 }
 printf("iteration of %d thread is %d",id,c); 
   
}

   
void *init2 (void*arg)
{
  int id,c;
  t_data *k=(t_data*)arg;
  id=k->x;
  c=k->counter;
  c=0;
  printf("\nentering thread %d\n",id);
  int f,i,l,r,c1,c2,c3,c4,c5,c6;
  usleep(200);
  printf("the value of check in thread 2 : %d\n",check);
  //pthread_barrier_wait (&barrier);
  while(check){
   printf("\nentering thread %d\n",id);
   pthread_mutex_lock(&lock1);
   c1=i1;
   c2=j;
  pthread_mutex_unlock(&lock1);
  printf("c1 and c2 =%d %d\n",c1,c2);
 // while(check==1){

   while(c1>=0 && c2>=0){
    pthread_mutex_lock(&lock2);
    f=usf[c1];l=usl[c2];i1=--c1;j=--c2;
    if((i1==-1)&&(usf[i1]>=usl[j]))
      check=0;
   pthread_mutex_unlock(&lock2);
   //printf("ft%d= %d , lt%d= %d \n ",id,f,id,l);
   //printf("i1t%d= %d , jt%d= %d \n ",id,i1,id,j);
    if(f<l){
    //printf("\nft%d and lt%d = %d %d",id,id,f,l);
    r=partition(x,f,l);
    c++;
    //printf("returned value : %d\n",r);
    //printf("Sorted elements:\n ");
    //for(i=0;i<size;i++)
    //printf(" %d\n",x[i]);
    pthread_mutex_lock(&lock3);
    c1=++i1;c2=++j;
    usf[i1]=f;usl[j]=r-1;
    c1=++i1;c2=++j;
    usf[i1]=r+1;usl[j]=l;

   // printf("i1t%d= %d , jt%d= %d \n ",id,i1,id,j);
   // printf("usf%d:\n ",id);
   /* for(i=0;i<=i1;i++)
    printf(" %d\n",usf[i]);
    printf("usl%d:\n ",id);
    for(i=0;i<=j;i++)
    printf(" %d\n",usl[i]);*/
    pthread_mutex_unlock(&lock3);

   //if(usf[i1]>=usl[j] && usf[i1-1]>=usl[j-1])
    }

   }

 }
 printf("iteration of %d thread is %d",id,c);

}

main(){
  int i,k1,k2,r;
  t_data t1[NOT];
  for (i=0;i<NOT;i++){
  t1[i].x=i+1;}
  pthread_t t[NOT];
  srand(time(NULL));

  printf("Enter size of the array: ");
  scanf("%d",&size);

  for(i=0;i<size;i++){
        // scanf("%d",&merge[i]);
        x[i]=rand() % 1000 + 1;
    }
    printf("\nrandom numbers in random order : ");
    for(i=0;i<size;i++){
        // scanf("%d",&merge[i]);
        //merge[i]=rand() % 1000 + 1;
        printf("%d  ",x[i]);
    }

  /*printf("Enter %d elements: ",size);
  for(i=0;i<size;i++)
    scanf("%d",&x[i]);*/
  //printf("error in the fuckin thread");

 //pthread_barrier_init (&barrier, NULL, 2);
  
  pthread_mutex_init(&lock, NULL);
  pthread_mutex_init(&lock1, NULL);
  pthread_mutex_init(&lock2, NULL);
  pthread_mutex_init(&lock3, NULL);
  pthread_mutex_init(&lock4, NULL);
  start=clock();
  i1=0;j=0;
  usf[i1]=0;
  usl[j]=size-1;
  i1--;j--;
  r=partition(x,0,size-1);
  i1++;j++;
    usf[i1]=0;usl[j]=r-1;
    i1++;j++;
    usf[i1]=r+1;usl[j]=size-1;

  
  //printf("error in the fuckin thread");
  //for (i=0;i<NOT;i++){
  k1=pthread_create(&t[0],NULL,init1,(void *)&t1[0]);
  k2=pthread_create(&t[1],NULL,init2,(void *)&t1[1]);
 
  //pthread_barrier_wait (&barrier);

 // quicksort(x,0,size-1);
  for (i = 0; i < 2; ++i) {
    pthread_join(t[i], NULL);
  }
  printf("Sorted elements: ");
  for(i=0;i<size;i++)
    printf(" %d",x[i]);
  
  end = clock();
  time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  //printf("\n%lf",time_spent);

}
/*void quicksort(int a[], int p, int r)    
{
  if(p < r)
  {
    int q;
    q = partition(a, p, r);
    quicksort(a, p, q-1);
    quicksort(a, q+1, r);
  }
}*/

int partition(int x[], int p, int r)
{
  int i, j1, temp,p_index;
 // printf("entering partition \n");
  p_index=p;
  i = p;
  j1 = r;
  
  while(i<j1)
  {
   while(x[i] <= x[p_index] && i<r)
   i++;
   while(x[j1] > x[p_index])
   j1--;
   if(i < j1)
   {
    temp = x[i];
    x[i] = x[j1];
    x[j1] = temp;
   }
  }
   
   
   temp=x[p_index];
   x[p_index]=x[j1];
   x[j1]=temp;
   
  
   return j1;
   
  
}
