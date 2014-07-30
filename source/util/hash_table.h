/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

/**

  Implementação de uma Tabela Hash com chave do tipo string (const char *) e valor de tipo
  genérico.

  Esta implementação utiliza vetores dinâmicos para alocação de itens e resolução de conflitos.
  No melhor caso, os itens são inseridos/acessados em O(1). No pior caso, onde todos os itens
  estão inseridos em uma mesma entrada da tabela, a implementação tem complexidade O(M),
  onde M é o número de elementos presentes em uma entrada específica da tabela hash, tanto
  para inserção quanto para acesso.

 */
template <class T> class HashTable
{

public:

    // Construtores/Destrutor.
    HashTable();
    HashTable(size_t tableCapacity);
    ~HashTable();

    // Número de elementos/capacidade.
    size_t getTotalElementsCount();
    size_t getCapacity();

    // Acesso/Inserção de itens.
    T  get(const char *key);
    void set(const char *key, T value);

    bool contains(const char *key);

private:

    unsigned int getIndex(const char *key);

    size_t tableCapacity_;
    vector < pair<const char*, T> > * hashTable_;

    bool compareKeys(const char *key1, const char *key2);

};

/**
  Construtor padrão - inicializa uma HashTable com o capacidade (número de entradas)
                      padrão igual a 10.
*/
template <class T> HashTable<T>::HashTable()
{
    this->tableCapacity_ = 10;
    this->hashTable_ = new vector< pair<const char*, T> >[this->tableCapacity_]();
}

/**
  Construtor alternativo - inicializa uma HashTable com uma capacidade (número de entradas)
                           específica.
  @param
     tableCapacity - capacidade (número de entradas) da HashTable.
*/
template <class T> HashTable<T>::HashTable(size_t tableCapacity)
{
    this->tableCapacity_ = tableCapacity;
    this->hashTable_ = new vector< pair<const char*, T> >[tableCapacity]();
}

/**
  Destrutor - desaloca espaço reservado em memória para a HashTable.
*/
template <class T> HashTable<T>::~HashTable()
{
    for(size_t i = 0; i < this->tableCapacity_; i++)
    {
        vector< pair<const char*, T> > * tableEntry = &this->hashTable_[i];

        for(size_t j = 0; j < tableEntry->size(); j++)
        {
            pair<const char*, T> & item = tableEntry->at(j);
            delete [] item.first;
        }
    }

    delete [] this->hashTable_;
}

/**
  Retorna a capacidade (número de entradas) da HashTable.

  @return capacidade (número de entradas) da HashTable.
*/
template <class T> size_t HashTable<T>::getCapacity()
{
    return this->tableCapacity_;
}

/**
  Retorna a quantidade de itens correntemente inseridos na HashTable.

  @return quantidade de itens correntemente inseridos na HashTable.
*/
template <class T> size_t HashTable<T>::getTotalElementsCount()
{
    return this->hashTable_->size();
}

/**
  Calcula e retorna em qual posição (índice de entrada) da HashTable um determinado
  item deve ser inserido/modificado ou recuperado.

  @param
     key - string que define a chave do item.

  @return
     índice da entrada na tabela HashTable em que um determinado item deve ser
     inserido/modificado ou recuperado.
*/
template <class T> unsigned int HashTable<T>::getIndex(const char *key)
{
    unsigned int sum = 0;

    char * pt = (char*)key;

    while (*pt)
    {
        // Função hash:
        // Soma os valores ASCII para cada caractere, convertido para minúsculo,
        // da chave do item.
        sum += tolower( (unsigned int)*pt++ );
    }

    // Índice(X) = Soma dos valores ASCII de cada caractere de X MOD capacidade da HashTable.
    return sum % this->tableCapacity_;
}


/**
  Insere/modifica um item na HashTable. Se a chave do item não for encontrada na HashTable,
  então um novo iem será inserido. Do contrário, apenas modifica-se o valor associado
  àquele item.

  @param
     key - string que define a chave do item.

  @param
     value - valor para o item que será inserido/modificado na HashTable.
*/
template <class T> void HashTable<T>::set(const char *key, T value)
{
    // Obtém índice para inserir novo item ou tentar recuperar um item já inserido.
    unsigned int index = getIndex(key);

    // Cria cópia da chave.
    char *itemKey  = new char[strlen(key) + 1];
    strcpy(itemKey, key);

    // Se a entrada designada para o item na HashTable estiver vazia,
    // então o mesmo deverá ser inserido (primeiro item daquela entrada).
    if (this->hashTable_[index].size() == 0)
    {
        pair<const char *, T> item(itemKey, value);
        this->hashTable_[index].push_back(item);
    }
    else
    {
        size_t itemIndex;
        bool itemFound = false;

        // Do contrário, percorrem-se os itens inseridos naquela entrada da HashTable
        // até encontrar a chave do item desejado ou encontrar o fim da listas de itens.
        for (itemIndex = 0; !itemFound && itemIndex < this->hashTable_[index].size(); itemIndex++)
        {
            pair<const char*, T> & item = this->hashTable_[index].at(itemIndex);
            itemFound = compareKeys(key, item.first);
        }

        // Se o item desejado for encontrado na entrada da HashTable,
        // então seu valor associado é modificado.
        if (itemFound)
        {
            pair<const char*, T> & item = this->hashTable_[index].at(itemIndex - 1);
            item.second = value;
        }
        else
        {
            // Caso o item não for encontrado na entrada da HashTable,
            // então o mesmo será inserido.
            pair<const char *, T> item(itemKey, value);
            this->hashTable_[index].push_back(item);
        }

    }

}


template <class T> bool HashTable<T>::contains(const char *key)
{
    size_t itemIndex;
    bool itemFound = false;

    // Calcula índice da entrada em que o item deve estar na HashTable.
    unsigned int index = getIndex(key);

    // Procura item percorrendo-se todos os itens inseridos naquela entrada calculada.
    for (itemIndex = 0; !itemFound && itemIndex < this->hashTable_[index].size(); itemIndex++)
    {
        pair<const char*, T>  item = this->hashTable_[index].at(itemIndex);
        itemFound = compareKeys(key, item.first);
    }

    return itemFound;
}

/**
  Recupera um item na HashTable. Se a chave do item não for encontrada na HashTable,
  então retorna-se NULL.

  @param
     key - string que define a chave do item.

  @return
     ponteiro para o item (par [string, valor]) recuperado da HashTable ou
     NULL caso o item não seja encontrado.
*/
template <class T> T HashTable<T>::get(const char *key)
{
    T  item = (T)NULL;
    size_t itemIndex;
    bool itemFound = false;

    // Calcula índice da entrada em que o item deve estar na HashTable.
    unsigned int index = getIndex(key);

    // Procura item percorrendo-se todos os itens inseridos naquela entrada calculada.
    for (itemIndex = 0; !itemFound && itemIndex < this->hashTable_[index].size(); itemIndex++)
    {
        pair<const char*, T>  item = this->hashTable_[index].at(itemIndex);
        itemFound = compareKeys(key, item.first);
    }

    // Se o item for encontrado, então recupera-se a referência para o mesmo a qual será
    // retornada.
    if (itemFound)
    {
        item = this->hashTable_[index].at(itemIndex - 1).second;
    }


    return item;
}

/**
  Realiza uma comparação de igualdade, case INSENSITIVE, entre duas chaves da HashTable.

  @param
     key1 string que define a primeira chave a ser comparada.

  @param
     key2 string que define a segunda chave a ser comparada.

  @return
     flag que indica se as chaves são iguais (true) ou não (false).
*/
template <class T> bool HashTable<T>::compareKeys(const char *key1, const char *key2)
{
    char * s = (char*)key1;
    char * t = (char*)key2;

    bool equal = true;

    // Se as chaves apontarem para o mesmo local na memória => chaves iguais.
    if(s == t)
        return true;
    // Se APENAS uma das chaves for nula => chaves diferentes.
    else if( (s == 0 && t != 0) || (s != 0 && t == 0) )
        return false;
    // Se as chaves tiverem tamanhos diferentes => chaves diferentes.
    else if(strlen(s) != strlen(t))
        return false;


    // Realiza comparação case INSENSITIVE para cada caractere das chaves até que se
    // encontre uma diferença (chaves diferentes) ou que se alcance o fim de ambas as
    // strings (chaves iguais).
    while (*s && equal)
    {
        equal = ( tolower(*s++) == tolower(*t++) );
    }

    return equal;
}

#endif
