#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

void ReadFile(string&, bool&);
void findKey(string);
void OutputToFile(string, int);

int main()
{
	string text;
	bool file = true;
	int inputKey;

	ReadFile(text, file);
	if (file)
	{
		cout << "Original Text: \n" << text << "\n\n";
		findKey(text);

		cout << "Scroll through the above ciphers to find the key (the key will be directly above the text that makes sense)." << endl;
		cout << "Enter the key: ";
		cin >> inputKey;

		OutputToFile(text, inputKey);
	}
	else
	{
		cout << "No ciphertext to decrypt.";
	}
	return 0;
}
/*
ReadFile function accepts string and bool variables both by reference.
Function attempts to open file, if file fails to open false is stored in file
and function ends. If file opens function uses a while loop to store text in string.
*/
void ReadFile(string &text, bool &file)
{
	ifstream in;
	in.open("cipher.txt");
	if (!in)
	{
		file = false;
		return;
	}
	while (in.good())
	{
		getline(in, text);		//store text in file
	}
	in.close();
}
/*Findkey function accepts a string and uses a nested for loop to determine case and
to add 1-25 to the achii value of each alphabet character. If the achii value goes passed 
aschii value for z it will loop around and add the difference to a aschii value. 
After running user can scroll through the options and select the key corresponding 
to the coherent text.*/
void findKey(string STR)
{
	int temp;
	int strLen = STR.length();

	for (int k = 1; k < 26; k++)
	{
		
		cout << "Key = " << k << "\n\n";
		for (int i = 0; i < strLen; i++)
		{
			if (STR[i] < 123 && STR[i] > 96)
			{
				//cout << text[i] + k;
				temp = int(STR[i]);		//typecast
				temp += k;
				if (temp > 122)
				{
					temp = (temp - 122) + 96;
				}
				cout << char(temp);		//typecast
			}
			else if (STR[i] < 91 && STR[i] >= 65)
			{
				temp = int(STR[i]);		//typecast
				temp += k;
				if (temp > 90)
				{
					temp = (temp - 91) + 65;
				}

				cout << char(temp);		//typecast
			}
			else
			{
				cout << STR[i];
			}
		}
		cout << "\n\n";
	}
}
/*OutputToFile function accepts a string to decrypt and a key. It uses a for
loop to add the key to all alphabet characters and if statements to detect upper 
and lower case characters. After the case is detected function adds key to aschii
value looping back around to a if z is reached and outputs to file.
***This function exports case sensitive****/
void OutputToFile(string text, int inputKey)
{
	ofstream out;
	int temp, strLen = text.length();
	out.open("decrypt.txt");
	for (int i = 0; i < strLen; i++)
	{
		if (text[i] < 123 && text[i] > 96)
		{
			//cout << text[i] + k;
			temp = int(text[i]);			//typecast to temp 
			temp += inputKey;
			if (temp > 122)
			{
				temp = (temp - 122) + 96;
			}

			out << char(temp);				//trypecast temp to char and output to file
		}
		else if (text[i] < 91 && text[i] >= 65)
		{
			temp = int(text[i]);		//typecast
			temp += inputKey;
			if (temp > 90)
			{
				temp = (temp - 91) + 65;
			}

			out << char(temp);		//typecast
		}
		else
		{
			out << text[i];
		}
	}
	out.close();
	cout << "\nThe plaintext has been exported to a text file.\n";
}