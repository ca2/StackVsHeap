// StackVsHeap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#pragma once

//-------------------------------------------------------------//
// "Malware related compile-time hacks with C++11" by LeFF   //
// You can use this code however you like, I just don't really //
// give a shit, but if you feel some respect for me, please //
// don't cut off this comment when copy-pasting... ;-)       //
//-------------------------------------------------------------//

////////////////////////////////////////////////////////////////////
template <int X> struct EnsureCompileTime {
   enum : int {
      Value = X
   };
};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//Use Compile-Time as seed
#define Seed ((__TIME__[7] - '0') * 1  + (__TIME__[6] - '0') * 10  + \
              (__TIME__[4] - '0') * 60   + (__TIME__[3] - '0') * 600 + \
              (__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000)
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
constexpr int LinearCongruentGenerator(int Rounds) {
   return 1013904223 + 1664525 * ((Rounds > 0) ? LinearCongruentGenerator(Rounds - 1) : Seed & 0xFFFFFFFF);
}
#define Random() EnsureCompileTime<LinearCongruentGenerator(10)>::Value //10 Rounds
#define RandomNumber(Min, Max) (Min + (Random() % (Max - Min + 1)))
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
template <int... Pack> struct IndexList {};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
template <typename IndexList, int Right> struct Append;
template <int... Left, int Right> struct Append<IndexList<Left...>, Right> {
   typedef IndexList<Left..., Right> Result;
};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
template <int N> struct ConstructIndexList {
   typedef typename Append<typename ConstructIndexList<N - 1>::Result, N - 1>::Result Result;
};
template <> struct ConstructIndexList<0> {
   typedef IndexList<> Result;
};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
const char XORKEY = static_cast<char>(RandomNumber(0, 0xFF));
constexpr char EncryptCharacter(const char Character, int Index) {
   return Character ^ (XORKEY + Index);
}

template <typename IndexList> class CXorString;
template <int... Index> class CXorString<IndexList<Index...> > {
private:
   char Value[sizeof...(Index) + 1];
public:
   constexpr CXorString(const char * const String)
      : Value{ EncryptCharacter(String[Index], Index)... } {}

   char * decrypt() {
      for (int t = 0; t < sizeof...(Index); t++) {
         Value[t] = Value[t] ^ (XORKEY + t);
      }
      Value[sizeof...(Index)] = '\0';
      return Value;
   }

   char * get() {
      return Value;
   }
};
#define XorS(X, String) CXorString<ConstructIndexList<sizeof(String)-1>::Result> X(String)
#define XorMember(X, String) CXorString<ConstructIndexList<sizeof(String)-1>::Result> X = String
#define XorString( String ) ( CXorString<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )
////////////////////////////////////////////////////////////////////
//#define XorString( String ) ( CXorString<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )

#pragma pack(push, 1)

class teste
{
public:

   int m_i1;
   int m_i2;
   int m_i3;
   int * m_pPointer;
   const char m_sz[6] = "teste";
   const char *m_psz = "teste";
   XorMember(m_szEncrypted, "StringQueNaoSei");


   teste()
   {

      m_i1 = 0xEFCDAB89;
      m_i2 = 0xABABABAB;
      m_i3 = -1; // 0xffffffff = 0 - 1
      m_pPointer = nullptr;

   }


};


#pragma pack (pop)

void print_int(int i)
{

   printf("\n\nEsse eh um inteiro. Estou printando o conteuhdo em decimal: %d\n\n", i);

   printf("\n\nEsse eh um inteiro. Estou printando o conteuhdo em hexadecimal: %08x\n\n", i);

}


void print_int_pointer(int * pint)
{

   print_int(*pint);

   

}

void print(const char * psz)
{

   printf("%s", psz);

}

int main()
{

   auto sz1 = "String1";

   teste teste;

   print(XorString(teste.m_szEncrypted));

   ::teste * pteste = new ::teste;

   int & uminteiro = teste.m_i1;
   int & outrointeiro = teste.m_i2;


   char * psz = (char *) teste.m_sz;

   psz[4] = 'a';

   char * psz3 = (char *)teste.m_psz;

   psz3[4] = 'a';

   int * p = (int *) 0x002f5607;

   *p = 12;

   print_int_pointer(&uminteiro);
   print_int_pointer(&outrointeiro);

   uminteiro = 1;

   print_int_pointer(&teste.m_i1);

   int * p1 = &teste.m_i1;
   
   p1[2] = 3;

   p1++;

   *p1 = 4;

   p1++;

   p1[-1] = 5;
   
   int copia_de_i1 = *p1;

   ::teste copia_de_teste = teste;



   ::teste * ptest2_referenciando_teste = &teste;

   int * p2 = &ptest2_referenciando_teste->m_i2;

   *p2 = 2;


   p2[0] = 3;

   int copia_de_inteiro = *p1;

   print_int(copia_de_inteiro);

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
