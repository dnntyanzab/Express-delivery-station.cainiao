#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 快递结构体
typedef struct Package {
    char id[20];       // 快递单号
    char phone[12];    // 收件人手机号
    int status;        // 0-未到站 1-待取件 2-已取件
    char code[6];      // 取件码
    struct Package* next;
} Package;

Package* head = NULL;  // 链表头节点
const char* status_str [] = {"未到站", "待取件", "已取件"};

// 函数声明
void addPackage();
void generateCode(char* code);
void saveToFile();
void loadFromFile();
void printMenu();
void takePackage();
void searchPackage();

int main() {
    loadFromFile();  // 启动时加载数据
    int choice;
    do {
        system("cls");  // 清除屏幕
        printMenu();
        if (scanf("%d", &choice) != 1) {
            // 清除输入缓冲区
            while (getchar() != '\n');
            printf("无效的输入！请重新输入。\n");
            system("pause");  // 暂停以便用户看到提示信息
            continue;
        }
        switch(choice) {
            case 1: addPackage(); break;
            case 2: takePackage(); break;
            case 3: searchPackage(); break;
            case 4: saveToFile(); break;
            case 0: break;  // 退出
            default: 
                printf("无效的操作！请重新输入。\n");
                system("pause");  // 暂停以便用户看到提示信息
                continue;  // 重新显示菜单
        }
        system("pause");  // 暂停以便用户看到提示信息
    } while(choice != 0);
    return 0;
}

// 生成4位取件码（字母+数字）
void generateCode(char* code) {
    srand(time(NULL));
    int i;
    for(i=0; i<4; i++) {
        if(rand()%2 == 0) 
            code[i] = 'A' + rand()%26;
        else
            code[i] = '0' + rand()%10;
    }
    code[4] = '\0';
}

// 添加快递
void addPackage() {
    Package* pkg = (Package*)malloc(sizeof(Package));
    printf("输入快递单号: ");
    scanf("%s", pkg->id);
    printf("输入收件人手机号: ");
    scanf("%s", pkg->phone);
    
    generateCode(pkg->code);  // 生成取件码
    pkg->status = 1;          // 默认待取件
    pkg->next = head;
    head = pkg;
    
    printf("快递已入库！取件码：%s\n", pkg->code);
    system("pause");  // 暂停以便用户看到提示信息
}

// 取件操作
void takePackage() {
    char code[6];
    printf("输入取件码: ");
    scanf("%s", code);
    
    Package* p = head;
    while(p != NULL) {
        if(strcmp(p->code, code) == 0 && p->status == 1) {
            p->status = 2;
            printf("取件成功！\n");
            
            // 【扩展功能】模拟短信通知
            int phone_length = strlen(p->phone);
            if (phone_length >= 4) {
                printf("[模拟短信] 尾号%s用户，快递%s已签收\n", 
                       p->phone + phone_length - 4, p->id);
            } else {
                printf("[模拟短信] 手机号长度不足，无法显示尾号。快递%s已签收\n", p->id);
            }
            system("pause");  // 暂停以便用户看到提示信息
            return;
        }
        p = p->next;
    }
    printf("取件码无效或快递已取走！\n");
    system("pause");  // 暂停以便用户看到提示信息
}

// 数据持久化
void saveToFile() {
    FILE* fp = fopen("packages.txt", "w");
    Package* p = head;
    while(p != NULL) {
        fprintf(fp, "%s,%s,%d,%s\n", 
            p->id, p->phone, p->status, p->code);
        p = p->next;
    }
    fclose(fp);
    printf("数据已保存！\n");
    system("pause");  // 暂停以便用户看到提示信息
}

// 加载数据
void loadFromFile() {
    FILE* fp = fopen("packages.txt", "r");
    if(fp == NULL) return;
    
    char id[20], phone[12], code[6];
    int status;
    while(fscanf(fp, "%[^,],%[^,],%d,%s\n", 
                 id, phone, &status, code) != EOF) {
        Package* pkg = (Package*)malloc(sizeof(Package));
        strcpy(pkg->id, id);
        strcpy(pkg->phone, phone);
        pkg->status = status;
        strcpy(pkg->code, code);
        pkg->next = head;
        head = pkg;
    }
    fclose(fp);
}

// 菜单界面
void printMenu() {
    printf("\n==== 菜鸟驿站系统 ====\n");
    printf("1. 添加快递\n");
    printf("2. 取件\n");
    printf("3. 查询快递\n");
    printf("4. 保存数据\n");
    printf("0. 退出\n");
    printf("请选择操作: ");
}

// 查询功能（扩展功能）
void searchPackage() {
    char key[20];
    printf("输入单号/手机号: ");
    scanf("%s", key);
    
    Package* p = head;
    while(p != NULL) {
        if(strcmp(p->id, key)==0 || strcmp(p->phone, key)==0) {
            printf("[单号:%s] 状态:%s 取件码:%s\n",
                   p->id, status_str[p->status], p->code);
            system("pause");  // 暂停以便用户看到提示信息
            return;
        }
        p = p->next;
    }
    printf("未找到相关快递！\n");
    system("pause");  // 暂停以便用户看到提示信息
}
