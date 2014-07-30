/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTEGER_HASH_TABLE_H
#define INTEGER_HASH_TABLE_H

#include <cctype>
#include <vector>
using namespace std;

/**

  Implementação de uma Tabela Hash com chave do tipo string (int) e valor de tipo
  genérico.

  Esta implementação utiliza vetores dinâmicos para alocação de itens e resolução de conflitos.
  No melhor caso, os itens são inseridos/acessados em O(1). No pior caso, onde todos os itens
  estão inseridos em uma mesma entrada da tabela, a implementação tem complexidade O(M),
  onde M é o número de elementos presentes em uma entrada específica da tabela hash, tanto
  para inserção quanto para acesso.

 */
template <class T> class IntegerHashTable
{

public:

    // Construtores/Destrutor.
    IntegerHashTable();
    IntegerHashTable(size_t tableCapacity);
    ~IntegerHashTable();

    // Número de elementos/capacidade.
    size_t getTotalElementsCount();
    size_t getCapacity();

    // Acesso/Inserção de itens.
    T  get(int key);
    void set(int key, T value);

    bool contains(int key);

private:

    unsigned int getIndex(int key);

    size_t tableCapacity_;
    vector < pair<int, T> > * hashTable_;

};

/**
  Construtor padrão - inicializa uma IntegerHashTable com o capacidade (número de entradas)
                      padrão igual a 10.
*/
template <class T> IntegerHashTable<T>::IntegerHashTable()
{
    this->tableCapacity_ = 10;
    this->hashTable_ = new vector< pair<int, T> >[this->tableCapacity_]();
}

/**
  Construtor alternativo - inicializa uma IntegerHashTable com uma capacidade (número de entradas)
                           específica.
  @param
     tableCapacity - capacidade (número de entradas) da IntegerHashTable.
*/
template <class T> IntegerHashTable<T>::IntegerHashTable(size_t tableCapacity)
{
    this->tableCapacity_ = tableCapacity;
    this->hashTable_ = new vector< pair<int, T> >[tableCapacity]();
}

/**
  Destrutor - desaloca espaço reservado em memória para a IntegerHashTable.
*/
template <class T> IntegerHashTable<T>::~IntegerHashTable()
{
    delete [] this->hashTable_;
}

/**
  Retorna a capacidade (número de entradas) da IntegerHashTable.

  @return capacidade (número de entradas) da IntegerHashTable.
*/
template <class T> size_t IntegerHashTable<T>::getCapacity()
{
    return this->tableCapacity_;
}

/**
  Retorna a quantidade de itens correntemente inseridos na IntegerHashTable.

  @return quantidade de itens correntemente inseridos na IntegerHashTable.
*/
template <class T> size_t IntegerHashTable<T>::getTotalElementsCount()
{
    return this->hashTable_->size();
}

/**
  Calcula e retorna em qual posição (índice de entrada) da IntegerHashTable um determinado
  item deve ser inserido/modificado ou recuperado.

  @param
     key - string que define a chave do item.

  @return
     índice da entrada na tabela IntegerHashTable em que um determinado item deve ser
     inserido/modificado ou recuperado.
*/
template <class T> unsigned int IntegerHashTable<T>::getIndex(int key)
{
    return key % this->tableCapacity_;
}


/**
  Insere/modifica um item na IntegerHashTable. Se a chave do item não for encontrada na IntegerHashTable,
  então um novo iem será inserido. Do contrário, apenas modifica-se o valor associado
  àquele item.

  @param
     key - string que define a chave do item.

  @param
     value - valor para o item que será inserido/modificado na IntegerHashTable.
*/
template <class T> void IntegerHashTable<T>::set(int key, T value)
{
    // Obtém índice para inserir novo item ou tentar recuperar um item já inserido.
    unsigned int index = getIndex(key);

    // Se a entrada designada para o item na IntegerHashTable estiver vazia,
    // então o mesmo deverá ser inserido (primeiro item daquela entrada).
    if (this->hashTable_[index].size() == 0)
    {
        pair<int, T> item(key, value);
        this->hashTable_[index].push_back(item);
    }
    else
    {
        size_t itemIndex;
        bool itemFound = false;

        // Do contrário, percorrem-se os itens inseridos naquela entrada da IntegerHashTable
        // até encontrar a chave do item desejado ou encontrar o fim da listas de itens.
        for (itemIndex = 0; !itemFound && itemIndex < this->hashTable_[index].size(); itemIndex++)
        {
            pair<int, T> & item = this->hashTable_[index].at(itemIndex);
            itemFound = (key == item.first);
        }

        // Se o item desejado for encontrado na entrada da IntegerHashTable,
        // então seu valor associado é modificado.
        if (itemFound)
        {
            pair<int, T> & item = this->hashTable_[index].at(itemIndex - 1);
            item.second = value;
        }
        else
        {
            // Caso o item não for encontrado na entrada da IntegerHashTable,
            // então o mesmo será inserido.
            pair<int, T> item(key, value);
            this->hashTable_[index].push_back(item);
        }

    }

}

template <class T> bool IntegerHashTable<T>::contains(int key)
{
    size_t itemIndex;
    bool itemFound = false;

    // Calcula índice da entrada em que o item deve estar na IntegerHashTable.
    unsigned int index = getIndex(key);

    // Procura item percorrendo-se todos os itens inseridos naquela entrada calculada.
    for (itemIndex = 0; !itemFound && itemIndex < this->hashTable_[index].size(); itemIndex++)
    {
        pair<int, T>  item = this->hashTable_[index].at(itemIndex);
        itemFound = (key == item.first);
    }

    return itemFound;
}


/**
  Recupera um item na IntegerHashTable. Se a chave do item não for encontrada na IntegerHashTable,
  então retorna-se NULL.

  @param
     key - string que define a chave do item.

  @return
     ponteiro para o item (par [string, valor]) recuperado da IntegerHashTable ou
     NULL caso o item não seja encontrado.
*/
template <class T> T  IntegerHashTable<T>::get(int key)
{
    T item = (T)NULL;
    size_t itemIndex;
    bool itemFound = false;

    // Calcula índice da entrada em que o item deve estar na IntegerHashTable.
    unsigned int index = getIndex(key);

    // Procura item percorrendo-se todos os itens inseridos naquela entrada calculada.
    for (itemIndex = 0; !itemFound && itemIndex < this->hashTable_[index].size(); itemIndex++)
    {
        pair<int, T>  item = this->hashTable_[index].at(itemIndex);
        itemFound = (key == item.first);
    }

    // Se o item for encontrado, então recupera-se a referência para o mesmo a qual será
    // retornada.
    if (itemFound)
    {
        item = this->hashTable_[index].at(itemIndex - 1).second;
    }


    return item;
}



#endif
