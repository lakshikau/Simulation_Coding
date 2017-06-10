#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(){
	float pData[1000][16]; //3positions,vel,accel,mass,preVel
	float forcePoint[4];// 3 position, force magnitude
	float tStep, force, sizeX, sizeY, sizeZ, radius, rInXZ, accelComp;
	int fnum,i,j,k,pCount, fRate, tDuration, lSteps ;
	char fname[50];	
		
	//set up constats
	srand(time(NULL));
	fRate=30;//frame rate
	tStep=1.0/(float)fRate;//time step duration
	tDuration=20;//simulaton duraion in seconds
	
	//set the lattice
	sizeX=20;
	sizeY=20;
	sizeZ=20;
	
	//set the attraction force
	forcePoint[0]=10.0;
	forcePoint[1]=10.0;
	forcePoint[2]=10.0;
	forcePoint[3]=1;
	
	pCount=1000;// particel count
	lSteps=fRate*tDuration;//loop iteration
	fnum=1;// starting file number
	
	//initialze pData
	
	for (j=0;j<pCount;j++){
	pData[j][0]=5.0+10.0*rand()/(float)RAND_MAX;//X coord
	pData[j][1]=5.0+10.0*rand()/(float)RAND_MAX;//Y coord
	pData[j][2]=5.0+10.0*rand()/(float)RAND_MAX;//Z coord
	pData[j][3]=0.0;//Vel-not used
	pData[j][4]=0.0;//accel
	pData[j][5]=1.0+4.0*rand()/(float)RAND_MAX;;//mass 
		
	//position and angle calculation
	rInXZ=sqrt(pow((forcePoint[0]-pData[j][0]),2)+pow((forcePoint[2]-pData[j][2]),2));//get the radius projection on XZ plane
	radius=sqrt(pow((forcePoint[0]-pData[j][0]),2)+pow((forcePoint[1]-pData[j][1]),2)+pow((forcePoint[2]-pData[j][2]),2));//get the radius
	
	pData[j][6]=fabs((forcePoint[1]-pData[j][1])/radius); // sin between radius and radius projection on XZ plane	- angComp1-sin
	pData[j][7]=fabs(rInXZ/radius);//angComp2-cos
	pData[j][8]=fabs((forcePoint[0]-pData[j][0])/rInXZ);//angComp3-cos
	pData[j][9]=fabs((forcePoint[2]-pData[j][2])/rInXZ);//angComp4-cos
	
	pData[j][10]=0.0;//velX
	pData[j][11]=0.0;//velY
	pData[j][12]=0.0;//velZ
	
	pData[j][13]=0.0;//accelX
	pData[j][14]=0.0;//accelY
	pData[j][15]=0.0;//accelZ
	}
	
	for (i=0;i<lSteps;i++){
	// file output open
	printf("fileNUmber %d\n",fnum);
	sprintf(fname, ".//Files/pDance_%04d.xyz", fnum);
	//printf("%s\n",fname);
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
	
	for(k=0;k<pCount;k++){
		//print the coordinates
		fprintf(fPointer,"%f %f %f\n", pData[k][0] ,pData[k][1],pData[k][2] );
		//update particel values
	
		//calculate distance from center
		radius=sqrt(pow((forcePoint[0]-pData[k][0]),2)+pow((forcePoint[1]-pData[k][1]),2)+pow((forcePoint[2]-pData[k][2]),2));
	
		//calculate force
		force=forcePoint[3];
		
		//cal accelatration
		pData[k][4]=force/pData[k][5];
		
		//calculate accleration components
		// Y accelaration
		if (forcePoint[1]<pData[k][1])
			{pData[k][14]=-1*(pData[k][6])*pData[k][4];}
		else
			{pData[k][14]=(pData[k][6])*pData[k][4];}
		
		//accelaration component on XZ plane	
		accelComp=pData[k][4]*pData[k][7];
		
		//X accelaration
		if (forcePoint[0]<pData[k][0])
			{pData[k][13]=-1*pData[k][4]*pData[k][8];}
		else
			{pData[k][13]=pData[k][4]*pData[k][8];}
			
		//Z accelaration
		if (forcePoint[2]<pData[k][2])
			{pData[k][15]=-1*pData[k][4]*pData[k][9];}
		else
			{pData[k][15]=pData[k][4]*pData[k][9];}
		
		//calculate x coord and x vel
		pData[k][0]=pData[k][0]+pData[k][10]*tStep+0.5*pData[k][13]*tStep*tStep;
		pData[k][10]=pData[k][10]+pData[k][13]*tStep;			
	
		//calculate y coord and y vel
		pData[k][1]=pData[k][1]+pData[k][11]*tStep+0.5*pData[k][14]*tStep*tStep;
		pData[k][11]=pData[k][11]+pData[k][14]*tStep;
	
		//calculate z coord and z vel
		pData[k][2]=pData[k][2]+pData[k][12]*tStep+0.5*pData[k][15]*tStep*tStep;
		pData[k][12]=pData[k][12]+pData[k][15]*tStep;
	
		}
	
	//close tha file
	fclose(fPointer);
	
	//file number increment
	fnum=fnum+1;
	}
	
	
	return 0;
}
