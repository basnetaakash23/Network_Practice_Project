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
	for(int i =0; i < (sizeof(buffer)/sizeof(buffer[0]));i++){
		printf("%u\n",buffer[i]);
	}
	return 0;
}






