#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include<windows.h>
 // ����Ƶ����з�����Ϣ�ṹ��
typedef struct HotelRoomInfo {
    char room_type[50];       // ��������
    double room_price;        // ����۸�
    int total_rooms;          // �ܷ�����
    int remaining_rooms;      // ʣ�෿����
    struct HotelRoomInfo* next;   // ָ����һ��������Ϣ�ڵ��ָ��
} HotelRoomInfo;

// ����ͻ��Ѷ�������Ϣ�ṹ��
typedef struct CustomerRoomInfo {
	char room_num[50];        //����� 
    char room_type[50];       // ��������
    double room_price;        // ����۸�
    struct CustomerRoomInfo* next;   // ָ����һ���ͻ�������Ϣ�ڵ��ָ��
} CustomerRoomInfo;

// ����ͻ���Ϣ�ṹ��
typedef struct Customer {
    char name[100];           // �ͻ�����
    char gender;              // �ͻ��Ա�
    char idcard[100];         //�ͻ����֤
    char phone[20];           // �ͻ��绰
    char check_in_date[20];   // �ͻ���ס����
    CustomerRoomInfo* room_info; // ָ��ͻ��Ѷ�������Ϣ��ָ��
    char booking_time[80];    // ����ʱ��
    double total_price;       // �����ܼ�
    struct Customer* next;    // ָ����һ���ͻ���Ϣ�ڵ��ָ��
} Customer;

struct link{
	int num;
	int room;
	char kind[30];
	char date[30];
	int price;
	struct link * next;
};

typedef struct project{
	int number;
	char name[30];
	int pri;
	struct project * next;
}pro;

void Room_Menu();//��ӡ���ܲ˵� 
void addRoomType(const char* roomType, double price, int totalRooms, int remaining_rooms); // ��ӷ�����Ϣ�������� 
void removeRoomType(const char* roomType) ;//ɾ������
void saveRoomInfoToFile() ;//�����ʹ����ļ�
void displayRoomTypes() ;//չʾ������Ϣ
void insertCustomerNode(Customer newCustomer); 
void saveCustomersToFile() ;//���ͻ���Ϣ���浽�ļ� 
void loadRoomInfoFromFile() ;//���ļ����ط�����Ϣ�Ϳͻ�������¼ 
void displayCustomerInfo() ;//��ʾ�ͻ���Ϣ 
void bookRoom() ;//���ж������� 
void checkOut(char *name) ;//�˷�
void sortCustomersByTotalPrice();// �����û������ܽ��ӵ͵��߽������� 
 void entertainment();
pro * Create(pro*head,int num,char *a,int pr);                            
link * Order(link*head1,int nu,int r,char *k,char *d,int p);             
void Function_Menu();                                                     
void Delete(pro* head,int n);                                           
void Change(pro *head,int n,int a);                                      
void Menu(pro * head);                                                   
void Sort_choose(pro *head);                                           
void Name_sort(pro *head);                                                
void Charge_sort(pro * head);                                              
void Order_choose(link *head1);                                                                                
void Search_sort(link*head1,int n);                                      
void Order_delete(link * head1,int k);                                    
void output(link * head1);                                              
int sum=0;
int nplus=0;
Customer* customer_head = NULL;  // ָ��ͻ���Ϣ����ͷ�ڵ�
/**
* �Ƶ����з��� operations 
*/ 
HotelRoomInfo* hotel_room_head = NULL; // ָ��Ƶ귿����Ϣ����ͷ�ڵ�


// ��ӷ�����Ϣ�������� 
void addRoomType(const char* roomType, double price, int totalRooms, int remaining_rooms) {
    HotelRoomInfo* newRoom = (HotelRoomInfo*)malloc(sizeof(HotelRoomInfo));
    
    strcpy(newRoom->room_type, roomType);
    newRoom->room_price = price;
    newRoom->total_rooms = totalRooms; 
    newRoom->remaining_rooms = remaining_rooms;
    newRoom->next = NULL;

    if (hotel_room_head == NULL) {
        hotel_room_head = newRoom;
    } else {
    	// ����������β�� �������ݲ��뵽����β�� 
        HotelRoomInfo* current = hotel_room_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newRoom;
    }
}
// ɾ������ 
void removeRoomType(const char* roomType) {
    HotelRoomInfo* current = hotel_room_head;
    HotelRoomInfo* prev = NULL; // prevΪָ��ǰһ������ָ�� 

    while (current != NULL) {
        if (strcmp(current->room_type, roomType) == 0) { // ���ΪҪɾ���ķ������� 
            if (prev == NULL) {  
                hotel_room_head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current); // ɾ���ý�� 
            return;
        }
        prev = current;
        current = current->next;
    }
}
// ��������Ϣ�����ļ� 
void saveRoomInfoToFile() {
    FILE* fp = fopen("room_info.txt", "w");
    if (fp == NULL) {
        printf("�޷�����������Ϣ�ļ�!\n");
        return;
    }

    HotelRoomInfo* current = hotel_room_head; // ��������, ��ÿ������������δ����ļ� 
    while (current != NULL) {
        fprintf(fp, "%s %.2lf %d %d\n", current->room_type, current->room_price, current->total_rooms, current->remaining_rooms);
        current = current->next;
    }

    fclose(fp);
    printf("�ɹ����淿����Ϣ���ļ�!\n");
}

// չʾ���з�����Ϣ 
void displayRoomTypes() {
    HotelRoomInfo* current = hotel_room_head;

    printf("���з�����Ϣ:\n");
    while (current != NULL) {
        printf("��������: %s, ����۸�: %.2lf, �ܷ�����: %d, ʣ�෿����: %d\n",
               current->room_type, current->room_price, current->total_rooms, current->remaining_rooms);
        current = current->next;
    }
}


/** 
* �ͻ�����
*/ 
 
void insertCustomerNode(Customer newCustomer) 
{
    // �����½ڵ�
    Customer* newNode = (Customer*)malloc(sizeof(Customer));
    *newNode = newCustomer;
    newNode->next = NULL;

    // �������Ϊ�գ����½ڵ���Ϊͷ�ڵ�
    if (customer_head == NULL) {
        customer_head = newNode;
        return;
    }

    // ���������ҵ����һ���ڵ㣬�����½ڵ����ĩβ
    Customer* current = customer_head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void saveCustomersToFile() //���ͻ���Ϣ���浽�ļ� 
{
    FILE* fp = fopen("customers.txt", "w");
    if (fp == NULL) {
        printf("�޷������ͻ���Ϣ�ļ�!\n");
        return;
    }

    Customer* current = customer_head;
    while (current != NULL) {
        fprintf(fp, "%s %c %s %s %s %s", current->name, current->gender,current->idcard, current->phone,current->check_in_date, current->booking_time);

        // �����ͻ��Ѷ�����������������Ϣ�洢���ļ���
        CustomerRoomInfo* roomInfo = current->room_info;
        while (roomInfo != NULL) {
            fprintf(fp, " %s %.2lf", roomInfo->room_type, roomInfo->room_price);
            roomInfo = roomInfo->next;
        }

        fprintf(fp, " %.2lf\n", current->total_price);

        current = current->next;
    }

    fclose(fp);
    printf("�ɹ�����ͻ���Ϣ���ļ�!\n");
}

//void loadRoomInfoFromFile() //���ļ����ط�����Ϣ�Ϳͻ�������¼ 
//{
//	// ���ؿͻ�������¼�ļ� 
//    FILE* fp = fopen("customers.txt", "r");
//	if (fp == NULL) {
//	    printf("δ�ҵ��ͻ���Ϣ�ļ����������ļ�!\n");
//	    return;
//	}
//	
//	while (!feof(fp)) {
//	    Customer newCustomer;
//	
//	    // ��ȡ�����ͻ���Ϣ
//	    int result = fscanf(fp, "%s %c %s %s %s %s",
//	                        newCustomer.name,
//	                        &newCustomer.gender,
//	                        newCustomer.idcard,
//	                        newCustomer.phone,
//	                        newCustomer.check_in_date,
//	                        newCustomer.booking_time);
//	
//	    // ��ʼ���ͻ��Ѷ���������ͷ
//	    newCustomer.room_info = NULL;
//	
//	    // ��ȡ������Ϣ���ܼ�
//	    double total_price = 0.0;
//	    char roomType[50];
//	    double roomPrice;
//	    char roomNum[20];
//	    // ÿ��ѭ����ȡһ��������Ϣ
//	    while (fscanf(fp, "%s %s %lf",roomNum, roomType, &roomPrice) == 3) {
//	        total_price += roomPrice;
//	
//	        // ���ӷ�����Ϣ�ڵ㵽�ͻ����Ѷ�����������
//	        CustomerRoomInfo* newRoom = (CustomerRoomInfo*)malloc(sizeof(CustomerRoomInfo));
//	        strcpy(newRoom->room_num, roomNum);
//			 strcpy(newRoom->room_type, roomType);
//	        newRoom->room_price = roomPrice;
//	        newRoom->next = NULL;
//	
//	        if (newCustomer.room_info == NULL) {
//	            newCustomer.room_info = newRoom;
//	        } else {
//	            CustomerRoomInfo* temp = newCustomer.room_info;
//	            while (temp->next != NULL) {
//	                temp = temp->next;
//	            }
//	            temp->next = newRoom;
//	        }
//	    }
//	
//	    newCustomer.total_price = total_price;
//	
//	    // �����½ڵ㲢��������
//	    insertCustomerNode(newCustomer);
//	}
//	
//	fclose(fp);
//
//
//
//    
//    // ���ؾƵ����з��ͼ�¼�ļ� 
//    fp = fopen("room_info.txt", "r");
//    if (fp == NULL) {
//        printf("δ�ҵ�������Ϣ�ļ����������ļ�!\n");
//        return;
//    }
//
//    while (!feof(fp)) {
//        char roomType[50];
//        double price;
//        int totalRooms, remainingRooms;
//
//        if (fscanf(fp, "%s %lf %d %d\n", roomType, &price, &totalRooms, &remainingRooms) == 4) {
//            addRoomType(roomType, price, totalRooms, remainingRooms);
//        }
//    }
//
//    fclose(fp);
//}

void displayCustomerInfo() //��ʾ�ͻ���Ϣ 
{
    Customer* current = customer_head;

    while (current != NULL) {
    
        printf("�ͻ�����: %s\n", current->name);
        printf("�ͻ��Ա�: %c\n", current->gender);
        printf("�ͻ����֤�ţ�%s\n",current->idcard);
        printf("�ͻ��绰: %s\n", current->phone);
        printf("��ס����: %s\n", current->check_in_date);
        printf("����ʱ��: %s\n", current->booking_time);
		printf("�ܽ��: %.2lf\n", current->total_price);
        // �����ͻ��Ѷ������������ʾ������Ϣ
        CustomerRoomInfo* roomInfo = current->room_info;
        printf("�ͻ��Ѷ�������Ϣ:\n");
        while (roomInfo != NULL) {
            printf("����ţ�%s, ��������: %s, ����۸�: %.2lf\n", roomInfo->room_num, roomInfo->room_type, roomInfo->room_price);
            roomInfo = roomInfo->next;
        }

        printf("--------------------\n");
        current = current->next;
    }
}

void bookRoom() //���ж������� 
{
	// ����ʱ��չʾ���з��� 
	displayRoomTypes();
	 
    Customer newCustomer;
    newCustomer.room_info = NULL; // ��ʼ��������Ϣ����
	 
    printf("����������: ");
    scanf("%s", newCustomer.name);
    
    printf("�������Ա�(M/F): ");
    scanf(" %c", &newCustomer.gender);
    
    printf("���������֤��: ");
    scanf(" %s", newCustomer.idcard);

    printf("������绰����: ");
    scanf("%s", newCustomer.phone);

    printf("��������ס����: ");
    scanf("%s", newCustomer.check_in_date);
	
//	 ����ʱ��Ϊ��ǰϵͳʱ�� 
	time_t rawtime;
	struct tm *timeinfo;
    time(&rawtime);
	timeinfo = localtime(&rawtime);
	
    char bookingTime[200];  // ���� booking_time ��һ�� char ����
	strftime(bookingTime, sizeof(bookingTime), "%Y-%m-%d-%H:%M:%S", timeinfo);
	
	sprintf(newCustomer.booking_time, "%s", bookingTime);
	

    // ����������ַ���������Ϣ��ֱ���������
    int moreRooms = 1;
    do {
        CustomerRoomInfo* newRoomInfo = (CustomerRoomInfo*)malloc(sizeof(CustomerRoomInfo));
        printf("�����: ");
        scanf("%s", newRoomInfo->room_num);
		printf("�����뷿������: ");
        scanf("%s", newRoomInfo->room_type);
        newRoomInfo->next = NULL;

        // �������в��Ҷ�Ӧ�������͵ķ�����Ϣ
        HotelRoomInfo* currentRoom = hotel_room_head;
        while (currentRoom != NULL) {
            if (strcmp(currentRoom->room_type, newRoomInfo->room_type) == 0) {
                // �ҵ���Ӧ�������ͣ����¿ͻ��ķ�����Ϣ
                strcpy(newRoomInfo->room_type, currentRoom->room_type);
                newRoomInfo->room_price = currentRoom->room_price;
                
				newCustomer.total_price += currentRoom->room_price;
				currentRoom->remaining_rooms -= 1;
                // ��ӷ�����Ϣ���ͻ��ķ�����Ϣ������
                if (newCustomer.room_info == NULL) {
                    newCustomer.room_info = newRoomInfo;
                } else {
                    CustomerRoomInfo* current = newCustomer.room_info;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newRoomInfo;
                }
                break;
            }
            currentRoom = currentRoom->next;
        }

        printf("���и��෿��ҪԤ����(1-�ǣ�0-��): ");
        scanf("%d", &moreRooms);
    } while (moreRooms);

    // ���µĿͻ���Ϣ��ӵ��ͻ���Ϣ������
    insertCustomerNode(newCustomer);

    // ���µĿͻ���Ϣ���浽�ļ�
    saveCustomersToFile();
    saveRoomInfoToFile();
}

//�˷�
void checkOut(char *name) {
   Customer *current = customer_head;
   Customer *prev = NULL;

   // �����ͻ���Ϣ�����ҵ���Ӧ�Ŀͻ����
   while (current != NULL) {
       if (strcmp(current->name, name) == 0) {
           // ����ҵ��˶�Ӧ�Ŀͻ���㣬�����������ɾ��
           if (prev == NULL) {
               customer_head = current->next;
           } else {
               prev->next = current->next;
           }

           // ���ͻ����ķ�����Ϣ������ӵ��Ƶ귿����Ϣ������
           CustomerRoomInfo *room_info = current->room_info;
           while (room_info != NULL) {
               HotelRoomInfo *room = hotel_room_head;
               while (room != NULL) {
                   if (strcmp(room->room_type, room_info->room_type) == 0) {
                       room->remaining_rooms++;
                       break;
                   }
                   room = room->next;
               }
               room_info = room_info->next;
           }

           // ���¿ͻ����� checked_out �ֶ�Ϊ true
         //  current->checked_out = true;

           // ���ͻ����� total_price �ֶ�����
           current->total_price = 0;

           // �ͷſͻ������ڴ�
           free(current);

       }
       prev = current;
       current = current->next;
   }

   // ���δ�ҵ���Ӧ�Ŀͻ���㣬���������Ϣ
   printf("δ�ҵ��ͻ� %s\n", name);
}
 

// �����û������ܽ��ӵ͵��߽������� 
void sortCustomersByTotalPrice() {
    if (customer_head == NULL || customer_head->next == NULL) {
        return; // ����Ϊ�ջ�ֻ��һ���ڵ㣬��������
    }

    int swapped;
    Customer *temp = NULL;

    do {
        swapped = 0;
        Customer *current = customer_head;
        while (current->next != NULL) {
            if (current->total_price > current->next->total_price) {
                // �����ڵ�λ��
                if (current == customer_head) {
                    customer_head = current->next;
                } else {
                    temp->next = current->next;
                }

                temp = current->next;
                current->next = temp->next;
                temp->next = current;
                swapped = 1;
            } else {
                temp = current;
                current = current->next;
            }
        }
    } while (swapped);
}

void Room_Menu()//��ӡ���ܲ˵� 
{
	printf("\n               �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("               �U         �Ƶ����ϵͳ             �U\n");
		printf("               �d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("               �U 1. ����                          �U\n");
		printf("               �U 2. չʾ���з�����Ϣ              �U\n");
		printf("               �U 3. ��ӷ�����Ϣ                  �U\n");
		printf("               �U 4. ɾ��������Ϣ                  �U\n");
		printf("               �U 5. չʾ�û�������Ϣ              �U\n");
		printf("               �U 6. ����ͻ�������¼              �U\n");
		printf("               �U 7. �˳�                          �U\n");
		printf("               �U 8. �˷�                          �U\n"); 
		printf("               �U 9. ������Ŀ                      �U\n"); 
		printf("               �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}
int main() {
    //loadRoomInfoFromFile(); 
    int choice;
    Room_Menu();
		printf("��ѡ�����: ");
		scanf("%d", &choice);
        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                displayRoomTypes();
                break;
            case 3:
                {
                    char roomType[50];
                    double price;
                    int totalRooms;

                    printf("������Ҫ��ӵķ�������: ");
                    scanf("%s", roomType);
                    printf("������۸�: ");
                    scanf("%lf", &price);
                    printf("�������ܷ�����: ");
                    scanf("%d", &totalRooms);

                    addRoomType(roomType, price, totalRooms, totalRooms);
                    //saveRoomInfoToFile(); // ���浽�ļ�
                }
                break;
            case 4:
                {
                    char roomTypeToRemove[50];
                    printf("������Ҫɾ���ķ�������: ");
                    scanf("%s", roomTypeToRemove);

                    removeRoomType(roomTypeToRemove);
                    saveRoomInfoToFile(); // ���浽�ļ�
                }
                break;
            case 5: 
            	displayCustomerInfo();
				break; 
            case 6:
            	sortCustomersByTotalPrice();
            	displayCustomerInfo();
            	break;
			case 7:
                saveRoomInfoToFile(); // ���浽�ļ�
                exit(0);
//            case 8:
//            	char name[20];
//            	printf("������Ҫ�˷��Ŀͻ�������");
//            	scanf("%s",name);
//            	void checkOut(char *name);
//            	break;
			 case 9:
			 	entertainment();
			 	break;
            default:
                printf("��Ч��ѡ��!\n");
        }
     while (choice != 9);

    return 0;
}

void entertainment()
{	bool flag;
    char c;
    pro * head=(pro *)malloc(sizeof(pro));
    link * head1=(link *)malloc(sizeof(link));
    head->next=NULL;
    head1->next=NULL;
	pro * ps;
	while(1)//����ѡ�� 
	{
     Function_Menu();
		c = getch();
		switch(c)
		{
			case '1':
			    int pr;
			    char a[30];
			    int num;
			   	printf("��������Ŀ��š����ƺͼ۸� \n"); 	
	            scanf("%d%s%d",&num,a,&pr);
	            if (num>0)
				  ps=Create(head,num,a,pr);
				  printf("\n���κμ����η������˵�\n");
				  getch();getch();    
				  break;
				  Function_Menu();
			case '2': 
			    int n;
				printf("������Ҫɾ������Ŀ���:");
                scanf("%d",&n); 
				Delete(ps,n);
				printf("\n���κμ����η������˵�\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '3': 
			    printf("��������Ҫ�޸ĵ���Ŀ��ţ�");
	            int e;
	            int y;
             	scanf("%d", &e);
	            if(e<=0)
		        printf("������޶�Ӧ��Ŀ��\n");
		        else
		        printf("��ѡ���޸Ķ���\n1������\n2���۸�\n");
		        y= getch();
				Change(ps,e,y);
				printf("\n���κμ����η������˵�\n");
	            getch();getch(); 
				break;
				Function_Menu();
			case '4': 
			    char c;
				Sort_choose(ps);
				c = getch();
		        switch(c)
		           {
			          case '1': Name_sort(head); break;
			          case '2': Charge_sort(head); break;
			          default: break;
	            	}
	            printf("����ɹ���\n��򿪲˵��鿴��");	
				printf("\n���κμ����η������˵�\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '5': 
			    int nu,r,pri;
			    char g[30],h[30];
			    printf("��������š�����š���Ŀ���ơ�ԤԼ���ںͼ۸�\n"); 	
	            scanf("%d%d%s%s%d",&nu,&r,g,h,&pri);
	            if (nu>0)
				Order(head1,nu,r,g,h,pri);
				printf("\n���κμ����η������˵�\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '6': 
			    char d;
			    int o;
				Order_choose(head1);
				d = getch();
		        switch(d)
		           {
			          case '1': 
			          printf("������Ҫ���ҵķ����");
			          scanf("%d",&o);
					  Search_sort(head1,o);
					  break;
			          case '2': output(head1);
					  break;
			          default: break;
	            	}
				printf("\n���κμ����η������˵�\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '7':
				system("cls"); 
			    Menu(ps);
			    printf("\n���κμ����η������˵�\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '8' :
				system("cls"); 
				int k;
				output(head1);
				printf("������Ҫɾ���Ķ������:");
                scanf("%d",&k); 
			    Order_delete(head1,k);
			    printf("\n���κμ����η������˵�\n");
	            getch();getch();    
			    break;
				Function_Menu();
			case '0': 
			system("cls");
			
				break;
					} 
	}
	
}


pro * Create(pro*head,int num,char *a,int pr)
{
  pro * p=head;
  while(p->next) {
  	p=p->next;
  }
  pro * q;//p��β   q �½�� 
  int t;
  char v;
 while(num>0)
  {
  	q=(pro *)malloc(sizeof(pro)); 
  	q->number=num;
  	strcpy(q->name,a);
  	q->pri=pr;
  	p->next=q;
  	p=q;
  	num=0;
  }
  p->next=NULL;
  printf("��ӳɹ����Ƿ�Ҫ�������(y/n)\n");
  v=getch();
  while (v=='y')
  {
 printf("\n��������Ŀ��š����ƺͼ۸� \n");
 scanf("%d%s%d",&num,a,&pr);
 while (num>0)
  {
    Create(head,num,a,pr);
  }
break;
   }                  
  return head;
}

link * Order(link*head1,int nu,int r,char *k,char *d,int pri)
{ char v;
  link * p=head1;
  while(p->next) {
  	p=p->next;
  }
  link * q;//p��β   q �½�� 
  int t;
  while(nu>0)
  {
  	q=(link *)malloc(sizeof(link)); 
  	q->num=nu;
	q->room=r;
	strcpy(q->kind,k);
	strcpy(q->date,d);
	q->price=pri;
    sum+=(q->price);
	nplus++;
  	p->next=q;
  	p=q;
  	nu=0;
  }
  p->next=NULL;
  printf("��ѡ��%d����Ŀ��һ��%dԪ\n",nplus,sum);
  printf("�Ƿ�Ҫ�������(y/n)\n");
  v=getch();
  while (v=='y')
  {
   printf("��������š�����š���Ŀ���ơ�ԤԼ���ںͼ۸�\n"); 	
	scanf("%d%d%s%s%d",&nu,&r,k,d,&pri);
 if (nu>0)
  {
    Order(head1,nu,r,k,d,pri);
  }
break;
   }    
       nplus=0;sum=0;
  return head1;
}

void Function_Menu()//��ӡ���ܲ˵� 
{
	printf("\n\n\n\n");
	printf("\t\t\t\t                 �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r                 \n");
	printf("\t\t\t\t�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g�Ƶ�������Ŀ����ϵͳ�d�T�T�T�T�T�T�T�T�T�T�T�T�T�r\n");
	printf("\t\t\t\t�U                �t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s             �U\n");
	printf("\t\t\t\t�U     ��1�������Ŀ             ��2��ɾ����Ŀ       �U\n");
	printf("\t\t\t\t�U                                                   �U\n");
	printf("\t\t\t\t�U     ��3���޸���Ŀ             ��4����Ŀ����       �U\n");
	printf("\t\t\t\t�U                                                   �U\n");
	printf("\t\t\t\t�U     ��5���˿�ѡ����Ŀ         ��6������鿴����   �U\n");
	printf("\t\t\t\t�U                                                   �U\n");
	printf("\t\t\t\t�U     ��7��չʾ�˵�             ��8��ɾ������       �U\n");
	printf("\t\t\t\t�U                                                   �U\n");
	printf("\t\t\t\t�U                   ��0���˳�ϵͳ                   �U\n");
	printf("\t\t\t\t�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
	printf("\t\t\t\t\t�������빦��ǰ�����ִ����Ӧ�Ĺ���:\n");
}

void Delete(pro* head,int n)
{  pro* p;
   pro *q;    
    while(head->next && head->next->number!=n) 
	head=head->next;
    if (head->next==NULL) return;
    p=head->next;
    q=p->next;
    head->next=q;
    free(p);
}

void Change(pro *head,int n,int a)//�޸�
{
	system("cls");
	pro *p = head->next;
	if (p == NULL) 
	{
		printf("ϵͳ��������Ŀ��Ϣ��\n\n");
	}
		for( int i = 1; i < n; i++)
		      p = p->next;
		switch(a)
		{
			case '1': 
				system("cls");
				printf("�������޸ĺ�����ƣ�\n");
				scanf("%s", p->name);
				getchar();
				break;
			case '2': 
				system("cls");
				printf("�������޸ĺ�ļ۸�\n");
				scanf("%d",&p->pri);
				break;
			default: 
				system("cls");
				break;
		}
		system("cls");
		printf("��Ŀ��Ϣ�޸ĳɹ���\n");
    }
	
void Menu(pro * head)//��ӡ�˵� 
{system("cls");
	int i = 1;
	pro * p = head->next;
	if (p== NULL) 
	{
		printf("ϵͳ��������Ŀ��Ϣ����¼����ٲ鿴��\n\n");
	}
	else 
	{
		printf("\t\t\t\t*********************************************************\n");
		printf("\t\t\t\t*\t\t\t��ӭ���ٱ��Ƶ�  \t\t\t*\n");
		printf("\t\t\t\t*********************************************************\n");
		printf("\t\t\t\t*���                 ����                    �۸�      *\n");
		printf("\t\t\t\t*********************************************************\n");
		while (p != NULL)
		{
			p->number = i;
	    printf("\t\t\t\t*% -3d                %-10s               ��%-6d    *\n", i, p->name, p->pri);
	    printf("\t\t\t\t*********************************************************\n");
			p = p->next;
			i++; 
		}
		printf("\n\t\t\t\t\t\t  һ����%d����Ŀ", i-1);
}
}

void Sort_choose(pro *head)//����ʽѡ�� 
{
	system("cls");
	pro *p = head;
	if (p == NULL) 
	{
		printf("ϵͳ��������Ŀ��Ϣ��\n\n");
	}
	else
	{ 
		printf("\n\n\n\n");
		printf("\t\t\t\t                 �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r                 \n");
		printf("\t\t\t\t�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g    ����ʽ    �d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r\n");
		printf("\t\t\t\t�U                �t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s                �U\n");
		printf("\t\t\t\t�U     ��1������������           ��2�����۸���    �U\n");
		printf("\t\t\t\t�U                                                  �U\n");
		printf("\t\t\t\t�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
		printf("\t\t\t\t\t�����������ѡ����Ӧ������ʽ:");   
		 
	} 
}

void Name_sort(pro *head)//��������� 
{
	system("cls");
	int n = 0;
	int t,a;
	pro *p = head;
	char  b[30];
	while(p != NULL)//�������� 
	{
		n++;
		p = p->next;
	}
	for(int i = 1; i < n; i++)
	{
		p = head;
		for(int j = 0; j < n - i; j++)
		{
			if(strcmp(p->name, p->next->name) > 0)
			{a = p->number;
				p->number= p->next->number;
				p->next->number= a;	
				strcpy(b, p->name);
				strcpy(p->name, p->next->name);
				strcpy(p->next->name, b);
				t = p->pri;
				p->pri= p->next->pri;
				p->next->pri= t;	
			}
			p = p->next;
		}
	}
}

void Charge_sort(pro * head)//���۸����� 
{system("cls");
	pro *p = head;
	int n = 0;
	int a,t;
	char b[30];
		while(p != NULL)//������Ŀ���� 
	{
		n++;
		p = p->next;
	}
	for(int i = 1; i < n; i++)
		{
			p =head;
			for(int j = 0; j < n - i; j++)
			{
				if(p->pri < p->next->pri)
				{a = p->number;
				p->number= p->next->number;
				p->next->number= a;
				strcpy(b, p->name);
				strcpy(p->name, p->next->name);
				strcpy(p->next->name, b);
				t = p->pri;
				p->pri= p->next->pri;
				p->next->pri= t;		
				}
				p = p->next;
			}
		}
    }

void Order_choose(link *head1)//����ʽѡ�� 
{
	system("cls");
	link*p = head1;
	if (p == NULL) 
	{
		printf("ϵͳ��������Ŀ��Ϣ��\n\n");
	}
	else
	{ 
		printf("\n\n\n\n");
		printf("\t\t\t\t                 �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r                 \n");
		printf("\t\t\t\t�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g    ����ʽ    �d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r\n");
		printf("\t\t\t\t�U                �t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s                �U\n");
		printf("\t\t\t\t�U         ��1���鿴���巿��ԤԼ��Ŀ                �U\n");
		printf("\t\t\t\t�U                                                  �U\n");
		printf("\t\t\t\t�U         ��2���鿴����ԤԼ��Ŀ������Ϣ            �U\n");
		printf("\t\t\t\t�U                                                  �U\n");
		printf("\t\t\t\t�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
		printf("\t\t\t\t\t�����������ѡ����Ӧ������ʽ:\n");   
		 } 
}

void Search_sort(link*head1,int n)
{   system("cls");
int i=1;
    link *p1=head1;
	while(n!=p1->room&&p1->next!=NULL)
	p1=p1->next;
	if(n==p1->room)
	{
	   printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*\t\t  ��ӭ���ٱ��Ƶ�  \t\t\t*\n");
	   printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*���     �����        ����           ����      �۸�   *\n");
	   printf("\t\t\t\t*********************************************************\n");
		while (p1 != NULL)
		{
			p1->num = i;
	   printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ��%-6d  *\n", i,p1->room,p1->kind,p1->date,p1->price);
	   printf("\t\t\t\t*********************************************************\n");
			p1 = p1->next;
			i++; 
		}
}
else
printf("�÷���˿���δԤԼ��Ŀ��\n");
}

void Order_delete(link*head1,int k)
{  system("cls");
link* p;
   link *q;    
    while(head1->next && head1->next->num!=k) 
	head1=head1->next;
    if (head1->next==NULL) return;
    p=head1->next;
    q=p->next;
    head1->next=q;
    free(p);
    printf("ɾ���ɹ���");
}

void output(link * head1)//��ӡ���� 
{
	int i = 1;
	link * p = head1->next;
	if (p== NULL) 
	{
		printf("ϵͳ��������Ŀ��Ϣ����¼����ٲ鿴��\n\n");
	}
	else 
	{ 
		printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*\t\t  ��ӭ���ٱ��Ƶ�  \t\t\t*\n");
	   printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*���     �����        ����           ����      �۸�   *\n");
	   printf("\t\t\t\t*********************************************************\n");
		while (p != NULL)
		{
			p->num = i;
	   printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ��%-6d  *\n", i,p->room,p->kind,p->date,p->price);
	   printf("\t\t\t\t*********************************************************\n");
			p = p->next;
			i++; 
		}
		printf("\n\t\t\t\t\t\t  һ����%d����Ŀ", i-1);
}
}



