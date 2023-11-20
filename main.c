#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node* next;
} node;

//wie wieiter?


void printNode(node* currentNode)
{
    if (currentNode == NULL)
    {
        printf("NULL");
        return;
    }
    printf("%d -> ", currentNode->value);
}

void printList(node* head)
{
    node* currentNode = head;

    while(currentNode != NULL)
    {
        printNode(currentNode);
        currentNode = currentNode->next;
    }

    printf("NULL\n");
}

node* createNode(int value)
{
    node* newNode = malloc(sizeof(node));
    printf("Node allocated: %d\n", value);

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}


void addBackRef(node** head, node* newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    node* currentNode = *head;

    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
}

node* addBack(node* head, node* newNode)
{
    node* currentNode = head;

    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
    return head;
}

node* addFront(node* head, node* newNode)
{
    newNode->next = head;
    return newNode;
}

void addFrontRef(node** head, node* newNode)
{
    newNode->next = *head;
    *head = newNode;
}

void insertAtIndex(int index, int len, node* head, node* newNode)
{
    node* currentNode = head;
    node* prevNode = NULL;
    if (index < 0)
    {
        return;
    }

    if(index > len+1)
    {
        return;
    }
    for (int i = 0; i < index; i++)
    {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    prevNode->next = newNode;
    newNode->next = currentNode;
}

int listLength(node* head)
{
    node* currentNode = head;
    int len = 0;
    while (currentNode != NULL)
    {
        len++;
        currentNode = currentNode->next;
    }
    return len;
}

void freeNode(node* currentNode)
{
    int value = currentNode->value;
    free(currentNode);
    printf("Node freed: %d\n", value);
}

void freeList(node* head)
{
    node* currentNode = head;

    while(currentNode != NULL)
    {
        node* nextNode = currentNode->next;
        freeNode(currentNode);
        currentNode = nextNode;
    }
}

node* getNodeAt(int index, node* head)
{
    node* currentNode = head;
    int i = 0;
    while(currentNode != NULL)
    {
        if (i >= index)
        {
            break;
        }
        currentNode = currentNode->next;
        i++;
    }
    return currentNode;
}

node* addNodeAt(node* head, node* newNode, int index)
{
    if(head == NULL || index <= 0)
    {
        return addFront(head, newNode);
    }
    if(index >= listLength(head))
    {
        return addBack(head, newNode);
    }
    node* prevNode = getNodeAt(index-1, head);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    return head;
}

node* deleteFrontNode(node* head)
{
    if (head == NULL)
    {
        return head;
    }
    node* currentNode = head;
    head = currentNode->next;
    freeNode(currentNode);
    return head;
}

void deleteFrontNodeRef(node** head)
{
    if (*head == NULL)
    {
        return;
    }
    node* currentNode = *head;
    *head = currentNode->next;
    freeNode(currentNode);
}

node* deleteFrontNodeMultiple(node* head, int times)
{
    for (int i = 1; i <= times; i++)
    {
        head = deleteFrontNode(head);
    }
    return head;
}

void deleteFrontNodeMultipleRef(node** head, int times)
{
    for (int i = 1; i <= times; i++)
    {
        deleteFrontNodeRef(head);
    }
}



node* deleteBackNode(node* head)
{
    if (head == NULL)
    {
        return head;
    }
    node* currentNode = head;
    node* prevNode = NULL;
    while(currentNode->next != NULL)
    {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == head)
    {
        deleteFrontNodeRef(&head);
    }

    freeNode(currentNode);
    prevNode->next = NULL;
    return head;
}

void deleteBackNodeRef(node** head)
{
    if (*head == NULL)
    {
        return;
    }

    node* currentNode = *head;
    node* prevNode = NULL;

    while(currentNode->next != NULL)
    {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == *head)
    {
        freeNode(currentNode);
        *head = NULL;
        return;
    }


    freeNode(currentNode);
    prevNode->next = NULL;
}
node* deleteNodeAt(node* head, int index)
{
    if (head == NULL)
    {
        return head;
    }
    if (index <= 0)
    {
        return deleteFrontNode(head);
    }
    if (index >= listLength(head))
    {
        return deleteBackNode(head);
    }
    node* prevNode = getNodeAt(index-1, head);
    node* deletedNode = getNodeAt(index, head);
    prevNode->next = prevNode->next->next;
    freeNode(deletedNode);
    return head;
}

void deleteNodeAtRef(node** head, int index)
{

if (*head == NULL)
    {
        return;
    }
    if (index <= 0)
    {
        deleteFrontNodeRef(head);
        return;
    }
    if (index >= listLength(*head))
    {
        deleteBackNodeRef(head);
        return;
    }
    node* prevNode = getNodeAt(index-1, *head);
    node* deletedNode = getNodeAt(index, *head);
    prevNode->next = prevNode->next->next;
    freeNode(deletedNode);
}

node* deleteWholeList(node* head)
{
    node* currentNode = head;
    while(currentNode != NULL)
    {
        node* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;

    }
    return NULL;
}

void deleteWholeListRef(node** head)
{
    node* currentNode = *head;
    while(currentNode != NULL)
    {
        node* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    *head = NULL;
}

node* deleteEveryNth(node* head, int multiples)
{
    if (multiples == 1)
    {
        return deleteWholeList(head);
    }

    if (multiples <= 0)
    {
        printf("\nError: \"Multiples\" must be bigger than 0.\n");
        return head;
    }
    node* currentNode = head;
    node* prevNode = NULL;
    node* nextNode = currentNode->next;
    int counter = 0;
    while (currentNode != NULL)
    {
        counter++;
        if (counter >= multiples)
        {
            prevNode->next = nextNode;
            freeNode(currentNode);
            currentNode = nextNode;
            if (currentNode == NULL)
            {
                break;
            }
            nextNode = currentNode->next;
            counter = 0;
        }
        else
        {
            prevNode = currentNode;
            currentNode = nextNode;
            if (currentNode == NULL)
            {
                break;
            }
            nextNode = currentNode->next;
        }
    }
    return head;
}

void deleteEveryNthRef(node** head, int multiples)
{
    if (multiples == 1)
    {
        deleteWholeListRef(head);
        return;
    }

    if (multiples <= 0)
    {
        printf("\nError: \"Multiples\" must be bigger than 0.\n");
        return;
    }
    node* currentNode = *head;
    node* prevNode = NULL;
    node* nextNode = currentNode->next;
    int counter = 0;
    while (currentNode != NULL)
    {
        counter++;
        if (counter >= multiples)
        {
            prevNode->next = nextNode;
            freeNode(currentNode);
            currentNode = nextNode;
            if (currentNode == NULL)
            {
                break;
            }
            nextNode = currentNode->next;
            counter = 0;
        }
        else
        {
            prevNode = currentNode;
            currentNode = nextNode;
            if (currentNode == NULL)
            {
                break;
            }
            nextNode = currentNode->next;
        }
    }
    return;
}

node* addFrontMultiple(node* head, int value, int times)
{
    for (int i = 1; i <= times; i++)
    {
        head = addFront(head, createNode(value));
    }
    return head;
}


void addFrontMultipleRef(node** head, int value, int times)
{
    for (int i = 1; i <= times; i++)
    {
        addFrontRef(head, createNode(value));
    }
}

node* addBackMultiple (node* head, int value, int  times)
{
    for (int i = 1; i <= times; i++)
    {
        head = addBack(head, createNode(value));
    }
    return head;
}

void addBackMultipleRef (node** head, int value, int times)
{
    for (int i = 1; i<=times; i++)
    {
        addBackRef(head, createNode(value));
    }
}

node* findByValue (node* head, int value)
{
    node* currentNode = head;
    while (currentNode != NULL)
    {
        if (currentNode->value == value)
            {
                return currentNode;
            }
        currentNode = currentNode->next;
    }
    printf("\nNo node with such value found.\n");
    return NULL;
}

//adds a value at the current Node
void addAt(node* currentNode, node* newNode)
{
    if (currentNode == NULL)
    {
        printf("\nSelected Node is NULL.\n");
        return;
    }
    if (newNode == NULL)
    {
        printf("\nNew Node is NULL.\n");
        return;
    }
    node* nextNode = currentNode->next;
    currentNode->next = newNode;
    newNode->next = nextNode;
}

node* getPrevNode (node* thisNode, node* head)
{
    if (thisNode == head)
    {
        printf("\nThere is no previous node because this is the head.\n");
        return NULL;
    }
    node* currentNode = head;
    while (currentNode != NULL)
    {
        if (currentNode->next == thisNode)
        {
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    printf("\nThe node is not in the list\n");
    return NULL;
}

node* replaceNode(node* currentNode, node* newNode, node* head)
{
    if (currentNode == NULL)
    {
        printf("\nSelected Node is NULL.\n");
        return head;
    }
    if (newNode == NULL)
    {
        printf("\nNew Node is NULL.\n");
        return head;
    }

    if (currentNode == head)
    {
        newNode->next = currentNode->next;
        freeNode(currentNode);
        return newNode;
    }

    node* prevNode = getPrevNode(currentNode, head);
    prevNode->next = newNode;
    newNode->next = currentNode->next;
    freeNode(currentNode);

    return head;
}



node* findAndReplaceNode (node* head, int value, node* newNode)
{
    node* currentNode = findByValue(head, value);
    if (currentNode == NULL)
    {
        printf("\nEnd Function because no such node could be found.\n");
        return head;
    }
    head = replaceNode(currentNode, newNode, head);
    return head;
}

node* switchWithNextNode (node* head, node* firstNode, node* prevNode)
{
    if (firstNode == NULL || firstNode->next == NULL)
    {
        return head;
    }


    node* secondNode = firstNode->next;
    if (firstNode == head)
    {
        head = secondNode;
    }
    else
    {
        prevNode->next = secondNode;
    }
    firstNode->next = secondNode->next;
    secondNode->next = firstNode;
    return head;
}

//not finished
node* sortByValue (node* head)
{
    node* currentNode = head;
    node* prevNode = NULL;
    while (currentNode != NULL && currentNode->next != NULL)
    {
        if (currentNode > currentNode->next)
        {
            head = switchWithNextNode(head, currentNode, prevNode);
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    return head;
}

node* reverseList (node* head)
{
    node* currentNode = head->next;
    head->next = NULL;  //head becomes tail, so next Node is NULL
    node* prevNode = head;  //prevNode initialized with first value, which is hea
    node* nextNode = currentNode->next;
    while (currentNode->next != NULL)
    {
        currentNode->next =  prevNode; //attach to previous node, from behind

        prevNode = currentNode;
        currentNode = nextNode;
        nextNode = currentNode->next;

    }

    currentNode->next = prevNode;
    head = currentNode;
    return head;
}

//delete by value
//sort by value



int main()
{
    node* head = NULL;
    /*
    head = createNode(123);
    addBackRef(&head, createNode(234));
    addBackRef(&head, createNode(234));
    addBackRef(&head, createNode(345));
    addBackRef(&head, createNode(456));
    addBackRef(&head, createNode(567));
    */


    addBackRef(&head, createNode(123));
    addBackRef(&head, createNode(234));
    addBackRef(&head, createNode(345));
    addBackRef(&head, createNode(456));
    addBackRef(&head, createNode(567));
    addBackRef(&head, createNode(678));
    addBackRef(&head, createNode(789));
    addBackRef(&head, createNode(890));
    addBackRef(&head, createNode(901));




    printList(head);

    head = reverseList(head);

    printList(head);

    head = sortByValue(head);

    printList(head);

    freeList(head);
    return 0;
}
