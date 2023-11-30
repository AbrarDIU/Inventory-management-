#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

FILE *file;

//***(Work of All structure)***//
//-----------------------------------------------------------//

// Define a structure for a product
struct Product
{
    int id;
    char name[50];
    float price;
    int quantity;
    char Ex_date[30];
    struct Product* next;
};
// Global variable for the head of the linked list
struct Product* head = NULL;


// Define a structure for a purchase record
struct Purchase
{
    int customerID;
    int productID;
    int quantityPurchased;
    float totalPrice;
    struct Purchase* next;
};
// Global variables for the heads of linked lists
struct Purchase* purchaseRecordsHead = NULL;


// Define a structure for a supplier
struct Supplier
{
    int id;
    char name[50];
    char contactInfo[100];
    struct Supplier* next;
};
// Global variable for the head of the linked list of suppliers
struct Supplier* supplierHead = NULL;
//-------------------------------------------------------------------------------------//

//Global veriable //
//******************************//
char password[26] = " ";
char username[26] = " ";
int isSignedIn = 0;
//*****************************//

//-------(All function)-------//
//-----------------------------------------------------------------------------------------------------------//
int displayMenu();
int login();
void changePassword();
void setPasswordAndUsername();
void alertsAndNotifications();
void associateSupplierWithProduct(int productId, int supplierId);
void displaySuppliers();
void addSupplier(int id, const char name[], const char contactInfo[]);
void calculateCost(int customerId);
void recordCustomerPurchase();
void searchProductByID(int id);
void searchProductByName(const char name[]);
void displayInventory();
void removeProduct(int id);
void updateProduct(int id);
void addProduct(int id, const char name[], float price, int quantity, const char Ex_date[]);
//--------------------------------------------------------------------------------------------------------------//

int main()
{
    system("color 3");

    file=fopen("Inventory Management System.txt","a");
    if(file==NULL)
    {
        printf("File Does not Exist\n\n");
        exit(0);
    }

    fputs("\n\n\t\t\t\t       ---------------\n\t\t\t\t\tStar\n\t\t\t\t             --------------\n\n\n",file);
    printf("\n\n\t\t\t\t       ---------------\n\t\t\t\t\t Welcome \n\t\t\t\t      --------------\n\n\n",file);
    int choice;
    do
    {
        choice = displayMenu();

        switch (choice)
        {
        case 1:
            if (login() == 1)
            {
                system("cls");
                // User is logged in, provide the menu for further operations
                int choiceOp;
                do
                {
                    printf("\n\n\t\t\t\t*****************************************\n");
                    printf("\t\t\t\t      Inventory Management System        \n");
                    printf("\t\t\t\t*****************************************\n\n");

                    printf("• Inventory Management:\t\t\t• Sales Management:\t\t\t• Supplier Management:\t\t\t• Alerts and Notifications:\n\n");
                    printf("1. Add new products\t\t\t5. Record customer purchases\t\t7. Add New Supplier\t\t\t10. Alerts and Notifications\n");
                    printf("2. Update products information\t\t6. Calculate cost\t\t        8. List Suppliers\n");
                    printf("3. Remove Product\t\t\t\t\t\t\t\t9. Associate Supplier with Product\n");
                    printf("4. Search  And View\n\n");

                    printf("\t\t\t\t\t\t\t11. Exit\n\n");
                    printf("\t\tEnter a valid number: ");
                    scanf("%d", &choiceOp);


                    if (choiceOp == 1)
                    {
//****************************************************************************************************//
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
//***************************************************************************************************//
                        int id, quantity;
                        char name[50], dateOfEx[30];
                        float price;

                        printf("Enter Product ID: ");
                        scanf("%d", &id);
                        getchar();  // Consuming newline character
                        printf("Enter Product Name: ");
                        gets(name);
                        printf("Enter Product Price: ");
                        scanf("%f", &price);
                        printf("Enter Product Quantity: ");
                        scanf("%d", &quantity);
                        printf("Enter Product Expiry Date: ");
                        getchar();  // Consuming newline character
                        gets(dateOfEx);

//*****************************************************************************************************//
                        fputs("\n\nAdd product: \nEnter Product ID: ", file);
                        fprintf(file, "%d", id);
                        fputs("\nProduct Name: ", file);
                        fputs(name, file);
                        fputs("\nProduct Price: ", file);
                        fprintf(file, "%.3f ", price);
                        fputs("\nProduct Quantity: ", file);
                        fprintf(file, "%d", quantity);
                        fputs("\nProduct Expiry Date: ", file);
                        fputs(dateOfEx, file);

                        fputs("\n\n", file);
                        fclose(file);
//**************************************************************************************************//
                        addProduct(id, name, price, quantity, dateOfEx);


                    }

                    if (choiceOp == 2)
                    {
//**************************************************************************************************//
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
//**************************************************************************************************//
                        int id;
                        printf("Enter the ID of the product to update: ");
                        scanf("%d", &id);
                        updateProduct(id); // New function for updating product info
                        fclose(file);
                    }
                    if (choiceOp == 3)
                    {
//*************************************************************************************************//
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
//***********************************************************************************************//

                        int id;
                        printf("Enter the ID of the product to remove: ");
                        scanf("%d", &id);
                        removeProduct(id);
                        fclose(file);
                    }

                    if (choiceOp == 4)
                    {
//**********************************************************************************************//
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
//*********************************************************************************************//
                        int s_v;
                        do
                        {
                            printf("Enter A Valid number:\n");
                            printf("1. Search By Name.\n");
                            printf("2. Search By ID.\n");
                            printf("3. Display All Inventory.\n");
                            scanf("%d", &s_v);
                        }
                        while (s_v < 1 || s_v > 3);
                        if (s_v == 1)
                        {
                            char name[50];
                            printf("Enter the name of the product to search: ");
                            scanf("%49s", name);
                            searchProductByName(name);
                        }
                        if (s_v == 2)
                        {
                            printf("Enter the ID of the product to search: ");
                            int id;
                            scanf("%d", &id);
                            searchProductByID(id);
                        }
                        if (s_v == 3)
                        {
                            displayInventory();
                        }
                        fclose(file);
                    }


                    if (choiceOp == 5)
                    {
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
                        recordCustomerPurchase();
                        fclose(file);
                    }

                    if (choiceOp == 6)
                    {
//*********************************************************************************************************//
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
//********************************************************************************************************//

                        // Calculate Cost
                        int customerId;
                        printf("Enter Customer ID to calculate cost: ");
                        scanf("%d", &customerId);
                        calculateCost(customerId);
                        fclose(file);
                    }

                    if (choiceOp == 7)
                    {
//********************************************************************************************************//
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
//*******************************************************************************************************//

                        // Add New Supplier
                        int supplierId;
                        char supplierName[50];
                        char supplierContactInfo[100];

                        printf("Enter Supplier ID: ");
                        scanf("%d", &supplierId);
                        getchar();  // Consume the newline character in the input buffer
                        printf("Enter Supplier Name: ");
                        fgets(supplierName, sizeof(supplierName), stdin);
                        printf("Enter Supplier Contact Information: ");
                        fgets(supplierContactInfo, sizeof(supplierContactInfo), stdin);

 //*************************************************************************************************************//
                         fputs("\n\nNew Supplier: ", file);
                        fprintf(file, "\nSupplier ID: %d", supplierId);
                        fputs("\nSupplier Name: ", file);
                        fputs(supplierName, file);
                        fputs("\nSupplier Contact Information: ", file);
                        fputs(supplierContactInfo, file);
                        fclose(file);
//*************************************************************************************************************//
                        addSupplier(supplierId, supplierName, supplierContactInfo);

                    }


                    if (choiceOp == 8)
                        displaySuppliers();

                    if (choiceOp == 9)
                    {
                        file = fopen("Inventory Management System.txt", "a");
                        if (file == NULL)
                        {
                            printf("File cannot be opened\n");
                            return;
                        }
                        int productId, supplierId;
                        printf("Enter the Product ID to associate with a Supplier: ");
                        scanf("%d", &productId);
                        printf("Enter the Supplier ID to associate with the Product: ");
                        scanf("%d", &supplierId);
                        associateSupplierWithProduct(productId, supplierId);
                        fclose(file);
                    }

                    // Add this function to the menu handling section
                    if (choiceOp == 10)
                    {
                        alertsAndNotifications();
                    }

                }
                while (choiceOp != 11);

            }
            break;
        case 2:
            setPasswordAndUsername();
            break;
        case 3:
            changePassword();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
    while (1);
    fclose(file);
    return 0;
}

//All Function
//*********************************************************************************************************//

// ---------------------------(Function to add a new product to the inventory)---------------------------
void addProduct(int id, const char name[], float price, int quantity, const char Ex_date[])
{
    // Allocate memory for the new product
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));

    // Check if memory allocation failed
    if (newProduct == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
//-----------------------------------------------------------------//
    // Open the file for logging
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//---------------------------------------------------------------------// connection part
    // Assign values to the new product
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->quantity = quantity;
    strcpy(newProduct->Ex_date, Ex_date);

    // Set the new product as the head of the product list
    newProduct->next = head;
    head = newProduct;
//-----------------------------------------------------------------//
    // Log successful addition of the product to the file
    fprintf(file, "\n\t\t----------------------------\n");
    fprintf(file, "\t\tProduct added successfully.\n");
    fprintf(file, "\t\t----------------------------\n");

    // Close the file
    fclose(file);
}

// Function to update product information by ID
void updateProduct(int id)
{
    // Pointer to traverse the product list
    struct Product* current = head;
//-------------------------------------------------------------//
    // Open the file for logging
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//---------------------------------------------------------------//
    // Search for the product by ID
    while (current != NULL)
    {
        if (current->id == id)
        {
            // Display menu for updating product information
            printf("\n----------------------------\n");
            printf("Product Found:\n");
            printf("1. Update Name\n");
            printf("2. Update Price\n");
            printf("3. Update Quantity\n");
            printf("4. Update Expiry Date\n");
            printf("5. Return to Main Menu\n");
            printf("----------------------------\n");

            int choice;
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                // Update product name
                printf("\nEnter the new name: ");
                scanf(" %49[^\n]", current->name);
                printf("Product name updated successfully.\n");
                //-----------------------------------------------------------------------//
                fprintf(file, "\n\n\t\t\tUpdated Product Name: %s\n", current->name);
                fclose(file);
                //-----------------------------------------------------------------------//
                break;
            case 2:
                // Update product price
                printf("\nEnter the new price: ");
                scanf("%f", &current->price);
                printf("Product price updated successfully.\n");
                //--------------------------------------------------------------------------//
                fprintf(file, "\n\n\t\t\tUpdated Product price: %.2f\n", current->price);
                fclose(file);
                //--------------------------------------------------------------------------//
                break;
            case 3:
                // Update product quantity
                printf("\nEnter the new quantity: ");
                scanf("%d", &current->quantity);
                printf("Product quantity updated successfully.\n");
                //-------------------------------------------------------------------------------//
                fprintf(file, "\n\n\t\t\tUpdated Product quantity: %d\n", current->quantity);
                fclose(file);
                //-------------------------------------------------------------------------------//
                break;
            case 4:
                // Update product expiry date
                printf("\nEnter the new expiry date: ");
                scanf(" %29[^\n]", current->Ex_date);
                printf("Expiry date updated successfully.\n");
                //.................................................................................//
                fprintf(file, "\n\n\t\t\tUpdated Product expiry date: %s\n", current->Ex_date);
                fclose(file);
                //.................................................................................//
                break;
            case 5:
                fclose(file);
                return; // Return to the main menu
            default:
                printf("\nInvalid choice.\n");
                fclose(file);
                break;
            }

            printf("----------------------------\n");
            return; // Exit the function after updating
        }
        current = current->next;
    }

    // Product not found for the given ID
    printf("Product with ID %d not found.\n", id);
}

// Function to remove a product by ID
void removeProduct(int id)
{
    //........................................................//
    // Open the file for logging
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
    //............................................................//

    // Pointers to traverse the product list and keep track of the previous node
    struct Product* current = head;
    struct Product* prev = NULL;

    // Search for the product by ID
    while (current != NULL)
    {
        if (current->id == id)
        {
            printf("\n----------------------------\n");
            if (prev == NULL)
            {
                // If the product to be removed is the first one in the list
                head = current->next;
            }
            else
            {
                // If the product to be removed is not the first one
                prev->next = current->next;
            }

            printf("Product with ID %d removed successfully.\n", id);

            printf("----------------------------\n");
//..............................................................................//
            // Log removal of the product in the file
            fputs("\n\n\t\t\tProduct with ID : ", file);
            fprintf(file, "%d", id);
            fputs(" removed\n", file);
            fclose(file);
//.................................................................................//
            // Free the memory allocated for the removed product
            free(current);
            return; // Exit the function after removing the product
        }

        // Move to the next product in the list
        prev = current;
        current = current->next;
    }

    // Product not found for the given ID
    printf("Product with ID %d not found.\n",id);
}

// Function to display the inventory
void displayInventory()
{
//..........................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//.........................................................//

    struct Product* current = head;

    if (current == NULL)
    {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\nInventory:\n");
//......................................................//
    fputs("\tUser do Display Operation  : ", file);
    fputs("\n\n\t\t\tInventory: \n", file);
//........................................................//
    while (current != NULL)
    {
        printf("\n--------------------------------\n");
        printf("ID: %d\n", current->id);
        printf("Name: %s\n", current->name);
        printf("Price: $%.2f\n", current->price);
        printf("Quantity: %d\n", current->quantity);
        printf("Expiry Date: %s\n\n", current->Ex_date);
        printf("--------------------------------\n");
//...............................................................//
        fputs(" ID: ", file);
        fprintf(file, "%d", current->id);
        fputs("\t\tName: ", file);
        fputs(current->name, file);
        fputs("\t\tPrice: ", file);
        fprintf(file, "%.3f ", current->price);
        fputs("\t\tQuantity: ", file);
        fprintf(file, "%d", current->quantity);
        fputs("\t\tExpiry Date: ", file);
        fputs(current->Ex_date, file);
        fputs("\n\n", file);
//.............................................................///
        current = current->next;
    }
    fclose(file);
}

// Function to search for a product by name
void searchProductByName(const char name[])
{
    struct Product* current = head;
    int found = 0;
//.............................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//.............................................................//
//............................................................//
    fputs("\n\n\t\tUser do Search Operation  : ", file);
    fputs(name, file);
//...........................................................//
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("Product found:\n");
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Price: $%.2f\n", current->price);
            printf("Quantity: %d\n", current->quantity);
            printf("Expiry Date: %s\n\n", current->Ex_date);
            found = 1;

//.........................................................................//
            fputs("\n\t\tFound It...\n\n", file);
            fputs(" ID: ", file);
            fprintf(file, "%d", current->id);
            fputs("\tName: ", file);
            fputs(current->name, file);
            fputs("\tPrice: ", file);
            fprintf(file, "%.3f ", current->price);
            fputs("\tQuantity: ", file);
            fprintf(file, "%d", current->quantity);
            fputs("\tExpiry Date: ", file);
            fputs(current->Ex_date, file);
//.............................................................................//

        }
        current = current->next;
    }

    if (!found)
    {
        printf("\nProduct with the name '%s' not found.\n", name);
        fputs("\t\tNot Found ...\n\n", file);
    }
    fclose(file);
}

// Function to search for a product by ID
void searchProductByID(int id)
{
    struct Product* current = head;
    int found = 0;
//..........................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
    fputs("\n\n\t\tUser do Search Operation  : ", file);
    fprintf(file, "%d", id);
//...........................................................................//
    while (current != NULL)
    {
        if (current->id == id)
        {
            printf("Product found:\n");
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Price: $%.2f\n", current->price);
            printf("Quantity: %d\n", current->quantity);
            printf("Expiry Date: %s\n\n", current->Ex_date);
            found = 1;
//...........................................................................//
            fputs("\n\t\tFound It...\n\n", file);
            fputs(" ID: ", file);
            fprintf(file, "%d", current->id);
            fputs("\tName: ", file);
            fputs(current->name, file);
            fputs("\tPrice: ", file);
            fprintf(file, "%.3f ", current->price);
            fputs("\tQuantity: ", file);
            fprintf(file, "%d", current->quantity);
            fputs("\tExpiry Date: ", file);
            fputs(current->Ex_date, file);
//..................................................................................//

            break; // We found the product, no need to continue searching
        }
        current = current->next;
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", id);
        fputs("\t\tNot Found ...\n\n", file);
    }
    fclose(file);
}


// Function to record customer purchases
void recordCustomerPurchase()
{
    int customerId;
    int productId;
    int quantityPurchased;
    struct Product* currentProduct = head;
//.....................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//........................................................................//

    printf("\nEnter Customer ID: ");
    scanf("%d", &customerId);
    printf("Enter Product ID: ");
    scanf("%d", &productId);

//.........................................................................//
    fputs("\n\n\t\tRecord Customer Purchase :\n", file);
    fputs("\n\t\tCustomer ID: ", file);
    fprintf(file, "%d", customerId);
    fputs("\n\t\tProduct ID: ", file);
    fprintf(file, "%d", productId);
//........................................................................//

    while (currentProduct != NULL)
    {
        if (currentProduct->id == productId)
        {
            printf("Product Found:\n");
            printf("Name: %s\n", currentProduct->name);
            printf("Price: $%.2f\n", currentProduct->price);
            printf("Available Quantity: %d\n", currentProduct->quantity);
            printf("Enter Quantity Purchased: ");
            scanf("%d", &quantityPurchased);

//.....................................................................................................//
            fputs("\n\t\tName: ", file);
            fputs(currentProduct->name, file);
            fputs("\n\t\tPrice: ", file);
            fprintf(file, "%.2f", currentProduct->price);
            fputs("\n\t\tAvailable Quantity: ", file);
            fprintf(file, "%d", currentProduct->quantity);
            fputs("\n\t\tQuantity Purchased: ", file);
            fprintf(file, "%d", quantityPurchased);
//....................................................................................................//

            if (quantityPurchased <= 0 || quantityPurchased > currentProduct->quantity)
            {
                printf("Invalid quantity. Purchase not recorded.\n");
                //................................................................//
                fputs("\n\t\tInvalid quantity. Purchase not recorded.\n", file);
                //.................................................................//
            }
            else
            {
                // Update product quantity
                currentProduct->quantity -= quantityPurchased;
                printf("Purchase recorded successfully.\n");
                //.....................................................//
                fputs("\n\t\tPurchase recorded successfully.\n", file);
                //.............................................................//
                // Add a new purchase record
                struct Purchase* newRecord = (struct Purchase*)malloc(sizeof(struct Purchase));
                if (newRecord == NULL)
                {
                    printf("Memory allocation failed for purchase record.\n");
                    return;
                }
                newRecord->customerID = customerId;
                newRecord->productID = productId;
                newRecord->quantityPurchased = quantityPurchased;
                newRecord->totalPrice = currentProduct->price * quantityPurchased;
                newRecord->next = purchaseRecordsHead;
                purchaseRecordsHead = newRecord;
            }
            fclose(file);
            return;
        }
        currentProduct = currentProduct->next;
    }

    printf("\nProduct with ID %d not found.\n");
}


// Function to calculate the total cost for a specific customer
void calculateCost(int customerId)
{
    //......................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
    //.........................................................//

    float totalCost = 0;
    struct Purchase* currentRecord = purchaseRecordsHead;

//..........................................................................//
    fputs("\n\n\t\tCalculate Cost for Customer ID ", file);
    fprintf(file, "%d", customerId);
//..........................................................................//
    while (currentRecord != NULL)
    {
        if (currentRecord->customerID == customerId)
        {
            totalCost += currentRecord->totalPrice;
        }
        currentRecord = currentRecord->next;
    }

    if (totalCost > 0)
    {
        fprintf(file, "%.2f", totalCost);
        printf("\n\n\t\t\tTotal cost for Customer ID %d: $%.2f\n", customerId, totalCost);
    }
    else
    {
        printf("\n\t\t\tNo purchase records found for Customer ID %d.\n", customerId);
    }
    fclose(file);
}

// Function to add a new supplier
void addSupplier(int id, const char name[], const char contactInfo[])
{
//........................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//.............................................................................//

    struct Supplier* newSupplier = (struct Supplier*)malloc(sizeof(struct Supplier));

    if (newSupplier == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newSupplier->id = id;
    strcpy(newSupplier->name, name);
    strcpy(newSupplier->contactInfo, contactInfo);
    newSupplier->next = supplierHead;
    supplierHead = newSupplier;
    printf("\nSupplier added successfully.\n");

    //.......................................................//
    fputs("\n\n\t\tSupplier added successfully.\n", file);
    fclose(file);
    //.........................................................//
}

// Function to display the list of suppliers
void displaySuppliers()
{
    struct Supplier* current = supplierHead;
//................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//..............................................................//

    if (current == NULL)
    {
        printf("No suppliers in the list.\n");
        //.......................................................................................//
        fputs("\n\t\tUser Display Suppliers Information: No suppliers in the list.\n", file);
        //......................................................................................//
        return;
    }
//.....................................................................//
    fputs("\n\t\tUser Display Suppliers Information:\n", file);
//.....................................................................//

    printf("List of Suppliers:\n");
    while (current != NULL)
    {

        printf("Supplier ID: %d\n", current->id);
        printf("Name: %s\n", current->name);
        printf("Contact Info: %s\n\n", current->contactInfo);
//............................................................................//
        fputs("\n\t\tSupplier ID: ", file);
        fprintf(file, "%d", current->id);
        fputs("\n\t\tName: ", file);
        fputs(current->name, file);
        fputs("\n\t\tContact Info: ", file);
        fputs(current->contactInfo, file);
//................................................................................//
        current = current->next;
    }
    fclose(file);
}

// Function to associate a supplier with a product
void associateSupplierWithProduct(int productId, int supplierId)
{
    struct Product* currentProduct = head;
    int productFound = 0;
    struct Supplier* currentSupplier = supplierHead;
    int supplierFound = 0;
//........................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//............................................................................//

    while (currentProduct != NULL)
    {
        if (currentProduct->id == productId)
        {
            productFound = 1;
            break;
        }
        currentProduct = currentProduct->next;
    }

    while (currentSupplier != NULL)
    {
        if (currentSupplier->id == supplierId)
        {
            supplierFound = 1;
            break;
        }
        currentSupplier = currentSupplier->next;
    }

    if (productFound && supplierFound)
    {
        currentProduct->id = supplierId;
        printf("\nProduct with ID %d is now associated with Supplier ID %d.\n", productId, supplierId);
//.......................................................................................//
        fputs("\n\t\tProduct with ID ", file);
        fprintf(file, "%d", productId);
        fputs(" is now associated with Supplier ID ", file);
        fprintf(file, "%d", supplierId);
        fputs("\n\n", file);
//.......................................................................................//

    }
    else
    {
        if (!productFound)
        {
            printf("Product with ID %d not found.\n", productId);
//..........................................................................//
            fputs("\n\t\tProduct with ID ", file);
            fprintf(file, "%d", productId);
            fputs(" not found.\n", file);
//..........................................................................//
        }
        if (!supplierFound)
        {
            printf("Supplier with ID %d not found.\n", supplierId);
//..........................................................................//
            fputs("\n\t\tSupplier with ID ", file);
            fprintf(file, "%d", supplierId);
            fputs(" not found.\n", file);
//.........................................................................//
        }
    }
    fclose(file);
}

// Function to handle alerts and notifications
void alertsAndNotifications()
{
    struct Product* current = head;
    int alertCount = 0, overstockCount = 0;
//..........................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//..........................................................................//

    printf("\nEnter Current Date: ");
    char currentDate[30];
    getchar();
    gets(currentDate);
    while (current != NULL)
    {
        // Alert for low stock (stockout - insufficient stock)
        if (current->quantity <= 0)
        {
            printf("Alert: Stockout for product %s (ID: %d). Current Quantity: %d\n", current->name, current->id, current->quantity);
//.............................................................................................................//
            fputs("\n\n\t\tAlert: Stockout for product ", file);
            fputs(current->name, file);
            fputs(" (ID: ", file);
            fprintf(file, "%d", current->id);
            fputs(" ). Current Quantity: ", file);
            fprintf(file, "%d", current->quantity);
//..................................................................................................................//
            alertCount++;
        }
        // Alert for excess stock (overstock)
        else if (current->quantity > 100) // You can set the threshold for overstock as needed
        {
            printf("Alert: Overstock for product %s (ID: %d). Current Quantity: %d\n", current->name, current->id, current->quantity);
//.....................................................................................................................................//
            fputs("\n\n\t\tAlert: Overstock for product ", file);
            fputs(current->name, file);
            fputs(" (ID: ", file);
            fprintf(file, "%d", current->id);
            fputs(" ). Current Quantity: ", file);
            fprintf(file, "%d", current->quantity);
//......................................................................................................................................//
            overstockCount++;
        }
        if (strcmp(current->Ex_date, currentDate) < 0)
        {
            printf("Alert: Expiry date reached for product %s (ID: %d). Expiry Date: %s\n", current->name, current->id, current->Ex_date);
            //...............................................................................................................................................//
            fprintf(file, "\n\nAlert: Expiry date reached for product %s (ID: %d). Expiry Date: %s\n", current->name, current->id, current->Ex_date);
            //..................................................................................................................................................//
            alertCount++;
        }
        current = current->next;
    }

    if (alertCount == 0 && overstockCount == 0)
    {
        printf("No alerts or notifications at this time.\n");
//.................................................................................//
        fputs("\n\t\tNo alerts or notifications at this time.\n", file);
//................................................................................//
    }
    fclose(file);
}

// Function to set or change the password and username
void setPasswordAndUsername()
{
//......................................................................//
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
//......................................................................//
    if (isSignedIn == 0)
    {
        char newPassword[26];
        char newUsername[26];

        printf("Enter a new username: ");
        scanf("%25s", newUsername);
        printf("Enter a new password: ");
        scanf("%25s", newPassword);
//..........................................................................//
        fputs("\n\t\t\tUsername :::   ", file);
        fputs(newUsername, file);
        fputs("\n\t\t\tPassword :::   ", file);
        fputs(newPassword, file);
//.............................................................................//

        if (strlen(newUsername) > 0 && strlen(newPassword) > 0)
        {
            strcpy(username, newUsername);
            strcpy(password, newPassword);
            printf("Username and password have been set/changed successfully.\n");
            fputs("\n\tUsername and password have been set/changed successfully\n\n", file);
        }
        else
        {
            printf("Username and password cannot be empty. They have not been changed.\n");
            fputs("\n\tUsername and password cannot be empty. They have not been changed\n\n", file);
        }
        isSignedIn = 1;
    }
    else
    {
        printf("\t\t\t Already Username and password have been set\n\n");
        fputs("\n\tAlready Username and password have been set\n\n", file);
    }
    fclose(file);
}

// Function to change the password
void changePassword()
{
    file = fopen("Inventory Management System.txt", "a");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    if (isSignedIn == 0)
    {
        printf("You must be signed in to change the password.\n\n");
        return;
    }

    char currentPassword[26];
    char newPassword[26];

    printf("\nEnter your current password: ");
    scanf("%25s", currentPassword);

    if (strcmp(currentPassword, password) == 0)
    {
        printf("\nEnter a new password: ");
        scanf("%25s", newPassword);

        if (strlen(newPassword) > 0)
        {
            strcpy(password, newPassword);
            fprintf(file,"\n\t\tchanged Password is:: %s\n\n",newPassword);
            fclose(file);
            printf("Password has been changed successfully.\n");
        }
        else
        {
            printf("New password cannot be empty. It has not been changed.\n");
        }
    }
    else
    {
        printf("Incorrect current password. Password change failed.\n");
    }
}


int login()
{
    int attempts = 0;


    if (strcmp(password, " ") == 0 || strcmp(username, " ") == 0)
    {
        printf("Password and Username are not set\n\n");
        return 0;
    }
    else
    {
        while (attempts < 3)
        {
            system("cls");
            printf("\n  **************************  LOGIN FORM  **************************  ");
            printf("\n                       ENTER USERNAME: ");
            char inputUsername[26];
            scanf("%s", inputUsername);
            fprintf(file, "\n\n\t\t\t\tEntered UseName is %s", inputUsername);

            printf("                       ENTER PASSWORD: ");
            fprintf(file, "\n\t\t\t\tEntered PASSWORD is ");
            char c;
            int i = 0;
            char inputPassword[26];
            while (1)
            {
                c = getch();
                if (c == 13)   // Enter key
                {
                    inputPassword[i] = '\0';
                    break;
                }
                else if (c == 8)     // Backspace key
                {
                    if (i > 0)
                    {
                        i--;
                        printf("\b \b");
                    }
                }
                else
                {
                    inputPassword[i] = c;
                    i++;
                    printf("*");
                }
            }
            fprintf(file, "%s", inputPassword);

            if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0)
            {
                printf("\n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL\n\n");
                fprintf(file, "\n\t\t\t      LOGIN IS SUCCESSFUL\n\n");
                fclose(file);
                return 1; // Access granted
            }
            else
            {
                printf("\n        SORRY !!!! LOGIN IS UNSUCCESSFUL\n");
                fprintf(file, "\n\t\t      LOGIN IS UNSUCCESSFUL\n\n");
                attempts++;

                if (attempts < 3)
                {
                    printf("Press any key to try again...\n");
                    fprintf(file, "\n\t\t      Again Trying.....\n\n");
                    getch();
                }
                else
                {
                    printf("Sorry, you have entered the wrong username and password too many times.\n");
                    fprintf(file, "\n\t\tSorry, you have entered the wrong username and password too many times.\n\n");
                    printf("Press any key to exit...\n");
                    getch();
                    //fclose(file);
                    return 0; // Access denied
                }
            }
        }
    }
    return 0; // Access denied
}


// Function to display the menu and get user's choice
int displayMenu()
{
    int choiceOp;

    printf("\n\n\n\n\n\n");

    printf("\t\t\t*****************************************\n");
    printf("\t\t\t      Inventory Management System        \n");
    printf("\t\t\t*****************************************\n\n");

    printf("\t\t\t\t1. Login For Access\n");
    printf("\t\t\t\t2. Sign in For New Access\n");
    printf("\t\t\t\t3. Change Password\n");
    printf("\t\t\t\t4. Exit\n\n");

    printf("\tEnter your choice: ");
    scanf("%d", &choiceOp);

    return choiceOp;
}
