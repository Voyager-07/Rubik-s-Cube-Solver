#include<stdio.h>
#include<strings.h>
#include "Cube.cpp"
#include"Algo_storing_stack.cpp"

 
void set_centre_to(char face)
{
	if(DOWN[1][1]==face){
		X(0);
		push('X',0);
	}
	else if(UP[1][1]==face){
		X(1);
		push('X',1);
	}
	else if(LEFT[1][1]==face){
		Y(0);											
		push('Y',0);
	}
	else if(RIGHT[1][1]==face){
		Y(1);
		push('Y',1);
	}
	else if(XRIGHT[1][1]==face){
		Y(1); Y(1);
		push('Y',1);
		push('Y',1);
	}
}

int compare(char *str,char key){
	int len=strlen(str);
	for(int i=0;i<len;i++) if(str[i]==key) return (i+1);
	return 0;
}
void free(char (* face)[3],int x,int y,char color){    //free the face's [x][y] postion from the color,i.e.,that color should not be present at parameter's postion
	if(face[x][y]==color)
	{
		F(0);
		if(face[x][y]!=color){
			push('F',0);  //F
			return;
		}
		F(1); F(1);
		if(face[x][y]!=color){
			push('F',1);	//F'
			return;
		}
		F(1);
		push('F',2);	//F2
	}
}

void righty_alg() {
	R(0);				U(0);				 R(1);				  U(1);
	push('R',0);	push('U',0);	push('R',1);	push('U',1);
}

void left_corner_insert() {
	printf("lci is called \n");
	U(1);  			L(1); 			U(0); 			L(0);
	push('U',1);	push('R',1);	push('U',0);	push('R',0);
}

void right_corner_insert() {
	printf("rci is called \n");
	U(0);  			R(0); 			U(1); 			R(1);
	push('U',0);	push('R',0);	push('U',1);	push('R',1);
}


void align_edge(char (* face)[3],int x,int y){    //align edge lvl1 is yellow face wale white pr solve kr rhe hain
	
	if(x==2 && y==0) {
		U(1);
		push('U',1);
	}
	else if(x==0 and y==0) { 
		U(0); U(0); 
		push('U',2);
	}
	else {
		U(0); 
		push('U',0);	
	} 

	// b(0);

	if(!(CENTRE[0][2]==RIGHT[1][1] and RIGHT[0][0]==CENTRE[1][1]))
	{
		d(0);
		//pass something else in pushback
		if(CENTRE[0][2]==RIGHT[1][1] and RIGHT[0][0]==CENTRE[1][1]) 
		{
			push('d',0);
			return;
		}
		
		d(1); d(1);
		
		if(CENTRE[0][2]==RIGHT[1][1] and RIGHT[0][0]==CENTRE[1][1]) 
		{
			push('d',1);
			return;
		}

		d(1);

		if(CENTRE[0][2]==RIGHT[1][1] and RIGHT[0][0]==CENTRE[1][1]) 
		{
			push('d',2);
			return;
		}

	}
}

void align_edge_2(char (*face)[3],int x,int y) {
	bool zero=false,zerotwo=false,cisf=false;
	
	if(x == 0 and y == 0) zero = true;
	else zerotwo = true;
	
//	if(face[1][1] == CENTRE[1][1]) 
//	{
//		
//		//lefty_algo(); lefty_algo(); lefty_algo(); lefty_algo();
//	}
//	else 
	printf("Center 0 0 is : %c\n",CENTRE[1][1]);
	printf("face 0 0 is : %c\n",face[1][1]);
	if(face[1][1] == RIGHT[1][1])
	{
		U(0); push('U',0);
		printf("1\n");
//		right_corner_push();
	}
	else if(face[1][1] == XRIGHT[1][1])
	{
		printf("2\n");
		U(0); U(0); push('U',0); push('U',0);
	}
	else if(face[1][1] == LEFT[1][1])
	{
		printf("3\n");
		U(1); push('U',1);
	}
	else cisf = true;
	display();
	
	if(zero) {  //corner white piece is at centre-top-left
			int ct = 0;
			while(LEFT[0][2] != LEFT[1][1]) {
				d(0); push('d',0);            
				U(0); U(0); 
				printf("left d d \n");
//			if(ct>5) break; 
			}
			ct++;
			printf("%d\n",cisf);
		left_corner_insert();
	}
	else if(zerotwo) {     //corner white piece is at centre-top-right
		int ct = 0;
		while(RIGHT[0][0] != RIGHT[1][1] ) 
		{
			d(0); push('d',0);              
			U(1); U(1); 
//			display();
			if(ct>5) break; 
			ct++;
			printf("right d d \n");
		}
		right_corner_insert();
	}
	display();
}

void align_edge_3() {
	
}

void  white_cross_solver()
{
	set_centre_to('Y');
	display();
	
	while(CENTRE[0][1]!='W' || CENTRE[1][0]!='W' || CENTRE[1][2]!='W' || CENTRE[2][1]!='W')
	{
		display();
		char a[]={LEFT[1][2], RIGHT[1][0], UP[2][1], DOWN[0][1]};
		if(compare(a,'W'))
		{
			switch(compare(a,'W'))
			{
				case 1:
					L(0);			F(1);			D(0);
					push('L',0); 	push('F',1);	push('D',0);
					break;
				case 2:
					R(0);			F(1);			U(0);
					push('R',0); 	push('F',1);	push('U',0);
					break;
				case 3:
					U(0);			F(1);			L(0);
					push('U',0); 	push('F',1);	push('L',0);
					break;
				case 4:
					D(0);			F(1);			R(0);
					push('D',0); 	push('F',1);	push('R',0);
					break;
			}
		}
		char b[]={XRIGHT[0][1], XRIGHT[1][0], XRIGHT[1][2], XRIGHT[2][1]};
		if(compare(b,'W'))
		{
			switch(compare(b,'W'))
			{
				case 1:
					free(CENTRE,0,1,'W');
					U(0); U(0);
					push('U',2);
					break;
				case 2:
					free(CENTRE,1,2,'W');
					R(0); R(0);
					push('R',2);
					break;
				case 3:
					free(CENTRE,1,0,'W');
					L(0); L(0);
					push('L',2);
					break;
				case 4:
					free(CENTRE,2,1,'W');
					D(0); D(0);
					push('D',2);
					break;
			}
		}
		char c[]={LEFT[0][1], RIGHT[0][1], UP[1][0], DOWN[1][0],UP[1][2], DOWN[1][2],LEFT[2][1], RIGHT[2][1]};
		if(compare(c,'W')){
			switch(compare(c,'W')){
				case 1:
					free(CENTRE,0,1,'W');
					U(1);
					push('U',1);
					break;
				case 2:
					free(CENTRE,0,1,'W');
					U(0);
					push('U',0);
					break;
				case 3:
					free(CENTRE,1,0,'W');
					L(0);
					push('L',0);
					break;
				case 4:
					free(CENTRE,1,0,'W');
					L(1);
					push('L',1);
					break;
				case 5:
					free(CENTRE,1,2,'W');
					R(1);
					push('R',1);
					break;
				case 6:
					free(CENTRE,1,2,'W');
					R(0);
					push('R',0);
					break;
				case 7:
					free(CENTRE,2,1,'W');
					D(0);
					push('D',0);
					break;
				case 8:
					free(CENTRE,2,1,'W');
					D(1);
					push('D',1);
					break;
			}
		}
		char d[]={LEFT[1][0], RIGHT[1][2], UP[0][1], DOWN[2][1]};
		if(compare(d,'W')){
			switch(compare(d,'W')){
				case 1:
					free(CENTRE,1,0,'W');
					L(0);			F(0);			U(1);
					push('L',0); 	push('F',0);	push('U',1);
					break;
				case 2:
					free(CENTRE,1,2,'W');
					R(0);			F(0);			D(1);
					push('R',0); 	push('F',0);	push('D',1);
					break;
				case 3:
					free(CENTRE,0,1,'W');
					U(0);			F(0);			R(1);
					push('U',0); 	push('F',0);	push('R',1);
					break;
				case 4:
					free(CENTRE,2,1,'W');
					D(0);			F(0);			L(1);
					push('D',0); 	push('F',0);	push('L',1);
					break;
			}
		}
	}
	display();
	
	int count=0;
	while(CENTRE[0][1]=='W' || CENTRE[1][0]=='W' || CENTRE[1][2]=='W' || CENTRE[2][1]=='W')
	{
		count++;
		if(count>10) break;
		display();
		if((UP[2][1]==UP[1][1] and CENTRE[0][1]=='W') || (RIGHT[1][0]==RIGHT[1][1] and CENTRE[1][2]=='W') || (LEFT[1][2]==LEFT[1][1] and CENTRE[1][0]=='W') || (DOWN[0][1]==DOWN[1][1] and CENTRE[2][1]=='W'))
		{
			
			if((UP[2][1]==UP[1][1] and CENTRE[0][1]=='W')) 
			{
				U(0); U(0);
				push('U',2);
			}
			if(RIGHT[1][0]==RIGHT[1][1] and CENTRE[1][2]=='W')
			{
				R(0); R(0);
				push('R',2);
			}
			if(LEFT[1][2]==LEFT[1][1] and CENTRE[1][0]=='W')
			{
				L(0); L(0);
				push('L',2);
			}
			if(DOWN[0][1]==DOWN[1][1] and CENTRE[2][1]=='W')
			{
				D(0); D(0);
				push('D',2);
			}
		}
		else{
			F(0);
			push('F',0);
			printf("1\n");
//			count++;
		}
	}
	
//	U(0); U(0);		D(0); D(0); 	R(0); R(0); 	L(0); L(0);
//	push('U',2);	push('D',2);	push('R',2);	push('L',2);
//	X(0); X(0);
//	
	printf("White Cross is Solved! \n");
//	display();
//	exit(0);
}


void white_edge_solver()
{
	//upper upper edges only start
	while(UP[0][0]=='W' || UP[0][2]=='W' || UP[2][0]=='W' || UP[2][2]=='W')
	{
//		printf("Loop entered!\n");
		if(UP[0][0]=='W')
		{
			align_edge(CENTRE,0,0);
		}
		else if(UP[0][2]=='W')
		{
			align_edge(CENTRE,0,2);
		}
		else if(UP[2][0]=='W')
		{
			align_edge(CENTRE,2,0);
		}
		else if(UP[2][2]=='W')
		{
			align_edge(CENTRE,2,2);
		}
		display();
		righty_alg();	righty_alg();	righty_alg();
	}
	//upper upper edges only end

	//upper right edges only start
	int count = 0;
	while(CENTRE[0][0]=='W' || CENTRE[0][2]=='W' || RIGHT[0][0]=='W' || RIGHT[0][2]=='W' || XRIGHT[0][0]=='W' || XRIGHT[0][2]=='W' || LEFT[0][0]=='W' || LEFT[0][2]=='W') {
		printf("Align edge 2 is called for i = %d\n",count);
//		if(count>25) break;
		if(CENTRE[0][0]=='W') 
		{
			align_edge_2(CENTRE,0,0);
		}
		if(CENTRE[0][2]=='W') 
		{
			align_edge_2(CENTRE,0,2);
		}
		if(RIGHT[0][0]=='W') 
		{
			align_edge_2(RIGHT,0,0);
		}
		if(RIGHT[0][2]=='W') 
		{
			align_edge_2(RIGHT,0,2);
		}
		if(XRIGHT[0][0]=='W') 
		{
			align_edge_2(XRIGHT,0,0);
		}
		if(XRIGHT[0][2]=='W') 
		{
			align_edge_2(XRIGHT,0,2);
		}
		if(LEFT[0][0]=='W') 
		{
			align_edge_2(LEFT,0,0);
		}
		if(LEFT[0][2]=='W') 
		{
			align_edge_2(LEFT,0,2);
		}
		count++;
		printf("Inside edge solver\n");
		display();
	}
	//upper right edges only end
}
int main()
{
	display();
	//giv_cube_array();
	R(0); R(0); U(0); U(0); R(1); U(1); L(1); U(1); L(0); L(0); U(0); U(0); 
	
	X(0); F(0); B(0);// U(0); r(0); u(0); 
	M(0); E(0); S(0);
	R(0); R(0); U(0); U(0); R(1); U(1); L(1); U(1); L(0); L(0); U(0); U(0); X(1);            //commenting this 
//	R(0); U(0); R(1); R(1); U(1); L(1); U(1); L(0); L(0); U(0); U(0); X(0);                     // and this will return buggy code.
//	R(0); R(0); U(0); U(1); R(1); F(0); R(0); R(0); U(1); R(1); F(1); R(0); U(0); //R(0); U(0); F(0); B(0); U(0); r(0); u(0); M(0); E(0); S(0);
//	F(0); R(0); R(0); U(1); R(1); 

	
	//IMPORTANT NOTE - LCI OR RIGHTY OR RCI CAN ALTER POSITION OF WHITE AND CAN BRING THEM BACK TO TOPMOST LAYER OF YELLOW SO WE'LL NEED TO CALL 
	//EDGE1 ONCE AGAIN.... SAD.
	
	
    // activate for edge 3 solver case
//	X(0); F(0); B(0);// U(0); r(0); u(0); 
//	M(0); E(0); S(0);
//	R(0); R(0); U(0); U(0); R(1); U(1); //L(1); U(1); L(0); L(0); U(0); U(0); X(1);            //commenting this 
//	R(0); U(0); R(1); R(1); U(1); L(1); U(1); L(0); L(0); U(0); U(0); X(0);                     
//	R(0); R(0); U(0); U(1); R(1); F(0); R(0); R(0); U(1); R(1); F(1); R(0); U(0); R(0); U(0); F(0); B(0); U(0); r(0); u(0); M(0); E(0); S(0);
//	F(0); R(0); R(0); U(1); R(1); 
	
	display();
	
	white_cross_solver();
	
	display();
	
	X(1); 
	push('X',1);
//	printf("\n");
//	printf("up ka center is : %c",UP[1][1]);
//	printf("\n");
	set_centre_to('R');
	Z(0);
	Z(0);
	white_edge_solver();
	set_centre_to('Y');
	white_edge_solver();
	display();
	set_centre_to('W');
	
	display();
	print_stack();
	
	
}
