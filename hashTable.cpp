#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct n{
	string c;
	struct n *prox;
};
typedef struct n node;

node *createHash(int tam);//Cria hash inicial
bool insertToHash(node *hash, string content, int colisao, int flag, int tam);//Insere na hash
bool getFromHash(node *hash, string content, int tam);//Busca na hash
bool removeFromHash(node *hash, string content, int tam);//remove da hash
void insereEncadeamento(node *hash, string content, int key);
void insereLinear(node *hash, string content, int key);
void insereQuadratica(node *hash, string content, int key);
void insereHashDuplo(node *hash, string content, int key);
int stringXor(string content);//Calcula função xor
int hash1(int key, int tam);//calcula h1(x)
int hash2(int key, int tam);//calcula h2(x) no caso de double hashing

int main()
{
	int tam= 500, qtd=0;
	int colisao, flag=0;
	bool status;
	double fator;
	node *hashTable = createHash(tam);
	string tag, content;
	cin>>tag>>content;		
	

	//TODO Tratar string vazia
	if(tag=="INSERT")
	{
		cout<<"insert"<<endl;		
		status=insertToHash(hashTable, content, colisao, flag, tam);
		qtd++; //adiciona mais um na quantidade
		if(qtd == 0)	
			fator=0;	
		else
		{
			fator = (double)qtd/tam; //calcula o fator de carga
			if(fator >= 0.75)
				flag=1; //ocorre o rehash
		}
	}
	else if(tag=="DELETE")
		cout<<"delete"<<endl;
	else if(tag=="GET")
		cout<<"get"<<endl;

	else
		cout<<"ERROR, UNDEFINED TAG"<<endl;

	cout<<content<<endl;
	
	//string teste= "umaString";
	//cout<<teste<<endl;
	//node *nNode;
	//insertToHash(teste);
	//cout<<"string"<<endl;

}

node *createHash(int tam)
{
	node *aux;
	aux=(node*)malloc(sizeof(node)*tam);
	
	return aux;
}	

bool insertToHash(node *hash, string content, int colisao, int flag, int tam)
{
	cout<<content<<endl;
	int key, pos;
	//cout<<"content da hash->"<<(hash+pos)->c<<endl;	
	//node *newNode;
	/*newNode=new node;*/
	//strcpy(newNode->c, content.c_str());
	//newNode->c=content;//.copy(content, content.length(), 0);
	//newNode->c=content;
	cout<<"teste"<<endl;
	key=stringXor(content); //retorna onde deve ser inserido na hash
	pos= hash1(key, tam); //faz a função k mod m
	node *auxNode=(hash+pos);
	cout<<"POSICOES "<<(hash+pos)->c<<" "<<auxNode<<endl;
	//sem colisão, insere normal da hash
	cout<<"teste"<<endl;
	cout<<"content da hash->"<<auxNode->c<<endl;
	cout<<"teste"<<endl;
	if((hash + pos)->c.empty())
	{
		cout<<"content da hash->"<<(hash+pos)->c<<endl;
		(hash + pos)->c=content;
	}
	
		
	else
	{
		//ocorreu a colisão, tratara ela com o modo adequado
		switch(colisao){
			case 0:
				insereEncadeamento(hash, content, key);			
			case 1:
				insereLinear(hash, content, key);
			case 2:
				insereQuadratica(hash, content, key);
			case 3:
				insereHashDuplo(hash, content, key);
		}
	}
	cout<<"POSICOES "<<(hash+pos)->c<<endl;
	return true;
	//}
}

bool getFromHash(node *hash, string content, int tam)
{
	int key, pos;
	key=stringXor(content); //retorna onde deve ser inserido na hash
	pos= hash1(key, tam); //faz a função k mod m
	if ((hash+pos)->c==content)
		return true;
	else
		return false;
}

bool removeFromHash(node *hash, string content, int tam)
{
	int key, pos;
	key=stringXor(content); //retorna onde deve ser inserido na hash
	pos= hash1(key, tam); //faz a função k mod m
	if ((hash+pos)->c==content)
	{
		(hash+pos)->c.clear();
		return true;
	}
	else
		return false;
}

int stringXor(string content)
{
    unsigned h = 0;

    for (int i = 0; i < content.length(); i++)
    {
        h ^= content[i];
        //cout<< "iteração "<<i<<" "<<h<<endl;
    }
    cout<< h<<endl;
    return h;
}

void insereEncadeamento(node *hash, string content, int key)
{
	cout<<"Insere Encadeado";
}

void insereLinear(node *hash, string content, int key)
{
	cout<<"Insere Linear";
}

void insereQuadratica(node *hash, string content, int key)
{
	cout<<"Insere Quadratico";
}

void insereHashDuplo(node *hash, string content, int key)
{
	cout<<"Insere Hash Duplo";
}

int hash1(int key, int tam)
{
	return key % tam;
}

int hash2(int key, int tam)
{
	return  1 + (key % (tam-1)); 
}