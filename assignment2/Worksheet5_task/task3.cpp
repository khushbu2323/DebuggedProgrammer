#include <cctype>
#include <string>
#include <iostream>

using namespace std;

void SubstitutionEncryption(char * plaintText, unsigned int EncryptionKey) {
	for (int i = 0; plaintText[i] != 0; i++) {
		if (plaintText[i] == ' ')
			continue;
		char InitialLetter = islower(plaintText[i]) ? 'a' : 'A';
		unsigned int
			AlphaOffsetKey = plaintText[i] - InitialLetter,
			NewAlphaOffsetKey = AlphaOffsetKey+EncryptionKey;
		plaintText[i] = InitialLetter + NewAlphaOffsetKey % 26;
	}
}

void SubstitutionDecryption(char * EncryptedText, unsigned int DecryptionKey) {
	for (int i = 0; EncryptedText[i] != 0; i++) {
		if (EncryptedText[i] == ' ')
			continue;
		
		char InitialLetter = islower(EncryptedText[i]) ? 'a' : 'A';
		unsigned int AlphaOffsetKey = EncryptedText[i] - InitialLetter;
		int NewAlphaOffsetKey = AlphaOffsetKey - DecryptionKey;
		
		if (NewAlphaOffsetKey < 0) {
			NewAlphaOffsetKey += 26;
		}
		
		EncryptedText[i] = InitialLetter + (NewAlphaOffsetKey % 26);
	}
}
int main() {
    string plaintText = "acbdefghijklmnopqrstuvwxyz";
	unsigned int EncryptionKey;
	
	cout << "Enter Plaint text"<<endl;
	getline(cin, plaintText);
	cout << "Enter Encryption key "<<endl;
	cin >> EncryptionKey ;
	
	cout << "Encrypted Text of : \""<< plaintText.c_str();
	SubstitutionEncryption(const_cast<char*>(plaintText.c_str()), EncryptionKey);
	cout << "\" is : \"" << plaintText << "\"" << endl;
	
	cout << "Decrypted Text of : \"" << plaintText.c_str();
	SubstitutionDecryption(const_cast<char*>(plaintText.c_str()), EncryptionKey);
	cout << "\" is: \"" << plaintText << "\"" << endl;
	return 0;
}