#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#define NUM_ITEMS 10
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
menu_item add_items(string item, float price);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    string items[NUM_ITEMS] = {"Burger",       "Vegan Burger",       "Hot Dog",   "Cheese Dog", "Fries",
                               "Cheese Fries", "Cold Pressed Juice", "Cold Brew", "Water",      "Soda"};
    float prices[NUM_ITEMS] = {9.5, 11, 5, 7, 5, 6, 7, 3, 2, 2};

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        menu[i] = add_items(items[i], prices[i]);
    }

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
menu_item add_items(string item, float price)
{
    menu_item temp;
    temp.item = item;
    temp.price = price;
    return temp;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcasecmp(menu[i].item, item) == 0)
        {
            return menu[i].price;
        }
    }
    return 0.0;
}
