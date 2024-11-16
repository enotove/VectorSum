#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>


int sum = 0;
int it = 0;


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
    setlocale(LC_ALL, "");
    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl;
    std::vector<int> counts_threads{ 1,2,4,8,16 };
    std::vector<int> count_numbers{ 1000, 10'000, 100'000, 1'000'000 };
    std::vector < std::vector<double>> time_array;
    for (int count_n : count_numbers)
    {
        sum = 0;
        it = 0;
        std::vector<int> vector_1 = randomVector(count_n);
        std::vector<int> vector_2 = randomVector(count_n);
        std::vector<double> time_numb;
        for (int count_t : counts_threads)
        {
            
            std::vector<std::thread> VT;
            
           
            auto start = std::chrono::steady_clock::now();
            for (int i = 0; i < count_t; i++)
            {
                VT.push_back(std::thread(SumVector, ref(vector_1), ref(vector_2), it));
            }
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> time = end - start;
            
            for (auto& jt : VT)
            {
                jt.join();
            }
            time_numb.push_back(time.count());
        }
        time_array.push_back(time_numb);
    }
    std::cout << '\t';
    for (int number : count_numbers)
    {
        std::cout << '\t' << number;
    }
    std::cout << std::endl;
    for (int i = 0; i < counts_threads.size(); i++)
    {
        std::cout << counts_threads[i] << " потоков\t";
        for (int j = 0; j < time_array.size(); j++)
        {
            std::cout << time_array[j][i] << '\t';
        }
        std::cout << std::endl;
    }
    
    
    
   
}
