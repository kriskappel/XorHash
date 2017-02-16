//REMINDER:

/*

*/

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct n {
    string c;
    struct n *prox;
    bool deleted=false;
};
typedef struct n node;

node *createHash(int tam);//Cria hash inicial
bool insertToHash(node *hash, string content, int colisao, int tam);//Insere na hash
bool getFromHash(node *hash, string content, int colisao, int tam);//Busca na hash
bool removeFromHash(node *hash, string content, int colisao, int tam);//remove da hash
node *ReHash(node *hash, string content, int colisao, int tam);

bool insertEncadeamento(node *hash, string content, int pos);
bool getEncadeamento(node *hash, string content, int pos);
bool deleteEncadeamento(node *hash, string content, int pos);

bool insertLinear(node *hash, string content, int key, int tam);
bool getLinear(node *hash, string content, int key, int tam);
bool deleteLinear(node *hash, string content, int key, int tam);

bool insertQuadratica(node *hash, string content, int key, int tam);
bool getQuadratica(node *hash, string content, int key, int tam);
bool deleteQuadratica(node *hash, string content, int key, int tam);

bool insertHashDuplo(node *hash, string content, int key, int tam);
bool getHashDuplo(node *hash, string content, int key, int tam);
bool deleteHashDuplo(node *hash, string content, int key, int tam);

int stringXor(string content);//Calcula função xor
int hash1(int key, int tam);//calcula h1(x)
int hash2(int key, int tam);//calcula h2(x) no caso de double hashing
int selectTreatment(char **argv);

string checkString(string content);

int main(int argc, char **argv) {
    int tam = 500, qtd = 0; //tamanho incial da hash = 500
    int colisao, flag = 0;
    bool status;
    double fator;
    node *hashTable = createHash(tam);
    string tag, content;

    //TESTA SE UM PARAMETRO FOI PASSADO.
    //só a chamada do .out conta como um parametro e ele so pode passar um parametro adicional por vez,
    //nao pode escolher dois tipos de metodo de tratamento de colisao, por exemplo.
    if (argc == 1 || argc > 2) {
        cout << "\nPlease select just a valid colision treatment :D\n\n-help for more options and explanations.\n";
        return 0;
    }
    colisao = selectTreatment(argv);//chama o metodo que transforma o argv em um int colisao

    //caso o metodo selectTreatment tenha invalidado a seleção ele retorna -1
    //caso ele tenha entrado na opçao de ajuda ele precisa encerrar o programa pro usuario poder executar de novo
    if (colisao == 4 || colisao == -1) {
        if (colisao == -1) {
            cout << "\nInvalid colision type detected :(\n\n-help for more options and explanations.\n";

        }
        return 0;
    }

    //Le a tag, referente ao tipo de operaçao, insert, get ou delete
    //Le o conteudo que quer se por na hash
	cin >> tag >> content;
	content=checkString(content);
    //cout<<argc;

    //cout<<*argv[1];

    //TODO Tratar string vazia
    while (tag != "0") // se a tag for 0 ele para a execução
    {
        if (tag == "INSERT") {
            cout << "INSERT " << content << " ";//só pra fins de teste

            content.erase(content.begin());
			content.erase(content.end()-1);

            status = insertToHash(hashTable, content, colisao, tam);//chama a funcao de inserção

            if (status)
                cout << " SUCCESS";
            else
                cout << " FAIL";

            qtd++; //adiciona mais um na quantidade
        
            fator = (double) qtd / tam; //calcula o fator de carga
            if (fator >= 0.75)
            {
                //flag = 1; //ocorre o rehash //karine aqui para que essa flag?
                hashTable=ReHash(hashTable, content, colisao, tam);
                qtd=0;
            }
        
        } else if (tag == "DELETE") {
            cout << "DELETE " << content<< " ";

            content.erase(content.begin());
			content.erase(content.end()-1);

            status=removeFromHash(hashTable, content, colisao, tam);

            if (status)
                cout << " SUCCESS";
            else
                cout << " FAIL";

        } else if (tag == "GET") {
            cout << "GET " << content << " ";

            content.erase(content.begin());
			content.erase(content.end()-1);

            status=getFromHash(hashTable, content, colisao, tam);

            if (status)
                cout << " SUCCESS";
            else
                cout << " FAIL";
        } else
            cout << "ERROR, UNDEFINED TAG ";

        //Karine aqui: não entendi essa parte. Perguntar para o Kristofer
        cout << endl;
        cin >> tag >> content;// le de novo as novas informações
        content=checkString(content);
    }

    //string teste= "umaString";
    //cout<<teste<<endl;
    //node *nNode;
    //insertToHash(teste);
    //cout<<"string"<<endl;
    return 0;

}

node *createHash(int tam) {
    node *aux;
    //aux=(node*)malloc(sizeof(node)*tam);
    aux = new node[tam];

    return aux;
}

bool insertToHash(node *hash, string content, int colisao, int tam) {
    //cout << "\n===INSERCAO===\n" << "Conteudo: " << content << endl;
    //cout<<content<<endl;
    int key, pos;
    //cout<<"content da hash->"<<(hash+pos)->c<<endl;
    //node *newNode;
    /*newNode=new node;*/
    //strcpy(newNode->c, content.c_str());
    //newNode->c=content;//.copy(content, content.length(), 0);
    //newNode->c=content;
    key = stringXor(content); //retorna onde deve ser inserido na hash
    cout<<key;
    pos = hash1(key, tam); //faz a função k mod m
    cout<< " "<<pos;
    //node *auxNode=(hash+pos);
    //cout<<"POSICOES "<<(hash+pos)->c<<" "<<auxNode<<endl;
    //sem colisão, insere normal da hash
    //out << "Posicao: " << pos << "\nKey: " << key << endl;

    //caso a hash esteja vazia ele só poe na posição e abraços
    if (hash[pos].c.empty())
    {
        //cout<<"content da hash->"<<(hash+pos)->c<<endl;
        hash[pos].c = content;
        hash[pos].deleted=false;
        cout<< " "<<pos<< " 0";
        //cout << "Status: Concluido com sucesso" << endl;

    }
    else if (hash[pos].c==content)
    {
    	cout<< " "<<pos<< " 0";
    	return false;
    	//cout << "Status: Valor ja inserido" << endl;
    }
    else {
        bool insertedFlag;
        //cout << "Status: Colisao na Insercao" << endl;
        //ocorreu a colisão, tratara ela com o modo adequado
        switch (colisao) {
            case 0: {
                insertedFlag = insertEncadeamento(hash, content, pos);
                return insertedFlag;
                break;
            }
            case 1: {
                insertedFlag=insertLinear(hash, content, key, tam);
                return insertedFlag;
                break;
            }
            case 2: {
                insertedFlag=insertQuadratica(hash, content, key, tam);
                return insertedFlag;
                break;
            }
            case 3: {
                insertedFlag = insertHashDuplo(hash, content, key, tam);
                return insertedFlag;
                break;
            }
        }
    }
    //cout<<"POSICOES "<<(hash+pos)->c<<endl;
    return true;
    //}
}

bool getFromHash(node *hash, string content, int colisao, int tam) {
    //SÓ PESQUISA NA HASH E RETORNA SE ACHOU OU NÃO (até o momento)
    //cout << "\n===BUSCA===\n" << "Conteudo: " << content << endl;
    int key, pos;
    key = stringXor(content); //retorna onde deve ser inserido na hash
    cout<<key;
    pos = hash1(key, tam); //faz a função k mod m
    cout<< " "<<pos;
    //out << "Posicao: " << pos << "\nKey: " << key << endl;
    if ((hash + pos)->c == content) {
        //cout << "Status: Concluido com sucesso" << endl;
        cout<< " "<<pos<< " 0";
        
        return true;
    } else {
        bool foundedFlag;
        //cout<<"Status: Chave nao encontrada"<<endl;
        switch (colisao) {
            case 0: {
                foundedFlag = getEncadeamento(hash, content, pos);
                return foundedFlag;
                break;
            }
            case 1: {
                foundedFlag=getLinear(hash, content, key, tam);
                return foundedFlag;
                break;
            }
            case 2: {
                foundedFlag=getQuadratica(hash, content, key, tam);
               	return foundedFlag;
                break;
            }
            case 3: {
                foundedFlag=getHashDuplo(hash, content, key, tam);
                return foundedFlag;
                break;
            }
        }
        return false;
    }
}

bool removeFromHash(node *hash, string content, int colisao, int tam) {
    //SÓ REMOVE DA HASH NORMALMENTE (até o momento)
    //cout << "\n===REMOCAO===\n" << "Conteudo: " << content << endl;
    int key, pos;
    key = stringXor(content); //retorna onde deve ser inserido na hash
    cout<<key;
    pos = hash1(key, tam); //faz a função k mod m
    cout<<" "<<pos;
    //cout << "Posicao: " << pos << "\nKey: " << key << endl;

    //se
    if ((hash + pos)->c == content && (hash + pos)->prox==NULL) {
        //cout << "Status: Concluido com sucesso" << endl;
        cout<< " "<<pos<< " 0";
        (hash + pos)->c.clear();
        (hash + pos)->deleted=true;
        return true;
    } else {
        bool deletedFlag;
        switch (colisao) {
            case 0: {
                deletedFlag = deleteEncadeamento(hash, content, pos);
                return deletedFlag;
                break;
            }
            case 1: {
                deletedFlag=deleteLinear(hash, content, key, tam);
                return deletedFlag;
                break;
            }
            case 2: {
                deletedFlag=deleteQuadratica(hash, content, key, tam);
                return deletedFlag;
                break;
            }
            case 3: {
                deletedFlag=deleteHashDuplo(hash, content, key, tam);
                return deletedFlag;
                break;
            }
        }
        //cout<<"Status: Erro na remocao"<<endl;
        return false;
    }
}

node *ReHash(node *hash, string content, int colisao, int tam)
{
    tam=2*tam;
    node *newHash=createHash(tam);
    node *auxPointer=new node();

    string transferedContent;
    if(colisao > 0)
    {
        for(int i=0; i<tam; i++)
        {
            if(!hash[i].c.empty())
                insertToHash(newHash, hash[i].c, colisao, tam);
        }
    }
    else
    {
        for(int i=0; i<tam; i++)
        {
            if(!hash[i].c.empty())
            {
                insertToHash(newHash, hash[i].c, colisao, tam);
                auxPointer= (hash + i);
                while(auxPointer!=NULL)
                {
                    insertToHash(newHash, auxPointer->c, colisao, tam);
                }
            }
        }
    }
    return newHash;
}

int stringXor(string content) {
    //Recebe a string e retorna a key formada por ela
    int h = 0;

    for (int i = 0; i < content.length(); i++) {
        h ^= content[i];
        //cout<< "iteração "<<i<<" "<<h<<endl;
    }
    //cout<< h<<endl;
    return abs(h);
}

bool insertEncadeamento(node *hash, string content, int pos) {
    //cout << "Insere Encadeado";
    int colisoes=0;

    node *auxPointer = (hash + pos);
    while (auxPointer->prox != NULL)//while pra ir até o final da lista encadeada
    {
    	colisoes++;
        if (auxPointer->c == content)
        {
        	cout<< " "<< pos;
        	cout<< " "<<colisoes;
            return false; //se ja achar o elemento na tabela retorna falso
        }

        auxPointer = auxPointer->prox;
    }
    if (auxPointer->c == content)
    {
    	cout<< " "<< pos;
    	cout<< " "<<colisoes;
        return false;
    }

    colisoes++;
    //no while ele ja foi até o final da lista, agora ele só adiciona na lista encadeada
    node *newNode = new node;
    newNode->c = content;
    newNode->prox = NULL;
    auxPointer->prox = newNode;

    cout<< " "<< pos;
    cout<< " "<<colisoes;
    return true;
}

bool getEncadeamento(node *hash, string content, int pos) {
    node *auxPointer = (hash + pos);
    int colisoes=0;

    if(auxPointer->prox==NULL)
    {
    	cout<< " "<< pos;
        cout<< " "<<colisoes;
    	return false;
    }
    while (auxPointer!= NULL)//while pra ir até o final da lista encadeada
    {
        //cout<<auxPointer->c;

        if (auxPointer->c == content)//if caso ache o nodo com o conteudo que quero
        {
        	cout<< " "<< pos;
        	cout<< " "<<colisoes;
            return true;
        }
        colisoes++;
        auxPointer = auxPointer->prox;

    }

    cout<< " "<< pos;
    cout<< " "<<colisoes;
    return false;
}

bool deleteEncadeamento(node *hash, string content, int pos) {
    node *auxPointer = (hash + pos);
    int colisoes=0;
    if(auxPointer->c == content) //Se a primeira posição é a ser deletada ele só atualiza o valor e deleta o prox
    {
    	node *toBeDeleted =auxPointer->prox;

    	auxPointer->c = auxPointer->prox->c;
    	auxPointer->prox = auxPointer->prox->prox;
    	free(toBeDeleted);

    	cout<< " "<< pos;
    	cout<< " "<<colisoes;
    	return true;
    }
    while (auxPointer==NULL)//while pra ir até o final da lista encadeada
    {
        if (auxPointer->prox->c == content)//if caso ache o nodo com o conteudo que quero
        {
            //vai até o local da lista com o conteudo desejado e apaga
            //node *anterior = auxPointer->prox->prox;
            //if(auxPointer->prox)
           	node *toBeDeleted =auxPointer->prox;

    		auxPointer->prox = auxPointer->prox->prox;
    		free(toBeDeleted);

    		cout<< " "<< pos;
    		cout<< " "<<colisoes;
            return true;
        }
        auxPointer = auxPointer->prox;

    }
    cout<< " "<< pos;
    cout<< " "<<colisoes;
    return false;
}

bool insertLinear(node *hash, string content, int key, int tam) {
    //cout << "Insere Linear";
    
    int pos;

    for (int i = 0; i < tam; i++)
    {
    	pos=hash1(key + i, tam);
        if (hash[pos].c.empty())
        {
            hash[pos].c = content;
            hash[pos].deleted=false;
            cout<< " "<<pos <<" "<< i;
            return true;
        }
        else if(hash[pos].c == content)
        {
        	cout<< " "<<pos <<" "<< i;
        	return false;
        }

    }
}

bool getLinear(node *hash, string content, int key, int tam)
{
    //cout << "get linear";
    int pos;

    for (int i = 0; i < tam; i++)
    {
    	pos=hash1(key + i, tam);
        if(hash[pos].c == content)
        {
        	cout<< " "<<pos <<" "<< i;
        	return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
        	cout<< " "<<pos <<" "<< i;
            return false;
        }
    }
}

bool deleteLinear(node *hash, string content, int key, int tam)
{
    //cout << "delete linear";
    //int colisoes=0;
    int pos;

    for (int i = 0; i < tam; i++)
    {
    	pos=hash1(key + i, tam);
        if(hash[pos].c == content)
        {
            hash[pos].c.clear();
            hash[pos].deleted=true;
            cout<< " "<<pos <<" "<< i;
        	return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
        	cout<< " "<<pos <<" "<< i;
            return false;
        }
    
    }

}

bool insertQuadratica(node *hash, string content, int key, int tam) {
    //Verificar essa função
    //cout << "Insere Quadratico";
    int pos = 0;

    for (int i = 1; pos < tam; i++){
        pos = hash1(key+i+i*i, tam);
        if(hash[pos].c.empty())
        {
            hash[pos].c = content;
            hash[pos].deleted = false;
            cout<< " "<<pos <<" "<< i;
            return true;
        }
        else if(hash[pos].c == content)
        {
        	cout<< " "<<pos <<" "<< i;
            return false;
        }
    }

}

bool getQuadratica(node *hash, string content, int key, int tam){
    //cout<<"get quadratica";
    int pos;

    for (int i = 0; i < tam; i++)
    {
        pos=hash1(key + i + i*i, tam);
        if(hash[pos].c == content)
        {
        	cout<< " "<<pos <<" "<< i;
            return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
        	cout<< " "<<pos <<" "<< i;
            return false;
        }
    }
}
bool deleteQuadratica(node *hash, string content, int key, int tam){
    //cout<<"get quadratica";

    int pos;

    for (int i = 0; i < tam; i++)
    {
        pos=hash1(key + i + i * i, tam);
        if(hash[pos].c == content)
        {
            hash[pos].c.clear();
            hash[pos].deleted=true;
            cout<< " "<<pos <<" "<< i;
            return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
        	cout<< " "<<pos <<" "<< i;
            return false;
        }
    
    }
}

bool insertHashDuplo(node *hash, string content, int key, int tam) {
    //cout << "Insere Hash Duplo";
    int aux=0, h1, h2;
    h1 = hash1(key, tam);
    h2 = hash2(key, tam);

    for (int i = 1; i < tam; ++i) {
        aux = hash1((h1 + i*h2), tam);
        if(hash[aux].c.empty()){
            hash[aux].c = content;
            hash[aux].deleted=false;
            cout<< " "<<aux <<" "<< i;
            return true;
        }
        else if(hash[aux].c == content){
        	cout<< " "<<aux <<" "<< i;
            return false;
        }
    }
}

bool deleteHashDuplo(node *hash, string content, int key, int tam)
{
    int aux=0, h1, h2;
    h1 = hash1(key, tam);
    h2 = hash2(key, tam);

    for (int i = 1; i < tam; ++i) {
        aux = hash1((h1 + i*h2), tam);
        if(hash[aux].c == content){
            hash[aux].c.clear();
            hash[aux].deleted=true;
            cout<< " "<<aux <<" "<< i;
            return true;
        }
        else if (hash[aux].c.empty() && (hash[aux].deleted==false))
        {
        	cout<< " "<<aux <<" "<< i;
            return false;
        }
    }

}

bool getHashDuplo(node *hash, string content, int key, int tam)
{
    int aux=0, h1, h2;
    h1 = hash1(key, tam);
    h2 = hash2(key, tam);
    for (int i = 1; i < tam; ++i) {
        aux = hash1((h1 + i * h2), tam);
        if (hash[aux].c == content)
        {
        	cout<< " "<<aux <<" "<< i;
            return true;
        }
        else if (hash[aux].c.empty() && (hash[aux].deleted==false))
        {
        	cout<< " "<<aux <<" "<< i;
            return false;
        }
    }

}


int hash1(int key, int tam) {
    return key % tam;
}

int hash2(int key, int tam) {
    return 1 + (key % (tam - 1));
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
    else if (!strcmp(argv[1], "-help")) {
        cout << " Hi :D \n This is a hash table and you have to select one out of 4 types of colision treatment in order to work properly!\n";
        cout << " This are the valid options and the way they work over it\n";
        cout << "-encadeamento:\n";
        cout << "\tsimple creates a linked list and adds the new key to the end of it\n";
        cout << "-linear:\n";
        cout << "\tin case of colisions the key increases in key + i\n";
        cout << "-quadratico\n";
        cout << "\tvery similar to linear probing but increases in i^2\n";
        cout << "-hash_duplo\n";
        cout << "\tthere's is a second hash that is used in case of colisions\n";
        return 4;
    } else
        return -1;
}

string checkString(string content)
{
	while(content.length()>101)// tem q ser 101 pq tem as aspas
	{
  	  	cout<<"ERROR"<<endl;
    	cin>>content;
	} 	
	
	return content;
}