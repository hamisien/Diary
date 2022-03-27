#include <iostream>
#include <cstdio>
using namespace std;

int main(void)
{
	while(1){
		cout << "Enter a plain text: ";

		char plain[100];
		cin >> plain;

		// cout << "Encoded to base64: ";
	
		char cmd[150];
		sprintf(cmd, "echo %s | base64", plain);
		system(cmd);

		cout << endl << endl;
	}
	
	return 0;
}
