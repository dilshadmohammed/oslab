#include <stdio.h>

int n, m;

void readMatrix(int matrix[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void addToAvailable(int available[], int released[])
{
    for (int i = 0; i < m; i++)
        available[i] += released[i];
}

int checkNeed(int need[], int available[])
{
    for (int i = 0; i < m; i++)
        if (need[i] > available[i])
            return 0;
    return 1;
}

int main()
{

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int available[m];
    int max[n][m];
    int allocation[n][m];
    int need[n][m];
    int finish[n], safesq[n];
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    printf("Enter Max matrix:\n");
    readMatrix(max);

    printf("Enter allocation matrix:\n");
    readMatrix(allocation);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int k = 0, progress = 1;
    while (progress)
    {
        progress = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i] && checkNeed(need[i], available))
            {
                addToAvailable(available, allocation[i]);
                finish[i] = 1;
                safesq[k++] = i;
                progress = 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            printf("\n\n<===System is in UNSAFE state===>\n");
            return 0;
        }
    }

    printf("\n\n<===System is in SAFE state===>\n");
    printf("\nSafe sequence: ");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d ->", safesq[i]);
    }
    printf("\b\b  ");
}