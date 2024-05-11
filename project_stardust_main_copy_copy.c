/*
Ioannis Marios Damalas
AM: 2022202300234
dit23234@go.uop.gr

Dimitrios Xristos Dafnomilis
AM: 2022202300245
dit23245@go.uop.gr
*/

//Function Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

//Programmer created Functions

char **Ship(int n, int m); //Allocates the memory needed for the game
void Evac(char **arr, int n); //"Evacuates" the allocated memory
void Menu(void); //Prints the main menu
void Boarding(int d, char **arr, int n, int m); //Spawns the enemies and obstacles "The stormtroopers board the ship with their 'supplies' (obstacles)"
void MCS(char **arr, int n, int m); //Spawns the main characters like the player (Leia), Darth Vader and R2D2
void PrintBoard(char **arr, int n, int m); //Prints the "Game Board"
void Help(char **arr, int n, int m); //Prints the board with no hidden tiles
void move_obj(char **arr1, char moves[]); //Moves an object from pos 1 to pos 2
void move_vader(char **arr, int n, int m); //Moves Vader closer to Leia (Player)
void move_storm(char **arr, int n, int m); //Moves the stormtroopers
int leia_moves(char **arr, char moves[], int n, int m, int lifes); //Moves Leia according to the player's instructions




//main START
int main(void)
{
    srand(time(NULL));

    int N, M, diff, i, j, k, hp = 1, len, lvl = 1, flag = 0, cnt = 0;
    char **Tantive_IV, mov[7] = {0};

    printf("Salutations, Princess Leia...\nPlease input the starting size ( N x M ) of your ship:\n");
    scanf("%d%d",&N,&M);
    while (((N < 12) && (M < 12)) || ((N > 26) && (M > 26)))
    {
        printf("Please input a valid starting size (12-26).\n");
        scanf("%d%d",&N,&M);
    }
    printf("\nPerfect!\nNow please input the challenge you would like to face:\n");
    printf("\n\t1. Easy\n\n\t2. Medium\n\n\t3. Hard\n\n\t4. Impossible\n");
    scanf("%d",&diff);
    //printf("\nSo you chose %d x %d size and difficulty %d\n",N,M,diff);
    while ((diff < 1) || (diff > 4))
    {
        printf("Please input a valid difficulty setting (1-4).\n");
        scanf("%d",&diff);
    }

    
    
        level_creation:
        
        if (((N < 8) && (M < 8)) || (lvl == 7))
        {
            printf("After finding R2D2, you secure the plans with him and record a message for someone who you think will be able to help.\nThen you send R2 with a mission to find C3P0 and board an escape pod to land on the planet of Tatooine and deliver the message.\nThanks for playing!!!\n\n");
            exit(1);
        }
        else
        {

        
            Tantive_IV = Ship(N,M);

            //Board(Tantive_IV,N,M);

            Boarding(diff,Tantive_IV,N,M);

            //printf("\n\n\n\n");

            //Board(Tantive_IV,N,M);

            //printf("\n\n\n\n");

            MCS(Tantive_IV,N,M);



            for (k = 0 ; k < 100000 ; k++)
            {
                if (hp == -1)
                {
                    N--;
                    M--;
                    hp = 1;
                    lvl++;
                    if (((N < 8) && (M < 8)) || (lvl == 7))
                    {
                        printf("Congratulations!\nThat was the last level!\nThanks for playing!!!\n\n");
                    }
                    else
                    {
                        printf("Nice going!\nChanging level...\n\n");
                    }
                    Evac(Tantive_IV,N);
                    cnt = 0;
                    goto level_creation; //Find out why there is an extra getchar. (Visual Studio Enterprise)
                }

                PrintBoard(Tantive_IV,N,M);
                if (k == 0)
                {
                    if (lvl == 1)
                    {
                        getchar();
                    }
                }
                printf("\nLevel %d\n",lvl);
                printf("Make your move(s) : ");
                fgets(mov,sizeof(mov),stdin);
                printf("\n");
                len = strlen(mov);
                //puts(mov);
                
                for (i = 0 ; i < len ; i++)
                {
                    if (mov[i] == '\n')
                    {
                        mov[i] = '\0';
                    }
                }   

                for (i = 0 ; i < len ; i++)
                {
                    if (mov[i] == '>')
                    {
                        flag = 1;
                    }
                }

                if (flag == 0)
                {
                    hp = leia_moves(Tantive_IV,mov,N,M,hp);
                }
                else
                {
                    if (cnt == 2)
                    {
                        printf("You have used up all your force energy and cannot move objects anymore for this level.\n\n");
                        flag = 0;
                    }
                    else
                    {
                        move_obj(Tantive_IV,mov);
                        flag = 0;
                        cnt++;
                    }
                }
            }
        }
        
    return 0;  
}
//main END

//Ship START
char **Ship(int n, int m)
{
    int i,j;
    char **arr;

    arr=(char**)malloc(n * sizeof(char*)); //Allocates memory for the rows

    if(arr == NULL) //Checks if malloc returned NULL
    {
        printf("\nError when allocating memory!\nTerminating...\n");
        exit(1); //If it has, the program terminates
    }

    for ( i = 0 ; i < n ; i++) 
    {
        arr[i] = (char*)malloc(m * sizeof(char)); //Allocates memory for the collumns

        if (arr[i] == NULL) //Checks if malloc returned NULL in every collumn
        {
            printf("\nError when allocating memory!\nTerminating...\n");
            exit(1); //If so the program terminates
        }

        for ( j = 0 ; j < m ; j++)
        {
            arr[i][j] = '#'; //Puts the hidden symbol '#' in every cell of the array
        }
    }

    return arr; //Returns the array
}
//Ship END

//Evac START
void Evac(char **arr, int n)
{
    int i;

    for (i = 0 ; i < n ; i++)
    {
        free(arr[i]);
    }
    free(arr);
}
//Evac END

//Menu START
void Menu(void)
{

}
//Menu END

//Boarding START
void Boarding(int d, char **arr, int n, int m)
{
    int i,en,obs,pos1,pos2;
    double r1,r2;
    if (d == 1) //Checks for the difficulty
    {
        en = (2 * (n * m)) / 100; //Finds the 2% of the array
        obs = (13 * (n * m)) / 100; //Finds the 13% of the array
        if ((en == 0) || (en == 1))
        {
            en = 2;  //remember to make it so it checks if en is less than 0.5 to ask the player to give a bigger array, if it's 0.5 <= en <= 1 then make en = 1
        }

        for (i = 0 ; i < en ; i++)
        {

            do //Loop that finds a random spot for the enemies, which is not the same as another enemy or is not the same as a corner block
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));
            
            arr[pos1][pos2] = '@'; //Puts the stormtrooper in the fresh found spot
            

        }



        for (i = 0 ; i < obs ; i++)
        {
            do  //Loop that finds a random spot for the obstacles, which is not the same as another obstacle or is not the same as a corner block
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));

            arr[pos1][pos2] = 'X'; //Puts the obstacle

        }

    }
    else if (d == 2)
    {
        en = (5 * (n * m)) / 100; //Finds the 5% of the array
        obs = (10 * (n * m)) / 100; //Finds the 10% of the array
        if ((en == 0) || (en == 1))
        {
            en = 2;
        }

        for (i = 0 ; i < en ; i++)
        {
            do
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));
            
            arr[pos1][pos2] = '@';

        }

        printf("\n\n");

        for (i = 0 ; i < obs ; i++)
        {
            do
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));
            
            arr[pos1][pos2] = 'X';

        }
    }
    else if (d == 3)
    {
        en = (10 * (n * m)) / 100;
        obs = (5 * (n * m)) / 100;
        if ((en == 0) || (en == 1))
        {
            en = 2;
        }

        for (i = 0 ; i < en ; i++)
        {
            do
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));

            arr[pos1][pos2] = '@';

        }

        printf("\n\n");

        for (i = 0 ; i < obs ; i++)
        {
            do
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));

            arr[pos1][pos2] = 'X';

        }
    }
    else if (d == 4)
    {
        en = (15 * (n * m)) / 100;
        if ((en == 0) || (en == 1))
        {
            en = 2;
        }

        for (i = 0 ; i < en ; i++)
        {
           do
            {
                r1 = (double)rand() / ((double) (RAND_MAX));
                r1 = r1 * n;
                pos1 = (int) r1;

                r2 = (double)rand() / ((double) (RAND_MAX));
                r2 = r2 * m;
                pos2 = (int) r2;
                //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
            }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));

            arr[pos1][pos2] = '@';

        }

        printf("\n\n");

    }

    return;
}
//Boarding END

//MCS START
void MCS(char **arr, int n, int m)
{
    int pos1,pos2;
    double r1,r2;
    
    //R2D2
    do
    {
        r1 = (double)rand() / ((double) (RAND_MAX));
        r1 = r1 * n;
        pos1 = (int) r1;
        r2 = (double)rand() / ((double) (RAND_MAX));
        r2 = r2 * m;
        pos2 = (int) r2;
        //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
    }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || ((pos1 == 0) && (pos2 == 0)) || ((pos1 == (n-1)) && (pos2 == (m-1))) || ((pos1 == 0) && (pos2 == (m-1))) || ((pos1 == (n-1)) && (pos2 == 0)));

    arr[pos1][pos2] = 'R';

    //Darth Vader
    r1 = (double)rand() / ((double) RAND_MAX + 1);
    r1 = r1 * 4 + 1;
    pos1 = (int) r1;
    if (pos1 == 1)
    {
        arr[0][0] = 'D';
    }
    else if (pos1 == 2)
    {
        arr[0][m-1] = 'D';
    }
    else if (pos1 == 3)
    {
        arr[n-1][0] = 'D';
    }
    else if (pos1 == 4)
    {
        arr[n-1][m-1] = 'D';
    }

    //Princess Leia (Player)
    do
    {
        r1 = (double)rand() / ((double) (RAND_MAX));
        r1 = r1 * n;
        pos1 = (int) r1;
        r2 = (double)rand() / ((double) (RAND_MAX));
        r2 = r2 * m;
        pos2 = (int) r2;
        //printf("[%d,%d]\n\n",pos1,pos2); //Prints the random selected position
    }while ((arr[pos1][pos2] == '@') || (arr[pos1][pos2] == 'X') || (arr[pos1][pos2] == 'R') || (arr[pos1][pos2] == 'D'));    
    
    arr[pos1][pos2] = 'L';

    return;

}
//MCS END

//PrintBoard START
void PrintBoard(char **arr, int n, int m)
{
    int i,j,cnt = 5,lp1,lp2;
    char c = 'A';

    //LEIA LOCATION FINDER
    for (i = 0 ; i < n ; i++)
    {
        for (j = 0 ; j < m ; j++)
        {
            if (arr[i][j] == 'L')
            {
                lp1 = i;
                lp2 = j;
            }
        }
    }





    printf("    ");
    for (i = 0 ; i < m ; i++)
    {
        printf(" %c",c);
        c++;
        cnt += 2;
    }

    printf("\n");
    
    for ( i = 0 ; i < cnt ; i++)
    {
        printf("-");
    }

    printf("\n");

    for (i = 0 ; i < n ; i++)
    {
        if (i < 9)
        {
           printf("%d | ",i+1); 
        }
        else
        {
            printf("%d| ",i+1);
        }

        for (j = 0 ; j < m ; j++)
        {   
            if ((i == lp1) || (j == lp2)) //Checks what character is standing on the given position (checks if i is in the same column as the char and j is in the same row as char) and prints accordingly to what exists in that spot
            {
                if (arr[i][j] == '@')
                {
                    printf(" %c",arr[i][j]);
                }
                else if (arr[i][j] == 'R')
                {
                    printf(" %c",arr[i][j]);
                }
                else if (arr[i][j] == 'X')
                {
                    printf(" %c",arr[i][j]);
                }
                else if (arr[i][j] == 'D')
                {
                    printf(" %c",arr[i][j]);
                }
                else if (arr[i][j] == 'L')
                {
                    printf(" %c",arr[i][j]);
                }
                else
                {
                    printf(" %c",'.');
                }
            }
            else //Provided that @ or R2D2 is in a non-visible spot (to Leia), then it prints # (hidden area), otherwise it prints the contents of the array, ex. Vader etc.
            {
                if (arr[i][j] == '@')
                {
                    printf(" %c",'#');
                }
                else if (arr[i][j] == 'R')
                {
                    printf(" %c",'#');
                }
                else
                {
                    printf(" %c",arr[i][j]);
                }
            }
        }
        printf("\n");
    }

    return;
}
//PrintBoard END

//Help START
void Help(char **arr, int n, int m)
{
    int i,j,cnt = 5,lp1,lp2;
    char c = 'A';

    printf("    ");
    for (i = 0 ; i < m ; i++)
    {
        printf(" %c",c);
        c++;
        cnt += 2;
    }

    printf("\n");
    
    for ( i = 0 ; i < cnt ; i++)
    {
        printf("-");
    }

    printf("\n");

    for (i = 0 ; i < n ; i++)
    {
        if (i < 9)
        {
           printf("%d | ",i+1); 
        }
        else
        {
            printf("%d| ",i+1);
        }

        for (j = 0 ; j < m ; j++)
        {   
            if (arr[i][j] == '@')
            {
                printf(" %c",'@');
            }
            else if (arr[i][j] == 'R')
            {
                printf(" %c",'R');
            }
            else if (arr[i][j] == '#')
            {
                printf(" %c",'.');
            }
            else
            {
                printf(" %c",arr[i][j]);
            }
        }
        printf("\n");
    }
    return;
}
//Help END

//leia_moves START
int leia_moves(char **arr, char moves[], int n, int m, int lifes)
{
    int i, j, k, l, lp1, lp2, cnt = 0;  
    
    l = strlen(moves);

    for (i = 0 ; i < n ; i++)
    {
        for (j = 0 ; j < m ; j++)
        {
            if (arr[i][j] == 'L')
            {
                lp1 = i;
                lp2 = j;
            }
        }
    }
    
    for (i = 0 ; i < l ; i++)
    {
        //if ((strncmp(moves+i,"L",1) == 0) || (strncmp(moves+i,"l",1) == 0))
        if ((moves[i] == 'L') || (moves[i] == 'l'))
        {
            if ((lp2 > 0) && (arr[lp1][lp2-1] != 'X'))
            {
                if(arr[lp1][lp2-1] == 'R')
                {
                    arr[lp1][lp2-1] = 'L';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("You found R2D2 and secured the plans for the rebellion!\nYou won!\n\n");
                    return -1;
                }
                else if(arr[lp1][lp2-1] == 'D')
                {
                    arr[lp1][lp2-1] = 'D';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("\nOh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n\n");
                    exit(1);
                }
                else if (arr[lp1][lp2-1] == '@')
                {
                    if (lifes == 1)
                    {
                        arr[lp1][lp2-1] = 'L';
                        arr[lp1][lp2] = '#';
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n\n");
                        lifes--;
                        lp2--;
                        cnt++;
                        if ((cnt % 2) == 0)
                        {
                            //move_vader(arr,n,m);
                            printf("Vader moved");
                        }
                    }
                    else
                    {
                        arr[lp1][lp2-1] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        printf("\nOh no... A stormtrooper managed to capture you!\nYou lose!\n\n");
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1][lp2-1] = 'L';
                    arr[lp1][lp2] = '#';
                    lp2--;
                    cnt++;
                    if ((cnt % 2) == 0)
                    {
                        //move_vader(arr,n,m);
                        printf("Vader moved");
                    }
                }
            }
            else
            {
                printf("This move is not possible.\n\n");
            }
        }
        //else if ((strncmp(moves+i,"R",1) == 0) || (strncmp(moves+i,"r",1) == 0))
        else if ((moves[i] == 'R') || (moves[i] == 'r'))
        {
            if ((lp2 < m - 1) && (arr[lp1][lp2+1] != 'X'))
            {
                if(arr[lp1][lp2+1] == 'R')
                {
                    arr[lp1][lp2+1] = 'L';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("You found R2D2 and secured the plans for the rebellion!\nYou won!\n\n");
                    return -1;
                }
                else if(arr[lp1][lp2+1] == 'D')
                {
                    arr[lp1][lp2+1] = 'D';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("\nOh no... Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n\n");
                    exit(1);
                }
                else if (arr[lp1][lp2+1] == '@')
                {
                    if (lifes == 1)
                    {
                        arr[lp1][lp2+1] = 'L';
                        arr[lp1][lp2] = '#';
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n\n");
                        lifes--;
                        lp2++;
                        cnt++;
                        if ((cnt % 2) == 0)
                        {
                            //move_vader(arr,n,m);
                            printf("Vader moved");
                        }
                    }
                    else
                    {
                        arr[lp1][lp2+1] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        printf("Oh no... A stormtrooper managed to capture you!\nYou lose!\n\n");
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1][lp2+1] = 'L';
                    arr[lp1][lp2] = '#';
                    lp2++;
                    cnt++;
                    if ((cnt % 2) == 0)
                    {
                        //move_vader(arr,n,m);
                        printf("Vader moved");
                    }
                }
            }
            else
            {
                printf("This move is not possible.\n\n");
            }   
        }
        //else if ((strncmp(moves+i,"U",1) == 0) || (strncmp(moves+i,"u",1) == 0))
        else if ((moves[i] == 'U') || (moves[i] == 'u'))
        {
            if ((lp1 > 0) && (arr[lp1-1][lp2] != 'X'))
            {
                if (arr[lp1-1][lp2] == 'R')
                {
                    arr[lp1-1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("You found R2D2 and secured the plans for the rebellion!\nYou won!\n\n");
                    return -1;
                }
                else if (arr[lp1-1][lp2] == 'D')
                {
                    arr[lp1-1][lp2] = 'D';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("\nOh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n\n");
                    exit(1);
                }
                else if (arr[lp1-1][lp2] == '@')
                {
                    if (lifes == 1)
                    {
                        arr[lp1-1][lp2] = 'L';
                        arr[lp1][lp2] = '#';
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n\n");
                        lifes--;
                        lp1--;
                        cnt++;
                        if ((cnt % 2) == 0)
                        {
                            //move_vader(arr,n,m);
                            printf("Vader moved");
                        }
                    }
                    else
                    {
                        arr[lp1-1][lp2] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        printf("\nOh no... A stormtrooper managed to capture you!\nYou lose!\n\n");
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1-1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                    lp1--;
                    cnt++;
                    if ((cnt % 2) == 0)
                    {
                        //move_vader(arr,n,m);
                        printf("Vader moved");
                    }
                }
            }
            else
            {
                printf("This move is not possible.\n\n");
            }
              
        }
        //else if ((strncmp(moves+i,"D",1) == 0) || (strncmp(moves+i,"d",1) == 0))
        else if ((moves[i] == 'D') || (moves[i] == 'd'))
        {
            if (lp1 < n - 1 && arr[lp1+1][lp2] != 'X')
            {
                if (arr[lp1+1][lp2] == 'R')
                {
                    arr[lp1+1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("You found R2D2 and secured the plans for the rebellion!\nYou won!\n\n");
                    return -1;
                }
                else if(arr[lp1+1][lp2] == 'D')
                {
                    arr[lp1+1][lp2] = 'D';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    printf("\nOh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n\n");
                    exit(1);
                }
                else if (arr[lp1+1][lp2] == '@')
                {
                    if (lifes == 1)
                    {
                        arr[lp1+1][lp2] = 'L';
                        arr[lp1][lp2] = '#';
                        printf("\nOh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n\n");
                        lifes--;
                        lp1++;
                        cnt++;
                        if ((cnt % 2) == 0)
                        {
                            //move_vader(arr,n,m);
                            printf("Vader moved");
                        }
                    }
                    else
                    {
                        arr[lp1+1][lp2] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        printf("\nOh no... A stormtrooper managed to capture you!\nYou lose!\n\n");
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1+1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                    lp1++;
                    cnt++;
                    if ((cnt % 2) == 0)
                    {
                        //move_vader(arr,n,m);
                        printf("Vader moved");
                    }
                }
            }
            else
            {
                printf("This move is not possible.\n\n");
            }
        }
        else if ((moves[i] == 'H') || (moves[i] == 'h'))
        {
            printf("Hmmmm...\nHelp you need I see...\nFrail do not young one, help you shall I!\n\n");
            Help(arr,n,m);
            printf("\n");
        }
        else if ((moves[i] == 'X') || (moves[i] == 'x'))
        {
            printf("\nExiting game...\n\n");
            Evac(arr,n);
            exit(1);
        }
        else
        {
            printf("\nThis command does not exist, please try one of these eligible commands:\n");
            printf("- Move Commands:\n\t- U/u : Move Leia upwards\n\t- D/d : Move Leia downwards\n\t- L/l : Move Leia to the left\n\t- R/r : Move Leia to the right.\n"); //Another word for going Left is "Sinistral" and for going Right is "Dextral"
            printf("- Special Commands:\n\t- Move Object Command > : Move an object using the force, from pos1 to pos2 (Max 2 times). Example: F4>F5 / f4>f5.\n");
            printf("\t- Help Command H/h : Master Yoda helps you by revealing all the hidden spots on the level.\n");
            printf("\t- Exit Command X/x : Evacuates the ship and closes the game.\n\n");
        }
    }
    
    return lifes;
}
//leia_moves END

//move_obj START
void move_obj(char **arr1, char moves[])
{
    int pi1, pj1, pi2, pj2;
    char c;

    if ((moves[0] >= 'A') && (moves[0] <= 'Z')) //Checks if the first pos is in the space of [A,Z]
    {

        c = moves[0];
        pi1 = (c - 'A') + 1;
    }
    else if ((moves[0] >= 'a') && (moves[0] <= 'z')) //Checks if the first pos is in the space of [a,z]
    {
        c = moves[0];
        pi1 = (c - 'a') + 1;
    }

    c = moves[1];
    pj1 = c - '0';

    if ((moves[3] >= 'A') && (moves[3] <= 'Z')) //Checks if the second pos is in the space of [A,Z]
    {
        c = moves[3];
        pi2 = (c - 'A') + 1;
    }
    else if ((moves[3] >= 'a') && (moves[3] <= 'z')) //Checks if the second pos is in the space of [a,z]
    {
        c = moves[3];
        pi2 = (c - 'a') + 1;
    }

    c = moves[4];
    pj2 = c - '0';

    //printf("[%d,%d]>[%d,%d]\n",pi1,pj1,pi2,pj2);

    pi1--;
    pj1--;
    pi2--;
    pj2--;

    //printf("[%d,%d]>[%d,%d]\n",pi1,pj1,pi2,pj2);

    if (arr1[pj1][pi1] == '#')
    {
        printf("There is not an object there for you to move...\nPlease try another position\n\n");
    }
    else if ((arr1[pj2][pi2] == 'X') || (arr1[pj2][pi2] == 'R') || (arr1[pj2][pi2] == 'L') || (arr1[pj2][pi2] == '@') || (arr1[pj2][pi2] == 'D'))
    {
        printf("There is something in the way and you cannot move the object to that position...\nPlease try another position\n\n");
    }
    else
    {
        arr1[pj2][pi2] = 'X';
        arr1[pj1][pi1] = '#';
        printf("You've succesfully used the force to move an object out of your way!\n\n");
    }

    return;
}
//move_obj END

//move_vader START
void move_vader(char **arr, int n, int m)
{
    int i, j, lpx, lpy, vpx, vpy, dx, dy;  

    //Leia location Finder
    for (i = 0 ; i < n ; i++)
    {
        for (j = 0 ; j < m ; j++)
        {
            if (arr[i][j] == 'L')
            {
                lpx = i;
                lpy = j;
            }
        }
    }
    
    //Vader location finder
    for (i = 0 ; i < n ; i++)
    {
        for (j = 0 ; j < m ; j++)
        {
            if (arr[i][j] == 'D')
            {
                vpx = i;
                vpy = j;
            }
        }
    }
    
    dx = lpx - vpx;
    dy = lpy - vpy;

    if (abs(dx) > abs(dy)) //Left & Right
    {
        if (dx > 0)
        {
            if ((vpx > m - 1) && (arr[vpy][vpx+1] != 'X') && (arr[vpy][vpx+1] != '@') && (arr[vpy][vpx+1] != 'R')) //Right
            {
                if (arr[vpy][vpx+1] == 'L')
                {
                    arr[vpy][vpx+1] = 'D';
                    arr[vpy][vpx] = '#';
                    PrintBoard(arr,n,m);
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n");
                    Evac(arr,n);
                    exit(1);
                }
                else
                {
                    arr[vpy][vpx+1] = 'D';
                    arr[vpy][vpx] = '#';
                    //vpx++;
                }
            }
        }
        else if (dx < 0)
        {
            if ((vpx > 0) && (arr[vpy][vpx-1] != 'X') && (arr[vpy][vpx-1] != '@') && (arr[vpy][vpx-1] != 'R')) //Left 
            {
                if (arr[vpy][vpx-1] == 'L')
                {
                    arr[vpy][vpx-1] = 'D';
                    arr[vpy][vpx] = '#';
                    PrintBoard(arr,n,m);
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n");
                    Evac(arr,n);
                    exit(1);
                }
                else
                {
                    arr[vpy][vpx-1] = 'D';
                    arr[vpy][vpx] = '#';
                    //vpx--;
                }
            }
        }
    }
    else if (abs(dx) < abs(dy)) //Up & Down
    {
        if (dy > 0)
        {
            if ((vpy > 0) && (arr[vpy-1][vpx] != 'X') && (arr[vpy-1][vpx] != '@') && (arr[vpy-1][vpx] != 'R')) //Up
            {
                if (arr[vpy-1][vpx] == 'L')
                {
                    arr[vpy-1][vpx] = 'D';
                    arr[vpy][vpx] = '#';
                    PrintBoard(arr,n,m);
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n");
                    Evac(arr,n);
                    exit(1);
                }
                else
                {
                    arr[vpy-1][vpx] = 'D';
                    arr[vpy][vpx] = '#';
                    //vpy--;
                }
            }
        }
        else if (dy < 0)
        {
            if ((vpy < n - 1) && (arr[vpy+1][vpx] != 'X') && (arr[vpy+1][vpx] != '@') && (arr[vpy+1][vpx] != 'R'))
            {
                if (arr[vpy+1][vpx] == 'L')
                {
                    arr[vpy+1][vpx] = 'D';
                    arr[vpy][vpx] = '#';
                    PrintBoard(arr,n,m);
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\nYou lose!\n");
                    Evac(arr,n);
                    exit(1);
                }
                else
                {
                    arr[vpy+1][vpx] = 'D';
                    arr[vpy][vpx] = '#';
                    //vpy++;
                } 
            }
        }
    }
    else if (abs(dx) == abs(dy)) //Diagonal
    {
        if (dx == 0)
        {

        }
    }

    


}
//move_vader END