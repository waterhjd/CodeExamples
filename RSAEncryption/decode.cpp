#include <iostream>
#include <stdio.h>

using namespace std;

#define ll long long

ll modular_pow(ll base, ll exponent, int modulus)
{
    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
   int a, b, x, y, gcd;
}

int main(int argc, char* argv[])
{
   int e, n;
   string fileName;

   if (argc == 4)
   {
      fileName = argv[1];
      e = atoi(argv[2]);
      n = atoi(argv[3]);
   }

   else
   {
      cout << "Please enter the filename e and n in the following format" << endl;
      cout << "./decode Filename d n" << endl;
      return 0;
   } 
  
  FILE* inputFile;
  FILE* outputFile;
  string eChar="";
  int c;
  inputFile=fopen (fileName.c_str(),"r");
  outputFile= fopen ((fileName+".decoded").c_str(), "w");

  if (inputFile==NULL) perror ("Error opening file");
  else
  {
    do {
      c = fgetc (inputFile);
      if (c != EOF)
      {
         if (c != ' ')
         {
            eChar += c;       
         } else {
            //cout << "eChar = " <<  eChar << endl;
            eChar = (char)modular_pow(stoi(eChar),e,n);
            cout << eChar;
            fprintf(outputFile, eChar.c_str());
            eChar = "";
         }
      }
    } while (c != EOF);
    fclose (inputFile);
    fclose (outputFile);
  }
  cout << endl;

  return 0;
}
