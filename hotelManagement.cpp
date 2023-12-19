#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    char room_type[50];       // 房间类型
    double room_price;        // 房间价格
    struct CustomerRoomInfo* next;   // 指向下一个客户房间信息节点的指针
} CustomerRoomInfo;

// 定义客户信息结构体
typedef struct Customer {
    char name[100];           // 客户姓名
    char phone[20];           // 客户电话
    char gender;              // 客户性别
    char check_in_date[20];   // 客户入住日期
    CustomerRoomInfo* room_info; // 指向客户已定房间信息的指针
    char booking_time[80];    // 订房时间
    double total_price;       // 订房总价
    struct Customer* next;    // 指向下一个客户信息节点的指针
} Customer;

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
 
void insertCustomerNode(Customer newCustomer) {
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

void saveCustomersToFile() {
    FILE* fp = fopen("customers.txt", "w");
    if (fp == NULL) {
        printf("无法创建客户信息文件!\n");
        return;
    }

    Customer* current = customer_head;
    while (current != NULL) {
        fprintf(fp, "%s %s %c %s %s", current->name, current->phone, current->gender, current->check_in_date, current->booking_time);

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



void loadRoomInfoFromFile() {
	// 加载客户订房记录文件 
    FILE* fp = fopen("customers.txt", "r");
	if (fp == NULL) {
	    printf("未找到客户信息文件，创建新文件!\n");
	    return;
	}
	
	while (!feof(fp)) {
	    Customer newCustomer;
	
	    // 读取基本客户信息
	    int result = fscanf(fp, "%s %s %c %s %s",
	                        newCustomer.name,
	                        newCustomer.phone,
	                        &newCustomer.gender,
	                        newCustomer.check_in_date,
	                        newCustomer.booking_time);
	
	    // 初始化客户已定房间链表头
	    newCustomer.room_info = NULL;
	
	    // 读取房间信息和总价
	    double total_price = 0.0;
	    char roomType[50];
	    double roomPrice;
	
	    // 每次循环读取一个房间信息
	    while (fscanf(fp, "%s %lf", roomType, &roomPrice) == 2) {
	        total_price += roomPrice;
	
	        // 增加房间信息节点到客户的已定房间链表中
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
	
	    // 创建新节点并插入链表
	    insertCustomerNode(newCustomer);
	}
	
	fclose(fp);



    
    // 加载酒店现有房型记录文件 
    fp = fopen("room_info.txt", "r");
    if (fp == NULL) {
        printf("未找到房型信息文件，创建新文件!\n");
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
        printf("客户姓名: %s\n", current->name);
        printf("客户电话: %s\n", current->phone);
        printf("客户性别: %c\n", current->gender);
        printf("入住日期: %s\n", current->check_in_date);
        printf("订房时间: %s\n", current->booking_time);
		printf("总金额: %.2lf\n", current->total_price);
        // 遍历客户已定房间的链表并显示房间信息
        CustomerRoomInfo* roomInfo = current->room_info;
        printf("客户已订房间信息:\n");
        while (roomInfo != NULL) {
            printf("房间类型: %s, 房间价格: %.2lf\n", roomInfo->room_type, roomInfo->room_price);
            roomInfo = roomInfo->next;
        }

        printf("--------------------\n");
        current = current->next;
    }
}


void bookRoom() {
	// 订房时先展示现有房型 
	displayRoomTypes();
	 
    Customer newCustomer;
    newCustomer.room_info = NULL; // 初始化房间信息链表

    printf("请输入姓名: ");
    scanf("%s", newCustomer.name);

    printf("请输入电话号码: ");
    scanf("%s", newCustomer.phone);

    printf("请输入性别(M/F): ");
    scanf(" %c", &newCustomer.gender);

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
	

    // 让用户连续输入多种房间类型信息，直到用户输入结束
    int moreRooms = 1;
    do {
        CustomerRoomInfo* newRoomInfo = (CustomerRoomInfo*)malloc(sizeof(CustomerRoomInfo));
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

int main() {
	
    loadRoomInfoFromFile(); 
    
    int choice;
    do {
       	printf("\n╔══════════════════════════════════╗\n");
		printf("║         酒店管理系统             ║\n");
		printf("╠══════════════════════════════════╣\n");
		printf("║ 1. 订房                          ║\n");
		printf("║ 2. 展示所有房型信息              ║\n");
		printf("║ 3. 添加房型信息                  ║\n");
		printf("║ 4. 删除房型信息                  ║\n");
		printf("║ 5. 展示用户订房信息              ║\n");
		printf("║ 6. 整理客户订房记录              ║\n");
		printf("║ 7. 退出                          ║\n");
		printf("╚══════════════════════════════════╝\n");
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
                    saveRoomInfoToFile(); // 保存到文件
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
            default:
                printf("无效的选择!\n");
        }
    } while (choice != 7);

    return 0;
}




