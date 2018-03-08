#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
	int length_of_file;
   
	FILE *ptr;
    FILE *ptr1;
	
	ptr = fopen("practice_project_test_file_1","rb");
    ptr1 = fopen("practice_project_write_file","ab+");
    fseek(ptr1, 0, SEEK_SET);
	fseek(ptr, 0, SEEK_END);
	length_of_file = ftell(ptr);
	printf("The length of file is %d\n",length_of_file);
	rewind(ptr);
	char buffer[length_of_file];
	int num_of_bytes = fread(buffer, length_of_file, 1, ptr);
	int j = 0;
    int i = 0;
//    while(i < length_of_file){
//        //printf("%02x\n",buffer[i]);
//        /*int size = sizeof(buffer[i]);
//        printf("The size of a buffer[i+1] is %d\n", size);*/
//        //printf("The index just before entering the if conditional is %d\n",i);
//        printf("The value in buffer is %u\n",buffer[i]);
//        if(buffer[i] == 0){
//            //printf("Buffer i is %02x and index is %u\n",buffer[i], i);
//            printf("The index here in type 1 is %d\n", i);
//            i = first_input_type_to_second(i, buffer);
//            printf("The index returned here in type 1 is %d\n",i);
//
//        }
//        else if(buffer[i] == 1){
//            printf("The index here in type 2 is %d\n",i);
//            i = second_input_type_to_first(i, buffer);
//            printf("The index returned here in type 2 is %d\n",i);
//        }
//
//    }
    printf("The index here in type 1 is %d\n",i);
    i = second_input_type_to_first(35, buffer, ptr1);
    printf("The index returned here in type 1 is %d\n",i);
    return 0;
}

extern int convert_option =3;
int first_input_type_to_second(int pos, char* binary_buffer, FILE* pointer){
    printf("The index before entering type 1 is %d\n", pos);
	int size_of_unit = 2;
	//printf("The number in binary buffer is %d",(int)binary_buffer[pos+1]);
	
	int num_of_units = size_of_unit * binary_buffer[pos+1];
	short int first_input[num_of_units/2];
	printf("The number of amount is %d\n",binary_buffer[pos+1]);
	//printf("The num of units is %d\n", num_of_units);
    if(convert_option == 3 || convert_option == 1){
        char type = '3';
        fwrite(type, sizeof(char), 1, pointer);
        char amount[3] = {'48','48',(char)amount};
        for(int x = sizeof(amount)/sizeof(char)-1; x>=0;x--){
            fwrite(amount+x, sizeof(char), 1, pointer);
        }
    }

	
	/*int num_of_units = size_of_unit * int(binary_buffer[pos+1]);//trying to figure out how many numbers of units are there */

	int count = pos+2;
	int inner_count = 0;
	int i =0;
	
	while(inner_count < num_of_units){
        printf("The binary_buffer is %d\n",binary_buffer[count]);
        printf("The binary_buffer+1 is %d\n",binary_buffer[count+1]);
//        first_input[i] = binary_buffer[count] <<8 | binary_buffer[count+1] >> 8;
//        printf("%d\n",first_input[i]);
        
        
        
        memcpy(first_input+i, (binary_buffer+count), 2);
        char *buffer;
        if(convert_option == 3 || convert_option == 1){
            sprintf(pointer,"%d", first_input+i);
            if(inner_count<=num_of_units-2){   //if condition to insert comma
                sprintf(pointer,"%c",",");
            }
            
        }
		i = i + 1;
		
		count = count + 2;
		inner_count = inner_count + 2;
	}
     //printf("The index before returning to main from type 1 is %d\n", count );
	return count;
}
int second_input_type_to_first(int pos, char* binary_buffer, FILE *pointer){
    printf("The index before entering type 2 is %d\n", pos);
	int i = pos;
    
	//int amount = (binary_buffer[i+1]<<16 | binary_buffer[i+2] << 8 | binary_buffer[i+3]) ;
    int amount = (binary_buffer[i+1]-48)*100 + (binary_buffer[i+2]-48)*10 + binary_buffer[i+3]-48;
//    printf("The binary buffer[i+1] is %d\n",binary_buffer[i+1]-48);
//    printf("The binary buffer[i+2] is %d\n",binary_buffer[i+2]-48);
//    printf("The binary buffer[i+3] is %d\n",binary_buffer[i+3]-48);
	printf("The amount is %d\n",amount);
	char second_input[amount];    //this is where we store asccii values so that they can be written later on on file
	
	i = i + 4;
	int count = 1;
    //for counting the numbers of unit of the type 1 and we assume that there is at least one such unit until we find either 0 or a comma.
    int j  = 0; //working around with concatenating the bytes of ascii values
    long value = 0;      //this is the variable where we temporarily store the asccii value
    int num_of_units = 0;
    int comma = 44;
    int type0 = 0;
    int type1 = 1;     //assigning value to type 1
    int ind = 0;      //this for storing values of numbers in character array
    
    while(num_of_units<amount){
        if(binary_buffer[i] == comma){
            num_of_units = num_of_units + 1;
            printf("The value of value is %ld\n",value);
            second_input[ind] = value;
            ind = ind + 1;
            i = i+1;
            j=0;
        }
        else if(binary_buffer[i] == type0 || binary_buffer[i] == type1){
            
            printf("The index before returning to main from type 2 is %d\n", i);
            if(convert_option == 3 && convert_option == 2){
                char type = '0';
                fwrite(type, sizeof(char), 1, pointer);
                char amount = (char)amount;
                fwrite(amount, sizeof(char),1, pointer);
                for(int index = 0; index<amount; index++){
                    fwrite((uint16_t)second_input[index], sizeof(uint16_t),1, pointer);
                }
                
                
            }
            else{
                printf("Just write whatever files we read onto the writefile\n");
            }
            
            return i;
        }
        else{
            if(j>0){
                value = value*10 + (binary_buffer[i]-48);
                printf("just the value is for the so on and so forth %ld\n", value);
                i = i + 1;
                j = j + 1;
            }
            else{
                value = binary_buffer[i]-48;
                printf("just the value is for the first time is  %ld\n", value);
                j = j+1;
                i = i+1;
        }
    }
    
 }
}








