#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50
#define MAX 4

typedef struct location{
int val;
int dead;
}location;

void bumpcheck(location map[SIZE][SIZE], int x, int y,FILE* file);
void bump(location map[SIZE][SIZE], int x, int y, FILE* file);
void print_map(location map[SIZE][SIZE],FILE* file);
void create_deadzone_line(location map[SIZE][SIZE], int num_dead);
void create_deadzone_glob(location map[SIZE][SIZE], int num_dead);
void print_coords(int x, int y, FILE* file);

int main(int argv, char* argc){
	srand(time(NULL));
	location map[SIZE][SIZE];
	int i,j,k, iter, numruns, dead_choice, num_dead;
	char c[20];
	char* filename;
	printf("Enter how many times to run\n");
	scanf("%d",&numruns);
	//printf("Deadzones? Enter a corresponding number\n0) No dead zones\n1) A singular dead neuron\n2) Line of dead neurons\n3) Glob of dead neurons\n");
	//scanf("%d",&dead_choice);
	/*switch(dead_choice){
		case(0):{
			break;
		}
		case(1):{
			break;
		}
		case(2):{
			printf("How many neurons in this line?\n");
                        scanf("%d",&num_dead);
			break;
		}
		case(3):{
			printf("How long is this 'glob'? Glob will be a straight line but also include all 4 neighbors for each neuron in the line.\n");
                        scanf("%d",&num_dead);
			break;
		}
		defult:{
			printf("Deadzone selection wrong\n");
			break;
		}
	}*/
	for(i=0;i<numruns;++i){
		//populate map with random numbers between 0 and the max potential-1.
		for(j=0;j<SIZE;++j){
                	for(k=0;k<SIZE;++k){
                        	(map[j][k]).val=rand()%MAX;
				(map[j][k]).dead=0;
                	}
		}
		/*switch(dead_choice){
                        case(0):{
                                break;
                        }
                        case(1):{
                                int a=rand()%SIZE;
                                int b=rand()%SIZE;
                                (map[a][b]).dead = 1;
                                break;
                        }
                        case(2):{
                                create_deadzone_line(map, num_dead);
                                break;
                        }
                        case(3):{
                                create_deadzone_glob(map, num_dead);
                                break;
                        }
                        default:{
                                printf("Deadzone creation failed");
                                break;
                        }
                }*/
		//create file to store run.
		sprintf(c,"%d",i);
		filename=strcat(c,".txt");
		FILE* file=fopen(filename,"w");
		//iter represents individual neuron bumps (essentially, how many neurons need to fire to do a particular action). Every time this for loop runs it will pick a randomlocation and bump it and then recursively begin checking if the neuron hit max potential and then bump neighboring neurons and continue to check and bump until all 4 neighbors of one neuron bump to less than the max potential.
		for (iter=0;iter<10000;++iter){
			int x=rand()%SIZE;
			int y=rand()%SIZE;
			bump(map,x,y,file);
			bumpcheck(map,x,y,file);
		}
	}
}

//TO DO
//create deadzone creation functions, test deadzone creation functions.
//needs to be recursive to avoid hitting deadends. When dead end is hit, needs to backtrack until it can pick a new direction again.
void create_deadzone_line(location map[SIZE][SIZE], int num_dead){
	int direction,i,j,k;
	int x=rand()%SIZE;
	int y=rand()%SIZE;
	j=x;
	k=y;
	for(i=0;i<num_dead;++i){
		printf("For Loop Start");
		if(map[x][y].dead!=1){
			map[x][y].dead=1;
		}
		while(map[j][k].dead==1){
			j=x;
			k=y;
			direction=rand()%4;
			switch(direction){
				case(0):{
					if(j!=0){
						j--;
					}
					break;
				}
				case(1):{
					if(j!=SIZE-1){
						j++;
					}
					break;
				}
				case(2):{
					if(k!=0){
						k--;
					}
					break;
				}
				case(3):{
					if(k!=SIZE-1){
						k++;
					}
					break;
				}
				default:{
					printf("Dead zone movement failed");
					break;
				}	
			}
		}
		x=j;
		y=k;
		printf(" - For Loop End\n");
	}
}

void create_deadzone_glob(location map[SIZE][SIZE], int num_dead){
	int direction,i;
        int x=rand()%SIZE;
        int y=rand()%SIZE;
        for(i=0;i<num_dead;++i){
                if(map[x][y].dead!=1){
                        map[x][y].dead=1;
                }
		if(x!=0){
			map[x-1][y].dead=1;
		}
		if(x!=SIZE-1){
                        map[x+1][y].dead=1;
                }
		if(y!=0){
                        map[x][y-1].dead=1;
                }
		if(y!=SIZE-1){
                        map[x][y-1].dead=1;
                }
                direction=rand()%4;
                switch(direction){
                        case(0):{
                                if(x!=0){
                                        x--;
                                }
                                break;
                        }
                        case(1):{
                                if(x!=SIZE-1){
                                        x++;
                                }
                                break;
                        }
                        case(2):{
                                if(y!=0){
                                        y--;
                                }
                                break;
                        }
                        case(3):{
                                if(y!=SIZE-1){
                                        y++;
                                }
                                break;
                        }
                        default:{
                                printf("Dead zone movement failed");
                                break;
                        }       
                }       
        }
}

void bumpcheck(location map[SIZE][SIZE], int x, int y,FILE* file){
	if((map[x][y]).val >= MAX){
		(map[x][y]).val = 0;
		if(x!=0){
			bump(map, x-1, y,file);
			bumpcheck(map,x-1,y,file);
		}
		if(x!=SIZE-1){
			bump(map, x+1,y,file);
			bumpcheck(map,x+1,y,file);
		}
		if(y!=0){
			bump(map,x,y-1,file);
			bumpcheck(map,x,y-1,file);
		}
		if(y!=SIZE-1){
			bump(map,x,y+1,file);
			bumpcheck(map,x,y+1,file);
		}
	}
}

void bump(location map[SIZE][SIZE], int x, int y,FILE* file){
	int bumper;
	//bumper=rand()%5+1;
	bumper=1;
	if(map[x][y].dead!=1){
		(map[x][y]).val += bumper;
	}
	//printf("Bumping\n");
	//print_map(map,file);
	print_coords(x,y,file);
	//printf("\n");
}

void print_coords(int x, int y, FILE* file){
	fprintf(file,"%d\t%d\n",x,y);
}

void print_map(location map[SIZE][SIZE],FILE* file){
	int i,j;
	char dig;
	for(i=0;i<SIZE;++i){
		for(j=0;j<SIZE;++j){
			if((map[i][j].dead)!=1){
				dig = (char)(((int)'0')+(map[i][j]).val);
				fputc(dig,file);
				fprintf(file, " ");
			}
			else{
				fputc('-',file);
				fprintf(file, " ");
			}
		}
		fprintf(file,"\n");
	}
	fprintf(file,"\n");
	
}
