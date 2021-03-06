#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> getTokensFromFile(string path)
{
   string myText;
   vector<string> arrayTokens;

   ifstream MyReadFile(path);

   if (MyReadFile.is_open())
   {
      while (getline(MyReadFile, myText))
      {
         arrayTokens.push_back(myText);
      }
      arrayTokens.push_back("$, eof");
      MyReadFile.close();
   }
   else
   {
      cout << "Unable to open file";
   }

   MyReadFile.close();

   return arrayTokens;
}
