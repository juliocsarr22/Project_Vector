/**
 * @file iterator.h
 * @author Janeto Erick
 * @author Julio Cesar
 * @brief Implementação da classe Iterator em C++
*/

template <typename T>
class MyIterator {

    private :
        T *current;

    public :
        // Below we have the iterator_traits common interface
        /// Difference type used to calculated distance between iterators.

        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using difference_type = std::ptrdiff_t; // <! Difference type used to calculated distance between pointers.
        using iterator_category = std::bidirectional_iterator_tag; // <! Iterator category.

        MyIterator( T * current_ = nullptr )
            : current(current_)
        { }

        MyIterator& operator =( const MyIterator& ) = default ;
        MyIterator( const MyIterator& ) = default ;
        /**
        * @brief Avança o iterador para o próximo local dentro do vetor.
        */
        MyIterator& operator ++ ( ){ // ++it
            current++;
            return *this;
        }
        /**
        * @brief Avança o iterador para o próximo local dentro do vetor.
        */
        MyIterator operator ++ ( T ){ // it++
            auto temp = *this;
            current++;
            return temp;
        }
        /**
        * @brief Volta o iterador para o local anterior dentro do vetor.
        */
        MyIterator& operator -- ( ){ // --it
            current--;
            return *this;
        }
          /**
        * @brief Volta o iterador para o local anterior dentro do vetor.
        */
        MyIterator operator -- ( T ){ // it--
            auto temp = *this;
            current--;
            return temp;
        }
        /**
        * @brief Retorna uma referência ao objeto localizado na posição apontada pelo iterador.
        */
        reference operator * ( ) const{
            return *current;
        }
        /**
        * @brief Retorna um ponteiro para a localização no vetor.
        */
        pointer operator ->( void ) const {
            assert(current != nullptr);
            return current;
        }
        /**
        * @brief Retorna um iterador apontando para o n-ésimo sucessor no vetor a partir dele.
        * @param n      N-ésimo termo que será apontado.
        * @param i       Iterador.
        */
        friend MyIterator operator +( difference_type n, MyIterator i){
            i.current += n;
            return i;
        }
        /**
        * @brief Retorna um iterador apontando para o n-ésimo sucessor no vetor a partir dele.
        * @param n      N-ésimo termo que será apontado.
        * @param i       Iterador.
        */
        friend MyIterator operator +( MyIterator i, difference_type n){
            i.current += n;
            return i;
        }
        /**
        * @brief Retorna um iterador apontando para o n-ésimo sucessor no vetor a partir dele.
        * @param n      N-ésimo termo que será apontado.
        * @param i       Iterador.
        */
        friend MyIterator operator -( difference_type n, MyIterator i){
            i.current -= n;
            return i;
        }
        /**
        * @brief Retorna um iterador apontando para o n-ésimo atecessor no vetor a partir dele.
        * @param n      N-ésimo termo que será apontado.
        * @param i       Iterador.
        */
        friend MyIterator operator -( MyIterator i, difference_type n){
            i.current -= n;
            return i;
        }
        /**
        * @brief Retorna um iterador apontando para o n-ésimo atecessor no vetor a partir dele.
        * @param n      N-ésimo termo que será apontado.
        * @param i       Iterador.
        */
        bool operator == ( const MyIterator &x ) const{
            return (current - x.current) == 0;
        }
        /**
        * @brief Retorna verdadeiro se ambos os iteradores se referirem a um diferente localização dentro do vetor, e falso caso contrário.
        */
        bool operator != ( const MyIterator &x ) const{
            return (current - x.current) != 0;
        }        
        
};