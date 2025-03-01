#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ��ݽṹ��
typedef struct Package {
    char id[20];       // ��ݵ���
    char phone[12];    // �ռ����ֻ���
    int status;        // 0-δ��վ 1-��ȡ�� 2-��ȡ��
    char code[6];      // ȡ����
    struct Package* next;
} Package;

Package* head = NULL;  // ����ͷ�ڵ�
const char* status_str [] = {"δ��վ", "��ȡ��", "��ȡ��"};

// ��������
void addPackage();
void generateCode(char* code);
void saveToFile();
void loadFromFile();
void printMenu();
void takePackage();
void searchPackage();

int main() {
    loadFromFile();  // ����ʱ��������
    int choice;
    do {
        system("cls");  // �����Ļ
        printMenu();
        if (scanf("%d", &choice) != 1) {
            // ������뻺����
            while (getchar() != '\n');
            printf("��Ч�����룡���������롣\n");
            system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
            continue;
        }
        switch(choice) {
            case 1: addPackage(); break;
            case 2: takePackage(); break;
            case 3: searchPackage(); break;
            case 4: saveToFile(); break;
            case 0: break;  // �˳�
            default: 
                printf("��Ч�Ĳ��������������롣\n");
                system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
                continue;  // ������ʾ�˵�
        }
        system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
    } while(choice != 0);
    return 0;
}

// ����4λȡ���루��ĸ+���֣�
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

// ��ӿ��
void addPackage() {
    Package* pkg = (Package*)malloc(sizeof(Package));
    printf("�����ݵ���: ");
    scanf("%s", pkg->id);
    printf("�����ռ����ֻ���: ");
    scanf("%s", pkg->phone);
    
    generateCode(pkg->code);  // ����ȡ����
    pkg->status = 1;          // Ĭ�ϴ�ȡ��
    pkg->next = head;
    head = pkg;
    
    printf("�������⣡ȡ���룺%s\n", pkg->code);
    system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
}

// ȡ������
void takePackage() {
    char code[6];
    printf("����ȡ����: ");
    scanf("%s", code);
    
    Package* p = head;
    while(p != NULL) {
        if(strcmp(p->code, code) == 0 && p->status == 1) {
            p->status = 2;
            printf("ȡ���ɹ���\n");
            
            // ����չ���ܡ�ģ�����֪ͨ
            int phone_length = strlen(p->phone);
            if (phone_length >= 4) {
                printf("[ģ�����] β��%s�û������%s��ǩ��\n", 
                       p->phone + phone_length - 4, p->id);
            } else {
                printf("[ģ�����] �ֻ��ų��Ȳ��㣬�޷���ʾβ�š����%s��ǩ��\n", p->id);
            }
            system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
            return;
        }
        p = p->next;
    }
    printf("ȡ������Ч������ȡ�ߣ�\n");
    system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
}

// ���ݳ־û�
void saveToFile() {
    FILE* fp = fopen("packages.txt", "w");
    Package* p = head;
    while(p != NULL) {
        fprintf(fp, "%s,%s,%d,%s\n", 
            p->id, p->phone, p->status, p->code);
        p = p->next;
    }
    fclose(fp);
    printf("�����ѱ��棡\n");
    system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
}

// ��������
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

// �˵�����
void printMenu() {
    printf("\n==== ������վϵͳ ====\n");
    printf("1. ��ӿ��\n");
    printf("2. ȡ��\n");
    printf("3. ��ѯ���\n");
    printf("4. ��������\n");
    printf("0. �˳�\n");
    printf("��ѡ�����: ");
}

// ��ѯ���ܣ���չ���ܣ�
void searchPackage() {
    char key[20];
    printf("���뵥��/�ֻ���: ");
    scanf("%s", key);
    
    Package* p = head;
    while(p != NULL) {
        if(strcmp(p->id, key)==0 || strcmp(p->phone, key)==0) {
            printf("[����:%s] ״̬:%s ȡ����:%s\n",
                   p->id, status_str[p->status], p->code);
            system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
            return;
        }
        p = p->next;
    }
    printf("δ�ҵ���ؿ�ݣ�\n");
    system("pause");  // ��ͣ�Ա��û�������ʾ��Ϣ
}
