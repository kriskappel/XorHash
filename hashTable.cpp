#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
	long long int k;
	string c;
};
typedef node node;

node *createHash(int tam);//Cria hash inicial
node *insertToHash(string content);//Insere na hash
int hashFunction(string content);//Calcula função xor

int main()
{
	int tam= 500;
	node *hashTable = createHash(tam);
	string teste= "umaString";
	//addToHash(teste);

}

node *createHash(int tam)
{
	node *aux;
	aux=(node*)malloc(sizeof(node)*tam);
	
	return aux;
}

node *addToHash(string content)
{
	node *newNode=(node*)malloc(sizeof(node));
	
	newNode->c=content;
	int key=hashFunction(content);
	newNode->k=key;
	return newNode;
}

int hashFunction(string content)
{
    unsigned h = 0;

    for (int i = 0; i < content.length(); i++)
    {
        h ^= content[i];
        cout<< "iteração "<<i<<" "<<h<<endl;
    }
    cout<< h<<endl;
    return h;
}