#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#define len(arr) (sizeof(arr) / sizeof(arr[0]))

char area[1000][1000];
char temp[1];
int x = 0;
int y = 0;
int ch;
int lastline = 0;
int iii =0;
int prev = 0;
int py =0;
char result[5];
char* number(int num){
    if (num < 10){
        sprintf(result,"000%d",num);
    }
    else if (num < 100){
        sprintf(result,"00%d",num);
    }
    else if (num < 1000){
        sprintf(result,"0%d",num);
    }
    else if (num < 10000){
        sprintf(result,"%d",num);
    }
    else{
        sprintf(result,"9999");
    }
    return result;
}





void disp(){

    prev = y / 27;
    for (int i = (27*prev); i < (27*prev +28); i++){
        if (i == y){ //checking if line has the cursor
            temp[0] = area[y][x]; // storing whats at the cursor
            area[y][x] = '~';   // placing in the cursor
        }
        printw("%s | %s\n",number(i),area[i]); // print
    }

    area[y][x] = temp[0]; // add back actual value
    printw("%d   %d    %ld",x,y,len(area[y]));

}



int main(int argc, char *argv[]){
    initscr();            // Start ncurses mode
    keypad(stdscr, TRUE); // Enable arrow keys
    noecho();             // Do not display input
    cbreak();             // Disable line buffering


    FILE *file = fopen(argv[1], "r");
    
    while (fgets(area[iii], len(area[iii]), file) != NULL) {
        for ( int chrs = 0; chrs < len(area[iii]); chrs++){
            if ( area[iii][chrs] == '\n'){
                area[iii][chrs] = '\0';
            }
        }
        iii++;
    }


    fclose(file);

    file = fopen(argv[1], "w");
    
    printf("\n");
    
    printw("Press arrow keys (ESC to exit)\n");
    disp();
    while ((ch = getch()) != 27) { // 27 = ESC key
        
        
        
        
        switch (ch) {
            case KEY_UP:
                erase();
                if ( y > 0){
                    y--;
                }
                printw("Up arrow key detected!\n");

                if (area[y][x] == '\0'){
                    for (int ii = 0; ii <= x; ii++){
                        if (area[y][ii]== '\0')
                            area[y][ii] = ' ';
                    }
                }


                disp();
                refresh();  // Update screen
                break;
            case KEY_DOWN:
                erase();
                if ( y < len(area) -1 ){
                    y++;
                }

                if (area[y][x] == '\0'){
                    for (int ii = 0; ii <= x; ii++){
                        if (area[y][ii]== '\0')
                            area[y][ii] = ' ';
                    }
                }
                


                printw("Down arrow key detected!\n");
                disp();
                refresh();  // Update screen
                break;
            case KEY_LEFT:
                erase();
                if (x>0){
                    x--;
                }
                printw("Left arrow key detected!\n");
                disp();
                refresh();  // Update screen
                
                break;
            case KEY_RIGHT:
                erase();
                x++;
                    if (area[y][x] == '\0'){
                        for (int ii = 0; ii <= x; ii++){
                            if (area[y][ii]== '\0')
                                area[y][ii] = ' ';
                        }
                    }
                

                
                printw("Right arrow key detected!\n");
                disp();
                refresh();  // Update screen
                
                break;
            case KEY_BACKSPACE:
                erase();
                if (x != 0)
                x--;
                area[y][x] = ' ';
                printw("Backspace key detected!\n");
                disp();
                refresh();
                break;
            case '\n':
            case KEY_ENTER:
                erase();
                x=0;
                y++;
                printw("Enter key detected\n");
                disp();
                refresh();
                break;
            case 15:
                erase();
                printw("Ctrl + O detected\n");
                disp();
                refresh();
                lastline = -1;  // Reset lastline before finding it
                for (int line = 0; line < len(area); line++){
                    if (area[line][0] != '\0') {  // Check if the line is not empty
                        lastline = line;
                    }
                }
            
                // Write the content of 'area' to the file
                for (int line = 0; line <= lastline; line++) {
                    if (area[line][0] == '\0') {
                        fprintf(file, "\n");  // Empty line, write only newline
                    } else {
                        fprintf(file, "%s\n", area[line]);  // Non-empty line, write the content
                    }
                }
                fclose(file);
                endwin();
                return 0;

                break;
            default:
                erase();
                printw("You pressed: %c\n", ch);
                area[y][x] = ch;
                x++;      
                disp();
                refresh();  // Update screen
                break;
        }
    }

    endwin();  // End ncurses mode
    return 0;
}
