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
void insertToHash(node *hash, string content, int colisao);//Insere na hash
int stringXor(string content);//Calcula função xor

int main()
{
	int tam= 500;
	int colisao;
	node *hashTable = createHash(tam);
	string tag, content;
	cin>>tag>>content;
	if(tag=="INSERT")
	{
		cout<<"insert"<<endl;
		insertToHash(hashTable, content, colisao);
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

void insertToHash(node *hash, string content, int colisao)
{
	cout<<content<<endl;

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
		int key=stringXor(content);
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