#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#define M 20			 // ��������λ��Ϊ(M-1)
char correctPassword[M]; // ���ó�ʼ����

bool authenticate() // �˺���������֤����,����֧��(M-1)λ���ַ�
{
	FILE *fp = fopen("codeProject\\hotelManagement\\password.txt", "r");
	if (fp == NULL)
	{
		printf("�޷����ļ����ļ�������\n");
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
			printf("����������:");
			while ((ch = getch()) != '\r' && i <= M)
			{
				if (ch == '\b')
				{
					if (i > 0)
					{
						i--;
						printf("\b \b"); // ����֧���˸��ʵ��
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
				printf("\n������ȷ         ���������\n");
				return true;
			}
			else
			{
				printf("\n�������        ������%d�λ���\n", 3 - tryCount);
			}
		}
		else
		{
			printf("\n���������        �޷���������!\n");
			return false;
		}
		tryCount++;
	}
}

void changethepassword() // �ú��������޸�ϵͳ����
{
	char ch1, ch2, password[M], repeatPassword[M];
	int i = 0, j = 0;
	do
	{
		i = 0, j = 0;
		printf("������������\n");
		while ((ch1 = getch()) != '\r' && i <= M)
		{
			if (ch1 == '\b')
			{
				if (i > 0)
				{
					i--;
					printf("\b \b"); // ����֧���˸��ʵ��
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
		printf("\n��ȷ��������\n");
		while ((ch2 = getch()) != '\r' && j <= M)
		{
			if (ch2 == '\b')
			{
				if (j > 0)
				{
					j--;
					printf("\b \b"); // ����֧���˸��ʵ��
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
			printf("\n�����޸ĳɹ���\n");
			break;
		}
		printf("\n�����������벻ͬ����������һ��\n");
	} while (1);
	strcpy(correctPassword, password);
	FILE *fp = fopen("password.txt", "w");
	if (fp == NULL)
	{
		printf("�޷��������ļ�!\n");
		return;
	}
	// д�����뵽�ļ���
	fprintf(fp, "%s", correctPassword);
	fclose(fp);
}
// ����Ƶ����з�����Ϣ�ṹ��
typedef struct HotelRoomInfo
{
	char room_type[50];			// ��������
	double room_price;			// ����۸�
	int total_rooms;			// �ܷ�����
	int remaining_rooms;		// ʣ�෿����
	struct HotelRoomInfo *next; // ָ����һ��������Ϣ�ڵ��ָ��
} HotelRoomInfo;

// ����ͻ��Ѷ�������Ϣ�ṹ��
typedef struct CustomerRoomInfo
{
	char room_num[50];			   // �����
	char room_type[50];			   // ��������
	double room_price;			   // ����۸�
	struct CustomerRoomInfo *next; // ָ����һ���ͻ�������Ϣ�ڵ��ָ��
} CustomerRoomInfo;

// ����ͻ���Ϣ�ṹ��
typedef struct Customer
{
	char name[100];				 // �ͻ�����
	char gender;				 // �ͻ��Ա�
	char idcard[100];			 // �ͻ����֤
	char phone[20];				 // �ͻ��绰
	char check_in_date[20];		 // �ͻ���ס����
	CustomerRoomInfo *room_info; // ָ��ͻ��Ѷ�������Ϣ��ָ��
	char booking_time[80];		 // ����ʱ��
	double total_price;			 // �����ܼ�
	struct Customer *next;		 // ָ����һ���ͻ���Ϣ�ڵ��ָ��
	int bookedRooms;			 // ��������
} Customer;

Customer *customer_head = NULL; // ָ��ͻ���Ϣ����ͷ�ڵ�

HotelRoomInfo *hotel_room_head = NULL; // ָ��Ƶ귿����Ϣ����ͷ�ڵ�

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

Project *entertainment_head = NULL; // ָ��Ƶ귿����Ϣ����ͷ�ڵ�

void Room_Menu();																		   // ��ӡ���˵�
void addRoomType(const char *roomType, double price, int totalRooms, int remaining_rooms); // ��ӷ�����Ϣ��������
void removeRoomType(const char *roomType);												   // ɾ������
void saveRoomInfoToFile();																   // �����ʹ����ļ�
void displayRoomTypes();																   // չʾ������Ϣ
void insertCustomerNode(Customer newCustomer);
void saveCustomersToFile();		  // ���ͻ���Ϣ���浽�ļ�
void loadInfoFromFile();		  // ���ļ����ط�����Ϣ�Ϳͻ�������¼
void displayCustomerInfo();		  // ��ʾ�ͻ���Ϣ
void bookRoom();				  // ���ж�������
void checkOut(char *idCard);	  // �˷�
void sortCustomersByTotalPrice(); // �����û������ܽ��ӵ͵��߽�������

void entertainment();						// Ԥ�����ֹ�����ģ��
void Create(int id, char *name, int price); // ����������Ŀ
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

// ��ӷ�����Ϣ��������
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
		// ����������β�� �������ݲ��뵽����β��
		HotelRoomInfo *current = hotel_room_head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newRoom;
	}
}
// ɾ������
void removeRoomType(const char *roomType)
{
	HotelRoomInfo *current = hotel_room_head;
	HotelRoomInfo *prev = NULL; // prevΪָ��ǰһ������ָ��

	while (current != NULL)
	{
		if (strcmp(current->room_type, roomType) == 0)
		{ // ���ΪҪɾ���ķ�������
			if (prev == NULL)
			{
				hotel_room_head = current->next;
			}
			else
			{
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
void saveRoomInfoToFile()
{
	FILE *fp = fopen("room_info.txt", "w");
	if (fp == NULL)
	{
		printf("�޷�����������Ϣ�ļ�!\n");
		return;
	}

	HotelRoomInfo *current = hotel_room_head; // ��������, ��ÿ������������δ����ļ�
	while (current != NULL)
	{
		fprintf(fp, "%s %.2lf %d %d\n", current->room_type, current->room_price, current->total_rooms, current->remaining_rooms);
		current = current->next;
	}

	fclose(fp);
	printf("�ɹ����淿����Ϣ���ļ�!\n");
}

// չʾ���з�����Ϣ
void displayRoomTypes()
{
	HotelRoomInfo *current = hotel_room_head;

	printf("���з�����Ϣ:\n");
	while (current != NULL)
	{
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
	Customer *newNode = (Customer *)malloc(sizeof(Customer));
	*newNode = newCustomer;
	newNode->next = NULL;

	// �������Ϊ�գ����½ڵ���Ϊͷ�ڵ�
	if (customer_head == NULL)
	{
		customer_head = newNode;
		return;
	}

	// ���������ҵ����һ���ڵ㣬�����½ڵ����ĩβ
	Customer *current = customer_head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = newNode;
}

void saveCustomersToFile() // ���ͻ���Ϣ���浽�ļ�
{
	FILE *fp = fopen("customers.txt", "w");
	if (fp == NULL)
	{
		printf("�޷������ͻ���Ϣ�ļ�!\n");
		return;
	}

	Customer *current = customer_head;
	while (current != NULL)
	{
		fprintf(fp, "%s %c %s %s %s %s %.2lf %d\n", current->name, current->gender, current->idcard, current->phone, current->check_in_date, current->booking_time, current->total_price, current->bookedRooms);

		// �����ͻ��Ѷ�����������������Ϣ�洢���ļ���
		CustomerRoomInfo *roomInfo = current->room_info;
		while (roomInfo != NULL)
		{
			fprintf(fp, "%s %s %.2lf\n", roomInfo->room_num, roomInfo->room_type, roomInfo->room_price);
			roomInfo = roomInfo->next;
		}
		current = current->next;
	}

	fclose(fp);
	printf("�ɹ�����ͻ���Ϣ���ļ�!\n");
}

// ���ļ����ط�����Ϣ�Ϳͻ�������¼
void loadInfoFromFile()
{
	// ���ؿͻ�������¼�ļ�
	FILE *fp = fopen("customers.txt", "r");
	if (fp == NULL)
	{
		printf("δ�ҵ��ͻ���Ϣ�ļ����������ļ�!\n");
		return;
	}

	while (!feof(fp))
	{
		Customer newCustomer;

		// ��ȡ�����ͻ���Ϣ
		int result = fscanf(fp, "%s %c %s %s %s %s  %lf %d\n",
							newCustomer.name,
							&newCustomer.gender,
							newCustomer.idcard,
							newCustomer.phone,
							newCustomer.check_in_date,
							newCustomer.booking_time,
							&newCustomer.total_price,
							&newCustomer.bookedRooms);

		// ��ʼ���ͻ��Ѷ���������ͷ
		newCustomer.room_info = NULL;

		// ��ȡ������Ϣ���ܼ�
		char roomType[50];
		double roomPrice;
		char roomNum[20];
		// ÿ��ѭ����ȡһ��������Ϣ
		for (int i = 1; i <= newCustomer.bookedRooms; i++)
		{
			result = fscanf(fp, "%s %s %lf\n", roomNum, roomType, &roomPrice);
			// ���ӷ�����Ϣ�ڵ㵽�ͻ����Ѷ�����������
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
			// �����½ڵ㲢��������
		}
		insertCustomerNode(newCustomer);
	}
	fclose(fp);

	// ���ؾƵ����з��ͼ�¼�ļ�
	fp = fopen("room_info.txt", "r");
	if (fp == NULL)
	{
		printf("δ�ҵ�������Ϣ�ļ����������ļ�!\n");
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

	// ����������Ŀ��¼�ļ�
	fp = fopen("entertainment_info.txt", "r");
	if (fp == NULL)
	{
		printf("δ�ҵ�������Ŀ��¼�ļ����������ļ�!\n");
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

void displayCustomerInfo() // ��ʾ�ͻ���Ϣ
{
	Customer *current = customer_head;

	while (current != NULL)
	{

		printf("�ͻ�����: %s\n", current->name);
		printf("�ͻ��Ա�: %c\n", current->gender);
		printf("�ͻ����֤�ţ�%s\n", current->idcard);
		printf("�ͻ��绰: %s\n", current->phone);
		printf("��ס����: %s\n", current->check_in_date);
		printf("����ʱ��: %s\n", current->booking_time);
		printf("�ܽ��: %.2lf\n", current->total_price);
		// �����ͻ��Ѷ������������ʾ������Ϣ
		CustomerRoomInfo *roomInfo = current->room_info;
		printf("�ͻ��Ѷ�������Ϣ:\n");
		while (roomInfo != NULL)
		{
			printf("����ţ�%s, ��������: %s, ����۸�: %.2lf\n", roomInfo->room_num, roomInfo->room_type, roomInfo->room_price);
			roomInfo = roomInfo->next;
		}

		printf("--------------------\n");
		current = current->next;
	}
}

void bookRoom() // ���ж�������
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
	newCustomer.bookedRooms = 0;

	// ����ʱ��Ϊ��ǰϵͳʱ��
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char bookingTime[200]; // ���� booking_time ��һ�� char ����
	strftime(bookingTime, sizeof(bookingTime), "%Y-%m-%d-%H:%M:%S", timeinfo);

	sprintf(newCustomer.booking_time, "%s", bookingTime);

	// ����������ַ���������Ϣ��ֱ���������
	int moreRooms = 1;
	do
	{
		CustomerRoomInfo *newRoomInfo = (CustomerRoomInfo *)malloc(sizeof(CustomerRoomInfo));
		printf("�����뷿������: ");
		scanf("%s", newRoomInfo->room_type);

		printf("�����뷿���: ");
		scanf("%s", newRoomInfo->room_num);
		newRoomInfo->next = NULL;

		// �������в��Ҷ�Ӧ�������͵ķ�����Ϣ
		HotelRoomInfo *currentRoom = hotel_room_head;
		while (currentRoom != NULL)
		{
			if (strcmp(currentRoom->room_type, newRoomInfo->room_type) == 0)
			{
				// �ҵ���Ӧ�������ͣ����¿ͻ��ķ�����Ϣ
				strcpy(newRoomInfo->room_type, currentRoom->room_type);
				newRoomInfo->room_price = currentRoom->room_price;

				newCustomer.total_price += currentRoom->room_price;
				currentRoom->remaining_rooms -= 1;
				// ��ӷ�����Ϣ���ͻ��ķ�����Ϣ������
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
		printf("���и��෿��ҪԤ����(1-�ǣ�0-��): ");
		scanf("%d", &moreRooms);
	} while (moreRooms);

	// ���µĿͻ���Ϣ��ӵ��ͻ���Ϣ������
	insertCustomerNode(newCustomer);

	// ���µĿͻ���Ϣ���浽�ļ�
	saveCustomersToFile();
	saveRoomInfoToFile();
}

// �˷����������֤�˷���
void checkOut(char *idCard)
{
	Customer *current = customer_head;
	Customer *prev = NULL;
	while (current != NULL)
	{
		// ����ҵ��˶�Ӧ�Ŀͻ���㣬�����������ɾ��
		if (strcmp(current->idcard, idCard) == 0)
		{
			// ɾ�����Ϊͷ���
			if (prev == NULL)
			{
				customer_head = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			// �ͷ�ɾ�����
			// 1.�ͷſͻ���������
			CustomerRoomInfo *currentRoomInfo = current->room_info;
			while (currentRoomInfo != NULL)
			{
				// ���˷��ķ������� + 1
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
			// 2.�ͷſͻ��������
			free(current);
			printf("�ͻ� %s �˷��ɹ�\n", current->name);
			saveCustomersToFile();
			return;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	printf("δ�ҵ����û���Ϣ: %s", idCard);
}

// �����û������ܽ��ӵ͵��߽�������
void sortCustomersByTotalPrice()
{
	if (customer_head == NULL || customer_head->next == NULL)
	{
		return; // ����Ϊ�ջ�ֻ��һ���ڵ㣬��������
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
				// �����ڵ�λ��
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

void Room_Menu() // ��ӡ���ܲ˵�
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
	printf("               �U 7. �˷�                        �U\n");
	printf("               �U 8. ������Ŀ                     �U\n");
	printf("               �U 9.�޸ĵ�¼����                    �U\n");
	printf("               �U 0. �˳�                        �U\n");
	printf("               �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}

int main()
{
	bool authenticated = false;
	// ѭ��ֱ����֤ͨ��
	do
	{
		authenticated = authenticate();
	} while (!authenticated);
	loadInfoFromFile();
	int choice;
	do
	{
		Room_Menu();
		printf("��ѡ�����: ");
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

			printf("������Ҫ��ӵķ�������: ");
			scanf("%s", roomType);
			printf("������۸�: ");
			scanf("%lf", &price);
			printf("�������ܷ�����: ");
			scanf("%d", &totalRooms);

			addRoomType(roomType, price, totalRooms, totalRooms);
			// saveRoomInfoToFile(); // ���浽�ļ�
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
			char idCard[20];
			printf("������Ҫ�˷��Ŀͻ����֤��");
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
			saveRoomInfoToFile(); // ���浽�ļ�
			exit(0);
		default:
			printf("��Ч��ѡ��!\n");
		}
	} while (choice != 0);
	system("pause");
	return 0;
}

void entertainment()
{
	char choice;
	while (1) // ����ѡ��
	{
		Function_Menu();
		choice = getch();
		switch (choice)
		{
		case '1':
			int price;
			char name[30];
			int id;
			printf("��������Ŀ��š����ƺͼ۸� \n");
			scanf("%d%s%d", &id, name, &price);
			Create(id, name, price);
			saveEntertainmentToFile();
			printf("\n���κμ����η������˵�\n");
			getch();
			getch();
			break;
		case '2':
			int id;
			printf("������Ҫɾ������Ŀ���:");
			scanf("%d", &id);
			Delete(id);
			printf("\n���κμ����η������˵�\n");
			getch();
			getch();
			break;
		case '3':
			printf("��������Ҫ�޸ĵ���Ŀ��ţ�");
			int id, choice;
			scanf("%d", &id);
			printf("��ѡ���޸Ķ���\n1������\n2���۸�\n");
			choice = getch();
			Change(id, choice);
			printf("\n���κμ����η������˵�\n");
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
			printf("����ɹ���\n��򿪲˵��鿴��");
			printf("\n���κμ����η������˵�\n");
			getch();
			getch();
			break;
		case '5':
			int id, roomNumber, price;
			char g[30], h[30];
			Menu();
			printf("��������š�����š���Ŀ���ơ�ԤԼ���ںͼ۸�\n");
			scanf("%d%d%s%s%d", &id, &roomNumber, g, h, &price);
			if (id > 0)
				newOrder(id, roomNumber, g, h, price);
			printf("\n���κμ����η������˵�\n");
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
				printf("������Ҫ���ҵķ����");
				scanf("%d", &roomNumber);
				Search_sort(roomNumber);
				break;
			case '2':
				output();
				break;
			default:
				break;
			}
			printf("\n���κμ����η������˵�\n");
			getch();
			getch();
			break;
		case '7':
			system("cls");
			Menu();
			printf("\n���κμ����η������˵�\n");
			getch();
			getch();
			break;

		case '8':
			system("cls");
			int id;
			output();
			printf("������Ҫɾ���Ķ������:");
			scanf("%d", &id);
			Order_delete(id);
			printf("\n���κμ����η������˵�\n");
			getch();
			getch();
			break;
		case '0':
			system("cls");
			return; // ֱ���˳�����
		}
	}
}

void saveEntertainmentToFile()
{
	FILE *fp = fopen("entertainment_info.txt", "w");
	if (fp == NULL)
	{
		printf("�޷����� entertainment_info.txt �ļ�");
		return;
	}
	Project *current = entertainment_head;
	while (current != NULL)
	{
		fprintf(fp, "%d %s %d\n", current->id, current->name, current->price);
		current = current->next;
	}
	fclose(fp);
	printf("�ɹ�����������Ŀ��Ϣ���ļ���\n");
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
	printf("��ӳɹ����Ƿ�Ҫ�������(y/n)\n");
	char v = getch();
	while (v == 'y')
	{
		printf("\n��������Ŀ��š����ƺͼ۸� \n");
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
	printf("��ѡ��%d����Ŀ��һ��%dԪ\n", nplus, sum);
	printf("�Ƿ�Ҫ�������(y/n)\n");
	char v = getch();
	while (v == 'y')
	{
		printf("��������š�����š���Ŀ���ơ�ԤԼ���ںͼ۸�\n");
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

void Function_Menu() // ��ӡ���ܲ˵�
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
		printf("ϵͳ��������Ŀ��Ϣ��\n\n");
		return;
	}
	while (current != NULL)
	{
		if (id == current->id)
		{
			if (choice == 1)
			{
				printf("�������޸ĺ�����ƣ�\n");
				scanf("%s", current->name);
			}
			else
			{
				printf("�������޸ĺ�ļ۸�\n");
				scanf("%d", &current->price);
			}
			return;
		}
		current = current->next;
	}
	printf("��Ŀ��Ϣ�޸ĳɹ���\n");
}

void Menu() // ��ӡ�˵�
{
	system("cls");
	Project *current = entertainment_head;
	int count = 0;
	if (entertainment_head == NULL)
	{
		printf("ϵͳ��������Ŀ��Ϣ����¼����ٲ鿴��\n\n");
		return;
	}
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*\t\t\t��ӭ���ٱ��Ƶ�  \t\t\t*\n");
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*���                 ����                    �۸�      *\n");
	printf("\t\t\t\t*********************************************************\n");
	while (current != NULL)
	{
		printf("\t\t\t\t*% -3d                %-10s               ��%-6d    *\n", current->id, current->name, current->price);
		printf("\t\t\t\t*********************************************************\n");
		printf("\t\t\t\t*********************************************************\n");
		current = current->next;
		count++;
	}
	printf("\n\t\t\t\t\t\t  һ����%d����Ŀ", count);
}

void Sort_choose() // ����ʽѡ��
{
	system("cls");
	Project *current = entertainment_head;
	if (current == NULL)
	{
		printf("ϵͳ��������Ŀ��Ϣ��\n\n");
		return;
	}
	printf("\n\n\n\n");
	printf("\t\t\t\t                 �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r                 \n");
	printf("\t\t\t\t�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g    ����ʽ    �d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r\n");
	printf("\t\t\t\t�U                �t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s                �U\n");
	printf("\t\t\t\t�U     ��1������������           ��2�����۸���    �U\n");
	printf("\t\t\t\t�U                                                  �U\n");
	printf("\t\t\t\t�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
	printf("\t\t\t\t\t�����������ѡ����Ӧ������ʽ:");
}

void Name_sort() // ���������
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

void Charge_sort() // ���۸�����
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

void Order_choose() // ����ʽѡ��
{
	system("cls");
	Order *current = order_head;
	if (order_head == NULL)
	{
		printf("ϵͳ��������Ŀ��Ϣ��\n\n");
		return;
	}

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

void Search_sort(int roomNumber)
{
	system("cls");
	Order *current = order_head;
	while (current != NULL)
	{
		if (current->roomNumber == roomNumber)
		{
			printf("\t\t\t\t*********************************************************\n");
			printf("\t\t\t\t*\t\t  ��ӭ���ٱ��Ƶ�  \t\t\t*\n");
			printf("\t\t\t\t*********************************************************\n");
			printf("\t\t\t\t*���     �����        ����           ����      �۸�   *\n");
			printf("\t\t\t\t*********************************************************\n");
			printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ��%-6d  *\n", current->id, current->roomNumber, current->kind, current->date, current->price);
			printf("\t\t\t\t*********************************************************\n");
			return;
		}
	}
	printf("�÷���˿���δԤԼ��Ŀ��\n");
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
	printf("ɾ���ɹ���");
}

void output() // ��ӡ����
{
	Order *current = order_head;
	if (order_head == NULL)
	{
		printf("ϵͳ��������Ŀ��Ϣ����¼����ٲ鿴��\n\n");
		return;
	}
	int count = 0;
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*\t\t  ��ӭ���ٱ��Ƶ�  \t\t\t*\n");
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*���     �����        ����           ����      �۸�   *\n");
	printf("\t\t\t\t*********************************************************\n");
	while (current != NULL)
	{
		printf("\t\t\t\t*%-3d       %-5d        %-10s     %-5s   ��%-6d  *\n", current->id, current->roomNumber, current->kind, current->date, current->price);
		printf("\t\t\t\t*********************************************************\n");
		current = current->next;
		count++;
	}
	printf("\n\t\t\t\t\t\t  һ����%d������", count);
}