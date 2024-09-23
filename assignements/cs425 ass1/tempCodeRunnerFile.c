// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>

// char* bit_string(int k){
//     char* s = (char*)malloc((k + 1) * sizeof(char));
//     for(int i = 0; i < k; i++){
//         s[i] = (rand() & 1) ? '1' : '0';
//     }
//     s[k] = '\0';
//     return s;
// }

// void string_xor(char* a, const char* b, int index){
//     int b_len = strlen(b);
//     if(index + b_len > strlen(a)){
//         return;
//     }

//     for(int i = 0; i < b_len; i++){
//         a[index + i] = (a[index + i] != b[i]) ? '1' : '0';
//     }
// }

// char* find_remainder(char* dividend, const char* divisor){
//     char* remainder = (char*)malloc((strlen(dividend) + 1) * sizeof(char));
//     int remainder_index = 0;

//     for(int i = 0; i < strlen(dividend); i++){
//         if(i + strlen(divisor) <= strlen(dividend)){
//             if(dividend[i] == '1'){
//                 string_xor(dividend, divisor, i);
//             }
//         }else{
//             remainder[remainder_index++] = dividend[i];
//         }
//     }
//     remainder[remainder_index] = '\0';

//     return remainder;
// }

// char* find_crc(const char* message, const char* polynomial){
//     int message_len = strlen(message);
//     char* extended_message = (char*)malloc((message_len + strlen(polynomial)) * sizeof(char));
//     strcpy(extended_message, message);

//     for(int i = 0; i < strlen(polynomial) - 1; i++){
//         strcat(extended_message, "0");
//     }

//     char* crc = find_remainder(extended_message, polynomial);
//     free(extended_message);
//     return crc;
// }

// char* find_fcs(const char* message, const char* polynomial){
//     char* crc = find_crc(message, polynomial);
//     int message_len = strlen(message);
//     char* frame = (char*)malloc((message_len + strlen(crc) + 1) * sizeof(char));
//     strcpy(frame, message);
//     strcat(frame, crc);
//     free(crc);
//     return frame;
// }

// void add_errors(char* t){
//     int error_prob = 10; // Each bit is flipped with an error probability of 1/error_prob

//     for(int i = 0; i < strlen(t); i++){
//         if(rand() % error_prob == 0){
//             t[i] = '1' - t[i] + '0';
//         }
//     }
// }

// int check_valid(char* t, const char* p){
//     printf("\nChecking validity of %s with respect to %s...\n", t, p);
//     char* remainder = find_remainder(t, p);
//     for(int i = 0; i < strlen(remainder); i++){
//         if(remainder[i] == '1'){
//             printf("Non-zero remainder: %s\nInvalid! It should be discarded.\n", remainder);
//             free(remainder);
//             return 0;
//         }
//     }

//     printf("Valid! It should be accepted.\n");
//     free(remainder);
//     return 1;
// }

// void q1_original(void);     // For checking CRC generation with 2 inputs
// void q1_modified(void);     // For parts a, b, c, d

// int main(){
//     srand(time(NULL));

//     char s[10];

//     while(1){
//         printf("\n\nThis program can be used in two ways:\n");
//         printf("(1) Generate CRC from two random strings\n");
//         printf("(2) Generate a 15-bit frame, introduce some errors, and check validity of resulting string\n\n");
//         scanf("%s", s);
//         printf("\n");

//         if(strlen(s) != 1){
//             printf("Please write only 1 or 2.\n");
//         }else if(s[0] == '1'){
//             q1_original();
//             break;
//         }else if(s[0] == '2'){
//             q1_modified();
//             break;
//         }else{
//             printf("Please write only 1 or 2.\n");
//         }
//     }

//     printf("\n");

//     return 0;
// }

// void q1_original(void){
//     int n = 10, k = 6;
//     char *t;

//     while(1){
//         printf("\nDo you want to give custom input (n and k)? [y/n]\n");
//         scanf("%s", t);

//         if(strlen(t) != 1){
//             printf("Please only enter 'y' or 'n' (without the quotes)\n");
//         }else if(t[0] == 'y'){
//             printf("Enter the value of integer n, the frame size: ");
//             scanf("%d", &n);
//             printf("Enter the value of integer k, the message size: ");
//             scanf("%d", &k);
            
//             if(n - k + 1 <= 0){
//                 printf("n should be greater than or equal to k\n");
//                 n = 10; k = 6;
//                 continue;
//             }else{
//                 break;
//             }
//         }else if(t[0] == 'n'){
//             printf("\n\nProceeding with default values n=10 and k=6...\n\n");
//             break;
//         }else{
//             printf("\nPlease only enter 'y' or 'n' (without the quotes)\n");
//         }
//     }

//     printf("First input:\n");
//     char *m = bit_string(k), *p = "0";
//     while(p[0] != '1'){
//         free(p);
//         p = bit_string(n - k + 1);
//     }
//     char *crc = find_crc(m, p);
    
//     printf("M = %s, P = %s\nCRC = %s\nFCS = %s\n", m, p, crc, strcat(m, crc));
//     check_valid(strcat(m, crc), p);

//     printf("\nSecond input:\n");
//     free(m);
//     m = bit_string(k);
//     free(p);
//     p = "0";
//     while(p[0] != '1'){
//         free(p);
//         p = bit_string(n - k + 1);
//     }
//     free(crc);
//     crc = find_crc(m, p);
    
//     printf("M = %s, P = %s\nCRC = %s\nFCS = %s\n", m, p, crc, strcat(m, crc));
//     check_valid(strcat(m, crc), p);

//     printf("\n");
// }

// void q1_modified(void){
//     int n = 15, k = 10;

//     char *m = bit_string(k), *p = "110101";
//     char *t = find_fcs(m, p);

//     printf("\nMessage: %s, Polynomial: %s", m, p);
//     printf("\nTransmission frame (T):\n%s\n", t);

//     add_errors(t);

//     printf("\nTransmission frame after introducing errors:\n%s\n", t);

//     check_valid(t, p);
// }




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100

char* bit_string(int k) {
    char* s = (char*)malloc((k + 1) * sizeof(char));
    int i;
    for (i = 0; i < k; i++) {
        s[i] = (rand() & 1) ? '1' : '0';
    }
    s[k] = '\0';
    return s;
}

void string_xor(char* a, const char* b, int index) {
    int i;
    int b_size = strlen(b);
    for (i = 0; i < b_size; i++) {
        a[index + i] = (a[index + i] != b[i]) ? '1' : '0';
    }
}

char* find_remainder(char* dividend, const char* divisor) {
    char* remainder = (char*)malloc(MAX_SIZE * sizeof(char));
    remainder[0] = '\0';

    int dividend_size = strlen(dividend);
    int divisor_size = strlen(divisor);
    int i;
    for (i = 0; i < dividend_size; i++) {
        if (i + divisor_size <= dividend_size) {
            if (dividend[i] == '1') {
                string_xor(dividend, divisor, i);
            }
        } else {
            strncat(remainder, &dividend[i], 1);
        }
    }

    return remainder;
}

char* find_crc(char* message, const char* polynomial) {
    int polynomial_size = strlen(polynomial);
    int i;
    for (i = 0; i < polynomial_size - 1; i++) {
        strcat(message, "0");
    }

    return find_remainder(message, polynomial);
}

char* find_fcs(const char* message, const char* polynomial) {
    char* fcs = (char*)malloc(MAX_SIZE * sizeof(char));
    strcpy(fcs, message);
    strcat(fcs, find_crc(message, polynomial));
    return fcs;
}

void add_errors(char* t) {
    int error_prob = 10; // Each bit is flipped with an error probability of 1/error_prob

    int i;
    for (i = 0; t[i] != '\0'; i++) {
        if (rand() % error_prob == 0) {
            t[i] = '1' - t[i] + '0';
        }
    }
}

int check_valid(char* t, const char* p) {
    printf("\nChecking validity of %s with respect to %s...\n", t, p);
    char* remainder = find_remainder(t, p);
    int i;
    for (i = 0; remainder[i] != '\0'; i++) {
        if (remainder[i] == '1') {
            printf("Non-zero remainder: %s\nInvalid! It should be discarded.\n", remainder);
            free(remainder);
            return 0;
        }
    }

    printf("Valid! It should be accepted.\n");
    free(remainder);
    return 1;
}

void q1_original(void); // For checking CRC generation with 2 inputs
void q1_modified(void); // For parts a, b, c, d

int main() {
    srand(time(NULL));

    char s[2];

    while (1) {
        printf("\n\nThis program can be used in two ways:\n");
        printf("(1) Generate CRC from two random strings\n");
        printf("(2) Generate a 15-bit frame, introduce some errors, and check validity of resulting string\n\n");
        scanf("%s", s);
        printf("\n");

        if (strlen(s) != 1) {
            printf("Please write only 1 or 2.\n");
        } else if (s[0] == '1') {
            q1_original();
            break;
        } else if (s[0] == '2') {
            q1_modified();
            break;
        } else {
            printf("Please write only 1 or 2.\n");
        }
    }

    printf("\n");

    return 0;
}

void q1_original() {
    int n = 10, k = 6;

    printf("\nDo you want to give custom input (n and k)? [y/n]\n");
    char t[2];
    scanf("%s", t);

    if (strlen(t) != 1) {
        printf("Please only enter 'y' or 'n'\n");
        return;
    } else if (t[0] == 'y') {
        printf("Enter the value of integer n, the frame size: ");
        scanf("%d", &n);
        printf("Enter the value of integer k, the message size: ");
        scanf("%d", &k);

        if (n - k + 1 <= 0) {
            printf("n should be greater than or equal to k\n");
            n = 10;
            k = 6;
            return;
        }
    }

    printf("\n\nProceeding with default values n=10 and k=6...\n\n");

    char* m = bit_string(k);
    char* p = "0";
    while (p[0] != '1') {
        free(p);
        p = bit_string(n - k + 1);
    }

    char* crc = find_crc(m, p);

    printf("M = %s, P = %s\nCRC = %s\nFCS = %s\n", m, p, crc, find_fcs(m, p));
    check_valid(find_fcs(m, p), p);

    free(m);
    free(p);
    free(crc);

    printf("\nSecond input:\n");
    m = bit_string(k);
    p = "0";
    while (p[0] != '1') {
        free(p);
        p = bit_string(n - k + 1);
    }

    crc = find_crc(m, p);

    printf("M = %s, P = %s\nCRC = %s\nFCS = %s\n", m, p, crc, find_fcs(m, p));
    check_valid(find_fcs(m, p), p);

    free(m);
    free(p);
    free(crc);

    printf("\n");
}

void q1_modified() {
    int n = 15, k = 10;

    char* m = bit_string(k);
    char* p = "110101";
    char* t = find_fcs(m, p);

    printf("\nMessage: %s, Polynomial: %s\n", m, p);
    printf("Transmission frame (T):\n%s\n", t);

    add_errors(t);

    printf("Transmission frame after introducing errors:\n%s\n", t);

    check_valid(t, p);

    free(m);
    free(t);
}
