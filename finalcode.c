#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void bsort(int array[], int l)
{ // bubble sort
    for (int i = 0; i < l; i++)
    {
        bool temps=false;
        for (int j = i + 1; j < l; j++)
        {
            if (array[j] < array[i])
            {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
                temps=true;
            }
        }
        if(temps==false){
            break;
        }
    }
}
void ssort(int array[], int n)
{ // selection sort
    for (int i = 0; i < n; i++)
    {
        int temp = i;
        for (int j = i + 1; j < n; j++)
        {
            if (array[j] < array[temp])
            {
                temp = j;
            }
        }
        if (temp != i)
        {
            int b = array[temp];
            array[temp] = array[i];
            array[i] = b;
        }
    }
}
int binarysearch(int array[], int x, int low, int high)
{ // binary search
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (array[mid] == x)
            return mid + 1;
        if (array[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
int linearsearch(int array[], int l, int num)
{ // linear search
    for (int i = 0; i < l; i++)
    {
        if (array[i] == num)
        {
            return i;
        }
    }
    return -1;
}
void menu()
{
    printf("||============================================================||\n");
    printf("||                            MENU                            ||\n");
    printf("||------------------------------------------------------------||\n");
    printf("||Hi, this is my sort program. You have the following choices:||\n");
    printf("||------------------------------------------------------------||\n");
    printf("||Linear search or Binary search(output the index of a number)||\n");
    printf("||------------------------------------------------------------||\n");
    printf("||   Selection sort or Bubble sort(output the sorted array)   ||\n");
    printf("||------------------------------------------------------------||\n");
    printf("||           Size of the file: 5000, 10000, or 50000          ||\n");
    printf("||------------------------------------------------------------||\n");
    printf("||    Output the result in the terminal or a separate file    ||\n");
    printf("||============================================================||\n");
}
int main(void)
{
    menu();
    char searchtype = '\0';
    while (searchtype != 'L' && searchtype != 'B' && searchtype != 'N')
    {
        searchtype =
            get_char("Press L for Linear search, B for Binary Search, and N if you do not wish to return the index of a number: ");
    }
    char sorttype = '\0';
    while (sorttype != 'S' && sorttype != 'B' && sorttype != 'N')
    {
        sorttype = get_char("Press S for Selection sort, B for Bubble sort, and N if you do not wish to return a sorted array: ");
    }
    bool bsize = false;
    int rsize = 0;
    while (bsize == false)
    {
        rsize = get_int("Please choose the size of the array: 5000, 10000, or 50000.\n");
        if (rsize == 5000 || rsize == 10000 || rsize == 50000)
        {
            bsize = true;
        }
    }
    char otype = '\0';
    while (otype != 'T' && otype != 'F')
    {
        otype = get_char("Press T to output in terminal and F to output on a separate file: ");
    }
    string filename = "random5000.txt";
    if (rsize == 10000)
    {
        filename = "random10000.txt";
    }
    else if (rsize == 50000)
    {
        filename = "random50000.txt";
    }
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("\nUnable to open: %s", filename);
        return 1;
    }
    int options2[rsize];
    for (int i = 0; i < rsize; i++)
    {
        fscanf(file, "%d", &options2[i]);
    }
    fclose(file);
    int options[rsize];
    for (int i = 0; i < rsize; i++)
    {
        options[options2[i]] = i;
    }
    int num, result;
    if (searchtype == 'L')
    {
        num = get_int("Enter a number you want to find: ");
        result = linearsearch(options2, rsize, num);
    }
    if (sorttype == 'S')
    {
        ssort(options2, rsize);
    }
    else if (sorttype == 'B')
    {
        bsort(options2, rsize);
    }
    if (searchtype == 'B')
    {
        ssort(options2, rsize);
        num = get_int("Enter a number you want to find: ");
        result = binarysearch(options2, num, 0, rsize - 1);
    }
    if (otype == 'T')
    {
        if (searchtype != 'N')
        {
            int ans = result;
            if (searchtype == 'B')
            {
                ans = options[result];
            }
            if (num > rsize || num < 1)
            {
                printf("Number %d not found in the array\n", num);
            }
            else
            {
                printf("Number %d found at index %d, line %d.\n", num, ans, ans + 1);
            }
        }
        if (sorttype != 'N')
        {
            printf("Here is the sorted array:\n");
            for (int i = 0; i < rsize; i++)
            {
                printf("%d\n", options2[i]);
            }
        }
    }
    else
    {
        FILE *outputFile = fopen("output.txt", "w");
        if (outputFile == NULL)
        {
            printf("Could not open file output.txt\n");
            return -1;
        }
        if (searchtype != 'N')
        {
            int ans = result;
            if (searchtype == 'B')
            {
                ans = options[result];
            }
            if (num > rsize || num < 1)
            {
                printf("Number %d not found in the array\n", num);
            }
            else
            {
                fprintf(outputFile, "Number %d found at index %d, line %d.\n", num, ans, ans + 1);
                printf("Searching complete complete. Check output.txt for the index of the assigned number.\n");
            }
        }
        if (sorttype != 'N')
        {
            fprintf(outputFile, "Here is the sorted array:\n");
            for (int i = 0; i < rsize; i++)
            {
                fprintf(outputFile, "%d\n", options2[i]);
            }
            printf("Sorting complete. Check output.txt for the sorted array.\n");
        }
        fclose(outputFile);
    }
    return 0;
}
