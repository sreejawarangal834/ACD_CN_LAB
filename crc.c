#include <stdio.h>
#include <string.h>

#define MAX 1000

// Convert each character into 8-bit ASCII binary
void wordToBinary(char word[], char binary[])
{
    int k = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int ch = (unsigned char)word[i];

        for (int j = 7; j >= 0; j--)
        {
            if ((ch & (1 << j)) != 0)
                binary[k++] = '1';
            else
                binary[k++] = '0';
        }
    }

    binary[k] = '\0';
}

// CRC division
void divide(char data[], char generator[], char remainder[])
{
    int n = strlen(generator);
    int len = strlen(data);

    char temp[MAX];
    strcpy(temp, data);

    for (int i = 0; i <= len - n; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < n; j++)
            {
                if (temp[i + j] == generator[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }

    strcpy(remainder, temp + len - (n - 1));
}

int main()
{
    char word[MAX], data[MAX];
    char generator[MAX], appendedData[MAX];
    char crc[MAX], codeword[MAX];
    char received[MAX], remainder[MAX];

    // ---------- SENDER ----------
    printf("Enter data: ");
    scanf("%s", word);

    // Convert word into binary
    wordToBinary(word, data);

    printf("Binary data: %s\n", data);

    printf("Enter generator: ");
    scanf("%s", generator);

    int n = strlen(generator);

    // Append n-1 zeros
    strcpy(appendedData, data);

    for (int i = 0; i < n - 1; i++)
        strcat(appendedData, "0");

    // Calculate CRC
    divide(appendedData, generator, crc);

    // Generate codeword
    strcpy(codeword, data);
    strcat(codeword, crc);

    printf("\n--- Sender ---\n");
    printf("CRC      : %s\n", crc);
    printf("Codeword : %s\n", codeword);

    // ---------- RECEIVER ----------
    printf("\nEnter received data (binary): ");
    scanf("%s", received);

    divide(received, generator, remainder);

    printf("\n--- Receiver ---\n");
    printf("Remainder : %s\n", remainder);

    int error = 0;

    for (int i = 0; remainder[i] != '\0'; i++)
    {
        if (remainder[i] == '1')
        {
            error = 1;
            break;
        }
    }

    if (error)
        printf("Error detected!\n");
    else
        printf("No error detected.\n");

    return 0;
}