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

//Programmer created Functions

//void Board(char **arr, int n, int m);
char **Ship(int n, int m); //Allocates the memory needed for the game
void Menu(void); //Prints the main menu
void Boarding(int d, char **arr, int n, int m); //Spawns the enemies and obstacles "The stormtroopers board the ship with their 'supplies' (obstacles)"
void MCS(char **arr, int n, int m); //Spawns the main characters like the player (Leia), Darth Vader and R2D2
void PrintBoard(char **arr, int n, int m); //Prints the "Game Board"
void move_leia(char **arr, char moves[3], int n, int m);


//main START
int main(void)
{
    srand(time(NULL));

    int N, M, diff,i,j,k;
    char **Tantive_IV,mov[3];

    printf("Salutations, Princess Leia...\nPlease input the starting size ( N x M ) of your ship:\n");
    scanf("%d%d",&N,&M);
    printf("\nPerfect!\nNow please input the challenge you would like to face:\n");
    printf("\n\t1. Easy\n\n\t2. Medium\n\n\t3. Hard\n\n\t4. Impossible\n");
    scanf("%d",&diff);
    //printf("\nSo you chose %d x %d size and difficulty %d\n",N,M,diff);

    Tantive_IV = Ship(N,M);

    //Board(Tantive_IV,N,M);

    Boarding(diff,Tantive_IV,N,M);

    //printf("\n\n\n\n");

    //Board(Tantive_IV,N,M);

    //printf("\n\n\n\n");

    MCS(Tantive_IV,N,M);
    
    

    for (k = 0 ; k < 100 ; k++)
    {
        PrintBoard(Tantive_IV,N,M);
        fgets(mov,sizeof(mov),stdin);
        move_leia(Tantive_IV,mov,N,M);
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

    if( arr == NULL ) //Checks if malloc returned NULL
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

        printf("\n\n");

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

/*void Board(char **arr, int n, int m)
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
            printf(" %c",arr[i][j]);
        }
        printf("\n");
    }
    return;
}
*/

//move Leia
void move_leia(char **arr, char moves[3], int n, int m)
{
    int i, j, lp1, lp2, life = 1;  
    
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
    
    for (i = 0 ; i < 1 ; i++)
    {
        if ((strncmp(moves+i,"L",1) == 0) || (strncmp(moves+i,"l",1) == 0))
        {
            if ((lp2 > 0) && (arr[lp1][lp2-1] != 'X'))
            {
                if(arr[lp1][lp2-1] == 'R')
                {
                    printf("You won!\n");
                    arr[lp1][lp2-1] = 'L';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    exit(1);
                }
                else if(arr[lp1][lp2-1] == 'D')
                {
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\n");
                    arr[lp1][lp2-1] = 'D';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    exit(1);
                }
                else if (arr[lp1][lp2-1] == '@')
                {
                    if (life == 1)
                    {
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n");
                        life--;
                        arr[lp1][lp2-1] = 'L';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                    }
                    else  //There is a bug here which doesn't make you lose when you encounter a 2nd stormtrooper 
                    {
                        printf("Oh no... A stormtrooper managed to capture you!\nYou lose!\n");
                        arr[lp1][lp2-1] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1][lp2-1] = 'L';
                    arr[lp1][lp2] = '#';
                }
            }
            else
            {
                printf("This move  is not possible.\n");
            }
        }
        else if ((strncmp(moves+i,"R",1) == 0) || (strncmp(moves+i,"r",1) == 0))
        {
            if ((lp2 < n + 1) && (arr[lp1][lp2+1] != 'X'))
            {
                if(arr[lp1][lp2+1] == 'R')
                {
                    printf("You won!\n");
                    arr[lp1][lp2+1] = 'L';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    exit(1);
                }
                else if(arr[lp1][lp2+1] == 'D')
                {
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\n");
                    arr[lp1][lp2+1] = 'D';
                    arr[lp1][lp2] = '#';
                    PrintBoard(arr,n,m);
                    exit(1);
                }
                else if (arr[lp1][lp2+1] == '@')
                {
                    if (life == 1)
                    {
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n");
                        life--;
                        arr[lp1][lp2+1] = 'L';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                    }
                    else  //There is a bug here which doesn't make you lose when you encounter a 2nd stormtrooper
                    {
                        printf("Oh no... A stormtrooper managed to capture you!\nYou lose!\n");
                        arr[lp1][lp2+1] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1][lp2+1] = 'L';
                    arr[lp1][lp2] = '#';
                }
            }   
        }
        else if ((strncmp(moves+i,"U",1) == 0) || (strncmp(moves+i,"u",1) == 0))
        {
            if ((lp1 > 0) && (arr[lp1-1][lp2] != 'X'))
            {
                if (arr[lp1-1][lp2] == 'R')
                {
                    printf("You won!\n");
                    arr[lp1-1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                    exit(1);
                }
                else if (arr[lp1-1][lp2] == 'D')
                {
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\n");
                    arr[lp1-1][lp2] = 'D';
                    arr[lp1][lp2] = '#';
                    exit(1);
                }
                else if (arr[lp1-1][lp2] == '@')
                {
                    if (life == 1)
                    {
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n");
                        life--;
                        arr[lp1-1][lp2] = 'L';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                    }
                    else  //There is a bug here which doesn't make you lose when you encounter a 2nd stormtrooper
                    {
                        printf("Oh no... A stormtrooper managed to capture you!\nYou lose!\n");
                        arr[lp1-1][lp2] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1-1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                }
            }
              
        }
        else if ((strncmp(moves+i,"D",1) == 0) || (strncmp(moves+i,"d",1) == 0))
        {
            if (lp1 < m - 1 && arr[lp1+1][lp2] != 'X')
            {
                if (arr[lp1+1][lp2] == 'R')
                {
                    printf("You won!\n");
                    arr[lp1+1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                    exit(1);
                }
                else if(arr[lp1+1][lp2] == 'D')
                {
                    printf("Oh no.. Darth Vader got you!\nYou Lost the plans and the rebellion trembles before the might of Vader!\n");
                    arr[lp1+1][lp2] = 'D';
                    arr[lp1][lp2] = '#';
                    exit(1);
                }
                else if (arr[lp1][lp2-1] == '@')
                {
                    if (life == 1)
                    {
                        printf("Oh no! You stumbled upon a stormtrooper but fortunately you managed to knock him down.\n Get to R2D2 before they improve their aim!\n");
                        life--;
                        arr[lp1+1][lp2] = 'L';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                    }
                    else  //There is a bug here which doesn't make you lose when you encounter a 2nd stormtrooper
                    {
                        printf("Oh no... A stormtrooper managed to capture you!\nYou lose!\n");
                        arr[lp1+1][lp2] = '@';
                        arr[lp1][lp2] = '#';
                        PrintBoard(arr,n,m);
                        exit(1);
                    }
                }
                else
                {
                    arr[lp1+1][lp2] = 'L';
                    arr[lp1][lp2] = '#';
                }
            }
        }    
    }
}

