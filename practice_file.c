//
//  practice_file.c
//  
//
//  Created by AakashBasnet on 3/8/18.
//

#include <stdio.h>

int main(){
    FILE *fp;
    
    int num[4] = {23,26,27,28};
    int *p = num;
    int c;
    fp = fopen("file2.bin", "ab");
    for(int i = 0; i<4; i++){
        fwrite(p+i, sizeof(int), 1, fp);
        
    }
    while(1){
        c = fgetc(fp);
        if(feof(fp)){
            break;
        }
        printf("%d\n", c);
    }
    
    fclose(fp);
    
    return 0;
}
