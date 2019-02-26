#include "do_not_submit.h"
#include <pthread.h>
#include <semaphore.h>


pthread_cond_t      condA  = PTHREAD_COND_INITIALIZER;
pthread_cond_t      condB  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct cord
{
   int x;
   int y;
   int tired;
   bool sleep;
}cord;

sem_t semarray[GRIDSIZE][GRIDSIZE];
sem_t semnaber;
cord *cords;

int bitti = 0;

bool inGrid(int x, int y){
	if(x >= GRIDSIZE || y >= GRIDSIZE || x < 0 || y < 0) return false;
	return true;
}

bool isFull(int x, int y){
	if(inGrid(x-1, y-1) && lookCharAt(x-1,y-1)=='-') return false;
	if(inGrid(x-1, y) && lookCharAt(x-1,y)=='-') return false;
	if(inGrid(x-1, y+1) && lookCharAt(x-1,y+1)=='-') return false;
	if(inGrid(x, y-1) && lookCharAt(x,y-1)=='-') return false;
	if(inGrid(x, y+1) && lookCharAt(x,y+1)=='-') return false;
	if(inGrid(x+1, y-1) && lookCharAt(x+1,y-1)=='-') return false;
	if(inGrid(x+1, y) && lookCharAt(x+1,y)=='-') return false;
	if(inGrid(x+1, y+1) && lookCharAt(x+1,y+1)=='-') return false;
	return true;
}

bool isFood(int x, int y){
	if(inGrid(x-1, y-1) && lookCharAt(x-1,y-1)=='o') return true;
	if(inGrid(x-1, y) && lookCharAt(x-1,y)=='o') return true;
	if(inGrid(x-1, y+1) && lookCharAt(x-1,y+1)=='o') return true;
	if(inGrid(x, y-1) && lookCharAt(x,y-1)=='o') return true;
	if(inGrid(x, y+1) && lookCharAt(x,y+1)=='o') return true;
	if(inGrid(x+1, y-1) && lookCharAt(x+1,y-1)=='o') return true;
	if(inGrid(x+1, y) && lookCharAt(x+1,y)=='o') return true;
	if(inGrid(x+1, y+1) && lookCharAt(x+1,y+1)=='o') return true;
	return false;
}

void newEmpty(cord* cordinat){
	//printf("chasdfhasdhfasdhfashdfahsdfhasdfhoord x: %d, y: %d\n", cordinat->x, cordinat->y);
	//sleep(1);
	////printf("\n");
	int rastgele;
	while(1){
		rastgele = rand() % 8;
		//printf("rastgele: %d\n", rastgele);
		//sleep(1);
		//printf("abiiii1: %d\n", rastgele==0);
		//printf("abiiii2: %d\n", inGrid((cordinat->x)-1, (cordinat->y)-1));
		//printf("abiiii3: %d\n", lookCharAt((cordinat->x)-1, (cordinat->y)-1)=='-');
		if(lookCharAt(cordinat->x, cordinat->y)=='1'){
			if(rastgele==0 && inGrid(cordinat->x-1, cordinat->y-1) && lookCharAt(cordinat->x-1, cordinat->y-1)=='-'){
				//printf("a1\n" );
				//sleep(5);
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x-1, cordinat->y-1, '1');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==1 && inGrid(cordinat->x-1, cordinat->y) && lookCharAt(cordinat->x-1, cordinat->y)=='-'){
				//printf("a2\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x-1,cordinat->y,'1');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y;break;
			}
			else if(rastgele==2 && inGrid(cordinat->x-1, cordinat->y+1) && lookCharAt(cordinat->x-1, cordinat->y+1)=='-'){
				//printf("a3\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x-1,cordinat->y+1,'1');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y+1;break;
			}
			else if(rastgele==3 && inGrid(cordinat->x, cordinat->y-1) && lookCharAt(cordinat->x, cordinat->y-1)=='-'){
				//printf("a4\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x,cordinat->y-1,'1');
				cordinat->x=cordinat->x;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==4 && inGrid(cordinat->x, cordinat->y+1) && lookCharAt(cordinat->x, cordinat->y+1)=='-'){
				//printf("a5\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x,cordinat->y+1,'1');
				cordinat->x=cordinat->x;
				cordinat->y=cordinat->y+1;break;
			}
			else if(rastgele==5 && inGrid(cordinat->x+1, cordinat->y-1) && lookCharAt(cordinat->x+1, cordinat->y-1)=='-'){
				//printf("a6\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x+1,cordinat->y-1,'1');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==6 && inGrid(cordinat->x+1, cordinat->y) && lookCharAt(cordinat->x+1, cordinat->y)=='-'){
				//printf("a7\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x+1,cordinat->y,'1');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y;break;
			}
			else if(rastgele==7 && inGrid(cordinat->x+1, cordinat->y+1) && lookCharAt(cordinat->x+1, cordinat->y+1)=='-'){
				//printf("a8\n" );
				cordinat->tired = 0;
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x+1,cordinat->y+1,'1');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y+1;break;
			}
			else{
				//printf("56565\n");
				//sleep(1);
				break;
			}
		}
		else if(lookCharAt(cordinat->x, cordinat->y)=='P' && cordinat->tired == 0){
			if(rastgele==0 && inGrid(cordinat->x-1, cordinat->y-1) && lookCharAt(cordinat->x-1, cordinat->y-1)=='-'){
				//printf("a1\n" );
				//sleep(5);
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x-1, cordinat->y-1, 'P');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==1 && inGrid(cordinat->x-1, cordinat->y) && lookCharAt(cordinat->x-1, cordinat->y)=='-'){
				//printf("a2\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x-1,cordinat->y,'P');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y;break;
			}
			else if(rastgele==2 && inGrid(cordinat->x-1, cordinat->y+1) && lookCharAt(cordinat->x-1, cordinat->y+1)=='-'){
				//printf("a3\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x-1,cordinat->y+1,'P');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y+1;break;
			}
			else if(rastgele==3 && inGrid(cordinat->x, cordinat->y-1) && lookCharAt(cordinat->x, cordinat->y-1)=='-'){
				//printf("a4\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x,cordinat->y-1,'P');
				cordinat->x=cordinat->x;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==4 && inGrid(cordinat->x, cordinat->y+1) && lookCharAt(cordinat->x, cordinat->y+1)=='-'){
				//printf("a5\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x,cordinat->y+1,'P');
				cordinat->x=cordinat->x;
				cordinat->y=cordinat->y+1;break;
			}
			else if(rastgele==5 && inGrid(cordinat->x+1, cordinat->y-1) && lookCharAt(cordinat->x+1, cordinat->y-1)=='-'){
				//printf("a6\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x+1,cordinat->y-1,'P');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==6 && inGrid(cordinat->x+1, cordinat->y) && lookCharAt(cordinat->x+1, cordinat->y)=='-'){
				//printf("a7\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x+1,cordinat->y,'P');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y;break;
			}
			else if(rastgele==7 && inGrid(cordinat->x+1, cordinat->y+1) && lookCharAt(cordinat->x+1, cordinat->y+1)=='-'){
				//printf("a8\n" );
				putCharTo(cordinat->x,cordinat->y,'-');
				putCharTo(cordinat->x+1,cordinat->y+1,'P');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y+1;break;
			}
			else{
				//printf("56565\n");
				//sleep(1);
				break;
			}
		}
		else if(lookCharAt(cordinat->x, cordinat->y)=='P' && cordinat->tired == 1){
			if(rastgele==0 && inGrid(cordinat->x-1, cordinat->y-1) && lookCharAt(cordinat->x-1, cordinat->y-1)=='-'){
				//printf("a1\n" );
				//sleep(5);
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x-1, cordinat->y-1, '1');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==1 && inGrid(cordinat->x-1, cordinat->y) && lookCharAt(cordinat->x-1, cordinat->y)=='-'){
				//printf("a2\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x-1,cordinat->y,'1');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y;break;
			}
			else if(rastgele==2 && inGrid(cordinat->x-1, cordinat->y+1) && lookCharAt(cordinat->x-1, cordinat->y+1)=='-'){
				//printf("a3\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x-1,cordinat->y+1,'1');
				cordinat->x=cordinat->x-1;
				cordinat->y=cordinat->y+1;break;
			}
			else if(rastgele==3 && inGrid(cordinat->x, cordinat->y-1) && lookCharAt(cordinat->x, cordinat->y-1)=='-'){
				//printf("a4\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x,cordinat->y-1,'1');
				cordinat->x=cordinat->x;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==4 && inGrid(cordinat->x, cordinat->y+1) && lookCharAt(cordinat->x, cordinat->y+1)=='-'){
				//printf("a5\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x,cordinat->y+1,'1');
				cordinat->x=cordinat->x;
				cordinat->y=cordinat->y+1;break;
			}
			else if(rastgele==5 && inGrid(cordinat->x+1, cordinat->y-1) && lookCharAt(cordinat->x+1, cordinat->y-1)=='-'){
				//printf("a6\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x+1,cordinat->y-1,'1');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y-1;break;
			}
			else if(rastgele==6 && inGrid(cordinat->x+1, cordinat->y) && lookCharAt(cordinat->x+1, cordinat->y)=='-'){
				//printf("a7\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x+1,cordinat->y,'1');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y;break;
			}
			else if(rastgele==7 && inGrid(cordinat->x+1, cordinat->y+1) && lookCharAt(cordinat->x+1, cordinat->y+1)=='-'){
				//printf("a8\n" );
				putCharTo(cordinat->x,cordinat->y,'o');
				putCharTo(cordinat->x+1,cordinat->y+1,'1');
				cordinat->x=cordinat->x+1;
				cordinat->y=cordinat->y+1;break;
			}
			else{
				//printf("56565\n");
				//sleep(1);
				break;
			}
		}
	}
}

void newEmptyTired(cord* cordinat){
	int tempx,tempy;
	int rastgele;
	while(1){
		if(bitti) break;
		rastgele = rand() % 8;
		if(rastgele==0 && inGrid(cordinat->x-1, cordinat->y-1) && lookCharAt(cordinat->x-1, cordinat->y-1)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==1 && inGrid(cordinat->x-1, cordinat->y) && lookCharAt(cordinat->x-1, cordinat->y)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==2 && inGrid(cordinat->x-1, cordinat->y+1) && lookCharAt(cordinat->x-1, cordinat->y+1)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==3 && inGrid(cordinat->x, cordinat->y-1) && lookCharAt(cordinat->x, cordinat->y-1)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==4 && inGrid(cordinat->x, cordinat->y+1) && lookCharAt(cordinat->x, cordinat->y+1)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==5 && inGrid(cordinat->x+1, cordinat->y-1) && lookCharAt(cordinat->x+1, cordinat->y-1)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==6 && inGrid(cordinat->x+1, cordinat->y) && lookCharAt(cordinat->x+1, cordinat->y)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else if(rastgele==7 && inGrid(cordinat->x+1, cordinat->y+1) && lookCharAt(cordinat->x+1, cordinat->y+1)=='o'){
			cordinat->tired = 1;
			newEmpty(cordinat);
			break;
		}
		else
			{}
	}
}

void *myThreadFun(cord *cordinat){
		int tempx,tempy;
		while(1){
			
			if(bitti) break;	
			if(cordinat->sleep){
				if(lookCharAt(cordinat->x, cordinat->y)=='1'){
					putCharTo(cordinat->x, cordinat->y, 'S');
				}
				else if(lookCharAt(cordinat->x, cordinat->y)=='P'){
					putCharTo(cordinat->x, cordinat->y, '$'); 
				}
				continue;
			}
			if(lookCharAt(cordinat->x, cordinat->y)=='S'){
				putCharTo(cordinat->x, cordinat->y, '1');
			}
			if(lookCharAt(cordinat->x, cordinat->y)=='$'){
				putCharTo(cordinat->x, cordinat->y, 'P');
			}

			usleep(getDelay() * 1000);



			tempx=cordinat->x;
			tempy=cordinat->y;
			sem_wait(&semnaber);

			if(inGrid(tempx-1, tempy-1)) sem_wait(&semarray[tempx-1][tempy-1]);
			if(inGrid(tempx-1, tempy)) sem_wait(&semarray[tempx-1][tempy]);
			if(inGrid(tempx-1, tempy+1)) sem_wait(&semarray[tempx-1][tempy+1]);
			if(inGrid(tempx, tempy-1)) sem_wait(&semarray[tempx][tempy-1]);
			if(inGrid(tempx, tempy+1)) sem_wait(&semarray[tempx][tempy+1]);
			if(inGrid(tempx+1, tempy-1)) sem_wait(&semarray[tempx+1][tempy-1]);
			if(inGrid(tempx+1, tempy)) sem_wait(&semarray[tempx+1][tempy]);
			if(inGrid(tempx+1, tempy+1)) sem_wait(&semarray[tempx+1][tempy+1]);


			// if(inGrid(tempx-1, tempy-1) && sem_trywait(&semarray[tempx-1][tempy-1])==-1){
			// 	continue;
			// }
			// else if(inGrid(tempx-1, tempy-1) && sem_trywait(&semarray[tempx-1][tempy-1])!=-1)  
			// 	sem_trywait(&semarray[tempx-1][tempy-1]);
				

			
			// if(inGrid(tempx-1, tempy) && sem_trywait(&semarray[tempx-1][tempy])==-1) {
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	continue;
			// }
			// else if(inGrid(tempx-1, tempy) && sem_trywait(&semarray[tempx-1][tempy])!=-1)  
			// 	sem_trywait(&semarray[tempx-1][tempy]);	
			
			
			// if(inGrid(tempx-1, tempy+1) && sem_trywait(&semarray[tempx-1][tempy+1])==-1) {
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	sem_post(&semarray[tempx-1][tempy]);
			// 	continue;
			// }
			// else if(inGrid(tempx-1, tempy+1) && sem_trywait(&semarray[tempx-1][tempy+1])!=-1)  
			// 	sem_trywait(&semarray[tempx-1][tempy+1]);	


			// if(inGrid(tempx, tempy-1) && sem_trywait(&semarray[tempx][tempy-1])==-1) {
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	sem_post(&semarray[tempx-1][tempy]);
			// 	sem_post(&semarray[tempx-1][tempy+1]);
			// 	continue;
			// }
			// else if(inGrid(tempx, tempy-1) && sem_trywait(&semarray[tempx][tempy-1])!=-1)  
			// 	sem_trywait(&semarray[tempx][tempy-1]);


			// if(inGrid(tempx, tempy+1) && sem_trywait(&semarray[tempx][tempy+1])==-1){
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	sem_post(&semarray[tempx-1][tempy]);
			// 	sem_post(&semarray[tempx-1][tempy+1]);				
			// 	sem_post(&semarray[tempx][tempy-1]);
			// 	continue;
			// }
			// else if(inGrid(tempx, tempy+1) && sem_trywait(&semarray[tempx][tempy+1])!=-1)  
			// 	sem_trywait(&semarray[tempx][tempy+1]);


			// if(inGrid(tempx+1, tempy-1) && sem_trywait(&semarray[tempx+1][tempy-1])==-1) {
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	sem_post(&semarray[tempx-1][tempy]);
			// 	sem_post(&semarray[tempx-1][tempy+1]);				
			// 	sem_post(&semarray[tempx][tempy-1]);
			// 	sem_post(&semarray[tempx][tempy+1]);
			// 	continue;
			// }
			// else if(inGrid(tempx+1, tempy-1) && sem_trywait(&semarray[tempx+1][tempy-1])!=-1)  
			// 	sem_trywait(&semarray[tempx+1][tempy-1]);



			// if(inGrid(tempx+1, tempy) && sem_trywait(&semarray[tempx+1][tempy])==-1) {	
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	sem_post(&semarray[tempx-1][tempy]);
			// 	sem_post(&semarray[tempx-1][tempy+1]);				
			// 	sem_post(&semarray[tempx][tempy-1]);
			// 	sem_post(&semarray[tempx][tempy+1]);				
			// 	sem_post(&semarray[tempx+1][tempy-1]);
			// 	continue;
			// }
			// else if(inGrid(tempx+1, tempy) && sem_trywait(&semarray[tempx+1][tempy])!=-1)  
			// 	sem_trywait(&semarray[tempx+1][tempy]);


			// if(inGrid(tempx+1, tempy+1) && sem_trywait(&semarray[tempx+1][tempy+1])==-1) {
			// 	sem_post(&semarray[tempx-1][tempy-1]);
			// 	sem_post(&semarray[tempx-1][tempy]);
			// 	sem_post(&semarray[tempx-1][tempy+1]);				
			// 	sem_post(&semarray[tempx][tempy-1]);
			// 	sem_post(&semarray[tempx][tempy+1]);				
			// 	sem_post(&semarray[tempx+1][tempy-1]);				
			// 	sem_post(&semarray[tempx+1][tempy]);
			// 	continue;
			// }
			// else if(inGrid(tempx+1, tempy+1) && sem_trywait(&semarray[tempx+1][tempy+1])!=-1)  
			// 	sem_trywait(&semarray[tempx+1][tempy+1]);	

			sem_post(&semnaber);
			
			char m=lookCharAt(cordinat->x, cordinat->y);
			if(m=='1' && cordinat->tired == 0){
				if(isFull( (cordinat->x), (cordinat->y)) ){
					if(inGrid(tempx-1, tempy-1)) sem_post(&semarray[tempx-1][tempy-1]);
					if(inGrid(tempx-1, tempy)) sem_post(&semarray[tempx-1][tempy]);
					if(inGrid(tempx-1, tempy+1)) sem_post(&semarray[tempx-1][tempy+1]);
					if(inGrid(tempx, tempy-1)) sem_post(&semarray[tempx][tempy-1]);
					if(inGrid(tempx, tempy+1)) sem_post(&semarray[tempx][tempy+1]);
					if(inGrid(tempx+1, tempy-1)) sem_post(&semarray[tempx+1][tempy-1]);
					if(inGrid(tempx+1, tempy)) sem_post(&semarray[tempx+1][tempy]);
					if(inGrid(tempx+1, tempy+1)) sem_post(&semarray[tempx+1][tempy+1]);
					continue;
				}

				if(inGrid(cordinat->x-1, cordinat->y-1) && lookCharAt(cordinat->x-1, cordinat->y-1)=='o'){
					//printf("99999\n");
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo((cordinat->x)-1, (cordinat->y)-1, 'P');
					//sleep(1);
					cordinat->x=cordinat->x-1;
					cordinat->y=cordinat->y-1;
				} 
				else if(inGrid(cordinat->x-1, cordinat->y) && lookCharAt(cordinat->x-1, cordinat->y)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x-1, cordinat->y, 'P');
					cordinat->x=cordinat->x-1;
					cordinat->y=cordinat->y;
				}
				else if(inGrid(cordinat->x-1, cordinat->y+1) && lookCharAt(cordinat->x-1, cordinat->y+1)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x-1, cordinat->y+1, 'P');
					cordinat->x=cordinat->x-1;
					cordinat->y=cordinat->y+1;
				}
				else if(inGrid(cordinat->x, cordinat->y-1) && lookCharAt(cordinat->x, cordinat->y-1)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x, cordinat->y-1, 'P');
					cordinat->x=cordinat->x;
					cordinat->y=cordinat->y-1;
				}
				else if(inGrid(cordinat->x, cordinat->y+1) && lookCharAt(cordinat->x, cordinat->y+1)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x, cordinat->y+1, 'P');
					cordinat->x=cordinat->x;
					cordinat->y=cordinat->y+1;
				}
				else if(inGrid(cordinat->x+1, cordinat->y-1) && lookCharAt(cordinat->x+1, cordinat->y-1)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x+1, cordinat->y-1, 'P');
					cordinat->x=cordinat->x+1;
					cordinat->y=cordinat->y-1;
				}
				else if(inGrid(cordinat->x+1, cordinat->y) && lookCharAt(cordinat->x+1, cordinat->y)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x+1, cordinat->y, 'P');
					cordinat->x=cordinat->x+1;
					cordinat->y=cordinat->y;
				}
				else if(inGrid(cordinat->x+1, cordinat->y+1) && lookCharAt(cordinat->x+1, cordinat->y+1)=='o'){
					putCharTo(cordinat->x, cordinat->y, '-');
					putCharTo(cordinat->x+1, cordinat->y+1, 'P');
					cordinat->x=cordinat->x+1;
					cordinat->y=cordinat->y+1;
				}
				// else if( (lookCharAt(cordinat->x-1, cordinat->y-1)=='1' || lookCharAt(cordinat->x-1, cordinat->y-1)=='P') && (lookCharAt(cordinat->x-1, cordinat->y)=='1' || lookCharAt(cordinat->x-1, cordinat->y)=='P') &&
				// 	 (lookCharAt(cordinat->x-1, cordinat->y+1)=='1' || lookCharAt(cordinat->x-1, cordinat->y+1)=='P') && (lookCharAt(cordinat->x, cordinat->y-1)=='1' || lookCharAt(cordinat->x, cordinat->y-1)=='P') &&
				// 	  (lookCharAt(cordinat->x, cordinat->y+1)=='1' || lookCharAt(cordinat->x, cordinat->y+1)=='P') && (lookCharAt(cordinat->x+1, cordinat->y-1)=='1' || lookCharAt(cordinat->x+1, cordinat->y-1)=='P') &&
				// 	   (lookCharAt(cordinat->x+1, cordinat->y)=='1' || lookCharAt(cordinat->x+1, cordinat->y)=='P') && (lookCharAt(cordinat->x+1, cordinat->y+1)=='1' || lookCharAt(cordinat->x+1, cordinat->y+1)=='P') ){
				// 		//printf("asdfadsasdg\n");
				// 		if(inGrid(tempx-1, tempy-1)) sem_post(&semarray[tempx-1][tempy-1]);
				// 		if(inGrid(tempx-1, tempy)) sem_post(&semarray[tempx-1][tempy]);
				// 		if(inGrid(tempx-1, tempy+1)) sem_post(&semarray[tempx-1][tempy+1]);
				// 		if(inGrid(tempx, tempy-1)) sem_post(&semarray[tempx][tempy-1]);
				// 		if(inGrid(tempx, tempy+1)) sem_post(&semarray[tempx][tempy+1]);
				// 		if(inGrid(tempx+1, tempy-1)) sem_post(&semarray[tempx+1][tempy-1]);
				// 		if(inGrid(tempx+1, tempy)) sem_post(&semarray[tempx+1][tempy]);
				// 		if(inGrid(tempx+1, tempy+1)) sem_post(&semarray[tempx+1][tempy+1]);
				// 		continue;
				// }
				else	newEmpty(cordinat);

			}
			else if(m=='1' && cordinat->tired == 1){
				newEmpty(cordinat);
			}


			else if(m=='P'){
				//printf("22\n");
				if(isFood(cordinat->x, cordinat->y)){
					newEmptyTired(cordinat);
				}
				else newEmpty(cordinat);
			}
			else if(m=='S'){
				//printf("33\n");
				newEmpty(cordinat);	
			}
			else{
				
				//printf("hassss\n");
			}
			if(inGrid(tempx-1, tempy-1)) sem_post(&semarray[tempx-1][tempy-1]);
			if(inGrid(tempx-1, tempy)) sem_post(&semarray[tempx-1][tempy]);
			if(inGrid(tempx-1, tempy+1)) sem_post(&semarray[tempx-1][tempy+1]);
			if(inGrid(tempx, tempy-1)) sem_post(&semarray[tempx][tempy-1]);
			if(inGrid(tempx, tempy+1)) sem_post(&semarray[tempx][tempy+1]);
			if(inGrid(tempx+1, tempy-1)) sem_post(&semarray[tempx+1][tempy-1]);
			if(inGrid(tempx+1, tempy)) sem_post(&semarray[tempx+1][tempy]);
			if(inGrid(tempx+1, tempy+1)) sem_post(&semarray[tempx+1][tempy+1]);
		}

		
		
	}

int main(int argc, char *argv[]) {
	int t;
    t = atoi(argv[3]);
    srand(time(NULL));
    pthread_t thread[atoi(argv[1])];
    sem_init(&semnaber,0,1);
    int i,j;
    for (i = 0; i < GRIDSIZE; i++) {
        for (j = 0; j < GRIDSIZE; j++) {
            sem_init(&semarray[i][j],0,1);
        }
    }

    time_t start, end;
    //////////////////////////////
    // Fills the grid randomly to have somthing to draw on screen.
    // Empty spaces have to be -.
    // You should get the number of ants and foods from the arguments 
    // and make sure that a food and an ant does not placed at the same cell.
    // You must use putCharTo() and lookCharAt() to access/change the grid.
    // You should be delegating ants to separate threads
    cords = (cord *) malloc(sizeof(cord)*atoi(argv[1]));
    for (i = 0; i < GRIDSIZE; i++) {
        for (j = 0; j < GRIDSIZE; j++) {
            putCharTo(i, j, '-');
        }
    }
    int a,b;

    for (i = 0; i < atoi(argv[2]); i++) {
        do {
            a = rand() % GRIDSIZE;
            b = rand() % GRIDSIZE;
        }while (lookCharAt(a,b) != '-');
        putCharTo(a, b, 'o');
    }
    for (i = 0; i < atoi(argv[1]); i++) {
        do {
            a = rand() % GRIDSIZE;
            b = rand() % GRIDSIZE;
        }while (lookCharAt(a,b) != '-');
        putCharTo(a, b, '1');
        cords[i].x=a;
        cords[i].y=b;
        cords[i].tired = 0;
        cords[i].sleep = false;
        pthread_create(&(thread[i]), NULL, myThreadFun, &cords[i]);
    }


    // you have to have following command to initialize ncurses.
    startCurses();

    // You can use following loop in your program. But pay attention to 
    // the function calls, they do not have any access control, you 
    // have to ensure that.
    start = time(NULL);

    char c;
    while (TRUE) {
        for(size_t i = 0; i < GRIDSIZE; i++)
            for(size_t j = 0; j < GRIDSIZE; j++)
                sem_wait(&semarray[i][j]);

        drawWindow();

        for(size_t i = 0; i < GRIDSIZE; i++)
            for(size_t j = 0; j < GRIDSIZE; j++)
                sem_post(&semarray[i][j]);


        c = 0;
        c = getch();

        //time_t end = time(NULL);
        end = time(NULL);
        if( end-start >= t){
        	bitti=1;
        	break;
        }
        //printf("%ld\n", ((double) (end - start) / CLOCKS_PER_SEC));
        for(i=0; i<getSleeperN(); i++){
        	cords[i].sleep=true;
        }
        for(i=getSleeperN(); i<atoi(argv[1]); i++){
        	cords[i].sleep=false;
        }

        if (c == 'q' || c == ESC) 
        	break;
        if (c == '+') {
            setDelay(getDelay()+10);
        }
        if (c == '-') {
            setDelay(getDelay()-10);
        }
        if (c == '*') {
            setSleeperN(getSleeperN()+1);
        }
        if (c == '/') {
            setSleeperN(getSleeperN()-1);
        }
        usleep(DRAWDELAY);
        // each ant thread have to sleep with code similar to this
        //usleep(getDelay() * 1000 + (rand() % 5000));
    }

    bitti = 1;
	for(int i=0; i<atoi(argv[1]); i++){    
    	pthread_join(thread[i], NULL);
	}
    
    // do not forget freeing the resources you get
    endCurses();
    
    return 0;
}
