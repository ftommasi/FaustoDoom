#include <stdio.h>
#include <stdlib.h>

#define byte char

typedef struct WAD{
    char type[5];
    unsigned int num_entries;
    unsigned int* directory;

}WAD;


const unsigned int big_endian_to_little_endian(unsigned int four_bytes){
  const unsigned int num_bits = 24; 
  
  //TODO:should everything shift in the same direction so its not confusing?
  return 
  (
  ((four_bytes & 0x000000ff) << num_bits) | 
  ((four_bytes & 0x0000ff00) << (num_bits - 16)) |
  ((four_bytes & 0x00ff0000) >> (num_bits - 16)) |
  ((four_bytes & 0xff000000) >> num_bits) 
  ) ;
}


int get_next_int_from_file(FILE* file){
    unsigned int num_entries = 0;
    char entries_string[5];
    entries_string[4] = 0;
    int i;
    for(i=0; i < 4; i++){
        int char_got = fgetc(file);
        entries_string[i] = char_got;
        num_entries |= (char_got & 0x000000ff);
        if(i != 3){
            num_entries = num_entries << 8;
        }
    }
    return num_entries;
}

int main(){
    const char* filename = "DOOM.wad";
    FILE* wad_file = fopen(filename,"r+");
    
    //process WAD header
    char file_type[5];
    file_type[4] = 0;
    int i;
    for(i=0; i < 4; i++){
        file_type[i] = fgetc(wad_file);
    }
    unsigned int  num_entries = big_endian_to_little_endian(get_next_int_from_file(wad_file));
    unsigned int  directory = big_endian_to_little_endian(get_next_int_from_file(wad_file));

    //process rest of WAD 
    //TODO errpr catching
    //assert(!feof(wad_file));
    while(1){
        int file_data =fgetc(wad_file);
        if(feof(wad_file)){
            break;
        }
    }
    fclose(wad_file);
    return 0;
}
