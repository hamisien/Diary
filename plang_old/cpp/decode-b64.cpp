#include <iostream>
#include <cstdio>
using namespace std;

int main(void)
{
	while(1){
		cout << "Enter a decoded text: ";

		char decoded[100];
		cin >> decoded;

		// cout << "Encoded to base64: ";
	
		char cmd[150];
		sprintf(cmd, "echo %s | base64 -d", decoded);
		system(cmd);

		cout << endl << endl;
	}
	
	return 0;
}
