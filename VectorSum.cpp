#include <iostream>
#include <vector>
#include <random>
#include <chrono>


std::vector<int> randomVector(int& count)
{
    std::vector<int> vector(count);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, count);
    auto rand_num([=]() mutable {return dis(gen); });
    std::generate(vector.begin(), vector.end(), rand_num);
    return vector;
}
double SumVector(std::vector<int>& a_vector, std::vector<int>& b_vector)
{
    auto start = std::chrono::steady_clock::now();
    std::vector<int> sumVector(a_vector.size());
    for (int i = 0; i < a_vector.size() - 1; i++)
    {
        sumVector[i] = a_vector[i] + b_vector[i];
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double,std::milli> time = end - start;
    return time.count();
}

int main()
{
    int count = 1000;
    std::vector<int> vector_1 = randomVector(count);
    std::vector<int> vector_2 = randomVector(count);
 
    double time = SumVector(vector_1, vector_2);
    std::cout << "Time: " << time << std::endl;
}
