#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int get_length(char str[], char delim){
   char *start;
   int i = 0;
   start = &str[0];
   while(*(start+i)!= '\0'){ //*(start+i) moves pointer
     i = i + 1;
}
   //printf("\nLength of string: %d",(i - 1));
   return (i - 1);//i is used as increment for index -1 gives array length
}

int token_count(char str[], char delim){
   char *start;
   int i = 0;
   int count = 0;
   start = &str[0];

   while(*(start+i)!= '\0'){
     if(*(start+i) == delim){
       count = count + 1;
     }
     i = i + 1; 
   }
   //printf("\nNumber of tokens: %d\n", (count + 1)); 
   return (count + 1); 
}
 
char *get_token_end(char str[], char* start, char delim){
   //printf("start: %c\n", *(start));
   char *end = start;
   int i =0;
   while(*(start+i)!='\0'){
     if(*(start+i) == delim){
    // printf("end: %c\n", *(end-1));
     return (end-1);
     }
     end = end + 1;
     i = i + 1;
   }
   //printf("end: %c\n", *(end-2));
   return (end-2);
}
char *copy_substring(char str[],char* start, char* end,int tokensize){
  char *substring = malloc(sizeof(char) * tokensize);
  int i = 0;
  while(start != end + 1){
    //printf("%c",*start);
    substring[i] = *start;
    i = i + 1;
    start = start + 1;
  }
  substring[i + 1] = *end;
  return substring;
}

void print_tokenizer(char str[],char** arr, int tokens,char *start,char delim){
  int i = 0;
  int j = 0;
  char *end;
  char token_length;
  for(i=0;i<tokens;i++){
    end = get_token_end(str,start,delim);
    token_length = end - start + 1;
    start = end + 2;
    printf("token[%d]: ",i);
    for(j=0;j<token_length;j++){
      printf("%c",arr[i][j]);

    } 
    printf("\n");
  }
}

char** tokenizer(char str[],int tokens,char delim){
  char** arr =malloc(sizeof(char*) * tokens);
  char *start = &str[0];
  char *end;
  int i;
  for(i=0;i<tokens;i++){
    end = get_token_end(str,start,delim);
    arr[i] = copy_substring(str, start, end,end - start + 1);
    start = end + 2;
  }
  return arr;
}



//int main(){
  // char user_string[40] = {'\0'};
  // printf("Enter a String $");
  // fgets(user_string,40,stdin);
   //char user_delim;
  // printf("Enter a delimiter$");
  // scanf("%c",&user_delim);
  // char *start = &user_string[0];
  // int string_length = get_length(user_string,user_delim);
  // int tokens = token_count(user_string,user_delim);
  // char** token_double = tokenizer(user_string,tokens,user_delim);
   //print_tokenizer(user_string,token_double,tokens,start,user_delim); 
  // return 0;
//} 

