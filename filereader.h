#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> readFile(string path )
{
   string myText;
   vector <string> arrayTokens;

  
   ifstream MyReadFile(path);


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

 
   MyReadFile.close();

   return arrayTokens;
}
