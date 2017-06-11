/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/11/2016
*/
#include "soldier.h"

void readSoldiers(int, Soldier*, int);
void writeSoldiers(int, Soldier*);

void heapSort(int, Soldier*);
void heapify(Soldier*, int, int);

void war(Soldier*, Soldier*);
void resultWar(Soldier*, Soldier*);

int main(int argc, char** argv)
{
	int function = atoi(argv[1]);
	if (function == 1)
	{
		int N = atoi(argv[2]);

		Soldier* soldiers;
		soldiers = new Soldier[N];
		readSoldiers(N, soldiers, function);

		clock_t t = clock();
		heapSort(N, soldiers);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds" << endl;

		writeSoldiers(N, soldiers);
		delete[] soldiers;
	}
	else if (function == 2)
	{
		int N = 10000;

		// Reading Clan A
		Soldier* clanA;
		clanA = new Soldier[N];
		readSoldiers(N, clanA, function-1);
		// Sorting Clan A
		clock_t t = clock();
		heapSort(N, clanA);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds sorting time for Clan A" << endl;
		

		// Reading Clan B
		Soldier* clanB;
		clanB = new Soldier[N];
		readSoldiers(N, clanB, function);
		//Sorting Clan B
		t = clock();
		heapSort(N, clanB);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds sorting time for Clan B" << endl;

		// WAR
		t = clock();
		war(clanA, clanB);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds WAR TIME" << endl;
		resultWar(clanA, clanB);
	}
	else
	{
		cout << "Wrong initial value" << endl;
	}
	return 0;
}

void readSoldiers(int N, Soldier* soldiers, int clan)
{
	char* unsortedFileName;
	int id;
	int cp;
	if (clan==1)
		unsortedFileName = (char*)"ClanA.txt";

	else
		unsortedFileName = (char*)"ClanB.txt";

	ifstream inputStream;
	inputStream.open(unsortedFileName, ios::in);
	for (int i = 0; i < N; i++)
	{
		inputStream >> id;
		inputStream >> cp;
		soldiers[i].setId(id);
		soldiers[i].setCp(cp);
	}
}

void writeSoldiers(int N, Soldier* soldiers)
{
	char* sortedFileName;

	sortedFileName = (char*)"A_sorted.txt";

	ofstream outputStream;
	outputStream.open(sortedFileName, ios::out | ios::trunc);
	for (int i = 0; i < N; i++)
	{
		outputStream << soldiers[i].getId() << " " << soldiers[i].getCp() << endl;
	}
}

// The main function to that sorts soldiers[] of size n using 
// Heap Sort
void heapSort(int N, Soldier* soldiers)
{
	// Build heap (rearrange array)
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(soldiers, N, i);

	// One by one extract an element from heap
	for (int i = N - 1; i >= 0; i--)
	{
	// Move current root to end
		swap(soldiers[0], soldiers[i]);

	// call max heapify on the reduced heap
		heapify(soldiers, i, 0);
	}
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(Soldier* soldiers, int N, int i)
{
	int largest = i;  // Initialize largest as root
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2;  // right = 2*i + 2

						// If left child is larger than root
	if (l < N && soldiers[l].getCp() > soldiers[largest].getCp())
		largest = l;

	// If right child is larger than largest so far
	if (r < N && soldiers[r].getCp() > soldiers[largest].getCp())
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(soldiers[i], soldiers[largest]);

		// Recursively heapify the affected sub-tree
		heapify(soldiers, N, largest);
	}
}

void war(Soldier* clanA, Soldier* clanB)
{
	int N = 10000;

	char* gamelog;
	int id;
	char attacker;
	int attackerPosition, attackedPosition;
	gamelog = (char*)"gamelogs.txt";

	ifstream inputStream;
	inputStream.open(gamelog, ios::in);

	while (inputStream >> id >> attacker >> attackerPosition >> attackedPosition)
	{
		// clans are sorted lower to higher
		//campaign(attacker, 9999 - attackerPosition, 9999 - attackedPosition);
		attackerPosition = 9999 - attackerPosition;
		attackedPosition = 9999 - attackedPosition;
		if (attacker == 'A')
		{
			//If a clan leader successfully attacks an enemy, she / he captures half of the enemy’s CPs.
			if (attackerPosition == 9999)
			{
				clanA[attackerPosition].setCp(clanA[attackerPosition].getCp() + clanB[attackedPosition].getCp() / 2);
				clanB[attackedPosition].setCp(clanB[attackedPosition].getCp() - clanB[attackedPosition].getCp() / 2);
			}
			//If a henchman attacks an enemy she/he obtains 500 CP and the attacked player loses 500 CPs.
			else if (attackerPosition <= 9998 && attackerPosition >= 9992)
			{
				clanA[attackerPosition].setCp(clanA[attackerPosition].getCp() + 500);
				clanB[attackedPosition].setCp(clanB[attackedPosition].getCp() - 500);
				if (clanB[attackedPosition].getCp() < 0)
					clanB[attackedPosition].setCp(0);
			}
			//If a soldier attacks an enemy, she / he obtains a CP of(height difference between two players + 1) multiplied by 30, and the attacked player loses 120 CPs.
			else
			{
				int heightDifference;
				if (attackerPosition == attackedPosition)
					heightDifference = 0;
				else
					heightDifference = abs(int(log(10000 - attackerPosition) / log(2)) - int(log(10000 - attackedPosition) / log(2)));
				clanA[attackerPosition].setCp(clanA[attackerPosition].getCp() + (heightDifference + 1) * 30);
				clanB[attackedPosition].setCp(clanB[attackedPosition].getCp() - 120);
				if (clanB[attackedPosition].getCp() < 0)
					clanB[attackedPosition].setCp(0);
			}
		}
		else if (attacker == 'B')
		{
			//If a clan leader successfully attacks an enemy, she / he captures half of the enemy’s CPs.
			if (attackerPosition == 9999)
			{
				clanB[attackerPosition].setCp(clanB[attackerPosition].getCp() + clanA[attackedPosition].getCp() / 2);
				clanA[attackedPosition].setCp(clanA[attackedPosition].getCp() - clanA[attackedPosition].getCp() / 2);
			}
			//If a henchman attacks an enemy she/he obtains 500 CP and the attacked player loses 500 CPs.
			else if (attackerPosition <= 9998 && attackerPosition >= 9992)
			{
				clanB[attackerPosition].setCp(clanB[attackerPosition].getCp() + 500);
				clanA[attackedPosition].setCp(clanA[attackedPosition].getCp() - 500);
				if (clanA[attackedPosition].getCp() < 0)
					clanA[attackedPosition].setCp(0);
			}
			//If a soldier attacks an enemy, she / he obtains a CP of(height difference between two players + 1) multiplied by 30, and the attacked player loses 120 CPs.
			else
			{
				int heightDifference;
				if (attackerPosition == attackedPosition)
					heightDifference = 0;
				else
					heightDifference = abs(int(log(10000 - attackerPosition) / log(2)) - int(log(10000 - attackedPosition) / log(2)));
				clanB[attackerPosition].setCp(clanB[attackerPosition].getCp() + (heightDifference + 1) * 30);
				clanA[attackedPosition].setCp(clanA[attackedPosition].getCp() - 120);
				if (clanA[attackedPosition].getCp() < 0)
					clanA[attackedPosition].setCp(0);
			}
		}
		else
			cout << "Wrong Clan" << endl;
		heapSort(N, clanA);
		heapSort(N, clanB);
	}
}
void resultWar(Soldier* clanA, Soldier* clanB)
{
	int totalCpA = 0;
	int totalCpB = 0;
	for (int i = 0; i < 10000; i++)
	{
		totalCpA += clanA[i].getCp();
		totalCpB += clanB[i].getCp();
	}
	cout << "Clan A: " << totalCpA << endl;
	cout << "Clan B: " << totalCpB << endl;
	if (totalCpA > totalCpB)
		cout << "Winner : Clan A" << endl << "Difference: " << totalCpA - totalCpB << endl;
	else
		cout << "Winner : Clan B" << endl << "Difference: " << totalCpB - totalCpA << endl;
}
