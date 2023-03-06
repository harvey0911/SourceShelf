#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define size 10
int Ticket_number_N=0;
int Ticket_number_E=100;


typedef struct tag{

    char name[50];
    int ticket_number;
    struct tag* next;

}client_info;


void menu(void){
   printf("\n\t\t------------- Menu --------------\n");
   printf("\n\t\t1.start the program\n");
   printf("\n\t\t2. add a new client \n");
   printf("\n\t\t3. serve a client\n");
   printf("\n\t\t4. leave the queue  \n");
   printf("\n\t\t5. emergency case\n");
   printf("\n\t\t6.time to leave");

  
  
}


void enqueue(client_info** pfront,client_info** prear,client_info* element){
client_info* walker=*pfront;

    if(*pfront==NULL){
    *pfront=element;
    *prear=element;
}else{

    if(element->ticket_number>=100){
        
        if(element->ticket_number==100){
            element->next=*pfront;
            *pfront=element;
            
        }else{

            while(walker->next->ticket_number>=100 && walker->next!=NULL){

        walker=walker->next;
    }
  
element->next=walker->next;
walker->next=element;
*prear=element;



        }
        
            
        }else{
    
            (*prear)->next=element;
            *prear=(*prear)->next;

        }



}




}
void traverse(client_info* front){
client_info* walker;
  walker=front;
printf("\n\t your linked list contains the following names\n");
while(walker!=NULL){        
    
    printf("\t %s\n",walker->name);
    walker=walker->next;
    

}
}

void start_the_program(FILE* infp,client_info**pfront,client_info** prear){
client_info* element;
Ticket_number_N=0;
Ticket_number_E=100;
  fseek(infp,0,0);
while(!feof(infp)){

  element=(client_info*)malloc(sizeof(client_info));
    fgets(element->name,50,infp);

    if(element->name[strlen(element->name)-1]=='\n'){
        element->name[strlen(element->name)-1]='\0';
    }
    
    element->ticket_number=++Ticket_number_N;
    element->next=NULL;

  enqueue(pfront,prear,element);
  
}
traverse(*pfront);
}

client_info dequeue(client_info**pfront){
client_info* temp, client_to_serve;

temp=*pfront;
client_to_serve=**pfront;
*pfront=(*pfront)->next;
free(temp);
return client_to_serve;

}
void quit_queue(client_info** pfront,client_info** prear,int ticket_to_delete,int* status){
client_info* temp,*walker;

    if((*pfront)->ticket_number==ticket_to_delete){
temp=*pfront;
*pfront=(*pfront)->next;
free(temp);
*status=1;

    }else{
        walker=*pfront;
        while (walker->next != NULL) {
    if (walker->next->ticket_number==ticket_to_delete) {
    
        if(walker->next==*prear){

        *prear=walker;
    }

       temp=walker->next;
       walker->next= temp->next ;
       free(temp);
      *status=1;
      break;

      }else{
      walker=walker->next;
      }
      
      
    }


    }



}
void time_to_leave(FILE* infp,client_info* front){
client_info* walker;

walker=front;
while(walker!=NULL){
 if(walker->next==NULL){
  fprintf(infp,"%s",walker->name);
}else{
  fprintf(infp,"%s\n",walker->name);
}

    walker=walker->next;
}

}

int main(void){
  
client_info* front=NULL,*rear=NULL;
client_info* new_element,served_client;
FILE* infp;
int choice,flag1=0,flag2,ticket_to_delete,status=0;

do{
  
menu();
scanf("%d",&choice);
switch (choice){

case 1:
flag1=1;
infp=fopen("AppointmentList.txt","r+");
if(infp==NULL){
    printf("file not found");

}else{
  
    if(fgetc(infp)==EOF){
    printf("the list of appointements is empty");
    }else{

        
        start_the_program(infp,&front,&rear);
fclose(infp);
    }
}
    break;
case 2:
if(flag1!=1){

    printf("you cannot add a new client before starting the program !");
}else{
    new_element=(client_info*)malloc(sizeof(client_info)); 
getchar();
printf("enter the name");

gets(new_element->name);
    new_element->ticket_number= ++Ticket_number_N;
    new_element->next=NULL;

    enqueue(&front,&rear,new_element);
    traverse(front);
}
    break;

case 3:
 if(flag1!=1){
printf("you cannot serve a client before starting the program !");
 }else{
    if(front==NULL){
printf("the queue is empty");
}else{
served_client=dequeue(&front);
printf("client %s with ticket #%d was served",served_client.name,served_client.ticket_number);
}
 }
    break;
case 4:
if(flag1!=1){

    printf("you cannot leave the queue before starting the program");
    
}else{

    if(front==NULL){
        printf("the queue is empty");
}else{
        printf("enter the ticket number of the client you want to delete ");
        scanf("%d",&ticket_to_delete);
        quit_queue(&front,&rear,ticket_to_delete,&status);

if(status==1){
        printf("client with ticket #%d left the queue",ticket_to_delete);
}else{
        printf("client with ticket #%d is not found in the queue",ticket_to_delete);
}
traverse(front);
}

}


    break;

case 5:
if(flag1!=1){
printf("you cannot add an emergency case before starting the program");
}else{
        new_element=(client_info*)malloc(sizeof(client_info));
        getchar();
        printf("enter the name");
        gets(new_element->name);

        new_element->ticket_number=Ticket_number_E++;
        new_element->next=NULL;

        enqueue(&front,&rear,new_element);
        traverse(front);
}

    break;
case 6:
if(flag1!=1){
    printf("the doctor cannot leave before starting the program");
}else{
    if(front==NULL){

printf("no one is left in the queue ! the doctor can leave");
}else{

if(front->ticket_number>=100){
    printf("you still have emergency cases the doctor should");
  flag2=0;
  
}else{
flag2=1;
infp=fopen("AppointmentList.txt","w");
    time_to_leave(infp,front);
}
}

}

    break;

  default:
    break;
}







}while(choice !=6 || flag1!=1|| flag2!=1);
    return 0;
}
