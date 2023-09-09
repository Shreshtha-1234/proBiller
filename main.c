#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

// Define structures for Customer, Product, Cart, and Invoice
struct Customer
{
    char name[100];
    char mobileNumber[15];
    float pendingBalance;
    float rewards;
};

struct Product
{
    char name[100];
    char barcode[20];
    float price;
    int quantityInStock;
};
struct Invoice
{
    char invoiceId[20];
    char date[20];
    char customerName[100];
    char customerMobile[15];
    float totalAmount;
    float pendingAmount;
};

// Function to save products to products.txt
void saveProducts(struct Product products[], int productCount)
{
    FILE *file = fopen("products.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    char tempName[100];
    for (int i = 0; i < productCount; i++)
    {
        strcpy(tempName, products[i].name);
        for (int j = 0; tempName[j] != '\0'; j++)
        {
            if (tempName[j] == ' ')
                tempName[j] = '_';
        }
        fprintf(file, "%s %s %.2f %d\n", tempName, products[i].barcode, products[i].price, products[i].quantityInStock);
    }

    fclose(file);
}

// Function to load products from products.txt
void loadProducts(struct Product products[], int *productCount)
{
    FILE *file = fopen("products.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }
    char tempName[100];
    while (fscanf(file, "%s %s %f %d", tempName, products[*productCount].barcode, &products[*productCount].price, &products[*productCount].quantityInStock) != EOF)
    {
        for (int j = 0; tempName[j] != '\0'; j++)
        {
            if (tempName[j] == '_')
                tempName[j] = ' ';
        }
        strcpy(products[*productCount].name, tempName);

        (*productCount)++;
    }
    printf("Loaded %d products from %s\n", *productCount, "products.txt");
    fclose(file);
}

// Function to load customer data from customers.txt
void loadCustomers(struct Customer customers[], int *customerCount)
{
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading: %s\n", "customers.txt");
        return;
    }

    *customerCount = 0; // Reset customer count
    char tempName[100];
    while (*customerCount < 100 && fscanf(file, "%s %s %f %f", tempName,
                                          customers[*customerCount].mobileNumber,
                                          &customers[*customerCount].pendingBalance,
                                          &customers[*customerCount].rewards) == 4)
    {
        for (int j = 0; tempName[j] != '\0'; j++)
        {
            if (tempName[j] == '_')
                tempName[j] = ' ';
        }
        strcpy(customers[*customerCount].name, tempName);
        (*customerCount)++;
    }

    fclose(file);
    printf("Loaded %d customers from %s\n", *customerCount, "customers.txt");
    return;
}

// Function to save customer data to customers.txt
void saveCustomers(const struct Customer customers[], int customerCount)
{
    FILE *file = fopen("customers.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing: %s\n", "customers.txt");
        return;
    }
    char tempName[100];
    for (int i = 0; i < customerCount; i++)
    {
        strcpy(tempName, customers[i].name);
        for (int j = 0; tempName[j] != '\0'; j++)
        {
            if (tempName[j] == ' ')
                tempName[j] = '_';
        }
        fprintf(file, "%s %s %.2f %.2f\n", tempName, customers[i].mobileNumber, customers[i].pendingBalance, customers[i].rewards);
    }

    fclose(file);

    return;
}

// Function to save invoices to invoices.txt
void saveInvoices(const struct Invoice invoices[], int invoiceCount)
{
    FILE *file = fopen("invoices.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    char tempName[100];

    for (int i = 0; i < invoiceCount; i++)
    {
        strcpy(tempName, invoices[i].customerName);
        for (int j = 0; tempName[j] != '\0'; j++)
        {
            if (tempName[j] == ' ')
                tempName[j] = '_';
        }
        fprintf(file, "%s %s %s %s %.2f %.2f\n",
                invoices[i].invoiceId, invoices[i].date, tempName,
                invoices[i].customerMobile, invoices[i].totalAmount, invoices[i].pendingAmount);
    }

    fclose(file);
}

// Function to load invoices from invoices.txt
void loadInvoices(struct Invoice invoices[], int *invoiceCount)
{
    FILE *file = fopen("invoices.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    struct Invoice currentInvoice;
    int loadedCount = 0;
    char tempName[100];

    while (fscanf(file, "%19s %19s %99s %14s %f %f\n",
                  currentInvoice.invoiceId, currentInvoice.date, tempName,
                  currentInvoice.customerMobile, &currentInvoice.totalAmount, &currentInvoice.pendingAmount) != EOF)
    {
        for (int j = 0; tempName[j] != '\0'; j++)
        {
            if (tempName[j] == '_')
                tempName[j] = ' ';
        }
        strcpy(invoices[*invoiceCount].customerName, tempName);
        invoices[loadedCount++] = currentInvoice;
    }

    fclose(file);
    *invoiceCount = loadedCount;

    printf("Loaded %d invoices from invoices.txt\n", *invoiceCount);

    return;
}

// Function to take product name invloving all cases
char *NameHandler()
{
    int c = 0;
    while ((c = getchar()) != '\n')
    {
        // Discard characters until a newline or end of file is encountered
    }
    char inputString[100];
    fgets(inputString, sizeof(inputString), stdin);

    // Remove the trailing newline character and adding null character
    size_t len = strlen(inputString);
    inputString[len - 1] = '\0';

    int start = 0;
    int end = len - 2;

    while (inputString[start] == ' ')
    {
        start++;
    }
    while (end > start && inputString[end] == ' ')
    {
        end--;
    }
    char str[100];
    if (!(start == 0 && end == len - 2))
    {
        // handles leading and trailing spaces
        int index = 0;
        while (start <= end)
        {
            str[index++] = inputString[start++];
        }
        str[index] = '\0';
    }
    else
    {
        strcpy(str, inputString);
    }

    // now removing intermediate spaces
    int spaceCount = 0;
    char tempstr[100];
    strcpy(tempstr, str);
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (spaceCount != 0 && str[i] != ' ')
            spaceCount = 0;
        if (str[i] == ' ')
        {
            if (spaceCount == 0)
            {
                tempstr[index++] = str[i];
                spaceCount++;
            }
        }
        else
        {
            if (str[i] >= 'a' && str[i] <= 'z')
                str[i] = str[i] - 32;
            tempstr[index++] = str[i];
        }
    }
    tempstr[index] = '\0';
    char *stringReturn = malloc(100);
    strcpy(stringReturn, tempstr);

    return stringReturn;
}

// Function to validate mobile number entered by user
bool isValidMobileNumber(const char number[])
{
    // length should be exactly 10
    if (strlen(number) != 10)
    {
        return false;
    }

    // mobile number should contain only digits
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(number[i]))
        {
            return false;
        }
    }

    // mobile number starts with 6 7 8 or 9
    if (number[0] >= '0' && number[0] <= '5')
    {
        return false;
    }

    return true;
}

// Function to validate barcode
bool isValidBarCode(const char code[])
{

    // barcode should contain only digits
    for (int i = 0; i < strlen(code); i++)
    {
        if (!isdigit(code[i]))
        {
            return false;
        }
    }

    // barcode should not start with 0
    if (code[0] == '0')
    {
        return false;
    }

    return true;
}

// Function to validate invoiceId
bool isValidInvoiceId(char invoice[])
{
    // the length of barcode should be atleast 4 coz its syntax is GST followed by some digits
    if (strlen(invoice) < 4)
        return false;

    // to convert "gst" to "GST"
    if (invoice[0] == 'g' && invoice[1] == 's' && invoice[2] == 't')
    {
        invoice[0] = 'G';
        invoice[1] = 'S';
        invoice[2] = 'T';
    }

    // to check whether invoice id starts with "GST" only
    if (!(invoice[0] == 'G' && invoice[1] == 'S' && invoice[2] == 'T'))
    {
        return false;
    }

    // invoice id should contain only digits after "GST"
    for (int i = 3; i < strlen(invoice); i++)
    {
        if (!isdigit(invoice[i]))
        {
            return false;
        }
    }

    // the first invoice generated is GST1 so it cant have 0 at 3rd index
    if (invoice[3] == '0')
    {
        return false;
    }

    return true;
}

// Function to validate date entered by user under format "YYYY-MM-DD"
bool isValidDateFormat(const char *date)
{
    // Check if the date string has the correct length (10 characters) and has hyphens in the right positions
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    // Check if the year, month, and day parts are valid integers
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    {
        return false;
    }

    // Check if the year, month, and day are within valid ranges
    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    return true;
}

// Function to validate quantity input
int validQuantityInput()
{
    bool flag = true;
    char str[100];
    scanf("%s", &str);
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            flag = false;
            break;
        }
    }
    while (flag == false)
    {
        printf("Invalid value! Enter a numeric value :");
        scanf("%s", &str);
        bool found = false;
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (!isdigit(str[i]))
            {
                found = true;
                break;
            }
        }
        if (found == false)
            break;
    }

    return atoi(str);
}

// Function to validate amounts (floats)
float validInput(char label[])
{
    int flag = true;
    char str[100];
    scanf("%s", &str);
    int decimalPointCount = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] == '.' && decimalPointCount == 0)
            {
                decimalPointCount++;
                // Allow one decimal point
            }
            else
            {
                flag = false;
                break;
            }
        }
    }

    while (flag == false)
    {
        printf("Invalid %s ! Enter a numeric value for %s :", label, label);
        scanf("%s", &str);
        bool found = false;
        decimalPointCount = 0;
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (!isdigit(str[i]))
            {
                if (str[i] == '.' && decimalPointCount == 0)
                {
                    decimalPointCount++;
                    // Allow one decimal point
                }
                else
                {
                    found = true;
                    break;
                }
            }
        }
        if (found == false)
            break;
    }

    return atof(str);
}

// Function to add a new customer
void addCustomer(struct Customer customers[], int *customerCount)
{
    char mobileNumber[15];

    do
    {
        printf("Enter Mobile Number : ");
        scanf("%s", mobileNumber);

        if (!isValidMobileNumber(mobileNumber))
        {
            printf("Invalid mobile number. It should have 10 digits and should start with 6 , 7 , 8 or 9 \n");
        }
    } while (!isValidMobileNumber(mobileNumber));

    // Check if the mobile number already exists in the customers.txt
    for (int i = 0; i < *customerCount; i++)
    {
        if (strcmp(mobileNumber, customers[i].mobileNumber) == 0)
        {
            printf("Customer with the same mobile number already exists. Cannot add the customer.\n");
            return; // Exit the function without adding the customer
        }
    }

    if (*customerCount < 100)
    {
        printf("Enter Customer Name: ");
        strcpy(customers[*customerCount].name, NameHandler());

        strcpy(customers[*customerCount].mobileNumber, mobileNumber); // Copy the mobile number
        customers[*customerCount].pendingBalance = 0;
        customers[*customerCount].rewards = 0;

        (*customerCount)++;
        saveCustomers(customers, *customerCount);
        printf("Customer added successfully!\n");
    }
    else
    {
        printf("Customer database is full. Cannot add more customers.\n");
    }
}

// Function to add a new product
void addProduct(struct Product products[], int *productCount)
{

    printf("Enter Product Name: ");
    strcpy(products[*productCount].name, NameHandler());

    char newBarcode[20];
    do
    {
        printf("Enter Barcode (unique identifier): ");
        scanf("%s", newBarcode);

        if (!isValidBarCode(newBarcode))
        {
            printf("Invalid bar code. It should have only digits and should not start with 0 \n");
        }
    } while (!isValidBarCode(newBarcode));

    // Check if the barcode already exists in the database
    for (int i = 0; i < *productCount; i++)
    {
        if (strcmp(newBarcode, products[i].barcode) == 0)
        {
            printf("Product with the same barcode already exists.You can update the qunatity using 9.\n");
            return; // Exit the function without adding the product
        }
    }

    if (*productCount < 100)
    {
        // If barcode is unique, copy it to the product structure
        strcpy(products[*productCount].barcode, newBarcode);

        printf("Enter Price: ");
        products[*productCount].price = validInput("Price");
        printf("Enter Quantity in Stock: ");
        products[*productCount].quantityInStock = validQuantityInput();

        (*productCount)++;
        saveProducts(products, *productCount);
        printf("\nProduct added successfully!\n");
    }
    else
    {
        printf("Product database is full. Cannot add more products.\n");
    }
}

// Function to update the quantity of an existing product
void updateProductQuantity(struct Product products[], int productCount)
{

    char updateBarcode[20];
    do
    {
        printf("Enter the Barcode of the product you want to update: ");
        scanf("%s", updateBarcode);

        if (!isValidBarCode(updateBarcode))
        {
            printf("Invalid bar code. It should have only digits and should not start with 0 \n");
        }
    } while (!isValidBarCode(updateBarcode));

    int found = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(updateBarcode, products[i].barcode) == 0)
        {
            printf("Product found:\n");
            printf("Product Name: %s\n", products[i].name);
            printf("Current Quantity in Stock: %d\n", products[i].quantityInStock);

            int newQuantity;
            printf("Enter the new Quantity to be added in Stock: ");
            newQuantity = validQuantityInput();

            // Update the product's quantity
            products[i].quantityInStock += newQuantity;
            printf("Quantity updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Product with the given barcode does not exist. Add a new product using 2 Add Product. \n");
    }

    saveProducts(products, productCount);
}

// Function to print an invoice based on the provided invoice ID
void printInvoice(struct Invoice invoiceData, int itemCount, struct Product itemsPurchased[], char invoiceId[],
                  float gst, float discount, float amountPaid, float rewards, float rewardsEarned)
{
    printf("\n\n====================== CRAZY STORE ======================\n");
    printf("\n========================= Invoice ========================\n");

    printf("Invoice ID: %s\n", invoiceData.invoiceId);
    printf("Date: %s\n", invoiceData.date);
    printf("Customer Name: %s\n", invoiceData.customerName);
    printf("Customer Mobile Number: %s\n", invoiceData.customerMobile);
    printf("\n----------------------------------------------------------\n");
    printf("Items Purchased:\n\n");
    printf("  %-20s %-10s %-10s %-10s\n", "Product Name", "Quantity", "Price", "Total");
    float amt = 0.0;
    for (int j = 0; j < itemCount; j++)
    {
        printf("  %-20s %-10d %-10.2f %-10.2f\n",
               itemsPurchased[j].name,
               itemsPurchased[j].quantityInStock,
               itemsPurchased[j].price,
               itemsPurchased[j].quantityInStock * itemsPurchased[j].price);

        amt += itemsPurchased[j].quantityInStock * itemsPurchased[j].price;
    }
    printf("\n---------------------------------------------------------\n");
    float gstAmount = (gst / 100.0 * amt);
    float discountAmount = (discount / 100.0 * amt);
    float totalAmt = amt + gstAmount - discountAmount;
    printf("Sub Total Amount: %.2f\n", amt);
    printf("GST: %.2f\n", gstAmount);
    printf("Discount: %.2f\n", discountAmount);
    printf("Total Amount: %.2f\n", totalAmt);
    if (rewards > 0)
        printf("Rewards Point used: %.2f\n", rewards);
    printf("Amount Paid: %.2f\n", amountPaid);
    printf("Amount Pending: %.2f\n", totalAmt - amountPaid - rewards);
    printf("\n----------------------------------------------------------\n");
    printf("            %.2f REWARD POINTS EARNED               \n", rewardsEarned);
    printf("        HURRAY! TODAY YOU SAVED RS. %.2f            \n", discountAmount);
    printf("\n----------------------------------------------------------\n");
    printf("            THANKS FOR SHOPPING FROM US !!!            \n\n");
}

// Function to create a new invoice with the system default date
void createInvoice(struct Invoice invoices[], int *invoiceCount, struct Product products[], int productCount, struct Customer customers[], int customerCount)
{
    printf("\n   CREATING INVOICE   \n");
    if (*invoiceCount < 100)
    {
        // Get the current time and store it as the date
        time_t t;
        struct tm *tm_info;

        time(&t);
        tm_info = localtime(&t);

        char date_str[11];
        strftime(date_str, sizeof(date_str), "%Y-%m-%d", tm_info);

        // Generate an invoice ID using "GST" followed by invoice count
        sprintf(invoices[*invoiceCount].invoiceId, "GST%d", *invoiceCount + 1);
        char *invoiceId = invoices[*invoiceCount].invoiceId;

        // Use the system default date
        strcpy(invoices[*invoiceCount].date, date_str);
        invoices[*invoiceCount].date[sizeof(invoices[*invoiceCount].date) - 1] = '\0';

        // Ask for the customer's mobile number
        char customerMobile[15];

        do
        {
            printf("Enter Customer Mobile Number: ");
            scanf("%s", customerMobile);

            if (!isValidMobileNumber(customerMobile))
            {
                printf("Invalid mobile number. It should have 10 digits and should start with 6 , 7 , 8 or 9 \n");
            }
        } while (!isValidMobileNumber(customerMobile));

        // Search for the customer's name based on the provided mobile number
        char customerName[100];
        int customerFound = 0;
        int customerIndex = -1;
        for (int i = 0; i < customerCount; i++)
        {
            if (strcmp(customerMobile, customers[i].mobileNumber) == 0)
            {
                strcpy(customerName, customers[i].name);
                customerIndex = i;
                customerFound = 1;
                break;
            }
        }

        if (!customerFound)
        {
            printf("Customer with the provided mobile number not found. Invoice creation failed.\n");
            return;
        }

        // Use the fetched customer name
        printf("Customer Name: %s\n", customerName);
        printf("\n");
        strcpy(invoices[*invoiceCount].customerName, customerName);
        strcpy(invoices[*invoiceCount].customerMobile, customerMobile);

        int itemCount = 0;
        float totalAmount = 0.0;
        struct Product productPurchased[100];
        while (1)
        {

            if (itemCount != 0)
            {
                printf("Add More products (y/n): ");
                char strchoice[100];
                char choice;
                scanf("%s", &strchoice);
                if (strlen(strchoice) > 1)
                {
                    printf("only single character y or n allowed\n");
                    continue;
                }
                else
                {
                    choice = strchoice[0];

                    if (choice == 'n' || choice == 'N')
                    {
                        break;
                    }

                    if (choice != 'y' && choice != 'Y')
                    {
                        printf("Invalid choice. Please enter 'y' to add an item or 'n' to finish.\n");
                        continue;
                    }
                }
            }

            if (itemCount < 100)
            {

                char itemBarcode[20];
                do
                {
                    printf("\n");
                    printf("Enter Barcode : ");
                    scanf("%s", itemBarcode);

                    if (!isValidBarCode(itemBarcode))
                    {
                        printf("Invalid bar code. It should have only digits and should not start with 0 \n");
                    }
                } while (!isValidBarCode(itemBarcode));

                int itemPresentIndex = -1;

                // check whether that item is already in the bill
                for (int i = 0; i < itemCount; i++)
                {
                    if (strcmp(itemBarcode, productPurchased[i].barcode) == 0)
                    {
                        itemPresentIndex = i;
                        break;
                    }
                }

                // check whether the given barcode exists in products[]
                int productIndex = -1;
                for (int i = 0; i < productCount; i++)
                {
                    if (strcmp(itemBarcode, products[i].barcode) == 0)
                    {
                        productIndex = i;
                        break;
                    }
                }

                if (productIndex == -1)
                {
                    printf("Product with the provided barcode not found. Please check the barcode and try again.\n");
                    continue;
                }

                printf("Item : %s\n", products[productIndex].name);

                // if this is existing product

                if (itemPresentIndex != -1)
                {
                    printf("This item already added in the bill\n");
                    printf("Do you want to update quantity ? (y/n)");
                    char updateChoice;
                    char strchoice[100];
                    scanf("%s", &strchoice);
                    if (strlen(strchoice) > 1)
                    {
                        printf("only single character y or n allowed\n");
                        continue;
                    }
                    updateChoice = strchoice[0];

                    if (updateChoice == 'n' || updateChoice == 'N')
                    {
                        continue;
                    }

                    if (updateChoice != 'y' && updateChoice != 'Y')
                    {
                        printf("Invalid choice. Please enter 'y' to update or 'n' to continue adding more items.\n");
                        return;
                    }

                    // new quantity
                    int quantityBought;
                    printf("Enter new quantity: ");
                    quantityBought = validQuantityInput();

                    if (quantityBought > 0 && quantityBought <= products[productIndex].quantityInStock)
                    {
                        int prevQuantity = productPurchased[itemPresentIndex].quantityInStock;
                        float pricePerItem = products[productIndex].price;

                        // deduct amount from current totalAmount
                        totalAmount -= pricePerItem * prevQuantity;

                        // update stock back
                        products[productIndex].quantityInStock += prevQuantity;

                        // Update total amount and add item to the invoice
                        totalAmount += pricePerItem * quantityBought;

                        productPurchased[itemPresentIndex].quantityInStock = quantityBought;

                        // Update product quantity in stock
                        products[productIndex].quantityInStock -= quantityBought;
                    }
                    else
                    {
                        printf("Sorry Low Stock.\n");
                        printf("Do you wanna update stock for barcode %s ? (y/n)\n", itemBarcode);

                        char printChoice;
                        char strchoice[100];
                        scanf("%s", &strchoice);
                        if (strlen(strchoice) > 1)
                        {
                            printf("only single character y or n allowed\n");
                            continue;
                        }
                        printChoice = strchoice[0];

                        scanf(" %c", &printChoice);

                        if (printChoice == 'n' || printChoice == 'N')
                        {
                            return;
                        }

                        if (printChoice != 'y' && printChoice != 'Y')
                        {
                            printf("Invalid choice. Please enter 'y' to print invoice or 'n' to finish.\n");
                            return;
                        }

                        int newQuantity;
                        printf("Enter the new Quantity to be added in Stock: ");
                        newQuantity = validQuantityInput();

                        // Update the product's quantity
                        products[productIndex].quantityInStock += newQuantity;
                        printf("Quantity updated successfully!\n");
                        printf("Now you can add it in invoice!\n");
                    }
                    saveProducts(products, productCount);
                    continue;
                }

                // if this is a new item

                printf("Enter Quantity Bought: ");
                int quantityBought;
                quantityBought = validQuantityInput();

                if (quantityBought > 0 && quantityBought <= products[productIndex].quantityInStock)
                {
                    // Calculate the total amount for this item
                    float pricePerItem = products[productIndex].price;
                    float itemTotal = pricePerItem * quantityBought;

                    // Update total amount and add item to the invoice
                    totalAmount += itemTotal;

                    strcpy(productPurchased[itemCount].name, products[productIndex].name);
                    strcpy(productPurchased[itemCount].barcode, products[productIndex].barcode);
                    productPurchased[itemCount].quantityInStock = quantityBought;
                    productPurchased[itemCount].price = products[productIndex].price;

                    // Update product quantity in stock
                    products[productIndex].quantityInStock -= quantityBought;
                    itemCount++;
                }
                else
                {
                    printf("Sorry Low Stock.\n");
                    printf("Do you wanna update stock for barcode %s ? (y/n)\n", itemBarcode);

                    char printChoice;
                    char strchoice[100];
                    scanf("%s", &strchoice);
                    if (strlen(strchoice) > 1)
                    {
                        printf("only single character y or n allowed\n");
                        continue;
                    }
                    printChoice = strchoice[0];

                    scanf(" %c", &printChoice);

                    if (printChoice == 'n' || printChoice == 'N')
                    {
                        return;
                    }

                    if (printChoice != 'y' && printChoice != 'Y')
                    {
                        printf("Invalid choice. Please enter 'y' to print invoice or 'n' to finish.\n");
                        return;
                    }

                    int newQuantity;
                    printf("Enter the new Quantity to be added in Stock: ");
                    newQuantity = validQuantityInput();

                    // Update the product's quantity
                    products[productIndex].quantityInStock += newQuantity;
                    printf("Quantity updated successfully!\n");
                    printf("Now you can add it in invoice!\n");
                }
                saveProducts(products, productCount);
            }
            else
            {
                printf("Cart is full. Cannot add more items.\n");
                break;
            }
        }

        printf("\n");
        float gst = 0.0, discount = 0.0;
        printf("Enter GST (in percentage): ");
        gst = validInput("GST");

        while (gst != 0 && gst != 5 && gst != 12 && gst != 18 && gst != 28)
        {
            printf(" GST can only be 0%% / 5%% / 12%% / 18%% / 28%%\n");
            printf("Enter GST: ");
            gst = validInput("GST");
        }

        printf("Enter Discount (in percentage): ");
        discount = validInput("Discount");

        while (discount < 0)
        {
            printf("Negative discount Not Allowed\n");
            printf("Enter Discount: ");
            discount = validInput("Discount");
        }

        while (discount > 100)
        {
            printf("Discount more than 100%% Not Allowed\n");
            printf("Enter Discount: ");
            discount = validInput("Discount");
        }
        float amt = totalAmount;
        float gstAmount = (gst / 100.0 * amt);
        float discountAmount = (discount / 100.0 * amt);
        float totalAmt = amt + gstAmount - discountAmount;
        printf("Sub Total Amount: Rs.%.2f\n", amt);
        printf("GST: Rs.%.2f\n", gstAmount);
        printf("Discount: Rs.%.2f\n", discountAmount);
        printf("Total Amount: Rs.%.2f\n", totalAmt);

        invoices[*invoiceCount].totalAmount = totalAmt;

        float paidByRewardPoints = 0;
        float availableRewardPoints = customers[customerIndex].rewards;
        if (availableRewardPoints > 0)
        {
            printf("\n");
            printf("Reward Points Available : %.2f\n", availableRewardPoints);

            printf("Do you want to pay by Reward Points (y/n) ?");

            char rewardChoice;
            scanf(" %c", &rewardChoice);

            if (rewardChoice == 'n' || rewardChoice == 'N')
            {
                printf("Reward Points Not Used!\n");
            }

            else if (rewardChoice != 'y' && rewardChoice != 'Y')
            {
                printf("Invalid choice. Please enter 'y' to use Reward Points else 'n'.\n");
                return;
            }

            else
            {
                if (availableRewardPoints >= totalAmt)
                {
                    paidByRewardPoints = totalAmt;
                    availableRewardPoints -= totalAmt;
                    totalAmt = 0;
                }
                else
                {
                    paidByRewardPoints = availableRewardPoints;
                    availableRewardPoints = 0;
                    totalAmt -= paidByRewardPoints;
                }
                printf("Used Rewards point : Rs.%0.2f\n", paidByRewardPoints);
                printf("After Using Rewards Point : Rs.%0.2f\n", totalAmt);
                customers[customerIndex].rewards = availableRewardPoints;
            }
        }
        float amountPaid = 0;
        if (totalAmt != 0)
        {

            printf("Enter Amount Paid: Rs.");
            amountPaid = validInput("Paid Amount");

            while (amountPaid < 0)
            {
                printf("Negative Amount Not Allowed\n");
                printf("Enter amount paid: ");
                amountPaid = validInput("Paid Amount");
            }

            while (amountPaid > totalAmt)
            {
                printf("You are paying more than bill amount\n");
                printf("Enter amount paid: ");
                amountPaid = validInput("Paid Amount");
            }

            totalAmt -= amountPaid;

            invoices[*invoiceCount].pendingAmount = totalAmt;
            customers[customerIndex].rewards += 1.0 / 100 * amountPaid;
            printf("Earned Rewards point : Rs.%0.2f\n", (1.0 / 100 * amountPaid));

            printf("Pending Amount : Rs. %.2f\n", totalAmt);
        }

        // saveInvoice(&invoices[*invoiceCount]);
        customers[customerIndex].pendingBalance += totalAmt;

        (*invoiceCount)++;
        saveInvoices(invoices, *invoiceCount);

        saveCustomers(customers, customerCount);

        printf("\nInvoice created successfully!\n");

        printf("Print invoice (y/n): \n");
        char printChoice;

        char strchoice[100];
        scanf("%s", strchoice);
        while (strlen(strchoice) > 1)
        {
            printf("only single character y or n allowed\n");
            printf("Print invoice (y/n): ");
            scanf("%s", strchoice);
        }

        printChoice = strchoice[0];

        if (printChoice == 'n' || printChoice == 'N')
        {
            return;
        }

        if (printChoice != 'y' && printChoice != 'Y')
        {
            printf("Invalid choice. Please enter 'y' to print invoice or 'n' to finish.\n");
            return;
        }
        int count = *invoiceCount;

        printInvoice(invoices[count - 1], itemCount, productPurchased, invoiceId, gst, discount, amountPaid, paidByRewardPoints, (1.0 / 100 * amountPaid));
    }
    else
    {
        printf("Invoice database is full. Cannot create more invoices.\n");
    }
}

// Function to display all customers
void displayCustomers(const struct Customer customers[], int customerCount)
{
    printf("===== Customer List =====\n");
    printf("%-20s %-15s %-15s %-15s\n", "Customer Name", "Mobile Number", "Pending Balance", "Reward Points");

    for (int i = 0; i < customerCount; i++)
    {
        printf("%-20s %-15s %-15.2f %.2f\n", customers[i].name, customers[i].mobileNumber, customers[i].pendingBalance, customers[i].rewards);
    }
}

// Function to display all products
void displayProducts(const struct Product products[], int productCount)
{
    printf("===== Product List =====\n");
    printf("%-20s %-15s %-10s %-10s\n", "Product Name", "Barcode", "Price", "Quantity in Stock");

    for (int i = 0; i < productCount; i++)
    {
        printf("%-20s %-15s %-10.2f %-10d\n", products[i].name, products[i].barcode, products[i].price, products[i].quantityInStock);
    }
}

// Function to display all invoice IDs, customer numbers, amounts, and dates
void displayAllInvoices(struct Invoice invoices[], int invoiceCount)
{
    printf("%-15s %-12s %-15s %-15s %-15s\n", "Invoice ID", "Date", "Customer Mobile", "Total Amount", "Balance Amount");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < invoiceCount; i++)
    {
        printf("%-15s %-12s %-15s %-15.2f %-15.2f\n",
               invoices[i].invoiceId,
               invoices[i].date,
               invoices[i].customerMobile,
               invoices[i].totalAmount,
               invoices[i].pendingAmount);
    }
}

// Function to display sales by date
void displaySalesByDate(struct Invoice invoices[], int invoiceCount)
{
    // Implementation here

    char date[12];

    do
    {
        printf("Enter the date (format: YYYY-MM-DD): ");
        scanf("%s", date);

        if (!isValidDateFormat(date))
        {
            printf("Invalid date format. Please enter a valid date in the format YYYY-MM-DD.\n");
        }
    } while (!isValidDateFormat(date));

    float totalSales = 0.0;
    int found = 0;

    printf("===== Sales for Date: %s =====\n", date);

    for (int i = 0; i < invoiceCount; i++)
    {
        if (strcmp(date, invoices[i].date) == 0)
        {
            if (found == 0)
                printf("%-10s %-20s %-15s %-10s\n", "Invoice ID", "Customer Name", "Customer Mobile", "Total Amount");
            printf("%-10s %-20s %-15s %.2f\n", invoices[i].invoiceId, invoices[i].customerName, invoices[i].customerMobile, invoices[i].totalAmount);
            totalSales += invoices[i].totalAmount;
            found = 1;
        }
    }

    if (!found)
    {
        printf("No sales found for the provided date.\n");
    }
    else
    {
        printf("Total Sales for %s: %.2f\n", date, totalSales);
    }
}

// Function to update balance of an invoice
void updateBalance(struct Invoice invoices[], int invoiceCount, struct Customer customers[], int customerCount)
{
    char invoiceId[10];
    float depositAmount;
    int invoiceIndex = -1;
    int customerIndex = -1;

    isValidInvoiceId(invoiceId);
    do
    {
        printf("Enter the Invoice ID: (GST___) : ");
        scanf("%s", invoiceId);

        if (!isValidInvoiceId(invoiceId))
        {
            printf("Invoice Id have atleast length 4 and should start with GST followed by non-zero digits \n");
        }
    } while (!isValidInvoiceId(invoiceId));

    // Finding the required invoice
    for (int i = 0; i < invoiceCount; i++)
    {
        if (strcmp(invoiceId, invoices[i].invoiceId) == 0)
        {
            invoiceIndex = i;
            break;
        }
    }

    if (invoiceIndex == -1)
    {
        printf("Invoice with the provided ID not found.\n");
        return;
    }

    // Display the current amount pending
    float currentPendingAmount = invoices[invoiceIndex].pendingAmount;
    printf("Current Amount Pending for Invoice %s: %.2f\n", invoiceId, currentPendingAmount);

    // Ask the user for the deposit amount
    printf("Enter the Deposit Amount: ");
    depositAmount = validInput("Deposit Amount");

    if (depositAmount <= 0.0)
    {
        printf("Invalid deposit amount. Please enter a positive amount.\n");
        return;
    }

    // Check if the deposit amount is less than or equal to the current pending amount
    if (depositAmount <= currentPendingAmount)
    {

        invoices[invoiceIndex].pendingAmount -= depositAmount;

        // Find the customer index using customerMobile from invoices
        const char *customerMobile = invoices[invoiceIndex].customerMobile;
        for (int i = 0; i < customerCount; i++)
        {
            if (strcmp(customerMobile, customers[i].mobileNumber) == 0)
            {
                customerIndex = i;
                break;
            }
        }

        if (customerIndex != -1)
        {

            customers[customerIndex].pendingBalance -= depositAmount;
            customers[customerIndex].rewards += (0.01 * depositAmount);
            printf("Deposit of %.2f successfully applied to Invoice %s.\n", depositAmount, invoiceId);
            printf("Reward Points Earned : %.2f\n", (0.01 * depositAmount));
        }

        if (customerIndex == -1)
        {
            printf("Customer not found \n");
        }
    }
    else
    {
        printf("Deposit amount exceeds the current pending amount for Invoice %s.\n", invoiceId);
    }
    saveInvoices(invoices, invoiceCount);
    saveCustomers(customers, customerCount);
}

// Function to display all invoices of a customer
void displayInvoicesByCustomer(struct Invoice invoices[], int invoiceCount)
{
    float totalPurchasedAmount = 0.0;
    float totalPendingAmount = 0.0;
    int found = 0;

    char mobileNumber[15];

    do
    {
        printf("Enter Mobile Number : ");
        scanf("%s", mobileNumber);

        if (!isValidMobileNumber(mobileNumber))
        {
            printf("Invalid mobile number. It should have 10 digits and should start with 6 , 7 , 8 or 9 \n");
        }
    } while (!isValidMobileNumber(mobileNumber));

    printf("===== Displaying all invoices for %s =====\n", mobileNumber);

    for (int i = 0; i < invoiceCount; i++)
    {
        if (strcmp(mobileNumber, invoices[i].customerMobile) == 0)
        {
            if (found == 0)
            {
                printf("Customer Name: %s\n", invoices[i].customerName);
                printf("%-10s %-20s %-15s %-15s %-15s\n", "Invoice ID", "Date", "Bill Amount", "Amount Paid", "Amount Pending");
            }

            float amountPaid = invoices[i].totalAmount - invoices[i].pendingAmount;

            printf("%-10s %-20s %-15.2f %-15.2f %-15.2f\n", invoices[i].invoiceId, invoices[i].date, invoices[i].totalAmount, amountPaid, invoices[i].pendingAmount);
            totalPurchasedAmount += invoices[i].totalAmount;
            totalPendingAmount += invoices[i].pendingAmount;
            found = 1;
        }
    }

    if (!found)
    {
        printf("No invoices found for the customer with the provided mobile number.\n");
    }
    else
    {
        printf("Total Purchased Amount: %.2f\n", totalPurchasedAmount);
        printf("Total Pending Amount: %.2f\n", totalPendingAmount);
    }
}

int main()
{

    bool isLoggedIn = false;
    char username[100];
    char password[100];

    printf("Enter username : ");
    fgets(username, sizeof(username), stdin);
    username[strlen(username) - 1] = '\0';

    printf("Enter password : ");
    fgets(password, sizeof(password), stdin);
    password[strlen(password) - 1] = '\0';

    if ((strcmp(username, "ADMIN") == 0) && (strcmp(password, "PROBILLER28") == 0))
    {
        isLoggedIn = true;
        printf("LOGIN SUCESSFULL !!!!\n");
        printf("Welcome ADMIN !\n");
    }
    int cnt = 0;
    while (!isLoggedIn)
    {
        cnt++;
        printf("ACCES DENIED\n");
        if (cnt == 3)
        {
            printf("You have exceeded the limits of wrong details. Kindly Restart the software.");
            break;
        }
        printf("Please enter your credentials again:\n");
        printf("Enter username : ");
        fgets(username, sizeof(username), stdin);
        username[strlen(username) - 1] = '\0';

        printf("Enter password : ");
        fgets(password, sizeof(password), stdin);
        password[strlen(password) - 1] = '\0';
        if ((strcmp(username, "ADMIN") == 0) && (strcmp(password, "PROBILLER28") == 0))
        {
            isLoggedIn = true;
            printf("LOGIN SUCESSFULL !!!!\n");
            printf("Welcome ADMIN !\n");
        }
    }

    if (!isLoggedIn)
        return 0;

    struct Customer customers[100];
    struct Product products[100];
    struct Invoice invoices[100];
    int customerCount = 0;
    int productCount = 0;
    int invoiceCount = 0;

    // Load data from text files at the start of the program
    loadCustomers(customers, &customerCount);
    loadProducts(products, &productCount);
    loadInvoices(invoices, &invoiceCount);

    int choice;
    do
    {
        printf("\n===== Billing Software Menu =====\n");
        printf("1. Add Customer\n");
        printf("2. Add Product\n");
        printf("3. Create Invoice\n");
        printf("4. Display All Customers\n");
        printf("5. Display All Products\n");
        printf("6. Update Quantity of Product\n");
        printf("7. Display Sales Date Wise\n");
        printf("8. Display Invoices by Customer\n");
        printf("9. Update Invoice Balance\n");
        printf("10. Display All Invoices\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        choice = validQuantityInput();

        switch (choice)
        {
        case 1:
            addCustomer(customers, &customerCount);
            break;
        case 2:
            addProduct(products, &productCount);
            break;
        case 3:
            createInvoice(invoices, &invoiceCount, products, productCount, customers, customerCount);
            break;
        case 4:
            displayCustomers(customers, customerCount);
            break;
        case 5:
            displayProducts(products, productCount);
            break;
        case 6:
            updateProductQuantity(products, productCount);
            break;
        case 7:
            displaySalesByDate(invoices, invoiceCount);
            break;
        case 8:
            displayInvoicesByCustomer(invoices, invoiceCount);
            break;
        case 9:
            updateBalance(invoices, invoiceCount, customers, customerCount);
            break;
        case 10:
            displayAllInvoices(invoices, invoiceCount);
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Save data to text files before exiting the program
    saveInvoices(invoices, invoiceCount);
    saveProducts(products, productCount);
    saveCustomers(customers, customerCount);

    return 0;
}
