#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    char room_type[50];       // ��������
    double room_price;        // ����۸�
    struct CustomerRoomInfo* next;   // ָ����һ���ͻ�������Ϣ�ڵ��ָ��
} CustomerRoomInfo;

// ����ͻ���Ϣ�ṹ��
typedef struct Customer {
    char name[100];           // �ͻ�����
    char phone[20];           // �ͻ��绰
    char gender;              // �ͻ��Ա�
    char check_in_date[20];   // �ͻ���ס����
    CustomerRoomInfo* room_info; // ָ��ͻ��Ѷ�������Ϣ��ָ��
    char booking_time[80];    // ����ʱ��
    double total_price;       // �����ܼ�
    struct Customer* next;    // ָ����һ���ͻ���Ϣ�ڵ��ָ��
} Customer;

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
 
void insertCustomerNode(Customer newCustomer) {
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

void saveCustomersToFile() {
    FILE* fp = fopen("customers.txt", "w");
    if (fp == NULL) {
        printf("�޷������ͻ���Ϣ�ļ�!\n");
        return;
    }

    Customer* current = customer_head;
    while (current != NULL) {
        fprintf(fp, "%s %s %c %s %s", current->name, current->phone, current->gender, current->check_in_date, current->booking_time);

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



void loadRoomInfoFromFile() {
	// ���ؿͻ�������¼�ļ� 
    FILE* fp = fopen("customers.txt", "r");
	if (fp == NULL) {
	    printf("δ�ҵ��ͻ���Ϣ�ļ����������ļ�!\n");
	    return;
	}
	
	while (!feof(fp)) {
	    Customer newCustomer;
	
	    // ��ȡ�����ͻ���Ϣ
	    int result = fscanf(fp, "%s %s %c %s %s",
	                        newCustomer.name,
	                        newCustomer.phone,
	                        &newCustomer.gender,
	                        newCustomer.check_in_date,
	                        newCustomer.booking_time);
	
	    // ��ʼ���ͻ��Ѷ���������ͷ
	    newCustomer.room_info = NULL;
	
	    // ��ȡ������Ϣ���ܼ�
	    double total_price = 0.0;
	    char roomType[50];
	    double roomPrice;
	
	    // ÿ��ѭ����ȡһ��������Ϣ
	    while (fscanf(fp, "%s %lf", roomType, &roomPrice) == 2) {
	        total_price += roomPrice;
	
	        // ���ӷ�����Ϣ�ڵ㵽�ͻ����Ѷ�����������
	        CustomerRoomInfo* newRoom = (CustomerRoomInfo*)malloc(sizeof(CustomerRoomInfo));
	        strcpy(newRoom->room_type, roomType);
	        newRoom->room_price = roomPrice;
	        newRoom->next = NULL;
	
	        if (newCustomer.room_info == NULL) {
	            newCustomer.room_info = newRoom;
	        } else {
	            CustomerRoomInfo* temp = newCustomer.room_info;
	            while (temp->next != NULL) {
	                temp = temp->next;
	            }
	            temp->next = newRoom;
	        }
	    }
	
	    newCustomer.total_price = total_price;
	
	    // �����½ڵ㲢��������
	    insertCustomerNode(newCustomer);
	}
	
	fclose(fp);



    
    // ���ؾƵ����з��ͼ�¼�ļ� 
    fp = fopen("room_info.txt", "r");
    if (fp == NULL) {
        printf("δ�ҵ�������Ϣ�ļ����������ļ�!\n");
        return;
    }

    while (!feof(fp)) {
        char roomType[50];
        double price;
        int totalRooms, remainingRooms;

        if (fscanf(fp, "%s %lf %d %d\n", roomType, &price, &totalRooms, &remainingRooms) == 4) {
            addRoomType(roomType, price, totalRooms, remainingRooms);
        }
    }

    fclose(fp);
}

void displayCustomerInfo() {
    Customer* current = customer_head;

    while (current != NULL) {
        printf("�ͻ�����: %s\n", current->name);
        printf("�ͻ��绰: %s\n", current->phone);
        printf("�ͻ��Ա�: %c\n", current->gender);
        printf("��ס����: %s\n", current->check_in_date);
        printf("����ʱ��: %s\n", current->booking_time);
		printf("�ܽ��: %.2lf\n", current->total_price);
        // �����ͻ��Ѷ������������ʾ������Ϣ
        CustomerRoomInfo* roomInfo = current->room_info;
        printf("�ͻ��Ѷ�������Ϣ:\n");
        while (roomInfo != NULL) {
            printf("��������: %s, ����۸�: %.2lf\n", roomInfo->room_type, roomInfo->room_price);
            roomInfo = roomInfo->next;
        }

        printf("--------------------\n");
        current = current->next;
    }
}


void bookRoom() {
	// ����ʱ��չʾ���з��� 
	displayRoomTypes();
	 
    Customer newCustomer;
    newCustomer.room_info = NULL; // ��ʼ��������Ϣ����

    printf("����������: ");
    scanf("%s", newCustomer.name);

    printf("������绰����: ");
    scanf("%s", newCustomer.phone);

    printf("�������Ա�(M/F): ");
    scanf(" %c", &newCustomer.gender);

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
	

    // ���û�����������ַ���������Ϣ��ֱ���û��������
    int moreRooms = 1;
    do {
        CustomerRoomInfo* newRoomInfo = (CustomerRoomInfo*)malloc(sizeof(CustomerRoomInfo));
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

int main() {
	
    loadRoomInfoFromFile(); 
    
    int choice;
    do {
       	printf("\n�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("�U         �Ƶ����ϵͳ             �U\n");
		printf("�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("�U 1. ����                          �U\n");
		printf("�U 2. չʾ���з�����Ϣ              �U\n");
		printf("�U 3. ��ӷ�����Ϣ                  �U\n");
		printf("�U 4. ɾ��������Ϣ                  �U\n");
		printf("�U 5. չʾ�û�������Ϣ              �U\n");
		printf("�U 6. ����ͻ�������¼              �U\n");
		printf("�U 7. �˳�                          �U\n");
		printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
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
                    saveRoomInfoToFile(); // ���浽�ļ�
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
            default:
                printf("��Ч��ѡ��!\n");
        }
    } while (choice != 7);

    return 0;
}




