/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : igomez1 Ian Gomez
 * Date        : 09/11/18
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens honor system"-igomez1
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit}{
        sieve();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        /**
            returns the amount of primes in the array
        */
        return num_primes_;
    }

    void display_primes() const {
        // displays the primes in a table format
        const int max_prime_width = num_digits(max_prime_), primes_per_row = 80/(max_prime_width+1);
        int primesLeft = primes_per_row;
        int totPrimes = num_primes_;
            for(int i = 0; i <= max_prime_; i++){
                if(is_prime_[i]){
                    cout << setw((num_primes_ > primes_per_row ? max_prime_width : 1)) <<  i  << (totPrimes <= 1 || primesLeft == 1 ? "" : " ");  
                    primesLeft -= 1;
                    totPrimes -= 1;
                    if(primesLeft == 0){
                        cout << endl;
                        primesLeft = primes_per_row;
                    }
                }
            }
            cout << endl;
        }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;
    int count_num_primes() const {
        /**
            Countes the amount of primes in the is_prime_ array
        */
        int primeCount = 0;
        for(int i = 0; i < limit_+1; i++){
            primeCount += is_prime_[i];
        }
        return primeCount;
    }

    int num_digits(int num) const {
        /**
            returns the amount of digits in the inputted number
        */
        int digCount = 1;
        while(num > 10){
            num = num / 10;
            digCount++;
        }
        return digCount;
    }

    void sieve() {
        /**
            takes in a limit+1 size array and determines which numbers are prime and which numbers are composite
            also sets the number for num_primes_
        */
        is_prime_[0] = false;
        is_prime_[1] = false;
        for(int i = 2; i < limit_+1 ;i++){
            is_prime_[i] = true;
        }
        int sqrtn = sqrt(limit_+1);
        for(int i = 2; i <= sqrtn;i++){
            if(is_prime_[i]){
                for(int j = i*i; j <= limit_+1; j += i){
                    is_prime_[j] = false;
                }
            }
        }
        for(int i = 2; i < limit_+1 ; i++){
            is_prime_[i] ? max_prime_ = i: max_prime_;
        }
        num_primes_ = count_num_primes();
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    PrimesSieve yeet(limit);
    cout << endl;
    cout << "Number of primes found: " << yeet.num_primes() << endl;
    cout << "Primes up to "<< limit << ":" << endl;
    yeet.display_primes();
    
    // TODO: write code that uses your class to produce the desired output.
    return 0;
}
