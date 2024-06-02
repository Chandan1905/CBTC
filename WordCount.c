#include <stdio.h>
#include <ctype.h>
#include<string.h>
// Function prototypes

int main() {
    FILE *file;
    char filename[100];
    int lines = 0, words = 0, characters = 0;
    int in_word = 0;  // Boolean to check if we're inside a word

    // Prompt user to enter the file name
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    char data[2000];
    fgets(data,sizeof(data),file);

    printf("%s",data);
    characters = strlen(data)-1;
    for(int i=0;i<strlen(data);i++){
        if(data[i]==' ' || data[i]=='/' || data[i]=='*' || data[i]=='-' || data[i]=='+' || data[i]=='\n'){
            words++;
        }
        if((data[i]=='.'&&data[i+1]==' ') || data[i]=='\n'){
            lines++;
        }
    }

    // Close the file
    fclose(file);

    // Display the counts
    printf("\nLines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);

    return 0;
}

