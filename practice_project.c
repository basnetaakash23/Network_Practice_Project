#include "stdio.h"
#include "stdlib.h"

int main(){
	int length_of_file;
	FILE *ptr;
	
	ptr = fopen("practice_project_test_file_1","rb");
	fseek(ptr, 0, SEEK_END);
	length_of_file = ftell(ptr);
	printf("The length of file is %d\n",length_of_file);
	rewind(ptr);
	char buffer[length_of_file];
	int num_of_bytes = fread(buffer, length_of_file, 1, ptr);
	int j = 0;
	for(int i =0; i < (sizeof(buffer)/sizeof(buffer[0]));){
		//printf("%02x\n",buffer[i]);
		/*int size = sizeof(buffer[i]);
		printf("The size of a buffer[i+1] is %d\n", size);*/
		//printf("The index just before entering the if conditional is %d\n",i);

		/*if(buffer[i] == 0){
			//printf("Buffer i is %02x and index is %u\n",buffer[i], i);
			printf("The index here is %d\n", i);
			j = first_input_type_to_second(i, buffer);

		}*/
		else if(buffer[i] == 1){
			j = second_input_type_to_first(i, buffer);

		}
		i++;
	}
	return 0;
}


int first_input_type_to_second(int pos, char* binary_buffer){
	int size_of_unit = 2;
	//printf("The number in binary buffer is %d",(int)binary_buffer[pos+1]);
	
	int num_of_units = size_of_unit * binary_buffer[pos+1];
	char first_input[num_of_units/2];
	printf("The number of amount is %d\n",binary_buffer[pos+1]);
	//printf("The num of units is %d\n", num_of_units);
	unsigned int amount = (binary_buffer[pos+1] << 8 | binary_buffer[pos+2]); //since the amount of type 0 is always 2 bytes

	
	/*int num_of_units = size_of_unit * int(binary_buffer[pos+1]);//trying to figure out how many numbers of units are there */

	int count = pos+2;
	int inner_count = 0;
	int i =0;
	
	while(inner_count < num_of_units){
		first_input[i] = binary_buffer[count] << 8 | binary_buffer[count+1] ;
		i = i + 1;
		//printf("%02x\n",first_input[i]);
		count = count + 2;
		inner_count = inner_count + 2;
	}

	return count-1;
}
int second_input_type_to_first(int pos, char* binary_buffer){
	int i = pos;
	int amount = (binary_buffer[i+1]<<16 | binary_buffer[i+2] << 8 | binary_buffer[i+3]) ;
	printf("The amount is %x\n",amount);
	char second_input[3];
	char value;
	i = i + 4;
	int j = 1;               //for byte concatenation
	value = binary_buffer[i];
	while(binary_buffer[i]!=0 | binary_buffer[i]!=1){
		if(binary_buffer[i] == '2c'){
			value = binary_buffer[i+1];
			i = i+1;
			j = 1;
			continue
		}
		else if(binary_buffer[i+1]){
			value = binary_buffer[i+1]<<8*j | value;

			j = j+1;
			i = i+1;
		}
		
	}





	return 0;


}








