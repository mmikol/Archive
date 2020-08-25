#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tchar.h>

#define QUANTUM 40
#define BUF_SIZE 255

DWORD WINAPI MyThreadFunction( LPVOID lpParam );
bool allDone(bool arr[], int size);
int nextThread(int current, bool arr[], int size);

typedef struct MyData {
    char* name;
    int time;
} MYDATA, *PMYDATA;

int main( int argc, char *argv[] ) {
    if (argc % 2 == 0) {
        printf("%s", "Incorrect Amount of Arguments");
        ExitProcess(4);
    }
    int pairs = (argc / 2);
    PMYDATA pDataArray[pairs];
    DWORD   dwThreadIdArray[pairs];
    HANDLE  hThreadArray[pairs];

    for( int i=0, j=1; i<pairs; i++, j+=2 )
    {
        // Allocate memory for thread data.

        pDataArray[i] = (PMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                sizeof(MYDATA));

        if( pDataArray[i] == NULL )
        {
           // If the array allocation fails, the system is out of memory
           // so there is no point in trying to print an error message.
           // Just terminate execution.
            ExitProcess(2);
        }

        // Generate unique data for each thread to work with.

        pDataArray[i]->name = argv[j];
        pDataArray[i]->time = atoi(argv[j+1]);

        // Create the thread to begin execution on its own.

        hThreadArray[i] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            pDataArray[i],          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[i]);   // returns the thread identifier 


        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (hThreadArray[i] == NULL) 
        {
           ExitProcess(3);
        }
    } // End of main thread creation loop.

    // Wait until all threads have terminated.
    WaitForMultipleObjects(pairs, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for(int i=0; i<pairs; i++)
    {
        CloseHandle(hThreadArray[i]);
        if(pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;    // Ensure address is not reused.
        }
    }

    return 0;
}

DWORD WINAPI MyThreadFunction( LPVOID lpParam ) 
{ 
    HANDLE hStdout;
    PMYDATA pDataArray;

    // Cast the parameter to the correct data type.
    // The pointer is known to be valid because 
    // it was checked for NULL before the thread was created.
 
    pDataArray = (PMYDATA)lpParam;

    int remaining = pDataArray->time - QUANTUM;
    while (remaining > 0) {
        printf("%s:%d:%d\n", pDataArray->name, QUANTUM, remaining);
        pDataArray->time = remaining;
        remaining = pDataArray->time - QUANTUM;
        Sleep(1000);
    }
        
    printf("%s:%d:%s\n", pDataArray->name, pDataArray->time, "done");
    return 0; 
} 