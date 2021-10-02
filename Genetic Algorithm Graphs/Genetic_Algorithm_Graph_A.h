#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream> 

class Chromosome    //an instance of this class represents a solution
{
public:
	Chromosome();
	void setGene(int i, short value);
	short getGene(int i);
	int getFitness(int edge[10][6]);
	void setFitness(int i);
	int FitnessCalculate(int edge[10][6]);


private:
	short Genes[26];
	int Fitness;
};

/*---------methods/constructors/gets-sets----------------*/
Chromosome::Chromosome()
{

	for (int i = 0;i < 26;i++)
	{
		short Gene = rand() % 2;
		Genes[i] = Gene;

	}
	Fitness = -1;
}

void Chromosome::setGene(int i, short value)
{
	Genes[i] = value;
}

short Chromosome::getGene(int i)
{
	return (Genes[i]);
}
void Chromosome::setFitness(int i)
{
	Fitness = i;
}
int Chromosome::getFitness(int edge[10][6])
{

	Fitness = 0;
	Fitness = FitnessCalculate(edge);
	return Fitness;
}


int Chromosome::FitnessCalculate(int edge[10][6])
{

	for (int i = 0; i < 25; i++)
	{
		if (Genes[i] != Genes[i + 1])
		{
			Fitness++;
		}

	}
	return Fitness;
}

class Population            //represents the population of the possible solutions-chromosomes
{
public:
	static const int PopulationSize = 50;
	Population(bool State, bool mutation);
	Population();
	bool getEnsureMutation();
	bool getStatereplacement();
	Chromosome getChromosome(int i);
	void setChromosome(Chromosome tmp, int i);
	Chromosome getFittestChrom(int edge[10][6]);

private:
	bool EnsureMutation;
	bool Statereplacement;
	Chromosome Chromosomes[PopulationSize];
};


Population::Population(bool State, bool mutation)
{
	EnsureMutation = mutation;
	Statereplacement = State;
	for (int i = 0;i < PopulationSize;i++)
	{
		Chromosomes[i] = Chromosome();
	}

}

Population::Population()
{
	EnsureMutation = true;
	Statereplacement = true;
	for (int i = 0;i < PopulationSize;i++)
	{
		Chromosomes[i] = Chromosome();
	}
}

bool Population::getEnsureMutation()
{
	return EnsureMutation;
}
bool Population::getStatereplacement()
{
	return Statereplacement;
}

Chromosome Population::getChromosome(int i)
{
	return Chromosomes[i];
}


void Population::setChromosome(Chromosome tmp, int i)
{
	Chromosomes[i] = tmp;
}

Chromosome Population::getFittestChrom(int edge[10][6])
{
	Chromosome tmpFittest;
	int BestFitness = -1;
	int tmpFit;

	for (int i = 0;i < PopulationSize;i++)
	{
		tmpFit = 0; tmpFit = Chromosomes[i].getFitness(edge);
		if (BestFitness < tmpFit)
		{
			BestFitness = tmpFit;
			tmpFittest = Chromosomes[i];
		}
	}
	return tmpFittest;
}

/*---------Tournament method----------------*/
Chromosome Tournament(Population pop, int edge[10][6])
{
	std::cout << "running tournament" << std::endl;
	int TournamentSize = pop.PopulationSize / 2;
	Chromosome *TournamentPop = new Chromosome[TournamentSize];
	//Chromosome TournamentPop[TournamentSize];
	for (int i = 0;i < TournamentSize;i++)
	{
		int Rand = rand() % pop.PopulationSize;
		Chromosome temp = pop.getChromosome(Rand);
		TournamentPop[i] = temp;
	}
	Chromosome Fittest;
	int BestFit = -1;
	for (int i = 0;i < TournamentSize;i++)
	{
		int tmpFit = TournamentPop[i].getFitness(edge);
		if (BestFit < tmpFit)
		{
			BestFit = tmpFit;
			Fittest = TournamentPop[i];
		}
	}
	delete[] TournamentPop;
	return Fittest;
}

/*---------crossover method--------------*/
void Crossover(Chromosome &Chrom1, Chromosome &Chrom2)
{
	int random = rand() % 26;
	std::cout << "random crosspoint is : " << random << std::endl;
	std::cout << "chromosomes before change : " << std::endl;
	for (int j = 0;j < 26;j++) {
		std::cout << Chrom1.getGene(j);
	}
	std::cout << std::endl;
	for (int j = 0;j < 26;j++) {
		std::cout << Chrom2.getGene(j);
	}
	std::cout << std::endl;
	for (int i = 0;i < 26;i++)
	{
		if (i > random)
		{
			short tmp = Chrom1.getGene(i);
			Chrom1.setGene(i, Chrom2.getGene(i));
			Chrom2.setGene(i, tmp);
		}
	}
	std::cout << "chromosomes after change : " << std::endl;
	for (int j = 0;j < 26;j++) {
		std::cout << Chrom1.getGene(j);
	}
	std::cout << std::endl;
	for (int j = 0;j < 26;j++) {
		std::cout << Chrom2.getGene(j);
	}
	std::cout << std::endl;
}
/*--------mutate methods---------------------*/

void Mutate(Chromosome &Chrom)
{
	int random = rand() % 100 + 1;

	if (random <= 2)       //2% mutation rate
	{
		std::cout << "mutating" << std::endl;
		int gene = rand() % 26;
		short GeneColor = Chrom.getGene(gene);
		if (GeneColor == 0)
			Chrom.setGene(gene, 1);
		else
			Chrom.setGene(gene, 0);
		for (int i = 0;i < 26;i++)
		{
			std::cout << Chrom.getGene(i);
		}
		std::cout << std::endl;


	}
}

void EnsureMutate(Chromosome &Chrom)
{
	std::cout << "ensured mutation" << std::endl;
	int gene = rand() % 26;
	short GeneColor = Chrom.getGene(gene);

	if (GeneColor == 0)
		Chrom.setGene(gene, 1);
	else
		Chrom.setGene(gene, 0);
	for (int i = 0;i < 26;i++)
	{
		std::cout << Chrom.getGene(i);
	}
	std::cout << std::endl;
}


int main()
{
	std::string temp;
	bool flag = false;
	int randm;
	int helpSize;
	int Mutation;
	bool StateReplacement;
	int Edge[10][6];
	std::cout << "The edges of our graph are :" << std::endl;

	for (int i=0; i<11; i++)
	{
	  for (int j=0; j<7; j++)
	  {
	      if((i>2 && j==0)||(i>2 && j==6))
	      {
	          Edge[i][j] = 1;
	      }
	      else if ((i==2 && j==1) || (i==1 && j==2) || (i==0 && j==3) || (i==1 && j==4) || (i==2 && j==5) || i==5)
	      {
	          Edge[i][j] = 1;
	      }
	      else
	      {
	          Edge[i][j]=0;
	      }
	      std::cout<<Edge[i][j];
	  }
	  std::cout<<std::endl;
	}

	std::cout << "------------------------Initialization---------------------------------" << std::endl;
	std::cout << "would you like to use steady state replacement in the 50% of the Population??" << std::endl;
	do {
		std::cout << "Type YES or NO" << std::endl;
		std::cin >> temp;
		if (temp == "YES" || temp == "yes")
		{
			flag = true;
			StateReplacement = true;
			std::cout << "Confirmed" << std::endl;
		}
		else if (temp == "NO" || temp == "no")
		{
			flag = true;
			StateReplacement = false;    std::cout << "Confirmed" << std::endl;
		}
		else
		{
			flag = false;
			std::cout << "Unconfirmed" << std::endl;
		}
	} while (flag == false);

	std::cout << "Whould you like to ensure mutation in the 10% of the population?" << std::endl;
	do {
		std::cout << "Type YES or NO" << std::endl;
		std::cin >> temp;
		if (temp == "YES" || temp == "yes")
		{
			flag = true;
			Mutation = true;
			std::cout << "Confirmed" << std::endl;
		}
		else if (temp == "NO" || temp == "no")
		{
			flag = true;
			Mutation = false;
			std::cout << "Confirmed" << std::endl;
		}
		else
		{
			flag = false;
			std::cout << "Unconfirmed" << std::endl;
		}
	} while (flag == false);

	bool found = false;
	Population Mypopulation = Population(StateReplacement, Mutation);
	int counter = 0;
	while (found == false)
	{
		for (int i = 0;i < Mypopulation.PopulationSize;i++)
		{
			Chromosome tmpChrom = Mypopulation.getChromosome(i);
			int fit = tmpChrom.getFitness(Edge);
			if (fit == 25)
			{
				std::cout << "Found" << std::endl;
				std::cout << "solution Chromosome :";
				for (int j = 0;j < 26;j++)
					std::cout << tmpChrom.getGene(j);

				found = true;
				std::cout << std::endl;
				break;
			}
		}
		if (found == true)
		{
			std::cout << "BREAKING" << std::endl;
			break;
		}
		counter++;
		std::cout << "CREATING NEXT GENERATION No" << counter << "\n" << std::endl;
		if (Mypopulation.getStatereplacement() == true)
			helpSize = Mypopulation.PopulationSize / 2;
		else
			helpSize = Mypopulation.PopulationSize;

		Chromosome *tempPopulation = new Chromosome[helpSize];
		//Chromosome tempPopulation[helpSize];


		for (int i = 0;i < (helpSize) / 2;i++)

		{
			std::cout << "GENERATING No" << i << std::endl;
			Chromosome FirstFit = Tournament(Mypopulation, Edge);

			Chromosome SecondFit = Tournament(Mypopulation, Edge);

			Crossover(FirstFit, SecondFit);

			if (Mypopulation.getEnsureMutation() == false)
			{
				Mutate(FirstFit);
				Mutate(SecondFit);
			}

			tempPopulation[i] = FirstFit;
			tempPopulation[(helpSize - 1) - i] = SecondFit;
		}


		if (Mypopulation.getEnsureMutation() == true)
		{
			for (int m = 0;m < (helpSize / 10);m++)
			{
				randm = rand() % helpSize;
				EnsureMutate(tempPopulation[randm]);
			}
		}

		bool checkflag;

		int *Previousrandom = new int[helpSize];
		//int Previousrandom[helpSize];
		randm = rand() % Mypopulation.PopulationSize;
		for (int i = 0;i < helpSize;i++)
		{

			if (i > 0)
				do {
					checkflag = true;
					randm = rand() % Mypopulation.PopulationSize;
					for (int l = 0;l < i;l++)
					{
						if (Previousrandom[l] == randm)
							checkflag = false;
					}
				} while (checkflag == false);

				Mypopulation.setChromosome(tempPopulation[i], randm);
				Previousrandom[i] = randm;

		}
		delete[] Previousrandom;

		std::cout << "\n" << std::endl;
	}
	system("pause");
}