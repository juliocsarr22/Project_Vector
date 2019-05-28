#include <iterator>             // std::begin(), std::end()
#include <functional>           // std::function
#include <algorithm>            // std::min_element

#include "gtest/gtest.h"        // gtest lib
#include "../include/vector.h"   // header file for tested functions



// ============================================================================
// TESTING VECTOR AS A CONTAINER OF INTEGERS
// ============================================================================

TEST(IntVector, DefaultConstructor)
{
    sc::vector<int> vec;

    EXPECT_EQ( vec.size(), 0 );
    EXPECT_EQ( vec.capacity(), 0 );
    EXPECT_TRUE( vec.empty() );
}


TEST(IntVector, ConstructorSize)
{
    sc::vector<int> vec(10);

    EXPECT_EQ( vec.size(), 0 );
    EXPECT_EQ( vec.capacity(), 10 );
    EXPECT_TRUE( vec.empty() );
}


TEST(IntVector, ListConstructor)
{
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    ASSERT_EQ( vec.size(), 5 );
    EXPECT_FALSE( vec.empty() );

    for( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( i+1, vec[i] );
}

TEST(IntVector, RangeConstructor)
{
    // Range = the entire vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    sc::vector<int> vec2( vec.begin(), vec.end() );
    ASSERT_EQ( vec2.size(), 5 );
    EXPECT_FALSE( vec.empty() );

    for( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( i+1, vec[i] );

    // Range is part of the vector.
    sc::vector<int> vec3( std::next( vec.begin(), 1 ), std::next( vec.begin(), 3 ) );
    ASSERT_EQ( vec3.size(), 2 );
    EXPECT_FALSE( vec3.empty() );

    for( auto i{0u} ; i < vec3.size() ; ++i )
        ASSERT_EQ( vec[i+1], vec3[i] );
}

TEST(IntVector, CopyConstructor)
{
    // Range = the entire vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    sc::vector<int> vec2( vec );
    ASSERT_EQ( vec2.size(), 5 );
    EXPECT_FALSE( vec2.empty() );

    // CHeck whether the copy worked.
    for( auto i{0u} ; i < vec2.size() ; ++i )
        ASSERT_EQ( i+1, vec2[i] );

    // Change the original vector and check
    // whether that also changes the second vec.
    vec[2] = 10;
    for( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( i+1, vec2[i] );
}

TEST(IntVector, MoveConstructor)
{
    // Range = the entire vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    sc::vector<int> vec2( std::move( vec ) );
    ASSERT_EQ( vec2.size(), 5 );
    EXPECT_FALSE( vec2.empty() );

    // CHeck whether the copy worked.
    for( auto i{0u} ; i < vec2.size() ; ++i )
        ASSERT_EQ( i+1, vec2[i] );
}

TEST(IntVector, AssignOperator)
{
    // Range = the entire vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    sc::vector<int> vec2;

    vec2 = vec;
    ASSERT_EQ( vec2.size(), 5 );
    EXPECT_FALSE( vec2.empty() );

    // CHeck whether the copy worked.
    for( auto i{0u} ; i < vec2.size() ; ++i )
        ASSERT_EQ( i+1, vec2[i] );
}

TEST(IntVector, MoveAssignOperator)
{
    // Range = the entire vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    sc::vector<int> vec2;

    vec2 = std::move( vec );
    ASSERT_EQ( vec2.size(), 5 );
    ASSERT_FALSE( vec2.empty() );
    EXPECT_EQ( vec.size(), 0 );
    EXPECT_EQ( vec.capacity(), 0 );
    EXPECT_TRUE( vec.empty() );

    // CHeck whether the copy worked.
    for( auto i{0u} ; i < vec2.size() ; ++i )
        ASSERT_EQ( i+1, vec2[i] );
}

TEST(IntVector, ListInitializerAssign)
{
    // Range = the entire vector.
    sc::vector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ( vec.size(), 5 );
    EXPECT_EQ( vec.capacity(), 5 );
    EXPECT_FALSE( vec.empty() );

    // CHeck whether the copy worked.
    for( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( i+1, vec[i] );
}

TEST(IntVector, Clear)
{
    // Range = the entire vector.
    sc::vector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ( vec.size(), 5 );
    EXPECT_EQ( vec.capacity(), 5 );
    EXPECT_FALSE( vec.empty() );

    vec.clear();

    EXPECT_EQ( vec.size(), 0 );
    EXPECT_EQ( vec.capacity(), 5 );
    EXPECT_TRUE( vec.empty() );
}

TEST(IntVector, PushFront)
{
    // #1 From an empty vector.
    sc::vector<int> vec;

    ASSERT_TRUE( vec.empty() );
    for ( auto i{0} ; i < 5 ; ++i )
    {
        vec.push_front( i+1 );
        ASSERT_EQ( vec.size(),  i+1 );
    }
    ASSERT_FALSE( vec.empty() );

    for( auto i{4u} ; i >= vec.size() ; --i )
        ASSERT_EQ( i+1, vec[i] );

    // REmove all elements.
    vec.clear();
    ASSERT_TRUE( vec.empty()  );
    for ( auto i{0} ; i < 5 ; ++i )
    {
        vec.push_front( i+1 );
        ASSERT_EQ( vec.size(),  i+1 );
    }
    ASSERT_FALSE( vec.empty() );

    for( auto i{4u} ; i >= vec.size() ; --i )
        ASSERT_EQ( i+1, vec[i] );
}

TEST(IntVector, PushBack)
{
    // #1 From an empty vector.
    sc::vector<int> vec;

    ASSERT_TRUE( vec.empty() );
    for ( auto i{0} ; i < 5 ; ++i )
    {
        vec.push_back( i+1 );
        ASSERT_EQ( vec.size(),  i+1 );
    }
    ASSERT_FALSE( vec.empty() );

    for( auto i{4u} ; i >= vec.size() ; --i )
        ASSERT_EQ( i+1, vec[i] );

    // REmove all elements.
    vec.clear();
    ASSERT_TRUE( vec.empty()  );
    for ( auto i{0} ; i < 5 ; ++i )
    {
        vec.push_back( i+1 );
        ASSERT_EQ( vec.size(),  i+1 );
    }
    ASSERT_FALSE( vec.empty() );

    for( auto i{4u} ; i >= vec.size() ; --i )
        ASSERT_EQ( i+1, vec[i] );
}

TEST(IntVector, PopBack)
{
    // #1 From an empty vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };

    while( not vec.empty() )
    {
        vec.pop_back();
        // Checke whether we have the same list except for the last.
        for( auto i{0u} ; i < vec.size() ; ++i )
            ASSERT_EQ( i+1, vec[i] );
    }
}

TEST(IntVector, PopFront)
{
    // #1 From an empty vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };

    auto start{2};
    while( not vec.empty() )
    {
        vec.pop_front();
        // Checke whether we have the same list except for the last.
        for( auto i{0u} ; i < vec.size() ; ++i )
            ASSERT_EQ( start+i, vec[i] );

        start++;
    }
}

TEST(IntVector, Front)
{
    // #1 From an empty vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };

    auto i{0};
    while( not vec.empty() )
    {
        auto current_size = vec.size();
        ASSERT_EQ( vec.front(), ++i );
        vec.front() = 100;
        ASSERT_EQ( current_size, vec.size() );
        ASSERT_EQ( vec[0], 100 );

        vec.pop_front();
    }
}
TEST(IntVector, FrontConst)
{
    // #1 From an empty vector.
    const sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    ASSERT_EQ( vec.front(), 1 );

    const sc::vector<char> vec2{ 'a', 'e', 'i', 'o', 'u' };
    ASSERT_EQ( vec2.front(), 'a' );
}

TEST(IntVector, Back)
{
    // #1 From an empty vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };

    auto i{5};
    while( not vec.empty() )
    {
        auto current_size = vec.size();
        ASSERT_EQ( vec.back(), i-- );
        vec.back() = 100;
        ASSERT_EQ( current_size, vec.size() );
        ASSERT_EQ( vec[vec.size()-1], 100 );
        vec.pop_back();
    }
}

TEST(IntVector, BackConst)
{
    // #1 From an empty vector.
    const sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    ASSERT_EQ( vec.back(), 5 );

    const sc::vector<char> vec2{ 'a', 'e', 'i', 'o', 'u' };
    ASSERT_EQ( vec2.back(), 'u' );
}

TEST(IntVector, AssignCountValue)
{
    // #1 From an empty vector.
    sc::vector<long> vec{ 1, 2, 3, 4, 5 };

    ASSERT_EQ( vec.size(), 5 );
    auto original_cap = vec.capacity();

    // Test assign with a count smaller than the original vec size.
    long value{-4};
    vec.assign( 3, value );
    ASSERT_EQ( vec.size(), 3 );
    // Capacity should be the same.
    EXPECT_EQ( vec.capacity(), original_cap );
    // Verify the elements.
    for ( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( value, vec[i] );

    // Test assign with a count GREATER than the original vec size.
    long new_value{42};
    vec.assign( 10, new_value );
    ASSERT_EQ( vec.size(), 10 );
    EXPECT_GE( vec.capacity(), original_cap );
    // Verify the elements.
    for ( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( new_value, vec[i] );
}



TEST(IntVector, OperatorBracketsRHS)
{
    const sc::vector<int> vec { 1, 2, 3, 4, 5 };
    const sc::vector<int> vec2 { 1, 2, 3, 4, 5 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( vec[i], vec2[i]);
}

TEST(IntVector, OperatorBracketsLHS)
{
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 10, 20, 30, 40, 50 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        vec[i] = vec2[i];
    for ( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( vec[i], vec2[i]);
}

TEST(IntVector, AtRHS)
{
    const sc::vector<int> vec { 1, 2, 3, 4, 5 };
    const sc::vector<int> vec2 { 1, 2, 3, 4, 5 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( vec.at(i), vec2.at(i));

    bool worked{false};
    try { vec.at( 40 ); }
    catch( std::out_of_range & e )
    { worked = true; }

    ASSERT_TRUE( worked );
}

TEST(IntVector, AtLHS)
{
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 10, 20, 30, 40, 50 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        vec.at(i) = vec2.at(i);
    for ( auto i{0u} ; i < vec.size() ; ++i )
        ASSERT_EQ( vec.at(i), vec2.at(i) );

    bool worked{false};
    try { vec.at( vec.size() ) = 100; }
    catch( std::out_of_range & e )
    { worked = true; }

    ASSERT_TRUE( worked );
}

TEST(IntVector, Capacity)
{
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    ASSERT_EQ( vec.capacity(), 5u );
    vec.reserve(10);
    ASSERT_EQ( vec.capacity(), 10u );
    vec.reserve(3); // Nothing happens here.
    ASSERT_EQ( vec.capacity(), 10u );

    auto i{0};
    for( const auto & e : vec )
        ASSERT_EQ( e, ++i );
}

TEST(IntVector, ShrinkToFit)
{
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    ASSERT_EQ( vec.capacity(), 5u );
    vec.pop_back();
    vec.pop_back();
    ASSERT_EQ( vec.capacity(), 5u );
    vec.shrink_to_fit();
    ASSERT_EQ( vec.capacity(), 3 );
    auto i{0};
    for( const auto & e : vec )
        ASSERT_EQ( e , ++i );
}

TEST(IntVector, OperatorEqual)
{
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec3 { 1, 2, 8, 4, 5 };
    sc::vector<int> vec4 { 8, 4, 5 };

    ASSERT_EQ( vec , vec2 );
    ASSERT_TRUE( not ( vec == vec3 ) );
    ASSERT_TRUE( not ( vec == vec4 ) );
}

TEST(IntVector, OperatorDifferent)
{
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec3 { 1, 2, 8, 4, 5 };
    sc::vector<int> vec4 { 8, 4, 5 };

    ASSERT_TRUE( not( vec != vec2 ) );
    ASSERT_NE( vec, vec3 );
    ASSERT_NE( vec,vec4 );
}

TEST(IntVector, InsertSingleValueAtPosition)
{
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 4, 5, 6 };

    // Insert at front
    vec.insert( vec.begin(), 0 );
    ASSERT_EQ( vec , ( sc::vector<int>{ 0, 1, 2, 4, 5, 6 } ) );
    // Insert in the middle
    vec.insert( vec.begin()+3, 3 );
    ASSERT_EQ( vec , ( sc::vector<int>{ 0, 1, 2, 3, 4, 5, 6 } ) );
    // Insert at the end
    vec.insert( vec.end(), 7 );
    ASSERT_EQ( vec , ( sc::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7 } ) );
}

TEST(IntVector, InsertRange)
{
    // Aux arrays.
    sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> source { 6, 7, 8, 9, 10 };

    // Inset at the begining.
    vec1.insert( vec1.begin(), source.begin(), source.end() );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

    // In the middle
    vec1 = vec2;
    vec1.insert( std::next( vec1.begin(), 2 ), source.begin(), source.end() );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

    // At the end
    vec1 = vec2;
    vec1.insert( vec1.end(), source.begin(), source.end() );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

    // Outside
    vec1 = vec2;
    vec1.insert( std::next( vec1.end(), 2 ) , source.begin(), source.end() );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5 } ) );

}

TEST(IntVector, InsertInitializarList)
{
    // Aux arrays.
    sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> source { 6, 7, 8, 9, 10 };

    // Inset at the begining.
    vec1.insert( vec1.begin(), { 6, 7, 8, 9, 10 } );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

    // In the middle
    vec1 = vec2;
    vec1.insert( std::next( vec1.begin(), 2 ), { 6, 7, 8, 9, 10 } );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

    // At the end
    vec1 = vec2;
    vec1.insert( vec1.end(), { 6, 7, 8, 9, 10 } );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

    // Outside
    vec1 = vec2;
    vec1.insert( std::next( vec1.end(), 2 ) , { 6, 7, 8, 9, 10 } );
    ASSERT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5 } ) );
}

TEST(IntVector, AssignCountValue2)
{
        // Initial vector.
        sc::vector<char> vec { 'a', 'b', 'c', 'd', 'e' };

        // assigning count values to sc::vector, with count < size().
        vec.assign( 3, 'x' );
        ASSERT_EQ( vec , ( sc::vector<char>{ 'x', 'x', 'x' } ) );
        ASSERT_EQ( vec.size() , 3 );
        ASSERT_EQ( vec.capacity() , 5 );

        // assigning count values to sc::vector, with count , size().
        vec = { 'a', 'b', 'c', 'd', 'e' };
        vec.assign( 5, 'y' );
        ASSERT_EQ( vec , ( sc::vector<char>{ 'y','y','y','y','y' } ) );
        ASSERT_EQ( vec.size() , 5 );
        ASSERT_EQ( vec.capacity() , 5 );

        // assigning count values to sc::vector, with count > size().
        vec = { 'a', 'b', 'c', 'd', 'e' };
        vec.assign( 8, 'z' );
        ASSERT_EQ( vec , ( sc::vector<char>{ 'z','z','z','z','z','z','z','z' } ) );
        ASSERT_EQ( vec.size() , 8 );
        ASSERT_EQ( vec.capacity() , 8 );
}

TEST(IntVector, EraseRange)
{
    // Initial vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    // removing a segment from the beginning.
    auto past_last = vec.erase( vec.begin(), std::next(vec.begin(),3) );
    ASSERT_EQ( vec.begin() , past_last );
    ASSERT_EQ( vec , ( sc::vector<int>{ 4, 5 } ) );
    ASSERT_EQ( vec.size() , 2 );

    // removing at the middle.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),1), std::next(vec.begin(),4) );
    ASSERT_EQ( std::next(vec.begin(),1) , past_last );
    ASSERT_EQ( vec , ( sc::vector<int>{ 1, 5 } ) );
    ASSERT_EQ( vec.size() , 2 );

    // removing a segment that reached the end.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),2), vec.end() );
    ASSERT_EQ( vec.end() , past_last );
    ASSERT_EQ( vec , ( sc::vector<int>{ 1, 2 } ) );
    ASSERT_EQ( vec.size() , 2 );

    // removing the entire vector.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( vec.begin(), vec.end() );
    ASSERT_EQ( vec.end() , past_last );
    ASSERT_TRUE( vec.empty() );
}

TEST(IntVector, ErasePos)
{
    // Initial vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    // removing a single element.
    vec = { 1, 2, 3, 4, 5 };
    auto past_last = vec.erase( vec.begin() );
    ASSERT_EQ( vec , ( sc::vector<int>{ 2, 3, 4, 5 } ) );
    ASSERT_EQ( vec.begin() , past_last );
    ASSERT_EQ( vec.size() , 4 );

    // removing a single element in the middle.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),2) );
    ASSERT_EQ( vec , ( sc::vector<int>{ 1, 2, 4, 5 } ) );
    ASSERT_EQ( std::next(vec.begin(),2) , past_last );
    ASSERT_EQ( vec.size() , 4 );

    // removing a single element at the end.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),vec.size()-1 ) );
    ASSERT_EQ( vec , ( sc::vector<int>{ 1, 2, 3, 4 } ) );
    ASSERT_EQ( vec.end() , past_last );
    ASSERT_EQ( vec.size() , 4 );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
