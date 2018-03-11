#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "inttypes.h"
#include "unistd.h"

extern int convert_option = 3;

int typezero_input(int pos, char* binary_buffer, FILE* pointer);
void convert_to_typeOne(FILE* pointer,  uint8_t amount, uint16_t numbers[]);
int typefirst_input(int pos, char* binary_buffer, FILE *pointer);
void convert_to_typeZero(FILE* pointer, short amount, short numbers[]);




int main(){
	int length_of_file;
   
	FILE *ptr;
    FILE *ptr1;
	
	ptr = fopen("practice_project_test_file_1","rb");
    ptr1 = fopen("practice_project_write_file_2","wb+");
    fseek(ptr1, 0, SEEK_SET);
	fseek(ptr, 0, SEEK_END);
	length_of_file = ftell(ptr);
	printf("The length of file is %d\n",length_of_file);
	rewind(ptr);
	char buffer[length_of_file];
	int num_of_bytes = fread(buffer, length_of_file, 1, ptr);
	int j = 0;
    int i = 0;
    while(i < length_of_file){
//        printf("The value in buffer is %d\n",buffer[i]);
//        printf("The value in buffer is %u\n",buffer[i]);
        if(buffer[i] == 0){
            //printf("Buffer i is %02x and index is %u\n",buffer[i], i);
            //printf("The index here in type 1 is %d\n", i);
            i = typezero_input(i, buffer,ptr1);
            //printf("The index returned here in type 1 is %d\n",i);

        }
        else if(buffer[i] == 1){
            //printf("The index here in type 2 is %d\n",i);
            i = typefirst_input(i,buffer, ptr1);
            //printf("The index returned here in type 2 is %d\n",i);
        }

        
    }
    
    printf("Succesfully converted and written into the file\n");
    //j = typezero_input(31,buffer, ptr1);
    
}


int typezero_input(int pos, char* binary_buffer, FILE* pointer){
    
    FILE* ptr = pointer;
    printf("The index before entering type 0 is %d\n", pos);
    int size_of_unit = 2;
    uint8_t amount = binary_buffer[pos+1];
    uint16_t first_input[amount];
    printf("The number of amount is %d\n",binary_buffer[pos+1]);
    int count = pos+2;
    
    int i = 0;
    
    while(i < amount){
        first_input[i] = binary_buffer[count]<<8 | binary_buffer[count+1] ;
        //printf("%d   ...\n", first_input[i]);
        count = count + 2;
        i = i + 1;
        
    }
    
    //change the format based on convert options
    
    if(convert_option == 1 || convert_option == 3){  //conversion from the command line argument
        convert_to_typeOne(ptr, amount, first_input);
    }
    else{                   //No conversion
        uint8_t type = 0;
        printf("%d   type\n",type);
        printf("%d    amount\n",amount);
        fwrite(&type, sizeof(uint8_t),1,pointer);
        fwrite(&amount, sizeof(uint8_t),1,pointer);
        for(int i =0; i<amount; i++){
            fwrite(&first_input[i], sizeof(short),1, pointer);
        }
    }
    printf("The index before returning from type 0 is %d\n", count);
    return count;
}

void convert_to_typeOne(FILE* pointer,  uint8_t amount, uint16_t numbers[]){
    uint8_t type = 1;
    uint8_t comma = 44;
    printf("I am inside the conversion function\n");
    fwrite(&type, sizeof(uint8_t), 1, pointer);
    printf("I was just about to convert it\n");
    char amount_array[4];
    amount_array[0] = 48;
    amount_array[1] = 48;
    amount_array[2] = amount;
    amount_array[3] = '\0' ; //null character
    fprintf(pointer, "%s", amount_array);
    int i = 0;
    while(i<amount){
        printf("Trying to write files\n");
        fprintf(pointer,"%d",numbers[i]);
        printf("Not sure if it was succesful\n");
        if(i<=amount-2){   //if condition to insert comma
            fwrite(&comma, sizeof(uint8_t),1,pointer);
            
        }
        i++;
        
    }
    
    printf("I think I converted it\n");
}



int typefirst_input(int pos, char* binary_buffer, FILE *pointer){
    printf("The index before entering type 1 is %d\n", pos);
    FILE* ptr = pointer;
    int i = pos;
    uint8_t amount = (binary_buffer[i+1]-48)*100 + (binary_buffer[i+2]-48)*10 + binary_buffer[i+3]-48;
    char amount_[4];                         //printing three bytes of amount
    printf("%d.....\n",binary_buffer[pos+1]);
    printf("%d.....\n",binary_buffer[pos+2]);
    printf("%d.....\n",binary_buffer[pos+3]);
    amount_[0] = binary_buffer[pos+1];
    amount_[1] = binary_buffer[pos+2];
    amount_[2] = binary_buffer[pos+3];
    amount_[3] = '\0';
    printf("The amount in type 1 is %d\n",amount);
    short second_input[amount];    //this is where we store asccii values so that they can be written later on on file
    
    i = i + 4;
    int count = 1;
    //for counting the numbers of unit of the type 1 and we assume that there is at least one such unit until we find either 0 or a comma.
    int j  = 0; //working around with concatenating the bytes of ascii values
    int value = 0;      //this is the variable where we temporarily store the asccii value
    int num_of_units = 0;
    int comma = 44;
    int type0 = 0;
    int type1 = 1;     //assigning value to type 1
    int ind = 0;      //this for storing values of numbers in character array
    
    while(num_of_units<amount){
        if(binary_buffer[i] == comma){
            num_of_units = num_of_units + 1;
            printf("The ascii value is %d\n",value);
            second_input[ind] = value;
            ind = ind + 1;
            i = i+1;
            j=0;
        }
        else if(binary_buffer[i] == type0 | binary_buffer[i] == type1){
            second_input[ind] = value;
            printf("The ascii value is %d\n",value);
            
            printf("The index before returning to main from type 1 is %d\n", i);
            if(convert_option == 3 || convert_option == 2){
//                convert_to_typeZero(ptr, amount, second_input);
                printf("Converting \n");
                uint8_t type = 0;
                fwrite(&type, sizeof(uint8_t), 1, pointer);
                fwrite(&amount, sizeof(uint8_t),1, pointer);
                for(int i =0; i<amount; i++){
                    printf("%d............type1\n",second_input[i]);
                    fwrite(&second_input[i], sizeof(short),1, pointer);
                }
            }
            
            else{                                        //writing to the file in ascii form
                uint8_t type = 1;
                fwrite(&type, sizeof(uint8_t),1, pointer);
                fprintf(pointer, "%s", amount_);

                for(int i = 0; i<amount; i++){
                    fprintf(pointer,"%d",second_input[i]);
                }
            }
            
            return i;
        }
        else{
            if(j>0){
                value = value*10 + (binary_buffer[i]-48);
                //printf("just the value is for the so on and so forth %ld\n", value);
                i = i + 1;
                j = j + 1;
            }
            else{
                value = binary_buffer[i]-48;
                //printf("just the value is for the first time is  %ld\n", value);
                j = j+1;
                i = i+1;
            }
        }
    }
}

void convert_to_typeZero(FILE* pointer, short amount, short numbers[]){
    if(convert_option == 3 || convert_option == 2){
        printf("Converting \n");
        uint8_t type = 0;
        uint8_t amount = (uint8_t) amount;
        
        fwrite(&type, sizeof(uint8_t), 1, pointer);
        fwrite(&amount, sizeof(uint8_t),1, pointer);
        for(int i =0; i<amount; i++){
            printf("%d............type0\n",numbers[i]);
            fwrite(&numbers[i], sizeof(short),1, pointer);
            
        }
    }
    else{
        printf("Just write whatever files we read onto the writefile\n");
    }
    printf("Converted\n");
    
}










