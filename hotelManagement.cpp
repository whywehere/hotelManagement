#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#define M 20			 // 设置密码位数为(M-1)
char correctPassword[M]; // 设置初始密码

bool authenticate() // 此函数用于验证密码,密码支持(M-1)位的字符
{
	FILE *fp = fopen("codeProject\\hotelManagement\\password.txt", "r");
	if (fp == NULL)
	{
		printf("无法打开文件或文件不存在\n");
	}
	else
	{
		fscanf(fp, "%s", correctPassword);
		fclose(fp);
	}
	int tryCount = 1;
	while (1)
	{
		if (tryCount <= 3)
		{
			char ch, password[M];
			int i = 0;
			printf("请输入密码:");
			while ((ch = getch()) != '\r' && i <= M)
			{
				if (ch == '\b')
				{
					if (i > 0)
					{
						i--;
						printf("\b \b"); // 密码支持退格的实现
					}
					else
						putchar(7);
				}
				else
				{
					password[i++] = ch;
					printf("*");
				}
			}
			password[i] = '\0';
			if (!strcmp(password, correctPassword))
			{
				printf("\n密码正确         请继续操作\n");
				return true;
			}
			else
			{
				printf("\n密码错误        您还有%d次机会\n", 3 - tryCount);
			}
		}
		else
		{
			printf("\n密码均错误        无法继续操作!\n");
			return false;
		}
		tryCount++;
	}
}

void changethepassword() // 该函数用于修改系统密码
{
	char ch1, ch2, password[M], repeatPassword[M];
	int i = 0, j = 0;
	do
	{
		i = 0, j = 0;
		printf("请输入新密码\n");
		while ((ch1 = getch()) != '\r' && i <= M)
		{
			if (ch1 == '\b')
			{
				if (i > 0)
				{
					i--;
					printf("\b \b"); // 密码支持退格的实现
				}
				else
					putchar(7);
			}
			else
			{
				password[i++] = ch1;
				printf("*");
			}
		}
		password[i] = '\0';
		printf("\n请确认新密码\n");
		while ((ch2 = getch()) != '\r' && j <= M)
		{
			if (ch2 == '\b')
			{
				if (j > 0)
				{
					j--;
					printf("\b \b"); // 密码支持退格的实现
				}
				else
					putchar(7);
			}
			else
			{
				repeatPassword[j++] = ch2;
				printf("*");
			}
		}
		repeatPassword[j] = '\0';
		if (strcmp(password, repeatPassword) == 0)
		{
			printf("\n密码修改成功！\n");
			break;
		}
		printf("\n两次输入密码不同，请再设置一遍\n");
	} while (1);
	strcpy(correctPassword, password);
	FILE *fp = fopen("password.txt", "w");
	if (fp == NULL)
	{
		printf("无法打开密码文件!\n");
		return;
	}
	// 写入密码到文件中
	fprintf(fp, "%s", correctPassword);
	fclose(fp);
}
// 定义酒店现有房间信息结构体
typedef struct HotelRoomInfo
{
	char room_type[50];			// 房间类型
	double room_price;			// 房间价格
	int total_rooms;			// 总房间数
	int remaining_rooms;		// 剩余房间数
	struct HotelRoomInfo *next; // 指向下一个房间信息节点的指针
} HotelRoomInfo;

// 定义客户已订房间信息结构体
typedef struct CustomerRoomInfo
{
	char room_num[50];			   // 房间号
	char room_type[50];			   // 房间类型
	double room_price;			   // 房间价格
	struct CustomerRoomInfo *next; // 指向下一个客户房间信息节点的指针
} CustomerRoomInfo;

// 定义客户信息结构体
typedef struct Customer
{
	char name[100];				 // 客户姓名
	char gender;				 // 客户性别
	char idcard[100];			 // 客户身份证
	char phone[20];				 // 客户电话
	char check_in_date[20];		 // 客户入住日期
	CustomerRoomInfo *room_info; // 指向客户已定房间信息的指针
	char booking_time[80];		 // 订房时间
	double total_price;			 // 订房总价
	struct Customer *next;		 // 指向下一个客户信息节点的指针
	int bookedRooms;			 // 订房数量
} Customer;

Customer *customer_head = NULL; // 指向客户信息链表头节点

HotelRoomInfo *hotel_room_head = NULL; // 指向酒店房间信息链表头节点

typedef struct Order
{
	int id;
	int roomNumber;
	char kind[30];
	char date[30];
	int price;
	struct Order *next;
} Order;

Order *order_head = NULL;

typedef struct Project
{
	int id;
	char name[30];
	int price;
	struct Project *next;
} Project;

Project *entertainment_head = NULL; // 指向酒店房间信息链表头节点

void Room_Menu();																		   // 打印主菜单
void addRoomType(const char *roomType, double price, int totalRooms, int remaining_rooms); // 添加房型信息到链表中
void removeRoomType(const char *roomType);												   // 删除房型
void saveRoomInfoToFile();																   // 将房型存入文件
void displayRoomTypes();																   // 展示房型信息
void insertCustomerNode(Customer newCustomer);
void saveCustomersToFile();		  // 将客户信息保存到文件
void loadInfoFromFile();		  // 从文件加载房型信息和客户订房记录
void displayCustomerInfo();		  // 显示客户信息
void bookRoom();				  // 进行订房操作
void checkOut(char *idCard);	  // 退房
void sortCustomersByTotalPrice(); // 根据用户订房总金额从低到高进行排序

void entertainment();						// 预定娱乐功能子模块
void Create(int id, char *name, int price); // 创建娱乐项目
void insertNewEntertainment(Project *newEntertainment);
void saveEntertainmentToFile();
void insertNewOrderNode(Order *newOrderNode);
void newOrder(int id, int roomNumber, char *kind, char *data, int price);
void Function_Menu();
void Delete(int id);
void Change(int id, int choice);
void Menu();
void Sort_choose();
void Name_sort();
void Charge_sort();
void Order_choose();
void Search_sort(int roomNumber);
void Order_delete(int id);
void output();
int sum = 0;
int nplus = 0;

// 添加房型信息到链表中
void addRoomType(const char *roomType, double price, int totalRooms, int remaining_rooms)
{
	HotelRoomInfo *newRoom = (HotelRoomInfo *)malloc(sizeof(HotelRoomInfo));

	strcpy(newRoom->room_type, roomType);
	newRoom->room_price = price;
	newRoom->total_rooms = totalRooms;
	newRoom->remaining_rooms = remaining_rooms;
	newRoom->next = NULL;

	if (hotel_room_head == NULL)
	{
		hotel_room_head = newRoom;
	}
	else
	{
		// 遍历到链表尾部 将新数据插入到链表尾部
		HotelRoomInfo *current = hotel_room_head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newRoom;
	}
}
// 删除房型
void removeRoomType(const char *roomType)
{
	HotelRoomInfo *current = hotel_room_head;
	HotelRoomInfo *prev = NULL; // prev为指向前一个结点的指针

	while (current != NULL)
	{
		if (strcmp(current->room_type, roomType) == 0)
		{ // 如果为要删除的房间类型
			if (prev == NULL)
			{
				hotel_room_head = current->next;
			}
			else
			{
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
void saveRoomInfoToFile()
{
	FILE *fp = fopen("room_info.txt", "w");
	if (fp == NULL)
	{
		printf("无法创建房型信息文件!\n");
		return;
	}

	HotelRoomInfo *current = hotel_room_head; // 遍历链表, 将每个结点数据依次存入文件
	while (current != NULL)
	{
		fprintf(fp, "%s %.2lf %d %d\n", current->room_type, current->room_price, current->total_rooms, current->remaining_rooms);
		current = current->next;
	}

	fclose(fp);
	printf("成功保存房型信息到文件!\n");
}

// 展示所有房型信息
void displayRoomTypes()
{
	HotelRoomInfo *current = hotel_room_head;

	printf("所有房型信息:\n");
	while (current != NULL)
	{
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
	Customer *newNode = (Customer *)malloc(sizeof(Customer));
	*newNode = newCustomer;
	newNode->next = NULL;

	// 如果链表为空，将新节点作为头节点
	if (customer_head == NULL)
	{
		customer_head = newNode;
		return;
	}

	// 遍历链表找到最后一个节点，并将新节点插入末尾
	Customer *current = customer_head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = newNode;
}

void saveCustomersToFile() // 将客户信息保存到文件
{
	FILE *fp = fopen("customers.txt", "w");
	if (fp == NULL)
	{
		printf("无法创建客户信息文件!\n");
		return;
	}

	Customer *current = customer_head;
	while (current != NULL)
	{
		fprintf(fp, "%s %c %s %s %s %s %.2lf %d\n", current->name, current->gender, current->idcard, current->phone, current->check_in_date, current->booking_time, current->total_price, current->bookedRooms);

		// 遍历客户已定房间的链表并将相关信息存储到文件中
		CustomerRoomInfo *roomInfo = current->room_info;
		while (roomInfo != NULL)
		{
			fprintf(fp, "%s %s %.2lf\n", roomInfo->room_num, roomInfo->room_type, roomInfo->room_price);
			roomInfo = roomInfo->next;
		}
		current = current->next;
	}

	fclose(fp);
	printf("成功保存客户信息到文件!\n");
}

// 从文件加载房型信息和客户订房记录
void loadInfoFromFile()
{
	// 加载客户订房记录文件
	FILE *fp = fopen("customers.txt", "r");
	if (fp == NULL)
	{
		printf("未找到客户信息文件，创建新文件!\n");
		return;
	}

	while (!feof(fp))
	{
		Customer newCustomer;

		// 读取基本客户信息
		int result = fscanf(fp, "%s %c %s %s %s %s  %lf %d\n",
							newCustomer.name,
							&newCustomer.gender,
							newCustomer.idcard,
							newCustomer.phone,
							newCustomer.check_in_date,
							newCustomer.booking_time,
							&newCustomer.total_price,
							&newCustomer.bookedRooms);

		// 初始化客户已定房间链表头
		newCustomer.room_info = NULL;

		// 读取房间信息和总价
		char roomType[50];
		double roomPrice;
		char roomNum[20];
		// 每次循环读取一个房间信息
		for (int i = 1; i <= newCustomer.bookedRooms; i++)
		{
			result = fscanf(fp, "%s %s %lf\n", roomNum, roomType, &roomPrice);
			// 增加房间信息节点到客户的已定房间链表中
			CustomerRoomInfo *newRoom = (CustomerRoomInfo *)malloc(sizeof(CustomerRoomInfo));
			strcpy(newRoom->room_num, roomNum);
			strcpy(newRoom->room_type, roomType);
			newRoom->room_price = roomPrice;
			newRoom->next = NULL;
			if (newCustomer.room_info == NULL)
			{
				newCustomer.room_info = newRoom;
			}
			else
			{
				CustomerRoomInfo *temp = newCustomer.room_info;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = newRoom;
			}
			// 创建新节点并插入链表
		}
		insertCustomerNode(newCustomer);
	}
	fclose(fp);

	// 加载酒店现有房型记录文件
	fp = fopen("room_info.txt", "r");
	if (fp == NULL)
	{
		printf("未找到房型信息文件，创建新文件!\n");
		return;
	}

	while (!feof(fp))
	{
		char roomType[50];
		double price;
		int totalRooms, remainingRooms;

		if (fscanf(fp, "%s %lf %d %d\n", roomType, &price, &totalRooms, &remainingRooms) == 4)
		{
			addRoomType(roomType, price, totalRooms, remainingRooms);
		}
	}
	fclose(fp);

	// 加载娱乐项目记录文件
	fp = fopen("entertainment_info.txt", "r");
	if (fp == NULL)
	{
		printf("未找到娱乐项目记录文件，创建新文件!\n");
		return;
	}
	while (!feof(fp))
	{
		Project *newNode = (Project *)malloc(sizeof(Project));
		if (fscanf(fp, "%d %s %d", &newNode->id, newNode->name, &newNode->price) == 3)
		{
			insertNewEntertainment(newNode);
		}
	}
	fclose(fp);
}

void displayCustomerInfo() // 显示客户信息
{
	Customer *current = customer_head;

	while (current != NULL)
	{

		printf("客户姓名: %s\n", current->name);
		printf("客户性别: %c\n", current->gender);
		printf("客户身份证号：%s\n", current->idcard);
		printf("客户电话: %s\n", current->phone);
		printf("入住日期: %s\n", current->check_in_date);
		printf("订房时间: %s\n", current->booking_time);
		printf("总金额: %.2lf\n", current->total_price);
		// 遍历客户已定房间的链表并显示房间信息
		CustomerRoomInfo *roomInfo = current->room_info;
		printf("客户已订房间信息:\n");
		while (roomInfo != NULL)
		{
			printf("房间号：%s, 房间类型: %s, 房间价格: %.2lf\n", roomInfo->room_num, roomInfo->room_type, roomInfo->room_price);
			roomInfo = roomInfo->next;
		}

		printf("--------------------\n");
		current = current->next;
	}
}

void bookRoom() // 进行订房操作
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
	newCustomer.bookedRooms = 0;

	// 订房时间为当前系统时间
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char bookingTime[200]; // 假设 booking_time 是一个 char 数组
	strftime(bookingTime, sizeof(bookingTime), "%Y-%m-%d-%H:%M:%S", timeinfo);

	sprintf(newCustomer.booking_time, "%s", bookingTime);

	// 连续输入多种房间类型信息，直到输入结束
	int moreRooms = 1;
	do
	{
		CustomerRoomInfo *newRoomInfo = (CustomerRoomInfo *)malloc(sizeof(CustomerRoomInfo));
		printf("请输入房间类型: ");
		scanf("%s", newRoomInfo->room_type);

		printf("请输入房间号: ");
		scanf("%s", newRoomInfo->room_num);
		newRoomInfo->next = NULL;

		// 在链表中查找对应房间类型的房间信息
		HotelRoomInfo *currentRoom = hotel_room_head;
		while (currentRoom != NULL)
		{
			if (strcmp(currentRoom->room_type, newRoomInfo->room_type) == 0)
			{
				// 找到对应房间类型，更新客户的房间信息
				strcpy(newRoomInfo->room_type, currentRoom->room_type);
				newRoomInfo->room_price = currentRoom->room_price;

				newCustomer.total_price += currentRoom->room_price;
				currentRoom->remaining_rooms -= 1;
				// 添加房间信息到客户的房间信息链表中
				if (newCustomer.room_info == NULL)
				{
					newCustomer.room_info = newRoomInfo;
				}
				else
				{
					CustomerRoomInfo *current = newCustomer.room_info;
					while (current->next != NULL)
					{
						current = current->next;
					}
					current->next = newRoomInfo;
				}
				break;
			}
			currentRoom = currentRoom->next;
		}
		newCustomer.bookedRooms++;
		printf("还有更多房间要预订吗？(1-是，0-否): ");
		scanf("%d", &moreRooms);
	} while (moreRooms);

	// 将新的客户信息添加到客户信息链表中
	insertCustomerNode(newCustomer);

	// 将新的客户信息保存到文件
	saveCustomersToFile();
	saveRoomInfoToFile();
}

// 退房（根据身份证退房）
void checkOut(char *idCard)
{
	Customer *current = customer_head;
	Customer *prev = NULL;
	while (current != NULL)
	{
		// 如果找到了对应的客户结点，将其从链表中删除
		if (strcmp(current->idcard, idCard) == 0)
		{
			// 删除结点为头结点
			if (prev == NULL)
			{
				customer_head = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			// 释放删除结点
			// 1.释放客户订房链表
			CustomerRoomInfo *currentRoomInfo = current->room_info;
			while (currentRoomInfo != NULL)
			{
				// 将退房的房间类型 + 1
				HotelRoomInfo *currentRoom = hotel_room_head;
				while (currentRoom != NULL)
				{
					if (strcmp(currentRoom->room_type, currentRoomInfo->room_type) == 0)
					{
						currentRoom->remaining_rooms += 1;
						break;
					}
					currentRoom = currentRoom->next;
				}
				CustomerRoomInfo *tempCurrentRoomInfo = currentRoomInfo;
				currentRoomInfo = currentRoomInfo->next;
				free(tempCurrentRoomInfo);
			}
			// 2.释放客户订房结点
			free(current);
			printf("客户 %s 退房成功\n", current->name);
			saveCustomersToFile();
			return;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	printf("未找到改用户信息: %s", idCard);
}

// 根据用户订房总金额从低到高进行排序
void sortCustomersByTotalPrice()
{
	if (customer_head == NULL || customer_head->next == NULL)
	{
		return; // 链表为空或只有一个节点，无需排序
	}

	int swapped;
	Customer *temp = NULL;

	do
	{
		swapped = 0;
		Customer *current = customer_head;
		while (current->next != NULL)
		{
			if (current->total_price > current->next->total_price)
			{
				// 交换节点位置
				if (current == customer_head)
				{
					customer_head = current->next;
				}
				else
				{
					temp->next = current->next;
				}

				temp = current->next;
				current->next = temp->next;
				temp->next = current;
				swapped = 1;
			}
			else
			{
				temp = current;
				current = current->next;
			}
		}
	} while (swapped);
}

void Room_Menu() // 打印功能菜单
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
	printf("               ║ 7. 退房                        ║\n");
	printf("               ║ 8. 娱乐项目                     ║\n");
	printf("               ║ 9.修改登录密码                    ║\n");
	printf("               ║ 0. 退出                        ║\n");
	printf("               ╚══════════════════════════════════╝\n");
}

int main()
{
	bool authenticated = false;
	// 循环直到验证通过
	do
	{
		authenticated = authenticate();
	} while (!authenticated);
	loadInfoFromFile();
	int choice;
	do
	{
		Room_Menu();
		printf("请选择操作: ");
		scanf("%d", &choice);
		switch (choice)
		{
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
			// saveRoomInfoToFile(); // 保存到文件
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
			char idCard[20];
			printf("请输入要退房的客户身份证：");
			scanf("%s", idCard);
			checkOut(idCard);
			break;
		case 8:
			entertainment();
			break;
		case 9:
			changethepassword();
			break;
		case 0:
			saveRoomInfoToFile(); // 保存到文件
			exit(0);
		default:
			printf("无效的选择!\n");
		}
	} while (choice != 0);
	system("pause");
	return 0;
}

void entertainment()
{
	char choice;
	while (1) // 功能选择
	{
		Function_Menu();
		choice = getch();
		switch (choice)
		{
		case '1':
			int price;
			char name[30];
			int id;
			printf("请输入项目序号、名称和价格： \n");
			scanf("%d%s%d", &id, name, &price);
			Create(id, name, price);
			saveEntertainmentToFile();
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '2':
			int id;
			printf("请输入要删除的项目序号:");
			scanf("%d", &id);
			Delete(id);
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '3':
			printf("请输入需要修改的项目序号：");
			int id, choice;
			scanf("%d", &id);
			printf("请选择修改对象：\n1：名称\n2：价格\n");
			choice = getch();
			Change(id, choice);
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '4':
			char c;
			Sort_choose();
			c = getch();
			switch (c)
			{
			case '1':
				Name_sort();
				break;
			case '2':
				Charge_sort();
				break;
			default:
				break;
			}
			printf("排序成功！\n请打开菜单查看。");
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '5':
			int id, roomNumber, price;
			char g[30], h[30];
			Menu();
			printf("请输入序号、房间号、项目名称、预约日期和价格\n");
			scanf("%d%d%s%s%d", &id, &roomNumber, g, h, &price);
			if (id > 0)
				newOrder(id, roomNumber, g, h, price);
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '6':
			int roomNumber;
			Order_choose();
			char choice = getch();
			switch (choice)
			{
			case '1':
				printf("请输入要查找的房间号");
				scanf("%d", &roomNumber);
				Search_sort(roomNumber);
				break;
			case '2':
				output();
				break;
			default:
				break;
			}
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '7':
			system("cls");
			Menu();
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;

		case '8':
			system("cls");
			int id;
			output();
			printf("请输入要删除的订单序号:");
			scanf("%d", &id);
			Order_delete(id);
			printf("\n按任何键两次返回主菜单\n");
			getch();
			getch();
			break;
		case '0':
			system("cls");
			return; // 直接退出函数
		}
	}
}

void saveEntertainmentToFile()
{
	FILE *fp = fopen("entertainment_info.txt", "w");
	if (fp == NULL)
	{
		printf("无法创建 entertainment_info.txt 文件");
		return;
	}
	Project *current = entertainment_head;
	while (current != NULL)
	{
		fprintf(fp, "%d %s %d\n", current->id, current->name, current->price);
		current = current->next;
	}
	fclose(fp);
	printf("成功保存娱乐项目信息到文件！\n");
}
void insertNewEntertainment(Project *newEntertainment)
{
	Project *current = entertainment_head;
	if (entertainment_head == NULL)
	{
		entertainment_head = newEntertainment;
		return;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = newEntertainment;
}
void Create(int num, char *a, int pr)
{
	Project *p = entertainment_head;
	Project *newNode = (Project *)malloc(sizeof(Project));
	strcpy(newNode->name, a);
	newNode->price = pr;
	newNode->id = num;
	newNode->next = NULL;
	insertNewEntertainment(newNode);
	printf("添加成功！是否要继续添加(y/n)\n");
	char v = getch();
	while (v == 'y')
	{
		printf("\n请输入项目序号、名称和价格： \n");
		scanf("%d%s%d", &num, a, &pr);
		Create(num, a, pr);
		break;
	}
}

void insertNewOrderNode(Order *newOrderNode)
{
	Order *current = order_head;
	if (order_head == NULL)
	{
		order_head = newOrderNode;
		return;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = newOrderNode;
}
void newOrder(int id, int roomNumber, char *kind, char *date, int price)
{
	Order *newNode = (Order *)malloc(sizeof(Order));
	Order *current = order_head;
	newNode->id = id;
	newNode->roomNumber = roomNumber;
	strcpy(newNode->kind, kind);
	strcpy(newNode->date, date);
	newNode->price = price;
	sum += price;
	newNode->next = NULL;
	insertNewOrderNode(newNode);
	nplus++;
	printf("已选择%d个项目，一共%d元\n", nplus, sum);
	printf("是否要继续添加(y/n)\n");
	char v = getch();
	while (v == 'y')
	{
		printf("请输入序号、房间号、项目名称、预约日期和价格\n");
		scanf("%d%d%s%s%d", &id, &roomNumber, kind, date, &price);
		if (id > 0)
		{
			newOrder(id, roomNumber, kind, date, price);
		}
		break;
	}
	nplus = 0;
	sum = 0;
}

void Function_Menu() // 打印功能菜单
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

void Delete(int id)
{
	Project *prev = NULL;
	Project *current = entertainment_head;
	while (current != NULL)
	{
		if (current->id == id)
		{
			if (prev == NULL)
			{
				entertainment_head = current->next;
				free(current);
			}
			else
			{
				prev->next = current->next;
				free(current);
			}
			return;
		}
		prev = current;
		current = current->next;
	}
}

void Change(int id, int choice)
{
	Project *current = entertainment_head;
	if (current == NULL)
	{
		printf("系统中暂无项目信息！\n\n");
		return;
	}
	while (current != NULL)
	{
		if (id == current->id)
		{
			if (choice == 1)
			{
				printf("请输入修改后的名称：\n");
				scanf("%s", current->name);
			}
			else
			{
				printf("请输入修改后的价格：\n");
				scanf("%d", &current->price);
			}
			return;
		}
		current = current->next;
	}
	printf("项目信息修改成功！\n");
}

void Menu() // 打印菜单
{
	system("cls");
	Project *current = entertainment_head;
	int count = 0;
	if (entertainment_head == NULL)
	{
		printf("系统中暂无项目信息，请录入后再查看。\n\n");
		return;
	}
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*\t\t\t欢迎光临本酒店  \t\t\t*\n");
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*序号                 名称                    价格      *\n");
	printf("\t\t\t\t*********************************************************\n");
	while (current != NULL)
	{
		printf("\t\t\t\t*% -3d                %-10s               ￥%-6d    *\n", current->id, current->name, current->price);
		printf("\t\t\t\t*********************************************************\n");
		printf("\t\t\t\t*********************************************************\n");
		current = current->next;
		count++;
	}
	printf("\n\t\t\t\t\t\t  一共有%d个项目", count);
}

void Sort_choose() // 排序方式选择
{
	system("cls");
	Project *current = entertainment_head;
	if (current == NULL)
	{
		printf("系统中暂无项目信息！\n\n");
		return;
	}
	printf("\n\n\n\n");
	printf("\t\t\t\t                 ╭════════════════╮                 \n");
	printf("\t\t\t\t╭════════════════╣    排序方式    ╠════════════════╮\n");
	printf("\t\t\t\t║                ╰════════════════╯                ║\n");
	printf("\t\t\t\t║     【1】按名称排序           【2】按价格降序    ║\n");
	printf("\t\t\t\t║                                                  ║\n");
	printf("\t\t\t\t╰══════════════════════════════════════════════════╯\n");
	printf("\t\t\t\t\t◎请输入序号选择相应的排序方式:");
}

void Name_sort() // 按序号排序
{
	system("cls");
	Project *current = entertainment_head;
	int n = 0;
	while (current != NULL)
	{
		current = current->next;
		n++;
	}
	for (int i = 1; i < n; i++)
	{
		current = entertainment_head;
		for (int j = 0; j < n - i; j++)
		{
			if (strcmp(current->name, current->next->name) > 0)
			{
				int id = current->id;
				current->id = current->next->id;
				current->next->id = id;
				char name[50];
				strcpy(name, current->name);
				strcpy(current->name, current->next->name);
				strcpy(current->next->name, name);
				int price = current->price;
				current->price = current->next->price;
				current->next->price = price;
			}
			current = current->next;
		}
	}
}

void Charge_sort() // 按价格排序
{
	system("cls");
	Project *current = entertainment_head;
	int n = 0;
	while (current != NULL)
	{
		current = current->next;
		n++;
	}
	for (int i = 1; i < n; i++)
	{
		current = entertainment_head;
		for (int j = 0; j < n - i; j++)
		{
			if (current->price < current->next->price)
			{
				int id = current->id;
				current->id = current->next->id;
				current->next->id = id;
				char name[50];
				strcpy(name, current->name);
				strcpy(current->name, current->next->name);
				strcpy(current->next->name, name);
				int price = current->price;
				current->price = current->next->price;
				current->next->price = price;
			}
			current = current->next;
		}
	}
}

void Order_choose() // 排序方式选择
{
	system("cls");
	Order *current = order_head;
	if (order_head == NULL)
	{
		printf("系统中暂无项目信息！\n\n");
		return;
	}

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

void Search_sort(int roomNumber)
{
	system("cls");
	Order *current = order_head;
	while (current != NULL)
	{
		if (current->roomNumber == roomNumber)
		{
			printf("\t\t\t\t*********************************************************\n");
			printf("\t\t\t\t*\t\t  欢迎光临本酒店  \t\t\t*\n");
			printf("\t\t\t\t*********************************************************\n");
			printf("\t\t\t\t*序号     房间号        名称           日期      价格   *\n");
			printf("\t\t\t\t*********************************************************\n");
			printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ￥%-6d  *\n", current->id, current->roomNumber, current->kind, current->date, current->price);
			printf("\t\t\t\t*********************************************************\n");
			return;
		}
	}
	printf("该房间顾客暂未预约项目！\n");
}

void Order_delete(int id)
{
	system("cls");
	Order *prev = NULL;
	Order *current = order_head;
	while (current != NULL)
	{
		if (current->id = id)
		{
			if (prev == NULL)
			{
				order_head = NULL;
			}
			else
			{
				prev->next = current->next;
			}
			free(current);
			return;
		}
		current = current->next;
	}
	printf("删除成功！");
}

void output() // 打印订单
{
	Order *current = order_head;
	if (order_head == NULL)
	{
		printf("系统中暂无项目信息，请录入后再查看。\n\n");
		return;
	}
	int count = 0;
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*\t\t  欢迎光临本酒店  \t\t\t*\n");
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*序号     房间号        名称           日期      价格   *\n");
	printf("\t\t\t\t*********************************************************\n");
	while (current != NULL)
	{
		printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ￥%-6d  *\n", current->id, current->roomNumber, current->kind, current->date, current->price);
		printf("\t\t\t\t*********************************************************\n");
		current = current->next;
		count++;
	}
	printf("\n\t\t\t\t\t\t  一共有%d条订单", count);
}