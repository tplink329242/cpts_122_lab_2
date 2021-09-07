#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <CUnit/Basic.h>

typedef enum boolean
{
    FALSE, TRUE

} Boolean;

typedef struct contact
{
    char name[50];
    char phone[12]; // 18005557577
    char email[50];
    char title[20];

}Contact;

typedef struct node
{
    Contact data;
    struct node *pNext;

}Node;

// Description: Allocates space for a Node on the heap and initializes the Node with the information found in newData.
// Returns: The address of the start of the block of memory on the heap or NULL if no memory was allocated
Node * makeNode(Contact newData);

// Description: Uses makeNode () to allocate space for a new Node and inserts the new Node into the list in alphabetic order ('a' - 'z')
//              based on the name field
// Returns: TRUE if memory was  allocated for a Node; FALSE otherwise
Boolean insertContactInOrder(Node **pList, Contact newData);

// Description: Deletes a Contact in the list based on the name field; deletes the first occurence of the name
// Returns: TRUE if the Contact was found; FALSE otherwise
Boolean deleteContact(Node **pList, Contact searchContact);

// Description: Edits a Contact in the list based on the name field; edits the first occurence of the name
// Returns: TRUE if the Contact was found; FALSE otherwise
Boolean editContact(Node *pList, Contact searchContact);

// Description: Loads all Contact information from the given file, in alphabetic order, based on the name, into the list
// Returns: TRUE if all Contacts were loaded; FALSE otherwise
Boolean loadContacts(FILE *infile, Node **pList);

// Description: Stores all Contact information from the list into the given file
// Returns: TRUE if all Contacts were stored; FALSE otherwise
Boolean storeContacts(FILE *infile, Node *pList);

// Description: Prints all contact information in the list
// Returns: Nothing
void printList(Node *pList);

//test functions
void sum_test();

int main(int argc, char const *argv[])
{
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
    // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
    // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL
    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_pSuite pSuite = NULL;
    // Add a suite to the registry
    pSuite = CU_add_suite("sum_test_suite", 0, 0);
    // Always check if add was successful
    if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
    }
    // Add the test to the suite
    if (NULL == CU_add_test(pSuite, "sum_test", sum_test)) {
    CU_cleanup_registry();
    return CU_get_error();
    }

   // Run the tests and show the run summary
   CU_basic_run_tests();

   return CU_get_error();
}

Node * makeNode(Contact newData)
{
    //allocte new memory
    Node* new_node = (Node* )malloc(sizeof(Node));
    strcpy(new_node->data.name, newData.name);
    strcpy(new_node->data.phone, newData.phone);
    strcpy(new_node->data.email, newData.email);
    strcpy(new_node->data.title, newData.title);
    
    //set pointer
    new_node->pNext = NULL;

    return new_node;
}

Boolean insertContactInOrder(Node **pList, Contact newData)
{
    Boolean success = TRUE;
    Node *pCurrent = *pList;

    //allocate memory
    Node* new_node = makeNode(newData);
    if (new_node == NULL)
    {
        success = FALSE;
    }

    //find locations in memory
    while (strcmp(pCurrent->data.name, newData.name) < 0 && pCurrent->pNext != NULL)
    {
        //move on
        pCurrent += 1;
    }
    
    //connect new node
    new_node->pNext = pCurrent->pNext;
    pCurrent->pNext = new_node;
    
    return success;
}

Boolean deleteContact(Node **pList, Contact searchContact)
{
    Boolean success = TRUE;
    Node *pCurrent = *pList;
    Node *pNext = pCurrent;

    //find locations in memory
    while (strcmp(pCurrent->pNext->data.name, searchContact.name) != 0)
    {
        //move on
        pCurrent += 1;
        pNext = pCurrent->pNext;

        if (pCurrent->pNext == NULL)
        {
            success = FALSE;
            break;
        }
    }

    if (success == TRUE)
    {
        pCurrent->pNext = pNext->pNext;
        free(pNext);
        /* code */
    }
    
    return success;
}

Boolean editContact(Node *pList, Contact searchContact)
{
    Boolean success = TRUE;

    while (strcmp(pList->data.name, searchContact.name) != 0)
    {
        pList += 1;

        if (pList->pNext == NULL)
        {
            success = FALSE;
        }
        
    }
    
    if (success == TRUE)
    {
        strcpy(pList->data.name, searchContact.name);
        strcpy(pList->data.phone, searchContact.phone);
        strcpy(pList->data.email, searchContact.email);
        strcpy(pList->data.title, searchContact.title);
    }

    return success;
}

Boolean loadContacts(FILE *infile, Node **pList)
{
    Boolean success = FALSE;
    Node* pCurrent = *pList;
    char temp_string[50] = {'\0'};
    int count = 0;

    Contact newData[100];

    for (size_t i = 0; i < 100; i++)
    {
        //get name
        fgets(temp_string, 50, infile);
        strcpy(newData[i].name, temp_string);

        //get phone
        fgets(temp_string, 50, infile);
        strcpy(newData[i].phone, temp_string);

        //get email
        fgets(temp_string, 50, infile);
        strcpy(newData[i].email, temp_string);

        //get title
        fgets(temp_string, 50, infile);
        strcpy(newData[i].title, temp_string);

        count++;
        if (feof(infile)) break;       

    }
    
    //write to node
    for (size_t i = 0; i < count; i++)
    {
        insertContactInOrder(pList, newData[i]);
        success = TRUE;
    }

    return success;
}

Boolean storeContacts(FILE *infile, Node *pList)
{
    Boolean success = FALSE;
    while (pList != NULL)
    {
        //print data
        fputs(pList->data.name, infile);
        fputs(pList->data.phone, infile);
        fputs(pList->data.email, infile);
        fputs(pList->data.title, infile);

        pList += 1;
    }

    success = TRUE;
    return success;
}

void printList(Node *pList)
{
    while (pList != NULL)
    {
        //print data
        puts(pList->data.name);
        puts(pList->data.phone);
        puts(pList->data.email);
        puts(pList->data.title);

        pList += 1;
    }
}

void sum_test()
{
    //check each of functions

    //init test case data
    Contact newData;
    strcpy(newData.email, "abc@wsu.edu");
    strcpy(newData.name, "David Jones");
    strcpy(newData.phone, "18005557577");
    strcpy(newData.title, "Students");


    Node* newList = (Node* )malloc(sizeof(Node));

    //test makenode
    CU_ASSERT_NOT_EQUAL(makeNode(newData), 0);


    
    //test insertContactInOrder
    newList->pNext = makeNode(newData);

    Contact newData_add;
    strcpy(newData_add.email, "abc@wsu.edu");
    strcpy(newData_add.name, "Tom Green");
    strcpy(newData_add.phone, "18005557577");
    strcpy(newData_add.title, "Students");

    insertContactInOrder(&newList, newData_add);

    CU_ASSERT_EQUAL(newList->pNext->data.name, "Tom Green");



}
