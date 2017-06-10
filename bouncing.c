#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	float sizeX, sizeY, sizeZ, tStep, g, currT,pRedius;
	float pDetails[2500][8];//3positions, Y velocity, intiVel, initDisp, e 
	int fnum,i,j,k,pCount, frameRate,lSteps, tDuration, setX, setZ;
	char fname[50];
	
	//physical constants
	g=9.8; // gravitational accelaration
	currT=0.0;// start time
	pRedius=0.1;//particle radius change this according to OVITO SW
	
	frameRate=30;
	tStep=1/(float)frameRate; //frame rate and subframes
	tDuration= 15; // simulation duration in seconds
	
	//init paticle count, file number, latice size
	fnum=1;
	pCount=2500;//particel count
	sizeX=60;
	sizeY=10;
	sizeZ=60;
	
	//initialize particels
	srand(time(NULL));
	setX=5.0;
	setZ=5.0;
	for (k=0;k<pCount;k++){
		pDetails[k][0]=setX;//X position
		pDetails[k][1]=8.0; //Y position
		pDetails[k][2]=setZ;//Z posiion
		pDetails[k][3]=0.0;//Y velocity
		pDetails[k][4]=0.0;//initVel
		pDetails[k][5]=8.0;//initDisp
		pDetails[k][6]=0.3+0.6*rand()/(float)RAND_MAX;//e
		pDetails[k][7]=0.0;
		if(setX==54){
			setZ=setZ+1;
			setX=5.0;
			}
		else{
			setX=setX+1;
			}
		}
	
	
	
	//loop iteration count
	lSteps=tDuration*frameRate;
	
	
	for (i=0;i<lSteps;i++){
	// file output open
	sprintf(fname, ".//Files/gTest_%04d.xyz", fnum);
	printf("%s\n",fname);
	FILE *fPointer;
	fPointer=fopen(fname, "w");
	//particle count
	fprintf(fPointer,"%d\n",pCount);
	//Latice size
	fprintf(fPointer,"Lattice=\" ");
	fprintf(fPointer,"%f  0.0  0.0 ",sizeX);
	fprintf(fPointer,"0.0  %f  0.0 ",sizeY);
	fprintf(fPointer,"0.0  0.0  %f",sizeZ);
	fprintf(fPointer,"\" Properties=pos:R:3\n");
	
	//currT=currT+tStep;
	
	for (j=0;j<pCount;j++){
		//position values
		fprintf(fPointer,"%f %f %f\n", pDetails[j][0] ,pDetails[j][1],pDetails[j][2] );
	
		
		//update values- particel positions
	
		// movment in +Y direction
		//incement time
		pDetails[j][7]=pDetails[j][7]+tStep;
		//Calculate the velocity
		pDetails[j][3]=pDetails[j][4]+(-1)*g*pDetails[j][7];
	
		//calculate the position
		pDetails[j][1]=pDetails[j][5]+(pDetails[j][4]*pDetails[j][7]+0.5*-1*g*(pDetails[j][7]*pDetails[j][7]));
		//check for ground contact
		if (pDetails[j][1]<=pRedius){
			pDetails[j][4]=-1*pDetails[j][6]*pDetails[j][3];
			pDetails[j][7]=0.0;
			pDetails[j][5]=pRedius;
			pDetails[j][1]=pDetails[j][5];
			}
		}
	
	//close tha file
	fclose(fPointer);
	
	//file number increment
	fnum=fnum+1;
	
	
		
	}		
	
	return 0;
	
}