#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>


int sum = 0;
int it = 0;
double time_all = 0.0;

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
    auto start = std::chrono::steady_clock::now();
    for (; it < a_vector.size(); it++)
    {
        sum += a_vector[it] + b_vector[it];
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration < double, std::milli> time = end - start;
    time_all += time.count();
    
    
   
}


  
int main()
{
    std::cout << std::thread::hardware_concurrency() << std::endl;
    std::vector<int> counts_threads{ 1,2,4,8,16 };
    std::vector<int> count_numbers{ 1000, 10'000, 100'000, 1'000'000 };
    for (int count_n : count_numbers)
    {
        time_all = 0.0;
        sum = 0;
        it = 0;
        std::vector<int> vector_1 = randomVector(count_n);
        std::vector<int> vector_2 = randomVector(count_n);
        
        

        for (int count_t : counts_threads)
        {
            
            std::vector<std::thread> VT;
           
            for (int i = 0; i < count_t; i++)
            {
                VT.push_back(std::thread(SumVector, ref(vector_1), ref(vector_2), it));
            }
           
            for (auto& jt : VT)
            {
                jt.join();
            }

            std::cout << count_t << " threads and " << count_n << " numbers in vector, time: " << time_all << std::endl;
        }
        
    }
    
    
    
    
   
}
