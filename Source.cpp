#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <stack>
#include <queue>
#include <math.h>
using namespace sf;
using namespace std;
bool start;
bool draw;
bool dfs;
bool bfs;
bool astar;
bool start_node;
bool target_node;
bool erase;
RectangleShape r[50][96];
RectangleShape menu[8];
priority_queue<pair<double, pair<int, int>>,vector<pair<double,pair<int,int>>>,greater<pair<double,pair<int,int>>>>pq;
queue<pair<int, int>>q;
stack<pair<int, int>>s;
map<pair<int,int>, pair<int, int>>path;
Texture t[8];
string buttons[8] = {"start","end","dfs","bfs","astar","s","reset","exit"};
int i, j,x,y;
int it, jt;
Clock c;
void init()
{
	start_node = 0;
	target_node = 0;
	start = 0;
	draw = 0;
	dfs = 1;
	bfs = 0;
	astar = 0;
	erase = 0;
	i = 0, j = 0; x = 0; y = 0;
	it = 49, jt = 95;
	while (s.empty() == 0)
		s.pop();
	while (q.empty() == 0)
		q.pop();
	while (pq.empty() == 0)
		pq.pop();
	path.clear();
	path[{0, 0}] = { -1,-1 };
	s.push({ i, j });
	q.push({ i,j });
	pq.push({ 0,{i,j} });
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 96; j++)
		{
			r[i][j].setSize(Vector2f(19.f, 19.f));
			r[i][j].setFillColor(Color::Blue);
			r[i][j].setPosition(j * 20, i * 20+80);
		}
	}
	r[i][j].setFillColor(Color::Black);
	r[it][jt].setFillColor(Color::Black);
	for (int i = 0; i < 8; i++)
	{
		menu[i].setSize(Vector2f(220.f,80.f));
		menu[i].setPosition(10+i * 240,0);
	}
	for (int i = 0; i < 8; i++)
	{
		t[i].loadFromFile(buttons[i] + ".png");
		menu[i].setTexture(&t[i]);
	}
	t[2].loadFromFile("dfst.png");
}
int main()
{
	RenderWindow w(VideoMode(1920,1080), "path visualizer", Style::Fullscreen);
	Event e;
	init();
	while (w.isOpen())
	{
		if (start==1 && bfs==1)
		{
			if (q.empty() == 0 && !(i == it && j == jt - 1) && !(i == it && j == jt + 1) && !(i == it + 1 && j == jt) && !(i == it - 1 && j == jt))
			{
				i = q.front().first;
				j = q.front().second;
				q.pop();
				if (r[i][j].getFillColor() != Color::Red)
				{
					if (r[i][j].getFillColor() == Color::Green)
						r[i][j].setFillColor(Color::Magenta);
					if (j > 0 && r[i][j - 1].getFillColor() == Color::Blue)
					{
						r[i ][j-1].setFillColor(Color::Green);
						q.push({ i, j - 1 });
						path[{i, j - 1}] = {i, j};
					}
					if (i > 0 && r[i - 1][j].getFillColor() == Color::Blue)
					{
						r[i - 1][j].setFillColor(Color::Green);
						q.push({ i - 1, j });
						path[{i-1, j}] = {i, j};
					}
					if (j < 95 && r[i][j + 1].getFillColor() == Color::Blue)
					{
						r[i ][j+1].setFillColor(Color::Green);
						q.push({ i , j + 1 });
						path[{i, j + 1}] = {i, j};
					}
					if (i < 49 && r[i + 1][j].getFillColor() == Color::Blue)
					{
						r[i + 1][j].setFillColor(Color::Green);
						q.push({ i + 1, j });
						path[{i+1, j}] = {i, j};
					}
				}
			}
			else
			{
				if (q.empty() == 0)
				{
					int a = i, b = j;
					while (a != -1 && b != -1)
					{
						int a1 = a, b1 = b;
						a = path[{a1, b1}].first;
						b = path[{a1, b1}].second;
						if (a != -1 && b != -1)
							r[a1][b1].setFillColor(Color::Yellow);
					}
				}
			}
		}
		if (start == 1 && dfs == 1)
		{
			if (s.empty() == 0 && !(i == it && j == jt - 1) && !(i == it && j == jt+1) && !(i == it+1 && j == jt) && !(i == it-1 && j == jt))
			{
				i = s.top().first;
				j = s.top().second;
				s.pop();
				if (r[i][j].getFillColor() != Color::Red)
				{
					if(r[i][j].getFillColor() == Color::Blue)
						r[i][j].setFillColor(Color::Magenta);
					if (j > 0 && r[i][j - 1].getFillColor() == Color::Blue)
					{
						s.push({ i, j - 1 });
						path[{i, j - 1}] = { i, j };
					}
					if (i > 0 && r[i - 1][j].getFillColor() == Color::Blue)
					{
						s.push({ i - 1, j });
						path[{i - 1, j}] = { i, j };
					}
					if (j < 95 && r[i][j + 1].getFillColor() == Color::Blue)
					{
						s.push({ i , j + 1 });
						path[{i, j + 1}] = { i, j };
					}
					if (i < 49 && r[i + 1][j].getFillColor() == Color::Blue)
					{
						s.push({ i + 1, j });
						path[{i + 1, j}] = { i, j };
					}
				}
			}
			else
			{
				if (s.empty() == 0)
				{
					int a = i, b = j;
					while (a != -1 && b != -1)
					{
						int a1 = a, b1 = b;
						a = path[{a1, b1}].first;
						b = path[{a1, b1}].second;
						if (a != -1 && b != -1)
							r[a1][b1].setFillColor(Color::Yellow);
					}
				}
			}
		}
		if (start == 1 && astar == 1)
		{
			if (pq.empty() == 0 && !(i == it && j == jt - 1) && !(i == it && j == jt + 1) && !(i == it + 1 && j == jt) && !(i == it - 1 && j == jt))
			{
				i = pq.top().second.first;
				j = pq.top().second.second;
				pq.pop();
				if (r[i][j].getFillColor() != Color::Red)
				{
					if (r[i][j].getFillColor() == Color::Green)
						r[i][j].setFillColor(Color::Magenta);
					if (i < 49 && r[i + 1][j].getFillColor() == Color::Blue)
					{
						r[i + 1][j].setFillColor(Color::Green);
						path[{i + 1, j}] = { i, j };
						pq.push({1.1*(abs(i + 1 - it) + abs(j - jt)) + abs(i + 1 - x) + abs(j - y),{ i + 1, j } });
					}
					if (j < 95 && r[i][j + 1].getFillColor() == Color::Blue)
					{
						r[i][j+1].setFillColor(Color::Green);
						path[{i, j + 1}] = { i, j };
						pq.push({1.1*(abs(i - it) +abs(j+1 - jt)) + abs(i  - x) + abs(j+1 - y),{ i , j + 1 } });
					}
					if (i > 0 && r[i - 1][j].getFillColor() == Color::Blue)
					{
						r[i - 1][j].setFillColor(Color::Green);
						path[{i - 1, j}] = { i, j };
						pq.push({1.1*(abs(i - 1 - it) +abs(j - jt))+abs(i-1-x)+abs(j-y),{ i - 1, j } });
					}
					if (j > 0 && r[i][j - 1].getFillColor() == Color::Blue)
					{
						r[i ][j-1].setFillColor(Color::Green);
						path[{i, j - 1}] = { i, j };
						pq.push({1.1*(abs(i  - it) + abs(j -1- jt)) + abs(i  - x) + abs(j-1 - y),{ i, j - 1 } });
					}
				}
			}
			else
			{
				if (pq.empty() == 0)
				{
					int a = i, b = j;
					while (a != -1 && b != -1)
					{
						int a1 = a, b1 = b;
						a = path[{a1, b1}].first;
						b = path[{a1, b1}].second;
						if (a != -1 && b != -1)
							r[a1][b1].setFillColor(Color::Yellow);
					}
				}
			}
		}
		while (w.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				w.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.y >= 80 && start==0)
				{
					if (start_node == 0 && target_node == 0)
					{
						if (e.mouseButton.button == Mouse::Left)
						{
							draw = 1; 
							if(r[(e.mouseButton.y / 20) - 4][e.mouseButton.x / 20].getFillColor()!=Color::Black)
							r[(e.mouseButton.y / 20) - 4][e.mouseButton.x / 20].setFillColor(Color::Red);
						}
						else if (e.mouseButton.button == Mouse::Right)
						{
							erase = 1; 
							if (r[(e.mouseButton.y / 20) - 4][e.mouseButton.x / 20].getFillColor() != Color::Black)
							r[(e.mouseButton.y / 20) - 4][e.mouseButton.x / 20].setFillColor(Color::Blue);
						}
					}
					else if(start_node==1 && r[(e.mouseButton.y / 20) - 4][e.mouseButton.x / 20].getFillColor()!=Color::Black)
					{
						r[i][j].setFillColor(Color::Blue);
						i = (e.mouseButton.y / 20) - 4;
						j = e.mouseButton.x / 20;
						r[i][j].setFillColor(Color::Black);
						while (s.empty() == 0)
							s.pop();
						s.push({ i,j });
						while (q.empty() == 0)
							q.pop();
						q.push({ i,j });
						while (pq.empty() == 0)
							pq.pop();
						pq.push({0,{i,j}});
						path.clear();
						path[{i, j}] = { -1,-1 };
						x = i;
						y = j;
					}
					else if (target_node == 1 && r[(e.mouseButton.y / 20) - 4][e.mouseButton.x / 20].getFillColor() != Color::Black)
					{
						r[it][jt].setFillColor(Color::Blue);
						it = (e.mouseButton.y / 20) - 4;
						jt = e.mouseButton.x / 20;
						r[it][jt].setFillColor(Color::Black);
					}
				}
				else
				{
					if (e.mouseButton.x >= 10 && e.mouseButton.x <= 230 && start==0)
					{
						if (start == 0)
						{
							if (start_node == 0)
								t[0].loadFromFile("startt.png");
							else
								t[0].loadFromFile("start.png");
							start_node = !start_node;
							target_node = 0;
							t[1].loadFromFile("end.png");
						}
					}
					if (e.mouseButton.x >= 250 && e.mouseButton.x <= 470 && start==0)
					{
						if (start == 0)
						{
							if (target_node == 0)
								t[1].loadFromFile("endt.png");
							else
								t[1].loadFromFile("end.png");
							target_node = !target_node;
							start_node = 0;
							t[0].loadFromFile("start.png");
						}
					}
					if (e.mouseButton.x >= 490 && e.mouseButton.x <= 710 && start==0)
					{
						if (start == 0)
						{
							t[2].loadFromFile("dfst.png");
							t[3].loadFromFile("bfs.png");
							t[4].loadFromFile("astar.png");
							dfs = 1;
							bfs = 0;
							astar = 0;
						}
					}
					if (e.mouseButton.x >= 730 && e.mouseButton.x <= 950 && start==0)
					{
						if (start == 0)
						{
							t[2].loadFromFile("dfs.png");
							t[3].loadFromFile("bfst.png");
							t[4].loadFromFile("astar.png");
							bfs = 1;
							dfs = 0;
							astar = 0;
						}
					}
					if (e.mouseButton.x >= 970 && e.mouseButton.x <= 1190)
					{
						if (start == 0)
						{
							t[2].loadFromFile("dfs.png");
							t[3].loadFromFile("bfs.png");
							t[4].loadFromFile("astart.png");
							bfs = 0;
							dfs = 0;
							astar = 1;
						}
					}
					if (e.mouseButton.x >= 1210 && e.mouseButton.x <= 1430)
					{
						t[5].loadFromFile("st.png");
						start = 1;
					}
					if (e.mouseButton.x >= 1450 && e.mouseButton.x <= 1670)
					{
						init();
					}
					if (e.mouseButton.x >= 1690 && e.mouseButton.x <= 1910)
					{
						w.close();
					}
				}
			}
			if (e.type == Event::MouseButtonReleased && start == 0)
			{
				if (e.mouseButton.button == Mouse::Left)
					draw = 0;
				else if (e.mouseButton.button == Mouse::Right)
					erase = 0;
			}
			if (e.type == Event::MouseMoved && start == 0)
			{
				if (e.mouseMove.y >= 80)
				{	
					if (draw == 1 && r[(e.mouseMove.y / 20) - 4][e.mouseMove.x / 20].getFillColor()!=Color::Black)
						r[(e.mouseMove.y / 20) - 4][e.mouseMove.x / 20].setFillColor(Color::Red);
					if (erase == 1 && r[(e.mouseMove.y / 20) - 4][e.mouseMove.x / 20].getFillColor() != Color::Black)
						r[(e.mouseMove.y / 20) - 4][e.mouseMove.x / 20].setFillColor(Color::Blue);

				}
			}
		}
		w.clear(Color::White);
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 96; j++)
			{
				w.draw(r[i][j]);
			}
		}
		for (int i = 0; i < 8; i++)
		{
			w.draw(menu[i]);
		}
		w.display();
	}
	return 0;
}
