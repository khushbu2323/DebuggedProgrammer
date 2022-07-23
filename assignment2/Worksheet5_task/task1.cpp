#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void DisplayInitials(const string& StringForInitials)
{
	if (StringForInitials.length() == 0)
		return;
	cout << (char)toupper(StringForInitials[0]);
	for (int i = 1; i < StringForInitials.length() - 1; i++)
		if (StringForInitials[i] == ' ')
			cout << " " << (char)toupper(StringForInitials[i + 1]);
}

// Driver code
int main()
{
	string StringForInitials;
    cout<<"Enter the string to print Initials"<<endl;
    getline(cin,StringForInitials);
    cout<<"Initial of given String"<<endl;
	DisplayInitials(StringForInitials);
	return 0;
}
