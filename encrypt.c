#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

bool validate(char* myArg){//validates the key
    if(!myArg) return false;

    //check if it contains 26 char
    size_t length = strlen(myArg);
    if(length != 26) return false;

    bool visited[26] = {false};
    for(int i = 0; i < 26; i++){
        //check if theyre all letters
        if(!isalpha(myArg[i])) return false;
        //check if theres is any repeated character
        int index = tolower((unsigned char)myArg[i]) - 'a';
        if(visited[index]) return false;//check every one of them if the myarg char is in visited its false
        visited[index] = true;//if it comes out its not visited then visit
    }
    return true;
}
void convert(char* key, char* str){//convert the input to the key format
    if(!str) return;
    for(int i = 0; str[i] != '\0'; i++){
        int index;
        if((int)str[i] > 64 && (int)str[i] < 91){//if its uppercase
            index = str[i] - 'A';
            str[i] = (char)toupper((unsigned char)key[index]);//the uppercase version of the key char
        }else if((int)str[i] > 96 && (int)str[i] < 123){
            index = str[i] - 'a';
            str[i] = key[index];//the key is already in lowecase no need to change
        }
        else continue;
    }
}
void revert(char* key, char* str){//change back to the original format
    if(!str) return;
    for(int i = 0; str[i] != '\0'; i++){
        if((int)str[i] > 64 && (int)str[i] < 91){//its uppercase{
            for(int j = 0; j < 26; j++){
                if(toupper((unsigned char)key[j]) == str[i]){
                    str[i] = (char)toupper((unsigned char)(j + 'A'));
                    break;
                }
            }
        }
        else if((int)str[i] > 96 && (int)str[i] < 123){//its lowercase
            for(int j = 0; j < 26; j++){
                if(key[j] == str[i]){
                    str[i] = (char)(j + 'a');
                    break;
                }
            }
        }
    }
}
void prompt(char* arg){
    char filename[15];
    char secondf[15];
    char str[4096];
    int c;
    printf("Enter the name of the input file: ");
    scanf("%14s", filename);
    do{
        printf("Enter the name of the output file: ");
        while((c = getchar()) != '\n' && c != EOF);//clear the input buffer for strcmp to work properly
        scanf("%14s", secondf);
        if(strcmp(filename, secondf) == 0){
            printf("The input and output file can not be the same, please enter a different name for the output file\n");
        }
    }while(strcmp(filename, secondf) == 0);
    

    FILE* file = fopen(filename, "rb");
    FILE* ofile = fopen(secondf, "wb");
    if(!file){
        printf("An error occured while opening the input file try naming without spaces\n");
        return;
    }
    if(!ofile){
        printf("An error occured while opening the output file try naming without spaces\n");
        fclose(file);
        return;
    }
    char choice;
    do{
        printf("Are you encrypting or decrypting the file? (e/d): ");
        scanf(" %c", &choice);
    }while(choice != 'e' && choice != 'd');

    if(choice == 'e'){//encrypt
        while(fgets(str, sizeof(str), file)){
            convert(arg, str);
            fputs(str, ofile);
        }
    }else if (choice == 'd'){//decrypt
        while(fgets(str, sizeof(str), file)){
            revert(arg, str);
            fputs(str, ofile);
        }
    }
        fclose(file);
        fclose(ofile);
        printf("The output has been written to %s\n", secondf);
        char deleteChoice;
        do{//restrict the user to only input y or n
            printf("would you like to delete the input file? (y/n): ");
            scanf(" %c", &deleteChoice);
        }while(tolower((unsigned char)deleteChoice) != 'y' && tolower((unsigned char)deleteChoice) != 'n');
        if(tolower((unsigned char)deleteChoice) == 'y'){
            if(remove(filename) == 0){
                printf("The input file has been deleted successfully.\n");
            }else{
                printf("An error occured while trying to delete the input file.\n");
            }
        }else{
            printf("the input file has not been deleted.\n");
        }
}
int main(int argc, char* argv[]){
    if(argc != 2){
        printf("An error occured with the command-line arguments(you must provide one more argument with the filename)\n");
        return 1;
    }
    for(int i = 0; argv[1][i] != '\0'; i++){//convert everything in here to lowercase
        argv[1][i] = (char)tolower((unsigned char)argv[1][i]);//use unsigned char just to avoid undefined behavior
    }
    bool works = validate(argv[1]);
    if(!works){
        printf("An error occured with the second argument each character must be unique, an alphabet and contain all letters(26)\n");
        return 1;
    }
    prompt(argv[1]);

    return 0;
}
