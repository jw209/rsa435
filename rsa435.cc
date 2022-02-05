// You need to complete this program for the first part of your first project.

// Standard libraries
#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"
#include "string"

// function declarations
BigUnsigned generateProbablePrime(int bits);
bool fermateTest(BigUnsigned, BigUnsigned);
BigUnsigned producePrime(int bits);
BigUnsigned calculatePhi(BigUnsigned, BigUnsigned);
BigUnsigned calculateD(BigUnsigned&, BigUnsigned);

int main(){
   
   srand(time(0));
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

      // produce to prime numbers and store them on two sepearate lines of a file 
      std::ofstream ostrm;
      ostrm.open("p_q.txt");
      std::string p_string, q_string;
      BigUnsigned p, q, n, e, d, phi;
      ostrm << producePrime(512) << "\n";
      ostrm << producePrime(512);
      ostrm.close();

      // open p_q.txt and extract p and qto calculate n
      std::ifstream istrm("p_q.txt");
      getline(istrm, p_string);
      p = stringToBigUnsigned(p_string);
      getline(istrm, q_string);
      q = stringToBigUnsigned(q_string);
      n = p * q;

      // get phi and d
      phi = calculatePhi(p, q);
      d = calculateD(e, phi);

      /* for testing purposes
      BigUnsigned x(4289), y
      std::cout << "X value is: " << x << std::endl;
      y = modexp(x, e, n);
      std::cout << "cipher text is: " << y << std:: endl;
      std::cout << "After decyphering: " << modexp(y, d, n) << std::endl;
      */

      // saving e_n and d_n
      ostrm.open("e_n.txt", std::ios::binary);
      if (ostrm.is_open()) {
         ostrm << e << "\n" << n;
      } else {
         std::cout << "error creating e_n.txt file" << std::endl;
      }
      ostrm.close();

      ostrm.open("d_n.txt", std::ios::binary);
      if (ostrm.is_open()) {
         ostrm << d << "\n" << n;
      } else {
         std::cout << "error creating d_n.txt file" << std::endl;
      }
      ostrm.close();

      std::cout << "successfully generated key pairs" << std::endl;

	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl; 
	}
	return 0;
}

// returns d value
BigUnsigned calculateD(BigUnsigned &e, BigUnsigned phi) {
   while (1) {
      BigUnsigned x = producePrime(13);
      BigUnsigned y;
      if (modinv(x, phi) != 0) {
         y = modinv(x, phi);
         e = x;
         return y;
      }
   }
}

// returns phi value
BigUnsigned calculatePhi(BigUnsigned p, BigUnsigned q) {
   BigUnsigned phi = (p-1) * (q-1);
   return phi;
}

// returns random odd numbers
BigUnsigned generateProbablePrime(int bits) { 
   BigUnsigned oddNumber;
   oddNumber.setBit(0, 1);
   for (int i = 1; i < bits; i++) {
      bool randomBit = rand() % 2;
      oddNumber.setBit(i, randomBit);
   }
   oddNumber.setBit(512, 1);
   return oddNumber;
}

// fermat test true if prime and false otherwise
bool fermatTest(BigUnsigned exp, BigUnsigned probablePrime) {
   if(modexp(2, exp, probablePrime) == 1) return true;
   else return false;
}

//  use generateProbablePrime and fermatTest to create prime numbers
BigUnsigned producePrime(int bits) {
   while(1) {
      BigUnsigned probablePrime(generateProbablePrime(bits));
      if(fermatTest(probablePrime-1, probablePrime) == 1) return probablePrime;
   }
}