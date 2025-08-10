#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;

void create_account();
void deposit();
void withdraw();
void check_balance();
void view_all();

int main() {
    int choice;
    while (1) {
        printf("\n--- Bank System ---\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. View All\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_account(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: check_balance(); break;
            case 5: view_all(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void create_account() {
    Account a;
    FILE *fp = fopen("bank.dat", "ab");
    printf("Enter name: "); scanf(" %[^\n]", a.name);
    printf("Enter account number: "); scanf("%d", &a.acc_no);
    printf("Enter initial deposit: "); scanf("%f", &a.balance);
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Account created!\n");
}

void deposit() {
    int no; float amt; Account a; int found = 0;
    FILE *fp = fopen("bank.dat", "rb+");
    printf("Enter account number: "); scanf("%d", &no);
    printf("Enter deposit amount: "); scanf("%f", &amt);
    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == no) {
            a.balance += amt;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            found = 1; break;
        }
    }
    fclose(fp);
    if (found) printf("Deposit successful!\n");
    else printf("Account not found.\n");
}

void withdraw() {
    int no; float amt; Account a; int found = 0;
    FILE *fp = fopen("bank.dat", "rb+");
    printf("Enter account number: "); scanf("%d", &no);
    printf("Enter withdrawal amount: "); scanf("%f", &amt);
    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == no) {
            if (amt > a.balance) { printf("Insufficient balance!\n"); break; }
            a.balance -= amt;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            found = 1; break;
        }
    }
    fclose(fp);
    if (found) printf("Withdrawal successful!\n");
}

void check_balance() {
    int no; Account a; int found = 0;
    FILE *fp = fopen("bank.dat", "rb");
    printf("Enter account number: "); scanf("%d", &no);
    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == no) {
            printf("Name: %s\nBalance: %.2f\n", a.name, a.balance);
            found = 1; break;
        }
    }
    fclose(fp);
    if (!found) printf("Account not found.\n");
}

void view_all() {
    Account a;
    FILE *fp = fopen("bank.dat", "rb");
    printf("\n--- Account List ---\n");
    while (fread(&a, sizeof(a), 1, fp))
        printf("Acc No: %d | Name: %s | Balance: %.2f\n", a.acc_no, a.name, a.balance);
    fclose(fp);
}
