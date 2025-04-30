#include <vector>
#include <iostream>
#include <windows.h> // Windows API for threading

struct Query
{
    int id;
    std::vector<int> conditions;
};

std::vector<int> data; // Global data
HANDLE mutex;
int total_matches = 0;

DWORD WINAPI thread_function(LPVOID lpParam);

struct ThreadData
{
    Query *query;
};

int main()
{
    int n;
    std::cout << "Enter total number of data elements: ";
    std::cin >> n;

    data.resize(n);
    std::cout << "Enter data elements:\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> data[i];
    }

    int num_queries;
    std::cout << "\nEnter number of queries: ";
    std::cin >> num_queries;

    std::vector<Query> queries(num_queries);
    for (int i = 0; i < num_queries; i++)
    {
        int k;
        std::cout << "Enter number of conditions for Query " << i + 1 << ": ";
        std::cin >> k;

        std::cout << "Enter " << k << " condition values:\n";
        queries[i].id = i;
        queries[i].conditions.resize(k);
        for (int j = 0; j < k; j++)
        {
            std::cin >> queries[i].conditions[j];
        }
    }

    // Create mutex
    mutex = CreateMutex(NULL, FALSE, NULL);

    // Create threads
    std::vector<HANDLE> threads(num_queries);
    std::vector<ThreadData> thread_data(num_queries);

    for (int i = 0; i < num_queries; i++)
    {
        thread_data[i].query = &queries[i];
        threads[i] = CreateThread(
            NULL, 0, thread_function, &thread_data[i], 0, NULL);
    }

    // Wait for all threads
    WaitForMultipleObjects(num_queries, &threads[0], TRUE, INFINITE);

    // Clean up
    for (int i = 0; i < threads.size(); i++)
    {
        CloseHandle(threads[i]);
    }
    CloseHandle(mutex);

    std::cout << "\n\nFinal total matches found: " << total_matches << std::endl;

    return 0;
}

DWORD WINAPI thread_function(LPVOID lpParam)
{
    ThreadData *data_ptr = (ThreadData *)lpParam;
    Query *query = data_ptr->query;

    int local_count = 0;

    for (int i = 0; i < data.size(); i++)
    {
        int record = data[i];
        for (int j = 0; j < query->conditions.size(); j++)
        {
            int cond = query->conditions[j];
            if (cond != 0 && record % cond == 0)
            {
                local_count++;
                break;
            }
        }
    }

    // Safely update global count
    WaitForSingleObject(mutex, INFINITE);
    std::cout << "Thread for Query " << query->id + 1 << " found " << local_count
              << " matches. Total so far: " << (total_matches + local_count) << std::endl;
    total_matches += local_count;
    ReleaseMutex(mutex);

    return 0;
}

