//Wai Phyo
//CS256-EX9
//completed on 08/03/2016

#include "Chromosome.h"

Chromosome::Chromosome(std::string d) : data(d)
{
}

std::string Chromosome::getData() const
{
    return data;
}

Chromosome Chromosome::mutate() const
{	
	std::string temp=data;//new string for new chromosome
	int randomPos = rand() % data.length();
	int randEven = rand() %2;
	if (randEven) // odd
	{
		++temp[randomPos];//increment
		if ( temp[randomPos] > 122 )//bigger than z, go back to a
		{
			temp[randomPos]-= 26;
		}
	}
	else //even
	{
		--temp[randomPos];//decrement
		if ( temp[randomPos] < 97 )//less than a, go back to z
		{
			temp[randomPos]+= 26;
		}
	}
	Chromosome tmepC(temp);	
	return tmepC;
    // implement mutation here

    // your mutate function should randomly choose
    // a character to modify then randomly choose
    // to either increment or decrement it
    // make sure to keep in range of lower-case letters!
}

Chromosome Chromosome::crossover(const Chromosome& c) const
{
	std::string temp=data;
	int randomPos = rand() % data.length();
	for( int a=randomPos; a< data.length(); ++a)
	{
		temp[a]=data[a];
	}
	for( int a=randomPos; a< data.length(); ++a)
	{
		temp[a]=c.data[a];
	}
	Chromosome tmepC(temp);	
	return tmepC;
    // implement crossover here

    // your crossover function should randomly choose
    // an index in the range of the chromosomes
    // then take the first part (up to the index) from *this
    // and the last part (from index to end) from c and
    // concatenate those together then return the result
}

int Chromosome::fitness(const std::string& target) const
{
    // computes fitness by sum of differences of each character
    // smaller is better (0 is perfect)

    int diff = 0;
    for (int i = 0; i < data.size(); i++)
    {
        int change = std::abs(data[i] - target[i]);
        if (change > 13) // handles wrap around for letters
        {
            change = 26 - change;
        }
        diff += change;
    }
    return diff;
}

std::ostream& operator<<(std::ostream& os, const Chromosome& c)
{
    os << c.getData();
    return os;
}
