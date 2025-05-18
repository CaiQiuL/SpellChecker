#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
static int exit_status = 1;

typedef struct node {
    int data; //Represents if the string is a word//1 = true and 0 = false
    struct node* children[128];
} node;
node* root = NULL;


node* create_node() {
    node *q = (node*) malloc(sizeof(node));
    for (int i =0; i <128; i++)
    {
        q->children[i] = NULL;
    }
    q->data =0;
    return q;
}

void insert_node(char word[]) {
    int length = strlen(word);
    int arrayindex;
    if (root == NULL)
    {
        root = create_node();
    }
    struct node *q = root; 
    for (int i = 0; i < length; i++) 
    {
        arrayindex = word[i];
        if (q->children[arrayindex] ==NULL) 
        {
            q->children[arrayindex] = create_node();
        }
        q = q->children[arrayindex];
    }
    q->data = 1;
}

int search(char word[]) {
    struct node *q = root;
    int length = strlen(word);
    int index = 0;
    int i =0;
    for (i =0; i < length; i++) {
          index = word[i];

        if (q->children[index] != NULL)
            q = q->children[index];
        else
            break;
    }
    if (word[i] == '\0' && q->data != 0)
        return q->data; //1 is True
    return 0; //False
}

int hyphenSearch(char words[]) {
    char * thisword = strdup(words);
    int originallength = strlen(thisword);
    if (strlen(words)==1)
    {
        words[0] ='\0';
        return 1;
    }
    //printf("%ld %s\n", strlen(words), words);
    for (int i=0; i<originallength; i++)
    {
        if (thisword[i] == '-')
        {
            thisword[i] = '\0';
        }
    }
    int length = 0;
    //printf("%ld\n", strlen(words+1));
    while (length < originallength)
    {
        char * altword = strdup(thisword+length);
        altword[0] = tolower(altword[0]);
        //printf("%s\n", words+length);
        if (search(thisword+length)==0 && search(altword)==0)
        {
            return 0;
        }
        length = 1+length + strlen(thisword+length);
    
    }
        return 1;
    

}

void dictionaryCreation(FILE* dict)
{
  int bufferLength =255;
    char buffer[bufferLength];
    while(fgets(buffer, bufferLength, dict))
    {
        char* word = strtok(buffer, "\n");
        insert_node(word);
        for (int i=0; i<strlen(word); i++)
        {
            word[i] = toupper(word[i]);
        }
        insert_node(word);
    }
return;
}


void fileReader (char fileName[])
{
    char str[4096];
    int row =1;
    //int column = 1;
    FILE* file = fopen(fileName, "r");
    if (file==NULL)
    {
        printf("Could not read the file \"%s\"\n", fileName);
        exit(EXIT_FAILURE);
    }
    while ((fgets(str, 4096, file)) != NULL) {
        char * word = strtok(str, " ,.?{}()[]\"!:;=#\n0123456789");
        while (word != NULL)
            {  
            /*char * altword = strdup(word);
            altword[0] = tolower(altword[0]);
            if (search(word)==0 && search(altword)==0 && strchr(word, '-')==NULL && word[0] != '\'')
            {
                printf("%s (%d,%ld): %s\n", fileName, row, word-str+1, word);
                exit_status = 0;
                
            }*/
            /*if (strchr(word, '-')!=NULL)
            {
                char* hyphen = strchr(word, '-');
                int hyphenIndex = hyphen-word;
                char wordone[40]; 
                char wordtwo[40];
                strcpy(wordtwo, word+(hyphen-word+1));
                strcpy(wordone, word);
                wordone[hyphenIndex] = '\0';
                char * altwordone = strdup(wordone);
                altwordone[0] = tolower(altwordone[0]);
                char * altwordtwo = strdup(wordtwo);
                altwordtwo[0] = tolower(altwordtwo[0]);
                if ((search(wordone)==0 && search(altwordone)==0) || (search(wordtwo)==0 && search(altwordtwo)==0))
                {
                printf("%s (%d,%ld): %s\n", fileName, row, word-str+1, word);
                exit_status = 0;
                }
            }*/
            /*if (strchr(word, '-')!=NULL)
            {
                if (hyphenSearch(word)==0)
                {
                    printf("%s (%d,%ld): %s\n", fileName, row, word-str+1, word);
                }
            }*/
            if (word[0] == '\'')
                {
                    char altword[40];
                    strcpy(altword, word+1);
                    while (altword[0] == '\'')
                    {
                    strcpy(altword, altword+1);
                    }
                    if (strlen(altword)>=1)
                    {
                        word = altword;
                    }
                }
            if (word[strlen(word)-1]=='\'')
            {
                char altword[40];
                altword[strlen(word)-1]='\0';
                if (strlen(altword)>=1)
                {
                    word = altword;
                }
            }
            char * altword = strdup(word);
            altword[0] = tolower(altword[0]);
            if (search(word)==0 && search(altword)==0 && strchr(word, '-')==NULL && word[0] != '\'')
            {
                printf("%s (%d,%ld): %s\n", fileName, row, word-str+1, word);
                exit_status = 0;
                
            }
            if (strchr(word, '-') !=NULL)
            {
                if (hyphenSearch(word)==0)
                {
                    printf("%s (%d,%ld): %s\n", fileName, row, word-str+1, word);
                    exit_status = 0;
                }
            }

            word = strtok (NULL, " ,.?{}()[]\"!:;=#\n0123456789");
            }
        
       row++;
       //column =1;
    }
}

void DirectoryTraversal(char dirName[]){
  struct dirent *direct;
  DIR* dir = opendir(dirName);
  if (dir ==NULL) {
    return;
  }
  while ((direct = readdir(dir))!=NULL)
  {
    char path[1024];
     if (strcmp(direct->d_name, ".") == 0 || strcmp(direct->d_name, "..") == 0)
    {
    continue;
    }

    snprintf(path, sizeof(path), "%s/%s", dirName, direct->d_name);

    struct stat path_stat;
    stat(path, &path_stat);
    if (S_ISDIR(path_stat.st_mode))
    {
        if (direct->d_name[0] != '.') {
                DirectoryTraversal(path);
            }
    }
    else
    {
        if(!strcmp(path + strlen(path) - 4, ".txt") && (direct->d_name[0] != '.'))
        {
            //printf("%s\n", path);
            fileReader(path);
        }
    }

  }
  closedir(dir);

}
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}




int main(int argc, char **argv)
{
    if (argc ==1)
    {
        printf("Error! Did not input a dictionary file and files or directories!\n");
        exit(EXIT_FAILURE);
    }
FILE* dictionary = fopen(argv[1], "r");
if (dictionary == NULL)
{
    printf("Could not read the dictionary file \"%s\"\n", argv[1]);
    exit(EXIT_FAILURE);
}

dictionaryCreation(dictionary);

for (int i=2; i<argc; i++)
{
if (isDirectory(argv[i]))
{
    DirectoryTraversal(argv[i]);
}
else 
{
    fileReader(argv[i]);
}
}

if (exit_status)
{
    exit(EXIT_SUCCESS);
}
if (!exit_status)
{
    exit(EXIT_FAILURE);
}

}