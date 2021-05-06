#include<stdio.h>
#include<queue>
#include<string.h>
#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

const int maxn = 10000;

int f, s, g, u, d;
int flag, step;

int vis[maxn];
int temp = 0;
int order[] = { 0 };

struct Node {
	int position;
	int nodeStep;
};
queue<Node> q;

bool errorCode(int a, int b, int c, int f)
{

	for (int i = 0; i < f; i++)
	{
		if ((c + i * b) % a == 0)
			return true;
	}

	return false;
}

void bfs(int s)
{


	Node now, next;
	now = (Node){ s, 0 };
	int count = 0;
	while (!q.empty()) q.pop();
	q.push(now);

	memset(vis, 0, sizeof(vis));
	vis[s] = 1;

	while (!q.empty())
	{
		now = q.front(); q.pop();

		for (int i = 1; i <= 2; i++)
		{
			if (i == 1) 
			{
				next.position = now.position + u;
			}
			if (i == 2) 
			{
				next.position = now.position - d;	
			}

			if (next.position < 1 ) continue;
			if (next.position > f) continue;

			if (!vis[next.position])
			{
				next.nodeStep = now.nodeStep + 1;
				if (temp < next.nodeStep)
				{

					order[count] = next.position;
					count++;

					temp = next.nodeStep;
				}
				q.push(next);
				if (next.position == g)
				{
					flag = 1;
					step = next.nodeStep;
					return;
				}
			}
		}
	}
	return;
}
int main()
{


	while (scanf("%d%d%d%d%d", &f, &s, &g, &u, &d) != EOF)
	{
		if (g > s)
		{
			if (u == 0)
			{
				printf("use the stairs\n");
				continue;
			}
			if (!errorCode(u, d, g - s, f))
			{
				printf("use the stairs\n");
				continue;
			}
		}
		else
		{
			if (d == 0 && g != s)
			{
				printf("use the stairs\n");
				continue;
			}
			if (!errorCode(d, u, s - g, f))
			{
				printf("use the stairs\n");
				continue;
			}
		}


		if (s == g)
		{
			printf("%d\n", s);
			printf("totally 0 steps\n");
			continue;
		}
		else if (g > f || g < 0)
		{
			printf("not meet requirement");
		}

		flag = 0;

		bfs(s);
		if (flag) {
			printf("%d\n", s);
			for (int i = 0; i < step; i++)
			{
				if (i != step - 1)
					printf("%d\n", order[i]);
				else
					printf("%d\n", g);
			}
			printf("totally %d steps\n", step);
		}
		else
			printf("use the stairs\n");
	}
	return 0;

}
