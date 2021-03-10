#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define Size 50
typedef struct node1 {
	int key, index;
	char first_name[100];
	struct friend1 *friend1;
	struct node1 *next;
}node1;

typedef struct friend1 {
	char friend_name[20];
	struct friend1 *next;
	struct friend1 *pre;
}friend1;

typedef struct {
	struct node1 *head;
	int count;
}hash1;



node1 *createnode1(int key, char * value, int hashIndex) {
	node1 *new_node1;
	new_node1 = (node1 *)malloc(sizeof(node1));
	//new_node1->first_name = value;
	strcpy(new_node1->first_name, value);
	new_node1->index = hashIndex;
	new_node1->key = key;
	new_node1->next = NULL;
	new_node1->friend1 = NULL;
	return new_node1;
}


friend1 *createfriend(char * name) {
	friend1 *new_friend;
	new_friend = (friend1 *)malloc(sizeof(friend1));
	strcpy(new_friend->friend_name, name);
	new_friend->next = NULL;
	new_friend->pre = NULL;
	return new_friend;
}

bool deletFriend(node1* inputNode,char* inputName)
{
	friend1* friendPointer=inputNode->friend1;
	int count=0;

	while(friendPointer)
	{
		if(!strcmp(friendPointer->friend_name,inputName))
		{
			friend1* temp=friendPointer->next;
			if(count==0)
			{			
				inputNode->friend1=temp;
				if(temp)
					temp->pre=inputNode->friend1;
				free(friendPointer);
			}
			else
			{
				friendPointer->pre->next=temp;
				if(temp)
					temp->pre=friendPointer->pre;
				free(friendPointer);
			}
			return true;		
		}
		count++;
		friendPointer=friendPointer->next;
	}
	return false;
	
}

int GetKey(char *value) {
	int key = 0;
	int i;
	for (i = 0; i < (int)strlen(value); i++)
	{
		key = key + value[i];
	}
	return key;
}



node1* find_table(hash1 * hashTable1, char * target_name, int size) {
	int key = GetKey(target_name);
	int hashIndex = key % size, flag = 0;
	node1 *node1 = hashTable1[hashIndex].head;

	if (!node1)
		return NULL;
	while (node1 != NULL) {
		if (strcmp(node1->first_name, target_name) == 0) {
			flag = 1;
			break;
		}
		node1 = node1->next;
	}

	if (!flag) {
		return NULL;
	}
	else
		return node1;
}

bool GetInputString(char* keyword, char* name1, char* name2)
{
	int k = 0;
	int i = 0;
	int j = 0;
	int space = 0;
	for (i = 0; i < 100; i++)
	{
		char ch = getchar();
		if (i == 0)
			*keyword = ch;
		if (ch == '\n') {
			break;
		}
		else if (ch == ' ')
			space++;
		else
		{
			if (space == 1)
				name1[j++] = ch;
			else if (space == 2)
				name2[k++] = ch;
		}
	}
	switch (*keyword)
	{
	case 'P':
	case 'L':
		if (strlen(name1) == 0)
			return false;
		break;
	case 'F':
	case 'U':
	case 'Q':
		if (strlen(name2) == 0)
			return false;
		break;
	}
	return true;
}

void menu()
{
	printf("P <name> - Create a person record of the specified first name. \n");
	printf("F <name1> <name2> - Record that the two specified people are friends. \n");
	printf("U <name1> <name2> - Record that the two specified people are no longer friends. \n");
	printf("L <name> - Print out the friends of the specified person. \n");
	printf("Q <name1> <name2> - Check whether the two people are friends.  \n");
	printf("X - terminate the program.  \n");
}

int main(int argc, char *argv[]) {

	hash1 *hashtable = (hash1 *) malloc(Size * sizeof(hash1));
	memset(hashtable, 0, Size * sizeof(hash1));
	while (1)
	{
		menu();
		char inputName1[100] = { 0 };
		char inputName2[100] = { 0 };
		char keyWord = 0;

		if (!GetInputString(&keyWord, inputName1, inputName2))
			continue;
		switch (keyWord)
		{
		case 'P':
		{

			node1 *new_node1 = createnode1(GetKey(inputName1), inputName1, GetKey(inputName1) % Size);

			int indexOftheHash = GetKey(inputName1) % Size;
			
			if (hashtable[indexOftheHash].head == NULL)
			{
				hashtable[indexOftheHash].count++;
				hashtable[indexOftheHash].head = new_node1;
				break;
			}
			else
			{
				new_node1->next = hashtable[indexOftheHash].head;
				hashtable[indexOftheHash].head = new_node1;
				hashtable[indexOftheHash].count++;
				break;
			}

		}

		case 'F':
		{

			node1 * node1Name1, *node1Name2;
			
			node1Name1 = find_table(hashtable, inputName1, Size);
			node1Name2 = find_table(hashtable, inputName2, Size);
			if (node1Name1 == NULL)
			{
				printf("sorry, we didn't find %s\n", inputName1);
				break;
			}
			else if (node1Name2 == NULL)
			{
				printf("sorry, we didn't find %s\n", inputName2);
				break;
			}
			else
			{
				friend1 *newFriend = createfriend(inputName2);
				if (node1Name1->friend1 == NULL)
				{
					node1Name1->friend1 = newFriend;
				}
				else
				{
					newFriend->next = node1Name1->friend1;
					node1Name1->friend1->pre = newFriend;
					node1Name1->friend1 = newFriend;
				}
				friend1 *newFriend2 = createfriend(inputName1);

				if (node1Name2->friend1 == NULL)
				{
					node1Name2->friend1 = newFriend2;
				}
				else
				{
					newFriend2->next = node1Name2->friend1;
					node1Name2->friend1->pre = newFriend2;
					node1Name2->friend1 = newFriend2;
				}

			}
			break;
		}
		case 'L':
		{
			node1* node1Name = NULL;
			int indexOftheHash = 0;
			friend1* pFriends = NULL;
			node1Name = find_table(hashtable, inputName1, Size);
			pFriends = node1Name->friend1;
			while (pFriends)
			{
				printf("  %s",pFriends->friend_name);
				pFriends = pFriends->next;
			}
			printf("\n", pFriends->friend_name);
			break;
		}
		case 'Q':
			{
			
			node1* node1Name = NULL;
			int indexOftheHash = 0;
			friend1* pFriends = NULL;
			node1Name = find_table(hashtable, inputName1, Size);
			pFriends = node1Name->friend1;
			bool end=false;
			while (pFriends)
			{
		 		if(!strcmp(inputName2,pFriends->friend_name))
				{
			   		printf(" %s  %s Yes\n",inputName1,inputName2);
			   		end=true;
			   		break;
				}
				
				pFriends = pFriends->next;
			}
			if(!end)
			printf("No\n");
			break;
			}
		case 'U':
			{
			node1 * node1Name1, *node1Name2;
			
			node1Name1 = find_table(hashtable, inputName1, Size);
			node1Name2 = find_table(hashtable, inputName2, Size);
			if (node1Name1 == NULL)
			{
				printf("sorry, we didn't find %s\n", inputName1);
				break;
			}
			else if (node1Name2 == NULL)
			{
				printf("sorry, we didn't find %s\n", inputName2);
				break;
			}
			else
			{
				if(!deletFriend(node1Name1,inputName2))
				{
					printf("  %s and %s are not friends\n",inputName1,inputName2 );
				}
				deletFriend(node1Name2,inputName1);
				
			}
			break;
			}
		case 'X':
		{
			for (int i = 0; i < Size; i++)
			{
				hash1 temp = hashtable[i];
				if (temp.head)
				{
					node1* tmpnode1 = temp.head;
					while (tmpnode1)
					{
						friend1* tmpfrind = tmpnode1->friend1;
							while (tmpfrind)
							{
								friend1* a = tmpfrind;
								tmpfrind = tmpfrind->next;
								free(a);
							}
						node1* b = tmpnode1;
						tmpnode1 = temp.head->next;
						free(b);
					}
					// free head;
				}
			}

			free(hashtable);
			return 0;
			break;
		}

		}
	}


	return 0;
}

