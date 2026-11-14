  
#include <stdio.h>
#include <string.h>

#define MAX 100
#define FLAG 0x7E
#define ESC  0x7D

// =================================================
// 1. CHARACTER COUNT
// =================================================

void characterCount()
{
    char frames[20][50];
    int n, i;

    printf("\n========== CHARACTER COUNT ==========\n");

    printf("Enter number of frames: ");
    scanf("%d", &n);

    printf("Enter frames:\n");

    for (i = 0; i < n; i++)
        scanf("%s", frames[i]);

    // Sender
    printf("\nTransmitted Stream: ");

    for (i = 0; i < n; i++)
        printf("%d%s", (int)strlen(frames[i]) + 1, frames[i]);

    printf("\n");

    // Receiver
    printf("\nReceived Frames:\n");

    char stream[MAX * 20];
    int pos = 0;

    // Construct stream
    for (i = 0; i < n; i++)
    {
        int len = strlen(frames[i]) + 1;
        pos += sprintf(stream + pos, "%d%s", len, frames[i]);
    }

    stream[pos] = '\0';

    i = 0;

    while (stream[i] != '\0')
    {
        int count = stream[i] - '0';

        printf("%.*s\n", count - 1, stream + i + 1);

        i += count;
    }
}


// =================================================
// 2. CHARACTER STUFFING (BYTE ORIENTED)
// =================================================

// Sender Side
int charStuffSender(int data[], int n, int stuffed[])
{
    int j = 0;

    printf("\n========== SENDER SIDE ==========\n");

    for (int i = 0; i < n; i++)
    {
        if (data[i] == FLAG || data[i] == ESC)
        {
            stuffed[j++] = ESC;
            stuffed[j++] = data[i] ^ 0x20;

            printf("Special byte: %02X -> %02X %02X\n",
                   data[i], ESC, data[i] ^ 0x20);
        }
        else
        {
            stuffed[j++] = data[i];

            printf("Normal byte: %02X -> No stuffing\n",
                   data[i]);
        }
    }

    return j;
}


// Receiver Side
int charStuffReceiver(int stuffed[], int n, int original[])
{
    int j = 0;

    printf("\n========== RECEIVER SIDE ==========\n");

    for (int i = 0; i < n; i++)
    {
        if (stuffed[i] == ESC)
        {
            i++;

            original[j++] = stuffed[i] ^ 0x20;

            printf("ESC found -> Recovered byte: %02X\n",
                   original[j - 1]);
        }
        else
        {
            original[j++] = stuffed[i];

            printf("Normal byte: %02X\n", stuffed[i]);
        }
    }

    return j;
}


// Display hexadecimal data
void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%02X ", a[i]);

    printf("\n");
}


void characterStuffing()
{
    int data[MAX], stuffed[MAX * 2], received[MAX];
    int n, stuffedLen, receivedLen;
    unsigned int value;

    printf("\n========== CHARACTER STUFFING ==========\n");

    printf("FLAG = 7E\n");
    printf("ESC  = 7D\n");

    printf("\nEnter number of bytes: ");
    scanf("%d", &n);

    printf("Enter data bytes in hexadecimal:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%x", &value);
        data[i] = value;
    }

    printf("\nOriginal Data: ");
    display(data, n);

    // Sender
    stuffedLen = charStuffSender(data, n, stuffed);

    printf("\nStuffed Data: ");
    display(stuffed, stuffedLen);

    // Receiver
    receivedLen = charStuffReceiver(stuffed, stuffedLen, received);

    printf("\nReceived Data: ");
    display(received, receivedLen);

    // Verification
    int equal = (n == receivedLen);
   if(equal)
   {
    for (int i = 0; i < n ; i++)
    {
        if (data[i] != received[i])
            equal = 0;
    }
   }

    if (equal)
        printf("\nSUCCESS: Original and received data are identical.\n");
    else
        printf("\nERROR: Data mismatch.\n");
}


// =================================================
// 3. BIT STUFFING
// =================================================

// Sender Side
void bitStuffing()
{
    char bits[MAX];
    char stuffed[MAX * 2];
    int count = 0, j = 0;

    printf("\n========== BIT STUFFING ==========\n");

    printf("Enter bit string: ");
    scanf("%s", bits);

    // Starting FLAG
    strcpy(stuffed, "01111110");
    j = 8;

    // Sender
    for (int i = 0; bits[i] != '\0'; i++)
    {
        stuffed[j++] = bits[i];

        if (bits[i] == '1')
        {
            count++;

            if (count == 5)
            {
                stuffed[j++] = '0';
                count = 0;
            }
        }
        else
        {
            count = 0;
        }
    }

    // Ending FLAG
    strcpy(stuffed + j, "01111110");

    printf("\nStuffed Frame: %s\n", stuffed);

    // Receiver
    char received[MAX];
    int k = 0;
    count = 0;

    // Skip starting FLAG and ending FLAG
    int len = strlen(stuffed);

    for (int i = 8; i < len - 8; i++)
    {
        received[k++] = stuffed[i];

        if (stuffed[i] == '1')
        {
            count++;

            if (count == 5)
            {
                i++; // Skip stuffed 0
                count = 0;
            }
        }
        else
        {
            count = 0;
        }
    }

    received[k] = '\0';

    printf("After De-stuffing: %s\n", received);
}


// =================================================
// MAIN FUNCTION
// =================================================

int main()
{
    int choice;

    while (1)
    {
        printf("\n========================================\n");
        printf(" DATA LINK LAYER FRAMING METHODS\n");
        printf("========================================\n");

        printf("1. Character Count\n");
        printf("2. Character Stuffing\n");
        printf("3. Bit Stuffing\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                characterCount();
                break;

            case 2:
                characterStuffing();
                break;

            case 3:
                bitStuffing();
                break;

            case 4:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
