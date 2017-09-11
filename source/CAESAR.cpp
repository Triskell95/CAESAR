//============================================================================
// Name        : CAESAR.cpp
// Author      : Thibaut DA SILVA
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

#define CDFT "\033[0m"  //default
#define CBLD "\033[1m"  //bold
#define CBLK "\033[30m" //black
#define CRED "\033[31m" //red
#define CGRN "\033[32m" //green
#define CYLW "\033[33m" //yellow
#define CBLU "\033[34m" //blue

#define C_NB_ALPHA    (26+26)
#define C_NB_CHIFFRE  10
#define C_NB_SYMBOL   33
#define C_MODULO (C_NB_ALPHA+C_NB_CHIFFRE+C_NB_SYMBOL)
#define C_CHAR_BASE ' '


void fnPrintHelp()
{
    cout << endl;
    cout << "Utilisation du programme \"caesar\":" << endl;
    cout << endl;

    cout << "Options:" << endl;
    cout << CBLU;
    cout << "\t-s <string> : string a crypter/decrypter" << endl;
    cout << "\t-c <int>    : cryptage" << endl;
    cout << "\t-d <int>    : decryptage" << endl;
    cout << "\t-i <string> : input_file" << endl;
    cout << "\t-o <string> : output_file" << endl;
    cout << CDFT << endl;

    cout << "Arguments necessaires (au choix):" << endl;
    cout << CBLU;
    cout << "\t-s ou -i" << endl;
    cout << "\t-c ou -d" << endl;
    cout << CDFT << endl;

    cout << "Argument optionnel:" << endl;
    cout << CBLU;
    cout << "\t-o" << endl;
    cout << CDFT << endl;

}

string fnSlurp(ifstream& in) {
    stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

string fnCrypt(string strValue, int iKey)
{
    string strRet = "";

    for(unsigned int i = 0; i < strValue.length(); i++)
    {
        if(strValue[i] >= C_CHAR_BASE and strValue[i] < ( C_CHAR_BASE + C_MODULO ) )
        {
            //printf("%c (%d)\n", strValue[i], strValue[i]);
            char c = (strValue[i] + iKey < C_CHAR_BASE + C_MODULO
                    ? strValue[i] + iKey
                    : (strValue[i] + iKey) - C_MODULO
                    );
            strRet.append(1, c);
        }
        else
        {
            //printf("%c (%d) - else\n", strValue[i], strValue[i]);
            strRet.append(1, strValue[i]);
        }
    }
    return strRet;
}

string fnDecrypt(string strValue, int iKey)
{
    string strRet = "";

    for(unsigned int i = 0; i < strValue.length(); i++)
    {
        if(strValue[i] >= C_CHAR_BASE and strValue[i] < ( C_CHAR_BASE + C_MODULO ) )
        {
            //printf("%c (%d)\n", strValue[i], strValue[i]);
            char c = (strValue[i] - iKey >= C_CHAR_BASE
                    ? strValue[i] - iKey
                    : (strValue[i] - iKey) + C_MODULO
                    );
            strRet.append(1, c);
        }
        else
        {
            //printf("%c (%d) - else\n", strValue[i], strValue[i]);
            strRet.append(1, strValue[i]);
        }
    }
    return strRet;
}


int main(int argc, char* argv[]) {

    //system("clear");
    cout << endl << "  ===== Crypto: Chiffre de Cesar =====" << endl << endl; // prints !!!Hello World!!!

   string strValue = "";
   string strOut = "";
   int iKey = 0;
   bool bStr    = false;
   bool bCrypt  = false;
   bool bDecrypt= false;
   bool bInput  = false;
   bool bOutput = false;

   if(argc < 3)
   {
       cout << CRED << "ERREUR: Pas assez d'arguments..." << CDFT << endl;
       fnPrintHelp();
       exit(1);
   }

   for(int i = 1; i < argc; i++)
   {
       //string a crypter
       if(strcmp(argv[i], "-s") == 0)
       {
           if(bStr or bInput)
           {
               cout << CRED << "ERREUR: '-s' ou '-i' deja utilises !" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
           if(i+1 < argc)
           {
               strValue = argv[i+1];
               bStr = true;
               i++;
           }
           else
           {
               cout << CRED << "ERREUR: Argument manquant avec '-s'" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
       }

       //input_file
       if(strcmp(argv[i], "-i") == 0)
       {
           if(bInput or bStr)
           {
               cout << CRED << "ERREUR: '-s' ou '-i' deja utilises !" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
           if(i+1 < argc)
           {
               std::ifstream ifs(argv[i+1]);
               strValue = fnSlurp(ifs);
               bInput = true;
           }
           else
           {
               cout << CRED << "ERREUR: Argument manquant avec '-i'" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
       }

       //key de cryptage
       if(strcmp(argv[i], "-c") == 0)
       {
           if(bCrypt or bDecrypt)
           {
               cout << CRED << "ERREUR: '-c' ou '-d' deja utilises !" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
           if(i+1 < argc)
           {
               iKey = atoi(argv[i+1]);
               bCrypt = true;
               i++;
           }
           else
           {
               cout << CRED << "ERREUR: Argument manquant avec '-c'" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
       }

       //key de decryptage
       if(strcmp(argv[i], "-d") == 0)
       {
           if(bCrypt or bDecrypt)
           {
               cout << CRED << "ERREUR: '-c' ou '-d' deja utilises !" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
           if(i+1 < argc)
           {
               iKey = atoi(argv[i+1]);
               bDecrypt = true;
               i++;
           }
           else
           {
               cout << CRED << "ERREUR: Argument manquant avec '-d'" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
       }

       //input_file
       if(strcmp(argv[i], "-o") == 0)
       {
           if(bOutput)
           {
               cout << CRED << "ERREUR: '-o' deja utilise !" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
           if(i+1 < argc)
           {
               strOut = argv[i+1];
               bOutput = true;
           }
           else
           {
               cout << CRED << "ERREUR: Argument manquant avec '-o'" << CDFT << endl;
               fnPrintHelp();
               exit(1);
           }
       }

   }

   //cout << "string: " << strValue.c_str() << " - cle: " << iKey << "/" << C_MODULO << endl;
   iKey = iKey % C_MODULO;

   string strResult = "";

   if(bCrypt)
   {
       strResult = fnCrypt(strValue, iKey);
   }
   else if(bDecrypt)
   {
       //strResult = fnCrypt(strValue, C_MODULO - iKey);
       strResult = fnDecrypt(strValue, iKey);
   }
   else
   {
       cout << CRED << "ERREUR: l'argument '-c' ou 'd' n'ont pas ete trouves !" << CDFT << endl;
       fnPrintHelp();
       exit(1);
   }

   if(bOutput)
   {
       ofstream myfile;
       myfile.open (strOut);
       //myfile << strValue;
       myfile << strResult;
       myfile.close();
   }
   else
   {
       if(bCrypt)
       {
           cout << "A crypter  : " << strValue << endl;
       }
       else
       {
           cout << "A decrypter: " << strValue << endl;
       }
       cout << "Cle        : " << iKey << endl;
       cout << "Resultat   : " << strResult << endl;
   }

   cout << endl;

	return 0;
}
