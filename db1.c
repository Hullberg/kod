#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len - 1] == '\n')
    dest[len - 1] = '\0';
}

int printscr(char *argv){
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
  // Read the input file
  printf("Loading database \"%s\"...\n\n", argv);
  return 0;
}


// Query a key in the database
int querykey(Node argv){
  char buffer[128];
  Node list = argv;
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n\n", buffer);
  }
  return 0;
}

// Updating an entry in the database
int updateentry(Node argv){
  char buffer[128];
  Node list = argv;
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n\n", buffer);
  }else{
    printf("Enter new value: ");
    readline(buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    puts("Value inserted successfully!\n");
  }
  return 0;
}


// New entry to the database
int newentry(Node argv){
  char buffer[128];
  Node list = argv;
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database for duplicate keys...");
  int found = 0;
  Node cursor = argv;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      printf("key \"%s\" already exists!\n\n", cursor->key);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){ // Insert new node to the front of the list
    puts("Key is unique!\n");
    Node newNode = malloc(sizeof(struct node));
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    printf("Enter value: ");
    readline(buffer, 128, stdin);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n\n", list->key, list->value);
  }
  return 0;
}


  // Main loop
int mainloop(char *argv){
    FILE *database = fopen(argv, "r");
    char buffer[128];
    Node list = NULL;
    while(!(feof(database))){
      Node newNode = malloc(sizeof(struct node));
      readline(buffer, 128, database);
      newNode->key = malloc(strlen(buffer) + 1);
      strcpy(newNode->key, buffer);
      readline(buffer, 128, database);
      newNode->value = malloc(strlen(buffer) + 1);
      strcpy(newNode->value, buffer);
      newNode->next = list;
      list = newNode;
      }
  int choice = -1;
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database");
    puts("0. Exit database");
    printf("? ");
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    /*int found;
    Node cursor;*/
    switch(choice){
    case 1:
      querykey(list);
      break;
    case 2:
      updateentry(list);
      break;
    case 3:
      newentry(list);
      break;
      /*case 4:
      removeentry(list);
      break;
    case 5:
      printdb(list);
      break;*/
    case 0:
       // Exit
      puts("¡Adios señor!\n");
      break;
      default:
    puts("Could not parse choice! Please try again!\n");
      }
  }
  return 0;
}

int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db1 [FILE]");
    return -1;
    }
  char *filename = argv[1];
  printscr(filename);
  mainloop(filename);
  return 0;
}


