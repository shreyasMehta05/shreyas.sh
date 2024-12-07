#include"display.h"

void printfColor(color *COLOR,const char* str,bool bold){
    // print string with color and bold
    if(bold){
        if(printf("%s",BOLD)==-1){
            fprintf(stderr,RED"Error Occoured in display/display.c --> printfColor()\n"RESET);
            exit(EXIT_FAILURE);
        }
    }
    if(printf("%s%s%s",COLOR,str,RESET)==-1){
        fprintf(stderr,RED"Error Occoured in display/display.c --> printfColor()\n"RESET);
        exit(EXIT_FAILURE);
    }
}