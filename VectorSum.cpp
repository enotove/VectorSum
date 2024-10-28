#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>


int sum = 0;

std::vector<int> randomVector(int& count)
{
    std::vector<int> vector(count);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, count);
    auto rand_num([=]() mutable {return dis(gen); });
    std::generate(vector.begin(), vector.end(), rand_num);
    return vector;
}
void SumVector(std::vector<int>& a_vector, std::vector<int>& b_vector, int it)
{
    for (; it < a_vector.size(); it++)
    {
        sum += a_vector[it] + b_vector[it];
    }
    
    
   
}


  
int main()
{
    std::cout << std::thread::hardware_concurrency() << std::endl;
    size_t count_threads = 4;
    int count = 1000;
    std::vector<int> vector_1 = randomVector(count);
    std::vector<int> vector_2 = randomVector(count);
    
    
    
    for (int i = 0; i < count_threads; i++)
    {
        
        for (int j = 0; j < count; j++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<std::thread> VT;
            VT.push_back(std::thread(SumVector, ref(vector_1), ref(vector_2), j));
            for (auto& jt : VT)
            {
                jt.join();
            }
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> time = end - start;
            std::cout << "Time with " << i << ": " << time.count() << std::endl;
        }
        
    }
    
    
    
    std::cout << "Sum: " << sum << std::endl;
}
