/**
 * @file vector.h
 * @author Janeto Erick
 * @author Julio Cesar
 * @brief Implementação da classe Vector em C++
*/

#include "iterator.h"

    namespace sc{
        template <typename T>
        class vector {

        public :
            using size_type = unsigned long; //!< The size type.
            using value_type = T; //!< The value type.
            using pointer = value_type*; //!< Pointer to a value stored in the container.
            using reference = value_type&; //!< Reference to a value stored in the container.
            using const_reference = const value_type&; //!< Const reference to a value stored in the co
            using iterator = MyIterator< T >; // See Code 3
            using const_iterator = MyIterator< const T >; // See Code 3

        private :
            size_type m_end;
            size_type m_capacity;
            T *m_storage;
            //std::unique_ptr<T[]> m_storage; //!< Data storage area for the dynamic array.

        public :        
            /**
            * @brief Cria uma lista vazia.
            */
            vector()
                : m_end(0)
                , m_capacity(1)
                , m_storage( new T[2] )
            { }
            /**
            * @brief Constrói a lista com instâncias inseridas por padrão de contagem de T.
            * @param size_       Tamanho da lista criada
            */
            explicit vector( size_type size_)
                : m_end(0)
                , m_storage( new T[size_+1])
                , m_capacity(size_)
            {}
            /**
            * @brief Destrói a lista. Os destruidores dos elementos são chamados e o armazenamento usado é alocado. Note que, se os elementos forem ponteiros, os objetos apontados não serão destruídos.
            */
            virtual ~vector( void ){
                delete [] m_storage; 
            }

            template <typename InputIt>
            /**
            * @brief Constrói a lista com o conteúdo do intervalo first, last.
            * @param first      Inicio do intevalo.
            * @param last       Fim do intervalo.
            */
            vector( InputIt &first, InputIt &last )
                : m_end(&last - &first)
                , m_capacity(&last - &first)
                , m_storage( new InputIt[&last-&first+1])
            {
                auto * temp = &first;
                for(auto i(0); i < &last-&first; ++i){
                    m_storage[i] = *temp;
                    temp++;
                }
            }
            /**
            * @brief Um construtor de cópia.
            * @param other      Onde será copiada a lista.
            */
            vector( const vector &other)
                : m_end(other.m_end)
                , m_capacity(other.m_capacity)
                , m_storage(new T[other.m_capacity+1])
            {
                for(int i(0); i < m_end; ++i)
                    m_storage[i] = other.m_storage[i];
            }
            /**
            * @brief Constrói a lista com o conteúdo da lista de inicializadores.
            * @param list     Lista de inicializadores.
            */
            vector( std::initializer_list<T> list)
                : m_end(list.size())
                , m_capacity(list.size())
                , m_storage(new T[list.size()+1])
            {}
            /**
            * @brief Copiar operador de atribuição. Substitui o conteúdo por uma cópia do conteúdo de outro.
            * @param other     O que será copiado
            */
            vector& operator =( const vector &other){
                m_capacity = other.m_capacity;
                m_end = other.m_end;
                m_storage = new T[other.m_capacity+1];

                for(int i(0); i < m_end; ++i)
                    m_storage[i] = other.m_storage[i];
            }
            /**
            * @brief Substitui o conteúdo por aqueles identificados pela lista de inicializadores.
            * @param list     Lista de inicializadores.
            */
            vector& operator =(std::initializer_list <T> list){
                while(m_capacity < list.size()){
                    m_capacity *= 2;
                }
                m_end = list.size();

                std::copy(list.begin(), list.end(), m_storage);
            }

            
            bool full( void ) { 
                return m_end == m_capacity; 
            }
            /**
            * @brief Retorna o número de elementos no container.
            */
            size_type size( void ) const{
                return m_end; 
            }
            /**
            * @brief Remove (logicamente ou fisicamente) todos os elementos do container.
            */
            void clear( void ) {
                m_end = 0; 
            }
            /**
            * @brief Retorna true se o container não contiver nenhum elemento, e false caso contrário.
            */
            bool empty( void ) const {
                return m_end == 0; 
            }
            /**
            * @brief Adiciona um valor no inicio da lista.
            * @param value     Valor a ser adicionado.
            */
            void push_front( const_reference value){
                if(full() and m_capacity != 0){
                    m_capacity *= 2;
                    T * m_storage_move = new T[m_capacity];
                    for(int i(0); i < m_end; ++i){
                        m_storage_move[i] = m_storage[i];
                    }
                    m_storage = m_storage_move;
                }else if(m_capacity == 0)
                    m_capacity = 1;

                m_end++;
            
                auto aux1 = m_end, aux2 = m_end;
                for(auto i(1); i < m_end; ++i){
                    if(i == 1){
                        aux1 = m_storage[i];
                        m_storage[i] = m_storage[i-1];
                    } else {
                        aux2 = m_storage[i];
                        m_storage[i] = aux1;
                        aux1 = aux2;
                    }

                }
                m_storage[0] = value;
            }
            /**
            * @brief Adiciona um valor ao final da lista.
            * @param value     Valor a ser adicionado.
            */
            void push_back( const_reference value){
                if(full() and m_capacity != 0){
                    m_capacity *= 2;
                    T * m_storage_move = new T[m_capacity];
                    for(int i(0); i < m_end; ++i){
                        m_storage_move[i] = m_storage[i];
                    }
                    m_storage = m_storage_move;
                }else if(m_capacity == 0)
                    m_capacity = 1;

                m_storage[m_end++] = value; 
            }
            /**
            * @brief Remove o objeto no final da lista.
            */
            void pop_back( void ){
                m_end--;
            }
            /**
            * @brief Remove o objeto no inicio da lista.
            */
            void pop_front( void ){
                for(auto i(0); i+1 < m_end; ++i){
                    m_storage[i] = m_storage[i+1];
                }
                m_end--;
            }
            /**
            * @brief Retorna o objeto no final da lista.
            */
            const_reference back( void ) const{ 
                return m_storage[m_end-1];
            }
            /**
            * @brief Retorna o objeto no final da lista.
            */
            reference back( void ){
                return m_storage[m_end-1];
            }
            /**
            * @brief Retorna o objeto no inicio da lista.
            */
            const_reference front( void ) const{ 
                return m_storage[0];
            }
            /**
            * @brief Retorna o objeto no inicio da lista.
            */
            reference front( void ){ 
                return m_storage[0];
            }
            /**
            * @brief Substitui o conteúdo da lista com cópias de um valor.
            * @param value     Valor que vai substituir.
            */
            void assign( size_type count, const_reference value){
                clear();
                m_end = count;
                if(m_end > m_capacity){
                    m_capacity *= 2;
                    m_storage = new T[m_capacity];
                }

                for(int i(0); i < m_end; ++i)
                    m_storage[i] = value;
            }
            /**
            * @brief Substitui o conteúdo de a lista com os elementos da lista de inicializadores.
            * @param list     Lista de inicializadores.
            */
            void assign( const std::initializer_list<T>& list){
                clear();
                m_end = list.size();

                std::copy(list.begin(), list.end(), m_storage);
            }

            template < typename InputItr >
            /**
            * @brief Substitui o conteúdo da lista por cópias dos elementos no intervalo First-Last.
            * @param First    Inicio do intervalo.
            * @param Last     FIm do intervalo.
            */
            void assign( InputItr first, InputItr last){
                clear();
                auto size = std::distance(&first, &last);
                m_end = size;

                std::copy(&first, &last, m_storage);
            }
            /**
            * @brief Retorna o objeto na posição do índice na matriz, sem verificação de limites.
            * @param pos     Posição do indice.
            */
            const_reference operator[]( size_type pos ) const{
                return m_storage[pos];
            }
            /**
            * @brief Retorna o objeto na posição do índice na matriz, sem verificação de limites.
            * @param pos     Posição do indice.
            */
            reference operator[]( size_type pos ) {
                return m_storage[pos]; 
            }
            /**
            * @brief retorna o objeto na posição do índice na matriz, com verificação de limites. Se pos não estiver dentro do intervalo da lista, uma exceção do tipo std :: out_of_range é lançado.
            * @param pos     Posição do indice.
            */
            const_reference at( size_type pos ) const{
                if(pos < 0 or pos >= m_end)
                    throw std::out_of_range("[at()] Cannot recover an element out of the range");
                else 
                    return m_storage[pos];
            }
            /**
            * @brief retorna o objeto na posição do índice na matriz, com verificação de limites. Se pos não estiver dentro do intervalo da lista, uma exceção do tipo std :: out_of_range é lançado.
            * @param pos     Posição do indice.
            */
            reference at( size_type pos){
                if(pos < 0 or pos >= m_end)
                    throw std::out_of_range("[at()] Cannot recover an element out of the range");
                else 
                    return m_storage[pos];
            }
            /**
            * @brief Retorna a capacidade de armazenamento interno da matriz.
            */
            size_type capacity( void ) const{ 
                return m_capacity; 
            }
            /**
            * @brief Aumenta a capacidade de armazenamento do array para um valor maior ou igual a new_cap.
            * @param new_cap     Novo valor da capacidade de armazenamento do array.
            */
            void reserve( size_type new_cap){
                if(new_cap > m_capacity){
                    m_capacity = new_cap;
                    T * m_storage_move = new T[m_capacity];
                    for(int i(0); i < m_end; ++i){
                        m_storage_move[i] = m_storage[i];
                    }
                    m_storage = m_storage_move;
                }
            }
            /**
            * @brief Solicita a remoção da capacidade não utilizada.
            */
            void shrink_to_fit( void ){ 
                m_capacity = m_end; 
            }
            /**
            * @brief Verifica se o conteúdo de lhs é igual ao de outra lista.
            * @param lhs     Lista.
            */
            bool operator==( const vector &lhs){
                if(lhs.size() != m_end)
                    return false;
                else {
                    for(int i(0); i < lhs.m_end; ++i){
                        if(lhs[i] != m_storage[i])
                            return false;
                    }
                }
                return true;
            }
            /**
            * @brief Verifica se o conteúdo de lhs é igual ao de outra lista (de forma inversa ao anterior).
            * @param lhs     Lista.            
            */
            bool operator!=( const vector &lhs){
                if(lhs.size() != m_end)
                    return true;

                for(int i(0); i < lhs.m_end; ++i){
                    if(lhs[i] != m_storage[i])
                        return true;
                }
                return false;
            }

            /**
            * @brief Retorna um iterador apontando para o primeiro item da lista. 
            */
            iterator begin( void ){
                return iterator( &m_storage[0]);
            }
            /**
            * @brief Retorna um iterador constante apontando para o primeiro item na lista.
            */
            const_iterator cbegin( void ) const{
                return const_iterator( &m_storage[0]);
            }
            /**
            * @brief Retorna um iterador apontando para a marca final na lista, isto é, a posição logo após o último elemento da lista.
            */
            iterator end( void ){
                return iterator( &m_storage[m_end]);
            }
            /**
            * @brief retorna um iterador constante apontando para a marca final na lista, ou seja, a posição logo após o último elemento da lista.
            */
            const_iterator cend( void ) const{
                return const_iterator( &m_storage[m_end]);
            }

            /**
            * @brief Adiciona valor a lista antes da posição dada pelo iterador x. O método retorna um iterador a posição do item inserido.
            * @param x     Posição dada pelo Iterador.
            * @param y     Valor a ser adicionado.         
            */
            iterator insert(iterator x, const_reference y){

                std::ptrdiff_t i = x - begin();

                if (i > m_end){
                    return begin();
                }
                reserve(m_end + 1);
                m_end++;
                iterator new_x = begin() + i;
                iterator end(&m_storage[m_end - 1]);

                while (end != new_x){
                    *end = *(end - 1);
                    end--;
                }
                *end = y;
                return new_x;
            }

            template < typename InputItr >
            /**
            * @brief Insere a partir do intervalo Inicio-Fim antes da posição dada pelo iterador x.
            * @param x     Posição dada pelo Iterador.
            * @param inicio     Inicio do intervalo.         
            * @param fim     Fim do intervalo.         
            */
            iterator insert(iterator x, InputItr inicio, InputItr fim){

                std::ptrdiff_t i = x - begin();

                if (i > m_end){
                    return begin();
                }

                int dist = std::distance(inicio, fim);
                reserve(m_end + dist);
                m_end += dist;

                iterator new_x = begin() + i;
                iterator old_end = end() - (dist + 1);
                iterator end(&m_storage[m_end - 1]);

                while (old_end != (new_x - 1)){
                    *end = *old_end;
                    old_end--;
                    end--;
                }
                fim--;
                while (fim != (inicio - 1)){
                    *end = *fim;
                    fim--;
                    end--;
                }
                return new_x;
            }
            /**
            * @brief Insere elementos da lista inicializadora lista antes da posição dada pelo iterador it.
            * @param it     Posição dada pelo Iterador.
            * @param lista     LIsta inicializadora.         
            */
            iterator insert(iterator it, const std::initializer_list<value_type> &lista){

                std::ptrdiff_t i = it - begin();

                if (i > m_end){
                    return begin();
                }

                int size = lista.size();
                reserve(m_end + size);
                m_end += size;
                iterator new_pos = begin() + i;
                iterator old_end = end() - (size + 1);
                iterator end(&m_storage[m_end - 1]);
                while (old_end != (new_pos - 1)){
                    *end = *old_end;
                    old_end--;
                    end--;
                }

                auto x = lista.begin();
                auto y = lista.end() - 1;
                while (y != (x - 1)){
                    *end = *y;
                    end--;
                    y--;
                }
                return new_pos;
            }
            /**
            * @brief Remove elementos no intervalo x-y. 
            * @param x     Inicio do intervalo.
            * @param y     Fim do intervalo.         
            */
            iterator erase(iterator x, iterator y){
                iterator passado_y = x;
                iterator atual_y = y;

                while (x != atual_y){
                    *x = *y;
                    m_end--;
                    x++;
                    y++;
                }
                return passado_y;
            }
            /**
            * @brief Remove o objeto na posição x.
            * @param x     Posição dada pelo Iterador.      
            */
            iterator erase(iterator x){
                iterator passado_last = x;

                while (x != end()){
                    *x = *(x + 1);
                    x++;
                }

                m_end--;
                return passado_last;
            }

            // [V] Element access

            pointer data( void );
            const_reference data( void ) const;

            
            void print(){

                std::cout << "[ ";
                for(auto i(0); i < m_end; ++i){
                    std::cout << m_storage[i] << " ";
                }

                std::cout << "]\n" << m_capacity << std::endl;
            }
        };
    }