//Wai Phyo
//CS256-EX9
//completed on 08/03/2016

#include "Chromosome.h"

Chromosome randomChromosome(int size)
{
    std::ostringstream sout;
    for (int i = 0; i < size; i++)
    {
        sout << (char) ((rand() % 26) + 97);
    }
    return Chromosome(sout.str());
}
Chromosome runGA(std::string target, int popSize, double mr, double cr)
{
	std::vector<Chromosome> myPop;// main population
	for(int a = 0; a< popSize; ++a)//loop and fill with chromosomes
	{
		myPop.push_back(randomChromosome(target.length()));
	}
	int counter = 1;//counter for display
	while (true)//do till true
	{
		std::cout<<"iteration: "<<counter<<std::endl;//display
		std::vector<Chromosome> tempPop;//temp population (twice as large) half of them is always murdered mercilessly
		for(int a = 0; a< (popSize*2); ++a)//fill temp population
		{
			int randNum = rand() % popSize;//get random chromosome 
			double randRate = (rand() % 100 ) / 100.00;//get percentage rate
			//std::cout<<randNum<<" "<<randRate<<"\n";
			if ( randRate <= cr )// become a chimera (cross over)
			{
				int randTemp=rand() % popSize; // find random species to cross over
				tempPop.push_back(myPop[randNum].crossover(myPop[randTemp]));//save new species
				//std::cout<<randTemp<<" "<<tempPop.back();
			}
			if ( randRate <= mr )//become an X man (mutated)
			{			
				tempPop.push_back(myPop[randNum].mutate());//save new species
				//std::cout<<tempPop.back()<<"\n";
			}
			else//a useless human (nth happens)
			{
				tempPop.push_back(myPop[randNum]);//save original species
			}
		}
		//now sort by ideal creature 
		auto cmp=[&](const Chromosome& c1, const Chromosome& c2) {return c1.fitness(target) < c2.fitness(target);};
		std::sort( tempPop.begin(), tempPop.end(), cmp );
		for(int a = 0; a< popSize; ++a)//keep the 1st half
		{
			myPop[a]=tempPop[a];
		}

		std::cout<<myPop[0]<<std::endl; // best chromosome so far
		if(myPop[0].getData() == target)//found ideal chromosome. 
		{
			return myPop[0];//sayonara infinite loop..
		}
		++counter;
	}
    // implement genetic algorithm here

    // use a vector<Chromosome> for the population
    // I recommend using STL algorithms such as std::sort

    // remember, the GA is a loop until you find a chromosome
    // of fitness 0

    // on each iteration, you should be generating a new population
    // of twice the size of popSize, filling it with chromosomes
    // that have been mutated, crossed, and/or copied based on
    // the probabilities given by mr and cr
    // then sort it and keep only the best half as the population
    // for the next iteration
    // when you find a chromosome of fitness 0, you have finished and
    // you should return it
}

int main(int argc, char **argv)
{
    srand(time(0));
    std::string target = argv[1];
    int popSize = atoi(argv[2]);
    double mr = atof(argv[3]);
    double cr = atof(argv[4]);
    Chromosome answer = runGA(target, popSize, mr, cr);

    std::cout << "Solution found: " << answer << std::endl;
}