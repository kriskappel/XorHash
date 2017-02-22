//REMINDER:

/*
tirar o qtd=0 depois rehash
*/

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct n {
    string c;
    struct n *prox = NULL;
    bool deleted = false;
};
typedef struct n node;

int totalColisao=0;

int linkedInsertion = 0, linkedDeletion = 0, linkedGet = 0, linearInsertion = 0, linearDeletion = 0, linearGet = 0;
int quadraticInsertion = 0, quadraticDeletion = 0, quadraticGet = 0, doubleInsertion = 0, doubleDeletion = 0, doubleGet = 0;


node *createHash(int tam);//Cria hash inicial
bool insertToHash(node *hash, string content, int colisao, int tam, bool rehash);//Insere na hash
bool getFromHash(node *hash, string content, int colisao, int tam);//Busca na hash
bool removeFromHash(node *hash, string content, int colisao, int tam);//remove da hash
node *ReHash(node *hash, int colisao, int *tam);

bool insertEncadeamento(node *hash, string content, int pos, bool rehash);
bool getEncadeamento(node *hash, string content, int pos);
bool deleteEncadeamento(node *hash, string content, int pos);

bool insertLinear(node *hash, string content, int key, int tam, bool rehash);
bool getLinear(node *hash, string content, int key, int tam);
bool deleteLinear(node *hash, string content, int key, int tam);

bool insertQuadratica(node *hash, string content, int key, int tam, bool rehash);
bool getQuadratica(node *hash, string content, int key, int tam);
bool deleteQuadratica(node *hash, string content, int key, int tam);

bool insertHashDuplo(node *hash, string content, int key, int tam, bool rehash);
bool getHashDuplo(node *hash, string content, int key, int tam);
bool deleteHashDuplo(node *hash, string content, int key, int tam);

int stringXor(string content);//Calcula função xor
int hash1(int key, int tam);//calcula h1(x)
int hash2(int key, int tam);//calcula h2(x) no caso de double hashing
int selectTreatment(char **argv);
bool CriaArquivo();
bool saidaArquivo(string c);

string checkString(string content);
//void splitString(std::string entrada, std::string &tag, std::string &content);

int main(int argc, char **argv) {
    int tam = 500, qtd = 0; //tamanho incial da hash = 500
    int colisao, flag = 0;
    int inicio, fim;
    bool status;
    double fator;
    node *hashTable = createHash(tam);
    //string tag, content; //entrada;
    char entradaTag[10], entradaContent[105];
    //TESTA SE UM PARAMETRO FOI PASSADO.
    //só a chamada do .out conta como um parametro e ele so pode passar um parametro adicional por vez,
    //nao pode escolher dois tipos de metodo de tratamento de colisao, por exemplo.
    //out<<argc;

    //cout<<*argv[1];
    bool CriaArquivo();
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
    //cin >> tag >> content;

    //cout<<argc;

    //cout<<*argv[1];

    //TODO Tratar string vazia
    while (scanf("%s %s", entradaTag, entradaContent)!=EOF)// se a tag for EOF ele para a execução
    //while(cin >> tag >> content)
    {
        string tag(entradaTag);
        string content(entradaContent);
        //cout<<"aqui2"<<endl;
        //splitString(entrada, tag, content);
        //cout<<tag<<content;
        content=checkString(content);
        if (content=="eita")
        {
            cout<<"\nERRO\n";
            return 0;
        }
        if (tag == "INSERT") {
            cout << "INSERT " << content << " ";//só pra fins de teste
            //saidaArquivo("INSERT \""+content+"\" ");
            inicio = 0;
            inicio = clock(); //inicia o clock

            content.erase(content.begin());
            content.erase(content.end()-1);

            status = insertToHash(hashTable, content, colisao, tam, false);//chama a funcao de inserção

            fim = 0;
            fim = clock();

            switch(colisao){
                case 0:
                    linkedInsertion += (fim-inicio);
                    break;
                case 1:
                    linearInsertion += (fim-inicio);
                    break;
                case 2:
                    quadraticInsertion += (fim-inicio);
                    break;
                case 3:
                    doubleInsertion += (fim-inicio);
                    break;
            }

            if (status)
                //saidaArquivo("SUCCESS\n");
                cout << " SUCCESS";
            else
                //saidaArquivo("FAIL\n");
                cout << " FAIL";
            cout<<endl;
            qtd++; //adiciona mais um na quantidade

            //cout<<endl;
            fator = (double) qtd / tam; //calcula o fator de carga
            if (fator >= 0.75)
            {
                //flag = 1; //ocorre o rehash //karine aqui para que essa flag?
                hashTable=ReHash(hashTable, colisao, &tam);
                //qtd=0;
            }

        } else if (tag == "DELETE") {
            cout << "DELETE " << content<< " ";
            //saidaArquivo("DELETE \""+content+"\" ");
            inicio = 0;
            inicio = clock(); //inicia o clock

            content.erase(content.begin());
            content.erase(content.end()-1);

            status=removeFromHash(hashTable, content, colisao, tam);

            fim = 0;
            fim = clock();

            switch(colisao){
                case 0:
                    linkedDeletion += (fim-inicio);
                    break;
                case 1:
                    linearDeletion += (fim-inicio);
                    break;
                case 2:
                    quadraticDeletion += (fim-inicio);
                    break;
                case 3:
                    doubleDeletion+= (fim-inicio);
                    break;
            }

            if (status)
                //saidaArquivo("SUCCESS\n");
                cout << " SUCCESS";
            else
                //saidaArquivo("FAIL\n");
                cout << " FAIL";
            cout<<endl;

        } else if (tag == "GET") {
            cout << "GET " << content << " ";
            //saidaArquivo("GET \""+content+"\" ");
            inicio = 0;
            inicio = clock(); //inicia o clock

            content.erase(content.begin());
            content.erase(content.end()-1);

            status=getFromHash(hashTable, content, colisao, tam);
            fim = 0;
            fim = clock();

            switch(colisao){
                case 0:
                    linkedGet += (fim-inicio);
                    break;
                case 1:
                    linearGet += (fim-inicio);
                    break;
                case 2:
                    quadraticGet += (fim-inicio);
                    break;
                case 3:
                    doubleGet += (fim-inicio);
                    break;
            }


            if (status)
                //saidaArquivo("SUCCESS\n");
                cout << " SUCCESS";
            else
                //saidaArquivo("FAIL\n");
                cout << " FAIL";
            cout<<endl;
        } else
            cout << "ERROR, UNDEFINED TAG ";

        //Karine aqui: não entendi essa parte. Perguntar para o Kristofer
        //cout << endl;
        //cin >> tag >> content;// le de novo as novas informações
        //content=checkString(content);
        //cout<<"aqui";
        //cout<<endl;
    }
    cout<<"total: "<<totalColisao<<endl;
    //string teste= "umaString";
    //cout<<teste<<endl;
    //node *nNode;
    //insertToHash(teste);
    //cout<<"string"<<endl;

    printf("Tempo encadeamento; INSERT: %dms\n", linkedInsertion);
    printf("Tempo encadeamento; GET: %dms\n", linkedGet);
    printf("Tempo encadeamento; DELETE: %dms\n", linkedDeletion);
    printf("Tempo linear; INSERT: %dms\n", linearInsertion);
    printf("Tempo linear; GET: %dms\n", linearGet);
    printf("Tempo linear; DELETE: %dms\n", linearDeletion);
    printf("Tempo quadratico; INSERT: %dms\n", quadraticInsertion);
    printf("Tempo quadratico; GET: %dms\n", quadraticGet);
    printf("Tempo quadratico; DELETE: %dms\n", quadraticDeletion);
    printf("Tempo hash duplo; INSERT: %dms\n", doubleInsertion);
    printf("Tempo hash duplo; GET: %dms\n", doubleGet);
    printf("Tempo hash duplo; DELETE: %dms\n", doubleDeletion);

    return 0;

}

node *createHash(int tam) {
    node *aux;
    //aux=(node*)malloc(sizeof(node)*tam);
    aux = new node[tam];

    return aux;
}

bool insertToHash(node *hash, string content, int colisao, int tam, bool rehash) {
    //cout << "\n===INSERCAO===\n" << "Conteudo: " << content << endl;
    //cout<<content<<endl;
    //cout<<tam<<endl;
    int key, pos;
    //cout<<"content da hash->"<<(hash+pos)->c<<endl;
    //node *newNode;
    /*newNode=new node;*/
    //strcpy(newNode->c, content.c_str());
    //newNode->c=content;//.copy(content, content.length(), 0);
    //newNode->c=content;
    key = stringXor(content); //retorna onde deve ser inserido na hash
    //saidaArquivo(key + " ");
    pos = hash1(key, tam); //faz a função k mod m
    //saidaArquivo(pos + " ");
    if(!rehash)
    {
        cout<<key;
        cout<< " "<<pos;
    }
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
        //saidaArquivo(pos + " 0 ");
        if(!rehash)
            cout<< " "<<pos<< " 0";
        //cout << "Status: Concluido com sucesso" << endl;

    }
    else if (hash[pos].c==content)
    {
        //saidaArquivo(pos + " 0 ");
        if(!rehash)
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
                insertedFlag = insertEncadeamento(hash, content, pos, rehash);
                return insertedFlag;
                break;
            }
            case 1: {
                insertedFlag=insertLinear(hash, content, key, tam, rehash);
                return insertedFlag;
                break;
            }
            case 2: {
                insertedFlag=insertQuadratica(hash, content, key, tam, rehash);
                return insertedFlag;
                break;
            }
            case 3: {
                insertedFlag = insertHashDuplo(hash, content, key, tam, rehash);
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
    //saidaArquivo(key + " ");
    cout<<key;
    pos = hash1(key, tam); //faz a função k mod m
    //saidaArquivo(pos + " ");
    cout<< " "<<pos;
    //out << "Posicao: " << pos << "\nKey: " << key << endl;
    if ((hash + pos)->c == content) {
        //cout << "Status: Concluido com sucesso" << endl;
        //saidaArquivo(pos + " 0 ");
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
    //saidaArquivo(key + " ");
    cout<<key;
    pos = hash1(key, tam); //faz a função k mod m
    //saidaArquivo(pos + " ");
    cout<<" "<<pos;
    //cout << "Posicao: " << pos << "\nKey: " << key << endl;

    //se
    if ((hash + pos)->c == content && (hash + pos)->prox==NULL) {
        //cout << "Status: Concluido com sucesso" << endl;
        //saidaArquivo(pos + " 0 ");
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
        //return false;
    }
}

node *ReHash(node *hash, int colisao, int *tam)
{
    *tam=2 * (*tam);
    node *newHash=createHash(*tam);
    node *linkeList=new node();
    //int teste=0;

    //string transferedContent;
    if(colisao > 0)
    {
        //cout<<endl;
        //cout<<"colisao mais q 0"<<endl;
        for(int i=0; i< (*tam)/2; i++)
        {
            if(!hash[i].c.empty())
            {
                //saidaArquivo("INSERT " + content + " ");
                //cout << "INSERT " << hash[i].c << " ";
                //cout<<hash[i].c;
                insertToHash(newHash, hash[i].c, colisao, *tam,true);
                //cout<<endl;
            }
        }
    }
    else
    {
        //cout<<"colisao 0"<<endl;
        for(int i=0; i<(*tam)/2; i++)
        {

            if(!hash[i].c.empty())
            {
                //insertToHash(newHash, hash[i].c, colisao, *tam);
                //cout<<"teste";
                linkeList= (hash + i);
                //cout<<linkeList->c;
                while(linkeList!=NULL)
                {
                    //teste++;
                    //saidaArquivo("INSERT " + content + " ");
                    //cout << "INSERT " << linkeList->c << " ";
                    insertToHash(newHash, linkeList->c, colisao, *tam, true);
                    linkeList=linkeList->prox;
                    //cout<<endl;
                }
            }
        }
    }
    //free(hash);
    //cout<<teste;
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
    return h;
}

bool insertEncadeamento(node *hash, string content, int pos, bool rehash) {
    //cout << "Insere Encadeado";
    int colisoes=1;

    node *auxPointer = (hash + pos);
    while (auxPointer->prox != NULL)//while pra ir até o final da lista encadeada
    {
        
        if (auxPointer->c == content)
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(colisoes + " ");
            if(!rehash)
            {
                colisoes=1;
                cout<< " "<< pos;
                cout<< " "<<colisoes;
                totalColisao=totalColisao+colisoes;
            }
            return false; //se ja achar o elemento na tabela retorna falso
        }
        //colisoes++;
        auxPointer = auxPointer->prox;
    }
    if (auxPointer->c == content)
    {
        //saidaArquivo(pos + " ");
        //saidaArquivo(colisoes + " ");
        if(!rehash)
        {
            cout<< " "<< pos;
            cout<< " "<<colisoes;
            totalColisao=totalColisao+colisoes;
        }
        return false;
    }

    //colisoes++;
    //no while ele ja foi até o final da lista, agora ele só adiciona na lista encadeada
    node *newNode = new node;
    newNode->c = content;
    newNode->prox = NULL;
    auxPointer->prox = newNode;

    //saidaArquivo(pos + " ");
    //saidaArquivo(colisoes + " ");
    if(!rehash)
    {
        //colisoes=1;
        cout<< " "<< pos;
        cout<< " "<< colisoes;
    //cout<<endl;
        //totalColisao=totalColisao+colisoes;
    }
    return true;
}

bool getEncadeamento(node *hash, string content, int pos) {
    node *auxPointer = (hash + pos);
    int colisoes=1;

    if(auxPointer->prox==NULL)
    {
        //saidaArquivo(pos + " ");
        //saidaArquivo(colisoes + " ");
        cout<< " "<< pos;
        cout<< " "<<colisoes;
        totalColisao=totalColisao+colisoes;
        return false;
    }
    while (auxPointer!= NULL)//while pra ir até o final da lista encadeada
    {
        //cout<<auxPointer->c;

        if (auxPointer->c == content)//if caso ache o nodo com o conteudo que quero
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(colisoes + " ");
            cout<< " "<< pos;
            cout<< " "<<colisoes;
            totalColisao=totalColisao+colisoes;
            return true;
        }
        //colisoes++;
        auxPointer = auxPointer->prox;

    }

    //saidaArquivo(pos + " ");
    //saidaArquivo(colisoes + " ");
    cout<< " "<< pos;
    cout<< " "<<colisoes;
    totalColisao=totalColisao+colisoes;
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

        //saidaArquivo(pos + " ");
        //saidaArquivo(colisoes + " ");
        //colisoes++;
        cout<< " "<< pos;
        cout<< " "<<colisoes;
        colisoes++;
        totalColisao=totalColisao+colisoes;
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

            //saidaArquivo(pos + " ");
            //saidaArquivo(colisoes + " ");
            //colisoes++;
            cout<< " "<< pos;
            cout<< " "<<colisoes;
            colisoes++;
            totalColisao=totalColisao+colisoes;
            return true;
        }
        auxPointer = auxPointer->prox;

    }
   
    //saidaArquivo(pos + " ");
    //saidaArquivo(colisoes + " ");
    colisoes++;
    cout<< " "<< pos;
    cout<< " "<<colisoes;
    
    totalColisao=totalColisao+colisoes;

    return false;
}

bool insertLinear(node *hash, string content, int key, int tam, bool rehash) {
    //cout << "Insere Linear";

    int pos;

    for (int i = 0; i < tam; i++)
    {
        pos=hash1(key + i, tam);
        if (hash[pos].c.empty())
        {
            hash[pos].c = content;
            hash[pos].deleted=false;
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            if(!rehash)
            {
                cout<< " "<<pos <<" "<< i;
                totalColisao=totalColisao+i;
            }
            return true;
        }
        else if(hash[pos].c == content)
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            if(!rehash)
            {
                cout<< " "<<pos <<" "<< i;
                totalColisao=totalColisao+i;
            }
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
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return false;
        }
    }
}

bool deleteLinear(node *hash, string content, int key, int tam)
{
    //cout << "delete linear";
    //int colisoes=0;
    int pos, i;

    for (i = 0; i < tam; i++)
    {
        pos=hash1(key + i, tam);
        if(hash[pos].c == content)
        {
            hash[pos].c.clear();
            hash[pos].deleted=true;
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return false;
        }

    }
    cout<< " "<<pos <<" "<< i;
    totalColisao=totalColisao+i;
}

bool insertQuadratica(node *hash, string content, int key, int tam, bool rehash) {
    //Verificar essa função
    //cout << "Insere Quadratico";
    int pos = 0;

    for (int i = 1; pos < tam; i++){
        pos = hash1(key+i+i*i, tam);
        if(hash[pos].c.empty())
        {
            hash[pos].c = content;
            hash[pos].deleted = false;
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            if(!rehash)
            {
                cout<< " "<<pos <<" "<< i;
                totalColisao=totalColisao+i;
            }
            return true;
        }
        else if(hash[pos].c == content)
        {
           // saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            if(!rehash)
            {
                cout<< " "<<pos <<" "<< i;
                totalColisao=totalColisao+i;
            }
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
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
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
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return true;
        }
        else if (hash[pos].c.empty() && hash[pos].deleted==false)
        {
            //saidaArquivo(pos + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<pos <<" "<< i;
            totalColisao=totalColisao+i;
            return false;
        }

    }
}

bool insertHashDuplo(node *hash, string content, int key, int tam, bool rehash) {
    //cout << "Insere Hash Duplo";
    int aux=0, h1, h2, i, firstValue=-1;
    h1 = hash1(key, tam);
    h2 = hash2(key, tam);

    for (i = 0; i < tam; ++i) {
        aux = hash1((h1 + i*h2), tam);
        if(aux==firstValue)
        {
            totalColisao=totalColisao+i;
            cout<< " "<< i;
            return false;
        }
        if(i==0)
        {
            firstValue= hash1((h1 + i*h2), tam);
        }
        //out<<endl;
        //cout<<"aux"<<aux<<endl;
        if(hash[aux].c.empty()){
            hash[aux].c = content;
            hash[aux].deleted=false;
            //saidaArquivo(aux + " ");
            //saidaArquivo(i + " ");
            //cout<<"teste1"<<endl;
            if(!rehash)
            {
                //cout<<"teste2"<<endl;
                cout<< " "<<aux <<" "<< i;
                totalColisao=totalColisao+i;
            }
            return true;
        }
        else if(hash[aux].c == content){
            //saidaArquivo(aux + " ");
            //saidaArquivo(i + " ");
            //cout<<"teste1"<<endl;
            if(!rehash)
            {
                //cout<<"teste2"<<endl;
                cout<< " "<<aux <<" "<< i;
                totalColisao=totalColisao+i;
            }
            return false;
        }
    }
    
}

bool deleteHashDuplo(node *hash, string content, int key, int tam)
{
    int aux=0, h1, h2;
    h1 = hash1(key, tam);
    h2 = hash2(key, tam);

    for (int i = 0; i < tam; ++i) {
        aux = hash1((h1 + i*h2), tam);
        if(hash[aux].c == content){
            hash[aux].c.clear();
            hash[aux].deleted=true;
            //saidaArquivo(aux + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<aux <<" "<< i;
            totalColisao=totalColisao+i;
            return true;
        }
        else if (hash[aux].c.empty() && (hash[aux].deleted==false))
        {
            //saidaArquivo(aux + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<aux <<" "<< i;
            totalColisao=totalColisao+i;
            return false;
        }
    }

}

bool getHashDuplo(node *hash, string content, int key, int tam)
{
    int aux=0, h1, h2;
    h1 = hash1(key, tam);
    h2 = hash2(key, tam);
    for (int i = 0; i < tam; ++i) {
        aux = hash1((h1 + i * h2), tam);
        if (hash[aux].c == content)
        {
            //saidaArquivo(aux + " ");
            //saidaArquivo(i + " ");
            totalColisao=totalColisao+i;
            cout<< " "<<aux <<" "<< i;
            return true;
        }
        else if (hash[aux].c.empty() && (hash[aux].deleted==false))
        {
            //saidaArquivo(aux + " ");
            //saidaArquivo(i + " ");
            cout<< " "<<aux <<" "<< i;
            totalColisao=totalColisao+i;
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
        return "eita";
    }

    return content;
}

bool CriaArquivo(){
    FILE *arq;

    arq = fopen("SaidaHashTable.txt", "w");  //
    if (arq == NULL) // Erro ao abrir o arquivo
        return false;
    else
        return true;

    }

bool saidaArquivo(string c){
    /*FILE *arq;
    int result;

    arq = fopen("SaidaHashTable.txt", "r+");  //
    if (arq == NULL) // Erro ao abrir o arquivo
    {
        return false;
    }
    result = fprintf(arq, c.c_str());
    fclose(arq);
    if (result == EOF) //Se a função NÃO for executada com sucesso, fputs retorna a constante EOF.
        return false;
    else
        return true;*/
    }

/*void splitString(std::string entrada, std::string &tag, std::string &content) {

    std::string delims = "\"";
    std::string results[2];
    size_t lastOffset = 0;
    int i = 0;

    while(true)
    {
        size_t offset = entrada.find_first_of(delims, lastOffset);
        results[i] = entrada.substr(lastOffset, offset - lastOffset);
        i++;
        if (offset == std::string::npos)
            break;
        else
            lastOffset = offset + 1; // add one to skip the delimiter
    }

    tag = results[0];
    content = results[1];
}*/
