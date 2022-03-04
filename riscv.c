#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
int to_decimal(int32_t hex){
return 0;

}
int compare_str(char** str){
  char add[3] = {'A','D','D'};
  char addi[4] = {'A','D','D','i'};
  char load[2] = {'L','W'};
  char store[2] = {'S','W'};
  //printf("%s\n", str[0]);
  
  if((str[0][0] == addi[0]) && (str[0][1] == addi[1]) && (str[0][2] == addi[2]) && (str[0][3] == addi[3])){//ADDi
      return 0;
       }
  if((str[0][0] == add[0]) && (str[0][1] == add[1]) && (str[0][2] == add[2])){//ADD
      return 1;

       }
  if((str[0][0] == store[0]) && (str[0][1] == store[1])){//SW: if length 2 and first char is 'S'
      return 4;
         }
  if((str[0][0] == load[0]) && (str[0][1] == load[1])){//LW: if length 2 and first char $
      return 5;
         }

  return 3;
}

int atoi_custom_adds(char *substr){
       int integer = 0;
       int sign = 1;
       int i = 1;//i=1 to skip over 'X'
       if(substr[0] == '-'){//catch sign
         sign = -1;
       }
       if(substr[0] != 'X' && substr[0] != '-'){//If ADDi is being performed
         i = 0;
       }
       for(;substr[i]!='\0';i++){
         integer = integer * 10 + substr[i] - '0';
       } 
      //printf("%d\n",integer * sign);
       return integer * sign;
}
bool interpret(char* instr){
       char user_delim = ',';
       char* start = &instr[0];
       int tokens = token_count(instr,user_delim);
       char** token_str = tokenizer(instr,tokens,user_delim);
      // print_tokenizer(instr,token_str,tokens,start,user_delim);
      // int oper_length = get_length(token_str[0],user_delim) + 1;
       //printf("Operation Length: %d\n",oper_length);
       int result = compare_str(token_str);
       if(result == 0){//ADDI
         printf("ADDi Performed\n");
         //Store = Reg1 + Immediate
         reg[atoi_custom_adds(token_str[1])] = reg[atoi_custom_adds(token_str[2])] + atoi_custom_adds(token_str[3]);
         //printf("Results = %d\n",reg[atoi_custom_adds(token_str[1])]);
         printf("Results in reg[%d]\n",atoi_custom_adds(token_str[1]));
       }

       if(result == 1){//ADD
         printf("ADD Performed: ");
         //Store = Reg1 + Reg2
         reg[atoi_custom_adds(token_str[1])] = reg[atoi_custom_adds(token_str[2])] + reg[atoi_custom_adds(token_str[3])];
         //printf("Results = %d\n", reg[atoi_custom_adds(token_str[1])]);//Output Results Stored in "X" Register
         printf("Results in reg[%d]\n",atoi_custom_adds(token_str[1]));
       }

       if(result == 4){//STORE
         printf("Store Performed\n");
         int reg_source = reg[atoi_custom_adds(token_str[1])];//Extract X(INT) to find index
         printf("destination reg: %d\n",reg_source);
         int32_t data_to_write; // equal to 4095
         int32_t address; // equal to 152
         char* mem_file = "mem.txt";
         int offset = 0;
         int mem_reg;
         char mem_delim;
         char* mem_address;
         char** mem_str;
         int mem_tokens;      
        //tokenize the memory address and offset
         mem_delim = '(';
         mem_address = &token_str[2][0];//token containing memory address
         mem_tokens = token_count(token_str[2],mem_delim);
         mem_str = tokenizer(token_str[2],mem_tokens,mem_delim);
         offset = atoi_custom_adds(mem_str[0]);//atoi offset
         mem_reg = reg[atoi_custom_adds(mem_str[1])];
         int final_address = offset + mem_reg;
        //memory address should be even 


         if((final_address % 2) != 0){
           final_address = final_address + 1;
         }
        
         data_to_write = reg_source;
         address = final_address;
         write_address(data_to_write,address,mem_file); 
         printf("memory address = %d\n",final_address); 
       }

       if(result == 5){//LOAD
         printf("Load Performed\n");
         int reg_source = atoi_custom_adds(token_str[1]);//Index of dest reg address
         printf("load from memory into reg[%d]\n",reg_source);
         int32_t write_to; // equal to 4095
         int32_t address; // equal to 152
         char* mem_file = "mem.txt";
         int offset = 0;
         int mem_reg;
         char mem_delim;
         char* mem_address;
         char** mem_str;
         int mem_tokens;      
        //tokenize the memory address and offset
         mem_delim = '(';
         mem_address = &token_str[2][0];//token containing memory address
         mem_tokens = token_count(token_str[2],mem_delim);
         mem_str = tokenizer(token_str[2],mem_tokens,mem_delim);
         offset = atoi_custom_adds(mem_str[0]);//atoi offset
         
         mem_reg = reg[atoi_custom_adds(mem_str[1])];
         int final_address = offset + mem_reg;
         //memory address should be even 
         if((final_address % 2) != 0){
           final_address = final_address + 1;
         }
         write_to = reg_source;
         address = final_address;
         int32_t read = read_address(address,mem_file);
         reg[reg_source] = read; 
         printf("from memory address = 0x%lX\n",read);
       }

       if(result == 3){
        printf("INVALID RV32 instruction\n");
        return false;
       }  
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 2; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf(" X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE
      
	print_regs();
        printf("\nEnter RV32 Instructions(Comma-Delimited)$");
        char* instruction = malloc(1000 * sizeof(char));
        bool is_null = false;
        is_null = fgets(instruction,1000,stdin) == NULL;
        while(!is_null){
          interpret(instruction);
          printf("\nUPDATED REGISTERS:\n ");
          print_regs();
          printf("\nEnter RV32 Instructions(Comma-Delimited)$");

          is_null = fgets(instruction,1000,stdin) == NULL;
        }
        printf("GOOD BYE!\n");
	return 0;

}
