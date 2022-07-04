#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
   string myText;
   vector <string> arrayTokens;

   // Read from the text file
   ifstream MyReadFile("tokens.txt");
// read the file and print each line 

   if (MyReadFile.is_open())
   {
      while (getline(MyReadFile, myText))
      {
        arrayTokens.push_back(myText);
      }
      MyReadFile.close();
   }
   else
   {
      cout << "Unable to open file";
   }

   // Close the file
   MyReadFile.close();

   cout << "The tokens are: " << endl;
   for (int i = 0; i < arrayTokens.size(); i++)
   {
      cout << arrayTokens[i] << endl;
   }
}
