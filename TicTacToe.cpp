#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <cstring>
#include <sys/wait.h>
using namespace std;


bool game_over = false;
void tokenize(char *input,int &argc,  char **argv){
    //checks for the spaces in the user input
    argc = 0;
    char *token = strtok(input, " ");
    while (token != NULL ) {
        //each token is stored in argv array
        *argv++ = token;
        argc++;
        //calls again with null argument to get next token
        token = strtok(NULL, " ");
    }
    *argv = NULL;
}
bool isWin(char arr[], int grid){
    int verticalx[grid];
    int verticalo[grid];
    int cases =0;
    int horizontalx[grid];
    int horizontalo[grid];
    int diagonalx[grid];
    int diagonalx2[grid];
    int diagonalo[grid];
    int diagonalo2[grid];
    int win1 = 88;
    int win2 = 79;
    for(int i =0; i<grid; i++){
        verticalx[i] = 0;
        verticalo[i] = 0;
        horizontalx[i] = 0;
        horizontalo[i] = 0;
        diagonalo[i] = 0;
        diagonalx[i] = 0;
        diagonalo2[i] = 0;
        diagonalx2[i] = 0;
    }
    //cases for if x's win vertically
    for (int i = 0; i<grid*grid; i++ ){
        for (int j = 0; j < grid; j++){
            if (arr[i] == win1 ){
                verticalx[cases]++;

                if (verticalx[cases]== grid){
                    cout<<"Player X wins! \nPlayer O loses\n";
                    game_over = true;
                    exit(1);
                }
            }
            i+=grid;
        }
        cases++;
        i-=(grid*grid);
        if (i >= grid -1 ){
            break;
        }
    }
    cases = 0;
    //cases for if o wins vertically
    for (int i = 0; i<grid*grid; i++ ){
        for (int j = 0; j < grid; j++){
            if (arr[i] == win2 ) {
                verticalo[cases]++;
                if (verticalo[cases]== grid){
                    cout<<"Player O wins!\nPlayer X loses\n";
                    game_over = true;
                    exit(1);
                }
            }
            i+=grid;
        }
        cases++;
        i-=(grid*grid);
        if (i >= grid -1 ){
            break;
        }
    }
    //horizontal cases for x
    cases =0;
    for (int i = 0; i<grid*grid; i++ ){
        for (int j = 0; j < grid; j++){
            if (arr[i] == win1 ) {
                horizontalx[cases]++;
                if (horizontalx[cases]== grid){
                    cout<<"Player X wins!\nPlayer O loses\n";
                    game_over = true;

                    exit(1);
                }
            }
            i++;
        }
        cases++;
        i--;

        if (i >= grid*grid -1 ){
            break;
        }
    }
    //horizontal cases for o
    cases = 0;
    for (int i = 0; i<grid*grid; i++ ){
        for (int j = 0; j < grid; j++){
            if (arr[i] == win2 ) {
                horizontalo[cases]++;
                if (horizontalo[cases]== grid){
                    cout<<"Player O wins!\nPlayer X loses\n";
                    game_over = true;
                    exit(1);
                }
            }
            i++;
        }
        cases++;
        i--;

        if (i >= grid*grid -1 ){
            break;
        }
    }
    //check diagonal cases for x
    cases =0;
    for (int i =0; i<grid*grid; i++){
        for (int j =0; j< grid; j++){

            if (arr[i] == win1){
                diagonalx[cases]++;
                if(diagonalx[cases] == grid){
                    cout<<"Player X wins! \nPlayer O loses\n";
                    game_over = true;
                    exit(1);
                }

            }
            i += grid +1;

        }
    }
    //diagonal cases for backwards side
    cases =0;
    for (int i =0 ; i<grid*grid; i++){
        for (int j =0; j< grid; j++){
            i += grid-1;
            if(arr[i] == win1){
                diagonalx2[cases]++;
                if(diagonalx2[cases]== grid){
                    cout<<"Player X wins!\nPlayer O loses\n";
                    game_over = true;
                    exit(1);
                }
            }
        }

        i = grid*grid;
    }
    //check for diagonal cases for o
    cases =0;
    for (int i =0; i<grid*grid; i++){
        for (int j =0; j< grid; j++){
            if (arr[i] == win2){
                diagonalo[cases]++;
                if(diagonalo[cases] == grid){
                    cout<<"Player O wins!\n Player X loses\n";
                    game_over = true;
                    exit(1);
                }
                i += grid;
            }
        }
        i += grid+1;

    }
    //check backwards diagonal for o
    cases =0;
    for (int i =0 ; i<grid*grid; i++){
        for (int j =0; j< grid; j++){
            i += grid-1;
            if(arr[i] == win2){
                diagonalo2[cases]++;
                if(diagonalo2[cases]== grid){
                    cout<<"Player O wins!\nPlayer X loses\n";
                    game_over = true;
                    exit(1);
                }
            }
        }

        i = grid*grid;
    }
    //check for draw
    cases = 0;
    for (int i =0; i<grid*grid; i++){
        if(arr[i] ==  win2 || arr[i] == win1){
            cases++;
        }
        if(cases == grid*grid){
            cout<<"Its a tie! XO\n";
            game_over = true;
            exit(0);
        }
    }
//call will exit while loop
    return game_over;
}
void display(int grid, char arr[]) {
    //const char* x[2] = {"X", "O"};
    int count = 0;
    int a;
    for (int i =0; i<grid; i++){
        for(int j = 0; j<grid -1; j++){
            cout<<" " ;
            if ((int)arr[count] >70){
                cout<< arr[count];
            }
            else {
                cout << (int) arr[count];
            }
            cout <<" |";
            count++;
        }

            cout << " " ;
    if((int)arr[count]>70){
        cout<<arr[count];
    }
    else {
        cout << (int) arr[count];
    }
        count++;
        cout<<"\n";
        for(int x = 0; x<grid*4 -1; x++) {
            if ( i == grid -1 ){
                break;
            }
            cout << "-";
        }
        cout<<"\n";
    }
}
void play(char *input,int argc, char **argv, char arr[],int pid,  int grid){
    cout <<"Enter your move based on numbers on board: ";
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    tokenize(input, argc, argv);

    int move;
    try {
        move = stoi(input);
        if(move >=grid*grid ){

            while(move >= grid*grid ){
                cout<<"invalid parameter try again\n";
                cout <<"Enter the box number for your move: ";
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                tokenize(input, argc, argv);
                move = stoi(input);
            }
        }
    }
    catch(...){

        while(move >= grid*grid){
            cout<<"Needs to be a number on the board: ";
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            tokenize(input, argc, argv);
            move = stoi(input);
        }

    }
    //checks if the spot is already taken and prompts user for input again
    while(arr[move]== 88|| arr[move]==79){
        cout<<"Choose a spot that's not already taken\n";
        cout <<"Enter the box number for your move: ";
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        tokenize(input, argc, argv);
        move = stoi(input);
    }

    for (int i = 0; i<grid*grid; i++) {

        if (i == move) {
            if (pid == 0) {
                arr[i] = 'X';
                display(grid, arr);
                isWin(arr, grid);
                return;
            } else {
                arr[i] = 'O';
                display(grid, arr);
                isWin(arr, grid);
                return;
            }
        }
    }
    return;
}

int main( int argc, char *argv[]) {
    
    int grid_size;
    if( argc==1){
        grid_size = 3;
    }
    else if( argc = 2 ) {
        try{
            grid_size = stoi(argv[1]);
            if ( grid_size < 2 ){
                cout <<"Invalid number\n";
                exit(0);
            }
        }
        catch (...){
            cout <<"Invalid parameter\n";
            exit(0);
        }

    }
    else {
        return 0;
    }
    //board size using user input
    char input[500];
    int row = grid_size;
    int col = grid_size;
    char arr[row*col];
    for (int i = 0; i<row*col; i++){
        arr[i] = (char)i;

    }
    display(grid_size, arr);
    while( game_over != true) {
         // Create the two processes
         pid_t pid = vfork();
         if (pid == 0){
             play(input,argc, argv,  arr,pid,  grid_size);

             exit(0);
         }
         else if( pid > 0){
             if(game_over == true){
                 exit(0);
             }
             play(input, argc, argv, arr,pid,   grid_size);
             wait(NULL);
         }
         else {
             //something went wrong with forking process
         }
    }
}