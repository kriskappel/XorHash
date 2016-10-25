#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct nod{
	string c;
	struct nod *prox;
};
typedef struct nod node;

node *createHash(int tam);//Cria hash inicial
void insertToHash(node *hash, string content, int colisao, int flag, int tam);//Insere na hash
void insereEncadeamento(node *hash, node *novo, int key);
void insereLinear(node *hash, node *novo, int key);
void insereQuadratica(node *hash, node *novo, int key);
void insereHashDuplo(node *hash, node *novo, int key);
int stringXor(string content);//Calcula função xor
int hash1(int key, int tam);
int hash2(int key, int tam);

int main()
{
	int tam= 500, qtd=0;
	int colisao, flag=0;
	double fator;
	node *hashTable = createHash(tam);
	string tag, content;
	cin>>tag>>content;		
	
	if(tag=="INSERT")
	{
		cout<<"insert"<<endl;		
		insertToHash(hashTable, content, colisao, flag, tam);
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

void insertToHash(node *hash, string content, int colisao, int flag, int tam)
{
	cout<<content<<endl;
	int key, pos;
	node *newNode;
	newNode=new node;
	if(newNode == NULL){
		cout<<"nulo";
	}
	else
	{
		//cout<<"aqui estamos"<<endl;
		//cout<<(*newNode).c<<endl;
		//strcpy(newNode->c, content.c_str());
		//newNode->c=content;//.copy(content, content.length(), 0);
		newNode->c=content;
		//cout<<newNode->c<< "só pra ter certeza"<<endl;	
		key=stringXor(content); //retorna onde deve ser inserido na hash
		pos= hash1(key, tam); //faz a função k mod m
		//sem colisão, insere normal da hash
		//if(hash[pos] == NULL)
		//	hash[pos] = newNode;
		//else{
			//ocorreu a colisão, tratara ela com o modo adequado
			switch(colisao){
				case 0:
					insereEncadeamento(hash,newNode, key);			
				case 1:
					insereLinear(hash,newNode, key);
				case 2:
					insereQuadratica(hash,newNode, key);
				case 3:
					insereHashDuplo(hash,newNode, key);
			}
		//}
	}
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

void insereEncadeamento(node *hash, node *novo, int key)
{
	cout<<"Insere Encadeado";
}

void insereLinear(node *hash, node *novo, int key)
{
	cout<<"Insere Linear";
}

void insereQuadratica(node *hash, node *novo, int key)
{
	cout<<"Insere Quadratico";
}

void insereHashDuplo(node *hash, node *novo, int key)
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