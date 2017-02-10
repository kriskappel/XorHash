//REMINDER:
//do a -help

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
bool insereEncadeamento(node *hash, string content, int key, int op);
void insereLinear(node *hash, string content, int key, int tam);
void insereQuadratica(node *hash, string content, int key);
void insereHashDuplo(node *hash, string content, int key);
int stringXor(string content);//Calcula função xor
int hash1(int key, int tam);//calcula h1(x)
int hash2(int key, int tam);//calcula h2(x) no caso de double hashing
int selectTreatment(char **argv);

int main(int argc, char **argv)
{
	int tam= 500, qtd=0; //tamanho incial da hash = 500
	int colisao, flag=0;
	bool status;
	double fator;
	node *hashTable = createHash(tam); 
	string tag, content;

	//TESTA SE UM PARAMETRO FOI PASSADO.
	//só a chamada do .out conta como um parametro e ele so pode passar um parametro adicional por vez,
	//nao pode escolher dois tipos de metodo de tratamento de colisao, por exemplo.
	if(argc==1 || argc>2)
	{
		cout<<"\nPlease select just a valid colision treatment :D\n\n-help for more options and explanations.\n";
		return 0;
	}
	colisao= selectTreatment(argv);//chama o metodo que transforma o argv em um int colisao

	//caso o metodo selectTreatment tenha invalidado a seleção ele retorna -1
	//caso ele tenha entrado na opçao de ajuda ele precisa encerrar o programa pro usuario poder executar de novo
	if (colisao == 4 || colisao == -1) 
	{
		if (colisao== -1)
		{
			cout<<"\nInvalid colision type detected :(\n\n-help for more options and explanations.\n";
			
		}
		return 0;
	}
	
	//Le a tag, referente ao tipo de operaçao, insert, get ou delete
	//Le o conteudo que quer se por na hash
	cin>>tag>>content; 

	
	//cout<<argc;

	//cout<<*argv[1];		

	//TODO Tratar string vazia
	while(tag != "0") // se a tag for 0 ele para a execução
	{
		if(tag=="INSERT") 
		{
			cout<<"insert"<<endl;//só pra fins de teste		
			status=insertToHash(hashTable, content, colisao, flag, tam);//chama a funcao de inserção
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
		{
			cout<<"delete"<<endl;
			removeFromHash(hashTable, content, tam);
		}
		else if(tag=="GET")
		{
			cout<<"get"<<endl;
			getFromHash(hashTable, content, tam);
		}
		else
			cout<<"ERROR, UNDEFINED TAG"<<endl;

		cout<<endl;
		cin>>tag>>content;// le de novo as novas informações
	}
		
	//string teste= "umaString";
	//cout<<teste<<endl;
	//node *nNode;
	//insertToHash(teste);
	//cout<<"string"<<endl;
	return 0;

}

node *createHash(int tam)
{
	node *aux;
	//aux=(node*)malloc(sizeof(node)*tam);
	aux= new node[tam];
	
	return aux;
}	

bool insertToHash(node *hash, string content, int colisao, int flag, int tam)
{
	cout<<"\n===INSERCAO===\n"<<"Conteudo: "<<content<<endl;
	//cout<<content<<endl;
	int key, pos;
	//cout<<"content da hash->"<<(hash+pos)->c<<endl;	
	//node *newNode;
	/*newNode=new node;*/
	//strcpy(newNode->c, content.c_str());
	//newNode->c=content;//.copy(content, content.length(), 0);
	//newNode->c=content;
	key=stringXor(content); //retorna onde deve ser inserido na hash
	pos= hash1(key, tam); //faz a função k mod m
	//node *auxNode=(hash+pos);
	//cout<<"POSICOES "<<(hash+pos)->c<<" "<<auxNode<<endl;
	//sem colisão, insere normal da hash
	cout<<"Posicao: "<<pos<<"\nKey: "<<key<<endl;

	//caso a hash esteja vazia ele só poe na posição e abraços
	if(hash[pos].c.empty())
	{
		//cout<<"content da hash->"<<(hash+pos)->c<<endl;
		hash[pos].c=content;
		cout<<"Status: Concluido com sucesso"<<endl;
	}
	else
	{
		bool founded;
		cout<<"Status: Colisao na Insercao"<<endl;
		//ocorreu a colisão, tratara ela com o modo adequado
		switch(colisao){
			case 0:
			{
				founded=insereEncadeamento(hash, content, key, 0);
				break;		
			}
			case 1:
			{
				insereLinear(hash, content, key, tam);
				break;
			}
			case 2:
			{
				insereQuadratica(hash, content, key);
				break;
			}
			case 3:
			{
				insereHashDuplo(hash, content, key);
				break;
			}
		}
	}
	//cout<<"POSICOES "<<(hash+pos)->c<<endl;
	return true;
	//}
}

bool getFromHash(node *hash, string content, int tam)
{
	//SÓ PESQUISA NA HASH E RETORNA SE ACHOU OU NÃO (até o momento)
	cout<<"\n===BUSCA===\n"<<"Conteudo: "<<content<<endl;
	int key, pos;
	key=stringXor(content); //retorna onde deve ser inserido na hash
	pos= hash1(key, tam); //faz a função k mod m
	cout<<"Posicao: "<<pos<<"\nKey: "<<key<<endl;
	if ((hash+pos)->c==content)
	{
		cout<<"Status: Concluido com sucesso"<<endl;
		return true;
	}
	else
	{
		cout<<"Status: Chave nao encontrada"<<endl;
		return false;
	}
}

bool removeFromHash(node *hash, string content, int tam)
{
	//SÓ REMOVE DA HASH NORMALMENTE (até o momento)
	cout<<"\n===REMOCAO===\n"<<"Conteudo: "<<content<<endl;
	int key, pos;
	key=stringXor(content); //retorna onde deve ser inserido na hash
	pos= hash1(key, tam); //faz a função k mod m
	cout<<"Posicao: "<<pos<<"\nKey: "<<key<<endl;
	if ((hash+pos)->c==content)
	{
		cout<<"Status: Concluido com sucesso"<<endl;
		(hash+pos)->c.clear();
		return true;
	}
	else
	{
		cout<<"Status: Erro na remocao"<<endl;
		return false;
	}
}

int stringXor(string content)
{
	//Recebe a string e retorna a key formada por ela
    unsigned h = 0;

    for (int i = 0; i < content.length(); i++)
    {
        h ^= content[i];
        //cout<< "iteração "<<i<<" "<<h<<endl;
    }
    //cout<< h<<endl;
    return h;
}

bool insereEncadeamento(node *hash, string content, int key, int op)
{
	//sei que o nome tava como insere, mas ele deveria fazer as 3 funçoes
	//cada numero do op significa uma operação
	//op=0 seria insere
	//op=1 seria get
	//op=2 seria delete
	cout<<"Insere Encadeado";
	node *auxPointer=(hash+key);
	while(auxPointer->prox!=NULL)//while pra ir até o final da lista encadeada
	{
		if(auxPointer->prox->c==content)//if caso ache o nodo com o conteudo que quero
		{
			if(op==2)
			{
				//vai até o local da lista com o conteudo desejado e apaga
				node *anterior=auxPointer->prox->prox;
				node *proximo =auxPointer->prox;
				free(proximo);
			}
			return true;
		}
		auxPointer=auxPointer->prox;
		
	}
	if(op==0)
	{
		//no while ele ja foi até o final da lista, agora ele só adiciona na lista encadeada
		node *newNode= new node;
		newNode->c=content;
		newNode->prox=NULL;
		auxPointer->prox=newNode;
	}
	return false;
}

void insereLinear(node *hash, string content, int key, int tam)
{
	cout<<"Insere Linear";
	//int i;
	for(int i=key; i<tam;i++)
	{
		if(hash[i].c.empty())
		{
			//KEEP IMPLEMENTING, NOT ENDED YET
			//return 
			//hash[i].c=content;
		}
	}
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

int selectTreatment(char **argv)
//MÉTODO QUE SÓ RECEBE O ARGUMENTO E RETORNA O CODIGO
{
	if (!strcmp(argv[1], "-encadeamento"))	
		return 0;
	else if (!strcmp(argv[1], "-linear"))	
		return 1;
	else if (!strcmp(argv[1], "-quadratico"))	
		return 2;
	else if (!strcmp(argv[1], "-hash_duplo"))	
		return 3;
	else if (!strcmp(argv[1], "-help"))
	{	
		cout<< " Hi :D \n This is a hash table and you have to select one out of 4 types of colision treatment in order to work properly!\n";
		cout<< " This are the valid options and the way they work over it\n";
		cout<< "-encadeamento:\n";
		cout<< "\tsimple creates a linked list and adds the new key to the end of it\n";
		cout<< "-linear:\n";
		cout<< "\tin case of colisions the key increases in key + i\n";
		cout<< "-quadratico\n";
		cout<< "\tvery similar to linear probing but increases in i^2\n";
		cout<< "-hash_duplo\n";
		cout<< "\tthere's is a second hash that is used in case of colisions\n";
		return 4;
	}
	else 
		return -1;
}
