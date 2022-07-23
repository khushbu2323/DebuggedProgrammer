#include <iostream>
using namespace std;

string CeaserEncrypt(string plaintext, int shiftingKey)
{
	string Encryptedtext = "";
	for (int i=0;i<plaintext.length();i++)
	{
		
		if (isupper(plaintext[i]))
			Encryptedtext += char(int(plaintext[i]+shiftingKey-65)%26 +65);
	else
		Encryptedtext += char(int(plaintext[i]+shiftingKey-97)%26 +97);
	}
	return Encryptedtext;
}

int main()
{
    string plaintext;
    cout<<"Enter a plain text to enter"<<endl;
    getline(cin,plaintext);
    int shiftingKey;
    cout<<"Enter a key"<<endl;
    cin>>shiftingKey;
	cout << "Plain Text : " << plaintext;
	cout << "\nShift Key: " << shiftingKey;
	cout << "\nEncrypted Text: " << CeaserEncrypt(plaintext, shiftingKey);
	return 0;
}
