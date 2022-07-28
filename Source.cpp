#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <stack>
#include <queue>
using namespace sf;
using namespace std;
//constants
#define scr_width 1920
#define scr_height 1080
bool start;
bool draw;
bool dfs;
bool bfs;
bool astar;
bool start_node;
bool target_node;
bool erase;
RectangleShape r[50][96];
RectangleShape menu[6];
queue<pair<int, int>>q;
stack<pair<int, int>>s;
map<pair<int,int>, pair<int, int>>path;
Texture t[6];
string buttons[5] = { "start","target","dfs","bfs","exit" };
int i, j,a,b;
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
	i = 0, j = 0;
	it = 49, jt = 95;
	while (s.empty() == 0)
		s.pop();
	while (q.empty() == 0)
		q.pop();
	path.clear();
	path[{0, 0}] = { -1,-1 };
	s.push({ i, j });
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
	for (int i = 0; i < 6; i++)
	{
		menu[i].setSize(Vector2f(300.f,80.f));
		menu[i].setPosition(10+i * 320,0);
	}
	for (int i = 0; i < 5; i++)
	{
		t[i].loadFromFile(buttons[i] + ".png");
		menu[i].setFillColor(Color::White);
		menu[i].setTexture(&t[i]);
	}
	menu[2].setFillColor(Color::Black);
}
int main()
{
	RenderWindow w(VideoMode(scr_width, scr_height), "path visualizer", Style::Fullscreen);
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
				if (r[i][j].getFillColor() == Color::Blue || r[i][j].getFillColor() == Color::Black)
				{
					if (r[i][j].getFillColor() == Color::Blue)
						r[i][j].setFillColor(Color::Magenta);
					if (j > 0 && r[i][j - 1].getFillColor() == Color::Blue)
					{
						q.push({ i, j - 1 });
						path[{i, j - 1}] = {i, j};
					}
					if (i > 0 && r[i - 1][j].getFillColor() == Color::Blue)
					{
						q.push({ i - 1, j });
						path[{i-1, j}] = {i, j};
					}
					if (j < 95 && r[i][j + 1].getFillColor() == Color::Blue)
					{
						q.push({ i , j + 1 });
						path[{i, j + 1}] = {i, j};
					}
					if (i < 49 && r[i + 1][j].getFillColor() == Color::Blue)
					{
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
				if (r[i][j].getFillColor() == Color::Blue || r[i][j].getFillColor() == Color::Black)
				{
					if(r[i][j].getFillColor() == Color::Blue)
						r[i][j].setFillColor(Color::Magenta);
					if (j > 0 && r[i][j - 1].getFillColor() == Color::Blue)
					{
						s.push({ i, j - 1 });
						path[{i, j - 1}] = { i,j };
					}
					if (i > 0 && r[i - 1][j].getFillColor() == Color::Blue)
					{
						s.push({ i - 1, j });
						path[{i-1, j}] = { i,j };
					}
					if (j < 95 && r[i][j + 1].getFillColor() == Color::Blue)
					{
						s.push({ i , j + 1 });
						path[{i, j + 1}] = { i,j };
					}
					if (i < 49 && r[i + 1][j].getFillColor() == Color::Blue)
					{
						s.push({ i + 1, j });
						path[{i+1, j}] = { i,j };
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
					else if(start_node==1)
					{
						r[i][j].setFillColor(Color::Blue);
						i = (e.mouseButton.y / 20) - 4;
						j = e.mouseButton.x / 20;
						r[i][j].setFillColor(Color::Black);
						if (dfs == 1)
						{
							while (s.empty() == 0)
								s.pop();
							s.push({ i,j });
						}
						if (bfs == 1)
						{
							while (q.empty() == 0)
								q.pop();
							q.push({ i,j });
						}
						path.clear();
						path[{i, j}] = { -1,-1 };
					}
					else if (target_node == 1)
					{
						r[it][jt].setFillColor(Color::Blue);
						it = (e.mouseButton.y / 20) - 4;
						jt = e.mouseButton.x / 20;
						r[it][jt].setFillColor(Color::Black);
					}
				}
				else
				{
					if (e.mouseButton.x >= 10 && e.mouseButton.x <= 310 && start==0)
					{
						if (start == 0)
						{
							if (start_node == 0)
								menu[0].setFillColor(Color::Black);
							else
								menu[0].setFillColor(Color::White);
							start_node = !start_node;
							target_node = 0;
							menu[1].setFillColor(Color::White);
						}
					}
					if (e.mouseButton.x >= 330 && e.mouseButton.x <= 620 && start==0)
					{
						if (start == 0)
						{
							if (target_node == 0)
								menu[1].setFillColor(Color::Black);
							else
								menu[1].setFillColor(Color::White);
							target_node = !target_node;
							start_node = 0;
							menu[0].setFillColor(Color::White);
						}
					}
					if (e.mouseButton.x >= 650 && e.mouseButton.x <= 950 && start==0)
					{
						if (start == 0)
						{
							menu[2].setFillColor(Color::Black);
							menu[3].setFillColor(Color::White);
							dfs = 1;
							bfs = 0;
						}
					}
					if (e.mouseButton.x >= 970 && e.mouseButton.x <= 1270 && start==0)
					{
						if (start == 0)
						{
							menu[3].setFillColor(Color::Black);
							menu[2].setFillColor(Color::White);
							bfs = 1;
							dfs = 0;
							q.push({i,j});
						}
					}
					if (e.mouseButton.x >= 1290 && e.mouseButton.x <= 1590)
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
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::R)
				{
					init();
				}
				if (e.key.code == Keyboard::Enter)
				{
					if(bfs==1 || dfs==1)
						start = 1;
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
		for (int i = 0; i < 6; i++)
		{
			w.draw(menu[i]);
		}
		w.display();
	}
	return 0;
}