// StackVsHeap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


class teste
{
public:

   int m_i1;
   int m_i2;


   teste()
   {

      m_i1 = 0xEFCDAB89;
      m_i2 = 0xABABABAB;

   }


};

void print_int(int i)
{

   printf("\n\nEsse eh um inteiro. Estou printando o conteuhdo em decimal: %d\n\n", i);

   printf("\n\nEsse eh um inteiro. Estou printando o conteuhdo em hexadecimal: %08x\n\n", i);

}


void print_int_pointer(int * pint)
{

   print_int(*pint);

}

int main()
{

   teste teste;

   ::teste * pteste = new ::teste;

   int & uminteiro = teste.m_i1;
   int & outrointeiro = teste.m_i2;

   print_int_pointer(&uminteiro);
   print_int_pointer(&outrointeiro);

   uminteiro = 1;

   print_int_pointer(&teste.m_i1);

   int * p1 = &teste.m_i1;

   
   
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
