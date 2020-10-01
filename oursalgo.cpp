#include<iostream>
#include <algorithm> 
#include <chrono> 
#include<vector>
//#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct point
{
	float x;
	float y;
};

float    random_between_two_int(float min, float max);
void newPoint(float a, float b);
void insertH(float pp, float qq);
int checkOrient(point p1, point p2, point p3);
void insertGtemp(float xx, float yy);

void convexHull();
void printHull();

void procesLLeft();
void procesULeft();
void procesLRight();
void procesURight();

int findLowerXMin();
int findUpperXMin();
int findLowerXMax();
int findUpperXMax();

int findLeftYMin();
int findRightYMin();
int findLeftYMax();
int findRightYMax();

void removeDuplicate();


vector <point> g1, g2, g3, gtemp, fhull ,chull;

float    random_between_two_int(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

int main()
{
	auto start = high_resolution_clock::now();
	
	//point p1;
	int ii;
	/*float arra[72][2] = { {0, 0 },{1, 2 },{-2 ,1},{ -1 ,-1} ,{3 ,4 },{4 ,3},
{ -5, 4} ,{6 ,5}, {7, 7},{ 7 ,-7 },{-7, -7} ,{-7 ,7 },{9 ,0 },{-9, 0} ,{0 ,9},
{ 0 ,-9},{ -8 ,0} ,{8 ,0},{ -7 ,0},{ 7 ,0},{ -6 ,0},{6 ,0},{ -5, 0},{ 5 ,0},{ -4, 0}, {4 ,0},{ -3 ,0},
{3 ,0} ,{-2 ,0} ,{2 ,0},{ -1 ,0}, {1 ,0} ,{0, -8},{ 0, 8},{ 0 ,-7},{ 0 ,7 },
{0 ,-6},{ 0 ,6} ,{0, -5},{ 0, 5},{ 0 ,-4 },{0 ,4} ,{0, -3},{ 0 ,3} ,{0 ,-2},{ 0 ,2},{ 0 ,-1}, {0 ,1},{ 1, 1},
{ 2 ,2 },{3 ,3},{ 4 ,4}, {5 ,5},{ 6 ,6},{ 1 ,-1},{2, -2},{ 3 ,-3} ,{4 ,-4},{ 5 ,-5},{6 ,-6} ,{-1, 1},{ -2 ,2},{ -3 ,3},
 {-4 ,4},{ -5 ,5},{ -6 ,6},{ -1 ,-1} ,{-2, -2},{ -3, -3},{ -4 ,-4},{ -5 ,-5},{-6 ,-6} };*/
	chull.clear();
	g1.clear();
	g2.clear();
	g3.clear();
	gtemp.clear();
	g1.resize(1000000);
	g2.resize(1000000);
	gtemp.resize(1000000);
	g3.resize(1000000);
	/*for (ii = 0; ii < 72; ii++)
	{
		newPoint(arra[ii][0],arra[ii][1]);
	}*/
	//p1.x = 4;
	//p1.y = 5;
	//g1.push_back(p1);
	float xx, yy;
	for (ii = 0; ii < 1000000; ii++)
	{
		xx= random_between_two_int(-1000000, 1000000);
		yy= random_between_two_int(-1000000, 1000000);
		newPoint(xx, yy);
	}
	point* p;
	//cout << g1[0].x << endl;
	/*for (ii = 0; ii < g1.size(); ii++)
	{
		cout << g1[ii].x << " "<<g1[ii].y<<endl;
	}*/

	//vector<struct point>::iterator it;
	//for (auto i = g1.begin(); i != g1.end(); ++i)
	//	cout << *i<< " ";
	/*for (it = g1.begin(); it != g1.end(); it++)
	{
		cout << *it->x << endl;
		
	}
	*/
	convexHull();
	removeDuplicate();
	printHull();
	 
	//cout << "hello world"<<endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;
	
	//system("pause");
	return 0;
}

void printHull()
{
	int i;
	cout << "point compromising convex hull are ";
	for (i = 0; i < fhull.size(); i++)
	{
		cout << "(" << fhull[i].x << " ," << fhull[i].y << "), ";
	}
	cout << endl;
}
void newPoint(float a, float b)
{
	point pp;
	pp.x = a;
	pp.y = b;
	g1.push_back(pp);

}
void convexHull()
{
	//cout << "welcome to convex hull" << endl;
	procesLLeft();
	//printHull();
	procesULeft();
	//printHull();
	procesLRight();
	//printHull();
	procesURight();
	//printHull();
	//procesULeft();

}
void procesLLeft()
{
	//cout << "welcome to processLLeft" << endl;
	int temp,i;
	int varx, vary,orient,orient1;
	point xpoint, ypoint;
	temp = 1;
	g2.clear();
	g3.clear();
	/*cout << "points in g1 are" << endl;
	for (i = 0; i < g1.size(); i++)
	{
		cout << "(" << g1[i].x << " ," << g1[i].y << "), ";
	}*/
	//cout << endl;
	g2 = g1;
	g3 = g1;
	int jj;
	gtemp.clear();
	varx = findLowerXMin();
	vary = findLeftYMin();
	//cout << "varx and vary are " << varx << " " << vary << endl;
	xpoint.x = g2[varx].x;
	xpoint.y = g2[varx].y;
	ypoint.x = g2[vary].x;
	ypoint.y = g2[vary].y;

	if (varx == vary)
	{
		insertH(g2[varx].x, g2[varx].y);
		g2.clear();
		return;
	}

	insertH(g2[varx].x, g2[varx].y);
	insertH(g2[vary].x, g2[vary].y);

	for (jj = 0; jj < g2.size(); jj++)
	{
		if (g2[jj].x < g2[vary].x && g2[jj].y < g2[varx].y)
		{
			insertGtemp(g2[jj].x, g2[jj].y);
		}
	}

	//cout << "gtemp size is" << gtemp.size() << endl;

	if (gtemp.size() == 0)
	{
		return;
	}
	else if(gtemp.size()==1)
	{
		orient=checkOrient(g2[varx], g2[vary], gtemp[0]);
		if (orient == 0)
		{
			insertH(gtemp[0].x, gtemp[0].y);
			return;
		}
		else if (orient == 1)
		{
			
			return;
		}
		else
		{
			insertH(gtemp[0].x, gtemp[0].y);
			return;
		}
	}
	g2.clear();
	g2 = gtemp;
	gtemp.clear();
	//cout << "g2 size is " << g2.size() << endl;
	/*for (jj = 0; jj < g2.size(); jj++)
	{
		cout << g2[jj].x << " " << g2[jj].y << endl;
	}*/
	while (temp != 0)
	{
		//cout << "welcome to while loop" << endl;
		varx=findLowerXMin();
		vary = findLeftYMin();
		//cout << "the value of new varx is " << varx << " " << vary << endl;
		if (varx == vary)
		{
			orient=checkOrient(xpoint, ypoint, g2[varx]);
			if (orient == 0)
			{
				insertH(g2[varx].x, g2[vary].y);
				return;
			}
			else if(orient==-1)
			{
				insertH(g2[varx].x, g2[vary].y);
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			//cout << g2[varx].x << " " << g2[varx].y << " " << g2[vary].x << " " << g2[vary].y << "check"<<endl;
			orient = checkOrient(xpoint, ypoint, g2[varx]);
			orient1= checkOrient(xpoint, ypoint, g2[vary]);
			if (orient > 0 && orient1 > 0)
			{
				//cout << "orient is negatave" << endl;
				return;
			}
			else if(orient<0&&orient1>0)
			{
				insertH(g2[vary].x, g2[vary].y);
				return;
			}
			else if (orient > 0 && orient1 < 0)
			{
				insertH(g2[varx].x, g2[varx].y);
				return;
			}
			else
			{
				insertH(g2[varx].x, g2[varx].y);
				insertH(g2[vary].x, g2[vary].y);
				xpoint.x = g2[varx].x;
				xpoint.y = g2[varx].y;
				ypoint.x = g2[vary].x;
				ypoint.y = g2[vary].y;
				for (jj = 0; jj < g2.size(); jj++)
				{
					if (g2[jj].x < g2[vary].x && g2[jj].y < g2[varx].y)
					{
						insertGtemp(g2[jj].x, g2[jj].y);
					}
				}
				//cout << "gtemp sizeee is " << gtemp.size() << endl;
				if (gtemp.size() == 0)
				{
					return;
				}
				else if (gtemp.size() == 1)
				{
					orient = checkOrient(xpoint, ypoint, gtemp[0]);
					if (orient == 0)
					{
						insertH(gtemp[0].x, gtemp[0].y);
						return;
					}
					else if (orient == 1)
					{
						
						return;
					}
					else
					{
						insertH(gtemp[0].x, gtemp[0].y);
						return;
					}
				}
				g2.clear();
				g2 = gtemp;
				gtemp.clear();

				
			}
		}
		
	}

}
void procesULeft()


	{
		//cout << "welcome to processULeft" << endl;
		int temp, i;
		int varx, vary, orient, orient1;
		point xpoint, ypoint;
		temp = 1;
		g2.clear();
		g3.clear();
		/*cout << "points in g1 are" << endl;
		for (i = 0; i < g1.size(); i++)
		{
			cout << "(" << g1[i].x << " ," << g1[i].y << "), ";
		}*/
		//cout << endl;
		g2 = g1;
		g3 = g1;
		int jj;
		gtemp.clear();
		varx = findUpperXMin();
		vary = findLeftYMax();
		//cout << "varx and vary are " << varx << " " << vary << endl;
		xpoint.x = g2[varx].x;
		xpoint.y = g2[varx].y;
		ypoint.x = g2[vary].x;
		ypoint.y = g2[vary].y;

		if (varx == vary)
		{
			insertH(g2[varx].x, g2[varx].y);
			g2.clear();
			return;
		}

		insertH(g2[varx].x, g2[varx].y);
		insertH(g2[vary].x, g2[vary].y);

		for (jj = 0; jj < g2.size(); jj++)
		{
			if (g2[jj].x < g2[vary].x && g2[jj].y > g2[varx].y)
			{
				insertGtemp(g2[jj].x, g2[jj].y);
			}
		}

		//cout << "gtemp size is" << gtemp.size() << endl;

		if (gtemp.size() == 0)
		{
			return;
		}
		else if (gtemp.size() == 1)
		{
			orient = checkOrient(g2[varx], g2[vary], gtemp[0]);
			if (orient == 0)
			{
				insertH(gtemp[0].x, gtemp[0].y);
				return;
			}
			else if (orient == 1)
			{
				insertH(gtemp[0].x, gtemp[0].y);
				return;
			}
			else
			{
				
				return;
			}
		}
		g2.clear();
		g2 = gtemp;
		gtemp.clear();
		//cout << "g2 size is " << g2.size() << endl;
		/*for (jj = 0; jj < g2.size(); jj++)
		{
			cout << g2[jj].x << " " << g2[jj].y << endl;
		}*/
		while (temp != 0)
		{
			//cout << "welcome to while loop" << endl;
			varx = findUpperXMin();
			vary = findLeftYMax();
			//cout << "the value of new varx is " << varx << " " << vary << endl;
			if (varx == vary)
			{
				orient = checkOrient(xpoint, ypoint, g2[varx]);
				if (orient == 0)
				{
					insertH(g2[varx].x, g2[vary].y);
					return;
				}
				else if (orient == 1)
				{
					insertH(g2[varx].x, g2[vary].y);
					return;
				}
				else
				{
					return;
				}
			}
			else
			{
				//cout << g2[varx].x << " " << g2[varx].y << " " << g2[vary].x << " " << g2[vary].y << "check"<<endl;
				orient = checkOrient(xpoint, ypoint, g2[varx]);
				orient1 = checkOrient(xpoint, ypoint, g2[vary]);
				if (orient < 0 && orient1 < 0)
				{
					//cout << "orient is negatave" << endl;
					return;
				}
				else if (orient < 0 && orient1>0)
				{
					insertH(g2[varx].x, g2[varx].y);
					
					return;
				}
				else if (orient > 0 && orient1 < 0)
				{
					insertH(g2[vary].x, g2[vary].y);
					return;
				}
				else
				{
					insertH(g2[varx].x, g2[varx].y);
					insertH(g2[vary].x, g2[vary].y);
					xpoint.x = g2[varx].x;
					xpoint.y = g2[varx].y;
					ypoint.x = g2[vary].x;
					ypoint.y = g2[vary].y;
					for (jj = 0; jj < g2.size(); jj++)
					{
						if (g2[jj].x < g2[vary].x && g2[jj].y < g2[varx].y)
						{
							insertGtemp(g2[jj].x, g2[jj].y);
						}
					}
					//cout << "gtemp sizeee is " << gtemp.size() << endl;
					if (gtemp.size() == 0)
					{
						return;
					}
					else if (gtemp.size() == 1)
					{
						orient = checkOrient(xpoint, ypoint, gtemp[0]);
						if (orient == 0)
						{
							insertH(gtemp[0].x, gtemp[0].y);
							return;
						}
						else if (orient == -1)
						{

							return;
						}
						else
						{
							insertH(gtemp[0].x, gtemp[0].y);
							return;
						}
					}
					g2.clear();
					g2 = gtemp;
					gtemp.clear();


				}
			}

		}

	}

void procesURight()
{
	//cout << "welcome to processupperright" << endl;
	int temp, i;
	int varx, vary, orient, orient1;
	point xpoint, ypoint;
	temp = 1;
	g2.clear();
	g3.clear();
	//cout << "points in g1 are" << endl;
	/*for (i = 0; i < g1.size(); i++)
	{
		cout << "(" << g1[i].x << " ," << g1[i].y << "), ";
	}*/
	//cout << endl;
	g2 = g1;
	g3 = g1;
	int jj;
	gtemp.clear();
	varx = findUpperXMax();
	vary = findRightYMax();
	//cout << "varx and vary are " << varx << " " << vary << endl;
	xpoint.x = g2[varx].x;
	xpoint.y = g2[varx].y;
	ypoint.x = g2[vary].x;
	ypoint.y = g2[vary].y;

	if (varx == vary)
	{
		insertH(g2[varx].x, g2[varx].y);
		g2.clear();
		return;
	}

	insertH(g2[varx].x, g2[varx].y);
	insertH(g2[vary].x, g2[vary].y);

	for (jj = 0; jj < g2.size(); jj++)
	{
		if (g2[jj].x > g2[vary].x && g2[jj].y > g2[varx].y)
		{
			insertGtemp(g2[jj].x, g2[jj].y);
		}
	}

	//cout << "gtemp size is" << gtemp.size() << endl;

	if (gtemp.size() == 0)
	{
		return;
	}
	else if (gtemp.size() == 1)
	{
		orient = checkOrient(g2[varx], g2[vary], gtemp[0]);
		if (orient == 0)
		{
			insertH(gtemp[0].x, gtemp[0].y);
			return;
		}
		else if (orient == 1)
		{

			return;
		}
		else
		{
			insertH(gtemp[0].x, gtemp[0].y);
			return;
		}
	}
	g2.clear();
	g2 = gtemp;
	gtemp.clear();
	//cout << "g2 size is " << g2.size() << endl;
	/*for (jj = 0; jj < g2.size(); jj++)
	{
		cout << g2[jj].x << " " << g2[jj].y << endl;
	}*/
	while (temp != 0)
	{
		//cout << "welcome to while loop" << endl;
		varx = findUpperXMax();
		vary = findRightYMax();
		//cout << "the value of new varx is " << varx << " " << vary << endl;
		if (varx == vary)
		{
			orient = checkOrient(xpoint, ypoint, g2[varx]);
			if (orient == 0)
			{
				insertH(g2[varx].x, g2[vary].y);
				return;
			}
			else if (orient == -1)
			{
				insertH(g2[varx].x, g2[vary].y);
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			//cout << g2[varx].x << " " << g2[varx].y << " " << g2[vary].x << " " << g2[vary].y << "check"<<endl;
			orient = checkOrient(xpoint, ypoint, g2[varx]);
			orient1 = checkOrient(xpoint, ypoint, g2[vary]);
			if (orient > 0 && orient1 > 0)
			{
				//cout << "orient is negatave" << endl;
				return;
			}
			else if (orient < 0 && orient1>0)
			{
				insertH(g2[vary].x, g2[vary].y);
				return;
			}
			else if (orient > 0 && orient1 < 0)
			{
				insertH(g2[varx].x, g2[varx].y);
				return;
			}
			else
			{
				insertH(g2[varx].x, g2[varx].y);
				insertH(g2[vary].x, g2[vary].y);
				xpoint.x = g2[varx].x;
				xpoint.y = g2[varx].y;
				ypoint.x = g2[vary].x;
				ypoint.y = g2[vary].y;
				for (jj = 0; jj < g2.size(); jj++)
				{
					if (g2[jj].x > g2[vary].x && g2[jj].y > g2[varx].y)
					{
						insertGtemp(g2[jj].x, g2[jj].y);
					}
				}
				//cout << "gtemp sizeee is " << gtemp.size() << endl;
				if (gtemp.size() == 0)
				{
					return;
				}
				else if (gtemp.size() == 1)
				{
					orient = checkOrient(xpoint, ypoint, gtemp[0]);
					if (orient == 0)
					{
						insertH(gtemp[0].x, gtemp[0].y);
						return;
					}
					else if (orient == 1)
					{

						return;
					}
					else
					{
						insertH(gtemp[0].x, gtemp[0].y);
						return;
					}
				}
				g2.clear();
				g2 = gtemp;
				gtemp.clear();


			}
		}

	}

}
void procesLRight()


	{
		//cout << "welcome to processULeft" << endl;
		int temp, i;
		int varx, vary, orient, orient1;
		point xpoint, ypoint;
		temp = 1;
		g2.clear();
		g3.clear();
		/*cout << "points in g1 are" << endl;
		for (i = 0; i < g1.size(); i++)
		{
			cout << "(" << g1[i].x << " ," << g1[i].y << "), ";
		}*/
		//cout << endl;
		g2 = g1;
		g3 = g1;
		int jj;
		gtemp.clear();
		varx = findLowerXMax();
		vary = findRightYMin();
		//cout << "varx and vary are " << varx << " " << vary << endl;
		xpoint.x = g2[varx].x;
		xpoint.y = g2[varx].y;
		ypoint.x = g2[vary].x;
		ypoint.y = g2[vary].y;

		if (varx == vary)
		{
			insertH(g2[varx].x, g2[varx].y);
			g2.clear();
			return;
		}

		insertH(g2[varx].x, g2[varx].y);
		insertH(g2[vary].x, g2[vary].y);

		for (jj = 0; jj < g2.size(); jj++)
		{
			if (g2[jj].x > g2[vary].x && g2[jj].y < g2[varx].y)
			{
				insertGtemp(g2[jj].x, g2[jj].y);
			}
		}

		//cout << "gtemp size is" << gtemp.size() << endl;

		if (gtemp.size() == 0)
		{
			return;
		}
		else if (gtemp.size() == 1)
		{
			orient = checkOrient(g2[varx], g2[vary], gtemp[0]);
			if (orient == 0)
			{
				insertH(gtemp[0].x, gtemp[0].y);
				return;
			}
			else if (orient == 1)
			{
				insertH(gtemp[0].x, gtemp[0].y);
				return;
			}
			else
			{

				return;
			}
		}
		g2.clear();
		g2 = gtemp;
		gtemp.clear();
		//cout << "g2 size is " << g2.size() << endl;
		/*for (jj = 0; jj < g2.size(); jj++)
		{
			cout << g2[jj].x << " " << g2[jj].y << endl;
		}*/
		while (temp != 0)
		{
			//cout << "welcome to while loop" << endl;
			varx = findLowerXMax();
			vary = findRightYMin();
			//cout << "the value of new varx is " << varx << " " << vary << endl;
			if (varx == vary)
			{
				orient = checkOrient(xpoint, ypoint, g2[varx]);
				if (orient == 0)
				{
					insertH(g2[varx].x, g2[vary].y);
					return;
				}
				else if (orient == 1)
				{
					insertH(g2[varx].x, g2[vary].y);
					return;
				}
				else
				{
					return;
				}
			}
			else
			{
				//cout << g2[varx].x << " " << g2[varx].y << " " << g2[vary].x << " " << g2[vary].y << "check"<<endl;
				orient = checkOrient(xpoint, ypoint, g2[varx]);
				orient1 = checkOrient(xpoint, ypoint, g2[vary]);
				if (orient < 0 && orient1 < 0)
				{
					//cout << "orient is negatave" << endl;
					return;
				}
				else if (orient < 0 && orient1>0)
				{
					insertH(g2[varx].x, g2[varx].y);

					return;
				}
				else if (orient > 0 && orient1 < 0)
				{
					insertH(g2[vary].x, g2[vary].y);
					return;
				}
				else
				{
					insertH(g2[varx].x, g2[varx].y);
					insertH(g2[vary].x, g2[vary].y);
					xpoint.x = g2[varx].x;
					xpoint.y = g2[varx].y;
					ypoint.x = g2[vary].x;
					ypoint.y = g2[vary].y;
					for (jj = 0; jj < g2.size(); jj++)
					{
						if (g2[jj].x > g2[vary].x && g2[jj].y < g2[varx].y)
						{
							insertGtemp(g2[jj].x, g2[jj].y);
						}
					}
					//cout << "gtemp sizeee is " << gtemp.size() << endl;
					if (gtemp.size() == 0)
					{
						return;
					}
					else if (gtemp.size() == 1)
					{
						orient = checkOrient(xpoint, ypoint, gtemp[0]);
						if (orient == 0)
						{
							insertH(gtemp[0].x, gtemp[0].y);
							return;
						}
						else if (orient == -1)
						{

							return;
						}
						else
						{
							insertH(gtemp[0].x, gtemp[0].y);
							return;
						}
					}
					g2.clear();
					g2 = gtemp;
					gtemp.clear();


				}
			}

		}

	}




int checkOrient(point p1, point p2, point p3)
{
	int value;
	value = (p2.x - p1.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p1.y);
	//anticlockwise value +ve 
	if (value == 0)
	{
		return 0;
	}
	else if (value > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
void insertGtemp(float xx,float yy)
{
	point ptemp;
	ptemp.x = xx;
	ptemp.y = yy;
	gtemp.push_back(ptemp);
}

void insertH(float pp, float qq)
{
	point p11;
	p11.x = pp;
	p11.y = qq;
	chull.push_back(p11);
}
void removeDuplicate()
{
	int dec;
	dec = 0;
	int i, j;
	for (i = 0; i < chull.size(); i++)
	{
		dec = 0;
		for (j = i + 1; j < chull.size(); j++)
		{
			if ((chull[i].x == chull[j].x) && (chull[i].y == chull[j].y))
			{
				dec++;
				break;
			}
			
		}

		if (dec == 0)
		{
			fhull.push_back(chull[i]);
		}
	}
}

int findLowerXMin()
{
	int i,res;
	float xL;
	xL = g2[0].x;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].x < xL)
		{
			xL = g2[i].x;
			res = i;
		}
		else if (g2[i].x== xL&&g2[i].y<g2[res].y)
		{
			xL = g2[i].x;
			res = i;
		}
	}
	return res;
}
int findUpperXMin()
{
	int i, res;
	float xL;
	xL = g2[0].x;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].x < xL)
		{
			xL = g2[i].x;
			res = i;
		}
		else if (g2[i].x == xL && g2[i].y > g2[res].y)
		{
			xL = g2[i].x;
			res = i;
		}
	}
	return res;
}
int findLowerXMax()
{
	int i, res;
	float xL;
	xL = g2[0].x;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].x > xL)
		{
			xL = g2[i].x;
			res = i;
		}
		else if (g2[i].x == xL && g2[i].y < g2[res].y)
		{
			xL = g2[i].x;
			res = i;
		}
	}
	return res;
}
int findUpperXMax()
{
	int i, res;
	float xL;
	xL = g2[0].x;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].x > xL)
		{
			xL = g2[i].x;
			res = i;
		}
		else if (g2[i].x == xL && g2[i].y > g2[res].y)
		{
			xL = g2[i].x;
			res = i;
		}
	}
	return res;
}

int findLeftYMin()
{
	int i, res;
	float xL;
	xL = g2[0].y;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].y < xL)
		{
			xL = g2[i].y;
			res = i;
		}
		else if (g2[i].y == xL && g2[i].x < g2[res].x)
		{
			xL = g2[i].y;
			res = i;
		}
	}
	return res;

}
int findRightYMin()
{
	int i, res;
	float xL;
	xL = g2[0].y;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].y < xL)
		{
			xL = g2[i].y;
			res = i;
		}
		else if (g2[i].y == xL && g2[i].x > g2[res].x)
		{
			xL = g2[i].y;
			res = i;
		}
	}
	return res;
}
int findLeftYMax()
{
	int i, res;
	float xL;
	xL = g2[0].y;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].y > xL)
		{
			xL = g2[i].y;
			res = i;
		}
		else if (g2[i].y == xL && g2[i].x < g2[res].x)
		{
			xL = g2[i].y;
			res = i;
		}
	}
	return res;
}
int findRightYMax()
{
	int i, res;
	float xL;
	xL = g2[0].y;
	res = 0;
	for (i = 1; i < g2.size(); i++)
	{
		if (g2[i].y > xL)
		{
			xL = g2[i].y;
			res = i;
		}
		else if (g2[i].y == xL && g2[i].x > g2[res].x)
		{
			xL = g2[i].y;
			res = i;
		}
	}
	return res;
}