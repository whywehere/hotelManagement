#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include<windows.h>
 // 定义酒店现有房间信息结构体
typedef struct HotelRoomInfo {
    char room_type[50];       // 房间类型
    double room_price;        // 房间价格
    int total_rooms;          // 总房间数
    int remaining_rooms;      // 剩余房间数
    struct HotelRoomInfo* next;   // 指向下一个房间信息节点的指针
} HotelRoomInfo;

// 定义客户已订房间信息结构体
typedef struct CustomerRoomInfo {
	char room_num[50];        //房间号 
    char room_type[50];       // 房间类型
    double room_price;        // 房间价格
    struct CustomerRoomInfo* next;   // 指向下一个客户房间信息节点的指针
} CustomerRoomInfo;

// 定义客户信息结构体
typedef struct Customer {
    char name[100];           // 客户姓名
    char gender;              // 客户性别
    char idcard[100];         //客户身份证
    char phone[20];           // 客户电话
    char check_in_date[20];   // 客户入住日期
    CustomerRoomInfo* room_info; // 指向客户已定房间信息的指针
    char booking_time[80];    // 订房时间
    double total_price;       // 订房总价
    struct Customer* next;    // 指向下一个客户信息节点的指针
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

void Room_Menu();//打印功能菜单 
void addRoomType(const char* roomType, double price, int totalRooms, int remaining_rooms); // 添加房型信息到链表中 
void removeRoomType(const char* roomType) ;//删除房型
void saveRoomInfoToFile() ;//将房型存入文件
void displayRoomTypes() ;//展示房型信息
void insertCustomerNode(Customer newCustomer); 
void saveCustomersToFile() ;//将客户信息保存到文件 
void loadRoomInfoFromFile() ;//从文件加载房型信息和客户订房记录 
void displayCustomerInfo() ;//显示客户信息 
void bookRoom() ;//进行订房操作 
void checkOut(char *name) ;//退房
void sortCustomersByTotalPrice();// 根据用户订房总金额从低到高进行排序 
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
Customer* customer_head = NULL;  // 指向客户信息链表头节点
/**
* 酒店现有房间 operations 
*/ 
HotelRoomInfo* hotel_room_head = NULL; // 指向酒店房间信息链表头节点


// 添加房型信息到链表中 
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
    	// 遍历到链表尾部 将新数据插入到链表尾部 
        HotelRoomInfo* current = hotel_room_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newRoom;
    }
}
// 删除房型 
void removeRoomType(const char* roomType) {
    HotelRoomInfo* current = hotel_room_head;
    HotelRoomInfo* prev = NULL; // prev为指向前一个结点的指针 

    while (current != NULL) {
        if (strcmp(current->room_type, roomType) == 0) { // 如果为要删除的房间类型 
            if (prev == NULL) {  
                hotel_room_head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current); // 删除该结点 
            return;
        }
        prev = current;
        current = current->next;
    }
}
// 将房型信息存入文件 
void saveRoomInfoToFile() {
    FILE* fp = fopen("room_info.txt", "w");
    if (fp == NULL) {
        printf("无法创建房型信息文件!\n");
        return;
    }

    HotelRoomInfo* current = hotel_room_head; // 遍历链表, 将每个结点数据依次存入文件 
    while (current != NULL) {
        fprintf(fp, "%s %.2lf %d %d\n", current->room_type, current->room_price, current->total_rooms, current->remaining_rooms);
        current = current->next;
    }

    fclose(fp);
    printf("成功保存房型信息到文件!\n");
}

// 展示所有房型信息 
void displayRoomTypes() {
    HotelRoomInfo* current = hotel_room_head;

    printf("所有房型信息:\n");
    while (current != NULL) {
        printf("房间类型: %s, 房间价格: %.2lf, 总房间数: %d, 剩余房间数: %d\n",
               current->room_type, current->room_price, current->total_rooms, current->remaining_rooms);
        current = current->next;
    }
}


/** 
* 客户订房
*/ 
 
void insertCustomerNode(Customer newCustomer) 
{
    // 创建新节点
    Customer* newNode = (Customer*)malloc(sizeof(Customer));
    *newNode = newCustomer;
    newNode->next = NULL;

    // 如果链表为空，将新节点作为头节点
    if (customer_head == NULL) {
        customer_head = newNode;
        return;
    }

    // 遍历链表找到最后一个节点，并将新节点插入末尾
    Customer* current = customer_head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void saveCustomersToFile() //将客户信息保存到文件 
{
    FILE* fp = fopen("customers.txt", "w");
    if (fp == NULL) {
        printf("无法创建客户信息文件!\n");
        return;
    }

    Customer* current = customer_head;
    while (current != NULL) {
        fprintf(fp, "%s %c %s %s %s %s", current->name, current->gender,current->idcard, current->phone,current->check_in_date, current->booking_time);

        // 遍历客户已定房间的链表并将相关信息存储到文件中
        CustomerRoomInfo* roomInfo = current->room_info;
        while (roomInfo != NULL) {
            fprintf(fp, " %s %.2lf", roomInfo->room_type, roomInfo->room_price);
            roomInfo = roomInfo->next;
        }

        fprintf(fp, " %.2lf\n", current->total_price);

        current = current->next;
    }

    fclose(fp);
    printf("成功保存客户信息到文件!\n");
}

//void loadRoomInfoFromFile() //从文件加载房型信息和客户订房记录 
//{
//	// 加载客户订房记录文件 
//    FILE* fp = fopen("customers.txt", "r");
//	if (fp == NULL) {
//	    printf("未找到客户信息文件，创建新文件!\n");
//	    return;
//	}
//	
//	while (!feof(fp)) {
//	    Customer newCustomer;
//	
//	    // 读取基本客户信息
//	    int result = fscanf(fp, "%s %c %s %s %s %s",
//	                        newCustomer.name,
//	                        &newCustomer.gender,
//	                        newCustomer.idcard,
//	                        newCustomer.phone,
//	                        newCustomer.check_in_date,
//	                        newCustomer.booking_time);
//	
//	    // 初始化客户已定房间链表头
//	    newCustomer.room_info = NULL;
//	
//	    // 读取房间信息和总价
//	    double total_price = 0.0;
//	    char roomType[50];
//	    double roomPrice;
//	    char roomNum[20];
//	    // 每次循环读取一个房间信息
//	    while (fscanf(fp, "%s %s %lf",roomNum, roomType, &roomPrice) == 3) {
//	        total_price += roomPrice;
//	
//	        // 增加房间信息节点到客户的已定房间链表中
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
//	    // 创建新节点并插入链表
//	    insertCustomerNode(newCustomer);
//	}
//	
//	fclose(fp);
//
//
//
//    
//    // 加载酒店现有房型记录文件 
//    fp = fopen("room_info.txt", "r");
//    if (fp == NULL) {
//        printf("未找到房型信息文件，创建新文件!\n");
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

void displayCustomerInfo() //显示客户信息 
{
    Customer* current = customer_head;

    while (current != NULL) {
    
        printf("客户姓名: %s\n", current->name);
        printf("客户性别: %c\n", current->gender);
        printf("客户身份证号：%s\n",current->idcard);
        printf("客户电话: %s\n", current->phone);
        printf("入住日期: %s\n", current->check_in_date);
        printf("订房时间: %s\n", current->booking_time);
		printf("总金额: %.2lf\n", current->total_price);
        // 遍历客户已定房间的链表并显示房间信息
        CustomerRoomInfo* roomInfo = current->room_info;
        printf("客户已订房间信息:\n");
        while (roomInfo != NULL) {
            printf("房间号：%s, 房间类型: %s, 房间价格: %.2lf\n", roomInfo->room_num, roomInfo->room_type, roomInfo->room_price);
            roomInfo = roomInfo->next;
        }

        printf("--------------------\n");
        current = current->next;
    }
}

void bookRoom() //进行订房操作 
{
	// 订房时先展示现有房型 
	displayRoomTypes();
	 
    Customer newCustomer;
    newCustomer.room_info = NULL; // 初始化房间信息链表
	 
    printf("请输入姓名: ");
    scanf("%s", newCustomer.name);
    
    printf("请输入性别(M/F): ");
    scanf(" %c", &newCustomer.gender);
    
    printf("请输入身份证号: ");
    scanf(" %s", newCustomer.idcard);

    printf("请输入电话号码: ");
    scanf("%s", newCustomer.phone);

    printf("请输入入住日期: ");
    scanf("%s", newCustomer.check_in_date);
	
//	 订房时间为当前系统时间 
	time_t rawtime;
	struct tm *timeinfo;
    time(&rawtime);
	timeinfo = localtime(&rawtime);
	
    char bookingTime[200];  // 假设 booking_time 是一个 char 数组
	strftime(bookingTime, sizeof(bookingTime), "%Y-%m-%d-%H:%M:%S", timeinfo);
	
	sprintf(newCustomer.booking_time, "%s", bookingTime);
	

    // 连续输入多种房间类型信息，直到输入结束
    int moreRooms = 1;
    do {
        CustomerRoomInfo* newRoomInfo = (CustomerRoomInfo*)malloc(sizeof(CustomerRoomInfo));
        printf("房间号: ");
        scanf("%s", newRoomInfo->room_num);
		printf("请输入房间类型: ");
        scanf("%s", newRoomInfo->room_type);
        newRoomInfo->next = NULL;

        // 在链表中查找对应房间类型的房间信息
        HotelRoomInfo* currentRoom = hotel_room_head;
        while (currentRoom != NULL) {
            if (strcmp(currentRoom->room_type, newRoomInfo->room_type) == 0) {
                // 找到对应房间类型，更新客户的房间信息
                strcpy(newRoomInfo->room_type, currentRoom->room_type);
                newRoomInfo->room_price = currentRoom->room_price;
                
				newCustomer.total_price += currentRoom->room_price;
				currentRoom->remaining_rooms -= 1;
                // 添加房间信息到客户的房间信息链表中
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

        printf("还有更多房间要预订吗？(1-是，0-否): ");
        scanf("%d", &moreRooms);
    } while (moreRooms);

    // 将新的客户信息添加到客户信息链表中
    insertCustomerNode(newCustomer);

    // 将新的客户信息保存到文件
    saveCustomersToFile();
    saveRoomInfoToFile();
}

//退房
void checkOut(char *name) {
   Customer *current = customer_head;
   Customer *prev = NULL;

   // 遍历客户信息链表，找到对应的客户结点
   while (current != NULL) {
       if (strcmp(current->name, name) == 0) {
           // 如果找到了对应的客户结点，将其从链表中删除
           if (prev == NULL) {
               customer_head = current->next;
           } else {
               prev->next = current->next;
           }

           // 将客户结点的房间信息重新添加到酒店房间信息链表中
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

           // 更新客户结点的 checked_out 字段为 true
         //  current->checked_out = true;

           // 将客户结点的 total_price 字段清零
           current->total_price = 0;

           // 释放客户结点的内存
           free(current);

       }
       prev = current;
       current = current->next;
   }

   // 如果未找到对应的客户结点，输出错误信息
   printf("未找到客户 %s\n", name);
}
 

// 根据用户订房总金额从低到高进行排序 
void sortCustomersByTotalPrice() {
    if (customer_head == NULL || customer_head->next == NULL) {
        return; // 链表为空或只有一个节点，无需排序
    }

    int swapped;
    Customer *temp = NULL;

    do {
        swapped = 0;
        Customer *current = customer_head;
        while (current->next != NULL) {
            if (current->total_price > current->next->total_price) {
                // 交换节点位置
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

void Room_Menu()//打印功能菜单 
{
	printf("\n               ╔══════════════════════════════════╗\n");
		printf("               ║         酒店管理系统             ║\n");
		printf("               ╠══════════════════════════════════╣\n");
		printf("               ║ 1. 订房                          ║\n");
		printf("               ║ 2. 展示所有房型信息              ║\n");
		printf("               ║ 3. 添加房型信息                  ║\n");
		printf("               ║ 4. 删除房型信息                  ║\n");
		printf("               ║ 5. 展示用户订房信息              ║\n");
		printf("               ║ 6. 整理客户订房记录              ║\n");
		printf("               ║ 7. 退出                          ║\n");
		printf("               ║ 8. 退房                          ║\n"); 
		printf("               ║ 9. 娱乐项目                      ║\n"); 
		printf("               ╚══════════════════════════════════╝\n");
}
int main() {
    //loadRoomInfoFromFile(); 
    int choice;
    Room_Menu();
		printf("请选择操作: ");
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

                    printf("请输入要添加的房间类型: ");
                    scanf("%s", roomType);
                    printf("请输入价格: ");
                    scanf("%lf", &price);
                    printf("请输入总房间数: ");
                    scanf("%d", &totalRooms);

                    addRoomType(roomType, price, totalRooms, totalRooms);
                    //saveRoomInfoToFile(); // 保存到文件
                }
                break;
            case 4:
                {
                    char roomTypeToRemove[50];
                    printf("请输入要删除的房间类型: ");
                    scanf("%s", roomTypeToRemove);

                    removeRoomType(roomTypeToRemove);
                    saveRoomInfoToFile(); // 保存到文件
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
                saveRoomInfoToFile(); // 保存到文件
                exit(0);
//            case 8:
//            	char name[20];
//            	printf("请输入要退房的客户姓名：");
//            	scanf("%s",name);
//            	void checkOut(char *name);
//            	break;
			 case 9:
			 	entertainment();
			 	break;
            default:
                printf("无效的选择!\n");
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
	while(1)//功能选择 
	{
     Function_Menu();
		c = getch();
		switch(c)
		{
			case '1':
			    int pr;
			    char a[30];
			    int num;
			   	printf("请输入项目序号、名称和价格： \n"); 	
	            scanf("%d%s%d",&num,a,&pr);
	            if (num>0)
				  ps=Create(head,num,a,pr);
				  printf("\n按任何键两次返回主菜单\n");
				  getch();getch();    
				  break;
				  Function_Menu();
			case '2': 
			    int n;
				printf("请输入要删除的项目序号:");
                scanf("%d",&n); 
				Delete(ps,n);
				printf("\n按任何键两次返回主菜单\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '3': 
			    printf("请输入需要修改的项目序号：");
	            int e;
	            int y;
             	scanf("%d", &e);
	            if(e<=0)
		        printf("该序号无对应项目！\n");
		        else
		        printf("请选择修改对象：\n1：名称\n2：价格\n");
		        y= getch();
				Change(ps,e,y);
				printf("\n按任何键两次返回主菜单\n");
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
	            printf("排序成功！\n请打开菜单查看。");	
				printf("\n按任何键两次返回主菜单\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '5': 
			    int nu,r,pri;
			    char g[30],h[30];
			    printf("请输入序号、房间号、项目名称、预约日期和价格\n"); 	
	            scanf("%d%d%s%s%d",&nu,&r,g,h,&pri);
	            if (nu>0)
				Order(head1,nu,r,g,h,pri);
				printf("\n按任何键两次返回主菜单\n");
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
			          printf("请输入要查找的房间号");
			          scanf("%d",&o);
					  Search_sort(head1,o);
					  break;
			          case '2': output(head1);
					  break;
			          default: break;
	            	}
				printf("\n按任何键两次返回主菜单\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '7':
				system("cls"); 
			    Menu(ps);
			    printf("\n按任何键两次返回主菜单\n");
	            getch();getch();    
				break;
				Function_Menu();
			case '8' :
				system("cls"); 
				int k;
				output(head1);
				printf("请输入要删除的订单序号:");
                scanf("%d",&k); 
			    Order_delete(head1,k);
			    printf("\n按任何键两次返回主菜单\n");
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
  pro * q;//p结尾   q 新结点 
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
  printf("添加成功！是否要继续添加(y/n)\n");
  v=getch();
  while (v=='y')
  {
 printf("\n请输入项目序号、名称和价格： \n");
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
  link * q;//p结尾   q 新结点 
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
  printf("已选择%d个项目，一共%d元\n",nplus,sum);
  printf("是否要继续添加(y/n)\n");
  v=getch();
  while (v=='y')
  {
   printf("请输入序号、房间号、项目名称、预约日期和价格\n"); 	
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

void Function_Menu()//打印功能菜单 
{
	printf("\n\n\n\n");
	printf("\t\t\t\t                 ╭════════════════════╮                 \n");
	printf("\t\t\t\t╭════════════════╣酒店娱乐项目管理系统╠═════════════╮\n");
	printf("\t\t\t\t║                ╰════════════════════╯             ║\n");
	printf("\t\t\t\t║     【1】添加项目             【2】删除项目       ║\n");
	printf("\t\t\t\t║                                                   ║\n");
	printf("\t\t\t\t║     【3】修改项目             【4】项目排序       ║\n");
	printf("\t\t\t\t║                                                   ║\n");
	printf("\t\t\t\t║     【5】顾客选择项目         【6】排序查看订单   ║\n");
	printf("\t\t\t\t║                                                   ║\n");
	printf("\t\t\t\t║     【7】展示菜单             【8】删除订单       ║\n");
	printf("\t\t\t\t║                                                   ║\n");
	printf("\t\t\t\t║                   【0】退出系统                   ║\n");
	printf("\t\t\t\t╰═══════════════════════════════════════════════════╯\n");
	printf("\t\t\t\t\t◎请输入功能前的序号执行相应的功能:\n");
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

void Change(pro *head,int n,int a)//修改
{
	system("cls");
	pro *p = head->next;
	if (p == NULL) 
	{
		printf("系统中暂无项目信息！\n\n");
	}
		for( int i = 1; i < n; i++)
		      p = p->next;
		switch(a)
		{
			case '1': 
				system("cls");
				printf("请输入修改后的名称：\n");
				scanf("%s", p->name);
				getchar();
				break;
			case '2': 
				system("cls");
				printf("请输入修改后的价格：\n");
				scanf("%d",&p->pri);
				break;
			default: 
				system("cls");
				break;
		}
		system("cls");
		printf("项目信息修改成功！\n");
    }
	
void Menu(pro * head)//打印菜单 
{system("cls");
	int i = 1;
	pro * p = head->next;
	if (p== NULL) 
	{
		printf("系统中暂无项目信息，请录入后再查看。\n\n");
	}
	else 
	{
		printf("\t\t\t\t*********************************************************\n");
		printf("\t\t\t\t*\t\t\t欢迎光临本酒店  \t\t\t*\n");
		printf("\t\t\t\t*********************************************************\n");
		printf("\t\t\t\t*序号                 名称                    价格      *\n");
		printf("\t\t\t\t*********************************************************\n");
		while (p != NULL)
		{
			p->number = i;
	    printf("\t\t\t\t*% -3d                %-10s               ￥%-6d    *\n", i, p->name, p->pri);
	    printf("\t\t\t\t*********************************************************\n");
			p = p->next;
			i++; 
		}
		printf("\n\t\t\t\t\t\t  一共有%d个项目", i-1);
}
}

void Sort_choose(pro *head)//排序方式选择 
{
	system("cls");
	pro *p = head;
	if (p == NULL) 
	{
		printf("系统中暂无项目信息！\n\n");
	}
	else
	{ 
		printf("\n\n\n\n");
		printf("\t\t\t\t                 ╭════════════════╮                 \n");
		printf("\t\t\t\t╭════════════════╣    排序方式    ╠════════════════╮\n");
		printf("\t\t\t\t║                ╰════════════════╯                ║\n");
		printf("\t\t\t\t║     【1】按名称排序           【2】按价格降序    ║\n");
		printf("\t\t\t\t║                                                  ║\n");
		printf("\t\t\t\t╰══════════════════════════════════════════════════╯\n");
		printf("\t\t\t\t\t◎请输入序号选择相应的排序方式:");   
		 
	} 
}

void Name_sort(pro *head)//按序号排序 
{
	system("cls");
	int n = 0;
	int t,a;
	pro *p = head;
	char  b[30];
	while(p != NULL)//计算总数 
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

void Charge_sort(pro * head)//按价格排序 
{system("cls");
	pro *p = head;
	int n = 0;
	int a,t;
	char b[30];
		while(p != NULL)//计算项目总数 
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

void Order_choose(link *head1)//排序方式选择 
{
	system("cls");
	link*p = head1;
	if (p == NULL) 
	{
		printf("系统中暂无项目信息！\n\n");
	}
	else
	{ 
		printf("\n\n\n\n");
		printf("\t\t\t\t                 ╭════════════════╮                 \n");
		printf("\t\t\t\t╭════════════════╣    排序方式    ╠════════════════╮\n");
		printf("\t\t\t\t║                ╰════════════════╯                ║\n");
		printf("\t\t\t\t║         【1】查看具体房间预约项目                ║\n");
		printf("\t\t\t\t║                                                  ║\n");
		printf("\t\t\t\t║         【2】查看所有预约项目订单信息            ║\n");
		printf("\t\t\t\t║                                                  ║\n");
		printf("\t\t\t\t╰══════════════════════════════════════════════════╯\n");
		printf("\t\t\t\t\t◎请输入序号选择相应的排序方式:\n");   
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
	   printf("\t\t\t\t*\t\t  欢迎光临本酒店  \t\t\t*\n");
	   printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*序号     房间号        名称           日期      价格   *\n");
	   printf("\t\t\t\t*********************************************************\n");
		while (p1 != NULL)
		{
			p1->num = i;
	   printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ￥%-6d  *\n", i,p1->room,p1->kind,p1->date,p1->price);
	   printf("\t\t\t\t*********************************************************\n");
			p1 = p1->next;
			i++; 
		}
}
else
printf("该房间顾客暂未预约项目！\n");
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
    printf("删除成功！");
}

void output(link * head1)//打印订单 
{
	int i = 1;
	link * p = head1->next;
	if (p== NULL) 
	{
		printf("系统中暂无项目信息，请录入后再查看。\n\n");
	}
	else 
	{ 
		printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*\t\t  欢迎光临本酒店  \t\t\t*\n");
	   printf("\t\t\t\t*********************************************************\n");
	   printf("\t\t\t\t*序号     房间号        名称           日期      价格   *\n");
	   printf("\t\t\t\t*********************************************************\n");
		while (p != NULL)
		{
			p->num = i;
	   printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ￥%-6d  *\n", i,p->room,p->kind,p->date,p->price);
	   printf("\t\t\t\t*********************************************************\n");
			p = p->next;
			i++; 
		}
		printf("\n\t\t\t\t\t\t  一共有%d个项目", i-1);
}
}



