/*
**
Team Id: 7052
* Author List: S Ragul,Srirama Charan,Muthu Bharathwaj,S Rajakanth
* Filename:	CB_Task_1_Sandbox.cpp
* Theme: Construct-O-Bot
* Functions: check_center(int,int),check_left(int),check_right(int),zig_zag(),e_shape(),Task_1_1(),Task_1_2(),
*            st_line(unsigned char,unsigned char,unsigned char,int),left_turn_wls(void),right_turn_wls(void),proximity(),search_ob(),pick_ob(),place_ob(),
			 minDistance(int dist[], bool sptSet[]),printpath(int parent[], int j),printSolution(int dist[]),dijkstra(int graph[V][V], int src, int dest),
			 chy(int pos, int nxt),chx(int pos, int nxt),change_dir(int pos,int nxt),chk_w(),minimum_dist(int pos),move().
* Global Variables: adj[V][V],dir,pik,st,dist[],m_s,posi,posj,path,vertex[34],node[34][2],map[19][13],w[5][6]
**
*/
//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions

#include "CB_Task_1_Sandbox.h"
#include<iostream>
#include<string>
#include<vector>
#define V 17  //number of nodes(or)vertices
int wt = 0;
using namespace std;

int adj[V][V];//creates a adjacency matrix to store the map

char dir = 'N';//Initialising direction as North
int pik = 0, st = 0;
int dist[V]; //stores the shortest distance between two nodes 
bool m_s[12] = { 1,1,1,1,1,1,1,1,1,1,1,1 };
int posi, posj;//stores the positions of the bot

vector<int> path;  // Number of vertices in the graph

int vertex[17];// Stores the vertex with minimum distance value, from  the set of vertices not yet included in shortest path tree

int node[17][2] = { {1,1},{0,1},{0,2},{1,2},{3,2},{5,2},{5,0},{3,0},{1,0},{2,2},{4,2},{4,0},{2,0},{6,1}, {6,2},{6,0},{0,0} };

//node stores the coorrdinates of all the nodes

int map[19][13] = {                             //node map(to give directions to the bot)
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
};

int w[5][6];  //w is a variable used to assign the houses with its specific material
//rows are houses from 1 to 5 and columns are the materials for each house
//column 0 represents sand
//column 0 represents electrical
//column 0 represents paint 
//column 0 represents cement
//column 0 represents gravel
//column 0 represents brick





/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
{

}
/*
*
* Function Name: check_left()
* Input: int c
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: check_left(3); //Turns left until black line is encountered
*
*/
int check_left(int c)
{
	int turn_factor = 0;
	while (1)
	{
		forward();
		velocity(30, 30);
		_delay_ms(1);
		left();
		_delay_ms(25);
		if (ADC_Conversion(1) || ADC_Conversion(2) || ADC_Conversion(3))
		{
			// returns when a line is detected
			return 1;
		}
		else if (turn_factor >= c)
		{
			//to turn only until a point and to return back to same point in zig zag
			break;
		}
		turn_factor++;
	}
	while (turn_factor > 0)
	{// to turn back the bot if line not found
		right();
		_delay_ms(25);
		turn_factor--;
	}
	return 0;
}


/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
	forward();
	velocity(150, 150);
	_delay_ms(400);
	left();
	_delay_ms(260);
	check_left(900);

}
/*
*
* Function Name: check_center();
* Input: int c,int d
* Output: void
* Logic: Uses white line sensors to turn until black line is encountered
* Example Call: check_center(1); //Turns  until black line is encountered
*
*/
int check_center(int direction, int blk_or_wt = 1)//blk_or_white is to check which line to follow 0 if white
											   //and 1 is white
{
	int turn_factor = 0;
	while (1)
	{
		forward();
		velocity(30, 30);
		_delay_ms(1);
		if (direction == 1)
			soft_right();
		else
			soft_left();
		_delay_ms(5);
		if (!ADC_Conversion(2) && !blk_or_wt)
			return 1;
		else if (ADC_Conversion(2) && blk_or_wt)
			return 1;//returns when center sensor is detecting black
		else if (turn_factor >= 4)
			break;
		turn_factor++;


	}
}

/*
*
* Function Name: check_right()
* Input: int c
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: check_right(3); //Turns right until black line is encountered
*
*/
int check_right(int c)
{
	int turn_factor = 0;
	while (1)
	{
		forward();
		velocity(30, 30);
		_delay_ms(1);
		right();
		_delay_ms(25);
		if (ADC_Conversion(1) || ADC_Conversion(2) || ADC_Conversion(3))
			return 1;// returns when a line is detected
		else if (turn_factor >= c)
			break;//to turn only until a point and to return back to same point in zig zag
		turn_factor++;


	}
	while (turn_factor > 0)
	{// to turn back the bot if line not found
		left();
		_delay_ms(25);
		turn_factor--;
	}

	return 0;
}
/*
*
* Function Name: st_line
* Input: left_sensor,right_sensor,center_sensor
* Output: void
* Logic: To move through a straight line without deviating
* Example Call: st_line(left_sensor, center_sensor, right_sensor);
*/
void st_line(unsigned char left_sensor, unsigned char center_sensor, unsigned char right_sensor, int vel)
{//This function is to make the bot follow the line properly between node to node
	if (!center_sensor)
		if (left_sensor)
		{//to get back on track when there is a deviation
			check_center(2, 1);
		}
		else if (right_sensor)
		{//to get back on track when there is a deviation
			check_center(1, 1);
		}
		else if (!left_sensor && !right_sensor)
		{// to wobble the bot to try to get it back on path
			velocity(0, 100);
			_delay_ms(25);
			velocity(100, 0);
			_delay_ms(25);
		}
		else
		{
			forward();
			velocity(60, 60);

		}
	else
		if (left_sensor)
		{ //to get back on track when there is a deviation
			check_center(2, 1);
		}
		else if (right_sensor)
		{ //to get back on track when there is a deviation
			check_center(1, 1);
		}
		else if (!left_sensor && !right_sensor)
		{// moves forward
			forward();
			velocity(vel, vel);
			_delay_ms(55);
		}
}



/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
	forward();
	velocity(150, 150);
	_delay_ms(400);
	right();
	_delay_ms(260);
	check_right(900);
}

/*
*
* Function Name: zig_zag
* Input: void
* Output: void
* Logic: Uses white line sensors to move in a zig-zag fashion
* Example Call: zig_zag(); //Moves in a zig-zag fashion till node is detected
*/


void zig_zag()
{
	unsigned char ls, rs, cs;
	int  x = 0;
	printf("Zig zag!!!!!!\n");
	while (1)
	{
		ls = ADC_Conversion(1);
		cs = ADC_Conversion(2);
		rs = ADC_Conversion(3);
		if (cs && rs && ls)
		{
			return;
		}

		if (!cs && !ls && !rs)
		{

			forward();
			_delay_ms(50);
			while (!ls)
			{

				if (x == 200)
					break;
				if (cs || ls)
					break;
				left();
				_delay_ms(1);
				ls = ADC_Conversion(1);
				cs = ADC_Conversion(2);
				rs = ADC_Conversion(3);
				x++;
			}
			if (ls == 0)
			{

				while (!ls)
				{
					if (x == 0)
						break;
					right();
					_delay_ms(1);
					x--;
				}
			}
			if (ls)
			{
				stop();
				_delay_ms(100);
				st_line(ls, cs, rs, 50);
				continue;
			}
			//stop();
			//_delay_ms(30);

			x = 0;
			while (!rs)
			{
				if (x == 200)
					break;
				if (cs || rs)
					break;
				right();
				_delay_ms(1);
				ls = ADC_Conversion(1);
				cs = ADC_Conversion(2);
				rs = ADC_Conversion(3);
				x++;
			}
			if (rs == 0)
			{

				while (!rs)
				{
					if (x == 0)
						break;
					left();
					_delay_ms(1);
					x--;
				}
			}
			if (rs)
			{
				stop();
				_delay_ms(100);
				st_line(ls, cs, rs, 50);
				continue;
			}


		}
		else
		{

			st_line(ls, cs, rs, 255);
		}
	}
}

/*
*
* Function Name: e_shape
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a e shape path on the arena
* Example Call: e_shape();
*/
void e_shape(void)
{
	int node = 0;
	unsigned char left_sensor, right_sensor, center_sensor;
	while (1)
	{
		left_sensor = ADC_Conversion(1);
		center_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		//printf("%d\t%d\t%d\n", left_sensor, center_sensor, right_sensor);


		if (left_sensor && right_sensor && center_sensor)
		{
			node++;
			if (node == 1 || (node >= 3 && node < 6))
			{
				forward();
				velocity(150, 150);
				_delay_ms(460);
				check_right(600);
			}

			if (node == 2)
			{
				forward();
				velocity(250, 250);
				_delay_ms(350);
				st_line(left_sensor, center_sensor, right_sensor, 230);
				continue;
			}
			if (node == 6)
			{
				stop();
				break;
			}
			forward();
			velocity(100, 0);
			_delay_ms(900);


		}
		st_line(left_sensor, center_sensor, right_sensor, 240);
	}
}

/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{// Write your task 1.1 Logic here
	int node = 0, white_zone = 0;
	unsigned char left_sensor, right_sensor, center_sensor;
	while (1)
	{
		left_sensor = ADC_Conversion(1);
		center_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		if (left_sensor == 0 && right_sensor == 0 && center_sensor == 255)//Condition for normal black line area
			white_zone = 0;
		else if (left_sensor && right_sensor && node == 13 && center_sensor == 0)//Condition for white line area
			white_zone++;
		//printf("%d\t%d\t%d\t%d\t%d\n",left_sensor,center_sensor,right_sensor,node,x);


		if (node == 5)
			st_line(left_sensor, center_sensor, right_sensor, 75);//This is for the curved path in the map
		else if (node == 9)
		{//This is for zig zag path in the map
			zig_zag();
		}
		else if (node == 13)
		{
			if (!center_sensor && !left_sensor && !right_sensor)//This makes sure that the bot doesn't come to a halt by
															   //wobbling the bot a little bit
			{
				soft_left();
				_delay_ms(120);
				soft_right();
				_delay_ms(120);
			}
			if (white_zone == 0)//This is for the normal black line part
			{
				stop();
				st_line(left_sensor, center_sensor, right_sensor, 45);
			}
			else   //This is for the white line portion
			{
				st_line(!left_sensor, !center_sensor, !right_sensor, 150);
				continue;
			}

		}
		else    //For the general path in the map
			st_line(left_sensor, center_sensor, right_sensor, 252);


		if (left_sensor && right_sensor && center_sensor)
		{//This indicates that a node is detected
			node++;
			if (node == 1 || node == 13 || node == 7 || node == 9 || node == 11 || node == 14)
			{//According to path, at these nodes the bot must turn left
				forward();
				velocity(150, 150);
				_delay_ms(460);
				right();
				_delay_ms(260);
				check_right(900);
			}
			else if (node == 5 || node == 6 || node == 8 || node == 10 || node == 12 || node == 15)
			{//According to path, at these nodes the bot must turn left
				forward();
				velocity(150, 150);
				_delay_ms(500);
				left();
				_delay_ms(260);
				check_left(900);//This will make the bot turn left until a black line is encountered
								//so that each time the bot will turn perfectly irrespective of its previous state
			}
			else if (node >= 2 && node < 5)
			{  //This is to make the bot continue forward in these nodes according to the path given
				forward();
				velocity(255, 255);
				_delay_ms(250);
				st_line(left_sensor, center_sensor, right_sensor, 255);
			}
			else if (node == 16)
			{	//The goal condition!!
				forward();
				_delay_ms(250);
				stop();
				break;
			}
		}
	}
}

/*
*
* Function Name: proximity()
* Input: void
* Output: void
* Logic: uses proximity sensors  to move between walls
* Example Call: proximity();
*
*/
void proximity()
{
	unsigned char lp, rp;
	while (1)
	{
		lp = ADC_Conversion(5);
		rp = ADC_Conversion(6);
		//cout << lp << "  " << rp << endl;
		printf("%d\t%d\n", lp, rp);
		if (ADC_Conversion(1) || ADC_Conversion(2) || ADC_Conversion(3))
		{
			//cout << "getting back";
			st_line(ADC_Conversion(1), ADC_Conversion(2), ADC_Conversion(3), 220);
			printf("back");
			return;
		}

		else if (lp > 4 && rp > 4 && rp < 75 && lp < 75)
		{
			forward();
			velocity(190, 190);
			_delay_ms(100);
		}
		else if (rp < 55 && lp> 77)
		{
			//cout << "left";
			//soft_left();
			velocity(0, 100);
			_delay_ms(4);
			forward();
			velocity(190, 190);
			_delay_ms(40);
		}
		else if (lp < 55 && rp>77)
		{
			//cout << "right";
			//soft_right();
			velocity(100, 0);
			_delay_ms(4);
			forward();
			velocity(190, 190);
			_delay_ms(40);
		}

		else if (lp > 100 && rp > 100)
		{
			return;
		}
	}
}

/*
*
* Function Name: search_ob()
* Input: void
* Output: void
* Logic: adjust the robot parallel to the object for it to pick
* Example Call: search_ob();
*
*/
void search_ob()
{
	while (ADC_Conversion(4) < 10)
	{
		soft_left();
		soft_right();
	}
	pick();
}

/*
*
* Function Name: pick_ob()
* Input: void
* Output: void
* Logic: picks up the object in front of the robot
* Example Call: pick_ob();
*
*/
void pick_ob()
{

	forward();
	search_ob();

}

/*
*
* Function Name: place_ob()
* Input: void
* Output: void
* Logic: places the object which the robot is carrying
* Example Call: place_ob();
*
*/
void place_ob()
{
	place();
	pik = 0;
	right();
	_delay_ms(1000);
	forward();
	_delay_ms(500);
	stop();
}


/*
*
* Function Name: minDistance(int [], bool [])
* Input: dist[],sptSet[]
* Output: min_index
* Logic: finds the minimum distance
* Example Call: minDistance(int dist[], bool sptSet[]);
*
*/



int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}



/*
*
* Function Name: printpath(int[],int)
* Input: parent[],j(Here j is the destination)
* Output: void
* Logic: stores the path
* Example Call: printpath(int parent[], int j);//stores the path to j from the current position
*
*/

void printpath(int parent[], int j)
{

	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	printpath(parent, parent[j]);

	//printf("%d ", j);
	path.push_back(j);

}


/*
*
* Function Name: printSolution(int [])
* Input: dist[]
* Output: 0
* Logic:   function to print the constructed distance array
* Example Call: printSolution(int dist[]);//prints the distance from source to each destination
*
*/


int printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("%d \t\t %d\n", i, dist[i]);
	return 0;
}


/*
*
* Function Name: dijkstra(int graph[V][V], int , int)
* Input: graph[v][v],src,dest
* Output: void
* Logic:  Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix
* Example Call: dijkstra(int graph[V][V], int src, int dest);//finds the shortest path to a node from a source
*
*/


void dijkstra(int graph[V][V], int src, int dest)
{
	path.clear();
	//clears the path array whenever dijkstra function is called
	int parent[V];
	//parent[v] used for printing the path
	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false, parent[src] = -1;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to  v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}

	}


	printpath(parent, dest);// print the path


}

/*
*
* Function Name: chy(int,int)
* Input: pos,nxt
* Output: 0,1 or -1
* Logic:  Function to check a change in y-position of the bot
* Example Call: chy(int pos, int nxt);//checks if there is a change in pos and nxt returns values accordingly
*
*/

int chy(int pos, int nxt)
{
	if (node[nxt][1] > node[pos][1])
		return 1;
	else if (node[nxt][1] < node[pos][1])
		return -1;

	return 0;

}

/*
*
* Function Name: chx(int,int)
* Input: pos,nxt
* Output: 0,1 or -1
* Logic:  Function to check a change in x-position of the bot
* Example Call: chx(int pos, int nxt);//checks if there is a change in pos and nxt returns values accordingly
*
*/

int chx(int pos, int nxt)
{
	if (node[nxt][0] > node[pos][0])
		return 1;
	else if (node[nxt][0] < node[pos][0])
		return -1;

	return 0;

}

/*
*
* Function Name: change_dir()
* Input: int pos, int nxt
* Output: void
* Logic: changes the direction
* Example Call: change_dir();
*
*/
void change_dir(int pos, int nxt)
{
	if (dir == 'N')
	{
		if (chy(pos, nxt) == 1)
		{
			right_turn_wls();
			dir = 'E';
		}
		else if (chy(pos, nxt) == -1)
		{
			left_turn_wls();
			dir = 'W';
		}
		else if (chx(pos, nxt) == 1)
		{
			right();
			_delay_ms(1000);
			forward();
			_delay_ms(500);
			dir = 'S';

		}
		else if (chx(pos, nxt) == -1)
		{
			forward();
			_delay_ms(500);

		}
	}
	else if (dir == 'E')
	{
		if (chy(pos, nxt) == 1)
		{
			forward();
			_delay_ms(500);
		}
		else if (chy(pos, nxt) == -1)
		{
			right();
			_delay_ms(1000);
			forward();
			_delay_ms(500);
			dir = 'W';
		}
		else if (chx(pos, nxt) == 1)
		{
			right_turn_wls();
			dir = 'S';

		}
		else if (chx(pos, nxt) == -1)
		{
			left_turn_wls();
			dir = 'N';
		}
	}
	else if (dir == 'W')
	{
		if (chy(pos, nxt) == 1)
		{
			right();
			_delay_ms(1000);
			forward();
			_delay_ms(500);
			dir = 'E';

		}
		else if (chy(pos, nxt) == -1)
		{
			forward();
			_delay_ms(500);

		}
		else if (chx(pos, nxt) == 1)
		{

			left_turn_wls();
			dir = 'S';

		}
		else if (chx(pos, nxt) == -1)
		{
			right_turn_wls();

			dir = 'N';
		}
	}
	else if (dir == 'S')
	{
		if (chy(pos, nxt) == 1)
		{
			left_turn_wls();
			dir = 'E';
		}
		else if (chy(pos, nxt) == -1)
		{
			right_turn_wls();
			dir = 'W';
		}
		else if (chx(pos, nxt) == 1)
		{
			forward();
			_delay_ms(500);
		}
		else if (chx(pos, nxt) == -1)
		{
			right();
			_delay_ms(1000);
			forward();
			_delay_ms(500);
			dir = 'N';
		}
	}
}
int chk_w()
{
	int ch = 1;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++)
			if (w[i][j] == 1)
				ch *= 0;
	return !ch;
}




/*
*
* Function Name: minimum_dist(int)
* Input: pos
* Output: void
* Logic: finds the minimum distance by summing up the distance between the current position and materials  and the distance between materials to the repective house
* Example Call: minimum_dist(int pos);
*
*/


void minimum_dist(int pos)
{
	int i, j, min = INT_MAX, total = 0, wh = 0, h = 0, c, d;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 6; j++)
			if (w[i][j] > 1)
			{
				dijkstra(adj, pos, w[i][j]);
				c = dist[w[i][j]];
				dijkstra(adj, w[i][j], i + 10);
				d = dist[i + 10];
				total = c + d;
				if (total < min)
				{
					min = total;
					posi = w[i][j];
					wh = j;
					h = i;
					posj = i + 10;

				}
				c = 0; d = 0;

			}
	w[h][wh] = 0;
}

/*
*
* Function Name: move()
* Input: void
* Output: void
* Logic: moves the robot along the path
* Example Call: move();
*
*/

void move()
{
	minimum_dist(st);
	printf("move!!!!");
	int pos = st, nxt, i = 0, d = 27;
	unsigned char left_sens, right_sens, center_sens;
	dijkstra(adj, pos, posi);
	for (int i = 0; i < path.size(); i++)
		cout << path[i];
	nxt = path[0];

	while (1)
	{
		if (wt == 0)
		{
			left_sens = ADC_Conversion(1);
			center_sens = ADC_Conversion(2);
			right_sens = ADC_Conversion(3);
			//printf("%d\t %d\t %d\n", left_sens, center_sens, right_sens);
		}
		else
		{

			left_sens = !ADC_Conversion(1);
			center_sens = !ADC_Conversion(2);
			right_sens = !ADC_Conversion(3);
			//printf("%d\t %d\t %d\n", left_sens, center_sens, right_sens);
			//printf("a");


		}
		if (center_sens && left_sens && right_sens)
		{
			i++;
			if (i >= path.size())
				break;
			pos = nxt;
			if (pos == posi)
				break;
			nxt = path[i];
			change_dir(pos, nxt);
			printf("b");
		}
		else if (!left_sens && !right_sens && !center_sens)
		{
			if ((pos == 4 && nxt == 14) || (nxt == 4 && pos == 14))
			{
				forward();
				_delay_ms(1000);
				proximity();
				printf("c");
			}
			else if ((pos == 12 && nxt == 6) || (nxt == 12 && pos == 6))
				zig_zag();
		}
		else if ((left_sens && right_sens && !center_sens) || (!left_sens && right_sens && !center_sens) && (pos == 8 || pos == 10) && nxt == 9)
			wt = 1;
		else if (wt == 1 && !left_sens && !right_sens && center_sens)
			wt = 0;
		else
			st_line(left_sens, center_sens, right_sens, 190);
	}
	pick_ob();
	right_turn_wls();
	if (dir == 'N')
		dir = 'S';
	else if (dir == 'S')
		dir = 'N';
	else if (dir == 'E')
		dir = 'W';
	else if (dir == 'W')
		dir = 'E';
	//cout << posj;
	dijkstra(adj, posi, posj);
	for (int i = 0; i < path.size(); i++)
	{
		printf("%d\n", path[i]);
	}
	pos = posi;
	i = 0;
	nxt = path[0];
	while (1)
	{
		if (wt == 0)
		{
			left_sens = ADC_Conversion(1);
			center_sens = ADC_Conversion(2);
			right_sens = ADC_Conversion(3);
		}
		else
		{
			left_sens = !ADC_Conversion(1);
			center_sens = !ADC_Conversion(2);
			right_sens = !ADC_Conversion(3);
		}
		if (center_sens && left_sens && right_sens)
		{
			i++;
			if (i >= path.size())
				break;
			pos = nxt;
			if (pos == posj)
				break;

			nxt = path[i];
			change_dir(pos, nxt);

		}
		else if (!left_sens && !right_sens && !center_sens)
		{
			if ((pos == 4 && nxt == 14) || (nxt == 4 && pos == 14))
			{
				st_line(left_sens, center_sens, right_sens, 150);
				//forward();
				//_delay_ms(1000);
				proximity();
			}
			else if ((pos == 12 && nxt == 6) || (nxt == 12 && pos == 6))
				zig_zag();
		}
		else if ((pos == 8 || pos == 10) && nxt == 9)
		{

			st_line(left_sens, center_sens, right_sens, 50);
			wt = 1;
			continue;
		}
		else if (wt == 1 && !left_sens && !right_sens && center_sens)
			wt = 0;
		else
			st_line(left_sens, center_sens, right_sens, 190);

	}

	forward();
	_delay_ms(230);
	place();
	st = posj;
	right_turn_wls();
	if (dir == 'N')
		dir = 'S';
	else if (dir == 'S')
		dir = 'N';
	else if (dir == 'E')
		dir = 'W';
	else if (dir == 'W')
		dir = 'E';
}
/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
	int i, min = 99, nd = 0;

	for (int i = 0; i < 17; i++)		//initialising the adjacency matrix with all zeroes and later it is updated
		for (int j = 0; j < 17; j++)
			adj[i][j] = 0;
	for (int i = 0; i < 5; i++)			//initialising the adjacency matrix with all zeroes and later it is updated
		for (int j = 0; j < 6; j++)
			w[i][j] = 0;
	w[0][0] = 4;
	w[0][2] = 5;
	w[1][4] = 6;
	w[1][3] = 9;
	w[2][1] = 8;
	w[2][0] = 4;
	w[3][5] = 5;
	w[4][5] = 7;
	w[4][1] = 9;

	adj[0][1] = 1;
	adj[1][2] = 4;
	adj[1][16] = 4;

	adj[2][1] = 4;
	adj[2][3] = 2;

	adj[3][2] = 2;
	adj[3][9] = 2;

	adj[4][9] = 2;
	adj[4][10] = 2;

	adj[5][10] = 2;
	adj[5][14] = 2;

	adj[6][15] = 2;
	adj[6][11] = 2;

	adj[7][11] = 2;
	adj[7][12] = 2;

	adj[8][16] = 2;
	adj[8][12] = 2;

	adj[9][12] = 8;
	adj[9][3] = 2;
	adj[9][4] = 2;

	adj[10][11] = 10;
	adj[10][4] = 2;
	adj[10][5] = 2;

	adj[11][10] = 10;
	adj[11][6] = 2;
	adj[11][7] = 2;

	adj[12][9] = 8;
	adj[12][7] = 2;
	adj[12][8] = 2;

	adj[13][15] = 4;
	adj[13][14] = 4;

	adj[14][13] = 4;
	adj[14][5] = 2;

	adj[15][6] = 2;
	adj[15][13] = 4;

	adj[16][1] = 4;
	adj[16][8] = 2;

	while (chk_w)
		move();
	printf("Done!!"); //simulation is done

}