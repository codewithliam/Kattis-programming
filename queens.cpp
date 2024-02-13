#include <string>
#include <iostream>
#include "queens.h"
using namespace std


int main() {
	pos queens[8];
	int a = 0;
	char ch = '';

for(int i=0; i<8; i++)
{
	for(int j=0; j<8; j++) {
		cin >> ch;
		if(ch == '*') {
			pos pos_struct;
			pos_struct.y = i;
			pos_struct.x = j;
			queens[a] = pos_struct;
			a++;
		}
	}
}

int **p;
p = new int*[3];
	for(int j=0; j<8; j++)
	{
		pos_struct = queens[j];
		p[0] =

	}
}


for(int i=0; i<8)
return 0;
}
